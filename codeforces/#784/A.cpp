#include <iostream>
#include <string>

int main() {
    int t, n;
    std::string s;
    std::cin >> t;
    while (t--) {
        std::cin >> n;

        if (n >= 1900) {
            s = "Division 1";
        } else if (n >= 1600) {
            s = "Division 2";
        } else if (n >= 1400) {
            s = "Division 3";
        } else {
            s = "Division 4";
        }
        std::cout << s << '\n';
    }
    return 0;
}