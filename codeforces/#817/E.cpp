#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

typedef long long ll;

ll vec_sum[1005][1005];

int main() {
    int t, n, q;
    std::cin >> t;
    while (t--) {
        for (int i = 1; i <= 1000; i++) {
            for (int j = 1; j <= 1000; j++) {
                vec_sum[i][j] = 0;
            }
        }
        std::cin >> n >> q;
        for (int i = 1; i <= n; i++) {
            int h, w;
            std::cin >> h >> w;
            vec_sum[h][w] += 1ll * h * w;
        }
        for (int i = 1; i <= 1000; i++) {
            for (int j = 1; j <= 1000; j++) {
                vec_sum[i][j] += vec_sum[i][j - 1];
            }
        }
        while (q--) {
            int hs, ws, hb, wb;
            ll ans = 0;
            std::cin >> hs >> ws >> hb >> wb;
            for (int i = hs + 1; i <= hb -1; i++) {
                ans += vec_sum[i][wb - 1] - vec_sum[i][ws];
            }
            std::cout << ans << '\n';
        }
    }
    return 0;
}