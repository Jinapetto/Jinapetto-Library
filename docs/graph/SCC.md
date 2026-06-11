## 説明
SCCです
## コンストラクタ
scc(int n) 頂点数nで初期化

add_e(int from,int to) fromからtoに辺を張る

vector<vector<int>> build() 構築、内側のリストと強連結成分が一対一に対応する。リストはトポロジカルソートされる。
## 計算量
構築 $O(N+M)$
## 参考文献
https://ei1333.github.io/luzhiled/snippets/graph/strongly-connected-components.html
## verify
https://judge.yosupo.jp/submission/252371
## 備考
