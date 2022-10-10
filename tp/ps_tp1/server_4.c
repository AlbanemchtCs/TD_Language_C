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
    printf("\n\nNumber signal received: %d\n", sig);
    running = FALSE; 
}

void exit_message(){
    // function adding an exit message 
     printf("Ending the program\n");
}

int main(){
    printf("Starting program \n");
    atexit(exit_message);

    // structure for sigaction 
    struct sigaction str; 
    str.sa_handler = &stop_handler; 
    if  (sigaction(SIGINT, &str, NULL) < 0){
        perror("Unable to register SIGINT");
        return EXIT_FAILURE;
    }
    sigaction(SIGTERM, &str, NULL);

    // wait for child process
    int child_status;
    wait(&child_status);

    // create a pipe
    int pipefd[2];
    pipe(pipefd);
    
    int buf;

    // fork function
    pid_t pid_fork = fork();

    while(running){
        if (pid_fork == 0){
            close(pipefd[1]);
        
            if (read(pipefd[0], &buf, sizeof(buf)) > 0){
                int pid = getpid();
                int fatherpid = getppid();
                printf("\nChild process : %d\n", pid);
                printf("Parent process : %d\n", fatherpid);
                printf("Le nombre aléatoire récupéré par le fils: %d\n", buf);
            } else{
                break;
            }
        } else{
            close(pipefd[0]);
            int random_nub = rand() % 100;
            write(pipefd[1], &random_nub, sizeof(buf));
            sleep(1);
            }
        }
        close(pipefd[0]); 
        close(pipefd[1]);

        if (WIFEXITED(child_status)){
        printf("Child exited with status of %d\n", WEXITSTATUS(child_status));
        } else if (WIFSIGNALED(child_status)){
        printf("Child terminated by signal %d\n", WTERMSIG(child_status));
        }
        return EXIT_SUCCESS;
    }
