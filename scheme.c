#include<stdio.h>
#include<stdbool.h>

bool isInteger(char c) {
    int digits[10] = {0,1,2,3,4,5,6,7,8,9};
    for(int i = 0; i <10; i++) {
        if((c-48) == digits[i]) {
            return true;
        }
    }
    return false;
}


int main() {
    char c;
    while((c = getchar()) != EOF) {
        printf("%d ",isInteger(c));
    }
}


