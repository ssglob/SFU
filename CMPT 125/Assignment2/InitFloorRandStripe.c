#include <stdio.h>
void InitFloorRandStripe(int **board, int numRows, int numCols, unsigned int seed )
{
	const int NUM_COLOURS_STRIPES = 6;
	srand(seed);
	int *row = NULL;
	row = (int *)malloc(numCols*sizeof(int));
	if(row == NULL)
	{
		return;
	}
	for(int K=0; K<numCols; K++)
	{
			row[K] = rand() % NUM_COLOURS_STRIPES + 1;
	}	
	for(int K=0; K<numRows; K++)
	{
		for(int J=0; J<numCols; J++)
		{
			board[K][J] = row[J]; }
	}
}
