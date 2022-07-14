# ACM模板

>Author：Sylvie233
>
>Date：2022/07/13



[TOC]

<img src="./ACM.png" alt="ACM技能树" style="zoom: 33%;" />



## 基础工具



## 一、图论



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

```





## 三、数论



## 四、字符串



## 五、其它算法



## 六、基础算法



## 七、搜索



## 八、动态规划



## 九、组合数学



## 十、计算几何