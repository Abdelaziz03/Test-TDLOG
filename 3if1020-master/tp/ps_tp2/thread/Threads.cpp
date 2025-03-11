/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Threads.cpp
 * c++ -std=c++20 Threads.cpp -o Threads -lpthread
 */

#include <iostream>
#include <thread>
 
 
#include "../Random.hpp"

#include "osyncstream.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include "MessageBox.hpp"
 
/*
 * Test avec 1 producteur et 1 consommateur
 */
void one_producer_one_consumer() {

    MessageBox box; // Boîte à lettres
    Random generator(50); // Nombres aléatoires

    // Création du producteur et du consommateur
    Producer producer(1, box, generator, 20); // ID du producteur, boîte, générateur, nombre de messages
    Consumer consumer(2, box, generator, 20); // ID du consommateur, boîte, générateur, nombre de messages

    std::thread producer_thread(std::ref(producer)); // Création du thread producteur
    std::thread consumer_thread(std::ref(consumer)); // Création du thread consommateur

    producer_thread.join(); // Attendre la fin du thread producteur
    consumer_thread.join(); // Attendre la fin du thread consommateur


}




/*
 * Test avec plusieurs producteurs et consommateurs méthod 1

void several_producers_and_consumers() {
        MessageBox box; // Création de la boîte à lettres
    Random generator(50); // Générateur de nombres aléatoires

    // Création du producteur et du consommateur avec les bons arguments
    Producer producer(1, box, generator, 20); // ID du producteur, boîte, générateur, nombre de messages
    Consumer consumer(2, box, generator, 20); // ID du consommateur, boîte, générateur, nombre de messages

    std::thread producer_thread(std::ref(producer)); // Création du thread producteur
    std::thread consumer_thread(std::ref(consumer)); // Création du thread consommateur

    producer_thread.join(); // Attendre la fin du thread producteur
    consumer_thread.join(); // Attendre la fin du thread consommateur
}

 */





/*
 * Méthode 2 avec std:: Des producteurs et des consommateurs en processus légers
*/
 void several_producers_and_consumers() {
    Random random_generator(20); // Nbr aléatoire entre 10 et 20
    int num_consumers = 10 + random_generator() % 11; // Nbr de consommateurs
    int num_producers = num_consumers * 2; // Nbr de producteurs (double des consommateurs)

    MessageBox box; // Boîte à lettres commune
    std::vector<std::thread> group; // Stockeage des threads

    // Les producteurs
    for (int i = 0; i < num_producers; ++i) {
        group.push_back(std::thread(Producer(i, box, random_generator, 10)));
    }

    // Les consommateurs
    for (int i = 0; i < num_consumers; ++i) {
        group.push_back(std::thread(Consumer(i, box, random_generator, 20)));
    }

    // Tous les threads
    for (auto &t : group) {
        if (t.joinable()) {
            t.join();
        }
    }
}



int main() {
    //one_producer_one_consumer();
    several_producers_and_consumers();
    return 0;
}

