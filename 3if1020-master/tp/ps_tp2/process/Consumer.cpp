/*
 * Programming curriculum - Information and digital technology track
 * System Programming - Lab #2
 *
 * Consumer.cpp
 * Compile with: c++ -std=c++20 Consumer.cpp -o Consumer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>

#include "../Random.hpp"
#include "../ProdOrCons.hpp"

#include "MessageBox.hpp"

/*
 * Message consuming class
 */
class Consumer : public ProdOrCons< MessageBox > {
public:
    // Inherits constructor from ProdOrCons
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // TODO: Remove nb_messages_ integers from box_ with a random delay
        // before each. Log the progress and errors for negative numbers.
        for (unsigned i = 0; i < nb_messages_; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(random_engine_()));
            int message = box_.get();
            if (message < 0) {
                std::cerr << "Error: Negative message retrieved: " << message << std::endl;
            } else {
                std::cout << "Consumer extracted message: " << message << std::endl;
            }
        }
    }
};


int main()
{
    using namespace boost::interprocess;

    // TODO: Synchronize with the producer to ensure the message box
    // is ready, then access the shared memory, map it, and use it as a mailbox
    // to start the consumer process
    
    named_semaphore semaphore(open_or_create, "Semaphore", 0);
    semaphore.wait();
    shared_memory_object shm(open_only, "SharedMemory", read_write);
    mapped_region region(shm, read_write);
    MessageBox* box = static_cast<MessageBox*>(region.get_address());
    Random random(1000); 
    const unsigned int numMessages = 20; 
    Consumer consumer(2, *box, random, numMessages); 
    consumer();

    return 0;
}
