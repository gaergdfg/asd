#include <iostream>
using namespace std;


const int MOD = 1000000000, TREE_BASE = 1 << 15;
int n, k, arr[20003], res[20003][11], tree[2 * TREE_BASE];


inline void insert(int position, int value) {
	int pos = position + TREE_BASE;

	while (pos > 0) {
		tree[pos] += value;
		tree[pos] %= MOD;
		pos /= 2;
	}
}


inline int query(int position) {
	int pos = position + TREE_BASE;
	int res = 0;

	while (pos > 0) {
		if (pos % 2 == 0) {
			res += tree[pos + 1];
			res %= MOD;
		}
		pos /= 2;
	}

	return res;
}


void resetTree() {
	for (int i = 0; i < 2 * TREE_BASE; i++) {
		tree[i] = 0;
	}
}


int main() {
	ios_base::sync_with_stdio(0);
	
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		res[i][1] = 1;
	}

	for (int l = 2; l <= k; l++) {
		for (int i = 0; i < n; i++) {
			res[i][l] = query(arr[i]);
			insert(arr[i], res[i][l - 1]);
		}

		resetTree();
	}

	int answer = 0;
	for (int i = 0; i < n; i++) {
		answer += res[i][k];
		answer %= MOD;
	}

	cout << answer << "\n";
}
