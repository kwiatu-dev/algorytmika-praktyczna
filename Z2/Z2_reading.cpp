#include <iostream>
#include <vector>

using namespace std;

vector<int> chapters;
vector<int> relations;
vector<bool> summary_chapters;

int read(int chapter, vector<bool>& learned, bool overwrite) {
	int pages = 0, relation = 0;

	for (; relation != -1; chapter = relations[chapter]) {
		if (learned[chapter] == false) {
			pages += chapters[chapter];
			learned[chapter] = overwrite ? true : learned[chapter];
		}

		relation = relations[chapter];
	}

	return pages;
}

void find_cc() {
	int min = INT_MAX;
	int pair[2] = {0, 0};
	int sum = 0;
	int n = chapters.size();
	vector<bool> learned(n, false);

	for (int i = 0; i < n - 1; i++) {
		if (summary_chapters[i] == true) {
			pair[0] = read(i, learned, true);

			for (int j = i + 1; j < n; j++) {
				if (summary_chapters[j] == true) {
					pair[1] = read(j, learned, false);
					sum = pair[0] + pair[1];

					if (min > sum) {
						min = sum;
					}
				}
			}

			learned.clear();
			learned.resize(n, false);
		}
	}

	cout << min << endl;
}

void book() {
	int n, q, b, a;
	cin >> n >> q;
	chapters.resize(n);
	relations.resize(n, -1);
	summary_chapters.resize(n, true);
	
	for (int i = 0; i < n; i++) {
		cin >> chapters[i];
	}

	for (int i = 0; i < q; i++) {
		cin >> b >> a;
		relations[a - 1] = b - 1;
		summary_chapters[b - 1] = false;
	}

	find_cc();
	chapters.clear();
	relations.clear();
	summary_chapters.clear();
}

int main() {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		book();
	}
}