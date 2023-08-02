#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



enum { EMPTY = -1, BOMB = 99 };


typedef struct tGame {
	// Define Game
	int** board;
} Game;

Game* initGame(int sizeOfBoard, int numOfBombs, int** isOpened)
{
	// Do not change the next line and do not call srand in any more.


	// Initialize game
	Game* game = (Game*)malloc(sizeof(Game));
	game->board = (int**)malloc(sizeOfBoard * sizeof(int*));
	for (int i = 0; i < sizeOfBoard; i++) {
		game->board[i] = (int*)malloc(sizeOfBoard * sizeof(int));
	}

	for (int i = 0; i < sizeOfBoard; ++i) {
		for (int j = 0; j < sizeOfBoard; ++j) {
			game->board[j][i] = EMPTY;
		}
	}
	srand(2021);
	int count = 0;
	while (count < numOfBombs) {
		int x = rand() % sizeOfBoard;
		int y = rand() % sizeOfBoard;
		if (game->board[y][x] == EMPTY) {
			game->board[y][x] = BOMB;
			++count;
		}
	}
	
	for (size_t i = 0; i < sizeOfBoard; i++)
	{
		for (size_t j = 0; j < sizeOfBoard; j++)
		{
			isOpened[i][j] = 0;
		}

	}
	return game;
}

void PrintBoardInit(int sizeOfBoard) {
	for (size_t i = 0; i < sizeOfBoard; i++)
	{
		for (size_t j = 0; j < sizeOfBoard; j++)
		{
			/* code */
			printf("- ");
		}
		printf("\n");
	}
	printf("\n");
}
int isWin(int** isOpened, Game* game, int sizeOfBoard) {

	for (size_t i = 0; i < sizeOfBoard; i++)
	{
		for (size_t j = 0; j < sizeOfBoard; j++)
		{
			if (isOpened[i][j] == 0 && game->board[i][j] != BOMB) {
				return 0;
			}
		}

	}
	return 1;

}

void fillNumOfBombs(Game* game, int sizeOfBoard, int** bombNum)
{

	for (int i = 0; i < sizeOfBoard; i++)
	{
		for (int j = 0; j < sizeOfBoard; j++)
		{
			bombNum[i][j] = 0;
		}

	}
	for (int i = 0; i < sizeOfBoard; i++)
	{
		for (int j = 0; j < sizeOfBoard; j++)
		{
			if (game->board[i][j] == BOMB) {
				continue;
			}

			for (int x = i - 1; x <= i + 1; x++) {
				for (int y = j - 1; y <= j + 1; y++) {
					if (x < 0 || y < 0 || x >= sizeOfBoard || y >= sizeOfBoard || (x == i && y == j)) {
						continue;
					}
					else if (game->board[x][y] == BOMB) {
						bombNum[i][j]++;
					}
				}

			}
		}
	}
}


void showBoardForWinOrLose(Game* game, int x, int y, int sizeOfBoard, int** isOpened, int** bombNum)
{
	for (int i = 0; i < sizeOfBoard; ++i) {
		for (int j = 0; j < sizeOfBoard; ++j) {
			if (isOpened[i][j] == 1) {
				printf("%d ", bombNum[i][j]);
				continue;
			}
			if (x == i && y == j) {
				if (game->board[i][j] == BOMB) {
					printf("* ");
				}
				else {
					printf("%d ", bombNum[i][j]);
				}
			}
			else {
				printf("- ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void showBoard(Game* game, int sizeOfBoard, int** isOpened, int** bombNum) {
	for (int i = 0; i < sizeOfBoard; i++) {
		for (int j = 0; j < sizeOfBoard; j++) {
			if (isOpened[i][j] == 1) {
				printf("%d ", bombNum[i][j]);
				continue;
			}
			else {
				printf("- ");
			}
		}
		printf("\n");
	}
	printf("\n");
}



void RecursiveSearch(Game* game, int** isOpened, int** bombNum, int sizeOfBoard, int i, int j) {
	if (i >= sizeOfBoard || j >= sizeOfBoard || i < 0 || j < 0) {
		return;
	}
	if (bombNum[i][j] == 0) {
		isOpened[i][j] = 1;
	}
	else {
		isOpened[i][j] = 1;
		if (isWin(isOpened, game, sizeOfBoard)) {
			showBoardForWinOrLose(game, i, j, sizeOfBoard, isOpened, bombNum);
			printf("You win.");
			exit(0);
		}
		return;
	}
	for (int x = i - 1; x <= i + 1; x++) {
		for (int y = j - 1; y <= j + 1; y++) {
			if (x < 0 || y < 0 || x >= sizeOfBoard || y >= sizeOfBoard || (x == i && y == j) || isOpened[x][y] == 1) {
				continue;
			}
			else {
				RecursiveSearch(game, isOpened, bombNum, sizeOfBoard, x, y);
			}
		}
	}
}

void playGame(Game* game, int** isOpened, int** bombNum, int sizeOfBoard)
{
	// Implement the function.
	while (true) {
		int i, j;
		scanf("%d %d", &j, &i);
		printf("\n");
		if (game->board[i][j] == BOMB) {
			showBoardForWinOrLose(game, i, j, sizeOfBoard, isOpened, bombNum);
			printf("You lose.");
			exit(0);
		}
		RecursiveSearch(game, isOpened, bombNum, sizeOfBoard, i, j);
		showBoard(game, sizeOfBoard, isOpened, bombNum);
	}
}

void PrintBoardAfterBombSetup(Game* game, int sizeOfBoard, int** bombNum) {
	printf("The board after bomb setup: \n");
	for (int i = 0; i < sizeOfBoard; i++) {
		for (int j = 0; j < sizeOfBoard; j++) {
			if (game->board[i][j] == BOMB) {
				printf("* ");
			}
			else {
				printf("%d ", bombNum[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	int sizeOfBoard = 0;
	int numOfBombs = 0;

	scanf("%d %d", &sizeOfBoard, &numOfBombs);

	int** isOpened = (int**)malloc(sizeOfBoard * sizeof(int*));
	for (int i = 0; i < sizeOfBoard; i++) {
		isOpened[i] = (int*)malloc(sizeOfBoard * sizeof(int));
	}
	int** bombNum = (int**)malloc(sizeOfBoard * sizeof(int*));
	for (int i = 0; i < sizeOfBoard; i++) {
		bombNum[i] = (int*)malloc(sizeOfBoard * sizeof(int));
	}

	Game* game = initGame(sizeOfBoard, numOfBombs, isOpened);
	PrintBoardInit(sizeOfBoard);
	fillNumOfBombs(game, sizeOfBoard, bombNum);
// 	PrintBoardAfterBombSetup(game, sizeOfBoard, bombNum);
	playGame(game, isOpened, bombNum, sizeOfBoard);

	return 0;
}





