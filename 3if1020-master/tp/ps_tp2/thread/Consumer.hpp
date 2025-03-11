/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../ProdOrCons.hpp"
 
#include "osyncstream.hpp"
#include "MessageBox.hpp"


/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons< MessageBox > {
public:
    // Dans ce qui suit on concidère constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // TODO :
        // - Retirer de box_ nb_messages_ entiers avec attente aléatoire avant
        //   chaque retrait.
        // - Afficher des messages entre chaque étape pour suivre l'avancement.
        // - Afficher un message d'erreur si un nombre négatif est extrait.
    Random generator(50); // Création du générateur pour des attentes entre 0 et 50 µs
    for (int i = 0; i < nb_messages_; ++i) {
        std::this_thread::sleep_for(std::chrono::microseconds(generator()));
        int message = box_.get(); // Retire un message
        if (message < 0) {
            osyncstream{ std::cout } << "Erreur: nombre négatif extrait\n";
        } else {
            osyncstream{ std::cout } << "Consommateur a extrait le message " << message << "\n";
        }
    }
}
};


