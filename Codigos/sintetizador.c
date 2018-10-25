#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *funcao(void *parametro){

 	 char *arg = malloc(sizeof(char)*2048);
 	 arg = (char*)parametro;
	 printf("%s\n", arg);

	 system(arg);
}

int main(int argc, char *argv[]){

   FILE *fp;
   char buff[1024];
   fp = fopen("mododepreparo.txt", "r");
   int tamanho = atoi(argv[1]);
   char buffer[1024];
   char *recebe[tamanho]; 	
   char *comando[2048];

   for(int i = 0; i<tamanho; i++){
   recebe[i] = malloc(sizeof(char)*1024);
   comando[i] = malloc(sizeof(char)*2048);
   }
	for(int i = 0; i<tamanho-1; i++){
	   fgets(recebe[i], 1024, (FILE*)fp);
	}
	fclose(fp);
		char numberstring[3];
        for(int i = 0; i<tamanho;i++){
        strcpy(comando[i], "gtts-cli \"");
        strcat(comando[i], recebe[i]);
        strcat(comando[i], "\" --lang pt-br -o ");
        sprintf(numberstring, "%d", i);
        strcat(comando[i], numberstring);
        strcat(comando[i], ".mp3");
   		}



   	pthread_t tid[tamanho];
	pthread_attr_t attr[tamanho];

	for(int i = 0; i<tamanho-1;i++){
	pthread_attr_init(&attr[i]);
	pthread_create(&tid[i],&attr[i],funcao,comando[i]);

	}

	for(int i = 0; i<tamanho-1;i++){
	pthread_join(tid[i], NULL);
	}

}