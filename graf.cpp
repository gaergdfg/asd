#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;


struct component {
	int val, leader;
} components[1000003];


bool component_comp(component a, component b) {
	if (a.leader == b.leader)
		return a.val < b.val;
	return a.leader < b.leader;
}


int n, leader[1000003], group_size[1000003], min_leader[1000003];
stack<int> leaders;


int find(int x) {
	if (leader[x] != x)
		leader[x] = find(leader[x]);
	return leader[x];
}


void unite(int a, int b) {
	find(a);
	find(b);
	if (a > b)
		leader[b] = a,
		group_size[a] += group_size[b];
	else
		leader[a] = b,
		group_size[b] += group_size[a];
}


int main() {
	ios_base::sync_with_stdio(0);
	
	cin >> n;
	for (int i = 0, x; i < n; i++) {
		cin >> x;

		int curr_leader = x;
		int leader_to_add = x;
		leader[x] = x;
		group_size[x] = 1;

		while (!leaders.empty() && leaders.top() > x) {
			unite(leader_to_add, leaders.top());

			curr_leader = leaders.top();
			leader_to_add = max(leader_to_add, leaders.top());

			leaders.pop();
		}

		leaders.push(leader_to_add);
	}

	for(int i = 1; i <= n; i++) {
		find(i);
	}

	for(int i = 1; i <= n; i++) {
		min_leader[leader[i]] = min_leader[leader[i]] == 0 ? i : min(min_leader[leader[i]], i);
	}

	for(int i = 1; i <= n; i++) {
		components[i] = {i, min_leader[leader[i]]};
	}

	sort(components + 1, components + n + 1, component_comp);

	int unique_leaders = 1;
	for (int i = 2; i <= n; i++) {
		unique_leaders += leader[i] != leader[i - 1];
	}

	cout << unique_leaders << "\n";
	for (int i = 1; i <= n;) {
		cout << group_size[leader[i]] << " ";
		
		do {
			cout << components[i++].val << " ";
		} while (i <= n && leader[i] == leader[i - 1]);

		cout << "\n";
	}
}
