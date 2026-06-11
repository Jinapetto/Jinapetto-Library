## 説明
Convex Hull Trick(Monotone Add) です。
## コンストラクタ
CHT<isMin = true> isMin = true で最小値取得、isMin = falseで最大値取得

add(ll a,ll b) ax+bの直線を追加　制約：aが広義単調増加

query(ll x) xの最小/最大を返す。

query_monotone_inc (ll x) xの最小/最大を返す。制約：xが広義単調増加

query_monotone_dec (ll x) xの最小/最大を返す。制約：xが広義単調減少
## 計算量
add(ll a,ll b) amortized $O(1)$

query(ll x) $O(\log{N})$

query_monotone_inc (ll x) amortized $O(1)$

query_monotone_dec (ll x) amortized $O(1)$
## 参考文献
https://ei1333.github.io/library/structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp
https://x.com/noimi_kyopro/status/1834880895200719196
## verify
https://atcoder.jp/contests/abc289/submissions/59082672
## 備考
