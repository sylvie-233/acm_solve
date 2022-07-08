#include <bits/stdc++.h>

using namespace std;

int main() {
	int t;
	char arr[8][8];
	cin >> t;
	while (t--) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				cin >> arr[i][j];
			}
		}

		for (int r = 1; r <= 6; r++) {
			bool flag = false;
			for (int c = 1; c <= 6; c++) {
				if (arr[r][c] == '#') {
					if (arr[r - 1][c - 1] == '#' 
						&& arr[r - 1][c + 1] == '#'
						&& arr[r + 1][c - 1] == '#'
						&& arr[r + 1][c + 1] == '#') {
						cout << r + 1 << " " << c + 1 << endl;
						flag = true;
						break;
					}
				}
			}
			if (flag) {
				break;
			}
		}
	}
	return 0;
}