## 説明
累積分布関数です。

https://ja.wikipedia.org/wiki/%E7%B4%AF%E7%A9%8D%E5%88%86%E5%B8%83%E9%96%A2%E6%95%B0

平均mean, 標準偏差std_devに従う正規分布において、x以下となる確率を求めます。

https://ja.wikipedia.org/wiki/%E6%AD%A3%E8%A6%8F%E5%88%86%E5%B8%83

平均mean, 標準偏差std_devに従う正規分布においてl以上r以下となるような確率は

normal_cdf(mean, std_dev, r) - normal_cdf(mean, std_dev, l) となります。

## 参考文献
https://qiita.com/thun-c/items/688442aad6a0410545cc#%E5%AE%9F%E8%A3%85%E8%AA%AC%E6%98%8E
