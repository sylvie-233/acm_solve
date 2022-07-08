#include <bits/stdc++.h>
#include <iostream>
#include <set>

using namespace std;

int main() {
	int t, n, x;
	set<int> s;
	cin >> t;
	while (t--) {
		cin >> n;
		s.clear();
		for (int i = 0; i < n; i++) {
			cin >> x;
			s.insert(x);
		}
		int len = s.size();
		if ((n - len) % 2 != 0) {
			len--;
		} 
		cout << len << endl;
	}
	return 0;
}