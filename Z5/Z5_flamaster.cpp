#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <unordered_map>

using namespace std;

char c;
string line;
istringstream iss;
stack<char> open;
stack<char> close;
unordered_map<char, char> close_open = { { '}', '{' }, { ')', '(' }, { ']', '[' } };
unordered_map<char, char> open_close = { { '{', '}' }, { '(', ')' }, { '[', ']' } };
bool cant = false;

bool open_bracket(char c) {
	if (c == '(') {
		return true;
	}
	else if (c == '[') {
		return true;
	}
	else if (c == '{') {
		return true;
	}

	return false;
}

void when_open_bracket(char c) {
	open.push(c);
}

void when_close_bracket(char c) {
	if (open.size() == 0) {
		close.push(c);
	}
	else {
		if (close_open[c] == open.top()) {
			open.pop();
		}
		else {
			cant = true;
		}
	}
}

void result() {
	string r;

	while(close.size()){
		r += close_open[close.top()];  close.pop();
	}

	r += line;

	while(open.size() > 0){
		r += open_close[open.top()]; open.pop();
	}

	if (!cant) {
		cout << r << endl;
	}
	else {
		cout << "NIE" << endl;
	}
}

void reset() {
	iss.clear();
	iss.seekg(0);
	cant = false;
}

void test() {
	getline(cin, line);
	iss.str(line);

	while (iss >> c) {
		if (open_bracket(c)) {
			when_open_bracket(c);
		}
		else {
			when_close_bracket(c);
		}

		if (cant) break;
	}

	result(); reset();
}

int main() {
	int t;
	cin >> t; cin.ignore();

	for (int i = 0; i < t; i++) {
		test();
	}

	return 0;
}