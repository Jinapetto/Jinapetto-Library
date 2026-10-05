## 説明
互いに重ならない半開区間 `[l, r)` と、それぞれに付いた値 `val` を `std::set` で管理する。
`update` では、隣り合っていて値も同じ区間は自動で1つにまとまる(値が違えば隣り合ったまま別の区間として残る)。
値を使わない場合は `insert` / `erase` だけで普通の区間集合として使える。

- `get(p)` : `p` を含む区間のイテレータ。無ければ `end()`
- `covered(p)` : 点 `p` がどこかの区間に含まれるか
- `covered(l, r)` : `[l, r)` 全体が1つの区間に含まれるか(`l == r` なら true)
- `get_val(p)` : `p` を含む区間の値。無ければ `identity`
- `get_mex(p = 0)` : `p` 以上で、どの区間にも含まれない最小の点
- `update(l, r, val)` : `[l, r)` を値 `val` で上書きする
- `insert(l, r)` : `update(l, r, VAL())` と同じ
- `erase(l, r)` : `[l, r)` を取り除く。はみ出した区間は切り詰める
- `begin()` / `end()` : 全区間を `l` の昇順に走査する(要素は `l`, `r`, `val` を持つ)

`update` / `insert` / `erase` は `add`, `del` を渡せる。区間を消すたびに `del(l, r, val)`、作るたびに `add(l, r, val)` が呼ばれる。
1回の操作で区間が一時的に消えて作り直されることがあるので、`add` と `del` は互いにちょうど逆の処理にすること。
```cpp
ll len = 0; // 覆われている長さの合計
s.insert(l, r, [&](ll l, ll r, ll){ len += r - l; }, [&](ll l, ll r, ll){ len -= r - l; });
```
## コンストラクタ
- `IntervalSet<T, VAL = long long> s(identity = VAL())` : 空の集合
- `IntervalSet<T, VAL> s(vector<VAL> v, identity = VAL())` : `v` の、同じ値が続く部分ごとに区間を作る(`identity` と同じ値の部分も区間になる)
## 計算量
- 取得・判定系 : O(log N)
- `update` / `insert` / `erase` : ならし O(log N)
- vector からの構築 : O(N log N)
## 参考文献
けんちょんさんのライブラリ https://github.com/drken1215/algorithm
## verify
https://atcoder.jp/contests/abc478/submissions/79806340

## 備考
- 元のコードから `operator[]`, `same`, `lower_bound`, `operator<<` を削除
- 元のコードの不具合を2つ修正
  - 負の座標で長さ0の区間が残る(`Node(l, 0, ...)` → `numeric_limits<T>::lowest()`)
  - `l == r` の `erase` で区間が割れる / `update` で長さ0の区間が入る(先頭で `l >= r` なら return)
- `get_mex` は値の違う区間が接していると誤る(`[0,3)=1, [3,5)=2` で `get_mex(0) = 3`)。`insert` だけで使うなら正しい
