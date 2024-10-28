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
        void splay(int value) {
            splay(root, value);
        };
    private:
        Node* root;
        // Rotación Zig-zig
        void zigzig(Node*& node) {
            Node* parent = node->left;
            Node* grandparent = parent->left;
            
            parent->left = grandparent->right;
            grandparent->right = parent;
            node->left = parent->right;
            parent->right = node;
            
            node = grandparent;
        }

        // Rotación Zig-zag
        void zigzag(Node*& node) {
            Node* parent = node->left;
            Node* grandparent = parent->right;

            parent->right = grandparent->left;
            grandparent->left = parent;
            node->left = grandparent->right;
            grandparent->right = node;

            node = grandparent;
        }

        // Rotación Zag-zig
        void zagzig(Node*& node) {
            Node* parent = node->right;
            Node* grandparent = parent->left;

            parent->left = grandparent->right;
            grandparent->right = parent;
            node->right = grandparent->left;
            grandparent->left = node;

            node = grandparent;
        }

        // Rotación Zag-zag
        void zagzag(Node*& node) {
            Node* parent = node->right;
            Node* grandparent = parent->right;

            parent->right = grandparent->left;
            grandparent->left = parent;
            node->right = parent->left;
            parent->left = node;

            node = grandparent;
        }

        // Rotación Zig (cuando el padre es la raíz)
        void zig(Node*& node) {
            Node* parent = node->left;
            node->left = parent->right;
            parent->right = node;
            node = parent;
        }

        // Rotación Zag (cuando el padre es la raíz)
        void zag(Node*& node) {
            Node* parent = node->right;
            node->right = parent->left;
            parent->left = node;
            node = parent;
        }


        void splay(Node*& node, int value) {
            if (node == nullptr || node->value == value) {
                return;
            }

            if (value < node->value) {
                if (node->left == nullptr) {
                    return;
                }

                if (node->left->value == value) {
                    zig(node);
                } else if (node->left->left != nullptr && node->left->left->value == value) {
                    zigzig(node);
                } else if (node->left->right != nullptr && node->left->right->value == value) {
                    zigzag(node);
                } else {
                    splay(node->left, value);
                    if (node->left != nullptr) {
                        zig(node);
                    }
                }
            } else {
                if (node->right == nullptr) {
                    return;
                }

                if (node->right->value == value) {
                    zag(node);
                } else if (node->right->right != nullptr && node->right->right->value == value) {
                    zagzag(node);
                } else if (node->right->left != nullptr && node->right->left->value == value) {
                    zagzig(node);
                } else {
                    splay(node->right, value);
                    if (node->right != nullptr) {
                        zag(node);
                    }
                }
            }
        }


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
};