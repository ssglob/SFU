#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES
int loop(int a) {
    for (int i = 0;i<10;i++){
        a --;
    }
    return a;
}
int main() {
    int a = loop(10);
    printf("%d",a);
    return 0;
}
