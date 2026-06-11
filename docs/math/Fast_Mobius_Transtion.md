## 説明
高速メビウス変換です．

上の方は

$s$ を含むような上位集合 $T$ についての $f(T)$ の総和 $g(s) = \sum_{s \subseteq T} f(T)$ の逆変換，
$s$ を含む上位集合 $T$ についての包徐

下の方は

$S$ に含まれる下位集合 $t$ についての $f(t)$ の総和 $g(S) = \sum_{t \subseteq S} f(t)$ の逆変換，
$S$ に含まれる下位集合 $t$ についての $f(t)$ の包徐

を計算します．

## FMT<T>(int n,vector<T> f)
メビウス変換を行います． $n = 2^{|f|}$ となるようにしてください．

## 計算量
$O(n2^n)$

## 参考文献
https://kopricky.github.io/code/Computation_Advanced/fast_mobius_transform.html

## verify
https://atcoder.jp/contests/abc349/submissions/61532456
## 備考
上の方はverifyしてないです．
