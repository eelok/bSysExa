#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int parent_id;
    int firstChild_id, secondChild_id;
    int fd[2];
    char kill_instruction[] = "kill";
    char not_Kill[] = "NOT kill";

    parent_id = getpid();

    if(pipe(fd) != 0){
        printf("Error initialising pipe!\n");
        exit(1);
    }

    if ((firstChild_id = fork()) == 0) { //First Child
        firstChild_id = getpid();

        for(int i = 1; i <= 6; i++){
            printf("First Child PID: %d, its Parent ID: %d, i=%d\n", firstChild_id, parent_id,i);
            if(i == 6){
                write(fd[1], kill_instruction, strlen(kill_instruction));
            } else {
                write(fd[1], not_Kill, strlen(not_Kill));
            }
            close(fd[0]);
            sleep(1);
        }
    } else { //Parent Process
        if((secondChild_id = fork())== 0){ //Second Child
            secondChild_id = getpid();
            close(fd[1]);
            while(1) {
                char buffer[10] = " ";
                read(fd[0], buffer, 10);
                printf("Second Child PID: %d, its parent: %d\n", secondChild_id, getppid());
                printf("Second Child: got from first child: %s\n", buffer);
                int res = strcmp(buffer, kill_instruction);
                if(res == 0) {                    
                    printf(">>>>>>First Child killed Second Child<<<<<<<<<\n");
                    kill(secondChild_id, 15);                  
                }
                sleep(1);
            }
        } else {//Parent Process
            for (int i = 1; i < 10; i++){
                printf("Parent ID %d\n", getpid());
                sleep(1);
            }
        }
    }
    return 0;
}