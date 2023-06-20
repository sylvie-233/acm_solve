#include <iostream>
#include <algorithm>

const int N = 1e5 + 5;

int n, m, l[N], r[N], arr[N], bit[N];

int ask(int i) {
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

bool check() {
    bool flag = false;
    for (int i = 1; i <= m; i++) {
        int cnt_1 = ask(r[i]) - ask(l[i] - 1);
        int cnt_0 = r[i] - l[i] + 1 - cnt_1;
        if (cnt_1 > cnt_0) {
            flag = true;
            break;
        }
    }
    return flag;
}

int main() {
    int t, q;
    std::cin >> t;
    while (t--) {
        for (int i = 0; i <= n; i++) bit[i] = 0;
        std::cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            std::cin >> l[i] >> r[i];
        }
        std::cin >> q;
        for (int i = 1; i <= q; i++) {
            std::cin >> arr[i];
            add(arr[i], 1);
        }
        bool flag = check();
        if (!flag) {
            std::cout << -1 << '\n';
            continue;
        } else {
            for (int i = 1; i <= q; i++) add(arr[i], -1);
            int last_pos = 0, l_pos = 0, r_pos = q + 1;
            while (l_pos + 1 < r_pos) {
                int mid_pos = (l_pos + r_pos) >> 1;
                if (mid_pos > last_pos) {
                    for (int i = last_pos + 1; i <= mid_pos; i++) add(arr[i], 1);
                } else {
                    for (int i = mid_pos + 1; i <= last_pos; i++) add(arr[i], -1);
                }
                if (check()) r_pos = mid_pos;
                else l_pos = mid_pos;
                last_pos = mid_pos;
            }
            std::cout << r_pos << '\n';
        }
    }
    return 0;
}