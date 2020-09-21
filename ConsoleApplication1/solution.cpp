#include <iostream>
#include <vector>
#include <string>
using namespace std;
/*
int pick(vector<vector<int>> &board, int lineNumber)
{
	int doll;

	for (int i = 0; i < board.size(); i++)
	{
		if (board[i][lineNumber - 1] != 0)
		{
			doll = board[i][lineNumber - 1];
			board[i][lineNumber - 1] = 0;
			return doll;
		}
	}
	return -1;
}
int solution(vector<vector<int>> board, vector<int> moves) {
	int answer = 0;

	int * arr = new int[moves.size()];
	
	int top = -1;

	for (int i = 0; i < moves.size(); i++)
	{
		int result = pick(board, moves[i]);
		if(result != -1)
			arr[++top] = result;
		if (top > 0 && arr[top] == arr[top - 1])
		{
			answer += 2;
			top -= 2;
		}
	}

	return answer;
}

int main()
{
	vector<vector<int>> board = { {0, 0, 0, 0, 0}, {0, 0, 1, 0, 3}, {0, 2, 5, 0, 1}, {4, 2, 4, 4, 2}, {3, 5, 1, 3, 1} };
	vector<int> moves = { 1,5,3,5,1,2,1,4 };
	cout << solution(board, moves);
}
*/
// /*
string solution(int n) 
{
	string answer = "";
	int a;
	bool borrow = false;
	while (n > 0)
	{
		a = n % 3;
		if (borrow)
			a--; 
		borrow = false;
		switch (a)
		{
		case 0:
			answer = '4' + answer;
			borrow = true;
			break;
		case 1:
			answer = to_string(a) + answer;
			break;
		case 2:
			answer = to_string(a) + answer;
			break;
		default:
			break;
		}

		n /= 3;
	}
	
	return answer;
}

int main()
{
	for (int i = 0; i < 30; i++)
	{
		cout << i << " -> " << solution(i) << endl;
	}
}
// */