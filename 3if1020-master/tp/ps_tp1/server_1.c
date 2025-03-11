/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_1.c
 * cc -o server_1 server_1.c
 */

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>

int main()
{
    printf("Starting random number generator...\n");

    while (1) {
         printf("PID: %d, PPID: %d, PGID: %d\n", getpid(), getppid(), getpgrp());
        
         int random_number = rand() % 100;
        printf("Random Number: %d\n", random_number);
        
         sleep(1);
    }

     printf("Ending program.\n");


        
    return EXIT_SUCCESS;
}

// Partie question

//Le processus server 1 a un processus pere 1280
// Chaque processus a un numero de groupe unique