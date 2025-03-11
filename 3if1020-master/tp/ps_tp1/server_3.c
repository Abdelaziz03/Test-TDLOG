/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_3.c
 * cc -o server_3 server_3.c
 */

// Commencer par recopier ici le code de server_2.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>

// Variable volatile globale pour gérer l'état de la boucle
volatile bool running = true;

// Gestionnaire de signaux pour SIGINT et SIGTERM
void stop_handler(int sig) {
    printf("Signal détecté : %d\n", sig);
    printf("Le serveur va s'arrêter...\n");
    running = false;
}

// Fonction pour afficher un message de conclusion
void exit_message() {
    printf("Fonction exit_message() : Fin du programme en cours...\n");
}

int main() {
    // Configuration du gestionnaire de signaux pour SIGINT et SIGTERM
    struct sigaction sa;
    sa.sa_handler = stop_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Erreur lors de la mise en place du gestionnaire de signaux");
        exit(EXIT_FAILURE);
    }

    // Enregistrement de la fonction exit_message() pour exécution à la fin
    if (atexit(exit_message) != 0) {
        perror("Erreur lors de l'enregistrement de exit_message");
        exit(EXIT_FAILURE);
    }

    printf("Le serveur est en fonctionnement...\n");

    while (running) {
        // Affiche l'identifiant du processus, celui de son parent et de son groupe
        printf("Identifiant du processus : %d\n", getpid());
        printf("Identifiant du processus parent : %d\n", getppid());
        printf("Identifiant du groupe de processus : %d\n", getpgrp());

        // Génération d'un nombre aléatoire entre 0 et 99
        srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
        int random_number = rand() % 100;
        printf("Nombre généré : %d\n", random_number);

        // Pause de 1 seconde
        sleep(1);
    }
        // Crée un processus fils
    pid_t child_pid = fork();

        if (child_pid < 0) {
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Code du fils
        printf("Serveur en cours d'exécution (fils)...\n");
    }

    printf("Le serveur a terminé son exécution.\n");
    return EXIT_SUCCESS;
}

/*
2.1. 1er Commit

Reponse a la premiere question de 2.1 : Les 2 processus s'arrêtent avec CTRL-C, On constate que n constate que le père et le fils ont le même ID de groupe
de processus, cela est explicable du fait que lorsqu'un processus est créé avec fork(),
le fils hérite du groupe de processus du père.

2.1. 2eme Comit 

a- Question : Utiliser kill pour arrêter le processus fils puis ps aj de nouveau : que remarquez-vous ? 

Reponse : 

Lors de l'exécution du programme initial, la commande ps aj affiche à la fois le processus père et le processus fils. 
Si le processus fils est arrêté avec kill, le processus père continue de fonctionner sans réagir à la terminaison de son fils. 
Bien que le processus fils reste visible dans la liste des processus, sa description change pour indiquer "00 [server_3] <defunct>".


b- Tuer le père, est-ce que le fils est toujours visible ?

Reponse :

Si on tue le pere auqu'un des deux processus ne se termine pas, ni pour le pere ni pour le fils 


c- Modifier votre code pour que le père s'arrête quand il détecte (via un signal) que le fils s'est arrêté.

Reponse :
 Quand le processus fils se termine, le processus père détecte cet événement du fait de
la gestion de signal (SIGCHLD) et s'arrête également.


d-  Relancer votre programme et commencer cette fois par tuer le père : qu'observez-vous ? 

Reponse :
 Le processus fils reste en vie si on kill le pere et ce processus du fils reste actif jusqu'a ce qu'on le kill manuellement


e-  Tuer le fils et modifier votre programme pour que le père, quand il est arrêté par un signal, 
arrête le fils.

Reponse :
 Le code se trouvant en amont est le code finale.



*/