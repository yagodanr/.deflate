#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <list>
#include <cstring>
#include <map>
#include <queue>

#include "rw_binary.cpp"


using namespace std;
#define MAX_BUFFER_SIZE 4096
#define DEBUG


template <typename T>
vector<tuple<int, int, T>> decode_Huffman(vector<bool> &code, map<tuple<int, int, T>, vector<bool>> &dict) {
    long long n = code.size();

    vector<tuple<int, int, T>> decoded;

    vector<bool> cur;
    for(long long i=0; i<n; ++i) {
        cur.push_back(code[i]);
        for(auto &[key, value]: dict) {
            if(value == cur) {
                decoded.push_back(key);
                cur = {};
                break;
            }
        }
    }
    return decoded;
}



int main(int argc, char *argv[]) {
    if(argc != 3) {
        argc = 3;
        argv = new char*[2];
        argv[1] = new char[strlen("lz_test2.deflate")+1];
        strcpy(argv[1], "lz_test2.deflate");
        argv[2] = new char[strlen("lz_test2_decoded.txt")+1];
        strcpy(argv[2], "lz_test2_decoded.txt");

    }


    ifstream fin;
    fin.open(argv[1], ios::binary);
    if(!fin.is_open()) {
        cout << "Couldn't open the file" << endl;
        return 1;
    }

    if (fin) {
        cout << "Read dictionary" << endl;
        map<tuple<int, int, char>, vector<bool>> dict = read_dict_binary<char>(fin);
        cout << "Read code" << endl;
        vector<bool> code = read_vb_binary(fin);


        #ifdef DEBUG
        print_dict(dict);
        for(auto x: code) {
            cout << x;
        }
        cout << endl;
        #endif

        vector<tuple<int, int, char>> decoded_h = decode_Huffman(code, dict);
        #ifdef DEBUG
        for(const auto &x: decoded_h) {
            cout << "(" << get<0>(x) << " " << get<1>(x) << " \"" << get<2>(x) << "\")"<< endl;
        }
        #endif
    }
    return 0;
}