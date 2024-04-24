#include <iostream>
#include <vector>
#include <string>
using namespace std;

void ignoreWhiteSpaces(char& input) {
	while (input == '\n' || input == '\t' || input == ' ') {
		input = cin.get();
	}
}

bool isCharacterALetter(char input) {
	return (input >= 'A' && input <= 'Z');
}

bool isCommand(char input) {
	return isCharacterALetter(input);
}

//struct char {
//	char content;
//};

class Board {
private:
	int rows;
	vector<int> columns;
	
public:
	vector<vector<char>> board;

	Board() : rows(0), columns(0), board(0){}

	Board(int rows, vector<int> columns, vector<vector<char>> board) {
		this->rows = rows;
		this->columns = columns;
		this->board = board;
	}
	void setRows(int rows) {
		this->rows = rows;
	}
	void setColumns(vector<int> columns) {
		this->columns = columns;
	}
	void setBoard(vector<vector<char>> board) {
		this->board = board;
	}
	int getRows() {
		return rows;
	}
	vector<int> getColumns() {
		return columns;
	}
	vector<vector<char>> getBoard() {
		return board;
	}
	int getSize() {
		return rows / 2;
	}
	int boardSize() {
		return board.size();
	}
	int boardSize(int i) {
		return board[i].size();
	}
	//char getBoardContent(int i, int j) {
	//	return board[i][j].content;
	//}
	string loadBoard() { //zwraca stringa bo pobiera kolejny element (wiec ostatni raz pobierze pierwsza komende)
		string input;
		vector<vector<char>> newBoard;
		int rows = 0;
		vector<int> columns;

		while (getline(cin, input) && !isCommand(input[0])) {
			vector<char> row;

			for (char inputChar : input) {
				row.push_back({ inputChar });
			}
			newBoard.push_back(row);
			columns.push_back(row.size());
			rows++;
		}

		setRows(rows);
		setColumns(columns);
		setBoard(newBoard);
		return input;
	}
	void showBoard() {
		for (int i = 0; i < boardSize(); i++) {
			for (int j = 0; j < boardSize(i); j++) {
				//cout << getBoardContent(i, j);
				cout << board[i][j];
			}
			cout << endl;
		}
	}

	~Board() {};
};

int pawnCounter(Board& board) {
	int counterOfPawns = 0;

	for (int i = 0; i < board.boardSize(); i++) {
		for (int j = 0; j < board.boardSize(i); j++) {
			if (board.board[i][j] == 'r' || board.board[i][j] == 'b') {
				counterOfPawns++;
			}
		}
	}

	return counterOfPawns;
}

void commandHandler(string command, Board board) {
	if (command == "BOARD_SIZE") {
		cout<<board.getSize()<<endl;
	}
	else if (command == "PAWNS_NUMBER") {
		//ile jest pionow
		cout << pawnCounter(board) << endl;
	}
	else if (command == "IS_BOARD_CORRECT") {

	}
	else if (command == "IS_GAME_OVER") {

	}
	else if (command == "IS_BOARD_POSSIBLE") {

	}
	else if (command == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {

	}
	else if (command == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {

	}
	else if (command == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {

	}
	else if (command == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {

	}
	else if (command == "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {

	}
	else if (command == "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {

	}
	else if (command == "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {

	}
	else if (command == "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {

	}
	else {
		return;
	}
}


int main() {
	string instruction;
	Board board;

	while (cin.peek() != EOF) {
		//tworzenie planszy
		board = Board();
		instruction = board.loadBoard();
		board.showBoard();

		//przyjmowanie komend
		do {
			commandHandler(instruction, board);
		} while (getline(cin, instruction) && isCommand(instruction[0]));
	}

	return 0;
}
