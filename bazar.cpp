#include <iostream>
using namespace std;


int n, m;
long long price[1000003], sum[1000003], bestLeft[1000003][2], bestRight[1000003][2];


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> price[i];
	}

	bestRight[n + 1][0] = bestRight[n + 1][1] = -1;
	for (int i = n; i > 0; i--) {
		sum[i] = price[i] + sum[i + 1];
		bestRight[i][0] = price[i] % 2 ? bestRight[i + 1][0] : price[i];
		bestRight[i][1] = price[i] % 2 ? price[i] : bestRight[i + 1][1];
	}

	bestLeft[1][0] = bestLeft[1][1] = -1;
	for (int i = 1; i < n; i++) {
		bestLeft[i + 1][0] = price[i] % 2 ? bestLeft[i][0] : price[i];
		bestLeft[i + 1][1] = price[i] % 2 ? price[i] : bestLeft[i][1];
	}
	
	cin >> m;
	while(m--) {
		int j, k;
		cin >> k;
		j = n - k + 1;

		if (sum[j] % 2) {
			cout << sum[j];
		} else {
			if (
				bestLeft[j][0] + bestRight[j][1] < max(bestLeft[j][0], bestRight[j][1]) &&
				bestLeft[j][1] + bestRight[j][0] < max(bestLeft[j][1], bestRight[j][0])
			) {
				cout << -1;
			} else if (
				bestLeft[j][0] + bestRight[j][1] > max(bestLeft[j][0], bestRight[j][1]) &&
				bestLeft[j][1] + bestRight[j][0] < max(bestLeft[j][1], bestRight[j][0])
			) {
				cout << sum[j] - (bestRight[j][1] - bestLeft[j][0]);
			} else if (
				bestLeft[j][0] + bestRight[j][1] < max(bestLeft[j][0], bestRight[j][1]) &&
				bestLeft[j][1] + bestRight[j][0] > max(bestLeft[j][1], bestRight[j][0])
			) {
				cout << sum[j] - (bestRight[j][0] - bestLeft[j][1]);
			} else {
				cout << sum[j] - min(bestRight[j][0] - bestLeft[j][1], bestRight[j][1] - bestLeft[j][0]);
			}
		}
		cout << "\n";
	}
}
