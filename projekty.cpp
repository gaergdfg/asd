#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


class Compare {
	public:
		bool operator() (int a, int b);
};


int n, m, k, cost[100003], blocking[100003], answer = -1;
vector <int> neighbor[100003], unlockable[100003];
priority_queue <int, vector <int>, Compare> projects;


bool Compare::operator() (int a, int b) {
	return cost[a] > cost[b];
}


int main() {
	ios_base::sync_with_stdio(0);

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		cin >> cost[i];
	}
	for (int i = 0, a, b; i < m; i++) {
		cin >> a >> b;
		blocking[a]++;
		unlockable[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		if (!blocking[i]) {
			projects.push(i);
		}
	}

	while (k--) {
		int min_project = projects.top();
		projects.pop();

		answer = max(answer, cost[min_project]);

		for (auto i : unlockable[min_project]) {
			blocking[i]--;
			if (!blocking[i]) {
				projects.push(i);
			}
		}
	}

	cout << answer << "\n";
}
