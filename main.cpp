#include <iostream>
#include <bitset>
#include <set>
#include <fstream>

using namespace std;


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

    char ch;
    while(fin.get(ch)) {
        cout << ch;
    }

    fin.close();
    return 0;
}