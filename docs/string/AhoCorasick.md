## 説明
Aho-Corasick法です。複数のパターン文字列をトライ木に登録し、失敗リンク（failure link）を構築することで、テキスト中に各パターンが何個出現するかを効率的に求められます。

`build()` 後は `match[v]` に「ノード `v` に対応するパターン数（suffix link 経由の累積込み）」が入ります。
## コンストラクタ
`AhoCora(int char_sz, int margin)` 初期化

- `char_sz`: アルファベットのサイズ（例: 26）
- `margin`: 文字の基準（例: `'a'`）
## メソッド
`add(string& s)` パターン文字列 `s` をトライ木に追加

`build()` 失敗リンクを構築（全パターン追加後に1回呼ぶ）
## フィールド（build後）
`g[v][c]` : ノード `v` で文字 `c` を読んだときの遷移先

`match[v]` : ノード `v` で終わるパターン数（suffix link 経由の累積込み）
## 計算量
構築: $O(\sum|P_i| \times \text{char\_sz})$

テキストのスキャン: $O(|T|)$（遷移 `g[v][c]` を辿るだけ）
## 参考文献
https://ei1333.github.io/library/string/aho-corasick.hpp.html
## verify
https://atcoder.jp/contests/abc458/submissions/76110713
## 備考
問題: https://atcoder.jp/contests/abc458/tasks/abc458_f
