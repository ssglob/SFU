#include <stdio.h>
void PrintFloorColoured (FILE* stdStream, int **board, struct Robot *myRobots, int numRows, int numCols, int numRobots)
{
	#define YELLOW_PRINT    "\x1b[33m"
	#define CYAN_PRINT      "\x1b[36m"
	#define GREEN_PRINT   	"\x1b[32m"
	#define BLUE_PRINT	"\x1b[34m"
	#define MAGENTA_PRINT   "\x1b[35m"
	#define WHITE_PRINT  	"\x1b[37m"
	#define RESET_PRINT     "\x1b[0m"

	for(int K=0; K<numRows; K++)
	{
		for(int J=0; J<numCols; J++)
		{
			/* Is there a robot on the tile? */
		    int isRobot = 0;
			for (int P = 0; P < numRobots; P++)
			{
				if( myRobots[P].y != K) continue;
				if( myRobots[P].x != J) continue;
				isRobot = 1;
			}


			switch(board[K][J])
			{
				case 1:
				if(isRobot == 0)
				{
					fprintf(stdStream,YELLOW_PRINT"Y"RESET_PRINT);
				}
				else
				{
					fprintf(stdStream,YELLOW_PRINT"R"RESET_PRINT);
				}
				break;

				case 2:
				if(isRobot == 0)
				{
   					fprintf(stdStream, CYAN_PRINT"C"RESET_PRINT);
				}
				else
				{
					fprintf(stdStream, CYAN_PRINT"R"RESET_PRINT);
				}
				break;

				case 3:
				if(isRobot == 0)
				{
   					fprintf(stdStream, GREEN_PRINT"G"RESET_PRINT);
				}
				else
				{
					fprintf(stdStream, GREEN_PRINT"R"RESET_PRINT);
				}
				break;

				case 4:
				if(isRobot == 0)
				{
   					fprintf(stdStream, BLUE_PRINT"B"RESET_PRINT);
				}
				else
				{
					fprintf(stdStream, BLUE_PRINT"R"RESET_PRINT);
				}
				break;

				case 5:
				if(isRobot == 0)
				{
   					fprintf(stdStream, MAGENTA_PRINT"M"RESET_PRINT);
				}
				else
				{
					fprintf(stdStream, MAGENTA_PRINT"R"RESET_PRINT);
				}
				break;


				case 6:
				if(isRobot == 0)
				{
   					fprintf(stdStream, WHITE_PRINT"W"RESET_PRINT);
				}
				else
				{
					fprintf(stdStream, WHITE_PRINT"R"RESET_PRINT);
				}
				break;

				default:
				fprintf(stdStream, "O");
				break;			}
		}
		printf("\n");
	}
	printf("\n\n");
}