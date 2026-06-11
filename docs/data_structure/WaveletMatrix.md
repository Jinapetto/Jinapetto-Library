## 説明
Wavelet Matrixです。
## コンストラクタ
WaveletMatrix<T> (vector<T> a): aでWaveletMatrixを生成する。

access(k) k番目の要素の値を得る。

kth_smallest(l, r, k) [l, r)の範囲でk(0-indexed)番目に小さい値を返す。

kth_largest(l, r, k) [l, r)の範囲でk(0-indexed)番目に大きい値を返す。

range_freq(l, r, upper) [l, r)の範囲でupper未満の要素の個数を返す。

prev_value(l, r, lower) l, rの範囲でupper未満の最後の値を返す。

next_value(l, r, lower) l, rの範囲でlower以上の最初の値を返す。
## 計算量
構築 $O(N\log{N})$

クエリ $O(\log{N})$
## 参考文献
https://nyaannyaan.github.io/library/data-structure-2d/wavelet-matrix.hpp.html
## verify
https://judge.yosupo.jp/submission/248194
## 備考
Wavelet Matrixといえば2次元クエリですが、よくわかっておらず対応してません。

定数倍は悪いですが、RangeTreeで対応できると思いたいです。
