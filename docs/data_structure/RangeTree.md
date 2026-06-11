## 説明
いわゆる2D_segtreeです。

xとyが疎のときにも使えます。

事前に座圧する必要がありません。

時間計算量は2D_segtreeと同じ、空間計算量が悪化してます。

segtreeに依存してます。
## コンストラクタ
RangeTree<T,op,e> (pair<ll,ll> cand, vector<T> val)

T,op,eはsegtreeと同様

pair<ll,ll> cand に使う座標を入れておく（そのため更新がある場合、クエリ先読みが必須）

vector<T> candに入れた座標の初期値

void update(ll x, ll y, T val) (x,y)の値をvalに更新

T query(ll lx, ll ly, ll rx, ll ry)　lx <= x, x < rx, ly <= y, y < ryを満たす(x,y)について計算
## 計算量
candに入れた座標のサイズを $N$ とすると

構築 $O(N\log{N})$

クエリ $O(\log^2{N})$

空間 $O(N\log{N})$
## 参考文献
https://kopricky.github.io/code/SegmentTrees/rangetree_pointupdate.html

をのいみさんが改変した

https://x.com/noimi_kyopro/status/1834880895200719196

をさらに改変
## verify
https://judge.yosupo.jp/submission/246654
## 備考
