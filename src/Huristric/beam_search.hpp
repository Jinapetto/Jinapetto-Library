// ========================================================================
// 高速 HashMap (Open Addressing)
// ========================================================================
template <class Key, class T>
struct HashMap {
public:
    explicit HashMap(uint32_t n) : n_(n), valid_(n, false), data_(n) {}
    pair<bool, int> get_index(Key key) const {
        Key i = key % n_;
        while (valid_[i]) {
            if (data_[i].first == key) return {true, i};
            if (++i == n_) i = 0;
        }
        return {false, (int)i};
    }
    void set(int i, Key key, T value) {
        valid_[i] = true;
        data_[i] = {key, value};
    }
    T get(int i) const { return data_[i].second; }
    void clear() { fill(valid_.begin(), valid_.end(), false); }
private:
    uint32_t n_;
    vector<bool> valid_;
    vector<pair<Key, T>> data_;
};

// ========================================================================
// ユーザー定義構造体のインターフェース仕様
// ========================================================================

struct Node {
    // 履歴復元と差分適用のための最小限のデータ (行動IDなど)
};

struct Cand {
    int leaf;           // 親ノードのインデックス
    bool active;        // ビームに残ったかどうかのフラグ
    int eval_score;     // 評価値 (大きいほど良い)
    uint64_t hash;      // 重複除去用 Zobrist Hash
    bool is_finished;   // ゴール到達フラグ

    Node to_node() const {
        return {};
    }
};

struct State {
    void apply(const Node& node) { }
    void revert(const Node& node) { }
    void expand(const Cand& cand, int next_leaf_idx, vector<Cand>& next_cand) { }
};

// ========================================================================
// Beam Search Engine
// ========================================================================

template <class State, class Cand, class Node>
struct BeamSearch {
    State state;
    vector<Node> trace, tour, next_tour;
    vector<int> leaf, next_leaf;
    vector<Cand> cand, next_cand;
    HashMap<uint64_t, bool> seen;

    double time_limit_sec;
    int best_score;          
    vector<Node> best_path;  

    BeamSearch(const State& initial_state, const Cand& initial_cand, 
               int max_turn, int max_beam_width, int max_branching,
               double time_limit_sec = 1.95) 
        : state(initial_state), 
          seen(max_beam_width * max_branching * 2), 
          time_limit_sec(time_limit_sec),
          best_score(-1e9) {
        
        trace.reserve(max_turn + 1);
        int max_cand_size = max_beam_width * max_branching;
        cand.reserve(max_cand_size);
        next_cand.reserve(max_cand_size);
        leaf.reserve(max_beam_width + 1);
        next_leaf.reserve(max_beam_width + 1);
        int max_tour_size = max_beam_width * 10;
        tour.reserve(max_tour_size);
        next_tour.reserve(max_tour_size);

        cand.push_back(initial_cand);
        leaf.push_back(0);
    }

    vector<Node> run(int total_turns, int initial_beam_width, int min_beam_width = 100) {
        int M = initial_beam_width;
        auto start_time = chrono::high_resolution_clock::now();
        auto last_check_time = start_time;

        for (int turn = 0; turn < total_turns; ++turn) {
            if (cand.empty()) break; 

            // // Time Management (動的ビーム幅調整)
            // if (turn > 0) {
            //     auto now = chrono::high_resolution_clock::now();
            //     double elp = chrono::duration<double>(now - last_check_time).count();
            //     double elapsed_total = chrono::duration<double>(now - start_time).count();
            //     double rem = time_limit_sec - elapsed_total;

            //     if (rem > 0) {
            //         double ratio = (rem / (total_turns - turn)) / (elp / 256.0);
            //         M = max(min_beam_width, (int)(M * sqrt(ratio)));
            //     } else {
            //         M = min_beam_width;
            //     }
            //     last_check_time = now;
            // }

            // step関数が true を返した場合、ゴールが見つかったため探索終了
            if (step(turn, M)) {
                break;
            }
        }

        // ループを抜けた段階で best_path が空なら、制限ターン到達時に未ゴールの候補からベストを探す
        if (best_path.empty()) {
            for (int i = 0; i < (int)cand.size(); ++i) {
                if (cand[i].eval_score > best_score) {
                    best_score = cand[i].eval_score;
                    best_path = restore(i);
                }
            }
        }

        return best_path;
    }

private:
    // ゴール到達時に true を返す
    bool step(int turn, int M) {
        trace.push_back(cand.back().to_node());

        if (turn == 0) {
            if (cand[0].is_finished) {
                best_score = cand[0].eval_score;
                best_path = { cand[0].to_node() };
                cand.clear();
                return true;
            }
            state.expand(cand[0], 0, next_cand);
            cand.swap(next_cand);
            return false;
        }

        // ==========================================
        // 候補の選択と重複除去 & ゴール抽出
        // ==========================================
        vector<int> idx(cand.size());
        iota(idx.begin(), idx.end(), 0);
        // 評価値の降順にソート (ここでソートするため、最初に見つかる is_finished がそのターンの最善解になる)
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return cand[a].eval_score > cand[b].eval_score;
        });

        seen.clear();
        int n_selected = 0;

        for (int i : idx) {
            auto [found, pos] = seen.get_index(cand[i].hash);
            if (!found) {
                seen.set(pos, cand[i].hash, true);
                
                if (cand[i].is_finished) {
                    // 1つでもゴール到達候補が見つかれば、即座に経路を復元して探索を打ち切る
                    best_score = cand[i].eval_score;
                    best_path = restore(i);
                    return true; 
                } else {
                    cand[i].active = true;
                    n_selected++;
                    if (n_selected >= M) break;
                }
            }
        }

        // ==========================================
        // 状態の遷移と展開
        // ==========================================
        next_tour.clear();
        next_leaf.clear();
        next_cand.clear();

        int f = 0;
        int li = leaf.size() - 1;

        for (int i = (int)cand.size() - 1; i >= 0; --i) {
            if (!cand[i].active) continue; 

            // 1. LCA（最小共通祖先）の距離を計算
            int lca = 0;
            int current_val = leaf[li];
            for (int j = li - 1; j >= cand[i].leaf; --j) {
                lca = max(lca, current_val - leaf[j]);
                current_val = leaf[j];
            }

            // 2. LCAまで状態をロールバック
            for (int j = turn + f - 1; j >= turn - lca; --j) {
                state.revert(trace[j]);
            }
            f = 1;

            // 3. 捨てた枝を next_tour に退避
            next_tour.insert(next_tour.end(), trace.begin() + turn - lca, trace.end());
            trace[turn] = cand[i].to_node();

            // 4. 過去に退避した tour から、現在進もうとしている枝を trace に復元する
            int prog = 0;
            for (int j = cand[i].leaf; j < li; ++j) {
                int rank = leaf[j + 1] - leaf[j];
                if (prog < rank) {
                    copy(tour.begin() + leaf[j], tour.begin() + leaf[j + 1] - prog, trace.begin() + turn - rank);
                    prog = rank;
                }
            }

            // 5. 復元した枝に沿って状態を適用 (LCAから現在のターンまで)
            for (int j = turn - lca; j <= turn; ++j) {
                state.apply(trace[j]);
            }

            // 6. 次の手を展開
            state.expand(cand[i], next_leaf.size(), next_cand);
            
            // 7. 枝のインデックスを記録
            next_leaf.push_back(next_tour.size());
            li = cand[i].leaf;
        }

        tour.swap(next_tour);
        leaf.swap(next_leaf);
        cand.swap(next_cand);
        
        return false;
    }

    vector<Node> restore(int idx) const {
        vector<Node> ret(trace.begin() + 1, trace.end());
        
        int len = ret.size();
        int prog = 0;
        for (size_t i = cand[idx].leaf; i < leaf.size() - 1; ++i) {
            int w0 = leaf[i];
            int w1 = leaf[i + 1];
            int rank = w1 - w0;
            if (prog < rank) {
                copy(tour.begin() + w0, tour.begin() + w1 - prog, ret.begin() + len - rank);
                prog = rank;
            }
        }
        ret.push_back(cand[idx].to_node());
        return ret;
    }
};
