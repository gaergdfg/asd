#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;


const int INF = 2020202020;

int n, best_dist[200003];

struct island {
	int nr, x, y;
} islands[200003];

vector <int> neighbor[200003];

priority_queue <pair <int, int>> paths;


int dist(int a, int b) {
	return min(abs(islands[a].x - islands[b].x), abs(islands[a].y - islands[b].y));
}


bool sortByX(island a, island b) {
	return a.x < b.x;
}


bool sortByY(island a, island b) {
	return a.y < b.y;
}


bool sortByNr(island a, island b) {
	return a.nr < b.nr;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 1, a, b; i <= n; i++) {
		cin >> a >> b;
		islands[i] = {i, a, b};
		best_dist[i] = INF;
	}

	sort(islands + 1, islands + n + 1, sortByX);
	for (int i = 1; i < n; i++) {
		neighbor[islands[i].nr].push_back(islands[i + 1].nr);
		neighbor[islands[i + 1].nr].push_back(islands[i].nr);
	}

	sort(islands + 1, islands + n + 1, sortByY);
	for (int i = 1; i < n; i++) {
		neighbor[islands[i].nr].push_back(islands[i + 1].nr);
		neighbor[islands[i + 1].nr].push_back(islands[i].nr);
	}

	sort(islands + 1, islands + n + 1, sortByNr);

	best_dist[1] = 0;
	paths.push({0, 1});
	while (!paths.empty()) {
		int curr = paths.top().second;
		paths.pop();

		for (auto node : neighbor[curr]) {
			int distance = dist(curr, node);
			if (best_dist[curr] + distance < best_dist[node]) {
				best_dist[node] = best_dist[curr] + distance;
				paths.push({-best_dist[node], node});
			}
		}
	}

	cout << best_dist[n] << "\n";
}