#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void main(int argc, char *argv[]){


//	int q = 1;

    char recebe[3];
    char comando[2000];
  //  sprintf(recebe, "%d", q);
    strcpy(comando, "mpg123 ");
    strcat(comando, argv[1]);
    strcat(comando, ".mp3");
    system(comando);

}