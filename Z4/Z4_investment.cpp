#include <iostream>
#include <unordered_map>

using namespace std;

int amount, years;
int d;
int** bonds;
unordered_map<int, int> amount_interest;

void load() {
	int cost, value;
	cin >> amount >> years;
	cin >> d;
	bonds = new int* [d];

	for (int i = 0; i < d; i++) {
		cin >> cost >> value;
		bonds[i] = new int[2] { cost, value };
	}
}

void reset() {
	for (int i = 0; i < d; i++) {
		delete[] bonds[i];
	}

	delete[] bonds;
	amount_interest.clear();
}

int lookdown(int amount) {
	return amount_interest.count(amount) > 0 ? amount_interest[amount] : 0;
}

int max_interest(int amount) {
	if (amount < 1000) return 0;
	if (amount_interest.count(amount) > 0) amount_interest[amount];
	int max = -1, temp = 0;
	int bond_cost, bond_value;

	for (int i = 0; i < d; i++) {
		bond_cost = bonds[i][0];
		bond_value = bonds[i][1];

		if (amount > bond_cost) {
			temp = bond_value + lookdown(amount - bond_cost);
		}
		else if (amount == bond_cost) {
			temp = bond_value;
		}

		if (max < temp) {
			max = temp;
		}
	}

	return max;
}

void compute_max_capital() {
	int a = 1000;

	for (int y = 1; y <= years; y++) {
		for (a -= 1000; a <= amount; a += 1000) {
			amount_interest[a] = max_interest(a);
		}

		amount += amount_interest[a - 1000];
	}

	cout << amount << endl;
}

void test() {
	load();
	compute_max_capital();
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