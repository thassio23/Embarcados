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


int main(void)
{

        int     fd[2], nbytes;
        int   	pid;
        char    string[20];
        char    readbuffer[80];
        char	comando[12];


      
        pipe(fd);
      

      	signal(SIGUSR1, SetaFlag);
      	signal(SIGUSR2, SetaFlagchild);
        pid = fork();

        if(pid == 0)
        {		

        		while(1){
        		flagchild = 0;
                close(fd[1]);
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));  
                strcpy(comando, "./fala ");
                strcat(comando, readbuffer);
                system(comando);  

                if(flagchild != 1){       
                kill(pid, SIGUSR1);    
                }   

                }

        }
        else	
        {	
        		signal(SIGINT, SIG_IGN); 
                close(fd[0]);
                int 	toca = 0;
        		char 	tocastring[3];
        		char mensagem[10];
    			while(1){
    			scanf("%s", string);

                if(strcmp(string, "leia") == 0 || strcmp(string, "repete") == 0 ){	
                toca = toca;
                }

                if(strcmp(string, "proximo") == 0){	
                toca++;
                }

                if(strcmp(string, "volta") == 0 ){	
                if(toca  == 0){
                toca = toca;
                }else{
                toca--;
            	}
                }

                sprintf(tocastring, "%d", toca);
    			if(flag == 1){	
                kill(0,SIGUSR2);
                }
                flag = 1;
                write(fd[1], tocastring, (strlen(tocastring)+1));
                
      			}


    	}
    
    
    	
    
        
        return(0);
}