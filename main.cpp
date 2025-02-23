#include <iostream>
#include <bitset>
#include <set>
#include <fstream>
#include <vector>
#include <cstring>

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

    if (fin) {
        //Reads the whole file
        // get length of file:
        fin.seekg (0, fin.end);
        int length = fin.tellg();
        fin.seekg (0, fin.beg);

        char *buffer = new char[length];

        cout << "Reading " << length << " characters... ";
        // read data as a block:
        fin.read (buffer,length);

        if (fin)
        cout << "all characters read successfully." << endl;
        else {
            cout << "error: only " << fin.gcount() << " could be read" << endl;
            fin.close();
            delete[] buffer;
            return 1;

        }
        fin.close();

        cout << buffer;

        delete[] buffer;
    }
    return 0;
}