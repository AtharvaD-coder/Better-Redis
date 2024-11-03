#include "../include/shard.hpp"
#include <atomic>
#include <memory>
using namespace std;

moodycamel::ConcurrentQueue<shared_ptr<TransactionWrapper>> transactionQueue;

Shard::Shard() : dahtable(Dashtable()), running(true) {
    shardThread = thread(&Shard::run, this);
}

void Shard::shutdown() {
    running.store(false, memory_order_relaxed);
}

void Shard::run() {
    while (running.load(memory_order_relaxed)) {
        shared_ptr<TransactionWrapper> wrapper;

        if (transactionQueue.try_dequeue(wrapper)) {
            switch (wrapper->transaction.type) {
                case PUT:
                    dahtable.Put(wrapper->transaction.key, wrapper->transaction.value);
                    wrapper->promiseObj.set_value("Put successful");
                    break;
                
                case DELETE:
                    dahtable.Delete(wrapper->transaction.key);
                    wrapper->promiseObj.set_value("Delete successful");
                    break;
                
                case GET: {
                    string result = dahtable.Get(wrapper->transaction.key);
                    wrapper->promiseObj.set_value(result);
                    break;
                }
            }
        } else {
            this_thread::sleep_for(chrono::milliseconds(3));
        }
    }

    shared_ptr<TransactionWrapper> remainingWrapper;
    while (transactionQueue.try_dequeue(remainingWrapper)) {
        switch (remainingWrapper->transaction.type) {
            case PUT:
                dahtable.Put(remainingWrapper->transaction.key, remainingWrapper->transaction.value);
                remainingWrapper->promiseObj.set_value("Put successful");
                break;
            case DELETE:
                dahtable.Delete(remainingWrapper->transaction.key);
                remainingWrapper->promiseObj.set_value("Delete successful");
                break;
            case GET: {
                string result = dahtable.Get(remainingWrapper->transaction.key);
                remainingWrapper->promiseObj.set_value(result);
                break;
            }
        }
    }
}

future<string> Shard::submitTransaction(Transaction transaction) {
    auto wrapper = make_shared<TransactionWrapper>(transaction);
    
    transactionQueue.enqueue(wrapper);

    return wrapper->promiseObj.get_future();
}

Shard::~Shard() {
    shutdown();
    if (shardThread.joinable()) {
        shardThread.join();
    }
}
