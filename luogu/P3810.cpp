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