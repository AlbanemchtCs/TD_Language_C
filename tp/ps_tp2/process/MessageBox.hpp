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
    void put( int message ) {
        // Ajout des mecanismes de synchronisation
        basic_put( message );
        unique_lock lock(mutex_box_);

        box_not_complete.wait(lock, [this]() { return sum_msg < box_size_; });

        basic_put(message);
        sum_msg++;

        mutex_box_.unlock();
        box_complete.notify_one();
    }
 
    int get() {
        // Ajout des instructions de synchronisation
        unique_lock lock(mutex_box_);

        box_complete.wait(lock, [this]() { return sum_msg > 0; });

        int message{ basic_get() };
        sum_msg--;

        mutex_box_.unlock();
        box_not_complete.notify_one();
        
        return message;
    }

private:
    // Ajout des objets de synchronisation
    int sum_msg = 0;

    typedef boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex>unique_lock;

    boost::interprocess::interprocess_mutex mutex_box_;
    boost::interprocess::interprocess_condition box_complete;
    boost::interprocess::interprocess_condition box_not_complete;
};
 
