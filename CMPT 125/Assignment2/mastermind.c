#include <stdio.h>
#include <stdlib.h>
#define MAX_TURNS 20
#define MAX_NUM 10

int compare_array(int* arr1, int* arr2){
    for (int i = 0;i < 6;i++){
        if (arr1[i] != arr2[i]){
            return 0;
        }
    }
    return 1;
}

void reset_array(int* arr){
    for (int i = 0;i < 6;i++){
        arr[i] = 0;
    }
}

int* check_guess(int* digits_left){
    int cur_num = 10; /*if scanf is invalid cur_num will still be 10*/
    int* checked;
    int i = 0;
    char c;
    scanf(" %c",&c);
    checked = malloc(6*sizeof(int));
    if (!checked) return NULL;
    for (int i = 0; i < 6; i++) {
        checked[i] = 10;
    }
    printf("1 ");
    while(c != '\n' && i < *digits_left){
        printf("%c ",c);
        cur_num = c - '0';
        if (cur_num > 5){
            checked[0] = cur_num;
            /*clear input*/
            while (c!='\n' && c != EOF){
                scanf(" %c",&c);
            }
            return checked;
        }
        printf("2 ");
        checked[i] = cur_num;
        cur_num = 10;
        i++;
        scanf(" %c",&c);
    }
    printf("3y");
    if (c == '\n'){
        if (i>0){
            *digits_left -= i-1;
        }
        printf("3.25");
    }
    /*clear input*/
    printf("%c",c);
    while (c!='\n' && c != EOF){
        printf("3.5");
        scanf("%c",&c);
    }
    printf("4");
    return checked;
}

int main(){
    int initSeed = 0;
    int solution[6] = {0,0,0,0,0,0};
    int turn = 1;
    int guess[6] = {0,0,0,0,0,0};
    int digits_left = 6;
    int prev_guess_num = 0;
    int iter = 0;
    printf("Enter the integer value of the seed for the game: ");
    scanf("%d",&initSeed);
    srand(initSeed);
    for (int i = 0;i < 6;i++){
        solution[i] = rand() % MAX_NUM;
        printf("%d",solution[i]);
    }
    printf("For each turn enter 6 digits 0 <= digit <= 5 \n");
    printf("Spaces or tabs in your response will be ignomagenta. \n\n");
    while((compare_array(&solution[0],&guess[0]) == 0) && (turn != MAX_TURNS)){
        while (digits_left>0){
            if (digits_left == 6){
                printf("Enter your guess, 6 digits \n");
            }
            else {
                printf("You need to enter %d more digits to complete your guess \n",digits_left);
            }
            int* check = check_guess(&digits_left);
            if (check[0]<=5){
                while(check[iter]){
                    guess[iter] = check[iter];
                    iter++;
                }
                iter = 0;
            }
            else{
                if (check[0] == 10){
                    printf("ERROR: A character in your guess was not a digit or a white space\n");
                }
                else{
                    printf("ERROR: A character in your guess was a digit that was too large\n");
                }
            }
            free(check);
        }
        for (int i=0;i<6;i++){
            printf("%d",guess[i]);
        }
        digits_left = 6;
        reset_array(&guess[0]);
        turn++;
    }
    return 0;
}