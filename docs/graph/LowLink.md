## 説明
LowLinkです。

vector<int> arti に関節点が、

vector<pair<int,int>> bridge に橋が入る
## コンストラクタ
LowLink(vector<vector<int>> g) 初期化

build() 構築
## 計算量
$O(V+E)$
## 参考文献
https://ei1333.github.io/luzhiled/snippets/graph/lowlink.html
## verify
https://judge.yosupo.jp/submission/248075

多重辺の対応を雑にしたため計算量が悪化してます。

ICPC2019 yokohama One-Way Conveyors 

https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=9840931#1

DFS木を復元するために改造したもの

https://atcoder.jp/contests/abc334/submissions/61112922
## 備考
