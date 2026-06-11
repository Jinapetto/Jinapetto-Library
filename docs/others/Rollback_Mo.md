## 説明
incrementalなMo's algorithmです
## コンストラクタ
Mo<T,add_l,add_r,out,snapshot,rollback,reset> (n,q)
- T 答えの型
- void add_l/r(int i) l/rを範囲に追加するときの処理
  
- T out(int l,int r) その時の答えを返す
  
- void snapshot() snapshotをとる(今までの履歴を消して、履歴を新しく取り始める)
  
- void rollback() snapshotをとったところまでrollbackする
  
- void reset() データ構造のリセット、履歴もリセットする

vector<T> run() 答えをvectorに詰めて返す
## 計算量
$O(Q\sqrt{N})$
## 参考文献
https://snuke.hatenablog.com/entry/2016/07/01/000000
https://ei1333.github.io/luzhiled/snippets/other/mo.html
## verify
https://www.acmicpc.net/source/85353567
## 備考
rollbackが二度連続で呼び出されることがない実装になってます(snapshotとrollbackが１対１で対応)
