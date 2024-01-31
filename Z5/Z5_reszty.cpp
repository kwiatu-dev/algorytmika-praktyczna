#include <iostream>
#include <string>
#include <sstream>
#define T unsigned long long

using namespace std;

int n;
string line;
istringstream sequence_a, sequence_b;
T a, b, temp = 0;

T NWD(T a, T b)
{
	if (b != 0)
		return NWD(b, a % b);

	return a;
}

void reset() {
	temp = 0;
	sequence_a.clear();
	sequence_a.seekg(0);
	sequence_b.clear();
	sequence_b.seekg(0);
}

void test() {
	cin >> n; cin.ignore();

	getline(cin, line);
	sequence_a.str(line);

	getline(cin, line);
	sequence_b.str(line);

	while (sequence_a >> a && sequence_b >> b) {
		temp = NWD(a - b, temp);
	}

	cout << temp << endl; reset();
}

int main() {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		test();
	}

	return 0;
}