## 説明
HLDです。
## コンストラクタ
HLD (int n)

大きさnで初期化

## add_edge (int u,int v)

uとvの間に辺を張る

## buid() 

構築

## int lca (int u,int v) 

uとvのlcaを返す

## for_each (int u,int v,F f) 

uからvのパスに含まれる頂点クエリを処理する　fには(l,r)が渡される。

## for_each_edge (int u,int v,F f) 

uからvのパスに含まれる辺クエリを処理する　fには(l,r)が渡される。

## for_subtree (int u,int v,F f)

uの部分木のクエリを処理する　fには(l,r)が渡される。

## 計算量
構築 $O(N)$

lca $O(\log{N})$

for_each fが $O(logN)$ 回呼び出される

for_each_edge fが $O(logN)$ 回呼び出される

for_subtree fが $1$ 回呼び出される
## 参考文献
https://ei1333.github.io/luzhiled/snippets/tree/heavy-light-decomposition.html
## verify
https://judge.yosupo.jp/submission/247157

https://atcoder.jp/contests/ABC294/submissions/51537719

https://atcoder.jp/contests/abc406/submissions/65922881
## 備考
辺に値を入れる場合は、子に対して値を張る。

AB間の辺に重みを載せたいとき

if(par[A] != B) swap(A, B);

seg.set(vid[A], val);

などとするとよい
