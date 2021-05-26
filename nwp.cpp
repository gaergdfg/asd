#include <iostream>
#include <algorithm>
using namespace std;


const int INF = 2020202020;
int n, m, c, a[1003], b[1003], result[1003][1003][23];


int main() {
	ios_base::sync_with_stdio(0);

	cin >> n >> m >> c;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> b[i];
	}

	for (int i = 0; i <= max(n, m); i++) {
		result[0][i][1] = result[i][0][1] = INF;
	}
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= m; y++) {
			result[x][y][1] = min(result[x - 1][y][1], result[x][y - 1][1]);
			if (a[x] == b[y]) {
				result[x][y][1] = min(result[x][y][1], a[x]);
			}
		}
	}
	if (result[n][m][1] == INF) {
		cout << "0\n";
		return 0;
	}

	for (int k = 2; k <= 20; k++) {
		for (int x = 0; x <= n; x++) {
			for (int y = 0; y <= m; y++) {
				if (y < k || x < k) {
					result[x][y][k] = INF;
				}
			}
		}

		for (int x = k; x <= n; x++) {
			for (int y = k; y <= m; y++) {
				result[x][y][k] = min(result[x - 1][y][k], result[x][y - 1][k]);
				if (a[x] == b[y] && a[x] + c >= result[x - 1][y - 1][k - 1]) {
					result[x][y][k] = min(result[x][y][k], max(a[x], result[x - 1][y - 1][k - 1]));
				}
			}
		}

		if (result[n][m][k] == INF) {
			cout << k - 1 << "\n";
			return 0;
		}
	}

	cout << "20\n";
}
