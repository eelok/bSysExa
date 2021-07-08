#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int firstChild_id, secondChild_id;
    int fd[2];
    int bufferSize = 1024;

    if(argc < 2){
        printf("Error. Please insert 2 command line arguments\n");
        exit(1);
    }

    if(pipe(fd) == -1){
        printf("Error initialising pipe!\n");
        exit(1);
    }

    if ((firstChild_id = fork()) == 0) { //First Child
        char buffer[bufferSize];
        
        int fileDescriptor = open(argv[1], O_RDONLY);
        if(fileDescriptor < 0){
            printf("Failed to open the file\n");
            exit(1);
        }
      
        int numOfBytes = read(fileDescriptor, buffer, bufferSize);//reads from file
        write(fd[1], buffer, numOfBytes);//writes to pipe

        close(fd[0]);
    } else { //Parent Process
        if((secondChild_id = fork())== 0){ //Second Child
            char buff[bufferSize];

            int fileDescriptor = open("outputfile.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IXUSR);
            if(fileDescriptor == -1){
                printf("Failed to open the file\n");
                exit(1);
            }

            int numOfBytes = read(fd[0], buff, bufferSize);
            write(fileDescriptor, buff, numOfBytes);
            close(fd[1]);
        }
    }
    return 0;
}