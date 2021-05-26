#include <iostream>
#define MODULO 1000000000
using namespace std;


int n, arr[1003], ans[1003][1003][2];


int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		ans[i][i][0] = 0;
		ans[i][i][1] = 1;
	}

	for (int length = 2; length <= n; length++) {
		for (int i = 1, j = length - 1; i <= n - length + 1; i++) {
			j = i + length - 1;

			ans[i][j][0] = arr[i] < arr[j] ? ans[i + 1][j][1] : 0;
			ans[i][j][0] += arr[i] < arr[i + 1] ? ans[i + 1][j][0] : 0;
			ans[i][j][0] %= MODULO;

			ans[i][j][1] = arr[j] > arr[j - 1] ? ans[i][j - 1][1] : 0;
			ans[i][j][1] += arr[j] > arr[i] ? ans[i][j - 1][0] : 0;
			ans[i][j][1] %= MODULO;
		}
	}

	cout << (ans[1][n][0] + ans[1][n][1]) % MODULO;
}
