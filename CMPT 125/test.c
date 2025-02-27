#include <stdio.h>
void reset_array(int* arr){
    for (int i = 0;i < 6;i++){
        arr[i] = 0;
    }
}
int main(){
    int c[6] = {1,1,1,1,1,1};
    reset_array(&c[0]);
    for(int i = 0;i < 6;i++){
        printf("%d",c[i]);
    }
    return 0;
}