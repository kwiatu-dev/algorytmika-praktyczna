#include <iostream>

using namespace std;

char board[5][5];
int points[2] = { 0, 0 };

void print() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << board[i][j];
		}

		cout << endl;
	}
}

void point(char c) {
	if (c == 'A') {
		points[0]++;
	}
	else if (c == 'B') {
		points[1]++;
	}
}

void check() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2]){
				point(board[i][j]);
			}

			if (board[j][i] == board[j + 1][i] && board[j][i] == board[j + 2][i]) {
				point(board[j][i]);
			}
		}
	}

	for (int j = 0; j < 3; j++) {
		for (int i = 2; i < 5; i++) {
			if (board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2]) {
				point(board[i][j]);
			}

			if (board[6 - i][j] == board[6 - (i + 1)][j + 1] && board[6 - i][j] == board[6 - (i + 2)][j + 2]) {
				point(board[i][j]);
			}
		}
	}
}

void result() {
	if (points[0] > 0 && points[1] > 0) {
		cout << "remis" << endl;
	}
	else if (points[0] > 0 && points[1] == 0) {
		cout << "A wygrywa" << endl;
	}
	else if(points[0] == 0 && points[1] > 0){
		cout << "B wygrywa" << endl;
	}
}

void game() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> board[i][j];
		}
	}
}

void init() {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		game();
		check();
		result();
	}
}

int main() {
	init();

	return 0;
}