#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int i;
    if(argc == 1) {
        printf("usage: args arg1 arg2 arg3 ...\n");
        return 1;
     }    
    if(argc == 2 && strcmp(argv[1],"-v") == 0) {
        printf("args version 1.0, C language course, 2012\n");
        return 2;
    }
    for(i = 0; i < argc; i++)
        printf("%s\n", argv[i]);
    return 0;
}