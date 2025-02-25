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
    }
    return 0;
}