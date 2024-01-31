#include <iostream>
#include <unordered_map>
#include <vector>
#define GRAPH unordered_map<int, vector<int>>

using namespace std;

int n, m;
int member;
char sign;
bool cycle = false;
GRAPH g;

bool DFS(vector<bool>& visited, vector<bool>& stack, int at) {
	visited[at] = true;
	stack[at] = true;

	for (int next : g[at]) {
		if (!visited[next] && DFS(visited, stack, next)) {
			return true;
		}
		else if (stack[next]) {
			return true;
		}
	}

	stack[at] = false;
	return false;
}

bool is_cycle() {
	vector<bool> visited(n * 2 + 1, false);
	vector<bool> stack(n * 2 + 1, false);

	for (int i = 1; i <= n; i++) {
		if (!visited[i] && DFS(visited, stack, i)) {
			return true;
		}
	}

	return false;
}

int index(char sign, int member) {
	if (sign == '+') {
		return member;
	}
	else {
		return member + n;
	}
}

int reverse(int index) {
	if (index > n) {
		return index - n;
	}
	else {
		return index + n;
	}
}

void from_to(int from, int to) {
	g[from].push_back(to);
}

void reset() {
	cycle = false;
	g.clear();
}

void test() {
	int from, to;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		cin >> sign >> member;
		from = index(sign, member);

		cin >> sign >> member;
		to = index(sign, member);

		from_to(from, reverse(to));
		from_to(to, reverse(from));
	}

	if (is_cycle()) {
		cout << "NIE" << endl;
	}
	else {
		cout << "TAK" << endl;
	}

	reset();
}

int main() {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		test();
	}

	return 0;
}