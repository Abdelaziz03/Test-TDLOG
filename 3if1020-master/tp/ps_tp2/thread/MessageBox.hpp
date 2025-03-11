/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <mutex>
#include <condition_variable>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre threads
 */
class MessageBox : public BasicMessageBox {
public:
    void put(int message) {
        std::unique_lock<std::mutex> lock(mtx);
        not_full.wait(lock, [this]() { return count < box_size_; });
        basic_put(message);
        ++count;
        not_empty.notify_one();
}
 
    int get() {
        std::unique_lock<std::mutex> lock(mtx);
        not_empty.wait(lock, [this]() { return count > 0; });
        int message = basic_get();
        --count;
        not_full.notify_one();
        return message;
}
private:
    std::mutex mtx; // Mutex for synchronisation
    std::condition_variable not_full; // Signaler ; la boîte pas pleine
    std::condition_variable not_empty; // Signaler ; la boîte pas vide
    unsigned int count = 0; // Compteur 
};
 
