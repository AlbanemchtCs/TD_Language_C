/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_4.c
 */

/* QUESTIONS
2.2.1. L'arrêt est bien correct avec CTRL-C, ainsi qu'avec un kill sur le fils puis sur le père ou l'inverse.
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


// Define True and False
#define TRUE 1
#define FALSE 0

bool running = TRUE;

void stop_handler(int sig){
    // function stop handler 
    printf("\nNumber signal received: %d \n", sig);
    running = FALSE; 
}

void exit_message(){
    // function adding an exit message 
     printf("\nEnding the program \n");
}

int main()
{
    int pipefd[2];
    int buf;
    if (pipe(pipefd) == -1)
    {
        exit(EXIT_FAILURE);
    }

    // structure for sigaction 
    struct sigaction str; 
    str.sa_handler = &stop_handler; 
    sigemptyset(&str.sa_mask);
    str.sa_flags = 0; 
    sigaction(SIGINT, &str, NULL);
    // adding SIGTERM signal 
    sigaction(SIGTERM, &str, NULL);
    
    atexit(exit_message);


    printf("Starting program \n");

    pid_t pid_fork = fork();

    if (pid_fork == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid_fork == 0){
        printf("Child process: %d\n", getpid());
        close(pipefd[1]);

        while (running && read(pipefd[0], &buf, sizeof(int)) > 0){
            //Lecture du nombre aléatoire puis affichage du message
            printf("\nLe nombre aléatoire récupéré par le fils: %d", buf);
        }  
        close(pipefd[0]);
        
    }
    else{
        printf("Father process %d\n", getpid());
        close(pipefd[0]);

        while(running){
            int pid = getpid();
            int fatherpid = getppid();
            int random_nub = rand() % 100;
            if (!write(pipefd[1], &random_nub, sizeof(int))){
                return EXIT_FAILURE;
            }
            sleep(1);
        }
        close(pipefd[1]);
        int child_status;
        wait(&child_status);
        printf("Child terminated with status %d\n", child_status);
    }
    return EXIT_SUCCESS;
}
