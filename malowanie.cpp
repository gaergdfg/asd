#include <iostream>
#include <algorithm>
using namespace std;


int n, q, arr[1 << 22];


inline void set(int curr, int a, int b, int low, int high, char value) {
	if (a > high || b < low) {
		return;
	}

	if (arr[curr] == high - low + 1) {
		arr[2 * curr] = arr[2 * curr + 1] = (high - low + 1) / 2;
	} else if (arr[curr] == 0) {
		arr[2 * curr] = arr[2 * curr + 1] = 0;
	}

	if (a == low && b == high) {
		if (value == 'B') {
			arr[curr] = high - low + 1;
		} else {
			arr[curr] = 0;
		}
	} else {
		int mid = (low + high) / 2;
		set(2 * curr, a, min(mid, b), low, mid, value);
		set(2 * curr + 1, max(a, mid + 1), b, mid + 1, high, value);
		
		arr[curr] = arr[2 * curr] + arr[2 * curr + 1];
	}
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> q;
	while (q--) {
		int a, b;
		char value;
		cin >> a >> b >> value;

		set(1, a, b, 1, 1 << 20, value);

		cout << arr[1] << "\n";
	}
}
