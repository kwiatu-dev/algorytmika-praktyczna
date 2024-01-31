#include <iostream>

using namespace std;

int n, kl, ll, sk = 0, sl = 0, s = 0;
int* k;
int* l;

int N() {
	cin >> n;
	if (n == 0) { exit(0); }

	return n;
}

int fir() {
	n = N();
	k = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> k[i];
	}

	return n;
}

int sec() {
	n = N();
	l = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> l[i];
	}

	return n;
}

void add(int connector) {
	if (sk > sl) {
		s += (sk + connector);
	}
	else {
		s += (sl + connector);
	}

	sk = 0; sl = 0;
}

void rest(int ki, int li) {
	for (; ki < kl; ki++) {
		sk += k[ki];
	}

	for (; li < ll; li++) {
		sl += l[li];
	}

	add(0);
}

void helix(int m, int n){ 
	int ki = 0, li = 0;
	kl = n; ll = m;

	for (; ki < kl && li < ll; ) {
		if (k[ki] < l[li]) {
			sk += k[ki++];
		}
		else if (l[li] < k[ki]) {
			sl += l[li++];
		}
		else {
			add(k[ki]);
			ki++; li++;
		}
	}

	rest(ki, li);
	cout << s << endl;
}

void reset() {
	sk = 0;
	sl = 0;
	s = 0;
	delete[] k, l;
}

void init() {
	while (true) {
		helix(sec(), fir());
		reset();
	}
}

int main() {
	init();

	return 0;
}