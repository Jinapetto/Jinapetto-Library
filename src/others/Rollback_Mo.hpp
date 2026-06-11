template<typename T,
         void (*add_l)(int),
         void (*add_r)(int),
         T (*out)(int, int),
         void (*snapshot)(),
         void (*rollback)(),
         void (*reset)()>
class Mo {
private:
    int width;
    vector<int> idx;
    vector<int> L, R;
    int N, Q;

public:
    Mo(int n, int q) {
        N = n;
        Q = q;
        width = max<int>(1, 1.0 * N / max<double>(1.0, sqrt(Q * 2.0 / 3.0)));
        L.reserve(q);
        R.reserve(q);
        idx.resize(q, 0);
        iota(idx.begin(), idx.end(), 0);
    }

    void add_q(int l, int r) {
        assert(L.size() < Q);
        L.push_back(l);
        R.push_back(r);
    }

    vector<T> run() {
        sort(idx.begin(), idx.end(), [&](const int a, const int b) {
            const int c = L[a] / width, d = L[b] / width;
            return (c == d) ? (R[a] < R[b]) : (c < d);
        });

        vector<T> ret(Q);
        reset();
        snapshot();
        for(int i = 0; i < Q; i++) {
            int pos = idx[i];
            if(R[pos] - L[pos] < width) {
                for(int j = L[pos]; j < R[pos]; j++) add_r(j);
                ret[pos] = out(L[pos], R[pos]);
                rollback();
                snapshot();
            }
        }
        int cur_r = 0, pre_block = -1;
        for(int i = 0; i < Q; i++) {
            int pos = idx[i];
            if(R[pos] - L[pos] < width) continue;
            int block = L[pos] / width;
            if(pre_block != block) {
                reset();
                pre_block = block;
                cur_r = (block + 1) * width;
            }
            while(cur_r < R[pos]) add_r(cur_r++);
            snapshot();
            for(int j = (block + 1) * width - 1; j >= L[pos]; j--) add_l(j);
            ret[pos] = out(L[pos], cur_r);
            rollback();
        }
        return ret;
    }
};
