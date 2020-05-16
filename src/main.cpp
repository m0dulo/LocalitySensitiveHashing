#include <iostream>
#include <dataloader.h>
#include <utlis.h>
#include <list>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include "Argument_helper.h"

using namespace std;

uint32_t BKDRHash(const string& s) {
   uint32_t seed = 131313;
   uint32_t hash = 0;
   for (size_t i = 0; i < s.length(); ++i) {
       hash = hash * seed + s.at(i);
   }
   return hash;
}


int main(int argc, char* argv[]) {
    string rawData = "";
    string hashData = "";
    dsr::Argument_helper ah;
    ah.new_named_string("rawdata", "raw_data", "named_string", 
         "named_string", rawData);
    ah.new_named_string("hashdata", "hash_data", "named_string", 
         "named_string", hashData);
    ah.process(argc, argv);
    Dataloader load(rawData);
    auto dataBuffer = load.loadData();
    LyxUtlis::log("Loaded data size: ", dataBuffer.size());
    ofstream ofs;
    ofs.open(hashData);
    vector<uint32_t> shingles;
    for (auto& line : dataBuffer) {
        int index = 0;
        for (auto &token : line) {
            auto hashValue = BKDRHash(token);
            ofs << hashValue << " ";
            if (find(shingles.begin(), shingles.end(), hashValue) == shingles.end()) {
                shingles.emplace_back(hashValue);
            }
        }
        ofs << "\n";
    }
    ofs.close();
    LyxUtlis::log("Shingles size: ", shingles.size());

    vector<string> matrix;
    for (size_t i = 0; i < shingles.size(); ++i) {
        matrix.emplace_back("");
    }

    ifstream in;
    in.open(hashData);
    string line;
    int i = 0;
    int cnt = 1;
    while (getline(in , line)) {
        vector<string> tokens;
        LyxUtlis::split(line, tokens, " ");
        int intRes = 0;
        for (string &token : tokens) {
            int index = 0;
            std::stringstream buffer(token);
            buffer >> intRes;
            intRes = atoi(token.c_str());
            //cout << intRes << " ";
            auto iter = find(shingles.begin(), shingles.end(), intRes);
            index =  iter - shingles.begin();
            matrix.at(index) += to_string(cnt);
            matrix.at(index) += " ";
        }
        cnt++;
    }
    in.close();
//    for (size_t i = 0 ; i < matrix.size(); ++i) {
//        cout << "Matrix " << i << " is: " << matrix.at(i);
//        cout << endl;
//    }
    LyxUtlis::log("Shingling Done!");

    int signMatrix[100][10000];
    int c = 40423;
    int a[100];
    int b[100];

    srand(time(nullptr));
    for (int i = 0 ; i < 100; ++i) {
        a[i] = rand() % 40322 + 40322;
        b[i] = rand() % 40322 + 40322;
    }

    for (size_t i = 0; i < 100; ++i) {
        for (size_t j = 0 ; j < 10000; ++j) {
            signMatrix[i][j] = 40389;
        }
    }


    int hash;
    vector<string> strs;
    for (std::size_t i = 0; i < 100; ++i) {
        for (std::size_t j = 0; j < matrix.size(); ++j) {
            hash = (a[i] * (j + 1) + b[i]) % c;
            LyxUtlis::split(matrix.at(j), strs, " ");
            int number;
            for (string& s : strs) {
//                cout << s<< " ";
                if (s != "") {
                    number = atoi(s.c_str()) - 1;
//                    cout << number << " ";
                }
                if (signMatrix[i][number] > hash) {
                    signMatrix[i][number] = hash;
                }
            }
        }
    }

    LyxUtlis::log("MiniHash Done!");

    vector<string> vs;
    ifstream raw;
    raw.open(rawData);
    string raw_line;
    while(getline(raw, raw_line)) {
        vs.emplace_back(raw_line);
    }
    raw.close();

    unordered_map<string, int> ht;
    unordered_map<string, int> hh;
    for (std::size_t i = 0; i < 20; ++i) {
        for (std::size_t m = 0; m < 10000; ++m) {
            string code = "";
            for (std::size_t j = 0; j < 5; ++j) {
                code += to_string(signMatrix[i * 5 + j][m]);
            }
            if (ht.find(code) == ht.end()) {
                ht[code] = 1;
                hh[code] = m + 1;
            } else {
                int l = ht[code];
                ht[code] = l + 1;
                cout << hh[code] << "号文档和" << m + 1 << "号文档是相似文档";
                cout << vs.at(hh[code] - 1) << endl;
                cout << vs.at(m) << endl;
                cout << endl;
            }
        }
        ht.clear();
    }

    return 0;
}
