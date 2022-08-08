#   ACM模板

>Author：Sylvie233
>
>Date：2022/07/13



[TOC]

<img src="./ACM.png" alt="ACM技能树" style="zoom: 33%;" />



## 基础工具

### 快速相乘

```c++

/**
 * @brief 快速相乘
 * 
 */

ll qmul(ll a, ll b) {
    ll ans = 0;
    while (b) {
        if (b & 1) {
            ans += a;
        }
        a += a;
        b >>= 1;
    }
    return ans;
}

ll qmul(ll a, ll b, ll mod) {
    ll ans = 0;
    while (b) {
        if (b & 1) {
            ans = (ans + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}
```





## 一、图论

### 最短路

#### 1.dijkstra（单源最短路）

```c++
/**
 * @brief dijkstra单源最短路 
 *  数据范围：0~n-1
 * 
 */
int n;
int cost[N][N], d[N];
bool used[N];

void dijkstra(int s) {
    std::fill(d, d + n, INF);
    std::fill(used, used + n, false);
    d[s] = 0;
    while (true) {
        int v = -1;
        for (int w = 0; w < n; w++) {
            if (!used[w] && (v == -1 || d[w] < d[v])) {
                v = w;
            }
        }
        if (v == -1) {
            break;
        }
        used[v] = true;
        for (int w = 0; w < n; w++) {
            d[w] = std::min(d[w], d[v] + cost[v][w]);
        }
    }
}
```



#### 2.dijkstra（单源最短路，优先队列优化）

```c++
/**
 * @brief dijkstra单源最短路 （优先队列优化）
 *  数据范围：0~n-1
 * 
 */
struct edge {
    int to, cost;
};
int n, d[N];
std::vector<edge> G[N];

void dijkstra(int s) {
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    std::fill(d, d + n, INF);
    d[s] = 0;
    que.push(P(0, s));
    while (!que.empty()) {
        P p = que.top();
        que.pop();
        int v = p.second;
        if (d[v] < p.first) {
            continue;
        }
        for (int i = 0; i < G[v].size(); i++) {
            edge e = G[v][i];
            if (d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}
```



### 最小生成树

#### 1.kruskal

```c++
/**
 * @brief kruskal（并查集）
 *  数据范围：0~n、0~m-1
 * 
 */
struct edge {
    int v, w, cost;
};
edge es[N];
int n, m;
int par[N], rk[N];

void init() {
    for (int i = 0; i < n; i++) {
        par[i] = i;
        rk[i] = 0;
    }
}

int find(int x) {
    if (par[x] == x) {
        return x;
    }
    return par[x] = find(par[x]);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
        return;
    }
    if (rk[x] < rk[y]) {
        par[x] = y;
    } else {
        par[y] = x;
        if (rk[x] == rk[y]) {
            rk[x]++;
        }
    }
}

bool same(int x, int y) {
    return find(x) == find(y);
}

int kruskal() {
    std::sort(es, es + m, [](edge a, edge b) {
        return a.cost < b.cost;
    });
    init();
    int res = 0;
    for (int i = 0; i < m; i++) {
        edge e = es[i];
        if (!same(e.v, e.w)) {
            unite(e.v, e.w);
            res += e.cost;
        }
    }
    return res;
}
```



### 二分图

#### 1.二分图匹配（最大匹配数）

```c++
/**
 * @brief 二分图匹配（最大匹配数）
 *  数据范围：1~n、1~m
 * 
 */
int n, m;
bool used[N];
int match[N], G[N][N];

int find(int x) {
    for (int i = 1; i <= m; i++) {
        if (!used[i] && G[x][i]) {
            used[i] = true;
            if (!match[i] || find(match[i])) {
                match[i] = x;
                return 1;
            }
        }
    }
    return 0;
}

int solve() {
    int res = 0;
    for (int i = 1; i <= n; i++) {
        std::memset(used, 0, sizeof(used));
        if (find(i)) {
            res++;
        }
    }
    return res;
}
```



### Tarjin（强连通分量分解、缩点）

```c++
/**
 * @brief Tarjin（强连通分量分解、缩点）
 * 数据范围：0~m-1、0~n-1
 */
struct {
    int v, next;
} edge[N];
int cnt, head[N];
int top, flag, tot, sta[N], dfn[N], low[N], id[N];
bool used[N];

void add_edge(int u, int v) {
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void init() {
    cnt = top = flag = tot = 0;
    std::memset(head, -1, sizeof(head));
    std::memset(dfn, 0, sizeof(dfn));
    std::memset(used, 0, sizeof(used));
}

void tarjin(int u) {
    dfn[u] = low[u] = ++flag;
    used[u] = true;
    sta[top++] = u;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (!dfn[v]) {
            tarjin(v);
            low[u] = std::min(low[u], low[v]);
        } else if (used[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        tot++;
        int t;
        do {
            t = sta[--top];
            used[t] = false;
            id[t] = tot;
        } while(t != u);
    }
}

void solve() {
    int n, m, u, v; // 删除
    init();
    for (int i = 0; i < m; i++) {
        add_edge(u, v);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjin(i);
        }
    }
}
```



### 拓扑排序

#### 1.有向图判环

```c++
/**
 * @brief 有向图判环
 *  数据范围：点：1~n，边：1~m  
 */
int n, m, in[N];
std::vector<int> G[N];

bool top_sort() {
    int res = 0;
    std::queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            que.push(i);
        }
    }
    while (!que.empty()) {
        int i = que.front();
        que.pop();
        res++;
        for (int j = 0; j < G[i].size(); j++) {
            if (!--in[G[i][j]]) {
                que.push(G[i][j]);
            }
        }
        G[i].clear();
    }
    return res != n;
}

void solve() {
    int u, v;
    while (m--) {
        G[u].push_back(v);
        in[v]++;
    }
    bool ans = top_sort();
}
```



#### 2.有向无环图最长路径

```c++
/**
 * @brief 有向无环图最长路径
 *  数据范围：点：1~n，边：1~m  
 */
int n, m, in[N], dp[N];
std::vector<P> G[N];

void top_sort() {
    std::queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            que.push(i);
        }
    }
    while (!que.empty()) {
        int t = que.front();
        que.pop();
        for (int i = 0; i < G[t].size(); i++) {
            int v = G[t][i].first, c = G[t][i].second;
            if (!--in[v]) {
                que.push(v);
            }
            dp[v] = std::max(dp[v], dp[t] +c);
        }
        G[t].clear();
    }
}

void solve() {
    int u, v, c;
    while (m--) {
        G[u].push_back(P(v, c));
        in[v]++;
    }
    top_sort();
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, dp[i]);
    }
}
```



### 2-SAT

```c++
/**
 * @brief 2-SAT
 *  给每个布尔变量赋值，使得所有条件可以得到满足
 *   数据范围：1~2n
 * 
 *      aVb = !a->b 且 !b->a
 *      如果x的拓排序比!x的拓排序大（id[x]比id[!x]小）则x为真
 */

struct {
    int v, next;
} edge[N];
int cnt, head[N];
int top, flag, tot, sta[N], dfn[N], low[N], id[N];
bool used[N];

void add_edge(int u, int v) {
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void init() {
    cnt = top = flag = tot = 0;
    std::memset(head, -1, sizeof(head));
    std::memset(dfn, 0, sizeof(dfn));
    std::memset(used, 0, sizeof(used));
}

void tarjin(int u) {
    dfn[u] = low[u] = ++flag;
    used[u] = true;
    sta[top++] = u;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (!dfn[v]) {
            tarjin(v);
            low[u] = std::min(low[u], low[v]);
        } else if (used[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        tot++;
        int t;
        do {
            t = sta[--top];
            used[t] = false;
            id[t] = tot;
        } while(t != u);
    }
}

void solve() {
    int n, m; // 删除
    init();
    while (m--) {
        int u1, v1, u2, v2;
        add_edge(u1 + n * (v1 & 1), u2 + n * (v2 ^ 1)); // !a->b
        add_edge(u2 + n * (v2 & 1), u1 + n * (v1 ^ 1)); // !b->a
    }
    for (int i = 1; i <= 2 * n; i++) {
        if (!dfn[i]) {
            tarjin(i);
        }
    }
    bool f = true;
    for (int i = 1; i <= n; i++) {
        if (id[i] == id[i + n]) {
            f = false;
            break;
        }
    }
    if (!f) {
        std::cout << "Error\n"; 
    } else {
        for (int i = 1; i <= n; i++) {
            std::cout << id[i] < id[i + n] << '\n';
        }
    }
}
```



### LCA

```c++
/**
 * @brief LCA
 *  数据范围：点：1~n，边：1~2m
 */
struct edge {
    int to, next;
} es[M << 1];
int cnt, head[N];
int d[N], par[N][21];

void add_edge(int u, int v) {
    es[cnt].to = v;
    es[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u, int f) {
    d[u] = d[f] + 1;
    par[u][0] = f;
    for (int i = 1; (1 << i) <= d[u]; i++) {
        par[u][i] = par[par[u][i - 1]][i - 1];
    }
    for (int i = head[u]; ~i; i = es[i].next) {
        int v = es[i].to;
        if (v == f) {
            continue;
        }
        dfs(v, u);
    }
} 

int lca(int u, int v) {
    if (d[u] > d[v]) {
        std::swap(u, v);
    }
    for (int i = 20; i >= 0; i--) {
        if (d[u] <= d[v] - (1 << i)) {
            v = par[v][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 20; i >= 0; i--) {
        if (par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

void solve() {
    int s, u, v, n, m;
    std::memset(head, -1, sizeof(head));
    for (int i = 1; i <= m; i++) {
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(s, 0);
    // lca(u, v)
}
```



### 树链剖分

```c++
/**
 * @brief 树链剖分
 *  数据范围：1~n
 * 
 *  1：将树从x到y节点的最短路径上的所有节点的值都加上z
 *  2：求树从x到y节点的最短路径上的所有节点的值的和
 *  3：将以x为根节点的子树上的所有节点值加上z
 *  4：求以x为根节点的子树上的所有节点值的和
 */
struct edge {
    int to, next;
} es[M];
struct node {
    int l, r, sum;
} seg[N << 2];

int cnt, head[N];
int lazy[N << 2];
int tot, dep[N], sz[N], par[N], id[N], son[N], top[N], val[N];
int rt, mod, n, m, d[N];

void add_edge(int u, int v) {
    es[cnt].to = v;
    es[cnt].next = head[u];
    head[u] = cnt++;
}

void pushdown(int i, int len) {
    if (lazy[i]) {
        lazy[i << 1] += lazy[i];
        lazy[i << 1] %= mod;
        lazy[(i << 1) | 1] += lazy[i];
        lazy[(i << 1) | 1] %= mod;
        seg[i << 1].sum = (seg[i << 1].sum + lazy[i] * (len - (len >> 1)) % mod) % mod;
        seg[(i << 1) | 1].sum = (seg[(i << 1) | 1].sum + lazy[i] * (len >> 1) % mod) % mod;
        lazy[i] = 0;
    }
}

void pushup(int i) {
    seg[i].sum = (seg[i << 1].sum + seg[(i << 1) | 1].sum) % mod;
}

void build(int l, int r, int rt) {
    seg[rt].l = l;
    seg[rt].r = r;
    lazy[rt] = 0;
    if (l == r) {
        seg[rt].sum = d[l] % mod;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, (rt << 1) | 1);
    pushup(rt);
}

int get_sum(int l, int r, int rt) {
    if (seg[rt].l == l && seg[rt].r == r) {
        return seg[rt].sum;
    }
    int mid = (seg[rt].l + seg[rt].r) >> 1;
    pushdown(rt, seg[rt].r - seg[rt].l + 1);
    if (r <= mid) {
        return get_sum(l, r, rt << 1);
    } else if (l > mid) {
        return get_sum(l, r, (rt << 1) | 1);
    }
    return get_sum(l, mid, rt << 1) + get_sum(mid + 1, r, (rt << 1) | 1);
}

void update(int v, int l, int r, int rt) {
    if (seg[rt].l == l && seg[rt].r == r) {
        lazy[rt] = (lazy[rt] + v) % mod;
        seg[rt].sum = (seg[rt].sum + v * (r - l + 1) % mod) % mod;
        return;
    }
    if (seg[rt].l == seg[rt].r) {
        return;
    }
    int mid = (seg[rt].l + seg[rt].r) >> 1;
    pushdown(rt, seg[rt].r - seg[rt].l + 1);
    if (r <= mid) {
        update(v, l, r, rt << 1);
    } else if (l > mid) {
        update(v, l, r, (rt << 1) | 1);
    } else {
        update(v, l, mid, rt << 1);
        update(v, mid + 1, r, (rt << 1) | 1);
    }
    pushup(rt);
}

void dfs1(int u, int f, int depth) {
    dep[u] = depth;;
    sz[u] = 1;
    son[u] = 0;
    par[u] = f;
    for (int i = head[u]; ~i; i = es[i].next) {
        int v = es[i].to;
        if (v == f) {
            continue;
        }
        dfs1(v, u, depth + 1);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v]) {
            son[u] = v;
        }
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    id[u] = ++tot;
    val[tot] = d[u];
    if (son[u]) {
        dfs2(son[u], tp);
    }
    for (int i = head[u]; ~i; i = es[i].next) {
        int v = es[i].to;
        if (v == par[u] || v == son[u]) {
            continue;
        }
        dfs2(v, v);
    }
}

void add(int u, int v, int w) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            std::swap(u, v);
        }
        update(1, id[top[u]], id[u], w);
        u = par[top[u]];
    }
    if (dep[u] > dep[v]) {
        std::swap(u, v);
    }
    update(1, id[u], id[v], w);
}

int sum(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            std::swap(u, v);
        }
        res = (res + get_sum(1, id[top[u]], id[u])) % mod;
        u = par[top[u]];
    }
    if (dep[u] > dep[v]) {
        std::swap(u, v);
    }
    res = (res + get_sum(1, id[u], id[v])) % mod;
    return res;
}

void solve() {
    int u, v;
    std::memset(head, -1, sizeof(head));
    while (m--) {
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs1(rt, 0, 1);
    dfs2(rt, rt);
    build(1, 1, n);

    /**
     * 1: add(u, v, w)
     * 2: sum(u, v)
     * 3: update(1, id[u], id[u] + sz[u] -1, w)
     * 4: get_sum(1, id[u], id[u] + sz[u] -1)
     */
}
```



### 网络流

#### 1.ek最大流

```c++
/**
 * @brief EK最大流算法
 *  数据范围：1~n
 */
int n, m, G[N][N], pre[N];
bool used[N];

bool bfs(int s, int t) {
    std::memset(used, 0 , (n + 1) * sizeof(bool));
    std::memset(pre, -1 , (n + 1) * sizeof(int));
    std::queue<int> que;
    pre[s] = s;
    used[s] = true;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = 1; i <= n; i++) {
            if (!used[i] && G[u][i] > 0) {
                pre[i] = u;
                used[i] = true;
                if (i == t) {
                    return true;
                }
                que.push(i);
            }
        }
    }
    return false;
}

int ek(int s, int t) {
    int res = 0;
    while (bfs(s, t)) {
        int d = INF;
        for (int i = t; i != s; i = pre[i]) {
            d = std::min(d, G[pre[i]][i]);
        }
        for (int i = t; i != s; i = pre[i]) {
            G[pre[i]][i] -= d;
            G[i][pre[i]] += d;
        }
        res += d;
    }
    return res;
}

void solve() {
    while (m--) {
        int u, v, w;
        G[u][v] += w;
    }
    int ans = ek(1, n);
}
```





## 二、数据结构

### 手写堆

```c++
/**
 * @brief 小顶堆
 *  索引范围：1~n-1，n为当前剩余空位，左右索引[index*2+1, index*2]
 *  堆顶：hp[0]
 */
int hp[N], n = 0;

void push(int x) {
    int index = n++;
    while (index > 0) {
        int p = (index - 1) / 2;
        if (hp[p] <= x) {
            break;
        }
        hp[index] = hp[p];
        index = p;
    }
    hp[index] = x;
}

int pop() {
    int ret = hp[0], x = hp[--n], index = 0;
    while (index * 2 + 1 < n) {
        int left = index * 2 + 1, right = index * 2 + 2;
        if (right < n && hp[right] < hp[left]) {
            left = right;
        }
        if (hp[left] >= x) {
            break;
        }
        hp[index] = hp[left];
        index = left;
    }
    hp[index] = x;
    return ret;
} 
```



### 单调栈（柱形图包含的长方形的最大面积）

```c++
/**
 * @brief 单调栈（柱形图包含的长方形的最大面积）
 *  数据范围：1~n
 */
int n, h[N], l[N], r[N];

int solve() {
    std::stack<int> sta;
    for (int i = 1; i <= n; i++) {
        while (!sta.empty() && h[sta.top()] >= h[i]) {
            sta.pop();
        }
        l[i] = sta.empty() ? 1 : sta.top() + 1;
        sta.push(i);
    }
    std::stack<int> sta2;
    for (int i = n; i >= 1; i++) {
        while (!sta2.empty() && h[sta2.top()] >= h[i]) {
            sta2.pop();
        }
        r[i] = sta2.empty() ? n : sta2.top() - 1;
        sta2.push(i);
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = std::max(res, (r[i] - l[i] + 1) * h[i]);
    }
    return res;
}
```



### 单调队列（固定长度区间最大、小值）

```c++
/**
 * @brief 单调队列求固定长度区间最大、小值
 *  索引范围：1~n，长度：k
 *  mx[]、mn[]的索引范围：[1,n-k+1]
 * 
 */
int n, k, d[N], mn[N], mx[N];
std::deque<int> dq;

void clear(std::deque<int>& dq) {
    std::deque<int> empty;
    std::swap(empty, dq);
}

void solve() {
    for (int i = 1; i <= n; i++) {
        while (!dq.empty() && d[dq.back()] >= d[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i - k + 1 > 0) {
            mn[i - k + 1] = d[dq.front()];
            if (dq.front() == i - k + 1) {
                dq.pop_front();
            }
        }
    }
    clear(dq);
    for (int i = 1; i <= n; i++) {
        while (!dq.empty() && d[dq.back()] <= d[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i - k + 1 > 0) {
            mx[i -k + 1] = d[dq.front()];
            if (dq.front() == i - k + 1) {
                dq.pop_front();
            }
        }
    }
}
```





### 并查集

```c++
/**
 * @brief 并查集
 *  带高度优化
 *  数据范围：1~n-1
 * 
 */
int n, par[N], rk[N];

void init() {
    for (int i = 0; i < n; i++) {
        par[i] = i;
        rk[i] = 0;
    }
}

int find(int x) {
    if (par[x] == x) {
        return x;
    }
    return par[x] = find(par[x]);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
        return;
    }
    if (rk[x] < rk[y]) {
        par[x] = y;
    } else {
        par[y] = x;
        if (rk[x] == rk[y]) {
            rk[x]++;
        }
    }
}

bool same(int x, int y) {
    return find(x) == find(y);
}
```



### ST表（区间最大、小值查询，不能更新）

```c++
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
    for (int j = 1; j <= 21; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            mx[i][j] = std::max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
            mn[i][j] = std::min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
        }
    }
}
```



### 树状数组

#### 1.单点更新，区间求和

```c++
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



#### 2.区间更新，单点查询

```c++
/**
 * @brief 树状数组（区间更新，单点查询）
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



#### 3.区间更新，区间查询

```c++
/**
 * @brief 树状数组（区间更新，区间查询）
 *  数据范围：1~n，bit[i][0]为公式前面，bit[i][1]为公式后面
 *     arr[1~3]：
 *        (3+1)*(c[1]+c[2]+c[3])-(1*c[1]+2*c[2]+3*c[3])
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



#### 4.单点更新，区间最值

```c++
/**
 * @brief 树状数组（单点更新，区间最值）
 *  数据范围：1~n，这里算的是max，最小值只需把max换成min即可
 *     7(111)   6(110)      4(100)
 *              5(101)   2(010) 3(101)
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



### 线段树

#### 1.单点更新，区间查询

```c++
/**
 * @brief 线段树（单点更新，区间查询）
 *  数据范围：1~n，根标号：1，左节点标号:i<<1，右节点标号：(i<<1)|1
 *                        1[1~5]
 *               2[1~3]              3[4~5]
 *         4[1~2]     5[3~3]      6[4~4] 7[5~5]
 *     8[1~1] 9[2~2]  
 *  
 */ 
struct node {
    int l, r, sum, mx;
};
int n, arr[N];
node seg[N << 2];

void pushup(int i) {
    seg[i].sum = seg[i << 1].sum + seg[(i << 1) | 1].sum;
    seg[i].mx = std::max(seg[i << 1].mx, seg[(i << 1) | 1].mx);
}

void build(int i, int l, int r) {
    seg[i].l = l;
    seg[i].r = r;
    if (l == r) {
        seg[i].sum = arr[l];
        seg[i].mx = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(i << 1, l, mid);
    build((i << 1) | 1, mid + 1, r);
    pushup(i);
}

int get_sum(int i, int l, int r) {
    if (seg[i].l == l && seg[i].r == r) {
        return seg[i].sum;
    }
    int mid = (seg[i].l + seg[i].r) /2;
    if (r <= mid) {
        return get_sum(i << 1, l, r);
    } else if (l > mid) {
        return get_sum((i << 1) | 1, l, r);
    }
    return get_sum(i << 1, l, mid) + get_sum((i << 1) | 1, mid + 1, r);
}

int get_max(int i, int l, int r) {
    if (seg[i].l == l && seg[i].r == r) {
        return seg[i].mx;
    }
    int mid = (seg[i].l + seg[i].r) /2;
    if (r <= mid) {
        return get_max(i << 1, l, r);
    } else if (l > mid) {
        return get_max((i << 1) | 1, l, r);
    }
    return std::max(get_max(i << 1, l, mid), get_max((i << 1) | 1, mid + 1, r));
}

void add(int i, int k, int v) {
    if (seg[i].l == k && seg[i].r == k) {
        seg[i].sum += v;
        seg[i].mx += v;
        return;
    }
    int mid = (seg[i].l + seg[i].r) / 2;
    if (k <= mid) {
        add(i << 1, k, v);
    } else {
        add((i << 1) | 1, k, v);
    }
    pushup(i);
}

void solve() {
    build(1, 1, n);
}
```



#### 2.区间更新，区间查询

```c++
/**
 * @brief 线段树（区间更新，区间查询）
 *  数据范围：1~n，根标号：1，左节点标号:i<<1，右节点标号：(i<<1)|1
 *                        1[1~5]
 *               2[1~3]              3[4~5]
 *         4[1~2]     5[3~3]      6[4~4] 7[5~5]
 *     8[1~1] 9[2~2]  
 *  
 */ 
struct node {
    int l, r, sum;
};
int arr[N], lz[N << 2];
node seg[N << 2];

void pushdown(int rt, int m) {
    if (lz[rt]) {
        lz[rt << 1] += lz[rt];
        lz[(rt << 1) | 1] += lz[rt];
        seg[rt << 1].sum += lz[rt] * (m - (m >> 1));
        seg[(rt << 1) | 1].sum += lz[rt] * (m >> 1);
        lz[rt] = 0;
    }
}

void pushup(int rt) {
    seg[rt].sum = seg[rt << 1].sum + seg[(rt << 1) | 1].sum;
}

void build(int l, int r, int rt) {
    seg[rt].l = l;
    seg[rt].r = r;
    lz[rt] = 0;
    if (l == r) {
        seg[rt].sum = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, (rt << 1) | 1);
    pushup(rt);
}

int query(int l, int r, int rt) {
    if (seg[rt].l == l && seg[rt].r == r) {
        return seg[rt].sum;
    }
    int mid = (seg[rt].l + seg[rt].r) >> 1;
    pushdown(rt, seg[rt].r - seg[rt].l + 1);
    if (r <= mid) {
        return query(l, r, rt << 1);
    } else if (l > mid) {
        return query(l, r, (rt << 1) | 1);
    }
    return query(l, mid, rt << 1) + query(mid + 1, r, (rt << 1) | 1);
}

void update(int v, int l, int r, int rt) {
    if (seg[rt].l == l && seg[rt].r == r) {
        lz[rt] += v;
        seg[rt].sum += v * (r - l + 1);
        return;
    }
    if (seg[rt].l == seg[rt].r) {
        return;
    }
    int mid = (seg[rt].l + seg[rt].r) >> 1;
    pushdown(rt, seg[rt].r - seg[rt].l + 1);
    if (r <= mid) {
        update(v, l, r, rt << 1);
    } else if (l > mid) {
        update(v, l, r, (rt << 1) | 1);
    } else {
        update(v, l, mid, rt << 1);
        update(v, mid + 1, r, (rt << 1) | 1);
    }
    pushup(rt);
}
```





## 三、数论

### 快速幂

```c++
typedef long long ll;

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res *= a;
        }
        a *= a;
        b >>= 1;
    }
    return res;
}

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
```



### 素性测试、约数枚举、整数分解

```c++
/**
 * @brief 素性测试、约数枚举、整数分解
 * 
 */

// 素性测试
bool pri(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return n != 1;
}

// 约数枚举
std::vector<int> divisor(int n) {
    std::vector<int> vec;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            vec.push_back(i);
            if (i != n / i) {
                vec.push_back(n / i);
            }
        }
    }
    return vec;
}

// 整数分解
std::map<int, int> decompose(int n) {
    std::map<int, int> mp;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            mp[i]++;
            n /= i;
        }
    }
    if (n != 1) {
        mp[n] = 1;
    }
    return mp;
}
```



### 素数筛

#### 埃氏筛

```c++
/**
 * @brief 埃氏筛 
 * 
 */
bool pri[N];

void init() {
    std::fill(pri, pri + N, true);
    pri[0] = pri[1] = false;
    for (int i = 2; i < N; i++) {
        if (pri[i]) {
            for(int j = 2 * i; j < N; j += i) {
                pri[j] = false;
            }
        }
    }
}
```



#### 欧拉筛

```c++
/**
 * @brief 欧拉筛
 * 
 */
int d[N];
bool pri[N];

void init() {
    int n = 1;
    std::fill(pri, pri + N, true);
    pri[0] = pri[1] = false;
    for (int i = 2; i < N; i++) {
        if (pri[i]) {
            d[n++] = i;
        }
        for (int j = 1; j < n; j++) {
            if (i * d[j] > N) {
                break;
            }
            pri[i * d[j]] = false;
            if (i % d[j] == 0) {
                break;
            }
        }
    }
}
```



### 欧几里得定理

```c++
/**
 * @brief 欧几里得定理
 *  a=kb+r
 */

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

```



### 扩展欧几里得定理

```c++
/**
 * @brief 欧几里得定理
 *  ax+by=gcd(a,b)=gcd(b,a%b)=b*x0+(a%b)*y0
 *      x0,y0为下层的值
 *  ax+by=a*y0+b*(x0-[a/b]*y0)，已递归求出下层的x0，y0，
 *  反过来求当前层的x，y：x=y0，y=x0-[a/b]*y0
 */
int exgcd(int a, int b, int& x, int& y) {
    int res = a;
    if (b) {
        res = exgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1;
        y = 0;
    }
    return res;
}
```



### 同余方程

#### 一元线性同余方程

```c++

/**
 * @brief 一元线性同余方程
 *  Xa 恒等于 b(mod m)
 *  求X
 *      ax + my = b 
 *      d = gcd(a, m)
 *      (a/d)x + (m/d)y = b/d
 *      (a/d)x + (m/d)y = 1 => ax + my = d 即扩展欧几里得
 *      X = x0 * (b/d) % (m/d)    
 */

ll f(ll a, ll b, ll m) {
    ll x, y, d;
    d = exgcd(a, m, x, y);
    if (b % d) {
        return -1;
    }
    x = x * (b / d) % (m / d);
    return (x % (m / d) + (m / d)) % (m / d);
}
```





## 四、字符串

### Manacher（最大回文子串：回文半径） 

```c++
/**
 * @brief Manacher（最大回文子串：回文半径） 
 *  数据范围：N为字符串长度的两倍，
 *      p为当前mx最远的回文串的中心 
 */
int Len[N];

int manacher(std::string s) {
    std::string t;
    t += "^";
    t += "#";
    for (int i = 0; i < s.size(); i++) {
        t += s[i];
        t += "#";
    }
    t += "$";
    int len = t.size(), p = 0, mx = 0, res = 0;
    for (int i = 1; i <= len - 2; i++) {
        Len[i] = mx > i ? std::min(Len[2 * p - i], mx - i) : 1;
        while (t[i + Len[i]] == t[i - Len[i]]) {
            Len[i]++;
        }
        if (i + Len[i] > mx) {
            mx = i + Len[i];
            p = i;
        }
        res = std::max(res, Len[i] - 1);
    }
    return res;
}
```



### 普通kmp

```c++
/**
 * @brief kmp（字符串匹配、个数统计）
 *  数据范围：1~n-1
 */
int next[N];

void get_next(char* T) {
    int i = 0, j = -1, len = std::strlen(T);
    next[0] = -1;
    while (i < len) {
        if (j == -1 || T[i] == T[j]) {
            next[++i] = ++j;
        } else {
            j = next[j];
        }
    }
}

int kmp_index(char* S, char* T) {
    int i = 0, j = 0, len_s = std::strlen(S), len_t = std::strlen(T);
    get_next(T);
    while (i < len_s && j < len_t) {
        if (j == -1 || S[i] == T[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j == len_t) {
        return i - len_t;
    }
    return -1;
}

int kmp_count(char* S, char* T) {
    int res = 0, len_s = std::strlen(S), len_t = std::strlen(T);
    if (len_s == 1 && len_t == 1) {
        if (S[0] == T[0]) {
            return 1;
        } else {
            return 0;
        }
    }
    get_next(T);
    for (int i = 0, j = 0; i < len_s; i++) {
        while (j > 0 && S[i] != T[j]) {
            j = next[j];
        }
        if (S[i] == T[j]) {
            j++;
        }
        if (j == len_t) {
            res++;
            j = next[j];
        }
        return res;
    }
}
```



### 扩展kmp（后缀匹配前缀）

```c++
/**
 * @brief 扩展kmp（后缀匹配前缀）
 *  数据范围：0~n-1
 */
int next[N], extend[N];

void get_next(std::string t) {
    int p = 0, len = t.size();
    next[0] = len;
    while (p + 1 < len && t[p] == t[p + 1]) {
        p++;
    }
    next[1] = p;
    p = 1;
    for (int i = 2; i < len; i++) {
        if (i + next[i - p] < p + next[p]) {
            next[i] = next[i - p];
        } else {
            int j = p + next[p] - i > 0 ? p + next[p] - i : 0;
            while (i + j < len && t[j] == t[i + j]) {
                j++;
            }
            next[i] = j;
            p = i;
        }
    }
}

void get_extend(std::string s, std::string t) {
    int p = 0, i = 0, len_s = s.size(), len_t = t.size();
    get_next(t);
    while (i < len_s && i < len_t && s[i] == t[i]) {
        i++;
    }
    extend[0] = i;
    p = 0;
    for (i = 1; i < len_s; i++) {
        if (i + next[i - p] < p + extend[p]) {
            extend[i] = next[i - p];
        } else {
            int j = p + extend[p] - i > 0 ? p + extend[p] - i : 0;
            while (i + j < len_s && j < len_t && t[j] == s[i + j]) {
                j++;
            }
            extend[i] = j;
            p = i;
        }
    }
}
```



### 字典树

```c++
/**
 * @brief 字典树
 *  数据范围：1~n，0为头结点
 */
struct node {
    int cnt;
    int next[26];
    void init() {
        cnt = 0;
        std::memset(next, -1, sizeof(next));
    }
} T[N];
int cnt;

void insert(std::string s) {
    int p = 0;
    for (int i = 0; i < s.size(); i++) {
        int j = s[i] - 'a';
        if (T[p].next[j] == -1) {
            T[cnt].init();
            T[p].next[j] = cnt++;
        }
        p = T[p].next[j];
        T[p].cnt++;
    }
}

bool query(std::string s) {
    int p = 0;
    for (int i = 0; i < s.size(); i++) {
        int j = s[i] - 'a';
        if (T[p].next[j] == -1) {
            return false;
        }
        p = T[p].next[j];
    }
    return true;
}
```



### 01字典树（求异或值最大的数）

```c++
/**
 * @brief 01字典树（求异或值最大的数）
 *  数据范围：1~n*32，0为头结点
 */
int cnt, trie[N * 32][2];
ll val[N * 32];

void init() {
    cnt = 1;
    std::memset(trie[0], 0, sizeof(trie[0]));
}

void insert(ll x) {
    int u = 0;
    for (int i = 32; i >= 0; i--) {
        int v = (x >> i) & 1;
        if (!trie[u][v]) {
            std::memset(trie[cnt], 0, sizeof(trie[cnt]));
            val[cnt] = 0;
            trie[u][v] = cnt++;
        }
        u = trie[u][v];
    }
    val[u] = x;
}

ll query(ll x) {
    int u = 0;
    for (int i = 32; i >= 0; i--) {
        int v = (x >> i) & 1;
        if (trie[u][v ^ 1]) {
            u = trie[u][v ^ 1];
        } else {
            u = trie[u][v];
        }
    }
    return val[u];
}
```





## 五、其它算法

### 分块算法

#### 1.区间更新，单点查询

```c++
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



#### 2.区间更新，查询区间内小于x的元素的个数

```c++
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



#### 3.区间更新，查询区间小于x的最大值

```c++
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



#### 4.区间更新，区间求和

```c++
/**
 * @brief 区间更新，区间求和
 *  数据范围：1~n, M为sqrt(N)
 * 
 */
int len, id[N], lazy[N];
int sum[M];
int n, d[N];

void add(int l, int r, int v) {
    for (int i = l; i < std::min(id[l] * len, r); i++) {
        d[i] += v;
        sum[id[l]] += v;
    }
    if (id[l] != id[r]) {
        for (int i = (id[r] - 1) * len + 1; i <= r; i++) {
            d[i] += v;
            sum[id[r]] += v;
        }
    }
    for (int i = id[l] + 1; i <= id[r] - 1; i++) {
        lazy[i] += v;
    }
}

int query(int l, int r, int v) {
    int res = 0;
    for (int i = l; i <= std::min(id[l] * len, r); i++) {
        res += d[i] + lazy[id[l]];
    }
    if (id[l] != id[r]) {
        for (int i = (id[r] - 1) * len + 1; i <= r; i++) {
            res += d[i] + lazy[id[r]];
        }
    }
    for (int i = id[l] + 1; i <= id[r] - 1; i++) {
        res += sum[i] + len * lazy[i];
    }
    return res;
}

void solve() {
    len = std::sqrt(n);
    for (int i = 1; i <= n; i++) {
        id[i] = (i - 1) / len + 1;
        sum[id[i]] += d[i];
    }
}
```



#### 5.区间开方，区间求和

```c++
/**
 * @brief 区间开方，区间求和
 *  数据范围：1~n, M为sqrt(N)
 * 
 */
int len, id[N], lazy[N];
bool used[M], sum[M];
int n, d[N];

void exec_sqrt(int x) {
    if (used[x]) {
        return;
    }
    used[x] = true;
    sum[x] = 0;
    for (int i = (x - 1) * len + 1; i <= x * len; i++) {
        d[i] = std::sqrt(d[i]);
        sum[x] += d[i];
        if (d[i] > 1) {
            used[x] = false;
        }
    }
}

void add(int l, int r) {
    for (int i = l; i < std::min(id[l] * len, r); i++) {
        sum[id[l]] -= d[i];
        d[i] = std::sqrt(d[i]);
        sum[id[l]] += d[i];
    }
    if (id[l] != id[r]) {
        for (int i = (id[r] - 1) * len + 1; i <= r; i++) {
            sum[id[r]] -= d[i];
            d[i] = std::sqrt(d[i]);
            sum[id[r]] += d[i];
        }
    }
    for (int i = id[l] + 1; i <= id[r] - 1; i++) {
        exec_sqrt(i);
    }
}

int query(int l, int r, int v) {
    int res = 0;
    for (int i = l; i <= std::min(id[l] * len, r); i++) {
        res += d[i];
    }
    if (id[l] != id[r]) {
        for (int i = (id[r] - 1) * len + 1; i <= r; i++) {
            res += d[i];
        }
    }
    for (int i = id[l] + 1; i <= id[r] - 1; i++) {
        res += sum[i];
    }
    return res;
}

void solve() {
    len = std::sqrt(n);
    for (int i = 1; i <= n; i++) {
        id[i] = (i - 1) / len + 1;
        sum[id[i]] += d[i];
    }
}
```



#### 6.区间乘法，区间加法，单点查询

```c++
/**
 * @brief 区间乘法，区间加法，单点查询
 *  数据范围：1~n, M为sqrt(N)
 * 
 */
int len, id[N], lazy_add[M], lazy_mul[M];
int n, d[N];

void reset(int x) {
    for (int i = (x - 1) * len + 1; i <= std::min(x * len, n); i++) {
        d[i] = d[i] * lazy_mul[x] + lazy_add[x];
    }
    lazy_mul[x] = 1;
    lazy_add[x] = 0;
}

void add(int f, int l, int r, int v) {
    reset(id[l]);
    for (int i = l; i < std::min(id[l] * len, r); i++) {
        if (f) {
            d[i] *= v;
        } else {
            d[i] += v;
        }
    }
    if (id[l] != id[r]) {
        reset(id[r]);
        for (int i = (id[r] - 1) * len + 1; i <= r; i++) {
            if (f) {
                d[i] *= v;
            } else {
                d[i] += v;
            }

        }
    }
    for (int i = id[l] + 1; i <= id[r] - 1; i++) {
        if (f) {
            lazy_mul[i] *= v;
            lazy_add[i] *= v;
        } else {
            lazy_add[i] += v;
        }
    }
}

void solve() {
    len = std::sqrt(n);
    for (int i = 1; i <= n; i++) {
        id[i] = (i - 1) / len + 1;
    }
    for (int i = 1; i <= id[n]; i++) {
        lazy_add[i] = 0;
        lazy_mul[i] = 1;
    }
    // 查询：d[i]*lazy_mul[id[i]]+lazy[id[i]]
}
```



#### 7.区间查询值为v的个数，并将该区间所有元素改为v

```c++
/**
 * @brief 区间查询值为v的个数，并将该区间所有元素改为v
 *  数据范围：1~n, M为sqrt(N)
 * 
 */
int len, id[N], lazy[M];
int n, d[N];

void reset(int x) {
    if (lazy[x] == -1) {
        return;
    }
    for (int i = (x - 1) * len + 1; i <= std::min(x * len, n); i++) {
        d[i] = lazy[x];
    }
    lazy[x] = -1;
}

int query(int l, int r, int v) {
    int res = 0;
    reset(id[l]);
    for (int i = l; i < std::min(id[l] * len, r); i++) {
        if (d[i] != v) {
            d[i] = v;
        } else {
            res++;
        }
    }
    if (id[l] != id[r]) {
        reset(id[r]);
        for (int i = (id[r] - 1) * len + 1; i <= r; i++) {
            if (d[i] != v) {
                d[i] = v;
            } else {
                res++;
            }
        }
    }
    for (int i = id[l] + 1; i <= id[r] - 1; i++) {
        if (lazy[i] != -1) {
            if (lazy[i] != v) {
                lazy[i] = v;
            } else {
                res += len;
            }
        } else {
            for (int j = (i - 1) * len + 1; j <= i * len; j++) {
                if (d[j] != v) {
                    d[j] = v;
                } else {
                    res++;
                }
            }
        }
    }
    return res;
}

void solve() {
    std::memset(lazy, -1, sizeof(lazy));
    len = std::sqrt(n);
    for (int i = 1; i <= n; i++) {
        id[i] = (i - 1) / len + 1;
    }
}
```





## 六、基础算法



## 七、搜索



## 八、动态规划

### 背包问题

#### 1.01背包

```c++
for (int i = 0; i < n; i++) {
    for (int j = m; j >= w[i]; j--) {
        dp[j] = std::max(dp[j], dp[j - w[i]] + v[i]);
    }
}
```



#### 2.完全背包

```c++
for (int i = 0; i <= n; i++) {
    for (int j = w[i]; j <= m; j++) {
        dp[j] = std::max(dp[j], dp[j - w[i]] + v[i]);
    }
}
```



#### 3.多重背包

```c++
for (int i = 0; i < n; i++) {
    for (int j = m; j >= w[i]; j--) {
        for (int k = 1; k <= c[i] && j >= k * w[i]; k++) {
            dp[j] = std::max(dp[j], dp[j - k * w[i]] + k * [i]);
        }
    }
}
```



### 最长子序列问题

#### 1.最长公共子序列

```c++
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        if (s[i] == t[j]) {
            dp[i + 1][j + 1] = dp[i][j] + 1;
        } else {
            dp[i + 1][j + 1] = std::max(dp[i + 1][j], dp[i][j + 1]);
        }
    }
}
```



#### 2.最长上升子序列

```c++
int res = 0;
for (int i = 0; i < n; i++) {
    dp[i] = 1;
    for (int j = 0; j < i; j++) {
        if (a[j] < a[i]) {
            dp[i] = std::max(d[i], dp[j] + 1);
        }
        res = std::max(res, dp[i]);
    }
}
```



### 划分数

```c++
/**
 * @brief 划分数（j的i划分数） 
 *  把n划分为不超过m份的划分数
 * 
 */
int dp[N][N];

void solve() {
    dp[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (j >= i) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - i];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
}
```





## 九、组合数学

### 组合数

#### 基础组合数

```c++
/**
 * @brief 基础组合数 
 *  C(n,m)= A(n,m)/m!=n!/(n-m)!/m!
 */

ll C(int n, int m) {
    ll ans = 1;
    if (m < n - m) {
        m = n - m;
    }
    for (int i = m + 1; i <= n; i++) {
        ans *= i;
    }
    for (int i = 1; i <= n - m; i++) {
        ans /= i;
    }
    return ans;
}
```





## 十、计算几何