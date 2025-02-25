#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

void write_vb_binary(ofstream &fout, vector<bool> a);
vector<bool> read_vb_binary(ifstream &fin);

template <typename T>
void write_tuple_binary(ofstream &fout, tuple<int, int, T> t);

template <typename T>
tuple<int, int, T> read_tuple_binary(ifstream &fin);

template<typename T>
void write_dict_binary(ofstream &fout, map<tuple<int, int, T>, vector<bool>> &dict);

template <typename T>
map<tuple<int, int, T>, vector<bool>> read_dict_binary(ifstream &fin);

template <typename T>
void print_dict(map<tuple<int, int, T>, vector<bool>> &dict);