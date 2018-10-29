#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int flag = 0;
int flagchild = 0;

void SetaFlagchild(){
	flagchild = 1;
	kill(0,SIGINT);
}
void SetaFlag(){
flag = 0;
}

const char * LerVoz()
{
	FILE *f; 
	char text[130];
	static char  trat[8], cmp[130];
	
	strcpy(text,"semorde");
	strcpy(trat,"semorde");
	
	
	f = fopen("/var/log/syslog","r");		//ABRE O SYSLOG
	fseek(f, -130, SEEK_END);				//COLOCA O CURSOR DE LEITURA NO FINAL DO ARQUIVO E VOLTA 130 POSIÇÕES
		
	fgets(text, 130, f);					//COPIA OS 130 ULTIMOS CARACTERES

	fclose(f);

	if(strcmp(text,cmp) == 0)				//COMPARA PRA N EXCUTAR ORDENS REPETIDAS
		return "semorde";
		
	strcpy(cmp,text);
	strcpy(trat, &text[122]);				//PEGA SÓ A PARTE DA ORDEM DO STRING
	

	
	if(strcmp(trat,"proximo") == 0)			//RETORNA APENAS A INFORMAÇÃO DESEJADA
		return trat;	
	if(strcmp(trat,"voltaaa") == 0)
		return trat;
	if(strcmp(trat,"repetee") == 0)
		return trat;
	if(strcmp(trat,"ler1234") == 0)
		return trat;
	if(strcmp(trat,"para123") == 0)
		return trat;
	else
		return "semorde";					//IGNORA POSSIVEIS MENSAGENS NO SYSLOG

}


int main(void)
{

        int     fd[2], nbytes;
        int   	pid;
        char    string[20], para[20];
        char    readbuffer[80];
        char	comando[12];


      
        pipe(fd);
      

      	signal(SIGUSR1, SetaFlag);
      	signal(SIGUSR2, SetaFlagchild);
        pid = fork();

        if(pid == 0)
        {		
        		while(1)
        		{
        		flagchild = 0;
                close(fd[1]);
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer)); 
                
                if (strcmp(readbuffer,"90") == 0)
					exit(0);
                
                   strcpy(comando, "mpg123 ");
  		   strcat(comando, readbuffer);
   		   strcat(comando, ".mp3");
                   system(comando); 					//AKI ELA FALA

                if(flagchild != 1)     
					kill(pid, SIGUSR1);    
 

                }
              

        }
        else	
        {	
				signal(SIGINT, SIG_IGN); 
                close(fd[0]);
                int 	toca = 0;
        		char 	tocastring[3];
        		char mensagem[10];
    			while(1)
    			{
					while(1)
					{
						strcpy(string,"semorde");
						strcpy(string,LerVoz());				// GUARDA A ORDEM EM UM VETOR DENOTRO DA MAIN
						strcpy(para, string);
						sleep(1);
						if(strcmp(string, "proximo") == 0 || strcmp(string, "repetee") == 0 || strcmp(string, "ler1234") == 0 || strcmp(string, "para123") == 0 || strcmp(string, "voltaaa") == 0)
						break;

					}
					
				if(strcmp(string,"semorde") != 0)
				{
					
					
					if(strcmp(string, "ler1234") == 0 || strcmp(string, "repetee") == 0 ){	
						toca = toca;
						strcpy(string,"x");
					}
					if(strcmp(string, "proximo") == 0){
						toca++;
						strcpy(string,"x");
					}
					if(strcmp(string, "para123") == 0){
						toca = 90;
						strcpy(string,"x");
					}
					if(strcmp(string, "voltaaa") == 0 )
					{	
						if(toca  == 0){
							toca = toca;
							strcpy(string,"x");
						}else{
							toca--;
							strcpy(string,"x");
							}
					}
					strcpy(string,"semorde");
				}
                sprintf(tocastring, "%d", toca);
    			if(flag == 1)
					kill(0,SIGUSR2);
                flag = 1;
                if(strcmp(string,"semorde") != 1)
					write(fd[1], tocastring, (strlen(tocastring)+1));
				
				
				if(strcmp(para,"para123") == 0)
				{
					sleep(1);
					exit(0);
				}	
                strcpy(string,"semorde");
               
                sleep(20);
      			}


    	}
    
    
    	
    
        
        return(0);
}
