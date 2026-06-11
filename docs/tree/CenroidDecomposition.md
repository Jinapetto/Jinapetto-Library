## 説明
木の重心分解です

koprickyさんのライブラリを改変したもの

使い方はソースコードのコメントにも書いてあるため，読んでください．
## コンストラクタ
CD (int n) サイズｎの木で初期化

## add_edge(int u,int v)
$u$ と $v$ の間に辺を張る．

## build()
重心分解を行う．

parはその重心を取り除いた時の部分グラフの重心たちを結んだ木(?)を表している．

コメントが書かれた場所に適切な処理を書く．

## 計算量

追加した処理が部分木の大きさを $N$ として $O(N)$ で行える場合，

O(NlogN)

## 参考文献
https://kopricky.github.io/code/GraphDecomposition/centroid_decomposition.html
## verify
https://atcoder.jp/contests/abc291/submissions/59126881

https://atcoder.jp/contests/abc359/submissions/61736519

後者のほうが参考になりそう．
## 備考
