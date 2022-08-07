#include <iostream>

char ch[55][55];

int main() {
    int t, n, m;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cin >> ch[i][j];
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = n - 1; j >= 0; j--) {
                if (ch[j][i] == '*') {
                    int k = j;
                    while (k < n - 1 && ch[k + 1][i] != '*' && ch[k + 1][i] != 'o') {
                        k++;
                    }
                    ch[j][i] = '.';
                    ch[k][i] = '*';
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cout << ch[i][j];
            }
            std::cout << '\n';
        }
    }
    return 0;
}