#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int n, m, team[40003][53];
vector <long long> players;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	for (int t = 0; t < m; t++) {
		for (int i = 1, x; i <= n; i++) {
			cin >> x;
			team[x][t] = i <= n / 2 ? 0 : 1;
		}
	}

	for (int i = 1; i <= n; i++) {
		long long player = 0;

		for (int t = 0; t < m; t++) {
			player *= 2;
			player += team[i][t];
		}

		players.push_back(player);
	}

	sort(players.begin(), players.end());

	for (int i = 1; i < players.size(); i++) {
		if (players[i] == players[i - 1]) {
			cout << "NIE\n";
			return 0;
		}
	}
	cout << "TAK\n";
}
