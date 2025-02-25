#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <list>
#include <cstring>
#include <map>
#include <queue>

using namespace std;
#define MAX_BUFFER_SIZE 4096
#define DEBUG



int main(int argc, char *argv[]) {
    if(argc != 3) {
        argc = 3;
        argv = new char*[2];
        argv[1] = new char[strlen("out.deflate")+1];
        strcpy(argv[1], "out.deflate");
        argv[2] = new char[strlen("lz_test3.txt")+1];
        strcpy(argv[2], "lz_test3.txt");

    }


    ifstream fin;
    fin.open(argv[1], ios::binary);
    if(!fin.is_open()) {
        cout << "Couldn't open the file" << endl;
        return 1;
    }

    if (fin) {
        long long dict_size;
        fin.read((char*)&dict_size, sizeof dict_size);
        cout << dict_size << endl;
        map<tuple<int, int, char>, vector<bool>> dict;
        fin.read((char*)&dict, dict_size);

        long long code_size;
        fin.read((char*)&code_size, sizeof code_size);
        vector<bool> code;
        fin.read((char*)&code, code_size);

        // #ifdef DEBUG
        cout << "Read dictionary" << endl;
        for(auto &x: dict) {
            cout << "\"" << get<0>(x.first) << " " << get<1>(x.first) << " " << get<2>(x.first) << "\" -> \"";
            for(auto bi: x.second) {
                cout << bi;
            }
            cout << "\"" << endl;
        }
        cout << "Read code" << endl;
        for(auto x: code) {
            cout << x;
        }
        cout << endl;
        // #endif
    }
    return 0;
}