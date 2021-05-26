#include <iostream>
#include <vector>
using namespace std;


int n, arr[1000003], leader[1000003], group_size[1000003];
vector<int> neighbor[1000003];


void dfs(int curr, int boss) {
	leader[curr] = boss;
	group_size[boss]++;

	for (auto node : neighbor[curr]) {
		if (!leader[node])
			dfs(node, boss);
	}
}


int main() {
	ios_base::sync_with_stdio(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}

	for (int a = 1; a <= n; a++) {
		for (int b = a + 1; b <= n; b++) {
			if (arr[a] > arr[b])
				neighbor[a].push_back(b);
				neighbor[b].push_back(a);
		}
	}

	int unique_leaders = 0;
	for (int i = 1; i <= n; i++) {
		if (!leader[i])
			unique_leaders++,
			dfs(i, i);
	}

	cout << unique_leaders << "\n";
	for (int i = 1; i <= n; i++) {
		if (group_size[i]) {
			cout << group_size[i] << " ";
			for (int j = 1; j <= n; j++) {
				if (leader[j] == i)
					cout << j << " ";
			}
			cout << "\n";
		}
	}
}
