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

/* QUESTIONS
1. Le message de stop_handler() s'affiche lorsque l'on utilise CTRL-C.
2. le message de stop handler() a été affiché en utilisant la commande kill avec l'option -s INT <PID>. 
3. Avec la commande kill <PID>, sans l'option -s, le message de l'handler ne s'affiche pas. Il faut pour cela rajouter la sigaction avec SIGTERM

4. Avec kill -s KILL <PID> le message de stop_handler() ne s'affiche pas. Avec <FATHERPID> le terminal se ferme. 
Ce signal est de type SIGKILL, il n'est donc pas possible de l'intercepter: "signum specifies the signal and can be any valid signal except SIGKILL and SIGSTOP."

5. Lorsque l'on enlève la variable running, les commandes CTLR + C et kill <PID> sont reçus (message affiché) mais le processus en cours ne s'arrête pas.
Avec la commande kill -9 <PID>, le programme s'arrête bien. 

6. La fonction exit_message() est bien activée quand le programme est arrêté avec les commandes CTRL+C et kill. 
Néanmoins, avec la commande kill -9, le message de sortie n'est pas affiché.
*/

bool running = TRUE;

// function stop_handler 
void stop_handler(int sig){
    printf("\nNumber signal received: %d \n", sig);
    running = FALSE; 
}

// function exit_message 
void exit_message(){
     printf("Ending \n" );
}

int main(){

    // structure for sigaction 
    struct sigaction str; 
    str.sa_handler = &stop_handler; 
    sigemptyset(&str.sa_mask);
    str.sa_flags = 0; 
    sigaction(SIGINT, &str, NULL);
    sigaction(SIGTERM, &str, NULL);
    
    atexit(exit_message);

    printf("Beginning \n");

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
