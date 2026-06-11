## 説明
のいみさんのライブラリを改変したcrtです。

ExtGCDに依存してます。
## コンストラクタ
pair<ll,ll> crt(vector<ll> b, vector<ll> c)

$x≡b_i(mod c_i),∀i∈{0,1,⋯,n−1}$
を解きます

解がない時は{0,-1}を、 $|b|=0$ のときは{0,1}を返します。
## 計算量
$O(\log{lcm(m_i)})$
## 参考文献
https://x.com/noimi_kyopro/status/1834880895200719196
## verify
https://atcoder.jp/contests/abc186/submissions/me
## 備考
