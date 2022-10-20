/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_6.c
 */

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>
// For boolean
#include <stdbool.h> 
// For signal action
#include <signal.h>
// For duplication
#include <unistd.h>
// For wait
#include <sys/wait.h>
// For fifo
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
// For TCP
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
// For bzero
#include <strings.h>

// Define True and False
#define TRUE 1
#define FALSE 0

#define MAX 80
#define PORT 8888
#define SA struct sockaddr

bool running = TRUE;

void stop_handler(int sig){
    printf("\n\nReceived signal %d\n", sig);
    running = false;
}

void exit_message(){
     printf("Ending\n");
}

int main(){
    printf("Beginning \n");
    atexit(exit_message);

    struct sigaction str; 
    str.sa_handler = &stop_handler; 
    if  (sigaction(SIGINT, &str, NULL) < 0){
        perror("Unable to register SIGINT");
        return EXIT_FAILURE;
    }
    sigaction(SIGTERM, &str, NULL);
    sigaction(SIGPIPE, &str, NULL);

    int child_status;
    wait(&child_status);

    int socket_desc, client_sock, random_number;
    struct sockaddr_in server, client;

    // Create socket function
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1){
        perror("\nCould not create socket\n");
        return EXIT_FAILURE;
    } else{
        printf(" - Socket created\n");
    }

    bzero(&server, sizeof(server));

    // prepare the sockadrr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  
    server.sin_port = htons(PORT);

    // Connect to remote server
    if (connect(socket_desc, (SA*)&server, sizeof(server))){
        perror("\nConnect failed. Error\n");
        return EXIT_FAILURE;
    } else{
        printf(" - Connected\n");
    }

    while (running){
        // Read data from server
        if (read(socket_desc, &random_number, sizeof(random_number)) > 0) {
            printf("Random number retrieved by the server: : %d\n", random_number);
        } else{
            break;  
        }
    }

    close(socket_desc);

    if (WIFEXITED(child_status)){
        printf("Child exited with status of %d\n", WEXITSTATUS(child_status));
    } else if (WIFSIGNALED(child_status)){
        printf("Child terminated by signal %d\n", WTERMSIG(child_status));
    }
    return EXIT_SUCCESS;
}
