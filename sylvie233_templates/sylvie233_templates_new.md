# ACM算法(4+4+1)

> Author: Sylvie233
>
> DateL: 23/5/27

[TOC]

## 图论

### 搜索

#### 深度优先搜索



#### 广度优先搜索



#### 记忆化搜索



#### 双向宽搜



#### A*



#### IDA*



#### 模拟退火







### 拓扑排序





### 连通性问题

#### 强连通分量

##### Tarjan

![image-20230607143849254](sylvie233_templates_new.assets/image-20230607143849254.png)

![image-20230607150034189](sylvie233_templates_new.assets/image-20230607150034189.png)

![image-20230607150104323](sylvie233_templates_new.assets/image-20230607150104323.png)





##### Tarjan SCC缩点

![image-20230607152312473](sylvie233_templates_new.assets/image-20230607152312473.png)



**校园网络**

![image-20230607150908569](sylvie233_templates_new.assets/image-20230607150908569.png)

![image-20230607150950897](sylvie233_templates_new.assets/image-20230607150950897.png)

















##### 强连通分支





#### 双连通分量



#### 图的割边和割点

##### Tarjan割点

![image-20230607153257535](sylvie233_templates_new.assets/image-20230607153257535.png)

![image-20230607153854408](sylvie233_templates_new.assets/image-20230607153854408.png)

![image-20230607154224450](sylvie233_templates_new.assets/image-20230607154224450.png)



##### Tarjan割边

![image-20230607155745195](sylvie233_templates_new.assets/image-20230607155745195.png)

![image-20230607160914303](sylvie233_templates_new.assets/image-20230607160914303.png)

![image-20230607161338394](sylvie233_templates_new.assets/image-20230607161338394.png)

![image-20230607161858612](sylvie233_templates_new.assets/image-20230607161858612.png)













#### 2-SAT





### 最小生成树

#### 次小生成树



#### k小生成树



#### 最优比例生成树







### 最短路

#### 第k短路径



#### 差分约束







### 网络流

#### 最大流

##### EK算法

![image-20230608114530680](sylvie233_templates_new.assets/image-20230608114530680.png)

![image-20230608115128413](sylvie233_templates_new.assets/image-20230608115128413.png)

![image-20230608120304685](sylvie233_templates_new.assets/image-20230608120304685.png)











#### 最小割







### 二分图

#### 二分图判定

![image-20230607114728970](sylvie233_templates_new.assets/image-20230607114728970.png)

![image-20230607115112236](sylvie233_templates_new.assets/image-20230607115112236.png)









#### 匈牙利算法

![image-20230607120159619](sylvie233_templates_new.assets/image-20230607120159619.png)

![image-20230607120406353](sylvie233_templates_new.assets/image-20230607120406353.png)

![image-20230607120930745](sylvie233_templates_new.assets/image-20230607120930745.png)

![image-20230607121213957](sylvie233_templates_new.assets/image-20230607121213957.png)



#### KM算法

![image-20230607121944715](sylvie233_templates_new.assets/image-20230607121944715.png)

![image-20230607122642861](sylvie233_templates_new.assets/image-20230607122642861.png)

![image-20230607124455358](sylvie233_templates_new.assets/image-20230607124455358.png)





#### Dinic算法

二分图转为网络流模型







#### 最大独立集





















### 欧拉回路



### 哈密顿回路



### 最小生成森林





### 稳定婚姻





### 仙人掌





### 带花树







### 斯坦纳树







### 支配树





### 基环树

#### 基环外向树







### 对偶图



### 最大团



### 树分治







## 数据结构

### 分块

#### 区间更新、单点查询

```
/**
 * @brief 区间更新，单点查询
 *  数据范围：1~n
 */
int n, len, id[N], lazy[N], data[N];

void add(int l, int r, int v) {
    for (int i = l; i <= std::min(id[l] * len, r); i++) {
        data[i] += v;
    }
    if (id[l] != id[r]) {
        for (int i = (id[r] - 1) * len + 1; i <= r; i++) {
            data[i] += v;
        }
    }
    for (int i = id[l] + 1; i <= id[r] - 1; i++) {
        lazy[i] += v;
    }
}

void solve() {
    len = std::sqrt(n);
    for (int i = 1; i <= n; i++) {
        id[i] = (i - 1) / len + 1; 
    }
    // data[i] + lazy[id[i]]
}
```





#### 区间更新、区间查询小于x的元素的个数

```
/**
 * @brief 区间更新，查询区间内小于x的元素的个数
 *  数据范围：1~n, M为sqrt(N)
 * 
 */
int len, id[N], lazy[N];
std::vector<int> bkt[M];
int n, d[N];

void reset(int x) {
    bkt[x].clear();
    for (int i = (x - 1) * len + 1; i < std::min(x * len, n); i++) {
        bkt[x].push_back(d[i]);
    }
    std::sort(bkt[x].begin(), bkt[x].end());
}

void add(int l, int r, int v) {
    for (int i = l; i < std::min(id[l] * len, r); i++) {
        d[i] += v;
    }
    reset(id[l]);
    if (id[l] != id[r]) {
        for (int i = (id[r] - 1) * len + 1; i <= r; i++) {
            d[i] += v;
        }
        reset(id[r]);
    }
    for (int i = id[l] + 1; i <= id[r] - 1; i++) {
        lazy[i] += v;
    }
}

int query(int l, int r, int v) {
    int res = 0;
    for (int i = l; i <= std::min(id[l] * len, r); i++) {
        if (d[i] + lazy[id[l]] < v) {
            res++;
        }
    }
    if (id[l] != id[r]) {
        for (int i = (id[r] - 1) * len + 1; i <= r; i++) {
            if (d[i] + lazy[id[r]] < v) {
                res++;
            }
        }
    }
    for (int i = id[l] + 1; i <= id[r] - 1; i++) {
        int x = v - lazy[i];
        res += std::lower_bound(bkt[i].begin(), bkt[i].end(), x) - bkt[i].begin();
    }
    return res;
}

void solve() {
    len = std::sqrt(n);
    for (int i = 1; i <= n; i++) {
        id[i] = (i - 1) / len + 1;
        bkt[id[i]].push_back(d[i]);
    }
    for (int i = 1; i <= id[n]; i++) {
        std::sort(bkt[i].begin(), bkt[i].end());
    }
}
```





#### 区间更新、区间查询小于x的最大值

```
/**
 * @brief 区间更新，查询区间小于x的最大值
 *  数据范围：1~n, M为sqrt(N)
 * 
 */
int len, id[N], lazy[N];
std::set<int> st[M];
int n, d[N];

void add(int l, int r, int v) {
    for (int i = l; i < std::min(id[l] * len, r); i++) {
        st[id[l]].erase(d[i]);
        d[i] += v;
        st[id[l]].insert(d[i]);
    }
    if (id[l] != id[r]) {
        for (int i = (id[r] - 1) * len + 1; i <= r; i++) {
            st[id[r]].erase(d[i]);
            d[i] += v;
            st[id[r]].insert(d[i]);
        }
    }
    for (int i = id[l] + 1; i <= id[r] - 1; i++) {
        lazy[i] += v;
    }
}

int query(int l, int r, int v) {
    int res = -1;
    for (int i = l; i <= std::min(id[l] * len, r); i++) {
        if (d[i] + lazy[id[l]] < v) {
            res = std::max(res, d[i] + lazy[id[l]]);
        }
    }
    if (id[l] != id[r]) {
        for (int i = (id[r] - 1) * len + 1; i <= r; i++) {
            if (d[i] + lazy[id[r]] < v) {
                res = std::max(res, d[i] + lazy[id[r]]);
            }
        }
    }
    for (int i = id[l] + 1; i <= id[r] - 1; i++) {
        auto it = st[i].lower_bound(v - lazy[i]);
        if (it == st[i].begin()) {
            continue;
        }
        res = std::max(res, *(--it) + lazy[i]);
    }
    return res;
}

void solve() {
    len = std::sqrt(n);
    for (int i = 1; i <= n; i++) {
        id[i] = (i - 1) / len + 1;
        st[id[i]].insert(d[i]);
    }
}
```



#### 区间更新、区间求和

```

```









### 链式前向星

```

```

![image-20230607083618297](sylvie233_templates_new.assets/image-20230607083618297.png)









![image-20230607081244249](sylvie233_templates_new.assets/image-20230607081244249.png)













#### 邻接矩阵

![image-20230607081613480](sylvie233_templates_new.assets/image-20230607081613480.png)



#### 边集数组

![image-20230607082041173](sylvie233_templates_new.assets/image-20230607082041173.png)



#### 邻接表

![image-20230607082406326](sylvie233_templates_new.assets/image-20230607082406326.png)



#### 链式邻接表

![image-20230607082909806](sylvie233_templates_new.assets/image-20230607082909806.png)





### bitset

```
bitset:
	any():
	count():
	flip():
	none():
	reset():
	set():
	size():
	to_string():
	to_ulong():
	to_ullong():
```





### 栈

#### 单调栈



### 队列

#### 优先队列



#### 双端队列



#### 单调队列

##### 滑动窗口最值

![image-20230618100644229](sylvie233_templates_new.assets/image-20230618100644229.png)

![image-20230618101215177](sylvie233_templates_new.assets/image-20230618101215177.png)

![image-20230618101336768](sylvie233_templates_new.assets/image-20230618101336768.png)







​	



### 堆



### 分治

#### CDQ分治

```
/*
	luogu P3810 三维偏序个数

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 5;

struct node {
	int a, b, c, cnt, ans;
} s1[N], s2[N];

int n, k, cnt, m, c[N], ans[N];

// 树状数组
void add(int x, int y) {
    while (x <= k) {
        c[x] += y;
        x += x & (-x);
    }
}

int ask(int x) {
    int res =0;
    while (x > 0) {
        res += c[x];
        x -= x & (-x);
    }
    return res;
}

// CDQ分治
void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    // 左边对左边收益、右边对右边收益
    cdq(l, mid);
    cdq(mid + 1, r);

    // 第二维排序
    auto cmp2 = [](const node& a, const node& b) {
        if (a.b == b.b) {
            return a.c < b.c;
        }
        return a.b < b.b;
    };
    std::sort(s2 + l, s2 + mid + 1, cmp2);
    std::sort(s2 + mid + 1, s2 + r + 1, cmp2);

    // 右边对左边收益（左边不可能对右边收益：左边第一维小）
    int j = l;
    for (int i = mid + 1; i <= r; i++) {
        while (s2[i].b >= s2[j].b && j <= mid) {
            add(s2[j].c, s2[j].cnt);
            j++;
        }
        s2[i].ans += ask(s2[i].c);
    } 
    for (int i = l; i < j; i++) 
        add(s2[i].c, -s2[i].cnt); // 清空
}




int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) 
        std::cin >> s1[i].a >> s1[i].b >> s1[i].c;


    auto cmp1 = [](const node& a, const node& b) {
        if (a.a == b.a) {
            if (a.b == b.b) return a.c < b.c;
            return a.b < b.b;
        }
        return a.a < b.a;
    };
    // 第一维排序
    std::sort(s1 + 1, s1 + 1 +n, cmp1);

    // 去除处理
    for (int i = 1; i <= n; i++) {
        cnt++;
        if (s1[i].a != s1[i + 1].a || s1[i].b != s1[i + 1].b || s1[i].c != s1[i + 1].c) {
            m++;
            s2[m] = s1[i];
            s2[m].cnt = cnt;
            cnt = 0;
        }
    }

    // CDQ分治
    cdq(1, m);

    for (int i = 1; i <= m; i++) {
        ans[s2[i].ans + s2[i].cnt - 1] += s2[i].cnt;
    }

    for (int i = 0; i < n; i++)
        std::cout << ans[i] << '\n';

	return 0;
}
```



![image-20230607132647044](sylvie233_templates_new.assets/image-20230607132647044.png)

![image-20230607132518116](sylvie233_templates_new.assets/image-20230607132518116.png)











### 树

#### 基环树



#### 二叉树





#### 二叉搜索树



#### 平衡树





#### 左偏树



### 线段树

![image-20230607124949567](sylvie233_templates_new.assets/image-20230607124949567.png)

![image-20230607125600904](sylvie233_templates_new.assets/image-20230607125600904.png)

![image-20230607125703516](sylvie233_templates_new.assets/image-20230607125703516.png)

![image-20230607125811073](sylvie233_templates_new.assets/image-20230607125811073.png)



![image-20230607130616119](sylvie233_templates_new.assets/image-20230607130616119.png)

![image-20230607132045729](sylvie233_templates_new.assets/image-20230607132045729.png)



















#### 离散线段树

<img src="sylvie233_templates_new.assets/image-20230528104234754.png" alt="image-20230528104234754" style="zoom:67%;" />



#### 扫描线

```
#include <iostream>
#include <algorithm>

const int N = 1e7 + 5;

using ll = long long;

struct Line{
    int x, y1, y2;
    int flg; // 左1，右-1
    bool operator<(Line& b) {
        return x < b.x;
    }
} L[N * 2];

struct Tree {
    int l, r, len; // 区间有效高度
    int cnt;
} tr[N * 8];

int n, Y[N * 2];

void build (int u, int l, int r) {
     tr[u].l = Y[l];
     tr[u].r = Y[r];
     if (r == l + 1) return; // 叶子宽度为2
     int mid = (l + r) >> 1;
     build(u << 1, l, mid);
     build((u << 1) | 1, mid, r);
}

void pushup(int u) {
    if (tr[u].cnt) { // 第u号区间被完全覆盖
        tr[u].len = tr[u].r - tr[u].l;
    } else {    // 第u号区间未完全覆盖
        tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
    }
}

void change(int u, int a, int b, int c) {
    if (a >= tr[u].r || b <= tr[u].l) return;
    if (a <= tr[u].l && tr[u].r <= b) {
        tr[u].cnt += c;
        pushup(u);
        return;
    }
    change(u << 1, a, b, c);
    change(u << 1 | 1, a, b, c);
    pushup(u);
}

int main() {
    std::cin >> n;
    int x1, x2, y1, y2;
    for (int i = 1; i <= n; i++) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        L[i] = { x1, y1, y2, 1};
        L[n + i] = { x2, y1, y2, -1};
        Y[i] = y1;
        Y[n + i] = y2;
    }
    n *= 2;
    std::sort(L + 1, L + n + 1); // 按照x从小到大排序
    std::sort(Y + 1, Y + 1 + n);
    build(1, 1, n); // Y中n的个数还可优化
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        change(1, L[i].y1, L[i].y2, L[i].flg);
        ans += 1ll * (L[i + 1].x - L[i].x) * tr[1].len;
    }
    std::cout << ans << '\n';
    return 0;
}
```



<img src="sylvie233_templates_new.assets/image-20230528103928547.png" alt="image-20230528103928547" style="zoom:67%;" />

<img src="sylvie233_templates_new.assets/image-20230528104434479.png" alt="image-20230528104434479" style="zoom:67%;" />

<img src="sylvie233_templates_new.assets/image-20230528104838064.png" alt="image-20230528104838064" style="zoom:67%;" />

<img src="sylvie233_templates_new.assets/image-20230528110134481.png" alt="image-20230528110134481" style="zoom:67%;" />

区间有效高度思想











#### zkw线段树



#### 线段树合并







### 李超树



### 主席树





### ST表

#### 区间最值

```
/**
 * @brief ST表（区间最大、小值查询，不能更新）
 * 区间范围：1~n，2^21=2e6
 */
int n, d[N], mx[N][22], mn[N][22];

int get_max(int l, int r) {
    int k = std::log2(r - l + 1);
    return std::max(mx[l][k], mx[r - (1 << k) + 1][k]);
}

int get_min(int l, int r) {
    int k = std::log2(r - l + 1);
    return std::min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

void init() {
    for (int i = 1; i <= n; i++) {
        mx[i][0] = mn[i][0] = d[i]; 
    }
    // 长度递推
    for (int j = 1; j <= 21; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            mx[i][j] = std::max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
            mn[i][j] = std::min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
        }
    }
}
```







### 树状数组

![image-20230607233338294](sylvie233_templates_new.assets/image-20230607233338294.png)



#### 单点更新、区间求和

```
/**
 * @brief 树状数组（单点更新，区间求和）
 *  数据范围：1~n 
 * 
 */
int n, arr[N], bit[N];

int sum(int i) {
    int res = 0;
    while (i > 0) {
        res += bit[i];
        i -= i & -i;
    }
    return res;
}

void add(int i, int v) {
    while (i <= n) {
        bit[i] += v;
        i += i & -i;
    }
}

void init() {
    for (int i = 1; i <= n; i++) {
        add(i, arr[i]);
    }
}
```



#### 区间更新、单点求和

```
/**
 * @brief 树状数组（区间更新，单点查询）
 *	数组拆分：区间[1~i]求和为a[i]
 *  数据范围：1~n
 * 
 */
int n, arr[N], bit[N];

int sum(int i) {
    int res = 0;
    while (i > 0) {
        res += bit[i];
        i -= i & -i;
    }
}

void add(int i, int v) {
    while (i <= n) {
        bit[i] += v;
        i += i & -i;
    }
}

void update(int l, int r, int v) {
    add(l, v);
    add(r + 1, -v);
}

void init() {
    for (int i = 1; i <= n; i++) {
        add(i, arr[i] - arr[i - 1]);
    }
}
```



#### 区间更新、区间查询

```
/**
 * @brief 树状数组（区间更新，区间查询）
 *	拆分思想
 *  数据范围：1~n，bit[i][0]为公式前面，bit[i][1]为公式后面
 *     arr[1~3]：
 *        (3+1)*(c[1]+c[2]+c[3])   -   (1*c[1]+2*c[2]+3*c[3])
 *		c[1] 
 *		c[1] + c[2]
 *		c[1] + c[2] + c[3]
 *
 * 
 */
int n, arr[N], bit[N][2];

int sum(int i, int f) {
    int res = 0;
    while (i > 0) {
        res += bit[i][f];
        i -= i & -i;
    }
}

void add(int i, int v, int f) {
    while (i <= n) {
        bit[i][f] += v;
        i += i & -i;
    }
}

void update(int l, int r, int v) {
    add(l, v, 0);
    add(r + 1, -v, 0);
    add(l, l * v, 1);
    add(r + 1, (r + 1) * -v, 1);
}

int query(int i) {
    return (i + 1) * sum(i, 0) - sum(i, 1);
}

void init() {
    for (int i = 1; i <= n; i++) {
        add(i, arr[i] - arr[i - 1], 0);
        add(i, i * (arr[i] - arr[i - 1]), 1);
    }
}
```



#### 单点更新、区间最值

```
/**
 * @brief 树状数组（单点更新，区间最值）
 *  数据范围：1~n，这里算的是max，最小值只需把max换成min即可
 *     7(111)   6(110)      4(100)
 *              5(101)   2(010) 3(011)
 *                       1(001)
 */
int n, arr[N], bit[N];

void update(int i) {
    while (i <= n) {
        bit[i] = arr[i];
        int x = i & -i;
        for (int j = 1; j < x; j++) {
            bit[i] = std::max(bit[i], bit[i - j]);
        }
        i += x;
    }
}

int query(int l, int r) {
    int res = 0;
    while (r >= l) {
        res = std::max(res, arr[r]);
        r--;
        while (r - (r & -r) >= l) {
            res = std::max(res, bit[r]);
            r -= r & -r;
        }
    }
    return res;
}

void init() {
    for (int i = 1; i <= n; i++) {
        update(i);
    }
    // 更新arr[1]
    arr[1] = 100;
    update(1);
}
```









### 树链剖分

#### 最近公共祖先

![image-20230608192608509](sylvie233_templates_new.assets/image-20230608192608509.png)

![image-20230608193342976](sylvie233_templates_new.assets/image-20230608193342976.png)

![image-20230608193359153](sylvie233_templates_new.assets/image-20230608193359153.png)





#### 树上修改、查询

![image-20230608193806268](sylvie233_templates_new.assets/image-20230608193806268.png)

![image-20230608194247484](sylvie233_templates_new.assets/image-20230608194247484.png)

![image-20230608194634914](sylvie233_templates_new.assets/image-20230608194634914.png)

![image-20230608194816505](sylvie233_templates_new.assets/image-20230608194816505.png)

![image-20230608194951399](sylvie233_templates_new.assets/image-20230608194951399.png)

![image-20230608195019393](sylvie233_templates_new.assets/image-20230608195019393.png)













### 字典树

#### 可持续化字典树





### 并查集

![image-20230530151329901](sylvie233_templates_new.assets/image-20230530151329901.png)

![image-20230530151748402](sylvie233_templates_new.assets/image-20230530151748402.png)

![image-20230530152034569](sylvie233_templates_new.assets/image-20230530152034569.png)











#### 带权并查集



#### 可持续化并查集





### Splay

#### Treap

#### FHQ Treap



### LCT



### 替罪羊树





### 莫队

#### 带修莫队





### 树套树





### 舞蹈链





### 笛卡尔树





### 猫树





### KD树

























## 数论

### 快速幂





### 贝祖定理

![image-20230611173011876](sylvie233_templates_new.assets/image-20230611173011876.png)





裴蜀定理

![image-20230609165349689](sylvie233_templates_new.assets/image-20230609165349689.png)

![image-20230609165503215](sylvie233_templates_new.assets/image-20230609165503215.png)

![image-20230609165517578](sylvie233_templates_new.assets/image-20230609165517578.png)











### 欧几里得

```
int gcd(int a, int b) {
	if (0 == b) return a;
	return gcd(b, a % b);
}
```

<img src="sylvie233_templates_new.assets/image-20230528171240527.png" alt="image-20230528171240527" style="zoom:67%;" />![image-20230528171828415](sylvie233_templates_new.assets/image-20230528171828415.png)

<img src="sylvie233_templates_new.assets/image-20230528171240527.png" alt="image-20230528171240527" style="zoom:67%;" />![image-20230528171828415](sylvie233_templates_new.assets/image-20230528171828415.png)

<img src="sylvie233_templates_new.assets/image-20230528172207939.png" alt="image-20230528172207939" style="zoom:67%;" />











#### 类欧几里得



#### 扩展欧几里得

![image-20230609170049208](sylvie233_templates_new.assets/image-20230609170049208.png)

![image-20230609170414516](sylvie233_templates_new.assets/image-20230609170414516.png)

![image-20230609170458792](sylvie233_templates_new.assets/image-20230609170458792.png)







### 母函数



### 泰勒展开





### 康托展开



### 同余

#### 逆元

扩展欧几里得求乘法逆元

![image-20230609170744849](sylvie233_templates_new.assets/image-20230609170744849.png)

![image-20230609170912380](sylvie233_templates_new.assets/image-20230609170912380.png)

![image-20230609171509564](sylvie233_templates_new.assets/image-20230609171509564.png)







#### 指数同余方程



#### 高次同余方程





### 二次剩余



### 威尔逊定理

![image-20230609164255420](sylvie233_templates_new.assets/image-20230609164255420.png)

![image-20230609164735490](sylvie233_templates_new.assets/image-20230609164735490.png)

![image-20230609164746479](sylvie233_templates_new.assets/image-20230609164746479.png)



### 欧拉定理

![image-20230609162940716](sylvie233_templates_new.assets/image-20230609162940716.png)









#### 扩展欧拉定理

![image-20230609163612765](sylvie233_templates_new.assets/image-20230609163612765.png)

![image-20230609163729753](sylvie233_templates_new.assets/image-20230609163729753.png)





### 中国剩余定理

![image-20230611171254698](sylvie233_templates_new.assets/image-20230611171254698.png)

![image-20230611171543102](sylvie233_templates_new.assets/image-20230611171543102.png)

![image-20230611171811917](sylvie233_templates_new.assets/image-20230611171811917.png)



#### 扩展中国剩余定理

![image-20230611172210733](sylvie233_templates_new.assets/image-20230611172210733.png)

![image-20230611172548586](sylvie233_templates_new.assets/image-20230611172548586.png)

![image-20230611173047138](sylvie233_templates_new.assets/image-20230611173047138.png)





### 素性测试

#### 试除法

![image-20230607222643717](sylvie233_templates_new.assets/image-20230607222643717.png)



#### 唯一分解定理

![image-20230607223156105](sylvie233_templates_new.assets/image-20230607223156105.png)



#### 约数个数筛法

![image-20230607231633728](sylvie233_templates_new.assets/image-20230607231633728.png)

![image-20230607231403316](sylvie233_templates_new.assets/image-20230607231403316.png)







#### 约数和筛法

![image-20230607232305043](sylvie233_templates_new.assets/image-20230607232305043.png)

![image-20230607232919417](sylvie233_templates_new.assets/image-20230607232919417.png)







### 素数筛

#### 埃氏筛

![image-20230607223712536](sylvie233_templates_new.assets/image-20230607223712536.png)



#### 线性欧拉筛

保证合数只被最小质因数去除

![image-20230607224747542](sylvie233_templates_new.assets/image-20230607224747542.png)





#### 杜教筛



#### Min25筛



#### 洲阁筛



### Miller-Rabin素数测试



### Pollard-Rho大数分解



### 素数密度定理







### BSGS

![image-20230615113937841](sylvie233_templates_new.assets/image-20230615113937841.png)

![image-20230615114024223](sylvie233_templates_new.assets/image-20230615114024223.png)

![image-20230615114306571](sylvie233_templates_new.assets/image-20230615114306571.png)









#### EXBSGS

![image-20230615114813075](sylvie233_templates_new.assets/image-20230615114813075.png)

![image-20230615115052544](sylvie233_templates_new.assets/image-20230615115052544.png)

![image-20230615115621342](sylvie233_templates_new.assets/image-20230615115621342.png)



### 原根





### 费马小定理

![image-20230609162024423](sylvie233_templates_new.assets/image-20230609162024423.png)

![image-20230609162215642](sylvie233_templates_new.assets/image-20230609162215642.png)

![image-20230609162406116](sylvie233_templates_new.assets/image-20230609162406116.png)





### 卢卡斯定理





### 积性函数

#### 积性函数前缀和



### 欧拉函数

![image-20230607225440159](sylvie233_templates_new.assets/image-20230607225440159.png)

![image-20230607225318348](sylvie233_templates_new.assets/image-20230607225318348.png)



#### 线性筛

![image-20230607225920012](sylvie233_templates_new.assets/image-20230607225920012.png)

![image-20230607230342496](sylvie233_templates_new.assets/image-20230607230342496.png)









### 莫比乌斯函数

#### 线性筛

![image-20230609160800177](sylvie233_templates_new.assets/image-20230609160800177.png)

![image-20230609161143280](sylvie233_templates_new.assets/image-20230609161143280.png)









#### 莫比乌斯反演



### 迪利克雷卷积

![image-20230619225337673](sylvie233_templates_new.assets/image-20230619225337673.png)

![image-20230619225640984](sylvie233_templates_new.assets/image-20230619225640984.png)

![image-20230619225821901](sylvie233_templates_new.assets/image-20230619225821901.png)

![image-20230619230013205](sylvie233_templates_new.assets/image-20230619230013205.png)

![image-20230619230219004](sylvie233_templates_new.assets/image-20230619230219004.png)

![image-20230619230730634](sylvie233_templates_new.assets/image-20230619230730634.png)















### 整除分块

![image-20230619220117081](sylvie233_templates_new.assets/image-20230619220117081.png)

![](sylvie233_templates_new.assets/image-20230619220408855.png)

![image-20230619220507000](sylvie233_templates_new.assets/image-20230619220507000.png)





#### 合式变化





### FFT

#### NTT



#### FWT



#### 生成函数





### 线性基



### 高斯消元

#### 线性方程组

![image-20230617213307106](sylvie233_templates_new.assets/image-20230617213307106.png)

![image-20230617213508950](sylvie233_templates_new.assets/image-20230617213508950.png)

![image-20230617213933671](sylvie233_templates_new.assets/image-20230617213933671.png)

![image-20230617214246241](sylvie233_templates_new.assets/image-20230617214246241.png)

![image-20230617214538460](sylvie233_templates_new.assets/image-20230617214538460.png)





#### 矩阵求逆

![image-20230617214832313](sylvie233_templates_new.assets/image-20230617214832313.png)

![image-20230617215602999](sylvie233_templates_new.assets/image-20230617215602999.png)

![image-20230617215743388](sylvie233_templates_new.assets/image-20230617215743388.png)

















## 字符串

### 字典树

![image-20230607095435517](sylvie233_templates_new.assets/image-20230607095435517.png)

![image-20230607095448448](sylvie233_templates_new.assets/image-20230607095448448.png)

![image-20230607100101404](sylvie233_templates_new.assets/image-20230607100101404.png)

![image-20230607100156630](sylvie233_templates_new.assets/image-20230607100156630.png)





#### 01字典树

![image-20230607100420496](sylvie233_templates_new.assets/image-20230607100420496.png)

![image-20230607100849676](sylvie233_templates_new.assets/image-20230607100849676.png)

![image-20230607102258937](sylvie233_templates_new.assets/image-20230607102258937.png)







### KMP

![image-20230607091125302](sylvie233_templates_new.assets/image-20230607091125302.png)

相同前后缀的最大长度

![image-20230607091926899](sylvie233_templates_new.assets/image-20230607091926899.png)



![image-20230607091954897](sylvie233_templates_new.assets/image-20230607091954897.png)









#### 扩展KMP

![image-20230607092124413](sylvie233_templates_new.assets/image-20230607092124413.png)

![image-20230607093136872](sylvie233_templates_new.assets/image-20230607093136872.png)

![image-20230607093501667](sylvie233_templates_new.assets/image-20230607093501667.png)

![image-20230607094021225](sylvie233_templates_new.assets/image-20230607094021225.png)





### 哈希

![image-20230607090021678](sylvie233_templates_new.assets/image-20230607090021678.png)

![image-20230607090211276](sylvie233_templates_new.assets/image-20230607090211276.png)





#### 最小表示法

![image-20230607085049060](sylvie233_templates_new.assets/image-20230607085049060.png)

![image-20230607085806300](sylvie233_templates_new.assets/image-20230607085806300.png)









### 后缀自动机

![image-20230608100654510](sylvie233_templates_new.assets/image-20230608100654510.png)

![image-20230608102031974](sylvie233_templates_new.assets/image-20230608102031974.png)

![image-20230608104115081](sylvie233_templates_new.assets/image-20230608104115081.png)

![image-20230608104756737](sylvie233_templates_new.assets/image-20230608104756737.png)

![image-20230608105203236](sylvie233_templates_new.assets/image-20230608105203236.png)

![image-20230608105317292](sylvie233_templates_new.assets/image-20230608105317292.png)

![image-20230608105331638](sylvie233_templates_new.assets/image-20230608105331638.png)







#### 广义后缀自动机





### 马拉车

![image-20230607094228391](sylvie233_templates_new.assets/image-20230607094228391.png)

![image-20230607094703134](sylvie233_templates_new.assets/image-20230607094703134.png)

![image-20230607094909292](sylvie233_templates_new.assets/image-20230607094909292.png)

![image-20230607095217009](sylvie233_templates_new.assets/image-20230607095217009.png)



![image-20230607095315986](sylvie233_templates_new.assets/image-20230607095315986.png)





### AC自动机

基于字典树、构造类似KMP

![image-20230608092351541](sylvie233_templates_new.assets/image-20230608092351541.png)

![image-20230608093828812](sylvie233_templates_new.assets/image-20230608093828812.png)

沿着回跳边寻找所有匹配的后缀字符串

![image-20230608094630538](sylvie233_templates_new.assets/image-20230608094630538.png)

![image-20230608094821082](sylvie233_templates_new.assets/image-20230608094821082.png)

![image-20230608094900420](sylvie233_templates_new.assets/image-20230608094900420.png)







### 回文自动机





### 后缀数组

相邻后缀的最长公共前缀长度

![image-20230608105837039](sylvie233_templates_new.assets/image-20230608105837039.png)

![image-20230608112236411](sylvie233_templates_new.assets/image-20230608112236411.png)

<img src="sylvie233_templates_new.assets/image-20230608112433896.png" alt="image-20230608112433896" style="zoom:67%;" />

![image-20230608113524388](sylvie233_templates_new.assets/image-20230608113524388.png)

![image-20230608113826972](sylvie233_templates_new.assets/image-20230608113826972.png)

![image-20230608113847091](sylvie233_templates_new.assets/image-20230608113847091.png)













### Lyndon分解





### BM算法









## 动态规划

### 一般DP

#### LCS

##### 最长公共子序列

<img src="sylvie233_templates_new.assets/image-20230530100642010.png" alt="image-20230530100642010" style="zoom:67%;" />

 <img src="sylvie233_templates_new.assets/image-20230530101014461.png" alt="image-20230530101014461" style="zoom:67%;" />

<img src="sylvie233_templates_new.assets/image-20230530101813589.png" alt="image-20230530101813589" style="zoom:67%;" />

<img src="sylvie233_templates_new.assets/image-20230530102006031.png" alt="image-20230530102006031" style="zoom:67%;" />



##### 最长公共子串

<img src="sylvie233_templates_new.assets/image-20230530102624685.png" alt="image-20230530102624685" style="zoom:67%;" />

<img src="sylvie233_templates_new.assets/image-20230530102932655.png" alt="image-20230530102932655" style="zoom:67%;" />





#### 编辑距离

<img src="sylvie233_templates_new.assets/image-20230530141730241.png" alt="image-20230530141730241" style="zoom:67%;" />

<img src="sylvie233_templates_new.assets/image-20230530142528168.png" alt="image-20230530142528168" style="zoom:67%;" />  

<img src="sylvie233_templates_new.assets/image-20230530143039749.png" alt="image-20230530143039749" style="zoom:67%;" />

滚动数组优化

<img src="sylvie233_templates_new.assets/image-20230530143539026.png" alt="image-20230530143539026" style="zoom:67%;" />









### 背包问题

#### 01背包

<img src="sylvie233_templates_new.assets/image-20230530143924910.png" alt="image-20230530143924910" style="zoom:67%;" /><img src="sylvie233_templates_new.assets/image-20230530144208520.png" alt="image-20230530144208520" />![image-20230530145309953](sylvie233_templates_new.assets/image-20230530145309953.png)

<img src="sylvie233_templates_new.assets/image-20230530145507481.png" alt="image-20230530145507481" style="zoom:67%;" />



#### 完全背包

![image-20230530145827571](sylvie233_templates_new.assets/image-20230530145827571.png)

<img src="sylvie233_templates_new.assets/image-20230530150228774.png" alt="image-20230530150228774" style="zoom:67%;" />

![image-20230530150748226](sylvie233_templates_new.assets/image-20230530150748226.png)



#### 多重背包

![image-20230618095327658](sylvie233_templates_new.assets/image-20230618095327658.png)

![image-20230618095528085](sylvie233_templates_new.assets/image-20230618095528085.png)

##### 二进制优化

![image-20230618100150170](sylvie233_templates_new.assets/image-20230618100150170.png)









### 区间DP

#### 石子合并

<img src="sylvie233_templates_new.assets/image-20230607105420620.png" alt="image-20230607105420620" style="zoom:67%;" />

![image-20230607105756233](sylvie233_templates_new.assets/image-20230607105756233.png)

![image-20230607110033261](sylvie233_templates_new.assets/image-20230607110033261.png)

<img src="sylvie233_templates_new.assets/image-20230607110324906.png" alt="image-20230607110324906" style="zoom:67%;" />













### 状态压缩DP

#### 玉米田

![image-20230607103854647](sylvie233_templates_new.assets/image-20230607103854647.png)

![image-20230607104303010](sylvie233_templates_new.assets/image-20230607104303010.png)

![image-20230607105105000](sylvie233_templates_new.assets/image-20230607105105000.png)





### 数位DP

#### Windy数

![image-20230607112512152](sylvie233_templates_new.assets/image-20230607112512152.png)

![image-20230607112912841](sylvie233_templates_new.assets/image-20230607112912841.png)

![image-20230607113423672](sylvie233_templates_new.assets/image-20230607113423672.png)

![image-20230607114208427](sylvie233_templates_new.assets/image-20230607114208427.png)



### 树形DP

#### 没有上司的舞会

![image-20230607102512726](sylvie233_templates_new.assets/image-20230607102512726.png)

![image-20230607102837998](sylvie233_templates_new.assets/image-20230607102837998.png)

![image-20230607103426063](sylvie233_templates_new.assets/image-20230607103426063.png)

![image-20230607103642083](sylvie233_templates_new.assets/image-20230607103642083.png)













### 概率DP





### 插头DP



### SOSDP





### DP优化













## 组合数学

### 排列

#### 多重集和排列



### 组合

#### 多重集的组合



#### 组合数公式

<img src="sylvie233_templates_new.assets/image-20230528095052539.png" alt="image-20230528095052539" style="zoom:67%;" />



![image-20230618085627953](sylvie233_templates_new.assets/image-20230618085627953.png)

![image-20230618085708535](sylvie233_templates_new.assets/image-20230618085708535.png)



#### 快速幂求组合数

![image-20230618090250326](sylvie233_templates_new.assets/image-20230618090250326.png)

![image-20230618090428268](sylvie233_templates_new.assets/image-20230618090428268.png)



#### 卢卡斯定理

![image-20230618090759408](sylvie233_templates_new.assets/image-20230618090759408.png)

![image-20230618091129549](sylvie233_templates_new.assets/image-20230618091129549.png)



#### 线性筛求组合数

![image-20230618091658877](sylvie233_templates_new.assets/image-20230618091658877.png)

![image-20230618092156221](sylvie233_templates_new.assets/image-20230618092156221.png)



#### 隔板法

![image-20230618092425318](sylvie233_templates_new.assets/image-20230618092425318.png)

![image-20230618093157427](sylvie233_templates_new.assets/image-20230618093157427.png)









### 二项式定理





### 鸽巢原理







### 容斥原理

#### 集合的并

![image-20230618093417048](sylvie233_templates_new.assets/image-20230618093417048.png)

![image-20230618094300829](sylvie233_templates_new.assets/image-20230618094300829.png)





#### 集合的交

![image-20230618094507951](sylvie233_templates_new.assets/image-20230618094507951.png)

![image-20230618094937032](sylvie233_templates_new.assets/image-20230618094937032.png)

![image-20230618095136369](sylvie233_templates_new.assets/image-20230618095136369.png)









### 错排问题





### 特殊计数

#### 斐波那契数列





#### 卡特兰数

![image-20230619215029711](sylvie233_templates_new.assets/image-20230619215029711.png)

![image-20230619215436879](sylvie233_templates_new.assets/image-20230619215436879.png)

![image-20230619215521125](sylvie233_templates_new.assets/image-20230619215521125.png)







#### 第一类斯特林数



#### 第二类斯特林树





### 生成函数

![image-20230619224221114](sylvie233_templates_new.assets/image-20230619224221114.png)

![image-20230619224831851](sylvie233_templates_new.assets/image-20230619224831851.png)

![image-20230619225053142](sylvie233_templates_new.assets/image-20230619225053142.png)

![image-20230619225108040](sylvie233_templates_new.assets/image-20230619225108040.png)









#### 普通生成函数

![image-20230619220852682](sylvie233_templates_new.assets/image-20230619220852682.png)

![image-20230619221224789](sylvie233_templates_new.assets/image-20230619221224789.png)

![image-20230619221737448](sylvie233_templates_new.assets/image-20230619221737448.png)

![image-20230619222419548](sylvie233_templates_new.assets/image-20230619222419548.png)

![image-20230619222812578](sylvie233_templates_new.assets/image-20230619222812578.png)









#### 指数生成函数

![image-20230619223202174](sylvie233_templates_new.assets/image-20230619223202174.png)

![image-20230619223359890](sylvie233_templates_new.assets/image-20230619223359890.png)

![image-20230619223605147](sylvie233_templates_new.assets/image-20230619223605147.png)

![image-20230619223840404](sylvie233_templates_new.assets/image-20230619223840404.png)



















### 线性递推方程

#### 非线性递推方程





### Burnside定理





### Polya计数













## 计算几何

### 最远曼哈顿距离



### 最小包围圆

#### 最小包围球



### 最远点对

#### 旋转卡壳



#### 最近点对



#### 最近圆对



### 费马点



### 圆交点

#### 圆的面积交



### 平面面积最大三角





### Pick定理





### 多边形面积

#### 重心





### 多边形判核





### 模拟退火







### 定长圆覆盖最多的点



### 不等大的圆的圆弧表示





### 矩形面积并

#### 矩形的周长并







### 圆的反演变换







## 博弈论

### 巴什博弈



### 威佐夫博弈





### Nim博弈





### SG函数



### 斐波那契博弈



### 其它博弈











## 其它

### 排序

#### 冒泡排序



#### 选择排序



#### 快速排序



#### 堆排序



#### 桶排序





#### 归并排序



#### 插入排序



### 贪心



### 尺取



### 前缀和



### 滚动数组



### 差分



### 二分

![image-20230609172142744](sylvie233_templates_new.assets/image-20230609172142744.png)



开区间模板

![xxx](sylvie233_templates_new.assets/image-20230609172549964.png)

![image-20230609172915592](sylvie233_templates_new.assets/image-20230609172915592.png)

![image-20230609173100532](sylvie233_templates_new.assets/image-20230609173100532.png)

![image-20230609173557620](sylvie233_templates_new.assets/image-20230609173557620.png)









#### 三分



### 扫描线



### 高精度





### 倍增



### 构造



### 交互



### 快读



### 扩栈



### STL

![image-20230530152142597](sylvie233_templates_new.assets/image-20230530152142597.png)







