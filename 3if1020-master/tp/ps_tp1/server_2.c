/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_2.c
 * cc -o server_2 server_2.c
 */

// Commencer par recopier ici le code de server_1.c




//1.2 Le code en bas en commentaire pour toutes les questions de 1.2 sauf la derniere avec son propre code en bas 






/*


#include <stdio.h>
// Pour le rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// Pour le getpid(), getppid()
#include <unistd.h>
// Pour le signal handling
#include <signal.h>
// Pour bool
#include <stdbool.h>


volatile bool running = true;


void handle_signal(int signal_num) {
    
    printf("Signal reçu : %d\n", signal_num);

    printf("Arrêt du programme en raison du signal SIGINT\n");

    
    running = false;
}

int main() {
    
    struct sigaction sa;
    sa.sa_handler = &handle_signal;
    sa.sa_flags = 0; 

     
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation du gestionnaire de signal");
        exit(EXIT_FAILURE);
    }

     
    srand(time(NULL));

    printf("Démarrage du générateur de nombres aléatoires...\n");

    
    while (running) {
        printf("PID: %d, PPID: %d, PGID: %d\n", getpid(), getppid(), getpgrp());

        
        int random_number = rand() % 100;
        printf("Nombre aléatoire: %d\n", random_number);

         
        sleep(1);
    }

     
    printf("Fin du programme.\n");

    return EXIT_SUCCESS;
}

*/





//1.2 Reponse aux questions :
// En utilisant la fonctionalite :'Clt+' dans le term1 et 'Kill -s INT' dans le term2 le message s'est affiche, mais en utilisant seulement Kill suivie du PID le message ne s'est pas affiche
// Avec Kill -9 le message ne s'est pas affiche comme avec Kill suivie du PID dans le term2






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//Derniere question partie 1.2 : Modifier votre fonction afin de ne plus modifier la variable running :
//Reponse :

//Nouveau code pour la derniere partie de 1.2 :





/*

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

volatile bool running = true;

void handle_signal(int signal) {
    printf("Signal reçu : %d\n", signal);
    printf("Arrêt du programme en raison du signal SIGINT\n");
    // J'ai commente la ligne qui modifie running 1.2
    // running = false; 
}

int main() {
    printf("Starting random number generator...\n");

    struct sigaction sa;
    sa.sa_handler = &handle_signal;
    sigaction(SIGINT, &sa, NULL);

    while (running) {
        printf("PID: %d, PPID: %d, PGID: %d\n", getpid(), getppid(), getpgrp());
        int random_number = rand() % 100;
        printf("Random Number: %d\n", random_number);
        sleep(1);
    }

    printf("Ending program.\n");
    return EXIT_SUCCESS;
}

*/







//Reponse a la derniere question de 1.2 : 

// 'Ctl+C' n'arrete plus le code 
// Kill suivie du PID arrete le code 
// Kill -s INT suivie du PID n'arrete pas le code 
// kill -9 suivie du PID arrete le code 






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








//Reponse a la partie 1.3




#include <stdio.h>
#include <stdlib.h>
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

    printf("Le serveur a terminé son exécution.\n");
    return EXIT_SUCCESS;
}





//Reponse a 1.3

// -On ajoute dans notre programme une fonction exit_message() qui affiche un message. 
// On l'installe en utilisant atexit(), pour qu'elle soit automatiquement exécutée à la fin du programme. 
// Cette fonction est activée quand le programme est arrêté via un CTRL-C, et un kill.
// En revanche elle n'est pas activée en utilisant un kill -9.
