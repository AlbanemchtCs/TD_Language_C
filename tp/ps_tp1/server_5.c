/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_5.c
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

// Define True and False
#define TRUE 1
#define FALSE 0

bool running = TRUE;

void stop_handler(int sig){
    printf("\n\nReceived signal %d\n", sig);
    running = false;
}

void exit_message(){
     printf("Ending\n");
}

int main() {
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

    char *fifo = "/tmp/ps_tp1_fifo";
    mkfifo(fifo, 0666);

    //  open FIFO for write only
    int fd = open(fifo, O_WRONLY);

    while (running){
        int random_number = rand() % 100;
        write(fd, &random_number, sizeof(random_number));
        sleep(1);
    }

    close(fd);

    if (WIFEXITED(child_status)){
        printf("Child exited with status of %d\n", WEXITSTATUS(child_status));
    } else if (WIFSIGNALED(child_status)){
        printf("Child terminated by signal %d\n", WTERMSIG(child_status));
    }
    return EXIT_SUCCESS;
}

