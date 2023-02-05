#include <iostream>
#include <vector>
#include <utility>

typedef std::pair<int, int> P;

char ch[55][55];
P tmp[15];
int pos;

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
        bool flag = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (ch[i][j] == '*') {
                    pos = 0;
                    if (j > 0) {
                        if (i > 0 && ch[i - 1][j - 1] == '*') {
                            tmp[pos++] = P(i - 1, j - 1);
                        }
                        if (ch[i][j - 1] == '*') {
                            tmp[pos++] = P(i, j - 1);
                        }
                        if (i < n - 1 && ch[i + 1][j - 1] == '*') {
                            tmp[pos++] = P(i + 1, j - 1);
                        }
                    }

                    if (i > 0) {
                        if (ch[i - 1][j] == '*') {
                            tmp[pos++] = P(i - 1, j);
                        }
                    }
                    if (i < n - 1) {
                        if (ch[i + 1][j] == '*') {
                            tmp[pos++] = P(i + 1, j);
                        }
                    }

                    if (j < m - 1) {
                        if (i > 0 && ch[i - 1][j + 1] == '*') {
                            tmp[pos++] = P(i - 1, j + 1);
                        }
                        if (ch[i][j + 1] == '*') {
                            tmp[pos++] = P(i, j + 1);
                        }
                        if (i < n - 1 && ch[i + 1][j + 1] == '*') {
                            tmp[pos++] = P(i + 1, j + 1);
                        }
                    }

                    if (pos != 2) {
                        flag = false;
                        break;
                    }
                    if (!(
                            ((tmp[0].first <= i && tmp[1].first <= i) ||
                            (tmp[0].first >= i && tmp[1].first >= i)) 
                        && 
                            ((tmp[0].second <= j && tmp[1].second <= j) ||
                            (tmp[0].second >= j && tmp[1].second >= j)) 
                        )) {
                            flag = false;
                            break;
                        }
                }
            }
            if (!flag) {
                break;
            }
        }
        std::cout << (flag ? "YES\n" : "NO\n");
    }
    return 0;
}