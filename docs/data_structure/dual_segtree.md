## 説明
双対セグメント木です．

ei1333さんの実装をもとに，ACLと同じ感触で利用できるよう，改造しました．

元の実装はFに!=が定義されている必要がありましたが，それはなくしました．

2025/04/14 vector で初期化するやつがバグっていたのでなおしました
2025/10/22 composition が可換な演算でないときに f <- g になっていたのを g <- f にしました。(ACLと同じ)
## コンストラクタ
dual_segtree<F,F cp(F, F), F id()> seg(int N)

長さNの双対セグ木を構築．
## get(int k)
一点取得
## apply(int l, int r,F f)
更新
## 計算量
構築 $O(N)$
更新 $O(logN)$
クエリ $O(logN)$
## 参考文献
https://ei1333.github.io/library/structure/segment-tree/dual-segment-tree.hpp.html
## verify
https://judge.yosupo.jp/submission/279068

https://atcoder.jp/contests/abc342/submissions/61698053

https://atcoder.jp/contests/abc428/submissions/70338801
## 備考
