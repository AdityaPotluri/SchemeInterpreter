#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

typedef enum {FIXNUM} object_type;
typedef struct object {
    object_type type;
    union {
        struct {
            long value;
        } fixnum;
    } data;
} object;

object *alloc_object(void) {
    object *obj;
    obj = malloc(sizeof(object));
    if(obj == NULL) {
        fprintf(stderr, "Out of Memory Lol\n");
        exit(1);
    }
    return obj;
}

object *make_fixnum(long value) {
    object* obj;
    obj = alloc_object();
    obj->type = FIXNUM;
    obj->data.fixnum.value = value;
    return obj;
}
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
   while(1) {

   }
}


