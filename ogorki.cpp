#include <iostream>

using namespace std;

#define INF 2020202020


int n, m, k;
int tree_base_n, tree_base_m;
int **tree_inner_max, **tree_inner_min;
int inner_index = -1, outer_index = -1;
int inner_left = -1, inner_right = -1;
bool query_max = false;


void fastscan(int &number) {
    bool negative = false;
    register int c;

    number = 0;

    c = getchar();
    if (c == '-') {
        negative = true;
        c = getchar();
    }

    for (; (c > 47 && c < 58); c = getchar())
        number = number * 10 + c - 48;

    if (negative)
        number *= -1;
}


int find_tree_base(int x) {
	int tree_base = 2;
	bool greater = tree_base >= x;

	while (!greater) {
		tree_base *= 2;
		greater = tree_base >= x;
	}

	return tree_base;
}


inline void insert_inner(int curr, int value) {
    if (curr == 0) {
        return;
    }

    tree_inner_min[outer_index][curr] = min(tree_inner_min[outer_index][curr], value);
    tree_inner_max[outer_index][curr] = max(tree_inner_max[outer_index][curr], value);

    insert_inner(curr / 2, value);
}


inline void insert_outer(int curr, int value) {
    if (curr == 0) {
        return;
    }

    outer_index = curr;
    insert_inner(tree_base_m + inner_index - 1, value);
    outer_index = -1;

    insert_outer(curr / 2, value);
}


void insert(int y, int x, int value) {
    inner_index = x;
    insert_outer(tree_base_n + y - 1, value);
    inner_index = -1;
}


inline int query_inner(int curr, int left, int right, int low, int high) {
    if (left > high || right < low) {
        if (query_max) {
            return 0;
        } else {
            return INF;
        }
    }

    if (left == low && right == high) {
        if (query_max) {
            return tree_inner_max[outer_index][curr];
        } else {
            return tree_inner_min[outer_index][curr];
        }
    } else {
        int mid = (low + high) / 2;
        int left_side = query_inner(2 * curr, left, min(mid, right), low, mid);
        int right_side = query_inner(2 * curr + 1, max(left, mid + 1), right, mid + 1, high);

        if (query_max) {
            return max(left_side, right_side);
        } else {
            return min(left_side, right_side);
        }
    }
}


inline int query_outer(int curr, int left, int right, int low, int high) {
    if (left > high || right < low) {
        if (query_max) {
            return 0;
        } else {
            return INF;
        }
    }

    if (left == low && right == high) {
        outer_index = curr;
        int result = query_inner(1, inner_left, inner_right, 1, tree_base_m);
        outer_index = -1;
        return result;
    } else {
        int mid = (low + high) / 2;
        int left_side = query_outer(2 * curr, left, min(mid, right), low, mid);
        int right_side = query_outer(2 * curr + 1, max(left, mid + 1), right, mid + 1, high);

        if (query_max) {
            return max(left_side, right_side);
        } else {
            return min(left_side, right_side);
        }
    }
}


int query(int a, int b, int c, int d) {
    inner_left = b;
    inner_right = d;

    query_max = true;
    int result = query_outer(1, a, c, 1, tree_base_n);
    query_max = false;

    result -= query_outer(1, a, c, 1, tree_base_n);

    inner_left = -1;
    inner_right = -1;

    return result;
}


int main() {
	fastscan(n);
	fastscan(m);
	fastscan(k);

	tree_base_n = find_tree_base(n);
	tree_base_m = find_tree_base(m);

	tree_inner_min = new int*[2 * tree_base_n];
	tree_inner_max = new int*[2 * tree_base_n];

	for (int i = 0; i < 2 * tree_base_n; i++) {
	    tree_inner_min[i] = new int[2 * tree_base_m];
        tree_inner_max[i] = new int[2 * tree_base_m];
	}

	for (int y = 0; y < 2 * tree_base_n; y++) {
	    for (int x = 0; x < 2 * tree_base_m; x++) {
	       tree_inner_min[y][x] = INF;
	       tree_inner_max[y][x] = 0;
	    }
	}

	for (int y = 1; y <= n; y++) {
		for (int x = 1, value; x <= m; x++) {
            fastscan(value);
			insert(y, x, value);
		}
	}

	 for (int i = 0, a, b, c, d; i < k; i++) {
	 	fastscan(a);
	 	fastscan(b);
	 	fastscan(c);
	 	fastscan(d);
	 	cout << query(a + 1, b + 1, c + 1, d + 1) << "\n";
	 }
}