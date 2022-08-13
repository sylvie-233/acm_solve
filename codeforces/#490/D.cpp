#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <queue>

#define N 200005
typedef std::pair<int, int> P;
typedef long long ll;

std::set<int> st;
int a[N], cnt[N], cnt2[N];
std::queue<int> que[N];
std::vector<int> vec2;

int main() {
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        cnt[a[i] % m]++;
    }
    int d = n / m;
    for (int i = 0; i < m; i++) {
        if (cnt[i] < d) {
            cnt2[i] = d - cnt[i];
            st.insert(i);
            st.insert(i + m);
        } else if (cnt[i] > d) {
            vec2.push_back(i);
        }
    }
    ll ans = 0;
    for (int i = 0; i < vec2.size(); i++) {
        int t = vec2[i];
        int c = cnt[t] - d;
        while (c) {
            int v = *st.lower_bound(t) % m;
            int w = cnt2[v];
            if (c >= w) {
                for (int x = 0; x < w; x++) {
                    que[t].push(v);
                }
                st.erase(v);
                st.erase(v + m);
                cnt2[v] = 0;
                ans += (t < v ? ((ll)1) * (v - t) * w : ((ll)1) *  (v + m - t) * w);
                c -= w;
            } else {
                for (int x = 0; x < c; x++) {
                    que[t].push(v);
                }
                cnt2[v] = w - c;
                ans += (t < v ? ((ll)1) * (v - t) * c : ((ll)1) * (v + m - t) * c);
                c = 0;
                break;
            }
        }
        cnt[t] = d;
    }
    std::cout << ans << '\n';
    for (int i = 1; i <= n; i++) {
        if (cnt[a[i] % m]) {
            cnt[a[i] % m]--;
            std::cout << a[i] << ' ';
        } else {
            int t = a[i] % m;
            int v = que[t].front();
            que[t].pop();
            if (v > t) {
                std::cout << a[i] + (v - t) << ' ';
            } else {
                std::cout << a[i] + (m + v - t) << ' ';
            }
        }
    }
    std::cout << '\n';
    return 0;
}
