#include <iostream>
#include <vector>
#include <cmath>
#include <string> 

using namespace std;

int factorial(int n) {
	if (n == 2) {
		return 2;
	}

	return factorial(n - 1) * n;
}

vector<float> solveEquations(float a1, float b1, float c1, float a2, float b2, float c2) {
	float det = a1 * b2 - a2 * b1;

	if (det == 0) {
		return vector<float>();
	}

	float a = (c1 * b2 - c2 * b1) / det;
	float b = (a1 * c2 - a2 * c1) / det;
	vector<float> ab = { a, b };

	return ab;
}

bool isInt(float n) {
	return floor(n) == n;
}

bool isIntDigit(float n) {
	if (n >= 0 && n <= 9) {
		return isInt(n);
	}

	return false;
}

bool isNum(char c) {
	if ('0' <= c && c <= '9') {
		return true;
	}
	
	return false;
}

int ctoi(char c) {
	return  c - '0';
}

int _S9(string s) {
	int sum = 0;

	for (char c : s) {
		if (isNum(c)) {
			sum += ctoi(c);
		}
	}

	return sum;
}

int _S11(string s) {
	int p = 0, np = 0;
	char c;

	for (int i = 0; i < s.length(); i++) {
		c = s[i];

		if (isNum(c)) {
			if (i % 2 == 0) {
				np += ctoi(c);
			}
			else {
				p += ctoi(c);
			}
		}
	}

	return p - np;
}

vector<float> _ab(string s) {
	int S9 = _S9(s), S11 = _S11(s);
	int S9mod9 = S9 % 9, S11mod11 = S11 % 11;
	vector<float> ab;
	float a, b;
	
	int c1[3] = {
		18 - S9mod9,
		9 - S9mod9,
		0 - S9mod9
	};

	int c2[3] = {
		22 - S11mod11,
		11 - S11mod11,
		0 - S11mod11
	};

	for (int k = 0; k < 3; k++) {
		for (int l = 0; l < 3; l++) {
			ab = solveEquations(1, 1, c1[k], 1, -1, c2[l]);
			a = ab[0];
			b = ab[1];

			if (isIntDigit(a) && isIntDigit(b)) {
				return ab;
			}
		}
	}

	exit(-1);
}

int _S13(string s, int ab) {
	int mark = 1;
	int sum = 0, n;
	int h[3] = { 100, 10, 1 };

	for (int i = 0; i < s.length(); i++) {
		if (isNum(s[i])) {
			n = ctoi(s[i]);
		}
		else {
			n = ab;
		}

		sum += h[i % 3] * n * mark;

		if ((i + 1) % 3 == 0) {
			mark *= -1;
		}
	}

	return sum;
}

bool isTwoAnswers(vector<float> ab) {
	if (ab[0] == 9 && ab[1] == 9) {
		return true;
	}
	else if (ab[0] == 0 && ab[1] == 0) {
		return true;
	}

	return false;
}

vector<float> ifHasTwoAnswers(string s, vector<float> ab) {
	int S13 = _S13(s, ab[0]);

	if (S13 % 13 == 0) {
		return ab;
	}
	else {
		ab[0] = abs(ab[0] - 9);
		ab[1] = abs(ab[1] - 9);

		return ab;
	}
}

void uncountable(string s) {
	vector<float> ab;
	ab = _ab(s);

	if (isTwoAnswers(ab)) {
		ab = ifHasTwoAnswers(s, ab);
	}

	cout << abs(ab[1]) << " " << abs(ab[0]) << endl;
}

void countable(int n, string s) {
	string number = to_string(factorial(n));

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == 'a') {
			cout << number[i] << " ";
		}
		else if(s[i] == 'b') {
			cout << number[i] << endl;
		}
	}
}

int main() {
	int t, n;
	string s;
	cin >> t;

	for (int i = 0; i < t; i++) {
		cin >> n >> s;

		if (n > 10) {
			uncountable(s);
		}
		else {
			countable(n, s);
		}
	}

	return 0;
}