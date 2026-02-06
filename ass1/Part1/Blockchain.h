#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm> // For std::reverse
#include "Block.h"

using namespace std;

class Blockchain {
private:
    // stores blocks by hash
    unordered_map<string, Block> chain;
    
    // latest block hash
    string tipHash;
    int height;

public:
    // init blockchain with genesis
    Blockchain() {
        // genesis block setup
        // parent: 64 zeros
        string genesisParent = string(64, '0'); 
        int genesisNonce = 0;
        string genesisDiff = string(64, 'f'); // max difficulty
        long genesisTime = 0;
        
        vector<string> genesisTxs;
        genesisTxs.push_back("Genesis Transaction");

        Block genesis(genesisParent, genesisNonce, genesisDiff, genesisTime, genesisTxs);
        
        // Add to chain
        chain.insert({genesis.hash, genesis});
        tipHash = genesis.hash;
        height = 0;

        cout << "Genesis block created with hash: " << genesis.hash << endl;
        displayBlock(genesis);
    }

    // get tip
    string getTipHash() const {
        return tipHash;
    }

    // get height
    int getHeight() const {
        return height;
    }

    // add new block
    void addBlock(const vector<string>& transactions) {
        // get parent block
        if (chain.find(tipHash) == chain.end()) return; // check if tip exists
        Block parentBlock = chain.at(tipHash);

        // prepare block data
        string parentHash = parentBlock.hash;
        int nonce = rand()%10000; // random nonce
        string difficulty = parentBlock.difficulty; // inherit difficulty
        long timestamp = time(nullptr); // current time

        // create block
        Block newBlock(parentHash, nonce, difficulty, timestamp, transactions);

        // update chain and tip
        chain.insert({newBlock.hash, newBlock});
        tipHash = newBlock.hash;
        height++;
        
        displayBlock(newBlock);
        // cout << "Current Tip: " << tipHash << endl;
        cout << "Current Height: " << height << endl;
        cout << "-----------------------" << endl;
    }
    // according to the starter code :)))) 
    // but i didnt use this anywhere i guess 
    void tip(const vector<string>& transactions) {
        addBlock(transactions);
    }

    // print block info
    void displayBlock(const Block& block) const {
        cout << "------ New Block ------" << endl;
        cout << "Parent Hash: " << block.parentHash << endl;
        cout << "Nonce: " << block.nonce << endl;
        cout << "Difficulty: " << block.difficulty << endl;
        cout << "Timestamp: " << block.timestamp << endl;
        cout << "Merkle Root: " << block.merkleRoot << endl;
        cout << "Hash: " << block.hash << endl;
        cout << "-----------------------" << endl;
    }

    // print full chain
    void displayBlockchainHashes() const {
        cout << "\nBlockchain from Genesis to Tip:" << endl;
        
        vector<string> hashes;
        string current = tipHash;

        // trace back to genesis
        while (chain.find(current) != chain.end()) {
            hashes.push_back(current);
            Block b = chain.at(current);
            
            // stop at genesis
            if (b.timestamp == 0 && b.nonce == 0) break; // identify genesis
            
            current = b.parentHash;
        }

        // reverse to show genesis first
        reverse(hashes.begin(), hashes.end());

        for (const string& h : hashes) {
            // print hash
            cout << "Block Hash: " << h << endl;
             // Print parent for verification
            // cout << "   (Parent: " << chain.at(h).parentHash << ")" << endl;
        }
        cout << "Current Tip: " << tipHash << endl;
    }
};

#endif