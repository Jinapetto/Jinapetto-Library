## 説明
平面幾何ライブラリ。うしさんのところから持ってきただけ。うしさんありがとう...

## 型・定数
- `Real` = `double`, `Point` = `complex<Real>`
- `EPS` = 1e-8, `PI` = acos(-1)
- `Line`, `Segment`, `Circle`, `Polygon`(= `vector<Point>`)

## 関数一覧

### 基本演算
- `eq(a, b)` : 誤差を考慮した等価判定
- `rotate(theta, p)` : 点 p を原点中心に反時計回りに theta 回転
- `cross(a, b)` / `dot(a, b)` : 外積 / 内積
- `ccw(a, b, c)` : 線分 ab に対する c の位置（+1反時計, -1時計, +2後方, -2前方, 0線分上）

### 直線・線分
- `parallel(a, b)` / `orthogonal(a, b)` : 平行 / 垂直判定
- `projection(l, p)` : 直線/線分 l への p の射影点
- `reflection(l, p)` : 直線 l を軸とした p の対称点

### 交差判定 `intersect(x, y)`
直線/線分/円/点の組み合わせに対応。円と線分は交差数(0/1/2)を返す。円と円は状態(0〜4)を返す。

### 距離 `distance(x, y)`
点/直線/線分/円の組み合わせに対応。

### 交点 `crosspoint(x, y)`
直線同士、線分同士、円と直線/線分、円と円に対応。

### 多角形
- `is_convex(p)` : 凸性判定
- `convex_hull(p)` : 凸包（Monotone Chain）
- `contains(Q, p)` : 点の包含判定（`IN`=2, `ON`=1, `OUT`=0）
- `convex_cut(U, l)` : 凸多角形を直線 l で切断し左側を返す
- `area(p)` : 多角形の面積
- `area(p, c)` : 多角形と円の共通部分の面積
- `convex_diameter(p)` : 凸多角形の直径（キャリパー法）

### その他
- `tangent(c, p)` : 点 p から円 c への接線の接点
- `tangent(c1, c2)` : 2円の共通接線
- `merge_segments(segs)` : 線分の重複除去
- `segment_arrangement(segs, ps)` : 線分アレンジメント（交点を頂点とした隣接リスト）
- `closest_pair(ps)` : 最近点対（分割統治 O(N log N)）

## 計算量
各関数 $O(1)$（closest_pair は $O(N \log N)$、convex_hull は $O(N \log N)$）

## 参考文献
https://ei1333.github.io/luzhiled/snippets/geometry/template.html

## verify

## 備考
`contains` の `OUT`/`ON`/`IN` は enum で定義。インクルード前に同名の定義がないか注意。
