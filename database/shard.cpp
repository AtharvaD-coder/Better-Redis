#include "../include/shard.hpp"
using namespace std;



Shard::Shard() : dahtable(Dashtable()), running(true) {
    shardThread = thread(&Shard::run, this);
}

void Shard::shutdown() {
    running = false; 
    queueCondition.notify_all(); 
}

void Shard::run() {
    while (running) {
        unique_lock<mutex> lock(queueMutex);
        queueCondition.wait(lock, [this] { return !transactionQueue.empty() || !running; });

        if (!running && transactionQueue.empty()) {
            break; 
        }

        if (!transactionQueue.empty()) {
            shared_ptr<TransactionWrapper> wrapper = move(transactionQueue.front());
            transactionQueue.pop();
            lock.unlock();

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
        }
    }
}

future<string> Shard::submitTransaction(Transaction transaction) {
    auto wrapper = make_shared<TransactionWrapper>(transaction); 

    lock_guard<mutex> lock(queueMutex);
    transactionQueue.push(wrapper);
    queueCondition.notify_one();

    return wrapper->promiseObj.get_future(); 
}

Shard::~Shard() {
    cout << "Shard DESTRUCTOR CALLED" << endl;
    shutdown();
    if (shardThread.joinable()) {
        cout << "Joining shard thread" << endl;
        shardThread.join();
    }
}
