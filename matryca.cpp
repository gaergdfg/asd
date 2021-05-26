#include <iostream>
#include <limits.h>
using namespace std;


string s;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> s;

	bool flag_multiple_chars = false;
	char first_char = '#';
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != '*') {
			if (first_char == '#') {
				first_char = s[i];
			} else if (first_char != s[i]) {
				flag_multiple_chars = true;
			}
		}
	}
	if (!flag_multiple_chars) {
		cout << "1\n";
		return 0;
	}

	int last_index = -1, min_dist = INT_MAX;
	char last_char = '#';
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != '*') {
			if (last_index != -1 && s[i] != last_char) {
				min_dist = min(min_dist, i - last_index - 1);
			}
			last_index = i;
			last_char = s[i];
		}
	}
	cout << s.size() - min_dist << "\n";
}
