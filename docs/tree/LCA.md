## 説明
LCAを求めます。

spase tableを利用したLCAが見つからなかったため、自分で書きました。

バグがある可能性が高いです。
## コンストラクタ
EulerTour(int n) 初期化

add_edge(int a,int b) aからbの辺を追加

lca(int a,int b) aとbのlcaを返す。
## 計算量
構築 $O(N\log{N})$

クエリ $O(1)$
## 参考文献
https://qiita.com/recuraki/items/72e37eb9be9f71bc623a

spase table: https://ei1333.github.io/luzhiled/snippets/structure/sparse-table.html
## verify
https://judge.yosupo.jp/submission/247159

https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=9840931#1
## 備考
連結でなくてもbuild(int root)に根を渡せば動いてくれます
