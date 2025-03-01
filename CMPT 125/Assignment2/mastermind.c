#include <stdio.h>
#include <stdlib.h>
#define MAX_TURNS 20
#define MAX_NUM 5

/*This program takes user input and uses it as a seed to generate 6 pseudo-random numbers that are between 0 and 5 inclusive. The program then prompts the user to guess the 6 digits,
and prints how many matches and partial matches the user got. If the user cannot get the numbers in 20 tries then the program prints something to signal that the game ended, and if 
the user gets all 6 numbers then the program prints a victory message. In both cases the program terminates.*/

int compare_array(int* arr1, int* arr2) {
    for (int i = 0;i < 6;i++){
        if (arr1[i] != arr2[i]){
            return 0;
        }
    }
    return 1;
}

void reset_array(int* arr) {
    for (int i = 0;i < 6;i++){
        arr[i] = 0;
    }
}

int* check_guess(int* digits_left) {
    int cur_num = 10;
    int* checked;
    int i = 0;
    char c = ' ';
    while (c==' ' || c=='\t'){
        c = getchar();
    }
    checked = malloc(6*sizeof(int));
    if (!checked) {
        return NULL;
    }
    for (int i = 0; i < 6; i++) {
        checked[i] = -1; /*Want to know when adding numbers to guess, if the number is valid*/
    }
    while(c != '\n' && i < *digits_left) {
        if (c >= '0' && c <='9') {
            cur_num = c - '0';
        }
        if (cur_num > 5){
            checked[0] = cur_num;
            /*clear input*/
            while ((c = getchar()) != '\n' && c != EOF);
            return checked;
        }
        checked[i] = cur_num;
        cur_num = 10;
        i++;
        c = ' ';
        while (c==' ' || c=='\t'){
            c = getchar();
        }
    }
    if (i > 0 && i <= *digits_left){
        *digits_left -= i;
    }
    if (c == '\n'){
        return checked;
    }
    /*clear input*/
    while ((c = getchar()) != '\n' && c != EOF);
    return checked;
}

void removes(int* arr, int index) {
    int i = 0;
    for (i = index;i < 5;i++){
        if (arr[i] < 0) {
            if (i>0) {
                i--;
            }
            break;
        }
        arr[i] = arr[i+1];
    }
    arr[i] = -1;
}

int in(int* arr, int num) {
    for (int i = 0;i < 6;i++){
        if (arr[i] < 0) {
            return -1;
        }
        if (arr[i] == num) {
            return i;
        }
    }
    return -1;
}

int* matches(int* arr1, int* arr2) {
    /*take two arrays and return pointer to first element of an array containing #exact/partial matches*/
    /*exact then partial*/
    int nums1[6];
    int nums2[6];
    int index1 = 0;
    int index2 = 0;
    int* num_match = (int*)calloc(2, sizeof(int));
    /*copy arr1 and arr2 into nums1 and nums2*/
    for (int i = 0;i < 6;i++){
        nums1[i] = arr1[i];
        nums2[i] = arr2[i];
    }
    for (int i = 0;i < 6;i++) {
        if (arr1[i] == arr2[i]) {
            num_match[0]++;
            removes(&nums1[0],in(&nums1[0],arr1[i]));
            removes(&nums2[0],in(&nums2[0],arr2[i]));
            continue;
        }
        index1 = in(&nums1[0],arr2[i]);
        index2 = in(&nums2[0],arr2[i]);
        if (index1 != -1 && index2 != -1) {
            num_match[1]++;
            removes(&nums1[0],index1);
            removes(&nums2[0],index2);
        }
        index1 = in(&nums2[0],arr1[i]);
        index2 = in(&nums1[0],arr1[i]);
        if (index1 != -1 && index2 != -1) {
            num_match[1]++;
            removes(&nums2[0],index1);
            removes(&nums1[0],index2);
        }
    }
    return num_match;
}

int main(){
    int initSeed = 0;
    int solution[] = {0,0,0,0,0,0};
    int turn = 0;
    int guess[] = {0,0,0,0,0,0};
    int digits_left = 6;
    int iter = 0;
    int* check;
    int guesses[20][8]; /*6 for the guess, 2 for partial/exact matches*/
    int* match;
    int reenter = 0;
    int start = 1;
    for(int i = 0;i < 20;i++){
        for(int i1 = 0;i1 < 8;i1++) guesses[i][i1] = -1; 
    }
    printf("Enter the integer value of the seed for the game: ");
    scanf("%d",&initSeed);
    while(getchar() != '\n'); /*clear stdin*/
    srand(initSeed);
    for (int i = 0;i < 6;i++){
        solution[i] = rand() % MAX_NUM;
    }
    printf("For each turn enter 6 digits 0 <= digit <= 5 \n");
    printf("Spaces or tabs in your response will be ignomagenta. \n\n");
    while((compare_array(&solution[0],&guess[0]) == 0) && (turn != MAX_TURNS)){
        reset_array(&guess[0]);
        printf("Enter your guess, 6 digits \n");
        for(int i = 0;i < 20;i++){
            if (guesses[i][0] < 0) {
                break;
            }
            printf("Previous guess %d: ",i+1);
            for (int i1 = 0;i1 < 6;i1++) printf("%d ",guesses[i][i1]);
            printf("- %d matches %d partial matches\n",guesses[i][6],guesses[i][7]);
        }
        while (digits_left>0){
            if (!start){
                if (reenter) {
                    printf("Reenter your guess, %d digits\n",digits_left);
                }
                else {
                    if (digits_left == 6){
                        printf("Enter your guess, 6 digits \n");
                    }
                    else {
                        printf("You need to enter %d more digits to complete your guess \n",digits_left);
                    }
                }
                
            }
            else start = 0;
            check = check_guess(&digits_left);
            if (check[0]<=5){
                for(int i = 0;i < 6;i++){
                    if (iter>5 || check[i]<0) {
                        break;
                    }
                    guess[iter] = check[i];
                    iter++;
                }
            }
            else{
                if (check[0] == 10){
                    printf("ERROR: A character in your guess was not a digit or a white space\n");
                }
                else{
                    printf("ERROR: A character in your guess was a digit that was too large\n");
                }
                reenter = 1;
            }
            free(check);
        }
        reenter = 0;
        digits_left = 6;
        for (int i = 0; i < 6; i++){
            guesses[turn][i] = guess[i];
        }
        match = matches(&guess[0],&solution[0]);
        printf("%d matches %d partial matches\n\n",match[0],match[1]);
        guesses[turn][6] = match[0]; /*exact*/
        guesses[turn][7] = match[1]; /*partial*/
        free(match);
        turn++;
        iter = 0;
    }
    if (compare_array(&solution[0],&guess[0]) == 1) {
        printf("YOU DID IT!!");
    }
    else printf("GAME OVER: NO MORE TURNS");
    return 0;
}