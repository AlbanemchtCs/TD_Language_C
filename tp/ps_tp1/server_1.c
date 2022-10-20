/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_1.c
 */

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>

// Define True and False
#define TRUE 1
#define FALSE 0


int main()
{
    printf("Beginning \n");

    while(TRUE){
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

