/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_3.c
 */

/* QUESTIONS
2.1.1. On peut distinguer les deux types de messages en fonction du <pid> et <fatherpid>. 
La commande CTRL+C tue les deux processus.

2.1.2. En arrêtant le processus avec kill <pid>:
* - En commençant par le kill du fils: le processus fils est toujours listé avec "ps a", il disparait après le kill du père 
* - En commençant par le kill du père: le processus fils continue d'exister, puis le processus fils disparait en le tuant

2.1.3. En utilisant la fonction wait(), permettant au père d'attendre la mort du fils pour s'executer:
* - Lorsque le fils s'arrête avec la commande CTRL-C, le status finit avec 0
* - Lorsque le fils s'arrête avec la commande kill <PID>, le status finit avec 0
* - Lorsque le fils s'arrête avec la commande kill -9, le status de fin est un 9 
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
     printf("Ending the program \n");
}

int main()
{
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

    if (pid_fork == -1) {
        perror("fork");
        exit(EXIT_FAILURE);}
    if(pid_fork == 0){
        printf("Child process: %d\n", getpid());
    }
    else{
        printf("Father process %d\n", getpid());
        int child_status;
        wait(&child_status);
        printf("Child terminated with status %d\n", child_status);
    }

    while(running){
        int pid = getpid();
        int fatherpid = getppid();
        int random_nub = rand() % 100;

        printf("pid: %d \n" , pid);
        printf("father pid: %d \n" , fatherpid);
        printf("randint: %d \n" , random_nub);

        sleep(1);
    }
    return EXIT_SUCCESS;
}
