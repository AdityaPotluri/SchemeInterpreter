#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

// defines all the different built in types in scheme
typedef enum {FIXNUM,BOOLEAN} object_type;

// defines the structure for all the different objects and their data
typedef struct object {
    object_type type;
    union {
        struct {
            long value;
        } fixnum;

        struct {
            bool value;
        } boolean;
    } data;
} object;




// allocates memory for the object (no garbage collection)
object* alloc_object(void) {
    object *obj;
    obj = malloc(sizeof(object));
    if(obj == NULL) {
        fprintf(stderr, "Out of Memory Lol\n");
        exit(1);
    }
    return obj;
}

object* make_boolean(bool b) {
    object* obj;
    obj = alloc_object();
    obj->type = BOOLEAN;
    obj->data.fixnum.value = b;
}


// the "constructor" for the fixnum type (integers basically)
object* make_fixnum(long value) {
    object* obj;
    obj = alloc_object();
    obj->type = FIXNUM;
    obj->data.fixnum.value = value;
    return obj;
}

bool isBool(object *obj) {
    return obj->type == BOOLEAN;
}

bool isTrue(object *obj) {
    return obj->data.boolean.value == true;
}

bool isFalse(object *obj) {
    return obj->data.boolean.value == false;
}

//just says if its a fixnum
bool isFixNum(object *obj) {
    return obj->type == FIXNUM;
}

//just says if it is a delimeter
bool is_delimiter(int c) {
    return (isspace(c) || c == ')' || c == '(' || c == ';' || c == '"' || c == EOF);
}

// reads from the top of a file
int peek(FILE *in) {
    int c;
    c = getc(in);
    ungetc(c,in);
    return c;
}

//removes all the whitespace from being read by the translator
void eatWhitespace(FILE *in) {
    int c;
    while((c = getc(in)) != EOF){

        if(isspace(c)) {
            continue;
        }

        else if(c == ';') {
            while(((c = getc(in)) != EOF) && (c != '\n'));
            continue;
            
        }
        ungetc(c,in);
        break;
    }
    
}


object *false_val;
object *true_val;
void init() {
    false_val = alloc_object();
    false_val->type = BOOLEAN;
    false_val->data.boolean.value = false;

    true_val = alloc_object();
    true_val->type  = BOOLEAN;
    true_val->data.boolean.value  = true;
}
// The read in Read Evalute Print Loop
object* read(FILE *in) {
    int c;
    short sign = 1;
    long num = 0;

    eatWhitespace(in);

    c = getc(in);    

    if (isdigit(c) || (c == '-' && (isdigit(peek(in))))) {
        /* read a fixnum */
        if (c == '-') {
            sign = -1;
        }
        else {
            ungetc(c, in);
        }
        while (isdigit(c = getc(in))) {
            num = (num * 10) + (c - '0');
        }
        num *= sign;
        if (is_delimiter(c)) {
            ungetc(c, in);
            return make_fixnum(num);
        }
        else {
            fprintf(stderr, "number not followed by delimiter\n");
            exit(1);
        }
    }

    if(c == '#') {
        c = getc(in);
        switch (c)
        {
        case 't':
            return true_val;
        case 'f':
            return false_val;
        default:
            fprintf(stderr, "unknown boolean literal\n");
            exit(1);
        }
    }
    else {
        fprintf(stderr, "bad input. Unexpected '%c'\n", c);
        exit(1);
    }
    fprintf(stderr, "read illegal state\n");
    exit(1);
}

//the eval in read eval print line
object* eval(object *exp) {
    return exp;
}

// the print in read eval print line
void write(object *obj) {
    switch (obj->type) {
        case FIXNUM:
            printf("%ld", obj->data.fixnum.value);
            break;
        case BOOLEAN:
            printf("#%c ", obj->data.boolean.value ? 't' : 'f' );
        default:
            fprintf(stderr, "cannot write unknown type\n");
            exit(1);
    }
}


int main(void) {
   printf("Scheme Bootstrap! press Ctrl ^c to to exit\n");
   init();
   while(1) {
       printf(">");
       write(eval(read(stdin)));
       printf("\n");
   }

   return 0;
}


