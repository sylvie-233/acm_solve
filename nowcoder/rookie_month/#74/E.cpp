#include <iostream>

const int N = 1e5 + 5;

int a[N], h[N];

int main() {
    int t, n, m, k, b;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> m >> k >> b;
        for (int i = 0; i < n; i++) {
            std::cin >> h[i];
        }
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }

        m--;
        for (int i = 0; i < n; i++) {
            int d1 = (k - h[i]) / a[i] + 1;
            int m_bak = m;
            if (m_bak >= d1) {
                m_bak -= d1;
                int d2 = (k - b) / a[i] + 1;
                m_bak %= d2;
                std::cout << b + a[i] * m_bak << ' ';
            } else {
                std::cout << h[i] + a[i] * m << ' ';
            
            }
        }
        std::cout << '\n';
    }
    return 0;
}