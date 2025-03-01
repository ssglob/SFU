#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMROWSLOWER 12
#define  NUMROWSUPPER 100
#define  NUMCOLSLOWER 12
#define  NUMCOLSUPPER 100
#define  NUMROBOTSLOWER 1
#define  NUMROBOTSUPPER 10
#define  INITTYPEVALUELOWER 1
#define  INITTYPEVALUEUPPER 3
#define  INITSEEDLOWER 10
#define  INITSEEDUPPER 32767
#define  NUMITERATIONSLOWER 5
#define  NUMITERATIONSUPPER 2000
#define  INTERVALLOWER 1
/*I define intervalUpper later as it is not a constant value that I can define here*/

struct Robot{
    int x;
    int y;
    int direction;
    int paintColour;
};
enum initTypeList{ RANDOM_STRIPES = 1, CHECKERBOARD, ALL_MAGENTA};

/*This program takes user input and attempts to open a file whose name is the input. It reads the contents of the file and assigns values to several variables.
Then, it will generate a floor and robots that will move along the floor. Every iteration the robots will move forward and then turn. The program prints every
iteration to an output file, and prints the 0th, 1st, and last iteration, as well as any iteration that is divisible by an interval provided by the input file.*/

int isint(char* string, int max) {
    char digits[12] = "1234567890-\n";
    int digit = 0;
    for (int i = 0;i < max-1;i++) {
        if (string[i] == "-" && i > 0) {
            return 0;
        }
        for (int i1 = 0;i1 < 11;i1++) {
            if (string[i] == digits[i1]) {
                digit = 1;
                break;
            }
        }
        if (!digit) {
            return 0;
        }
        digit = 0;
    }
    return 1;
}

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
    int white = 0;
    int rowWhite = 0;
    for (int i = 0;i < numRows;i++) {
        if (i % 4 == 0) {
            if (rowWhite == 0) {
                rowWhite = 1;
            }
            else {
                rowWhite = 0;
            }
        }
        if (rowWhite) {
            white = 0;
        }
        else {
            white = 1;
        }
        for (int j = 0;j < numCols;j++) {
            if (j % 4 == 0) {
                if (white == 0) {
                    white = 1;
                }
                else {
                    white = 0;
                }
            }
            if (white) {
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
    int BUFFER = 0;
    int arr[] = {0,0,0,0,0};
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
        if (inputfile == NULL) {
            return 1;
        }
        if (file_open_count > 0) printf("ERROR: input file not opened correctly\n");
        printf("Enter the name of the input file: ");
        while (c!='\n') {
            if (iter == len) {
                len = len*2;
                inputfile = realloc(inputfile,len*sizeof(char));
                if (inputfile == NULL) {
                    return 0;
                }
            }
            c = getchar();
            if (c != '\n') {
                inputfile[iter] = c;
            }
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
    input = fgetc(file);
    while (iter < 8) {
        // printf("%c",input);
        if (input == '\n' || input == EOF) {
            if (iter == 7) {
                strcpy(outputfile,buff);
                break;
            }
            if (buff[0] == '\0') {
                break;
            }
            if (!isint(&buff[0],iter1)) {
                ERROR = 1;
            }
            BUFFER = atoi(buff);
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
                if (BUFFER > NUMROWSUPPER || BUFFER < NUMROWSLOWER) {
                    fprintf(stderr,"ERROR: The number of rows was outside the specified range (%d to %d inclusive)\n",NUMROWSLOWER,NUMROWSUPPER);
                    return 0;
                }
            }
            if (iter == 1) {
                if (BUFFER > NUMCOLSUPPER || BUFFER < NUMCOLSLOWER) {
                    fprintf(stderr,"ERROR: The number of columns was outside the specified range (%d to %d inclusive)\n",NUMCOLSLOWER,NUMCOLSUPPER);
                    return 0;
                }
            }
            if (iter == 2) {
                if (BUFFER > NUMROBOTSUPPER || BUFFER < NUMROBOTSLOWER) {
                    fprintf(stderr,"ERROR: The number of robots was outside the specified range (%d to %d inclusive) \n",NUMROBOTSLOWER,NUMROBOTSUPPER);
                    return 0;
                }
            }
            if (iter == 3) {
                if (BUFFER > INITTYPEVALUEUPPER || BUFFER < INITTYPEVALUELOWER) {
                    fprintf(stderr,"ERROR: The initialization type was outside the specified range (%d to %d inclusive)\n",INITTYPEVALUELOWER,INITTYPEVALUEUPPER);
                    return 0;
                }
            }
            if (iter == 4) {
                if (BUFFER > INITSEEDUPPER || BUFFER < INITSEEDLOWER) {
                    fprintf(stderr,"ERROR: The initialization seed was outside the specified range (%d to %d inclusive) \n",INITSEEDLOWER,INITSEEDUPPER);
                    return 0;
                }
            }
            if (iter == 5) {
                if (BUFFER > NUMITERATIONSUPPER || BUFFER < NUMITERATIONSLOWER) {
                    fprintf(stderr,"ERROR: The number of iterations was outside the specified range (%d to %d inclusive)\n",NUMITERATIONSLOWER,NUMITERATIONSUPPER);
                    return 0;
                }
            }
            if (iter == 6) {
                const int intervalUpper = *numIterations;
                if (BUFFER > intervalUpper || BUFFER < INTERVALLOWER) {
                    fprintf(stderr,"ERROR: The print interval was outside the specified range (%d to %d inclusive)\n",INTERVALLOWER,intervalUpper);
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
                        initTypeValue = ALL_MAGENTA;
                    }
                }
                if (iter == 4) {
                    initSeed = BUFFER;
                }
            }
            memset(buff,0,sizeof(buff));
            iter++;
            iter1 = 0;
            BUFFER = 0;
        }
        else {
            buff[iter1] = input;
            iter1++;
        }
        input = fgetc(file);
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
    if (initTypeValue == 1) {
        InitFloorRandStripe(room,*numRows,*numCols,initSeed);
    }
    if (initTypeValue == 2) {
        InitFloorChecker(room,*numRows,*numCols);
    }
    if (initTypeValue == 3) {
        InitFloorAllMagenta(room,*numRows,*numCols);
    }
    myRobots = (struct Robot*)malloc(*numRobots*sizeof(*myRobots));
    if (myRobots == NULL) {
        fprintf(stderr,"ERROR: Array of robots could not be allocated\n");
        return 0;
    }
    for (int i = 0;i < *numRobots;i++) {
        myRobots[i].x = rand() % (*numCols);
        myRobots[i].y = rand() % (*numRows);
        myRobots[i].direction = rand() % 4;
        myRobots[i].paintColour = (rand() % 4)+1;
        room[myRobots[i].y][myRobots[i].x] = myRobots[i].paintColour;
    }

    /*reuse file*/
    file = fopen(outputfile,"w");
    for (int i = 0;i < *numIterations;i++) {
        if ((i+1) % *interval == 0 || i == 1 || i == 0) {
            printf("Iteration %d: ",i);
            if (i == 0) {
                printf("robots on floor with initial tile pattern");
            }
            printf("\n");
            PrintFloorColoured(stdout,room,myRobots,*numRows,*numCols,*numRobots);
        }
        fprintf(file,"Iteration %d: ",i);
        if (i == 0) {
            fprintf(file,"robots on floor with initial tile pattern");
        }
        fprintf(file,"\n");
        print_to_file(file,room,*numRows,*numCols);
        fprintf(file,"\n\n");
        /*0 - North, 1 - East, 2 - South, 3 - West*/
        for (int i1 = 0;i1 < *numRobots;i1++) {
            if (myRobots[i1].direction == 0) {
                for (int j = 0;j < 4;j++) {
                    myRobots[i1].y = (myRobots[i1].y - 1 + *numRows) % *numRows;
                    if (j != 3) {
                        room[myRobots[i1].y][myRobots[i1].x] = myRobots[i1].paintColour;
                    }
                }
            }
            if (myRobots[i1].direction == 1) {
                for (int j = 0;j < 4;j++) {
                    myRobots[i1].x = (myRobots[i1].x + 1) % *numCols;
                    if (j != 3) {
                        room[myRobots[i1].y][myRobots[i1].x] = myRobots[i1].paintColour;
                    }
                }
            }
            if (myRobots[i1].direction == 2) {
                for (int j = 0;j < 4;j++) {
                    myRobots[i1].y = (myRobots[i1].y + 1) % *numRows;
                    if (j != 3) {
                        room[myRobots[i1].y][myRobots[i1].x] = myRobots[i1].paintColour;
                    }
                }
            }
            if (myRobots[i1].direction == 0) {
                for (int j = 0;j < 4;j++) {
                    myRobots[i1].x = (myRobots[i1].x - 1 + *numCols) % *numCols;
                    if (j != 3) {
                        room[myRobots[i1].y][myRobots[i1].x] = myRobots[i1].paintColour;
                    }
                }
            }
            if (room[myRobots[i1].y][myRobots[i1].x] == 1) {
                myRobots[i1].direction = (myRobots[i1].direction + 1) % 4;
            }
            if (room[myRobots[i1].y][myRobots[i1].x] == 2) {
                myRobots[i1].direction = (myRobots[i1].direction + 2) % 4;
            }
            if (room[myRobots[i1].y][myRobots[i1].x] == 3) {
                myRobots[i1].direction = (myRobots[i1].direction + 3) % 4;
            }
            if (room[myRobots[i1].y][myRobots[i1].x] == 4) {
                myRobots[i1].direction = (myRobots[i1].direction) % 4;
            }
            if (room[myRobots[i1].y][myRobots[i1].x] == 5) {
                myRobots[i1].direction = (myRobots[i1].direction + 1) % 4;
            }
            if (room[myRobots[i1].y][myRobots[i1].x] == 6) {
                myRobots[i1].direction = (myRobots[i1].direction + 2) % 4;
            }
            room[myRobots[i1].y][myRobots[i1].x] = myRobots[i1].paintColour;
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