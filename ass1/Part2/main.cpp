#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include "Blockchain.h"

using namespace std;

// miner thread
void miner(Blockchain& bc, int minerID) {
    // rng setup
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> sleepDist(10, 100); // Sleep between 10ms and 100ms

    for (int i = 0; i < 10; ++i) {
        // simulate delay
        this_thread::sleep_for(chrono::milliseconds(sleepDist(gen)));

        // prepare txs
        vector<string> txs;
        txs.push_back("Miner " + to_string(minerID) + " Block " + to_string(i));
        
        // add block
        bc.addBlock(txs);
        
        // debug print
        cout << "Miner " << minerID << " added a block." << endl;
    }
}

int main() {
    cout << "Initializing Blockchain with Genesis Block..." << endl;
    Blockchain bc;

    cout << "\nLaunching 5 miners (threads)..." << endl;
    vector<thread> miners;

    // start threads
    for (int i = 1; i <= 5; ++i) {
        miners.emplace_back(miner, ref(bc), i);
    }

    // join threads
    for (auto& t : miners) {
        if (t.joinable()) {
            t.join();
        }
    }

    cout << "\nAll miners have finished." << endl;

    // Display results
    bc.displayBlockchainHashes();

    return 0;
}