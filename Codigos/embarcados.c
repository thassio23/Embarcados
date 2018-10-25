#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[ ]){  

   FILE *fp;
   int i = 0;
   int armazena;
   int conta = 0;

    char *nome = (char*)malloc(1025*sizeof(char*));

   char **ingredientes = (char**)malloc(1025*sizeof(char*));
    for(int i=0; i<1025; i++){
        ingredientes[i]=(char*)malloc(1025*sizeof(char));
    }

      char **MDP = (char**)malloc(1025*sizeof(char*));
    for(int i=0; i<1025; i++){
        MDP[i]=(char*)malloc(1025*sizeof(char));
   }

    strcpy(nome, "\0");
    for(int o = 1 ; o < argc ;o++){
    if(o == argc){
      break;
    }
    strcat(nome, argv[o]);
    if(o+1 != argc){
    strcat(nome, " ");
   }
   }

   strcat(nome, ".txt");

  printf("%s\n", nome);

   fp = fopen(nome, "r");
  
  while(fgets(ingredientes[i], 1000, fp) != NULL){

  	if(ingredientes[i][15] == ':'){
  		break;
  	}

  conta++;

   i++;
}	

   FILE *fpgrava;
   fpgrava = fopen("ingredientes.txt", "w+");



   for(int i = 1; i<conta;i++){
    fputs(ingredientes[i], fpgrava);
   }

   fclose(fpgrava);  	

   int conta1 = 0;

    char comando[1024];

  while(fgets(MDP[i], 1000, fp) != NULL){
  conta1++;
  

   i++;
}	 		

   FILE *fpgrava1;
   fpgrava1 = fopen("mododepreparo.txt", "w+");



   for(int b = conta; b<conta1+conta;b++){
    fputs(MDP[b], fpgrava1);
   }

   fclose(fpgrava1);

         fclose ( fp );

    return 0;
}

