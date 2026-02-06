#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include "sha256_utils.h"

using namespace std;

class Block {
public:
    // block data
    string parentHash;
    int nonce;
    string difficulty;
    long timestamp;
    string merkleRoot;
    vector<string> transactions;
    string hash; // block hash

    // Constructor
    Block(string parentHash, int nonce, string difficulty, long timestamp, vector<string> transactions) {
        this->parentHash = parentHash;
        this->nonce = nonce;
        this->difficulty = difficulty;
        this->timestamp = timestamp;
        this->transactions = transactions;

        // compute merkle root
        this->merkleRoot = calculateMerkleRoot(transactions);

        // compute block hash
        this->hash = calculateHash();
    }

    // compute block hash from header
    string calculateHash() const {
        stringstream ss;
        // header: parent + merkle + nonce + diff + time
        ss << parentHash << merkleRoot << nonce << difficulty << timestamp;
        return sha256(ss.str());
    }

    // compute merkle root by hashing all txs
    static string calculateMerkleRoot(const vector<string>& transactions) {
        if (transactions.empty()) return "";
        
        stringstream ss;
        for (const auto& tx : transactions) {
            ss << tx;
        }
        return sha256(ss.str());
    }
};

#endif