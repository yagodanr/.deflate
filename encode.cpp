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

template<typename T>
vector<tuple<int, int, T>> LZ77(const T* inp, const int size) {
    vector<tuple<int, int, T>> code;

    list<T> buffer;
    long long buffer_size = 0;

    for(int i=0; i<size;) {

        int p_index = 0;
        int p_size = 0;
        T p_next = inp[i];

        int cur_index = 1;
        for(auto it=buffer.end(); it!=buffer.begin(); --it, ++cur_index) {

            int cur = i;
            int cur_size = 0;
            T cur_next = inp[cur];

            auto t = it;
            --t;
            while(cur < size) {
                if(t == buffer.end()) {
                    t = it;
                    --t;
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

template<typename T>
class Tree {
public:
    pair<int, T> val;
    Tree<T> *left;
    Tree<T> *right;

    Tree() {
        this->left = nullptr;
        this->right = nullptr;
    }
    Tree(const pair<int, T>& val) {
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    bool operator>(Tree<T> *other) {
        return this->val.first > other->val.first;
    }
    bool operator<(Tree<T> *other) {
        return this->val.first < other->val.first;
    }
};


template<typename T>
void get_codes(Tree<T> *root, map<T, vector<bool>> &mp, vector<bool> code=vector<bool>()) {
    if(!root->left && !root->right) {
        mp[root->val.second] = code;
        return ;
    }
    code.push_back(0);
    get_codes(root->left, mp, code);
    code[code.size()-1] = 1;
    get_codes(root->right, mp, code);

    return ;
}

template<typename T>
pair<vector<bool>, map<T, vector<bool>>> Huffman(vector<T> inp) {
    map<T, int> counter;
    long long total_count = inp.size();

    for(const auto &x: inp) {
        ++counter[x];
    }

    auto comp = [](Tree<T>* a, Tree<T>* b) {
        return a->val.first > b->val.first;
    };
    priority_queue<Tree<T>*, vector<Tree<T>*>, decltype(comp)> p_q(comp);

    for(auto &x: counter) {
        pair<int, T> temp = {x.second, x.first};
        Tree<T> *tr = new Tree<T>(temp);
        p_q.push(tr);
    }

    Tree<T> *root;
    while(p_q.size() > 1){
        auto x = p_q.top();
        p_q.pop();
        auto y = p_q.top();
        p_q.pop();

        long long sum = x->val.first + y->val.first;
        Tree<T> *newNode = new Tree<T>;
        root = newNode;
        newNode->val.first = sum;
        newNode->left = x;
        newNode->right = y;
        p_q.push(newNode);
    }


    map<T, vector<bool>> mp;
    get_codes(root, mp);
    long long total_code=0;
    for(auto &x: inp) {
        total_code += mp[x].size();
    }
    vector<bool> encoded(total_code);

    for(int i=0, inp_i=0; i<total_code && inp_i<inp.size(); ++inp_i) {
        auto c = mp[inp[inp_i]];
        for(int j=0, s=c.size(); j<s; ++j, ++i) {
            encoded[i] = c[j];
        }
    }
    return {encoded, mp};

}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        argc = 3;
        argv = new char*[2];
        argv[1] = new char[strlen("lz_test1.txt")+1];
        strcpy(argv[1], "lz_test1.txt");
        argv[2] = new char[strlen("lz_test1.deflate")+1];
        strcpy(argv[2], "lz_test1.deflate");

    }


    ifstream fin;
    fin.open(argv[1], ios::binary);
    if(!fin.is_open()) {
        cout << "Couldn't open the file" << endl;
        return 1;
    }

    if (!fin) {
        cout << "Problem with file open the file" << endl;
        return 1;
    }
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

    auto code = LZ77(buffer, length);
    #ifdef DEBUG
    cout << buffer << endl;
    for(const auto &x: code) {
        cout << "(" << get<0>(x) << " " << get<1>(x) << " \"" << get<2>(x) << "\")"<< endl;
    }
    #endif

    delete[] buffer;
    auto p = Huffman(code);
    #ifdef DEBUG
    print_dict(p.second);
    for(auto x: p.first) {
        cout << x;
    }
    cout << endl;
    #endif


    #ifdef DEBUG
    auto k = Huffman(vector<int>({1, 1, 2, 15, 32, 15, 15, 15, 15, 15, 15, 1, 1, 1, 1}));
    cout << endl;
    for(auto &x: k.second) {
        cout << "\"" << x.first << "\" -> \"";
        for(auto bi: x.second) {
            cout << bi;
        }
        cout << "\"" << endl;
    }
    for(auto x: k.first) {
        cout << x;
    }
    cout << endl;
    #endif

    ofstream fout;
    fout.open(argv[2], ios::binary);
    if(!fout.is_open()) {
        cout << "Couldn't open the file" << endl;
        return 1;
    }
    write_dict_binary(fout, p.second);
    long long code_size = sizeof p.first;
    fout.write((char*)&code_size, sizeof code_size);
    fout.write((char*)&p.first, sizeof code_size);
    fout.close();

    return 0;
}