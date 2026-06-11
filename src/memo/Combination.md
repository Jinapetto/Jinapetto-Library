## 二項係数頻出公式
$\sum_{i = 0}^n \binom{n}{i} = 2n$

$\sum_{i = 0}^{\lfloor \frac{n}{2} \rfloor} \binom{n}{2i} = 2^{n - 1}$

$\sum_{i = 0}^k \binom{n + i}{i} = \binom{n + i + 1}{i}$

$\sum_{i = 0}^k \sum_{j = 0}^l \binom{i + j}{i} = \binom{k + l + 2}{k + 1}$

$\sum_{i = 0}^k \binom{n}{i} \binom{m}{k - i} = \binom{n + m}{k}$

$\sum_{i = 0}^k \binom{n + i}{i} \binom{m - i}{k - i} = \binom{n + m + 1}{k}$

## 積の和典型
長さが $N$ で総和が $M$ の任意の整数列 $a$ について， $\prod_{i=1}^N a_i$ を求めその総和を求める．

$a_i = (1+1+\cdots +1)$ と考えると，各 $i$ について $a_i$ 個の1から1個選ぶ個数と一致する．

これは区別できない $M$ 個のボールを区別できる $N$ グループに分けた上で，それぞれのグループのボール1個を選んで(グループの中ではボールは区別可能)黒く塗る方法の個数に等しい．

$M$ 個のボールに $N−1$ 個の仕切りを追加して $N+N−1$ 個選び，選んだ要素を{黒,仕切り,黒,仕切り,...}とすると

$\binom{M + N - 1}{N + N - 1}$

総和が $M$ 以下の場合， $\binom{M+N-1}{N+N}$

https://ei1333.hateblo.jp/entry/2021/07/30/144201

## 二項係数のprefix sumの多点評価
$f(n,m) = \sum_{k=0}^m \binom{n}{k}$ と置くと，以下が成立する．

- $f(n,m + 1) = f(n,m) + \binom{n}{m + 1}$
- $f(n,m - 1) = f(n,m) - \binom{n}{m}$
- $f(n + 1,m) = 2 \times f(n,m) - \binom{n}{m}$
- $f(n - 1,m) = \left(f(n,m) + \binom{n - 1}{m} \right)/2$

二次元のMoに乗せることでクエリとして解ける．

https://yukicoder.me/problems/no/2206/editorial

## $\sum_{r = 1}^n \binom{n}{r}r^k$
$f(x) = (1+x)^n = \sum_{r = 0}^{n} \binom{n}{r}x^r$ であるので，微分してxを掛けると，

$nx(1+x)^{n - 1} = \sum_{r = 1}^n \binom{n}{r}rx^r$ これを $k$ 回繰り返し， $x = 1$ とすると目的の式となる．

$dp[a][b][c]$ を関数 $x^b(1+x)^c$ の微分を $k$ 回行い， $x = 1$ とした値とする．

$\sum_{r = 1}^n \binom{n}{r}r^k = dp[k][0][n]$ となる．

遷移は
$\frac{d}{dx}(x^b(1 + x)^c) = bx^b(1 + x)^c + cx^{b + 1}(1 + x)^{c - 1}$ より，

$dp[a][b][c] = b \times dp[a - 1][b][c] + c \times dp[a - 1][b + 1][c - 1]$

$b + c$ が $k$ で抑えられるため， $O(k^2)$

https://codeforces.com/blog/entry/57796

## 多項係数 -> 二項係数の積

$\frac{(A_1 + A_2 + \dots + A_N)!}{A_1!A_2! \dots A_N!} = \binom{A_1}{A_1}\binom{A_1 + A_2}{A_2} \dots \binom{A_1+A_2+\dots +A_N}{A_N}$
