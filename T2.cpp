#include <iostream>
#include <chrono>
#include <random>
using namespace std;
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

// Estructura para las métricas del experimento
struct Metrics
{
    double tiempoBusquedaABB;
    double tiempoBusquedaSplay;
};

Metrics guardarMetricas(double tABB, double tSplay)
{
    Metrics metrics;
    metrics.tiempoBusquedaABB = tABB;
    metrics.tiempoBusquedaSplay = tSplay;
    return metrics;
}

struct Node
{
    int value;
    Node *left;
    Node *right;
    Node *parent;

    Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

class ABB
{
public:
    ABB() : root(nullptr) {}

    void insert(int value)
    {
        root = insert(root, value);
    };
    bool search(int value)
    {
        return search(root, value);
    };
    void print()
    {
        print(root);
    };

private:
    Node *root;
    Node *insert(Node *node, int value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }
        if (value < node->value)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->value)
        {
            node->right = insert(node->right, value);
        }
        return node;
    }
    bool search(Node *node, int value)
    {
        if (node == nullptr)
        {
            return false;
        }
        if (node->value == value)
        {
            return true;
        }
        if (value < node->value)
        {
            return search(node->left, value);
        }
        return search(node->right, value);
    };
    void print(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        print(node->left);
        cout << node->value << " ";
        print(node->right);
    };
};

class splayTree
{
public:
    splayTree() : root(nullptr) {}

    void insert(int value)
    {
        root = insert(root, value);
        root = splay(root, value);
    }

    bool search(int value)
    {
        Node *result = search(root, value);
        if (result != nullptr)
        {
            root = splay(root, value); // Realizar splay si se encuentra el valor
            return true;
        }
        return false;
    }

    void splay(int value)
    {
        root = splay(root, value);
    }

    void print()
    {
        print(root);
    }

private:
    Node *root;

    // Método para rotación hacia la derecha
    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        y->left = x->right;
        if (x->right != nullptr)
            x->right->parent = y;
        x->right = y;

        x->parent = y->parent;
        y->parent = x;
        return x;
    }

    // Método para rotación hacia la izquierda
    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->left = x;

        y->parent = x->parent;
        x->parent = y;
        return y;
    }

    // Método de splay modificado
    Node *splay(Node *root, int key)
    {
        // Caso base: si root es nulo o la clave ya está en root
        if (root == nullptr || root->value == key)
            return root;

        // Si la clave está en el subárbol izquierdo
        if (root->value > key)
        {
            // Si el subárbol izquierdo es nulo, terminamos
            if (root->left == nullptr)
                return root;

            // Zig-Zig (Izquierda-Izquierda)
            if (root->left->value > key)
            {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            }
            else if (root->left->value < key) // Zig-Zag (Izquierda-Derecha)
            {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }

            // Segunda rotación
            return (root->left == nullptr) ? root : rightRotate(root);
        }
        else // Si la clave está en el subárbol derecho
        {
            // Si el subárbol derecho es nulo, terminamos
            if (root->right == nullptr)
                return root;

            // Zig-Zag (Derecha-Izquierda)
            if (root->right->value > key)
            {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            }
            else if (root->right->value < key) // Zag-Zag (Derecha-Derecha)
            {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            }

            // Segunda rotación
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

    Node *insert(Node *node, int value)
    {
        if (node == nullptr)
            return new Node(value);
        if (value < node->value)
        {
            Node *leftChild = insert(node->left, value);
            node->left = leftChild;
            leftChild->parent = node;
        }
        else if (value > node->value)
        {
            Node *rightChild = insert(node->right, value);
            node->right = rightChild;
            rightChild->parent = node;
        }
        return node;
    }

    Node *search(Node *node, int value)
    {
        if (node == nullptr || node->value == value)
            return node;
        if (value < node->value)
            return search(node->left, value);
        return search(node->right, value);
    }

    void print(Node *node)
    {
        if (node == nullptr)
            return;
        print(node->left);
        cout << node->value << " ";
        print(node->right);
    }
};

double f(int i, int N)
{
    double sum = 0.0;
    for (int j = 0; j < N; j++)
    {
        sum += 1.0 / pow(j + 1, 2);
    }
    double C = 1.0 / sum;
    return C / pow(i + 1, 2);
}

Metrics primerExperimento(int N, int M)
{
    cout << "=== PRIMER EXPERIMENTO ===" << endl;

    ABB abb;
    splayTree splay;

    auto start = chrono::high_resolution_clock::now();

    // Generar N valores aleatorios y se insertan en B
    vector<int> N_values, M_values;
    for (int i = 0; i < N; i++)
    {
        int x = rand();
        N_values.push_back(x);
    }

    // Crear M/N copias de cada elemento y agregarlas a M_values
    int copias = M / N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < copias; j++)
        {
            M_values.push_back(N_values[i]);
        }
    }

    int resto = M % N;
    for (int i = 0; i < resto; i++)
    {
        M_values.push_back(N_values[i]);
    }

    // Permutar aleatoriamente M_values
    shuffle(M_values.begin(), M_values.end(), default_random_engine(0));

    // Insertar  y buscar en el ABB
    auto start_insert_ABB = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        abb.insert(N_values[i]);
    };
    auto end_insert_ABB = chrono::high_resolution_clock::now();
    cout << "Tiempo Insercion ABB Primer Experimento: "
         << chrono::duration_cast<chrono::milliseconds>(end_insert_ABB - start_insert_ABB).count()
         << " ms" << endl;

    auto start_search_ABB = chrono::high_resolution_clock::now();
    for (int i = 0; i < M; i++)
    {
        abb.search(M_values[i]);
    }
    auto end_search_ABB = chrono::high_resolution_clock::now();
    auto tBusquedaABB = chrono::duration_cast<chrono::milliseconds>(end_search_ABB - start_search_ABB).count();
    cout << "Tiempo busqueda ABB Primer Experimento: "
         << tBusquedaABB
         << " ms" << endl;

    // Insertar y buscar en el Splay
    auto start_insert_splay = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        splay.insert(N_values[i]);
    };
    auto end_insert_splay = chrono::high_resolution_clock::now();
    cout << "Tiempo Insercion Splay Primer Experimento: "
         << chrono::duration_cast<chrono::milliseconds>(end_insert_splay - start_insert_splay).count()
         << " ms" << endl;

    auto start_search_splay = chrono::high_resolution_clock::now();
    for (int i = 0; i < M; i++)
    {
        splay.search(M_values[i]);
    }
    auto end_search_splay = chrono::high_resolution_clock::now();
    auto tBusquedaSplay = chrono::duration_cast<chrono::milliseconds>(end_search_splay - start_search_splay).count();
    cout << "Tiempo busqueda Splay Primer Experimento: "
         << tBusquedaSplay
         << " ms" << endl;

    return guardarMetricas(tBusquedaABB, tBusquedaSplay);
}

Metrics segundoExperimento(int N, int M)
{
    cout << "=== SEGUNDO EXPERIMENTO ===" << endl;

    ABB abb;
    splayTree splay;
    vector<int> N_values, B;

    // Generar N valores aleatorios y insertarlos en los árboles
    for (int i = 0; i < N; i++)
    {
        int x = rand();
        N_values.push_back(x);
    }

    // Crear el arreglo B utilizando la función de probabilidad f(i, N)
    for (int i = 0; i < N; i++)
    {
        double prob = f(i, N);
        int s_i = floor(M * prob);
        for (int j = 0; j < s_i; j++)
        {
            B.push_back(N_values[i]);
        }
    }

    // Permutar aleatoriamente B
    shuffle(B.begin(), B.end(), default_random_engine(time(0)));

    // Realizar las inserciones y busquedas en el ABB
    auto start_insert_ABB = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        abb.insert(N_values[i]);
    }
    auto end_insert_ABB = chrono::high_resolution_clock::now();
    cout << "Tiempo segundo experimento insercion abb: "
         << chrono::duration_cast<chrono::milliseconds>(end_insert_ABB - start_insert_ABB).count()
         << " ms" << endl;

    auto start_search_ABB = chrono::high_resolution_clock::now();
    for (int i = 0; i < M; i++)
    {
        abb.search(B[i]);
    }
    auto end_search_ABB = chrono::high_resolution_clock::now();
    auto tBusquedaABB = chrono::duration_cast<chrono::milliseconds>(end_search_ABB - start_search_ABB).count();
    cout << "Tiempo segundo experimento busqueda abb: "
         << tBusquedaABB
         << " ms" << endl;

    // Realizar las inserciones y busquedas en el Splay
    auto start_insert_splay = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        splay.insert(N_values[i]);
    }
    auto end_insert_splay = chrono::high_resolution_clock::now();
    cout << "Tiempo segundo experimento insercion splay: "
         << chrono::duration_cast<chrono::milliseconds>(end_insert_splay - start_insert_splay).count()
         << " ms" << endl;

    auto start_search_splay = chrono::high_resolution_clock::now();
    for (int i = 0; i < M; i++)
    {
        splay.search(B[i]);
    }
    auto end_search_splay = chrono::high_resolution_clock::now();
    auto tBusquedaSplay = chrono::duration_cast<chrono::milliseconds>(end_search_splay - start_search_splay).count();
    cout << "Tiempo segundo experimento busqueda splay: "
         << tBusquedaSplay
         << " ms" << endl;

    return guardarMetricas(tBusquedaABB, tBusquedaSplay);
}

Metrics tercerExperimento(int N, int M)
{
    cout << "=== TERCER EXPERIMENTO ===" << endl;

    ABB abb;
    splayTree splay;
    vector<int> N_values, M_values;

    // Generar N valores aleatorios
    for (int i = 0; i < N; i++)
    {
        int x = rand();
        N_values.push_back(x);
    }

    sort(N_values.begin(), N_values.end());

    int copias = M / N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < copias; j++)
        {
            M_values.push_back(N_values[i]);
        }
    }

    // Manejar el resto si M % N != 0
    int resto = M % N;
    for (int i = 0; i < resto; i++)
    {
        M_values.push_back(N_values[i]);
    }

    shuffle(M_values.begin(), M_values.end(), default_random_engine(0));

    // Realizar las inserciones y busquedas al ABB
    auto start_insert_ABB = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        abb.insert(N_values[i]);
    }
    auto end_insert_ABB = chrono::high_resolution_clock::now();
    cout << "Tiempo tercer experimento insert abb: "
         << chrono::duration_cast<chrono::milliseconds>(end_insert_ABB - start_insert_ABB).count()
         << " ms" << endl;

    auto start_search_ABB = chrono::high_resolution_clock::now();
    for (int i = 0; i < M_values.size(); i++)
    {
        abb.search(M_values[i]);
    }
    auto end_search_ABB = chrono::high_resolution_clock::now();
    auto tBusquedaABB = chrono::duration_cast<chrono::milliseconds>(end_search_ABB - start_search_ABB).count();
    cout << "Tiempo tercer experimento buscar abb: "
         << tBusquedaABB
         << " ms" << endl;

    // Realizar las inserciones y busquedas al Splay
    auto start_insert_splay = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        splay.insert(N_values[i]);
    }
    auto end_insert_splay = chrono::high_resolution_clock::now();
    cout << "Tiempo tercer experimento insert splay: "
         << chrono::duration_cast<chrono::milliseconds>(end_insert_splay - start_insert_splay).count()
         << " ms" << endl;

    auto start_search_splay = chrono::high_resolution_clock::now();
    for (int i = 0; i < M_values.size(); i++)
    {
        splay.search(M_values[i]);
    }
    auto end_search_splay = chrono::high_resolution_clock::now();
    auto tBusquedaSplay = chrono::duration_cast<chrono::milliseconds>(end_search_splay - start_search_splay).count();
    cout << "Tiempo tercer experimento buscar splay: "
         << tBusquedaSplay
         << " ms" << endl;

    return guardarMetricas(tBusquedaABB, tBusquedaSplay);
}

Metrics cuartoExperimento(int N, int M)
{
    cout << "=== CUARTO EXPERIMENTO ===" << endl;

    ABB abb;
    splayTree splay;
    vector<int> A_values, C_values, M_values;

    // Generar N valores aleatorios y almacenarlos en A_values
    for (int i = 0; i < N; i++)
    {
        int x = rand();
        A_values.push_back(x);
    }

    // Copiar A_values a C_values y ordenar C_values
    C_values = A_values;
    sort(C_values.begin(), C_values.end());

    // Crear M_values utilizando la función de probabilidad f(i, N) basada en A_values
    for (int i = 0; i < N; i++)
    {
        double prob = f(i, N);
        int s_i = floor(M * prob);
        for (int j = 0; j < s_i; j++)
        {
            M_values.push_back(A_values[i]); // Usamos A_values para mantener el desorden
        }
    }
    // Permutar aleatoriamente M_values
    shuffle(M_values.begin(), M_values.end(), default_random_engine(time(0)));

    // Insertar y buscar en splay tree
    auto start_insert_splay = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        splay.insert(C_values[i]);
    }
    auto end_insert_splay = chrono::high_resolution_clock::now();
    cout << "Tiempo cuarto experimento: "
         << chrono::duration_cast<chrono::milliseconds>(end_insert_splay - start_insert_splay).count()
         << " ms" << endl;
    auto start_search_splay = chrono::high_resolution_clock::now();
    for (int i = 0; i < M_values.size(); i++)
    {
        splay.search(M_values[i]);
    }
    auto end_search_splay = chrono::high_resolution_clock::now();
    auto tBusquedaSplay = chrono::duration_cast<chrono::milliseconds>(end_search_splay - start_search_splay).count();
    cout << "Tiempo cuarto experimento: "
         << tBusquedaSplay
         << " ms" << endl;

    // Insertar y buscar en abb tree
    auto start_insert_abb = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        abb.insert(C_values[i]);
    }
    auto end_insert_abb = chrono::high_resolution_clock::now();
    cout << "Tiempo cuarto experimento: "
         << chrono::duration_cast<chrono::milliseconds>(end_insert_abb - start_insert_abb).count()
         << " ms" << endl;

    auto start_search_abb = chrono::high_resolution_clock::now();
    for (int i = 0; i < M_values.size(); i++)
    {
        abb.search(M_values[i]);
    }
    auto end_search_abb = chrono::high_resolution_clock::now();
    auto tBusquedaABB = chrono::duration_cast<chrono::milliseconds>(end_search_abb - start_search_abb).count();
    cout << "Tiempo cuarto experimento buscar abb: "
         << tBusquedaABB
         << " ms" << endl;

    return guardarMetricas(tBusquedaABB, tBusquedaSplay);
}

Metrics busquedaPrimerExperimento(ABB abb, splayTree splay, vector<int> B)
{
    auto start_search_ABB = chrono::high_resolution_clock::now();
    for (int i = 0; i < B.size(); i++)
    {
        abb.search(B[i]);
    }
    auto end_search_ABB = chrono::high_resolution_clock::now();
    auto tBusquedaABB = chrono::duration_cast<chrono::milliseconds>(end_search_ABB - start_search_ABB).count();

    auto start_search_splay = chrono::high_resolution_clock::now();
    for (int i = 0; i < B.size(); i++)
    {
        splay.search(B[i]);
    }
    auto end_search_splay = chrono::high_resolution_clock::now();
    auto tBusquedaSplay = chrono::duration_cast<chrono::milliseconds>(end_search_splay - start_search_splay).count();

    return guardarMetricas(tBusquedaABB, tBusquedaSplay);
}

void ejecutarExperimentos(int N, int M)
{
    // Generar vector A y el vector B
    vector<int> A;
    vector<int> B;
    vector<int> Bprob;
    ABB abb;
    splayTree splay;
    for (int i = 0; i < N; i++)
    {
        int A_i = rand();
        A.push_back(rand());

        // Creamos los arboles e insertamos el valor A_i
        abb.insert(A_i);
        splay.insert(A_i);

        // Guardamos M/N copias de A_i en B
        for (int j = 0; j < M / N; j++)
        {
            B.push_back(A_i);
        }

        // Guardamos M * f(i) veces
    }

    // BUSQUEDA EXPERIMENTO 1
    vector<int> shuffle_B = B;
    shuffle(shuffle_B.begin(), shuffle_B.end(), default_random_engine(0));
    Metrics metricaPrimerExp = busquedaPrimerExperimento(abb, splay, shuffle_B);

    // BUSQUEDA EXPERIMENTO 2
}

int main()
{
    // Crear TSV
    ofstream data_tsv;
    data_tsv.open("data.tsv");
    data_tsv << "i\tN\tM\ttiempoABB\ttiempoSplay\n"; // TSV Header

    // Ejecutar los experimentos
    // desde 0.1 hasta 1
    for (float i = 0.1; i <= 0.2; i += 0.1)
    {
        int N = pow(10, 6) * i;
        int M = 100 * N;
        Metrics primerExp = primerExperimento(N, M);
        data_tsv << i << "\t" << N << "\t" << M << "\t" << primerExp.tiempoBusquedaABB << "\t" << primerExp.tiempoBusquedaSplay << "\n";

        Metrics segundoExp = segundoExperimento(N, M);
        data_tsv << i << "\t" << N << "\t" << M << "\t" << segundoExp.tiempoBusquedaABB << "\t" << segundoExp.tiempoBusquedaSplay << "\n";

        Metrics tercerExp = tercerExperimento(N, M);
        data_tsv << i << "\t" << N << "\t" << M << "\t" << tercerExp.tiempoBusquedaABB << "\t" << tercerExp.tiempoBusquedaSplay << "\n";

        Metrics cuartoExp = cuartoExperimento(N, M);
        data_tsv << i << "\t" << N << "\t" << M << "\t" << cuartoExp.tiempoBusquedaABB << "\t" << cuartoExp.tiempoBusquedaSplay << "\n";
    }

    data_tsv.close();
    printf("Finalizado\n");
    return 0;
}
