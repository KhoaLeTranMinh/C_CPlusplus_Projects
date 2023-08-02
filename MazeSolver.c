// C program for list implementation of queue
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// A structure to represent a queue


typedef struct Coordinates {
	int x, y;
	int left, right, up, down;
} Coor;


// function to create a queue
// of given capacity.
// It initializes size of queue as 0

char* intToBinary(int n) {
	long long bin = 0;
	int rem, factor = 1;

	while (n != 0) {
		rem = n % 2;
		n /= 2;
		bin += rem * factor;
		factor *= 10;
	}

	char* roomNum = (char*)malloc(sizeof(char) * 5); //Have to do this dynamically, because we are returning a char* type. If we do otherwise, every mazeInfoBin element will have the same address
	int i = 3;
	int binCopy = bin;
	while (i >= 0) {
		roomNum[i] = bin % 10 + '0'; //Worth Noting
		bin /= 10;
		i--;
	}
	roomNum[4] = '\0'; // Remember this characteristic in C-String
	return roomNum;

}

void mazeInfoFill(Coor* room, char* roomNum) {
	if (roomNum[0] == '1') {
		room->down = 1;
	}
	if (roomNum[1] == '1') {
		room->up = 1;
	}
	if (roomNum[2] == '1') {
		room->right = 1;
	}
	if (roomNum[3] == '1') {
		room->left = 1;
	}
}

int*** pathList;
int** currentPath;

void roomFinder(Coor* room, bool** visited, Coor* finish, Coor** roomCoords, int size, int* pathIndex, int* pathSizes, int height, int width) {
	//pathNumber, size will be initialized as 0;
	int x = room->x;
	int y = room->y;
	size++;
	visited[x][y] = true;
	currentPath[size - 1][0] = x;
	currentPath[size - 1][1] = y;

	if (x == finish->x && y == finish->y) {
		visited[x][y] = false;
		for (int i = 0; i < size; i++) {
			pathList[*pathIndex][i][0] = currentPath[i][0];
			pathList[*pathIndex][i][1] = currentPath[i][1];
		}
		pathSizes[*pathIndex] = size;
		(*pathIndex)++;
		currentPath[size - 1][0] = -1;
		currentPath[size - 1][1] = -1;
		return;
	}
	if (room->up == 0) {
		if (visited[x - 1][y] == false) {
			roomFinder(&roomCoords[x - 1][y], visited, finish, roomCoords, size, pathIndex, pathSizes, height, width);
		}
	}

	if (room->right == 0) {
		if (visited[x][y + 1] == false) {
			roomFinder(&roomCoords[x][y + 1], visited, finish, roomCoords, size, pathIndex, pathSizes, height, width);
		}
	}

	if (room->down == 0) {
		if (visited[x + 1][y] == false) {
			roomFinder(&roomCoords[x + 1][y], visited, finish, roomCoords, size, pathIndex, pathSizes, height, width);
		}
	}

	if (room->left == 0) {
		if (visited[x][y - 1] == false) {
			roomFinder(&roomCoords[x][y - 1], visited, finish, roomCoords, size, pathIndex, pathSizes, height, width);
		}
	}

	currentPath[size - 1][0] = -1;
	currentPath[size - 1][1] = -1;
	visited[x][y] = false;
	return;

}

int main()
{
	int width, height;
	scanf("%d %d", &width, &height);
	int startX, startY;
	scanf("%d %d", &startY, &startX);
	int goalX, goalY;
	scanf("%d %d", &goalY, &goalX);
	Coor* start = (Coor*)malloc(sizeof(Coor) * 1);
	Coor* finish = (Coor*)malloc(sizeof(Coor) * 1);


	int** roomInfo = (int**)malloc(sizeof(int*) * height);
	for (int i = 0; i < height; i++) {
		roomInfo[i] = (int*)malloc(sizeof(int) * width);
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			scanf("%d", &roomInfo[i][j]);
		}
	}


	char*** roomInfoBin = (char***)malloc(sizeof(char**) * height);
	for (int i = 0; i < height; i++) {
		roomInfoBin[i] = (char**)malloc(sizeof(char*) * width);
		for (int j = 0; j < width; j++)
		{
			roomInfoBin[i][j] = (char*)malloc(sizeof(char) * 5);
		}
	}



	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			roomInfoBin[i][j] = intToBinary(roomInfo[i][j]);
		}
	}

	//for (int i = 0; i < height; i++) {
	//	for (int j = 0; j < width; j++) {
	//		printf("%s ", roomInfoBin[i][j]);
	//	}
	//	printf("\n");
	//}


	Coor** roomCoords = (Coor**)malloc(sizeof(Coor*) * height);
	for (int i = 0; i < height; i++) {
		roomCoords[i] = (Coor*)malloc(sizeof(Coor) * width);
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Coor temp = { i,j,0,0,0,0 };
			roomCoords[i][j] = temp;
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			mazeInfoFill(&roomCoords[i][j], roomInfoBin[i][j]);
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (roomCoords[i][j].x == startX && roomCoords[i][j].y == startY) {
				start = &roomCoords[i][j];
			}

			if (roomCoords[i][j].x == goalX && roomCoords[i][j].y == goalY) {
				finish = &roomCoords[i][j];
			}
		}
	}


	pathList = (int***)malloc(sizeof(int**) * 1000);
	for (int i = 0; i < 1000; i++) {
		pathList[i] = (int**)malloc(sizeof(int*) * 1000);
		for (int j = 0; j < 1000; j++) {
			pathList[i][j] = (int*)malloc(sizeof(int) * 2);
		}
	}



	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			pathList[i][j][0] = -1;
			pathList[i][j][1] = -1;
		}
	}

	currentPath = (int**)malloc(sizeof(int*) * 1000);
	for (size_t i = 0; i < 1000; i++)
	{
		currentPath[i] = (int*)malloc(sizeof(int) * 2);
	}

	bool** visited = (bool**)malloc(sizeof(bool*) * height);
	for (int i = 0; i < height; i++)
	{
		visited[i] = (bool*)malloc(sizeof(bool) * width);
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			visited[i][j] = false;
		}
	}

	int* pathIndex = (int*)malloc(sizeof(int) * 1);
	(*pathIndex) = 0;
	int* pathSizes = (int*)malloc(sizeof(int) * 1000);
	for (int i = 0; i < 1000; i++)
	{
		pathSizes[i] = 0;
	}
	roomFinder(&roomCoords[0][0], visited, finish, roomCoords, 0, pathIndex, pathSizes, height, width);


	int toBeSorted[1000];
	for (int i = 0; i < *pathIndex; i++) {
		toBeSorted[i] = i;
	}

	for (int i = 0; i < *pathIndex - 1; i++)
		for (int j = 0; j < *pathIndex - i - 1; j++)
			if (pathSizes[j] > pathSizes[j + 1]) {
				int temp = pathSizes[j];
				pathSizes[j] = pathSizes[j+1];
				pathSizes[j + 1] = temp;


				int temp2 = toBeSorted[j];
				toBeSorted[j] = toBeSorted[j + 1];
				toBeSorted[j + 1] = temp2;
				
			}
				

	for (int i = 0; i < *pathIndex; i++) {
		for (int j = 0; j < pathSizes[i]; j++) {
			printf("(%d, %d) ", pathList[toBeSorted[i]][j][1], pathList[toBeSorted[i] ][j][0]);
		}

		printf("\n");
	}



	return 0;
}

