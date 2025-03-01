#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int numRowsLower = 12;
const int numRowsUpper = 100;
const int numColsLower = 12;
const int numColsUpper = 100;
const int numRobotsLower = 1;
const int numRobotsUpper = 10;
const int initTypeValueLower = 1;
const int initTypeValueUpper = 3;
const int initSeedLower = 10;
const int initSeedUpper = 32767;
const int numIterationsLower = 5;
const int numIterationsUpper = 2000;
const int intervalLower = 1;
/*I define intervalUpper later as it is not a constant value*/
const char colours[4] = "YCGB";

struct Robot{
    int x;
    int y;
    int direction;
    int paintColour;
};
enum initTypeList{ RANDOM_STRIPES = 1, CHECKERBOARD, ALL_MAGENTA};

void InitFloorAllMagenta(int **floor, int numRows, int numCols) {
    for (int i = 0;i < numRows;i++) {
        for (int j = 0;j < numCols;j++) {
            floor[i][j] = 5;
        }
    }
}

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

void print_to_file(FILE* file,int** room,int numRows,int numCols){
    for (int i1 = 0;i1 < numRows;i1++) { 
        for (int j = 0;j < numCols;j++) {
            fprintf(file,"%d",room[i1][j]);
        }
        fprintf(file,"\n");
    }
}
void InitFloorChecker(int **floor, int numRows, int numCols) {
    for (int i = 0;i < numRows;i++) {
        for (int j = 0;j < numCols;j++) {
            if ((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0)) {
                floor[i][j] = 6;
            }
            else {
                floor[i][j] = 5;
            }
        }
    }
}

/*Provided function*/
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

int main() {
    char* inputfile;
    char c = ' ';
    char input;
    char buff[50];
    char outputfile[50];
    int len = 10;
    int iter = 0;
    int iter1 = 0;
    int file_open_count = 0;
    int ERROR = 0;
    int BUFFER = -1;
    int arr[] = {-1,-1,-1,-1,-1}; /*Inputs can't be less than 0 so if it is then we know it's invalid*/
    int** room = NULL;
    struct Robot* myRobots = NULL;
    int* numRows = &arr[0];
    int* numCols = &arr[1];
    int* numRobots = &arr[2];
    enum initTypeList initTypeValue = 0;
    unsigned int initSeed = 0;
    int* numIterations = &arr[3];
    int* interval = &arr[4];
    FILE* file = NULL;

    while (file_open_count < 5 && file == NULL) {
        inputfile = (char *)malloc(len*sizeof(char));
        if (inputfile == NULL) return 1;
        if (file_open_count > 0) printf("ERROR: input file not opened correctly\n");
        printf("Enter the name of the input file: ");
        while (c!='\n') {
            if (iter == len) {
                len = len*2;
                inputfile = realloc(inputfile,len*sizeof(char));
                if (inputfile == NULL) return 0;
            }
            c = getchar();
            if (c != '\n') inputfile[iter] = c;
            iter++;
        }
        file = fopen(inputfile,"r");
        free(inputfile);
        file_open_count++;
        len = 10;
        iter = 0;
        c = ' ';
    }

    if (file == NULL) {
        printf("ERROR: Failed to open the input file 5 times,\n%30s","terminating the program\n");
        return 0;
    }

    /*re-use iter here*/
    iter = 0;
    while (input = fgetc(file) != EOF && iter < 7) {
        if (input == '\n') {
            BUFFER = (int)buff;
            if (BUFFER == -1) ERROR = 1; 
            if (ERROR) {
                if (iter == 0) {
                    fprintf(stderr,"ERROR: The number of rows could not be read due to corrupt data in the file\n");
                }
                if (iter == 1) {
                    fprintf(stderr,"ERROR: The number of columns could not be read due to corrupt data in the file\n");
                }
                if (iter == 2) {
                    fprintf(stderr, "ERROR: The number of robots could not be read due to corrupt data in the file \n");
                }
                if (iter == 3) {
                    fprintf(stderr,"ERROR: The initialization type could not be read due to corrupt data in the file\n");
                }
                if (iter == 4) {
                    fprintf(stderr,"ERROR: The initialization seed could not be read due to corrupt data in the file\n");
                }
                if (iter == 5) {
                    fprintf(stderr,"ERROR: The number of iterations could not be read due to corrupt data in the file\n");
                }
                if (iter == 6) {
                    fprintf(stderr,"ERROR: The print interval could not be read due to corrupt data in the file \n");
                }
                return 0;
            }
            if (iter == 0) {
                if (BUFFER > numRowsUpper || BUFFER < numRowsLower) {
                    fprintf(stderr,"ERROR: The number of rows was outside the specified range (%d to %d inclusive)\n",numRowsLower,numRowsUpper);
                    return 0;
                }
            }
            if (iter == 1) {
                if (BUFFER > numColsUpper || BUFFER < numColsLower) {
                    fprintf(stderr,"ERROR: The number of columns was outside the specified range (%d to %d inclusive)\n",numColsLower,numColsUpper);
                    return 0;
                }
            }
            if (iter == 2) {
                if (BUFFER > numRobotsUpper || BUFFER < numRobotsLower) {
                    fprintf(stderr,"ERROR: The number of robots was outside the specified range (%d to %d inclusive) \n",numRobotsLower,numRobotsUpper);
                    return 0;
                }
            }
            if (iter == 3) {
                if (BUFFER > initTypeValueUpper || BUFFER < initTypeValueLower) {
                    fprintf(stderr,"ERROR: The initialization type was outside the specified range (%d to %d inclusive)\n",initTypeValueLower,initTypeValueUpper);
                    return 0;
                }
            }
            if (iter == 4) {
                if (BUFFER > initSeedUpper || BUFFER < initSeedLower) {
                    fprintf(stderr,"ERROR: The initialization seed was outside the specified range (%d to %d inclusive) \n",initSeedLower,initSeedUpper);
                    return 0;
                }
            }
            if (iter == 5) {
                if (BUFFER > numIterationsUpper || BUFFER < numIterationsLower) {
                    fprintf(stderr,"ERROR: The number of iterations was outside the specified range (%d to %d inclusive)\n",numIterationsLower,numIterationsUpper);
                    return 0;
                }
            }
            if (iter == 6) {
                const int intervalUpper = arr[5];
                if (BUFFER > intervalUpper || BUFFER < intervalLower) {
                    fprintf(stderr,"ERROR: The print interval was outside the specified range (%d to %d inclusive)\n",intervalLower,intervalUpper);
                    return 0;
                }
            }
            if (iter != 3 && iter != 4) {
                if (iter < 3) {
                    arr[iter] = BUFFER;
                }
                else {
                    arr[iter-2] = BUFFER; /*for iter = 5 and iter = 6*/
                }
            }
            else {
                if (iter == 3) {
                    if (BUFFER == 1) {
                        initTypeValue = RANDOM_STRIPES;
                    }
                    if (BUFFER == 2) {
                        initTypeValue = CHECKERBOARD;
                    }
                    if (BUFFER == 3) {
                        initTypeValue = RANDOM_STRIPES;
                    }
                }
                if (iter == 4) initSeed = BUFFER;
            }
            memset(buff,0,sizeof(buff));
            iter++;
            iter1 = 0;
            BUFFER = -1;
        }
        else {
            buff[iter1] = input;
            iter1++;
        }
    }
    if (input == EOF && iter < 7) {
        if (iter == 0) {
            fprintf(stderr,"ERROR: The number of rows was not in the input file (reached eof)\n");
        }
        if (iter == 1) {
            fprintf(stderr,"ERROR: The number of columns was not in the input file (reached eof)\n");
        }
        if (iter == 2) {
            fprintf(stderr, "ERROR: The number of robots was not in the input file (reached eof)\n");
        }
        if (iter == 3) {
            fprintf(stderr,"ERROR: The initialization type was not in the input file (reached eof)\n");
        }
        if (iter == 4) {
            fprintf(stderr,"ERROR: The initialization seed was not in the input file (reached eof)\n");
        }
        if (iter == 5) {
            fprintf(stderr,"ERROR: The number of iterations was not in the input file (reached eof)\n");
        }
        if (iter == 6) {
            fprintf(stderr,"ERROR: The print interval was not in the input file (reached eof)\n");
        }
        return 0;
    }
    iter = 0;
    while (input = fgetc(file) != '\n' && input != EOF) {
        outputfile[iter] = input;
        iter++;
    }
    fclose(file);

    room = (int**)malloc(*numRows*sizeof(int*));
    if (room == NULL) {
        fprintf(stderr,"ERROR: Array of pointers for 2-D array could not be allocated\n");
        return 0;
    }
    for (int i = 0;i < *numRows;i++) {
        room[i] = calloc(*numCols,sizeof(int));
        if (room[i] == NULL) {
            fprintf(stderr,"ERROR: Array storage for the 2-D array could not be allocatedn\n");
            return 0;
        }
    }
    if (initTypeValue == 1) InitFloorRandStripe(room,*numRows,*numCols,initSeed);
    if (initTypeValue == 2) InitFloorChecker(room,*numRows,*numCols);
    if (initTypeValue == 3) InitFloorAllMagenta(room,*numRows,*numCols);
    myRobots = (struct Robot*)malloc(*numRobots*sizeof(*myRobots));
    if (myRobots == NULL) {
        fprintf(stderr,"ERROR: Array of robots could not be allocated\n");
        return 0;
    }
    for (int i = 0;i < *numRobots;i++) {
        myRobots[i].x = rand() % (*numCols);
        myRobots[i].y = rand() % (*numRows);
        myRobots[i].direction = rand() % 4;
        myRobots[i].paintColour = (rand() % 4) + 1;
        room[myRobots[i].y][myRobots[i].x] = myRobots[i].paintColour;
    }

    /*reuse file*/
    file = fopen(outputfile,"a");
    for (int i = 0;i < *numIterations;i++) {
        if ((i+1) % *interval == 0 || i == 1) {
            printf("Iteration %d: ",i);
            if (i == 0) {
                printf("robots on floor with initial tile pattern");
            }
            printf("\n");
            PrintFloorColoured(stdout,room,myRobots,*numRows,*numCols,*numRobots);
        }
        fprintf(file,"Iteration %d: ",i);
        if (i == 0) {
            printf("robots on floor with initial tile pattern");
        }
        fprintf(file,"\n");
        print_to_file(file,room,*numRows,*numCols);
        fprintf(file,"\n\n");
        /*0 - North, 1 - East, 2 - South, 3 - West*/
        for (int i1 = 0;i1 < *numRobots;i1++) {
            if (myRobots[*numRobots].direction == 0) {
                for (int j = 0;j < 4;j++) {
                    myRobots[*numRobots].y = (myRobots[*numRobots].y - 1) % *numRows;
                    if (j != 3) {
                        room[myRobots[*numRobots].y][myRobots[*numRobots].x] = myRobots[*numRobots].paintColour;
                    }
                }
            }
            if (myRobots[*numRobots].direction == 1) {
                for (int j = 0;j < 4;j++) {
                    myRobots[*numRobots].x = (myRobots[*numRobots].x + 1) % *numCols;
                    if (j != 3) {
                        room[myRobots[*numRobots].y][myRobots[*numRobots].x] = myRobots[*numRobots].paintColour;
                    }
                }
            }
            if (myRobots[*numRobots].direction == 2) {
                for (int j = 0;j < 4;j++) {
                    myRobots[*numRobots].y = (myRobots[*numRobots].y + 1) % *numRows;
                    if (j != 3) {
                        room[myRobots[*numRobots].y][myRobots[*numRobots].x] = myRobots[*numRobots].paintColour;
                    }
                }
            }
            if (myRobots[*numRobots].direction == 0) {
                for (int j = 0;j < 4;j++) {
                    myRobots[*numRobots].x = (myRobots[*numRobots].x - 1) % *numCols;
                    if (j != 3) {
                        room[myRobots[*numRobots].y][myRobots[*numRobots].x] = myRobots[*numRobots].paintColour;
                    }
                }
            }
            if (room[myRobots[*numRobots].y][myRobots[*numRobots].x] == 1) {
                myRobots[*numRobots].paintColour = (myRobots[*numRobots].paintColour + 1) % 4;
            }
            if (room[myRobots[*numRobots].y][myRobots[*numRobots].x] == 2) {
                myRobots[*numRobots].paintColour = (myRobots[*numRobots].paintColour + 2) % 4;
            }
            if (room[myRobots[*numRobots].y][myRobots[*numRobots].x] == 3) {
                myRobots[*numRobots].paintColour = (myRobots[*numRobots].paintColour + 3) % 4;
            }
            if (room[myRobots[*numRobots].y][myRobots[*numRobots].x] == 4) {
                myRobots[*numRobots].paintColour = (myRobots[*numRobots].paintColour) % 4;
            }
            if (room[myRobots[*numRobots].y][myRobots[*numRobots].x] == 5) {
                myRobots[*numRobots].paintColour = (myRobots[*numRobots].paintColour + 1) % 4;
            }
            if (room[myRobots[*numRobots].y][myRobots[*numRobots].x] == 6) {
                myRobots[*numRobots].paintColour = (myRobots[*numRobots].paintColour + 2) % 4;
            }
            room[myRobots[*numRobots].y][myRobots[*numRobots].x] = myRobots[*numRobots].paintColour;
        }
    }
    printf("Iteration %d:\n",*numIterations);
    PrintFloorColoured(stdout,room,myRobots,*numRows,*numCols,*numRobots);

    fprintf(file,"Iteration %d: ",*numIterations);
    fprintf(file,"\n");
    print_to_file(file,room,*numRows,*numCols);

    /*free memory*/
    fclose(file);
    for (int i = 0;i < *numRows;i++) {
        free(room[i]);
    }
    free(room);
    free(myRobots);
    return 0;
}