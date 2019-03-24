#include "huff.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

Node ::Node (char c,int freq){
    this->data = c;
    this->freq = freq;
    this->left = this->right = NULL;
}

Huff:: Huff(string fileName){
    if (fileName.find(".txt")!= std::string::npos){
        //compressing mode

        int freq[127] = {};//the range of ASCII code for the printable characters from 32 - 126 but new line code is 10
        char tmp;

		freopen(fileName.c_str(), "r", stdin);
		while(scanf("%c", &tmp) != EOF){
            freq[tmp]++;
		}
		fclose(stdin);

        vector<Node *> leafNodes;
        for(int i = 9; i < 127; ++i){//Constricting all the leaf nodes
            if (freq[i] != 0){
                Node *newNode = new Node(static_cast<char>(i),freq[i]);
                leafNodes.push_back(newNode);
            }
        }
        this->root = constarctTree(leafNodes);
        makeTable(this->root, "");
        compress(fileName);
        //decompress("daah.txt");
    }else{
    //decompressing mode

    }
}

struct compare {
    bool operator()(Node* l, Node* r){
        return (l->getFreq() > r->getFreq());
    }
};

Node *Huff:: constarctTree(vector<Node *> leafNodes){
    Node *left, *right, *top;
     priority_queue<Node*, vector<Node*>, compare> minHeap;
     for (int i =0 ;i < (int)leafNodes.size();++i)
        minHeap.push(new Node(leafNodes[i]->getData(),leafNodes[i]->getFreq()));
    while ((int) minHeap.size() > 1){
        right = minHeap.top();
        minHeap.pop();

        left = minHeap.top();
        minHeap.pop();

        top = new Node('y',(right->getFreq() + left->getFreq()));
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }
    return minHeap.top();
}

void Huff::makeTable(Node* curNode, string curCode){
    if(curNode->getLeft() == NULL && curNode->getRight() == NULL){
		this->huffCodeTable[curNode->getData()] = curCode;
		return;
	}
	makeTable(curNode->getLeft(), curCode + '0');
	makeTable(curNode->getRight(), curCode + '1');
	return;
}

int binaryToDecimal(string bin) {
	while ((int)bin.size() < 8) bin += "0";
	int dec = 0;
	reverse(bin.begin(), bin.end());
	for (int i = 0; i < (int)bin.size(); ++i)
		dec += (bin[i] == '1') * (1 << i);
	return dec;
}

void Huff::compress(string fileName){
    char tmp;
    freopen(fileName.c_str(), "r", stdin);
    string result = "";
    while(scanf("%c", &tmp) != EOF)
        result += this->huffCodeTable[tmp];
    fclose(stdin);


    string temp = "";
    for (int i = 0; i < (int)result.size(); i += 8){
        temp += char(binaryToDecimal(result.substr(i, 8)));
    }

    size_t size = temp.size();
	fstream outFile;
	outFile.open("final.bin", ios::out | ios::binary);
	outFile.write(temp.c_str(), size);
	outFile.close();
}

/*
for testing
void Huff::decompress(string compressedFile){
    char tmp;

    string s = "",str = "";
   for (int i = 0; i< (int)ans.size(); ++i){
        s += ans[i];
        for(int i = 9; i < 127; ++i){
            if (huffCodeTable[static_cast<char>(i)] == s){
                str += static_cast<char>(i);
                cout << i;
                s = "";
                break;
            }
        }
    }
      freopen(compressedFile.c_str(), "w", stdout);
      cout << str;
      fclose(stdout);
}
*/
int main()
{
    string fileName;
    cin >> fileName;
    Huff test(fileName);
    return 0;
}
