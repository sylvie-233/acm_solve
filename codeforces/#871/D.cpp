#include <iostream>
#include <string>
#include <algorithm>

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    int t, n, m;
    std::string YES = "YES\n", NO = "NO\n";
    std::cin >> t;
    while (t--) {
        std::cin >> n >> m;
        if (n == m) {
            std::cout << YES;
            continue;
        } else if (n < m) {
            std::cout << NO;
            continue;
        } else {
            int t_gcd = gcd (n, m);
            n /= t_gcd;
            m /= t_gcd;
            int t_n = 0, t_m = 0;
            while (n % 3 == 0) {
                n /= 3;
                t_n++;
            }
            if (n != 1) {
                std::cout << NO;
                continue;
            }
            while (m % 3 == 0) {
                m /= 3;
                t_m++;
            }
            while (m % 2 == 0) {
                m /= 2;
                t_m++;
            }
            if (m != 1) {
                std::cout << NO;
                continue;
            }
            if (t_n >= t_m) {
                std::cout << YES;
                continue;
            } else {
                std::cout << NO;
                continue;
            }

        }
    }
    return 0;
}