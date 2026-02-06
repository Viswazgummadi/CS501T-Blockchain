// test 1: sha256

// #include <iostream>
// #include "sha256_utils.h"

// int main() {
//     std::string input = "test";
//     std::string output = sha256(input);
    
//     std::cout << "Input: " << input << "\n";
//     std::cout << "Hash:  " << output << "\n";
    
//     // Known hash for "test": 9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08
//     return 0;
// }


// test 2: block creation


// #include <iostream>
// #include <vector>
// #include "Block.h" // local includes

// using namespace std;

// int main() {
//     // dummy data
//     string parentHash = "00000000000000000000000000000000"; // dummy parent
//     int nonce = 100;
//     string difficulty = "ffff";
//     long timestamp = time(nullptr);
    
//     vector<string> txs;
//     txs.push_back("Alice pays Bob 10 BTC");
//     txs.push_back("Bob pays Charlie 5 BTC");

//     // create block
//     cout << "Creating Block..." << endl;
//     Block b(parentHash, nonce, difficulty, timestamp, txs);

//     // verify output
//     cout << "Block Created!" << endl;
//     cout << "Merkle Root: " << b.merkleRoot << endl;
//     cout << "Block Hash:  " << b.hash << endl;

//     return 0;
// }



// test 3: full chain

#include <iostream>
#include <vector>
#include <string>
#include "Blockchain.h"

using namespace std;

int main() {
    // init blockchain
    cout << "Initializing Blockchain..." << endl;
    Blockchain bc;

    // add 50 blocks
    cout << "\nMining 50 blocks..." << endl;
    for (int i = 1; i <= 50; i++) {
        vector<string> dummyTxs;
        dummyTxs.push_back("Transaction " + to_string(i) + "-A");
        dummyTxs.push_back("Transaction " + to_string(i) + "-B");
        
        bc.addBlock(dummyTxs);
        
        // detailed print
        // cout << "Added Block " << i << endl;
    }

    // show chain
    // - The hashes of all blocks in the longest chain.
    bc.displayBlockchainHashes();

    return 0;
}