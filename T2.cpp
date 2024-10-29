#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;

    Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
};
double f(int i){
    return 1.0 /(i+1);
}

void primerExperimento(int N, int M) {
    ABB abb;
    splayTree splay;
    vector<int> N_values, M_values;

    for (int i = 0; i < N; i++) {
        N_values.push_back(rand());
    }

    int buscar = M / N;
    for (int i = 0; i < M; i++) {
        M_values.push_back(N_values[i % buscar]);
    }

    shuffle(M_values.begin(), M_values.end(), default_random_engine(0));

    // Inserta los valores de 1 a N en ambos árboles
    for (int i = 1; i <= N; i++) {
        abb.insert(i);
        splay.insert(i);
    }

    // Busca los valores de 1 a M en ambos árboles
    for (int i = 1; i <= M; i++) {
        abb.search(i);
        splay.search(i);
    }
}

void segundoExperimento(int N, int M){
    ABB abb;
    splayTree splay;
    vector<int> N_values, B;
    for(int i = 0; i < N; i++){
        int x = rand();
        N_values.push_back(x);
        abb.insert(x);
        splay.insert(x);
    }
    for(int i = 0; i < M; i++){
        int x= floor(f(i)*N);
        for(int j = 0; j < x; j++){
            B.push_back(N_values[j]);
        }
    }
    shuffle(B.begin(), B.end(), default_random_engine(0));
    for(int i = 0; i < M; i++){
        abb.search(B[i]);
        splay.search(B[i]);
    }
}



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
        void splay(int value) {
            splay(root);
        };
        void print() {
            print(root);
        };
        
    
    private:
    Node* root;

    void zig(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = x;
        }
        y->right = x;

        y->parent = x->parent;
        if (x->parent != nullptr) {
            if (x->parent->left == x) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
        }
        x->parent = y;

        if (x == root) {
            root = y;
        }
    }

    void zag(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->left = x;

        y->parent = x->parent;
        if (x->parent != nullptr) {
            if (x->parent->left == x) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
        }
        x->parent = y;

        if (x == root) {
            root = y;
        }
    }



    void splay(Node* x) {
        if (x == nullptr) {
            return;
        }

        while (x->parent != nullptr) {
            Node* parent = x->parent;
            Node* grandparent = parent->parent;

            if (grandparent == nullptr) {
                // Rotación simple
                if (x == parent->left) {
                    zig(parent);
                } else {
                    zag(parent);
                }
            } else if (x == parent->left && parent == grandparent->left) {
                // Zig-Zig
                zig(grandparent);
                zig(parent);
            } else if (x == parent->right && parent == grandparent->right) {
                // Zag-Zag
                zag(grandparent);
                zag(parent);
            } else if (x == parent->left && parent == grandparent->right) {
                // Zig-Zag
                zig(parent);
                zag(grandparent);
            } else {
                // Zag-Zig
                zag(parent);
                zig(grandparent);
            }
        }

        root = x;
    }

    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->value) {
            Node* leftChild = insert(node->left, value);
            node->left = leftChild;
            leftChild->parent = node;
        } else if (value > node->value) {
            Node* rightChild = insert(node->right, value);
            node->right = rightChild;
            rightChild->parent = node;
        }
        return node;
    }

    Node* search(Node* node, int value) {
        if (node == nullptr || node->value == value) {
            return node;
        }
        if (value < node->value) {
            return search(node->left, value);
        }
        return search(node->right, value);
    }

    void print(Node* node) {
        if (node == nullptr) {
            return;
        }
        print(node->left);
        cout << node->value << " ";
        print(node->right);
    }
};

int main() {
    // Ejecuta la experimentación en ambos árboles
    primerExperimento(1000, 10000);

    return 0;
}
