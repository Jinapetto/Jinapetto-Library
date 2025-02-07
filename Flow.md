## output_checkerの作成

### output_checkerの仕様
test_lib形式で受け取ります。
コマンドライン引数で`(int argc, char *argv[])`を受け取ります。

`argv[1]` が入力ファイル、 `argv[2]` がユーザープログラムの出力ファイル、 `argv[3]` が想定解の回答ファイルになります。

return 0で`AC`、それ以外で`WA`、output_checkerの異常終了で`IE`となります。

`registerTestlibCmd(argc, argv);` とすることでtest_libを利用してファイルを読み進めることができます。

スペースや改行が問題文で指定されたのとは異なる、最後にスペースが入っていても`AC`と判定したい場合は以下のコードを使えばよいです。

https://github.com/MikeMirzayanov/testlib/tree/master/checkers ここに色々あります。

```C++
#include <bits/stdc++.h>

#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    int n = 0;
    string j, p;

    while (!ans.seekEof() && !ouf.seekEof()) {
        n++;

        ans.readWordTo(j);
        ouf.readWordTo(p);

        if (j != p)
            quitf(_wa, "%d%s words differ - expected: '%s', found: '%s'", n, englishEnding(n).c_str(),
                  compress(j).c_str(), compress(p).c_str());
    }

    if (ans.seekEof() && ouf.seekEof()) {
        if (n == 1)
            quitf(_ok, "\"%s\"", compress(j).c_str());
        else
            quitf(_ok, "%d tokens", n);
    } else {
        if (ans.seekEof())
            quitf(_wa, "Participant output contains extra tokens");
        else
            quitf(_wa, "Unexpected EOF in the participants output");
    }
}

```

### TESTSETの設定
以下のように追加します。variant=testlib_judge_runnerとすることでtestlib方式で扱えます。
```Python
cxx_judge(src='output_checker.cpp', flags=my_cpp_flags, dependency = my_dependency, variant=testlib_judge_runner)
```

### 備考
`#include <bits/stdc++>` がないと、自分の環境ではtestが通っても、GitHub上のtestはコンパイルエラーで落ちました。

## scoreをつける
AtCoder 上でサンプルとそれ以外で区別したいので scoreをつけます。

TESTSETに以下のように追加します。
```Python
subtask_testset(name='Sample', score=0, input_patterns=['*sample*'])
subtask_testset(name='All', score=100, input_patterns=['*'])
```

`input_patterns` に正規表現で表現します。部分点も同じようにつけれます。 

部分点をつける場合は `SOLUTION` に 以下のように記述するとその解法がその部分点になるかを `rime test` で判定してくれます。

```Python
expected_score(100)
```
`rime test` をするときは、`-k` オプションをつけると正常に部分点が正しくつくかを判定してくれます。

## AtCoder へのアップロード

```sh
$ rime pack
```

を実行します。 pack が終わると `rime-out` の中に `atcoder` というファイルが作成されます。

`imojudge_upload.php` と同じディレクトリに `config-imojudge_upload.php` を作成して、以下のように記述します。

```PHP
<?php
@define('IMOJUDGE_CONTEST_ID', xxxx); // コンテストID
@define('IMOJUDGE_TASK_UPLOAD_PASSWORD', 'xxxx'); // アップロードパスワード
@define('IMOJUDGE_TASK_ID_LOWER_BOUND', xxxx); // inclusive
@define('IMOJUDGE_TASK_ID_UPPER_BOUND', xxxx); // inclusive
?>
```

情報はコンテストページの問題ページのアップローダ設定情報にあるのを入れます。

```sh
php imojudge_upload.php <task_id> <先ほど作成した atcoder のパス>
```

で AtCoder にアップロードできます。(PHP の実行環境が必要です。) `task_id` は `TASK_ID_LOWER_BOUND` をA問題として順番に振られています。

同じ task_id にもう一度アップロードすることでジャッジの上書きができます。

## 問題文のアップロード

```sh
python md2atcoder.py <マークダウンで書かれた問題文のパス>
```

をするとマークダウンを html にしてくれます。

それをコンテストページの問題を編集から貼り付けます。
