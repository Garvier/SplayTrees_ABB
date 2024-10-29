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


double f(int i, int N) {
    double sum = 0.0;
    for (int j = 0; j < N; j++) {
        sum += 1.0 / pow(j + 1, 2);
    }
    double C = 1.0 / sum;
    return C / pow(i + 1, 2);
}


void primerExperimento(int N, int M) {
    ABB abb;
    splayTree splay;
    vector<int> N_values, M_values;

    // Generar N valores aleatorios y insertarlos en los árboles
    for (int i = 0; i < N; i++) {
        int x = rand();
        N_values.push_back(x);
        abb.insert(x);
        splay.insert(x);
    }

    // Crear M/N copias de cada elemento y agregarlas a M_values
    int copias = M / N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < copias; j++) {
            M_values.push_back(N_values[i]);
        }
    }


    int resto = M % N;
    for (int i = 0; i < resto; i++) {
        M_values.push_back(N_values[i]);
    }

    // Permutar aleatoriamente M_values
    shuffle(M_values.begin(), M_values.end(), default_random_engine(0));

    // Realizar las búsquedas
    for (int i = 0; i < M_values.size(); i++) {
        abb.search(M_values[i]);
        splay.search(M_values[i]);
    }
}


void segundoExperimento(int N, int M) {
    ABB abb;
    splayTree splay;
    vector<int> N_values, B;

    // Generar N valores aleatorios y insertarlos en los árboles
    for (int i = 0; i < N; i++) {
        int x = rand();
        N_values.push_back(x);
        abb.insert(x);
        splay.insert(x);
    }

    // Crear el arreglo B utilizando la función de probabilidad f(i, N)
    for (int i = 0; i < N; i++) {
        double prob = f(i, N);
        int s_i = floor(M * prob);
        for (int j = 0; j < s_i; j++) {
            B.push_back(N_values[i]);
        }
    }

    // Permutar aleatoriamente B
    shuffle(B.begin(), B.end(), default_random_engine(time(0)));

    // Realizar las búsquedas
    for (int i = 0; i < B.size(); i++) {
        abb.search(B[i]);
        splay.search(B[i]);
    }
}


void tercerExperimento(int N, int M) {
    ABB abb;
    splayTree splay;
    vector<int> N_values, M_values;

    // Generar N valores aleatorios
    for (int i = 0; i < N; i++) {
        int x = rand();
        N_values.push_back(x);
    }

    sort(N_values.begin(), N_values.end());


    for (int i = 0; i < N; i++) {
        abb.insert(N_values[i]);
        splay.insert(N_values[i]);
    }

    int copias = M / N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < copias; j++) {
            M_values.push_back(N_values[i]);
        }
    }

    // Manejar el resto si M % N != 0
    int resto = M % N;
    for (int i = 0; i < resto; i++) {
        M_values.push_back(N_values[i]);
    }

    shuffle(M_values.begin(), M_values.end(), default_random_engine(0));

    // Realizar las búsquedas
    for (int i = 0; i < M_values.size(); i++) {
        abb.search(M_values[i]);
        splay.search(M_values[i]);
    }
}


void cuartoExperimento(int N, int M) {
    ABB abb;
    splayTree splay;
    vector<int> A_values, C_values, M_values;

    // Generar N valores aleatorios y almacenarlos en A_values
    for (int i = 0; i < N; i++) {
        int x = rand();
        A_values.push_back(x);
    }

    // Copiar A_values a C_values y ordenar C_values
    C_values = A_values;
    sort(C_values.begin(), C_values.end());

    // Insertar los elementos ordenados de C_values en los árboles
    for (int i = 0; i < N; i++) {
        abb.insert(C_values[i]);
        splay.insert(C_values[i]);
    }

    // Crear M_values utilizando la función de probabilidad f(i, N) basada en A_values
    for (int i = 0; i < N; i++) {
        double prob = f(i, N);
        int s_i = floor(M * prob);
        for (int j = 0; j < s_i; j++) {
            M_values.push_back(A_values[i]); // Usamos A_values para mantener el desorden
        }
    }

    // Permutar aleatoriamente M_values
    shuffle(M_values.begin(), M_values.end(), default_random_engine(time(0)));

    // Realizar las búsquedas
    for (int i = 0; i < M_values.size(); i++) {
        abb.search(M_values[i]);
        splay.search(M_values[i]);
    }
}

int main() {
    // Ejecuta la experimentación en ambos árboles
    // falta generar los N y el calculo de las ejecuciones de cada una
    primerExperimento(1000, 10000);
    segundoExperimento(1000, 10000);
    tercerExperimento(1000, 10000);
    cuartoExperimento(1000, 10000);
    return 0;
}
