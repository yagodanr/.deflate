#include <iostream>
#include <bitset>
#include <set>
#include <fstream>
#include <vector>
#include <tuple>
#include <list>


using namespace std;
#define MAX_BUFFER_SIZE 5

template<typename T>
vector<tuple<int, int, T>> LZ77(const T* inp, const int size) {
    vector<tuple<int, int, T>> code;

    list<T> buffer;
    int buffer_size = 0;

    for(int i=0; i<size;) {

        int p_index = 0;
        int p_size = 0;
        T p_next = inp[i];

        int cur_index = 0;
        for(auto it=buffer.end(); it!=buffer.begin(); --it, ++cur_index) {
            if(it == buffer.end()) {
                continue;
            }

            int cur = i;
            int cur_size = 0;
            T cur_next = inp[cur];

            auto t = it;
            while(cur < size) {
                if(t == buffer.end()) {
                    t = it;
                }
                if(*t != cur_next) {
                    break;
                }
                ++cur_size;
                ++cur;
                cur_next = inp[cur];
                t++;
            }

            if(cur_size > p_size) {
                p_index = cur_index;
                p_size = cur_size;
                p_next = cur_next;
            }
        }
        for(int j=0; j<p_size+1; ++j, ++i) {
            buffer.push_back(inp[i]);
            if(buffer_size == MAX_BUFFER_SIZE) {
                buffer.pop_front();
            }
            else {
                ++buffer_size;
            }
        }
        // cout << " \"" << inp[size-1] << "\"" ;

        // cout << endl;
        // for(auto &x: buffer) {
        //     cout << x;
        // }
        // cout << endl << p_index << " " << p_size << " " << p_next << endl << endl;
        code.push_back({p_index, p_size, p_next});
    }

    return code;
}


int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Wrong arguments" << endl;
        return 1;
    }

    ifstream fin;
    fin.open(argv[1], ios::binary);
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
        fin.read(buffer,length);

        if (fin)
            cout << "all " << length << " characters read successfully." << endl;
        else {
            cout << "error: only " << fin.gcount() << " could be read" << endl;
            fin.close();
            delete[] buffer;
            return 1;

        }
        fin.close();

        // cout << buffer;
        cout << buffer << endl;
        auto code = LZ77(buffer, length);
        for(const auto &x: code) {
            cout << get<0>(x) << " " << get<1>(x) << " " << get<2>(x) << endl;
        }

        delete[] buffer;
    }
    return 0;
}