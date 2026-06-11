## 説明
ACLのDSUをちょっと変えただけ
## コンストラクタ
頂点 $$i$$ の重みを $$W_i$$ と呼ぶことにする

merge( $$u,v,d$$ ) $$W_v-W_u=d$$ になるようにする

diff( $$u,v$$ ) $$W_v-W_u$$を返す(今までのmergeが矛盾してたらもちろん壊れる)不定かどうかはsame(u,v)で確認してください

check() これまでのmergeが矛盾していないか(正常:true, 異常:false)
mergeした後rollbackできないので使いどころがほとんどない
## 計算量

## 参考文献
https://atcoder.github.io/ac-library/master/document_ja/dsu.html
## verify
https://atcoder.jp/contests/abc087/submissions/60199646
https://judge.yosupo.jp/submission/252410
## 備考
groups()はverifyしてない
