#include<iostream>
using namespace std;


struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int value) {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class ABB{
    public:
        ABB() : root(nullptr) {}

        void insert(int value) {
            root = insert(root, value);
        };
        bool search(int value) {
            return search(root, value);
        };
        void print() {
            print(root);
        };
    private:
        Node* root;
        Node* insert(Node* node, int value) {
            if (node == nullptr) {
                return new Node(value);
            }
            if (value < node->value) {
                node->left = insert(node->left, value);
            } else if (value > node->value) {
                node->right = insert(node->right, value);
            }
            return node;
        }
        bool search(Node* node, int value) {
            if (node == nullptr) {
                return false;
            }
            if (node->value == value) {
                return true;
            }
            if (value < node->value) {
                return search(node->left, value);
            }
            return search(node->right, value);
        };
        void print(Node* node) {
            if (node == nullptr) {
                return;
            }
            print(node->left);
            cout << node->value << " ";
            print(node->right);
        };
};


class splayTree{
    public:
        splayTree() : root(nullptr) {}

        void insert(int value) {
            root = insert(root, value);
        };
        bool search(int value) {
            return search(root, value);
        };
        void print() {
            print(root);
        };
        void splay(int value) {
            root = splay(root, value);
        };
    private:
        
};