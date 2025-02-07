## output_checkerの作成

### output_checkerの仕様
test_lib形式で受け取ります。
コマンドライン引数で`(int argc, char *argv[])`を受け取ります。

`argv[1]` が入力ファイル、 `argv[2]` がユーザープログラムの出力ファイル、 `argv[3]` が想定解の回答ファイルになります。

return 0で`AC`、それ以外で`WA`、output_checkerの異常終了で`IE`となります。

`registerTestlibCmd(argc, argv);` とすることでtest_libを利用してファイルを読み進めることができます。

スペースや改行が問題文で指定されたのとは異なる、最後にスペースが入っていても`AC`と判定したい場合は以下のコードを使えばよいです。

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
subtask_testset(name='All', score=100, input_patterns=['*'])
subtask_testset(name='sample', score=0, input_patterns=['*sample*'])
```

input_patterns に正規表現で表現します。部分点も同じようにつけれます。

部分点をつける場合は SOLUTION に 以下のように記述するとその解法がその部分点になるかを rime test で判定してくれます。

```Python
expected_score(100)
```
rime test をするときは、-k オプションをつけると正常に部分点が正しくつくかを判定してくれます。

