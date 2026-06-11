## 説明
Mo's algorithm
## コンストラクタ
Mo<T,add_l,add_r,del_l,del_r,out> (int n,int q)
  T: 答えの型
  void add/del_l/r: l/rが追加/削除されたときの処理を行う
  T out(int l,int r): 呼び出された時点での答えを出力
void add_q(int l,int r): クエリを登録[l,r)
vector<T> run: add_qで追加された順番でvectorにつめて返す

## 計算量

## 参考文献
https://nyaannyaan.github.io/library/misc/mo.hpp.html
## verify
https://atcoder.jp/contests/abc174/submissions/58876057

https://atcoder.jp/contests/abc293/submissions/58876270

区間クエリじゃなくて二次元のやつ

https://atcoder.jp/contests/abc384/submissions/60814285
## 備考
