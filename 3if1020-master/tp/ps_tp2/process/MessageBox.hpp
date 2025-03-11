/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <array>
#include <algorithm>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre processus
 */
class MessageBox : public BasicMessageBox {
public:
    MessageBox() : count_(0) {}
    void put( int message ) {
        // TODO : ajouter les mecanismes de synchronisation
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex_);
        buffer_[count_] = message;
        count_++;
        cond_.notify_one();
    }
 
    int get() {
        // TODO : ajouter les mecanismes de synchronisation
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex_);
        while (count_ == 0) {
            cond_.wait(lock);
        }
        int message = buffer_[0];
        for (int i = 0; i < count_ - 1; ++i) {
            buffer_[i] = buffer_[i + 1];
        }
        count_--;
        return message;
    }
private:
    // TODO : ajouter les objets de synchronisation
    boost::interprocess::interprocess_mutex mutex_;
    boost::interprocess::interprocess_condition cond_;
    int count_;
    int buffer_[100];
 
};
