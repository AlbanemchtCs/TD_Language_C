/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <array>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre threads
 */
class MessageBox : public BasicMessageBox {
public:
    void put( int message ) {
        // Ajout des instructions de synchronisation
        unique_lock lock(mutex_box_);

        while (sum_msg != 0) {
            box_not_complete.wait(lock);
        }
        
        basic_put( message );
        sum_msg++;
        box_complete.notify_one();
    }

    int get() {
        // Ajout des instructions de synchronisation
        unique_lock lock(mutex_box_);

        while (sum_msg == 0) {
            box_complete.wait(lock);
        }

        int message{ basic_get() };
        sum_msg = 0;
        box_not_complete.notify_one();

        return message;
    }

private:
    // Ajout des objets de synchronisation
    int sum_msg = 0;

    std::mutex mutex_box_;
    typedef std::unique_lock<std::mutex> unique_lock;

    std::condition_variable box_complete;
    std::condition_variable box_not_complete;
};
 
