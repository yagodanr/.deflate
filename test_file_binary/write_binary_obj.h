#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

void write_vb_binary(ofstream &fout, vector<bool> a);
vector<bool> read_vb_binary(ifstream &fin);