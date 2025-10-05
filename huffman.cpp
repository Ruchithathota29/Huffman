#include <iostream>
#include <queue>
#include <map>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void getCodes(Node* root, string code, map<char, string>& huffCodes) {
    if (root == nullptr)
        return;

    if (root->ch != '\0') {
        huffCodes[root->ch] = code;
    }

    getCodes(root->left, code + "0", huffCodes);
    getCodes(root->right, code + "1", huffCodes);
}

void buildHuffmanTree(string S, int freq[]) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (int i = 0; i < S.length(); ++i) {
        pq.push(new Node(S[i], freq[i]));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    Node* root = pq.top();
    map<char, string> huffCodes;
    getCodes(root, "", huffCodes);


    cout << "\nHuffman codes will be:\n";
    for (auto it : huffCodes) {
        cout << it.first << " : " << it.second << endl;
    }
}

int main() {
    string S;
    cout << "Enter the string S: ";
    cin >> S;

    int n = S.length();
    int freq[n];
    cout << "Enter the frequencies for each character in order:\n";
    for (int i = 0; i < n; ++i) {
        cin >> freq[i];
    }

    buildHuffmanTree(S, freq);

    return 0;
}