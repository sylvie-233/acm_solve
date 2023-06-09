#include <iostream>
#include <set>

int main() {
    int t, n, m;
    std::cin >> t;
    int a;
    std::set<int> st;
    while (t--) {
        std::cin >> n >> m;
        st.clear();
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cin >> a;
                if (!st.count(a)) {
                    st.insert(a);
                    cnt++;
                }
            }
        }
        std::cout << cnt << '\n';
    }
    return 0;
}