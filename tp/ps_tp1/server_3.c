/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_3.c
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

/* QUESTIONS
2.1.1. On peut distinguer les messages du père de ceux du fils.
Les deux processus s'arrêtent avec la commande CTRL+C.

2.1.2. En utilisant la commande kill <pid> pour arrêter le processus fils, nous remarquons :
* - En commençant par le kill du fils: le processus fils apparaît toujours avec "ps a", il disparait après le kill du père 
* - En commençant par le kill du père: le processus fils ne s'arrête pas, puis le processus fils disparait en le tuant

2.1.3. En utilisant la fonction wait(), permettant au père d'attendre la mort du fils pour s'éxecuter:
* - Lorsque le fils s'arrête avec la commande CTRL-C, le status affiche 0
* - Lorsque le fils s'arrête avec la commande kill <PID>, le status affiche 0
* - Lorsque le fils s'arrête avec la commande kill -9, le status de fin affiche 9 
*/

bool running = TRUE;

void stop_handler(int sig){
    printf("\nNumber signal received: %d \n", sig);
    running = FALSE; 
}

void exit_message(){
     printf("Ending \n");
}

int main(){

    struct sigaction str; 
    str.sa_handler = &stop_handler; 
    sigemptyset(&str.sa_mask);
    str.sa_flags = 0; 
    sigaction(SIGINT, &str, NULL);
    sigaction(SIGTERM, &str, NULL);
    
    atexit(exit_message);

    printf("Beginning \n");

    // adding fork()
    pid_t pid_fork = fork();

    if (pid_fork == -1){
        perror("fork");
        exit(EXIT_FAILURE);}
    if(pid_fork == 0){
        printf("Child pid: %d\n", getpid());
    }
    else{
        printf("Father pid %d\n", getpid());
        int child_status;
        // adding function wait()
        wait(&child_status);
        printf("Final child status %d\n", child_status);
    }

    while(running){
        int pid = getpid();
        int fatherpid = getppid();
        int random_number = rand() % 100;

        printf("pid: %d \n" , pid);
        printf("father pid: %d \n" , fatherpid);
        printf("randint: %d \n" , random_number);

        sleep(1);
    }
    return EXIT_SUCCESS;
}
