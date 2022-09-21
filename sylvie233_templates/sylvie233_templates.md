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



### 静态仙人掌

```c++
/**
 * @brief 静态仙人掌
 *  无向仙人掌图：任意一条边至多只出现在一条简单回路的无向连通图
 * 
 *  问题：给一个有n个点和m条边的仙人掌图，和q组询问，每次询问两个点u，v之间的最短路
 */

/**
 * @brief 圆方树：一种将图变成树的方法
 *  规则：
 *      1.对于每个环，在环心建一个方点，让环上一个割点做环的根，从割点向方点连一条权值为0的边，从方点向其它原点连一条权值为s的边，s是圆点到割点的最短路，这个方点与环上其它圆点连成菊花图
 *      2.对于不在环上的两个圆点，保留原图中的边权
 *      （利用tarjin完成图的转化）
 * 
 * 问题从图上的最短路转化为树上的最短路，利用倍增法（设p=lca（u，v））
 *      1.若p为圆点，则d(u,v)=d[u]+d[v]-2*d[p]
 *      2.若p为方点，则需要找出o在环上的两个儿子A，B，分别为u和v的祖先
 *          d(u,v)=d(A,B)+d(A,u)+d(B,v)
 *          d(A,B)可以利用环长（单向）求解，len=abs(s[A]-s[B])，d(A,B)=min(len, sc[A]-len)。其中是s[A]是A到割点的环长（单向，区分于d值），sc[A]是A所在环的总长度。
 *          d(A,u)=d[u]-d[A],d(B,v)=d[v]-d[B]
 * 
 */

struct edge {
    int v, w, ne;
} e[M];

int n, m, q;

int h1[N], h2[N], idx = 1;
int dfn[N], low[N], tim;
int s[N], sc[N], fa[N], fw[N], fe[N], cn;
int f[N][14], dep[N], d[N];

int A, B;

void add(int *h, int u, int v, int w) {
    e[++idx] = {v, w, h[u]};
    h[u] = idx;
}

// lca构建
void dfs(int u, int father) {
    dep[u] = dep[father] + 1;
    f[u][0] = father;
    for (int k = 1; k <= 13; k++) {
        f[u][k] = f[f[u][k - 1]][k - 1];
    }
    for (int i = h2[u]; i; i = e[i].ne) {
        int v = e[i].v, w = e[i].w;
        d[v] = d[u] + w;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        std::swap(u, v);
    }
    for (int k = 13; k >= 0; k--) {
        if (dep[f[u][k]] >= dep[v]) {
            u = f[u][k];
        }
    }
    if (u == v) {
        return u;
    }
    for (int k = 13; k >= 0; k--) {
        if (f[u][k] != f[v][k]) {
            u = f[u][k];
            v = f[v][k];
        }
    }
    // 存lca的两个儿子
    A = u;
    B = v;
    return f[u][0];
}

void build_tree(int u, int v, int w) {
    int sum = w;
    for (int k = v; k != u; k = fa[k]) {
        s[k] = sum;
        sum += fw[k]; // 单向环长前缀和
    }
    s[u] = sc[u] = sum;
    // 割点加0边
    add(h2, u, ++cn, 0);
    for (int k = v; k != u; k = fa[k]) {
        sc[k] = sum;
        // 构建菊花图，长度为割点的最短路（环总长-单向环长）
        add(h2, cn, k, std::min(s[k], sum - s[k]));
    }
}

void tarjan(int u, int ine) {
    dfn[u] = low[u] = ++tim;
    for (int i = h1[u]; i; i = e[i].ne) {
        int v = e[i].v, w = e[i].w;
        if (!dfn[v]) {
            fa[v] = u;
            fw[v] = w;
            fe[v] = i;
            tarjan(v, i);
            low[u] = std::min(low[u], low[v]);
            if (dfn[u] < low[v]) {
                // 非环边，直接加边（环边low[v]<=dnf[u]）
                add(h2, u, v, w);
            }
        } else if (i != (ine ^ 1)) {
            // 不是同一边的双向（边数邻近+1）
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    for (int i = h1[u]; i ; i = e[i].ne) {
        int v = e[i].v, w = e[i].w;
        // tarjin判环成功
        if (dfn[u] < dfn[v] && fe[v] != i) {
            build_tree(u, v, w);
        }
    }
}

int main(){
    std::cin >> n >> m >> q;
    cn = n;
    while(m--){
        int a, b, c;
        std::cin >> a >> b >> c;
        // 无向变有向
        add(h1, a, b, c);
        add(h1, b, a, c);
    }
    tarjan(1, -1); //找环建树
    dfs(1, 0); //lca打表
    while(q--){
        int u, v;
        std::cin >> u >> v;
        int p = lca(u, v);//找lca
        if (p <= n) {
            //若是圆点
            std::cout << d[u] + d[v] - 2 * d[p] << '\n';
        }
        else { 
            //若是方点
            int len = std::abs(s[A] - s[B]);
            int dAB = std::min(len, sc[A] - len);
            int dis = dAB + d[u] - d[A] + d[v] - d[B];
            std::cout << dis << '\n';
        }
    }
    return 0;
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



### 可持续化数组

```c++
/**
 * @brief 可持续化数组
 *  你需要维护这样的一个长度为 N 的数组，支持如下几种操作
 *      1.在某个历史版本上修改某一个位置上的值
 *      2.访问某个历史版本上的某一位置的值
 *      3.此外，每进行一次操作（对于操作2，即为生成一个完全一样的版本，不作任何改动），就会生成一个新的版本。版本编号即为当前操作的编号（从1开始编号，版本0表示初始状态数组）
 *  
 *  使用可持续化线段树来维护数组，区间维护下标，动态开点存储
 */

#define lc(x) tr[x].l
#define rc(x) tr[x].r

struct node {
    int l, r;
    int v;
} tr[N * 25];

int n, m, a[N];
int root[N], idx;

// 初始化区间（1，n）
void build(int &x, int l, int r) {
    x = ++idx;
    if (l == r) {
        tr[x].v = a[l];
        return;
    }
    int m = l + r >> 1;
    build(lc(x), l, m);
    build(rc(x), m + 1, r);
}

/**
 * @brief 修改历史版本上的pos上的值
 * 
 * @param x 当前版本的节点指针
 * @param y 被修改的节点指针
 * @param l 
 * @param r 
 * @param pos 
 * @param v 
 */
void modify(int &x, int y, int l, int r, int pos, int v) {
    x = ++idx;
    tr[x] = tr[y];
    if (l == r) {
        tr[x].v = v;
        return;
    }
    int mid = l + r >> 1;
    if (pos <= mid) {
        modify(lc(x), lc(y), l, mid, pos, v);
    } else {
        modify(rc(x), rc(y), mid + 1, r, pos, v);
    }
}

/**
 * @brief 访问历史版本上pos位置上的值
 * 
 * @param x 版本指针
 * @param l 
 * @param r 
 * @param pos 
 * @return int 
 */
int query(int x, int l, int r, int pos) {
    if (l == r) {
        return tr[x].v;
    }
    int mid = l + r >> 1;
    if (pos <= mid) {
        return query(lc(x), l, mid, pos);
    } else {
        return query(rc(x), mid + 1, r, pos);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int ver, op, x, y;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    // 初始化
    build(root[0], 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> ver >> op;
        if (op == 1) {
            std::cin >> x >> y;
            modify(root[i], root[ver], 1, n, x, y);      
        } else{
            std::cin >> x;
            std::cout << query(root[ver], 1, n, x) << '\n';
            root[i] = root[ver];
        }
    }
    return 0;
}
```





### 主席树

```c++
/**
 * @brief 主席树
 *  可持续化线段树求区间第k小
 * 
 * 
 *  主席树：
 *      支持回退，访问之前版本的线段树，每次insert操作，增加插入查询路径上的logN个节点
 * 
 *  权值线段树：
 *      节点区间：序列的值域
 *      节点信息：值域内数出现的次数
 *  
 * 
 */

#define lc(x) tr[x].l
#define rc(x) tr[x].r

struct node {
    int l, r;
    int s; // 节点值域中的个数
} tr[N * 22];

int n, m, a[N];
int root[N], idx;
std::vector<int> v;

// 建空树，值域（l,r)
void build(int &x, int l, int r) {
    x = ++idx;
    if (l == r) {
        return;
    }
    int m = l + r >> 1;
    build(lc(x), l, m);
    build(rc(x), m + 1, r);
}

// 插入数，并新增logN节点
// x为前一版本的节点指针，y为当前版本的节点指针
void insert(int x, int &y, int l, int r, int v) {
    y = ++idx;
    // 复制前一个版本的当前节点
    tr[y] = tr[x];
    tr[y].s++;
    if (l == r) {
        return;
    }
    int m = l + r >> 1;
    if (v <= m) {
        insert(lc(x), lc(y), l, m, v);
    } else {
        insert(rc(x), rc(y), m + 1, r, v);
    }
}

// 区间第k小=【l，r】的信息-【1，l-1】的信息，
// 查询信息即为在第l~第r次插入中节点新增个数信息中的第k个
int query(int x, int y, int l, int r, int k) {
    if (l == r) {
        return l;
    }
    int m = l + r >> 1;
    // 差值即为新增个数
    int s = tr[lc(y)].s - tr[lc(x)].s;
    if (k <= s) {
        return query(lc(x), lc(y), l, m, k);
    } else {
        return query(rc(x), rc(y), m + 1, r, k - s);
    }
}

int get_id(int x) {
    return std::lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

int main(){
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        v.push_back(a[i]);
    }
    std::sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int vn = v.size(); //值域边界
    // 初始空树
    build(root[0], 1, vn);
    for(int i = 1; i <= n; i++) {
        insert(root[i - 1], root[i], 1, vn, get_id(a[i]));
    }
        
    while (m--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        int id = query(root[l - 1], root[r], 1, vn, k) - 1;
        std::cout << v[id] << '\n';
    }
    return 0;
}
```





### 平衡树

#### 普通平衡树Splay

```c++
/**
 * @brief 普通平衡树Splay
 * 
 *  1.插入 xx 数
 *  2.删除 xx 数(若有多个相同的数，因只删除一个)
 *  3.查询 xx 数的排名(排名定义为比当前数小的数的个数 +1 )
 *  4.查询排名为 xx 的数
 *  5.求 xx 的前驱(前驱定义为小于 xx，且最大的数)
 *  6.求 xx 的后继(后继定义为大于 xx，且最小的数)
 * 
 *  节点序号为0则为空
 */

struct node {
    int s[2], p, v, cnt, size;
    void init(int p1, int v1) {
        p = p1;
        v = v1;
        cnt = size = 1;
    }
} tr[N];

// 根节点序号，当前序号
int root, idx;

// 更新当前子树size
void pushup(int x) {
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + tr[x].cnt;
}

// x、y左旋或右旋
void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    // 更新x子节点
    tr[y].s[k] = tr[x].s[k ^ 1];
    tr[tr[x].s[k ^ 1]].p = y;
    // 更新y父节点
    tr[x].s[k ^ 1] = y;
    tr[y].p = x;
    // 更新x父节点
    tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    pushup(y);
    pushup(x);
}

/**
 * @brief 
 *  1. k>0时，把x旋转到k下面
 *  2. k=0时，把x旋转到根
 */
void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) {
            ((tr[y].s[0] == x) ^ (tr[z].s[0] == y)) ? rotate(x) : rotate(y);
        }
        rotate(x);
    }
    if (k == 0) {
        root = x;
    }
}

// 找到v所在节点，并把该节点转到根
void find(int v) {
    int x = root;
    while (tr[x].s[v > tr[x].v] && v != tr[x].v) {
        x = tr[x].s[v > tr[x].v];
    }
    splay(x, 0);
}

// 求v的前驱，返回其节点序号
int get_pre(int v) {
    find(v);
    int x = root;
    if (tr[x].v < v) {
        return x;
    }
    x = tr[x].s[0];
    while (tr[x].s[1]) {
        x = tr[x].s[1];
    }
    return x;
}

// 求v的后继，返回其节点序号
int get_suc(int v) {
    find(v);
    int x = root;
    if (tr[x].v > v) {
        return x;
    }
    x = tr[x].s[1];
    while (tr[x].s[0]) {
        x = tr[x].s[0];
    }
    return x;
}

// 删除v（若有多个相同的数，只删除一个）
void del(int v) {
    int pre = get_pre(v);
    int suc = get_suc(v);
    splay(pre, 0);
    splay(suc, pre);
    int del = tr[suc].s[0];
    if (tr[del].cnt > 1) {
        tr[del].cnt--;
        splay(del, 0);
    } else {
        tr[suc].s[0] = 0;
        splay(suc, 0);
    }
}

// 查询v数的排名
int get_rank(int v) {
    find(v);
    return tr[tr[root].s[0]].size;
}

// 查询排名为k的数值
int get_val(int k) {
    int x = root;
    while (true) {
        int y = tr[x].s[0];
        if (tr[y].size + tr[x].cnt < k) {
            k -= tr[y].size + tr[x].cnt;
            x = tr[x].s[1];
        } else {
            if (tr[y].size >= k) {
                x = tr[x].s[0];
            } else {
                break;
            }
        }
    }
    splay(x, 0);
    return tr[x].v;
}

// 插入v
void insert(int v) {
    int x = root, p = 0;
    while (x && tr[x].v != v) {
        p = x;
        x = tr[x].s[v > tr[x].v];
    }
    if (x) {
        tr[x].cnt++;
    } else {
        x = ++idx;
        tr[p].s[v > tr[p].v] = x;
        tr[x].init(p, v);
    }
    splay(x, 0);
}

int main() {
    // 哨兵
    insert(-1e9);
    insert(1e9);

    std::cin >> n;
    while (n--) {
        int op, x;
        std::cin >> op >> x;
        switch (op) {
            case 1:
                insert(x);
                break;
            case 2:
                del(x);
                break;
            case 3:
                std::cout << get_rank(x) << '\n';
                break;
            case 4:
                std::cout << get_val(x + 1) << '\n';
                break;
            case 5:
                std::cout << tr[get_pre(x)].v << '\n';
                break;
            case 6:
                std::cout << tr[get_suc(x)].v << '\n';
        }
    }
    return 0;
}
```



#### 文艺平衡树

```c++
/**
 * @brief 文艺平衡树
 * 您需要写一种数据结构（可参考题目标题），来维护一个有序数列。
 * 其中需要提供以下操作：翻转一个区间，例如原有序序列是 5 4 3 2 1，翻转区间是 [2,4]的话，结果是5 2 3 4 1。
 *
 * 输入格式
 * 第一行两个正整数 n,m，表示序列长度与操作个数。序列中第 i 项初始为 i。
 * 接下来 m 行，每行两个正整数 l,r，表示翻转的区间。
 *
 * 输出格式
 * 输出一行 n个正整数，表示原始序列经过 m次变换后的结果。
 */

struct node {
    int s[2], p, v, size, tag;
    void init(int p1, int v1) {
        p = p1;
        v = v1;
        size = 1;
    }
} tr[N];

// 根节点序号，当前序号
int root, idx;
int n, m;

// 更新当前子树size
void pushup(int x) {
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}

// x、y左旋或右旋
void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    // 更新x子节点
    tr[y].s[k] = tr[x].s[k ^ 1];
    tr[tr[x].s[k ^ 1]].p = y;
    // 更新y父节点
    tr[x].s[k ^ 1] = y;
    tr[y].p = x;
    // 更新x父节点
    tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    pushup(y);
    pushup(x);
}

/**
 * @brief 
 *  1. k>0时，把x旋转到k下面
 *  2. k=0时，把x旋转到根
 */
void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) {
            ((tr[y].s[0] == x) ^ (tr[z].s[0] == y)) ? rotate(x) : rotate(y);
        }
        rotate(x);
    }
    if (k == 0) {
        root = x;
    }
}

// 插入v
void insert(int v) {
    int x = root, p = 0;
    while (x && tr[x].v != v) {
        p = x;
        x = tr[x].s[v > tr[x].v];
    }
    x = ++idx;
    tr[p].s[v > tr[p].v] = x;
    tr[x].init(p, v);
    splay(x, 0);
}

// 下传（左右子节点交互（旋转操作））
void pushdown(int x) {
    if (tr[x].tag) {
        std::swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[0]].tag ^= 1;
        tr[tr[x].s[1]].tag ^= 1;
        tr[x].tag = 0;
    }
}

// 返回第k个节点编号
int get_k(int k) {
    int x = root;
    while (true) {
        pushdown(x);
        int y = tr[x].s[0];
        if (tr[y].size + 1 < k) {
            k -= tr[y].size + 1;
            x = tr[x].s[1];
        } else if (tr[y].size >= k) {
            x = y;
        } else {
            return x;
        }
    }
}

// 中序遍历输出
void output(int x) {
    pushdown(x);
    if (tr[x].s[0]) {
        output(tr[x].s[0]);
    }
    if (tr[x].v >= 1 && tr[x].v <= n) {
        std::cout << tr[x].v << ' ';
    }
    if (tr[x].s[1]) {
        output(tr[x].s[1]);
    }
}
int main() {
    // 哨兵
    insert(-1e9);
    insert(1e9);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        insert(i);
    }
    while (m--) {
        int l, r;
        std::cin >> l >> r;
        // [l-1, r+1] 
        l = get_k(l);
        r = get_k(r + 2);
        splay(l, 0);
        splay(r, l);
        tr[tr[r].s[0]].tag ^= 1;
    }
    output(root);
    return 0;
}
```



#### 普通平衡树 FHQ Treap

```c++
/**
 * @brief 普通平衡树 FHQ Treap
 * 使用分裂合并来维护树的平衡
 */

struct node {
    int l, r;
    int val;
    int key; //堆的随机值（小顶堆）
    int size;
} tr[N];

// 根节点序号，当前序号
int n, root, idx;

int new_node(int v) {
    tr[++idx].val = v;
    tr[idx].key = rand(); // 堆分配随机值
    tr[idx].size = 1;
    return idx;
}

// 更新当前子树size
void pushup(int p) {
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1;
}

// 分裂，根据v值分裂成两棵子树，x为左子树的根（val<=v），y为右子树的根（val>v）
void split(int p, int v, int &x, int &y) {
    if (!p) {
        x = y = 0;
        return;
    }
    if (tr[p].val <= v) {
        x = p;
        split(tr[x].r, v, tr[x].r, y);
    } else {
        y = p;
        split(tr[y].l, v, x, tr[y].l);
    }
    pushup(p);
}

// 合并，左右子树
int merge(int x, int y) {
    if (!x || !y) {
        return x + y;
    }
    if (tr[x].key < tr[y].key) {
        tr[x].r = merge(tr[x].r, y);
        pushup(x);
        return x;
    } else {
        tr[y].l = merge(x, tr[y].l);
        pushup(y);
        return y;
    }
}

// 插入v
void insert(int v) {
    int x, y, z;
    split(root, v, x, y);
    z = new_node(v);
    root = merge(merge(x, z), y);
}

// 删除
void del(int v) {
    int x, y, z;
    split(root, v, x, z);
    split(x, v - 1, x, y);
    y = merge(tr[y].l, tr[y].r);
    root = merge(merge(x, y), z);
}

// 返回第k个节点编号
int get_k(int p, int k) {
    if (k <= tr[tr[p].l].size) {
        return get_k(tr[p].l, k);
    }
    if (k == tr[tr[p].l].size + 1) {
        return p;
    }
    return get_k(tr[p].r, k - tr[tr[p].l].size - 1);
}

// 前驱
int get_pre(int v) {
    int x, y;
    split(root, v - 1, x, y);
    int p = get_k(x, tr[x].size);
    int res = tr[p].val;
    root = merge(x, y);
    return res;
}

// 后继
int get_suc(int v) {
    int x, y;
    split(root, v, x, y);
    int p = get_k(y, 1);
    int res = tr[p].val;
    root = merge(x, y);
    return res;
}

// 排名
int get_rank(int v) {
    int x, y;
    split(root, v - 1, x, y);
    int res = tr[x].size + 1;
    root = merge(x, y);
    return res;
}

// 数值
int get_val(int k) {
    int p = get_k(root, k);
    return tr[p].val;
}

void solve() {
}
```



#### 文艺平衡树 FHQ Treap

```c++
/**
 * @brief 文艺平衡树 FHQ Treap
 * 使用分裂合并来维护树的平衡
 */

struct node {
    int l, r;
    int val;
    int key; //堆的随机值（小顶堆）
    int size;
    int tag; // 交换懒标记
} tr[N];

// 根节点序号，当前序号
int n, m, root, idx;

int new_node(int v) {
    tr[++idx].val = v;
    tr[idx].key = rand(); // 堆分配随机值
    tr[idx].size = 1;
    return idx;
}

// 更新当前子树size
void pushup(int p) {
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1;
}

// 下传（更新懒标记、交换）
void pushdown(int p) {
    if (!tr[p].tag) {
        return;
    }
    std::swap(tr[p].l, tr[p].r);
    tr[tr[p].l].tag ^= 1;
    tr[tr[p].r].tag ^= 1;
    tr[p].tag = 0;
}

// 分裂，根据v值分裂成两棵子树，x为左子树的根（val<=v），y为右子树的根（val>v）
// 排名为左子树的大小
void split(int p, int k, int &x, int &y) {
    if (!p) {
        x = y = 0;
        return;
    }
    // 获取子节点之前先进行旋转操作
    pushdown(p);
    if (k > tr[tr[p].l].size) {
        k -= tr[tr[p].l].size + 1;
        x = p;
        split(tr[x].r, k, tr[x].r, y);
    } else {
        y = p;
        split(tr[y].l, k, x, tr[y].l);
    }
    pushup(p);
}

// 合并，左右子树
int merge(int x, int y) {
    if (!x || !y) {
        return x + y;
    }
    if (tr[x].key < tr[y].key) {
        pushdown(x);
        tr[x].r = merge(tr[x].r, y);
        pushup(x);
        return x;
    } else {
        pushdown(y);
        tr[y].l = merge(x, tr[y].l);
        pushup(y);
        return y;
    }
}

// 中序遍历输出
void output(int p) {
    if (!p) {
        return;
    }
    pushdown(p);
    output(tr[p].l);
    std::cout << tr[p].val << " ";
    output(tr[p].r);
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        root = merge(root, new_node(i));
    }
    while (m--) {
        int l, r, x, y, z;
        std::cin >> l >> r;
        split(root, r, x, z);
        split(x, l - 1, x, y);
        tr[y].tag ^= 1;
        root = merge(merge(x, y), z);
    }
    output(root);
    return 0;
}
```



#### 可持续化平衡树

```c++
/**
 * @brief 可持续化平衡树
 *      基于FHQ Treap的动态开点
 * 
 *  您需要写一种数据结构（可参考题目标题），来维护一个可重整数集合，其中需要提供以下操作（ 对于各个以往的历史版本 ）：
 *      1.插入 x
 *      2.删除 x（若有多个相同的数，应只删除一个，如果没有请忽略该操作）
 *      3.查询 x 的排名（排名定义为比当前数小的数的个数 +1
 *      4.查询排名为 x 的数
 *      5.求 x 的前驱（前驱定义为小于 x，且最大的数，如不存在输出 -2^31+1）
 *      6.求 x 的后继（后继定义为大于 x，且最小的数，如不存在输出 2^31-1）
 *  和原本平衡树不同的一点是，每一次的任何操作都是基于某一个历史版本，同时生成一个新的版本。（操作3, 4, 5, 6即保持原版本无变化）
 *  每个版本的编号即为操作的序号（版本0即为初始状态，空树）
 * 
 *  每行：v,opt,x
 */

struct node {
    int l, r;
    int val;
    int rnd;
    int size;
} tr[N * 50];

int root[N], idx;

void new_node(int &x, int v) {
    x = ++idx;
    tr[x].val = v;
    tr[x].rnd = std::rand();
    tr[x].size = 1;
}

void pushup(int p) {
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1;
}

/**
 * @brief 分裂时，记录分裂路径，对路径上的点进行动态开点
 * 
 * @param p 
 * @param v 
 * @param x 
 * @param y 
 */
void split(int p, int v, int &x, int &y) {
    if (!p) {
        x = y = 0;
        return;
    }
    if (tr[p].val <= v) {
        x = ++idx;
        tr[x] = tr[p];
        split(tr[x].r, v, tr[x].r, y);
        pushup(x);
    } else {
        y = ++idx;
        tr[y] = tr[p];
        split(tr[y].l, v, x, tr[y].l);
        pushup(y);
    }
}

int merge(int x, int y) {
    if (!x || !y) {
        return x + y;
    }
    if (tr[x].rnd < tr[y].rnd) {
        tr[x].r = merge(tr[x].r, y);
        pushup(x);
        return x;
    } else {
        tr[y].l = merge(x, tr[y].l);
        pushup(y);
        return y;
    }
}

void insert(int &root, int v) {
    int x, y, z;
    // 分裂路径动态开点(因为插入点仅影响分裂路径上的点的结构：x的右节点，y的左节点 上的点，而不影响前一版本上的点)
    split(root, v, x, y);
    new_node(z, v);
    root = merge(merge(x, z), y);
}

void del(int &root, int v) {
    int x, y, z;
    // 分裂路径动态开点
    split(root, v, x, z);
    split(x, v - 1, x, y);
    y = merge(tr[y].l, tr[y].r);
    root = merge(merge(x, y), z);
}

int get_rank(int &root, int v) {
    int x, y;
    split(root, v - 1, x, y);
    int ans = tr[x].size + 1;
    root = merge(x, y);
    return ans;
}

int get_val(int root, int v) {
  if(v == tr[tr[root].l].size+1)
    return tr[root].val;
  else if(v <= tr[tr[root].l].size)
    return get_val(tr[root].l, v);
  else 
    return get_val(tr[root].r, 
        v - tr[tr[root].l].size - 1);
}

int get_pre(int &root, int v){
  int x, y, s, ans;
  split(root, v - 1, x, y);
  if (!x)
    return -2147483647;
  s = tr[x].size;
  ans = get_val(x, s);
  root = merge(x, y);
  return ans;
}

int get_nxt(int &root, int v) {
  int x, y, ans;
  split(root, v, x, y);
  if (!y)
    return 2147483647;
  else 
    ans = get_val(y, 1);
  root = merge(x, y);
  return ans;
}

int main(){
    int n, ver, op, v;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> ver >> op >> v;
        root[i] = root[ver];
        if (op == 1) insert(root[i], v);
        else if(op == 2) del(root[i], v);
        else if(op == 3) std::cout << get_rank(root[i], v) << '\n';
        else if(op == 4) std::cout << get_val(root[i], v) << '\n';
        else if(op == 5) std::cout << get_pre(root[i], v) << '\n';
        else std::cout << get_nxt(root[i], v) << '\n';
    }
  return 0;
}
```



### 线段树套平衡树

```c++
/**
 * @brief 线段树套平衡树
 *  线段树的每个节点对应一个区间，在每个节点上构建一棵平衡树，维护该区间的序列
 * 
 *  您需要写一种数据结构（可参考题目标题），来维护一个有序数列，其中需要提供以下操作：
 *      1.查询 k 在区间内的排名
 *      2.查询区间内排名为 k 的值
 *      3.修改某一位值上的数值
 *      4.查询 k 在区间内的前驱（前驱定义为严格小于 x，且最大的数，若不存在输出 -2147483647）
 *      5.查询 k 在区间内的后继（后继定义为严格大于 x，且最小的数，若不存在输出 2147483647）
 */

#define ls(x) tr[x].s[0]
#define rs(x) tr[x].s[1]
#define lc u<<1
#define rc u<<1|1

struct node {
    int s[2], p;
    int v, siz;
    void init(int p1, int v1) {
        p = p1;
        v = v1;
        siz = 1;
    }
} tr[N * 40];

int n, m, w[N], idx;
int root[N * 4];

void pushup(int x) {
    tr[x].siz = tr[ls(x)].siz + tr[rs(x)].siz + 1;
}

void rotate(int x) {
    // x转到y的位置
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;

    tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;

    tr[y].s[k] = tr[x].s[k ^ 1];
    tr[tr[x].s[k ^ 1]].p = y;
    
    tr[x].s[k ^ 1] = y;
    tr[y].p = x;

    pushup(y);
    pushup(x);
}

void splay(int &root, int x, int k) {
    while (tr[x].p != k) {
        // x转到z的位置（转两次，若z等于k则转一次）
        int y = tr[x].p, z = tr[y].p;
        // 曲链转直链，直链再转曲链
        if (z != k) {
            if ((rs(y) == x) ^ (rs(z) == y)) {
                rotate(x);
            } else {
                rotate(y);
            }
        }
        rotate(x);
    }
    if (!k) {
        root = x;
    }
}

void insert(int &root, int v) {
    int u = root, p = 0;
    while (u) {
        p = u;
        u = tr[u].s[v > tr[u].v];
    }
    u = ++idx;
    tr[p].s[v > tr[p].v] = u;
    tr[u].init(p, v);
    splay(root, u, 0);
}

int get_rank(int root, int v) {
    int u = root, res = 0;
    while (u) {
        if (tr[u].v < v) {
            res += tr[ls(u)].siz + 1;
            u = rs(u);
        } else {
            u = ls(u);
        }
    }
    return res;
}

void del(int &root, int v) {
    int u = root;
    while (u) {
        if (tr[u].v == v) {
            break;
        }
        if (tr[u].v < v) {
            u = rs(u);
        } else {
            u = ls(u);
        }
    }
    splay(root, u, 0);
    int l = ls(u), r = rs(u);
    while (rs(l)) {
        l = rs(l);
    }
    while (ls(r)) {
        r = ls(r);
    }
    splay(root, l, 0);
    splay(root, r, l);
    ls(r) = 0;
    splay(root, r, 0);
}

int get_pre(int root, int v) {
    int u = root, res = -INF;
    while (u) {
        if (tr[u].v < v) {
            res = tr[u].v;
            u = rs(u);
        } else {
            u = ls(u);
        }
    }
    return res;
}

int get_nxt(int root, int v) {
    int u = root, res = INF;
    while (u) {
        if (tr[u].v > v) {
            res = tr[u].v;
            u = ls(u);
        } else {
            u = rs(u);
        }
    }
    return res;
}

// 树套树的构建(区间1~n)
void build(int u, int l, int r) {
    insert(root[u], -INF);
    insert(root[u], INF);
    for (int i = l; i <= r; i++) {
        insert(root[u], w[i]);
    }
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}

/**
 * @brief 求区间排名
 *  线段树负责裂开，平衡树负责查找
 * 
 * @param u 
 * @param l 固定区间
 * @param r 
 * @param x 查询区间
 * @param y 
 * @param v 
 * @return int 
 */
int query_rank(int u, int l, int r, int x, int y, int v) {
    if (x <= l && r <= y) {
        // 减去一个-INF
        return get_rank(root[u], v) - 1;
    }
    int mid = l + r >> 1, res = 0;
    if (x <= mid) {
        res += query_rank(lc, l, mid, x, y, v);
    }
    if (y > mid) {
        res += query_rank(rc, mid + 1, r, x, y, v);
    }
    return res;
}

/**
 * @brief 求区间排名为k的数值
 *  二分查找(枚举数值)
 * @param u 
 * @param x 
 * @param y 
 * @param k 
 * @return int 
 */
int query_val(int u, int x, int y, int k) {
    int l = 0, r = 1e8, ans;
    while (l <= r) {
        int mid = l + r >> 1;
        if (query_rank(1, 1, n, x, y, mid) + 1 <= k) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid -1;
        }
    }
    return ans;
}

/**
 * @brief 修改某一位置上的值，穿透每一层，在平衡树上删除数，再添加数
 * 
 * @param u 
 * @param l 
 * @param r 
 * @param pos 
 * @param v 
 */
void change(int u, int l, int r, int pos, int v) {
    del(root[u], w[pos]);
    insert(root[u], v);
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    if (pos <= mid) {
        change(lc, l, mid, pos, v);
    } else {
        change(rc, mid + 1, r, pos, v);
    }
}

/**
 * @brief 区间某值前驱
 * 
 * @param u 
 * @param l 
 * @param r 
 * @param x 
 * @param y 
 * @param v 
 * @return int 
 */
int query_pre(int u, int l, int r, int x, int y, int v) {
    if (x <= l && r <= y) {
        return get_pre(root[u], v);
    }
    int mid = l + r >> 1, res = -INF;
    if (x <= mid) {
        res = std::max(res, query_pre(lc, l, mid, x, y, v));
    }
    if (y > mid) {
        res = std::max(res, query_pre(rc, mid + 1, r, x, y, v));
    }
    return res;
}

/**
 * @brief 区间某值后继
 * 
 * @param u 
 * @param l 
 * @param r 
 * @param x 
 * @param y 
 * @param v 
 * @return int 
 */
int query_nxt(int u, int l, int r, int x, int y, int v) {
    if (x <= l && r <= y) {
        return get_nxt(root[u], v);
    }
    int mid = l + r >> 1, res = INF;
    if (x <= mid) {
        res = std::min(res, query_nxt(lc, l, mid, x, y, v));
    }
    if (y > mid) {
        res = std::min(res, query_nxt(rc, mid + 1, r, x, y, v));
    }
    return res;
}

int main(){
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        std::cin >> w[i];
    }
    build(1, 1, n);
    while (m--) {
        int op, x, y, v;
        std::cin >> op;
        if (op == 3) std::cin >> x >> v;
        else std::cin >> x >> y >> v;

        if (op == 1)
            std::cout << query_rank(1, 1, n, x, y, v) + 1 << '\n';
        if (op == 2) 
            std::cout << query_val(1,x,y,v) << '\n';;
        if (op == 3){
            change(1, 1, n, x, v);
            w[x] = v;
        }
        if (op == 4)
            std::cout << query_pre(1, 1, n, x, y, v) << '\n';
        if (op == 5)
            std::cout << query_nxt(1, 1, n, x, y, v) << '\n';
    }
    return 0;
}
```





### 动态树 LCT

```c++
/**
 * @brief 动态树 （LCT）
 * 给定 n 个点以及每个点的权值，要你处理接下来的 m 个操作。
 * 操作有四种，操作从 0 到 3 编号。点从 1 到 n 编号。
 *
 * 0 x y 代表询问从 x 到 y 的路径上的点的权值的 xor 和。保证 x 到 y 是联通的。
 * 1 x y 代表连接 x 到 y，若 x 到 y 已经联通则无需连接。
 * 2 x y 代表删除边 (x,y)，不保证边 (x,y) 存在。
 * 3 x y 代表将点 x 上的权值变成 y。
 * 
 * 实链剖分：把树拆分成若干条实链，用splay来维护实链，通过对实链的拆分和组合构造答案
 *  一个节点只能选一个儿子做实儿子，其他都是虚儿子
 *    1.实边：父节点与实儿子之间的双相边
 *    2.虚边：由虚儿子指向父节点的边（单向）
 *    3.实链：由实边构成的链。（每条实链的节点深度是严格递增的）
 * 
 * 辅助树：由若干splay构成，与原树等价（每条实链用一个splay维护，中序遍历按深度严格递增）
 *    1.区分树根和splay的根
 *    2.虚边从下面splay的根指向上面splay中的父亲（原树实链中根的父亲）
 *    3.实边和虚边是动态变化的
 * 
 * 
 * 一些辅助树构成了LCT，其维护的是整个森林
 * 
 * 
 * 辅助树中实链的中序遍历为原树中的实链从上至下遍历
 * 原树+辅助树
 * 单节点也算一个辅助树
 * 实链之间用虚边相连
 */

#define fa(x) tr[x].p
#define lc(x) tr[x].s[0]
#define rc(x) tr[x].s[1]
#define notroot(x) lc(fa(x))==x||rc(fa(x))==x

struct node{
  int s[2], p, v;
  int sum; // 仅记录实链上的子树和
  int tag; // 翻转懒标记
}tr[N];

int n, m;

// 更新实链上的和
void pushup(int x) {
    tr[x].sum = tr[lc(x)].sum ^ tr[x].v ^ tr[rc(x)].sum;
}

void pushdown(int x) {
    if (tr[x].tag) {
        std::swap(lc(x), rc(x));
        tr[lc(x)].tag ^= 1;
        tr[rc(x)].tag ^= 1;
        tr[x].tag = 0;
    }
}

// x与父节点旋转交换
void rotate(int x) {
    int y = fa(x), z = fa(y);
    int k = rc(y) == x;
    // 加notroot判断：维持旋转后两个splay之间的虚边性质
    // （x，z）连边放在上面：否则会破坏notroot(y)判断
    if (notroot(y)) {
        tr[z].s[rc(z) == y] = x;
    }
    fa(x) = z;

    tr[y].s[k] = tr[x].s[k ^ 1];
    fa(tr[x].s[k ^ 1]) = y;

    tr[x].s[k ^ 1] = y;
    fa(y) = x;

    pushup(y);
    pushup(x);
}

// 找到根，旋转x到根之间的路径
void pushall(int x) {
    if (notroot(x)) {
        pushall(fa(x));
    }
    pushdown(x);
}

// x旋转到根（在维持虚边性质的前提下）
// x仅在一棵小的splay树上旋转
void splay(int x) {
    pushall(x);
    while (notroot(x)) {
        int y = fa(x), z = fa(y);
        if(notroot(y)) {
           (rc(y) == x) ^ (rc(z) == y) ? rotate(x) : rotate(y);
        }
        rotate(x);
    }
}

// 打通从x到原树树根的路径，并把路径变成一条实链
/**
 *  1.把当前点转到当前splay的根
 *  2.把当前点的右儿子换成之前的节点（上一个splay的根）
 *  3.更新当前点的信息
 *  4.把当前点换成当前点的父亲，循环操作
 * 
 * 
 *  完成实链的拆分和重组，把不在路径上的点踢出去，把路径上虚边变实边
 * 
 *  access后的辅助树的实边的中序遍历正是原树上从树根到x的路径
 */
void access(int x) {
    for (int y = 0; x;) {
        splay(x);
        rc(x) = y;
        pushup(x);
        y = x;
        x = fa(x);
    }
}

/**
 * @brief 换根：把x变为原树树根，让x变成深度最小的根
 *  换根 = 通路 + 伸展 + 翻转
 */
void makeroot(int x) {
    access(x);
    splay(x);
    tr[x].tag ^= 1;
}

// split分离路径为算法的核心
/**
 * @brief 把从x到y的路径分离出来，把路径变为一条实链，根为y
 * 
 * @param x 
 * @param y 
 */
void split(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
}

int output(int x, int y) {
    split(x, y);
    return tr[y].sum;
}

/**
 * @brief 把树根找出来，并转到根（中序遍历第一个点）
 *  从x开始
 * 
 */
int findroot(int x) {
    access(x);
    splay(x);
    while (lc(x)) {
        pushdown(x);
        x = lc(x);
    }
    splay(x); // 防止卡链
    return x;
}

void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) {
        fa(x) = y;
    }
}

/**
 * @brief x和y在同一棵子树上，且y是x的后继节点
 * 
 * @param x 
 * @param y 
 */
void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x
        && fa(y) == x && !lc(y)) {
            rc(x) = fa(y) = 0;
            pushup(x);
        }
}

void change(int x, int y) {
    splay(x);
    tr[x].v = y;
    pushup(x);
}

int main(){
    std::cin >> n >> m;
    for(int i=1; i<=n; i++) {
        std::cin >> tr[i].v;
    }
    while(m--){
        int t, x, y;
        std::cin >> t >> x >> y;
        if(t == 0) std::cout << output(x, y) << '\n';
        else if(t == 1) link(x, y);
        else if(t == 2) cut(x, y);
        else change(x, y);
    }
    return 0;
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



#### 中国剩余定理

```c++
/**
 * @brief 中国剩余定理
 *  a 恒等于 ai(mod ni)，ni之间互质，求a的最小通解
 */

ll f_china(int *a, int *n, int len) {
    ll num = 1, ans = 0, x, y;
    for (int i = 0; i < len; i++) {
        num *= n[i];
    }
    for (int i = 0; i < len; i++) {
        ll m = num / n[i];
        exgcd(m, n[i], x, y);
        ans = (ans + ((ll)1) * a[i] * m * x % num) % num;
    }
    return (ans % num + num) % num;
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



### 字符串Hash

```c++
/**
 * @brief Hash
 * 二维hash（一维字符串hash，在区间hash值上再hash长度为m的区间）
 * 	：区间字符串的比较
 */

const ull b = 131, x = 173, mod = 17111354211743357;

ull hashs(std::string s) {
    ull res = 0;
    for (int i = 0; i < s.length(); i++) {
        res = (res * b % mod + (s[i] - 'a' + 1)) % mod;
    }
    return res;
}

ull hashs2(std::string s) {
    ull res = 131;
    for (int i = 0; i < s.length(); i++) {
        res = (res * x % mod+ (s[i] - 'a' + 1)) % mod;
    }
    return res;
}

for (int i = 1; i <= n; i++) {
    d_hash[i] = hashs(s[i]);
    d_hash2[i] = hashs2(s[i]);
}

ull sum = 0;
for (int j = 1; j <= m; j++) {
    sum = (sum * x % mod + d_hash[j]) % mod;
}
ull sum2 = 0;
for (int j = 1; j <= m; j++) {
    sum2 = (sum2 * b % mod + d_hash2[j]) % mod;
}

// s[1 ~ m]区间字符串的最终hash值
ull ans_hash = (sum + sum2) % mod;
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



### 可持续化01字典树

```c++
/**
 * @brief 可持续化01字典树
 *  给定一个非负整数序列 {a}，初始长度为n。
 *      有 m 个操作，有以下两种操作类型：
 *          1. A x：添加操作，表示在序列末尾添加一个数 x，序列的长度 n+1。
 *          2. Q l r x：询问操作，你需要找到一个位置 p，满足l≤p≤r，使得： a[p]⊕a[p+1]⊕...⊕a[N]⊕x 最大，输出最大是多少。
 * 
 * 
 *  区间和转为前缀和：
 *      s[i]=a[1]⊕a[2]⊕...⊕a[i]
 *      a[p]⊕a[p+1]⊕...⊕a[N]⊕x => s[p-1]  ⊕  s[n]⊕x
 *          p属于[l,r],则查询区间p-1属于[l-1,r-1],查询数为s[n]⊕x的异或最大值
 *      从r-1的历史版本中查询，并且边界不能超过l-1
 * 
 *  动态开点
 */

int n, m, s[N];
int ch[N * 25][2], ver[N * 25];
int root[N], idx, len = 23;

/**
 * @brief 插入新节点
 * 
 * @param x 当前版本的根节点
 * @param y 上一版本的根节点
 * @param i 版本号（区间下标）
 */
void insert(int x, int y, int i) {
    ver[x] = i;
    for (int k = len; k >= 0; k--) {
        int c = (s[i] >> k) & 1;
        ch[x][!c] = ch[y][!c];
        ch[x][c] = ++idx;
        x = ch[x][c];
        y = ch[y][c];
        ver[x] = i;
    }
}

/**
 * @brief 异或查询[l-1,r-1],最大结果值
 * 
 * @param x r-1版本的根
 * @param L l-1左边界版本
 * @param v 值s[n]^x
 * @return int 
 */
int query(int x, int L, int v) {
    int res = 0;
    for (int k = len; k >= 0; k--) {
        int c = (v >> k) & 1;
        // 即使到了0号节点也能继续
        if (ver[ch[x][!c]] >= L) {
            x = ch[x][!c];
            res += 1 << k;
        } else {
            x = ch[x][c];
        }
    }
    return res;
}

int main(){
    int l, r, x, ans;
    char op;
    std::cin >> n >> m;
    // 0号节点的版本为-1
    ver[0] = -1;
    // 空树的根节点标号为1（0号节点的左右儿子仍为0）
    root[0] = ++idx;
    insert(root[0], 0, 0);

    for(int i = 1; i <= n; i++) {
        std::cin >> x;
        root[i] = ++idx;
        s[i] = s[i-1] ^ x;
        insert(root[i], root[i - 1], i);
    }

    while(m--) {
        std::cin >> op;
        if (op == 'A') {
            std::cin >> x;
            root[++n] = ++idx;
            s[n] = s[n-1]^x;
            insert(root[n], root[n-1], n);
        }
        else {
            std::cin >> l >> r >> x;
            ans = query(root[r - 1], l - 1,s[n] ^ x);
            std::cout << ans << '\n';
        }
    }
    return 0;
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

### 多边形面积

```c++
/**
 * @brief 多边形面积（逆时针）
 *  S=1/2|x1y2-x2y1|
 */

struct node {
    double x, y;
} d[N];

double cross(node t1, node t2) {
    return (t1.x - d[0].x) * (t2.y - d[0].y) - (t2.x - d[0].x) * (t1.y - d[0].y);
}

void solve() {
    double ans = 0;
    for (int i = 1; i < n - 1; i++) {
        ans += cross(d[i], d[i + 1]);
    }
    ans /= 2;
}
```

