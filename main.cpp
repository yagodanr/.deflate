#include <iostream>
#include <bitset>
#include <set>
#include <fstream>

using namespace std;

#define BUFFER_SIZE 5


int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Wrong arguments" << endl;
        return 1;
    }

    ifstream fin;
    fin.open(argv[1]);
    if(!fin.is_open()) {
        cout << "Couldn't open the file" << endl;
        return 1;
    }

    char ch[BUFFER_SIZE];
    while(fin.read(ch, BUFFER_SIZE)) {
        for(int i=0; i<BUFFER_SIZE; ++i) {
            cout << ch[i];
        }
        cout << "+" <<  endl;
    }


    fin.close();
    return 0;
}