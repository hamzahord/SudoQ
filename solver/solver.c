#include <stdio.h>
#include <stdlib.h>
#include "solver.h"

char sudoku[9][9] = {
		{'.','8','.','7','9','.','.','.','.'},
		{'.','.','.','.','.','2','.','9','.'},
		{'.','.','3','.','.','8','4','5','.'},
		{'.','.','8','.','.','.','.','.','1'},
		{'.','9','6','.','.','.','3','7','.'},
		{'3','.','.','.','.','.','2','.','.'},
		{'.','3','2','5','.','.','9','.','.'},
		{'.','4','.','8','.','.','.','.','.'},
		{'.','.','.','.','6','4','.','2','.'},
};

int main(void) {

	Solve(sudoku);
	PrintSudoku(sudoku);
}

void PrintSudoku(char sudoku[9][9]) {
	for (unsigned int x = 0; x < 9; x++)
	{
		printf("| ");
		for (unsigned int y = 0; y < 9; y++)
		{
			printf("%c | ", sudoku[x][y]);
		}
		printf("\n");
	}
}

//0 false; 1 true;

//is it possible to do it faster with histogram ?
int AlreadyInColumn(char sudoku[9][9], unsigned y, char val) {
	if (y > 8) {
		//EXCEPTION
	}
	for (unsigned int x = 0; x < 9; x++)
	{
		if (val == sudoku[x][y])
		{
			return 1;
		}
	}
	return 0;
}

int AlreadyInLine(char sudoku[9][9], unsigned x, char val) {
	if (x > 8) {
		//EXCPETION
	}
	for (unsigned int y = 0; y < 9; y++)
	{
		if (val == sudoku[x][y])
		{
			return 1;
		}
	}
	return 0;
}


int AlreadyInSquare(char sudoku[9][9], unsigned x, unsigned y, char val) {

	for (unsigned int i = 3*(x/3); i < 3 * (x / 3) + 3; i++)
	{
		for (unsigned int j = 3 * (y / 3); j < 3 * (y / 3) + 3; j++)
		{
			if (sudoku[i][j] == val) {
				return 1;
			}
		}
	}
	return 0;
}

int SolveRec(char sudoku[9][9], unsigned x, unsigned y) {
	if (x == 9 && y == 0) {
		return 1;
	}
	if (sudoku[x][y] == '.') {
		for (unsigned int i = 0; i < 10; i++)
		{
			//is valid ?
			if (!AlreadyInColumn(sudoku, y, i) && !AlreadyInLine(sudoku, x, i) && !AlreadyInSquare(sudoku, x, y, i))
			{
				sudoku[x][y] = i +'0';
				if (y == 8)
				{
					if (SolveRec(sudoku, x+1, 0) == 1) {
						return 1;
					}
				}
				else {
					if (SolveRec(sudoku, x, y+1) == 1)
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

void Solve(char sudoku[9][9]) {
	SolveRec(sudoku, 0, 0);
}
