/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_2.c
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

// Define True and False
#define TRUE 1
#define FALSE 0

bool running = TRUE;

void stop_handler(int sig){
    // function stop handler 
    printf("\n Number signal received: %d \n ", sig);
    running = FALSE; 
}

/* QUESTIONS
1. Le message de stop_handler() s'affiche lorsque l'on utiliser CTRL-C.
2. le message de stop handler() a été affiché en utilisant la commande kill avec l'option -s INT <PID>. 
3. Avec la commande kill <PID>, sans l'option- -s, le message de l'handler ne s'affiche pas. Il faut pour cela rajouter la sigaction avec SIGTERM

4. Avec kill -s KILL <PID> le message de l'handler n'est pas affiché. Avec <FATHERPID> le terminal est fermé. 
Avec un signal SIGKILL par définition de ce type de signal il n'est pas possible de l'intercepter:
"signum specifies the signal and can be any valid signal except SIGKILL and SIGSTOP."
*/

int main()
{
    // structure for sigaction 
    struct sigaction str; 
    str.sa_handler = &stop_handler; 
    sigemptyset(&str.sa_mask);
    str.sa_flags = 0; 
    sigaction(SIGINT, &str, NULL);
    
    printf("Starting program \n");

    while(running){
        int pid = getpid();
        int fatherpid = getppid();
        int random_nub = rand() % 100;

        printf("pid: %d \n" , pid);
        printf("father pid: %d \n" , fatherpid);
        printf("randint: %d \n" , random_nub);

        sleep(1);
    }
    printf("Ending program \n");
    return EXIT_SUCCESS;
}
