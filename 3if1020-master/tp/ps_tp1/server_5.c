/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_5.c
 * cc -o server_5 server_5.c
 */

//3.1. Un serveur, un client, une fifo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int fifo_fd;
int server_pid;
int client_pid;
int client_exit_status;

void signal_handler(int signal) {
    if (signal == SIGPIPE) {
        fprintf(stderr, "Serveur (PID : %d) - Le client (PID : %d) a fermé la connexion, arrêt du serveur en cours.\n", server_pid, client_pid);
    } else if (signal == SIGCHLD) {
        fprintf(stderr, "Serveur (PID : %d) - Le client (PID : %d) a terminé son exécution avec le statut %d, fermeture du serveur.\n", server_pid, client_pid, client_exit_status);
    } else if (signal == SIGTERM) {
        fprintf(stderr, "Serveur (PID : %d) - Fin de l'exécution du serveur.\n", server_pid);
    }
    exit(EXIT_SUCCESS);
}

int main() {
    server_pid = getpid();
    if (mkfifo("myfifo", 0666) == -1) {
        perror("Échec de la création de la FIFO");
        exit(EXIT_FAILURE);
    }
    if ((fifo_fd = open("myfifo", O_WRONLY)) == -1) {
        perror("Impossible d'ouvrir la FIFO en écriture");
        exit(EXIT_FAILURE);
    }

    signal(SIGPIPE, signal_handler);
    signal(SIGCHLD, signal_handler);
    signal(SIGTERM, signal_handler);

    while (1) {
        int random_number = rand() % 100;
        if (write(fifo_fd, &random_number, sizeof(random_number)) == -1) {
            perror("Erreur lors de l'écriture dans la FIFO");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }

    close(fifo_fd);
    exit(EXIT_SUCCESS);
}




