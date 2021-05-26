#include <iostream>
#include <set>
using namespace std;


int n, m;
multiset<int> left_set, right_set;


int main() {
	ios_base::sync_with_stdio(0);

	cin >> n >> m;

	left_set.insert(0);
	right_set.insert(n + 1);

	for (int i = 0; i < m; i++) {
		char c;
		int a, b;
		cin >> c >> a >> b;

		if (a == 1) {
			if (c == '+') {
				left_set.insert(b);
			} else {
				left_set.erase(b);
			}
		} else {
			if (c == '+') {
				right_set.insert(a);
			} else {
				right_set.erase(a);
			}
		}

		auto it = left_set.end();
		it--;
		a = *it;
		it = right_set.begin();
		b = *it;

		cout << max(b - a - 1, 0) << "\n";
	}
}
