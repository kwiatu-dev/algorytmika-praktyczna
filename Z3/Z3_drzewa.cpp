#include <iostream>

using namespace std;

int K, V, L;

int flags_V, flags_L;
int* answers;
bool* flags;

void print(bool b) {
	cout << b << " ";
}

int root(int i) {
	return i / (V / 3);
}

int vertices(int k) {
	return (pow(3, k) - 1) / 2;
}

int parent(int i) {
	return (i - 1) / 3;
}

int left(int i) {
	return 3 * i + 1;
}

int mid(int i) {
	return 3 * i + 2;
}

int right(int i) {
	return 3 * i + 3;
}

int level(int i) {
	return floor(log((i * 3) + 4) / log(3)) - 1;
}

int leafs(int k) {
	return pow(3, k - 1);
}

int flag_node(int ask) {
	return flags_V - flags_L + ask / 3;
}

bool lookup(int i) {
	if (i < 1) { return flags[i]; }

	int p = parent(i);
	bool flag = flags[p];
	flags[p] = !flags[p];

	if (answers[p]++ == 2) {
		return lookup(p);
	}

	return flag;
}

bool flag(int ask) {
	int i = flag_node(ask - 1);
	bool flag = flags[i];
	flags[i] = !flags[i];

	if (++answers[i] == 3) {
		return lookup(i);
	}

	return flag;
}

void set_variables() {
	V = vertices(K);
	L = leafs(K);
	flags_V = vertices(K - 1);
	flags_L = leafs(K - 1);
	flags = new bool[flags_V] {0};
	answers = new int[flags_V] {0};
}

void answer(int ask) {
	print(flag(ask));
}

void init() {
	set_variables();
	int ask;

	for (int i = 0; i < L; i++) {
		cin >> ask;
		answer(ask);
	}

	cout << endl;

	delete[] flags, answers;
}

int main() {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		cin >> K;
		init();
	}

	return 0;
}