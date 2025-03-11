/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_4.c
 * cc -o server_4 server_4.c
 */








#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

volatile bool running = true;
pid_t child_pid;
int communication_pipe[2];

void child_exit_message() {
    printf("Fils (PID : %d) - Le fils se termine proprement.\n", getpid());
}

void handle_pipe_closed(int signal) {
    printf("Pere (PID : %d) - Le tube a ete ferme par le fils, le pere se termine proprement.\n", getpid());
    exit(EXIT_SUCCESS);
}

int main() {
    if (pipe(communication_pipe) == -1) {
        perror("Erreur lors de la creation du tube de communication");
        exit(EXIT_FAILURE);
    }

    // Enregistrement du gestionnaire de signal pour SIGPIPE
    if (signal(SIGPIPE, handle_pipe_closed) == SIG_ERR) {
        perror("Erreur lors de la definition du gestionnaire de signal");
        exit(EXIT_FAILURE);
    }

    printf("Serveur en cours d'execution (pere) - PID : %d...\n", getpid());

    // Cree un processus fils
    child_pid = fork();

    if (child_pid < 0) {
        perror("Erreur lors de la creation du processus fils");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Code du fils
        close(communication_pipe[1]);  // Le fils ne lit que du tube
        while (true) {
            int random_number;
            ssize_t rten = read(communication_pipe[0], &random_number, sizeof(random_number));
            if (rten == -1) {
                perror("Erreur lors de la lecture du tube de communication");
                exit(EXIT_FAILURE);
            } else if (rten == 0) {
                printf("Fils : PID : %d - Le tube a ete ferme par le pere, le fils se termine proprement.\n", getpid());
                child_exit_message();
                break; // Le tube est ferme par le père
            }
            printf("Fils : PID : %d - Nombre reçu = %d\n", getpid(), random_number);
        }
        close(communication_pipe[0]);
    } else {
        // Code du pere
        close(communication_pipe[0]);  // Le pere n'ecrit que dans le tube

        while (running) {
            srand(time(NULL));
            int random_number = rand() % 100;
            ssize_t wten = write(communication_pipe[1], &random_number, sizeof(random_number));
            if (wten == -1) {
                perror("Erreur lors de l'ecriture dans le tube de communication");
                exit(EXIT_FAILURE);
            }

            sleep(1);
        }

        close(communication_pipe[1]);  // Ferme l'extremite d'ecriture du tube
    }
    return EXIT_SUCCESS;
}








/* 2.2 Reponses :

- Lorsque la commande kill PID (Pere) est executee, les deux messages suivants sont affiches :

    - Le fils : PID : 3059 - Le père a ferme le tube, le fils se termine correctement.
    - Fils (PID : 3059) - La fin du fils est parfaite.

- D'autre part, lors de l'execution de la commande kill PID (Fils), aucun message n'est affiche.
- Il est essentiel de modifier le code afin d'afficher le message de fin du père lorsque le fils est arrete en premier, afin que le père reponde au signal de fermeture du tube par le fils (SIGPIPE).
- De cette manière, lorsque le fils ferme le tube, le père affiche son message de fin et se termine de manière adequate.

*/
