#include <bits/stdc++.h>

using namespace std;

set<int> s;

int main() {
	int arr[]{
		0 * 60 + 0,
		1 * 60 + 10,
		2 * 60 + 20,
		3 * 60 + 30,
		4 * 60 + 40,
		5 * 60 + 50,
		10 * 60 + 1,
		11 * 60 + 11,
		12 * 60 + 21,
		13 * 60 + 31,
		14 * 60 + 41,
		15 * 60 + 51,
		20 * 60 + 2,
		21 * 60 + 12,
		22 * 60 + 22,
		23 * 60 + 32
	};
	int t, h, m, x;
	scanf("%d", &t);
	while (t--) {
		scanf("%d:%d %d", &h, &m, &x);
		// printf("%d %d %d\n", h, m, x);
		int time = h * 60 + m;
		int cnt = 0;
        s.clear();
        s.insert(time);

		for(int i = 0; i < 2022; i++) {
            time = (time + x) % 1440;
            s.insert(time);
        }
        for (auto x : s) {
            for (auto y : arr) {
                if (x == y) {
                    cnt++;
                    break;
                }
            }
        }
		printf("%d\n", cnt);
	}
	return 0;
}
