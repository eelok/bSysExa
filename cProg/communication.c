#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int parent_id;
    int firstChild_id, secondChild_id;
    int fd[2];
    int bufferSize = 1024;

    parent_id = getpid();

    if(argc < 2){
        printf("Insert 2 command line arguments");
        exit(1);
    }

    if(pipe(fd) != 0){
        printf("Error initialising pipe!\n");
        exit(1);
    }

    if ((firstChild_id = fork()) == 0) { //First Child
        firstChild_id = getpid();
        printf("First Child PID: %d, its Parent ID: %d\n", firstChild_id, parent_id); 
        char buffer[bufferSize];
        int fileDesciptorIn = open(argv[1], O_RDONLY);

        if(fileDesciptorIn < 0){
            printf("Error open a file\n");
            exit(2);
        }
      
        int numOfBytes = read(fileDesciptorIn, buffer, bufferSize);//reads from file
        write(fd[1], buffer, numOfBytes);//writes to pipe
        printf("First Child read from file: %s\n", buffer);
        close(fd[0]);
    } else { //Parent Process
        if((secondChild_id = fork())== 0){ //Second Child
            char buff[bufferSize];
            secondChild_id = getpid();
            printf("Second Child PID: %d, its parent: %d\n", secondChild_id, getppid());
            int fileDescriptor = open("outputfile.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IXUSR);
            int nread = read(fd[0], buff, bufferSize);
            write(fileDescriptor, buff, nread);
            close(fd[1]);
            
        } else {//Parent Process
            printf("Parent ID %d\n", getpid());
        }
    }
    return 0;
}