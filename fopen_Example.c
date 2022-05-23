#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



FILE *file;

int main(void)
{

    //file = fopen("c:\\Holis.txt","rt");
    file = fopen("D:\\Armando\\Desktop\\Holi.txt","rt");

    if(file == NULL) { 

        
        printf("%s\n", strerror(errno));

        // switch(errno) {
        // case ENOENT: //printf("The file doesn't exist\n"); 
        //             break;
        // case EMFILE: printf("You've opened too many files\n"); 
        //             break;
        // default:     printf("The error number is %d\n",errno);
        // }
    }
    else
        printf("File found!! :)");
}