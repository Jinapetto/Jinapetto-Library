## 説明
最大独立集合を求めます。捕グラフを考えることで最大クリークと同値になります。
## vector\<int\> max_independent(int n, vector\<vector\<bool\>\> g)
頂点数 $N$ の隣接行列が $g$ となるグラフの最大独立集合を構成するグラフの idx を返します。

## 計算量
$O(N2^{\frac{N}{2}})$
## 参考文献
https://img.atcoder.jp/code-thanks-festival-2017-open/editorial.pdf?_gl=1*1m8uhx0*_ga*Mjk1MzkxMjMuMTY2OTQ2Mzg2NA..*_ga_RC512FD18N*czE3NTEzNzczMTgkbzEzODYkZzEkdDE3NTEzNzczNTIkajI2JGwwJGgw
## verify
https://atcoder.jp/contests/code-thanks-festival-2017-open/submissions/67223562
## 備考
集合のサイズしか verify してません。