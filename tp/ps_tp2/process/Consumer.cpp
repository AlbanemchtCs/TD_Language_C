/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.cpp
 * c++ -std=c++20 Consumer.cpp -o Consumer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "../Random.hpp"
#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"
#include "MessageBox.hpp"

/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
    using milliseconds = std::chrono::duration<int, std::milli>;

    void operator()() override {
        
        // Dépose dans box nb_messages nombres entiers positifs avec attente aléatoire entre chaque
        // Affiche des messages entre chaque étape pour suivre l'avancement
        for (int m = 0; m < nb_messages_; m++) {
            
            int message = box_.get();
            osyncstream(std::cout) << "Consumer message " << message << "\n";
            std::this_thread::sleep_for(milliseconds{random_engine_()});
        }
    }
};

int main() {
    using namespace boost::interprocess;

    // Accède à la mémoire partagée, la projete en mémoire, y accéde comme boîte à lettres, lance le consommateur
    int memory_box = sizeof(MessageBox);

    struct sharedbox_remove {
        ~sharedbox_remove() { shared_memory_object::remove("Memory box shared"); }
    } remover;

    shared_memory_object memory_shared(open_only, "Memory box shared", read_write);
    memory_shared.truncate(memory_box);
    mapped_region reg_mapped = mapped_region(memory_shared, read_write, 0, memory_box);

    MessageBox *msg_box = (MessageBox *)reg_mapped.get_address();
    Random rdm_number{50};
    Consumer cons{2, *msg_box, rdm_number, 20};
    cons();

    return 0;
}


