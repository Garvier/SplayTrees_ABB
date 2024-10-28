#include<iostream>
using namespace std;


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

int main() {
    // Probando ABB
    cout << "Probando ABB:" << endl;
    ABB abbTree;

    // Insertar valores en el ABB
    abbTree.insert(5);
    abbTree.insert(3);
    abbTree.insert(7);
    abbTree.insert(2);
    abbTree.insert(4);
    abbTree.insert(6);
    abbTree.insert(8);

    // Intentar insertar valores duplicados
    abbTree.insert(5);
    abbTree.insert(3);
    abbTree.insert(7);

    // Imprimir el ABB
    cout << "Elementos del ABB en orden: ";
    abbTree.print();
    cout << endl;

    // Buscar algunos valores
    cout << "Buscar 4 en ABB: " << (abbTree.search(4) ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscar 9 en ABB: " << (abbTree.search(9) ? "Encontrado" : "No encontrado") << endl;

    // Probando splayTree
    cout << "\nProbando splayTree:" << endl;
    splayTree splayTree;

    // Insertar valores en el splayTree
    splayTree.insert(5);
    splayTree.insert(3);
    splayTree.insert(7);
    splayTree.insert(2);
    splayTree.insert(4);
    splayTree.insert(6);
    splayTree.insert(8);

    // Intentar insertar valores duplicados
    splayTree.insert(5);
    splayTree.insert(3);
    splayTree.insert(7);

    // Imprimir el splayTree
    cout << "Elementos del splayTree en orden: ";
    splayTree.print();
    cout << endl;

    // Buscar algunos valores
    cout << "Buscar 4 en splayTree: " << (splayTree.search(4) ? "Encontrado" : "No encontrado") << endl;
    splayTree.print(); // Imprimir después de splay para ver el cambio en la estructura

    cout << "Buscar 9 en splayTree: " << (splayTree.search(9) ? "Encontrado" : "No encontrado") << endl;
    splayTree.print(); // Imprimir después de intento de búsqueda

    return 0;
}