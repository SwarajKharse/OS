#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <ctime>
#include <cstdlib>
using namespace std;

#define NUM_READERS 2
#define NUM_WRITERS 2

mutex mtx;
condition_variable cond_reader, cond_writer;

int readers_count = 0;
int writers_count = 0;
int resource = 0;
bool synchronized_flag = true; // To switch between synchronized and unsynchronized cases

// Reader function
void readerFunction(int reader_id) {
    if (synchronized_flag) {
        unique_lock<mutex> lock(mtx);
        while (writers_count > 0) {
            cout << "Reader " << reader_id << " is waiting because a writer is writing" << endl;
            cond_reader.wait(lock);
        }
        readers_count++;
        lock.unlock();

        // Read the resource
        cout << "Reader " << reader_id << " reading shared resource" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        lock.lock();
        readers_count--;
        if(readers_count == 0) {
            cond_writer.notify_one();
        }
        lock.unlock();
    }else { // Without synchronization
        // Read the resource
        cout << "Reader " << reader_id << " reads resource: " << resource << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "Reader " << reader_id << " completed with reading, CS is free" << endl;
}

// Writer function
void writerFunction(int writer_id) {
    if (synchronized_flag) {
        unique_lock<mutex> lock(mtx);
        writers_count++;
        while (readers_count > 0 || writers_count > 1) {
            cout << "Writer " << writer_id << " wants to write but not allowed" << endl;
            cond_writer.wait(lock);
        }
        lock.unlock();

        // Write to the resource
        resource = writer_id;
        cout << "Writer " << writer_id << " writing shared resource" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        lock.lock();
        writers_count--;
        cond_writer.notify_one();
        cond_reader.notify_all(); // Signal all readers
        lock.unlock();
    } else { // Without synchronization
        // Write to the resource
        resource = writer_id;
        cout << "Writer " << writer_id << " writes resource: " << resource << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "Writer " << writer_id << " completed with writing, CS is free" << endl;
}

int main() {
    thread readers[NUM_READERS];
    thread writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        writer_ids[i] = i + 1;
    }

    srand(time(nullptr));

    // Reader-Reader (RR) case
    synchronized_flag = true;
    cout << "Reader-Reader (RR) case:" << endl;
    for (int i = 0; i < NUM_READERS; i++) {
        readers[i] = thread(readerFunction, reader_ids[i]);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        readers[i].join();
    }

    // Reader-Writer (RW) case
    synchronized_flag = true;
    cout << "\nReader-Writer (RW) case:" << endl;
    readers[0] = thread(readerFunction, reader_ids[0]);
    writers[0] = thread(writerFunction, writer_ids[0]);
    readers[0].join();
    writers[0].join();

    // Writer-Writer (WW) case
    synchronized_flag = true;
    cout << "\nWriter-Writer (WW) case:" << endl;
    for (int i = 0; i < NUM_WRITERS; i++) {
        writers[i] = thread(writerFunction, writer_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        writers[i].join();
    }

    // Writer-Reader (WR) case
    synchronized_flag = true;
    cout << "\nWriter-Reader (WR) case:" << endl;
    writers[0] = thread(writerFunction, writer_ids[0]);
    readers[0] = thread(readerFunction, reader_ids[0]);
    readers[0].join();
    writers[0].join();

    // Reader-Reader (RR) case without synchronization
    synchronized_flag = false;
    cout << "\nReader-Reader (RR) case without synchronization:" << endl;
    for (int i = 0; i < NUM_READERS; i++) {
        readers[i] = thread(readerFunction, reader_ids[i]);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        readers[i].join();
    }

    // Reader-Writer (RW) case without synchronization
    synchronized_flag = false;
    cout << "\nReader-Writer (RW) case without synchronization:" << endl;
    readers[0] = thread(readerFunction, reader_ids[0]);
    writers[0] = thread(writerFunction, writer_ids[0]);
    readers[0].join();
    writers[0].join();

    // Writer-Writer (WW) case without synchronization
    synchronized_flag = false;
    cout << "\nWriter-Writer (WW) case without synchronization:" << endl;
    for (int i = 0; i < NUM_WRITERS; i++) {
        writers[i] = thread(writerFunction, writer_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        writers[i].join();
    }

    // Writer-Reader (WR) case without synchronization
    synchronized_flag = false;
    cout << "\nWriter-Reader (WR) case without synchronization:" << endl;
    writers[0] = thread(writerFunction, writer_ids[0]);
    readers[0] = thread(readerFunction, reader_ids[0]);
    readers[0].join();
    writers[0].join();

    return 0;
}
