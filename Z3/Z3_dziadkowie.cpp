#include <iostream>
#include <string>
#include <cmath>
//#include <set>
//#include <algorithm>

using namespace std;

/*
bool hasUniqueNumbers(string n) {
	set<char> unique_numbers;

	for (char c : n) {
		if (unique_numbers.count(c) > 0) {
			return false;
		}

		unique_numbers.insert(c);
	}

	return true;
}

int _X() {
	string n;

	for (int x = 100; x >= 10; x--) {
		n = to_string(pow(x, 2)) + to_string(pow(x, 3));

		if (n.length() == 10) {
			if (hasUniqueNumbers(n)) {
				return x;
			}
		}
	}
}
*/

/*
int row(int i, int *z) {
	return z[i] + z[i + 1] + z[i + 2];
}

int col(int i, int *z) {
	return z[i] + z[i + 3] + z[i + 6];
}

bool is(int* z) {
	if (row(0, z) != 12 || row(3, z) != 12 || row(6, z) != 12) {
		return false;
	}

	if (col(0, z) != 12 || col(1, z) != 12 || col(2, z) != 12) {
		return false;
	}

	return true;
}

int _i() {
	int z[9] = { 0,1,2,3,4,5,6,7,8 };
	int n = 1;

	do {
		if (is(z)) { 
			if (n++ == 9) { 
				return z[3]; 
			}
		}
	} while (next_permutation(z, z + 9));

	exit(-1);
}
*/

long long int granny(long long n) {
	return round(n - ((3 / 7) * n));
}

long long int papa(long long n) {
	return round((3 / 7) * n);
}

void init(int X, long long int n, int i) {
	if (i % X == 0) {
		cout << "AP 2023" << endl;
	}
	else {
		cout << granny(n) << endl;
	}
}

int main() {
	int t;
	//int X = _X();
	int X = 69;
	long long int n;
	cin >> t;

	for (int i = 1; i <= t; i++) {
		cin >> n;
		init(X, n, i);
	}

	return 0;
}