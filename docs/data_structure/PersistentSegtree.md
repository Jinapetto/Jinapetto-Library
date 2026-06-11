# per_segtree (永続セグメント木)

## 説明
うしさんのライブラリを ACL っぽくして根の管理を version で行うように改変した永続セグ木です。

## コンストラクタ

* `per_segtree()`
  空の永続セグメント木を構築します。

* `per_segtree(int n)`
  長さ $n$ の配列を単位元 `e()` で初期化し、バージョン `0` として構築します。

* `per_segtree(const std::vector<S>& v)`
  配列 `v` の要素で初期化し、バージョン `0` として構築します。

## メソッド

* `void query_reserve(int q)`
  今後発生する更新クエリの回数 $q$ を指定し、内部のメモリプールを事前に確保（`reserve`）します。

* `int set(int version, int k, const S& x)`
  `version` 番目の状態をもとに、インデックス `k` の要素を `x` に更新した新しいバージョンを生成し、その新しいバージョン番号を返します。

* `int apply(int version, int k, const S& x)`
  `version` 番目の状態をもとに、インデックス `k` の要素に `x` を作用（`op(元の値, x)`）させた新しいバージョンを生成し、その新しいバージョン番号を返します。

* `S get(int version, int k) const`
  `version` 番目の状態における、インデックス `k` の要素を返します。

* `S prod(int version, int a, int b) const`
  `version` 番目の状態における、半開区間 $[a, b)$ の要素をマージした結果を返します。$a = b$ または $a > b$ の場合は `e()` を返します。

* `S all_prod(int version) const`
  `version` 番目の状態における、配列全体の要素をマージした結果を返します。

  * `template <class F> int max_right(int version, int l, F f) const`
  `version` 番目の状態において、以下の条件をすべて満たす最大の $r$ を返します。
  * $l \le r \le n$
  * `f(prod(version, l, r)) == true`
  ※ `f(e()) == true` である必要があります。

* `template <class F> int min_left(int version, int r, F f) const`
  `version` 番目の状態において、以下の条件をすべて満たす最小の $l$ を返します。
  * $0 \le l \le r$
  * `f(prod(version, l, r)) == true`
  ※ `f(e()) == true` である必要があります。

## 計算量
$N$ を配列の要素数とします。

構築: $O(N)$
クエリ: $O(\log N)$
all_prodだけ $O(1)$

## 参考文献
https://ei1333.github.io/library/structure/segment-tree/persistent-segment-tree.hpp.html

## verify
ABC453 G
https://atcoder.jp/contests/abc453/submissions/74989969

max_right の verify ACL Contest J
https://atcoder.jp/contests/practice2/submissions/74989932

## 備考