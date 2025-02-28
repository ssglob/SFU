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

int main(){
    char* inputfile;
    char c = ' ';
    char input;
    char buff[50];
    char outputfile[50];
    int len = 10;
    int iter = 0;
    int iter1 = 0;
    int file_open_count = 0;
    int arr[] = {-1,-1,-1,-1,-1,-1,-1}; /*Inputs can't be less than 0 so if it is then we know it's invalid*/
    int** room = calloc(1,sizeof(int*));
    int* numRows = &arr[0];
    int* numCols = &arr[1];
    int* numRobots = &arr[2];
    int* initTypeValue = &arr[3];
    int* initSeed = &arr[4];
    int* numIterations = &arr[5];
    int* interval = &arr[6];
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
            arr[iter] = (int)buff;
            if (arr[iter] == -1) {
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
            for (int i = 0;i < 7;i++) {
                if (iter == 0) {
                    if (arr[iter] > numRowsUpper || arr[iter] < numRowsLower) {
                        fprintf(stderr,"ERROR: The number of rows was outside the specified range (%d to %d inclusive)\n",numRowsLower,numRowsUpper);
                        return 0;
                    }
                }
                if (iter == 1) {
                    if (arr[iter] > numColsUpper || arr[iter] < numColsLower) {
                        fprintf(stderr,"ERROR: The number of columns was outside the specified range (%d to %d inclusive)\n",numColsLower,numColsUpper);
                        return 0;
                    }
                }
                if (iter == 2) {
                    if (arr[iter] > numRobotsUpper || arr[iter] < numRobotsLower) {
                        fprintf(stderr,"ERROR: The number of robots was outside the specified range (%d to %d inclusive) \n",numRobotsLower,numRobotsUpper);
                        return 0;
                    }
                }
                if (iter == 3) {
                    if (arr[iter] > initTypeValueUpper || arr[iter] < initTypeValueLower) {
                        fprintf(stderr,"ERROR: The initialization type was outside the specified range (%d to %d inclusive)\n",initTypeValueLower,initTypeValueUpper);
                        return 0;
                    }
                }
                if (iter == 4) {
                    if (arr[iter] > initSeedUpper || arr[iter] < initSeedLower) {
                        fprintf(stderr,"ERROR: The initialization seed was outside the specified range (%d to %d inclusive) \n",initSeedLower,initSeedUpper);
                        return 0;
                    }
                }
                if (iter == 5) {
                    if (arr[iter] > numIterationsUpper || arr[iter] < numIterationsLower) {
                        fprintf(stderr,"ERROR: The number of iterations was outside the specified range (%d to %d inclusive)\n",numIterationsLower,numIterationsUpper);
                        return 0;
                    }
                }
                if (iter == 6) {
                    const int intervalUpper = arr[5];
                    if (arr[iter] > intervalUpper || arr[iter] < intervalLower) {
                        fprintf(stderr,"ERROR: The print interval was outside the specified range (%d to %d inclusive)\n",intervalLower,intervalUpper);
                        return 0;
                    }
                }
                return 0;
                }
            memset(buff,0,sizeof(buff));
            iter++;
            iter1 = 0;
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
    room = realloc(room, *numRows*sizeof(int*));
    room;
    return 0;
}