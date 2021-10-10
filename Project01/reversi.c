/*
reversi.c
Erez Cohen 21/04/2021
ID : 316098219
This program implements the game Reversi
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define ROWS 20
#define COLS 20
#define PLAYER1 'O'
#define PLAYER2 'X'
#define SIZE_10 10
#define SIZE_15 15

void checkWinner(char board[][COLS], int cols, int rows);
void initBoard(char board[][COLS], int rows, int cols);
void showBoard(char board[][COLS], int rows, int cols);
int printMenu();
int nextStep(char board[][COLS], char playerNum, int rows, int cols);
int flipDisc(char board[][COLS], char playerNum1, char playerNum2, int L, int C, int rows, int cols, int move);
int checkMove(char board[][COLS], int rows, int cols, char playerNum1, char playerNum2);
int move01(char board[][COLS], char PlayerNum1, char playerNum2, int L, int C, int dL, int dC, int rows, int cols, int move);
int move02(char board[][COLS], char PlayerNum1, char playerNum2, int L, int C, int dL, int dC, int rows, int cols, int move);
char switch_Players(char PlayerNum);

void main()
{
	char board[ROWS][COLS];
	char playerNum = PLAYER1;
	int numSize, rows, cols, finished = 0;
	numSize = printMenu();
	
	while (numSize != 0)
	{
		if (numSize == 1)
		{
			rows = SIZE_10;
			cols = SIZE_10;
			initBoard(board, rows, cols);

			while (finished != 1)
			{
				showBoard(board, rows, cols);
				finished = nextStep(board, playerNum, rows, cols);
				playerNum = switch_Players(playerNum);
			}
			checkWinner(board, cols, rows);
			numSize = 0;
		}
		else if (numSize == 2)
		{
			rows = SIZE_15;
			cols = SIZE_15;
			initBoard(board, rows, cols);

			while (finished != 1)
			{
				showBoard(board, rows, cols);
				finished = nextStep(board, playerNum, rows, cols);
				playerNum = switch_Players(playerNum);
			}
			checkWinner(board, cols, rows);
			numSize = 0;
		}
		else if (numSize == 3)
		{
			rows = ROWS;
			cols = COLS;
			initBoard(board, rows, cols);

			while (finished != 1)
			{
				showBoard(board, rows, cols);
				finished = nextStep(board, playerNum, rows, cols);
				playerNum = switch_Players(playerNum);
			}
			checkWinner(board, cols, rows);
			numSize = 0;
		}
		else
		{
			printf("Invalid choice! Please Try Again\n");
			numSize = printMenu();
		}
	}
	printf("Good Bye.\n");
}

int printMenu()
{
	int numSize;
	printf("Please enter the size of the board or press 0 to exit:\n0. Exit\n1.'10X10'\n2.'15X15'\n3.'20X20'\n");
	scanf("%d", &numSize);
	return numSize;
}

void initBoard(char board[][COLS], int rows, int cols)
{
	int i, j;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			board[i][j] = ' ';
	}
	board[(rows / 2) -1][(cols / 2) - 1] = PLAYER1;
	board[(rows / 2) - 1][cols / 2] = PLAYER2;
	board[rows / 2][(cols / 2) - 1] = PLAYER2;
	board[rows / 2][cols / 2] = PLAYER1;
}

void showBoard(char board[][COLS], int rows, int cols)
{
	int i, j;
	
	printf("\n   ");
	for (i = 1; i <= cols ; i++)
		printf("%2d|", i);
	printf("\n");

	for (i = 0; i < rows; i++)
	{
		printf("%2d|", i+1);
		for (j = 0; j < cols; j++)
			printf("%2c|", board[i][j]);
		printf("\n");
	}
	for (i = 0; i < cols * 3.5; i++)
		printf("-");
	printf("\n");
}

char switch_Players(char PlayerNum)
{
	if (PlayerNum == PLAYER2)
		PlayerNum = PLAYER1;
	else
		PlayerNum = PLAYER2;
	return (PlayerNum);
}

int nextStep(char board[][COLS], char playerNum, int rows ,int cols)
{
	int colNum, rowNum;
	bool wrongInput = true;

	if (checkMove(board, rows, cols, PLAYER2, PLAYER1) == 0 && checkMove(board, rows, cols, PLAYER1, PLAYER2) == 0)
	{
		printf("No player can make more invalid moves! The game is Over.\n");
		return 1;
	}
	else if (checkMove(board, rows, cols, PLAYER1, PLAYER2) == 0 && playerNum == PLAYER1)
	{
		printf("Player %c, You can not make any move! You lost your turn.\n",playerNum);
		return 0;
	}
	else if (checkMove(board, rows, cols, PLAYER2, PLAYER1) == 0 && playerNum == PLAYER2)
	{
		printf("Player %c, You can not make any move! You lost your turn.\n", playerNum);
		return 0;
	}
	else
	{
		while (wrongInput)
		{
			printf("Player %c, Please enter your move (num Of Row and Column): ", playerNum);
			scanf("%d%d", &rowNum, &colNum);

			rowNum--;
			colNum--;

			if (rowNum >= 0 && rowNum < rows && colNum >= 0 && colNum < cols && board[rowNum][colNum] == ' ')
			{
				if (playerNum == PLAYER1 && flipDisc(board, PLAYER1, PLAYER2, rowNum, colNum, rows, cols, 1) == 0)
				{
					printf("Invalid move! Please Try Again.\n");
					wrongInput = true;
				}

				else if (playerNum == PLAYER2 && flipDisc(board, PLAYER2, PLAYER1, rowNum, colNum, rows, cols, 1) == 0)
				{
					printf("Invalid move! Please Try Again.\n");
					wrongInput = true;
				}
				else
					wrongInput = false;
			}
			else
			{
				printf("Invalid move! Please Try Again.\n");
				wrongInput = true;
			}
		}
	return 0;
	}
}

int checkMove(char board[][COLS], int rows, int cols, char playerNum1, char playerNum2)
{
	int i, j;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if ((board[i][j] == ' ') && (flipDisc(board, playerNum1, playerNum2, i, j, rows, cols, 0) == 1))
				return 1;
		}
	}
	return 0; // no invalid move
}

int flipDisc(char board[][COLS], char playerNum1, char playerNum2, int L, int C, int rows, int cols, int move)
{
	int cnt = 0;

	cnt += move01(board, playerNum1, playerNum2, L, C, 0, 1, rows, cols, move); //Left
	cnt += move02(board, playerNum1, playerNum2, L, C, 0, 1, rows, cols, move); //Right
	cnt += move01(board, playerNum1, playerNum2, L, C, 1, 0, rows, cols, move); //Top
	cnt += move02(board, playerNum1, playerNum2, L, C, 1, 0, rows, cols, move); //Down
	cnt += move01(board, playerNum1, playerNum2, L, C, 1, 1, rows, cols, move); //Left Up Diagonal
	cnt += move02(board, playerNum1, playerNum2, L, C, 1, 1, rows, cols, move); //Right Down Diagonal
	cnt += move02(board, playerNum1, playerNum2, L, C, -1, 1, rows, cols, move); //Right Up Diagonal
	cnt += move01(board, playerNum1, playerNum2, L, C, -1, 1, rows, cols, move); //Left Down Diagonal
	
	if (cnt > 0)
		return 1;
	return 0; // cnt = 0
}

int move01(char board[][COLS], char playerNum1, char playerNum2, int L, int C, int dL, int dC, int rows, int cols, int move)
{
	int count = 0;
	int i = 1;

	while ((L - i * dL > -1 && L - i * dL < rows && C - i * dC  >-1 && C - i * dC < cols) && board[L - i * dL][C - i * dC] == playerNum2)
	{
		count++;
		i++;
	}

	if (board[L - i * dL][C - i * dC] == playerNum1 && count != 0)
	{
		if (move == 1)
		{
			while (count > 0)
			{
				board[L - count * dL][C - count * dC] = playerNum1;
				count--;
			}
			board[L][C] = playerNum1;
		}
		return 1;
	}
	return 0;
}

int move02(char board[][COLS], char playerNum1, char playerNum2, int L, int C, int dL, int dC, int rows, int cols, int move)
{
	int count = 0;
	int i = 1;
	
	while ((L + i * dL > -1 && L + i * dL < rows && C + i * dC >-1 && C + i * dC < cols) && board[L + i * dL][C + i * dC] == playerNum2)
	{
		count++;
		i++;
	}

	if (board[L + i * dL][C + i * dC] == playerNum1 && count != 0)
	{
		if (move == 1) // flip disc
		{
			while (count > 0)
			{
				board[L + count * dL][C + count * dC] = playerNum1;
				count--;
			}
			board[L][C] = playerNum1;
		}
		return 1;
	}
	return 0;
}

void checkWinner(char board[][COLS], int cols, int rows)
{
	int i, j, count1=0, count2=0;
	
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (board[i][j] == PLAYER1)
				count1++;
			else if (board[i][j] == PLAYER2)
				count2++;
		}
	}
	printf("The score is:\nPlayer %c : %d\nPlayer %c : %d\n", PLAYER1, count1, PLAYER2, count2);

	if (count1 > count2)
		printf("Player %c is the winner!!!\n\n", PLAYER1);
	else if (count2 > count1)
		printf("Player %c is the winner!!!\n\n", PLAYER2);
	else
		printf("Tie !!!\n\n");
}