#include <iostream>
#include <iomanip>
#include <string>
#include <set>

using namespace std;

int a, k;
char* alphabet;
set<char> sub_alphabet;
string encrypted_text;
string* encrypted_words;
int** rels;

void create_sub_alphabet(string s) {
	if (sub_alphabet.size() == a) return;

	for (int i = 0; i < s.length(); i++) {
		sub_alphabet.insert(s[i]);
	}
}

char sub_alphabet_letter(int index) {
	return *next(sub_alphabet.begin(), index);
}

int sub_alphabet_index(char letter) {
	int i = 0;

	for (char c : sub_alphabet) {
		if (c == letter) {
			return i;
		}

		i++;
	}
}

void print() {
	cout << "A: " << a << endl;
	cout << "K: " << k << endl;
	cout << endl;
	cout << "Encrypted words: " << endl;

	for (int i = 0; i < k; i++) {
		cout << encrypted_words[i] << endl;
	}

	cout << endl;
	cout << "Encrypted text: " << endl;
	cout << encrypted_text << endl;
	cout << endl;
	cout << "Relations: " << endl;

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < a; j++) {
			cout << setw(2) << rels[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	cout << "Substitution alphabet: " << endl;

	for (int i = 0; i < a; i++) {
		cout << sub_alphabet_letter(i) << ", ";
	}

	cout << endl << endl;
}

void set_vars() {
	alphabet = new char[a];
	encrypted_words = new string[k];
	rels = new int* [a];

	for (int i = 0; i < a; i++) {
		rels[i] = new int[a] {0};
	}
}

void reset_vars() {
	sub_alphabet.clear();
	encrypted_text = "";

	for (int i = 0; i < a; i++) {
		delete[] rels[i];
	}

	delete[] alphabet, encrypted_words, rels;

}

void load_words() {
	for (int i = 0; i < k; i++) {
		cin >> encrypted_words[i];
		create_sub_alphabet(encrypted_words[i]);
	}

	cin.ignore();
	getline(cin, encrypted_text);
}

void complate_rels(int r1, int r2) {
	for (int i = 0; i < a; i++) {
		if (rels[r2][i] == 1 && i != r1) {
			rels[r1][i] = 1;
			rels[i][r1] = -1;
		}

		if (rels[i][r1] == 1 && i != r2) {
			rels[i][r2] = 1;
			rels[r2][i] = -1;
		}
	}
}

bool can_decrypt() {
	int sum;

	for (int i = 0; i < a; i++) {
		sum = 0;

		for (int j = 0; j < a; j++) {
			sum += abs(rels[i][j]);
		}

		if (sum != a - 1) {
			return false;
		}
	}

	return true;
}

void result() {
	int sum;
	int r = a - 1;
	char c;

	for (int i = 0; i < a; i++) {
		sum = 0;

		for (int j = 0; j < a; j++) {
			if (rels[i][j] == 1) {
				sum++;
			}
		}

		alphabet[i] = sub_alphabet_letter(r - sum);
	}

	for (int i = 0; i < encrypted_text.length(); i++) {
		c = encrypted_text[i];

		if (sub_alphabet.count(c) > 0) {
			cout << alphabet[sub_alphabet_index(c)];
		}
		else {
			cout << c;
		}
	}

	cout << endl;
}

void decrypt() {
	int l;
	int r1, r2;
	string w1, w2;

	for (int w = 0; w < k - 1; w++) {
		w1 = encrypted_words[w];
		w2 = encrypted_words[w + 1];
		l = min(w1.length(), w2.length());

		for (int i = 0; i < l; i++) {
			if (w1[i] != w2[i]) {
				r1 = sub_alphabet_index(w1[i]);
				r2 = sub_alphabet_index(w2[i]);

				rels[r1][r2] = 1;
				rels[r2][r1] = -1;
				complate_rels(r1, r2);
				break;
			}
		}

		if (can_decrypt()) { result(); return; }
	}

	if (k - 1 > 0) {
		cout << "Message cannot be decrypted" << endl;
	}
	else {
		cout << encrypted_text << endl;
	}
}

void start() {
	set_vars();
	load_words();
}

void end() {
	reset_vars();
}

void test() {
	cin >> a >> k;
	start();
	decrypt();
	//print();
	end();
}

int main() {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		test();
	}

	return 0;
}