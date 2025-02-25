#include <iostream>
#include <fstream>
#include <vector>
#include "write_binary_obj.h"

using namespace std;

void write_vb_binary(ofstream &fout, vector<bool> a) {

    long long num_elements = a.size();
    fout.write((char*)(&num_elements), sizeof(num_elements));

    for (bool x : a) {
        fout.write((char*)(&x), sizeof(x));
    }
}

vector<bool> read_vb_binary(ifstream &fin) {
    long long num_elements;
    fin.read((char*)(&num_elements), sizeof(num_elements));

    vector<bool> vb(num_elements); // Resize the vector *before* reading

    for (size_t i = 0; i < num_elements; ++i) {
        bool temp;
        fin.read((char*)(&temp), sizeof(temp)); // Read each boolean
        vb[i] = temp;
    }
    return vb;
}

int main() {
    vector<bool> a = {true, true, true, false, false}; // Use true/false for clarity
    for (bool x : a) {
        cout << x;
    }

    ifstream find;
    find.open("writing_binary_dict.deflate", ios::binary);
    map<tuple<int, int, char>, vector<bool>> dict = read_dict_binary<char>(find);
    find.close();
    print_dict(dict);

    ofstream fout;
    fout.open("writing_binary.deflate", ios::binary);
    write_vb_binary(fout, a);
    fout.close();


    ifstream fin;
    fin.open("writing_binary.deflate", ios::binary);
    vector<bool> a1 = read_vb_binary(fin);
    fin.close();
    cout << endl;
    for (bool x : a1) {
        cout << x;
    }


    return 0;
}