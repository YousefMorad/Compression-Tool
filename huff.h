#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Node{
private:
    char data;
    int freq;

public:
    Node *left, *right;
    Node(){}
    Node(char,int);
    inline char getData(){ return this->data; }
	inline int getFreq() {return this->freq; }
	inline Node * getLeft(){ return this->left; }
	inline Node * getRight(){ return this->right; }
    //Node * mearg(Node *,Node *)
};

class Huff{
private:
    Node *root;
    map<char,string> huffCodeTable;
public:
    Huff(string);
    Node * constarctTree(vector<Node *>);//return the root node pointer
    void makeTable(Node *,string);//Take the root node as it's parameter
    void compress(string);//Take the file name as it's parameter
    void decompress(string);//Take the file name as it's parameter
};
