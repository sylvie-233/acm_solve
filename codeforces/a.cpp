#include <bits/stdc++.h>

using namespace std;

int main() {
	int test = 0;
	int a, b, c, d;
	cin >> test;
	while (test--) {
		cin >> a >> b >> c >> d;
		int index = 0;
		if (b > a) {
			index++;
		}
		if (c > a) {
			index++;
		}
		if (d > a) {
			index++;
		}
		cout << index << endl;
	}
	return 0;
}