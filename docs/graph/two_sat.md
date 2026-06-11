## 説明
two_sat です
SCC に依存しています
## コンストラクタ
```
two_sat ts(int n)
```
two_sat(int n) 頂点数 $N$ で初期化
## add_clause
```
void ts.add_clause(int i, bool f, int j, bool g)
```
(x_i = f) ∨ (x_j = g) というクローズを足します
## satisfiable
```
bool ts.satisfiable()
```
条件を足す割当が存在するかどうかを判定する。割当が存在するならば `true` 、そうでないなら `false` を返す。
## answer
```
vector<bool> ts.answer()
```
クローズを満たす割当を返す。satisfiable を呼んで `true` が返ってきたとき以外は未定義
## 計算量
初期化 : $O(N)$

add_edge : $O(1)$

satisfiable : $O(N)$

answer : $O(N)$

## 参考文献
https://atcoder.github.io/ac-library/master/document_ja/twosat.html
## verify
https://judge.yosupo.jp/submission/278757
## 備考
