#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <numeric>
#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

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

class ABBNodo
{
public:
    int valor;
    std::unique_ptr<ABBNodo> izquierda;
    std::unique_ptr<ABBNodo> derecha;

    ABBNodo(int val) : valor(val), izquierda(nullptr), derecha(nullptr) {}
};

class ABB
{
public:
    ABB() : raiz(nullptr) {}

    void insertar(int valor)
    {
        insertar(raiz, valor);
    }

    bool buscar(int valor) const
    {
        return buscar(raiz, valor);
    }

    void imprimirInOrden() const
    {
        inOrden(raiz);
        std::cout << std::endl;
    }

private:
    std::unique_ptr<ABBNodo> raiz;

    // Función auxiliar para insertar un valor en el árbol
    void insertar(std::unique_ptr<ABBNodo> &nodo, int valor)
    {
        if (!nodo)
        {
            nodo = std::make_unique<ABBNodo>(valor);
        }
        else if (valor < nodo->valor)
        {
            insertar(nodo->izquierda, valor);
        }
        else // Incluye el caso de duplicados aquí
        {
            insertar(nodo->derecha, valor);
        }
    }

    // Función auxiliar para buscar un valor en el árbol
    bool buscar(const std::unique_ptr<ABBNodo> &nodo, int valor) const
    {
        if (!nodo)
            return false;
        if (valor == nodo->valor)
            return true;
        if (valor < nodo->valor)
            return buscar(nodo->izquierda, valor);
        return buscar(nodo->derecha, valor);
    }

    // Función auxiliar para imprimir el árbol en orden
    void inOrden(const std::unique_ptr<ABBNodo> &nodo) const
    {
        if (!nodo)
            return;
        inOrden(nodo->izquierda);
        std::cout << nodo->valor << " ";
        inOrden(nodo->derecha);
    }
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
        else if (value >= node->value)
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

// Funcion auxiliar para crear un vector de enteros únicos
vector<int> generar_enteros_unicos(int N)
{
    std::vector<int> numeros(N);

    // Llenar el vector con números únicos [0, 1, 2, ..., N-1]
    std::iota(numeros.begin(), numeros.end(), 0);

    // Configurar el generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());

    // Mezclar el vector aleatoriamente
    std::shuffle(numeros.begin(), numeros.end(), gen);

    return numeros;
}

// Funcion auxiliar para crear el vector B de la forma M/N
vector<int> generarVectorB(vector<int> A, int N, int M)
{
    vector<int> B;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M / N; j++)
        {
            B.push_back(A[i]);
        }
    }
    return B;
}

double busquedaABB(ABB &abb, vector<int> A, unordered_map<int, int> ponderacion)
{
    double tiempoTotal = 0;

    int size = A.size();
    for (int i = 0; i < size; i++)
    {

        auto start_search_ABB = chrono::high_resolution_clock::now();
        abb.buscar(A[i]);
        auto end_search_ABB = chrono::high_resolution_clock::now();
        auto tBusquedaABB = chrono::duration_cast<chrono::milliseconds>(end_search_ABB - start_search_ABB).count();
        tiempoTotal += tBusquedaABB * ponderacion[A[i]];

        // Mostrar el progreso en incrementos del 10%
        if ((i % (size / 10)) == 0)
        {
            int porcentaje = (i * 100) / size;
            cout << "Busqueda ABB: " << porcentaje << "% completada (" << i << " de " << size << ")" << endl;
        }
    }

    return tiempoTotal;
}

Metrics busquedaExperimento(ABB &abb, splayTree splay, vector<int> A, vector<int> B, unordered_map<int, int> ponderacion)
{
    int size = B.size();

    // Realizar las busquedas en el ABB
    double tBusquedaABB = busquedaABB(abb, A, ponderacion);

    auto start_search_splay = chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++)
    {
        splay.search(B[i]);
    }
    auto end_search_splay = chrono::high_resolution_clock::now();
    auto tBusquedaSplay = chrono::duration_cast<chrono::milliseconds>(end_search_splay - start_search_splay).count();

    return guardarMetricas(tBusquedaABB, tBusquedaSplay);
}

vector<Metrics> ejecutarExperimentos(int N, int M)
{

    cout << "=== PREPARANDO ARBOLES 1 Y 2 ===" << endl;
    // Generar vector A y el vector B
    vector<int> A;
    vector<int> B;     // B es el vector que se usará en los experimentos 1 y 3
    vector<int> Bprob; // Bprob es el vector que se usará en el experimento 2 y 4
    ABB abb;
    splayTree splay;

    unordered_map<int, int> ponderacionABBConst;
    unordered_map<int, int> ponderacionABBProb;

    // Generar N valores aleatorios y se insertan en A
    A = generar_enteros_unicos(N);
    for (int i = 0; i < N; i++)
    {
        // Creamos los arboles e insertamos el valor A_i
        abb.insertar(A[i]);
        splay.insert(A[i]);

        // Guardamos M/N copias de A_i en B
        for (int j = 0; j < M / N; j++)
        {
            B.push_back(A[i]);
        }

        // Guardamos M * f(i) veces
        double prob = f(i, N);
        int s_i = floor(M * prob);
        for (int j = 0; j < s_i; j++)
        {
            Bprob.push_back(A[i]);
        }

        // Guardamos la ponderacion de A_i
        ponderacionABBConst[A[i]] = M / N;
        ponderacionABBProb[A[i]] = s_i;
    }

    vector<int> C = A; // C es el vector A ordenado
    sort(C.begin(), C.end());
    // Validar datos:
    // 1. A no tiene elementos repetidos
    // 2. B tiene M elementos
    // 3. Bprob tiene M elementos
    // En caso de que no se cumpla alguna de las condiciones, se detiene el programa
    if (unique(C.begin(), C.end()) != C.end())
    {
        cout << "Error: A tiene elementos repetidos" << endl;
        exit(1);
    }
    if (B.size() != M)
    {
        cout << "Error: B no tiene M elementos:" << B.size() << endl;
        exit(1);
    }

    cout << "=== PREPARANDO ARBOLES 3 Y 4 ===" << endl;
    // Arboles Experimento 3 y 4:
    // Se insertan los valores de A ordenados, es decir, el vector C
    ABB abb2;
    splayTree splay2;
    for (int i = 0; i < N; i++)
    {
        abb2.insertar(C[i]);
        splay2.insert(C[i]);
    }

    // BUSQUEDA EXPERIMENTO 1
    vector<int> shuffle_B = B;
    shuffle(shuffle_B.begin(), shuffle_B.end(), default_random_engine(0));
    cout << "=== BUSQUEDA EXPERIMENTO 1 ===" << endl;
    Metrics metricaPrimerExp = busquedaExperimento(abb, splay, A, shuffle_B, ponderacionABBConst);

    // BUSQUEDA EXPERIMENTO 2
    vector<int> shuffle_B2 = Bprob;
    shuffle(shuffle_B2.begin(), shuffle_B2.end(), default_random_engine(0));
    cout << "=== BUSQUEDA EXPERIMENTO 2 ===" << endl;
    Metrics metricaSegundoExp = busquedaExperimento(abb, splay, A, shuffle_B2, ponderacionABBProb);

    // BUSQUEDA EXPERIMENTO 3
    // Calcular B para el experimento 3
    vector<int> B3 = generarVectorB(C, N, M);
    vector<int> shuffle_B3 = B3;
    shuffle(shuffle_B3.begin(), shuffle_B3.end(), default_random_engine(0));
    cout << "=== BUSQUEDA EXPERIMENTO 3 ===" << endl;
    Metrics metricaTercerExp = busquedaExperimento(abb2, splay2, A, shuffle_B3, ponderacionABBConst);

    // BUSQUEDA EXPERIMENTO 4
    vector<int> shuffle_B4 = Bprob;
    shuffle(shuffle_B4.begin(), shuffle_B4.end(), default_random_engine(0));
    cout << "=== BUSQUEDA EXPERIMENTO 4 ===" << endl;
    Metrics metricaCuartoExp = busquedaExperimento(abb2, splay2, A, shuffle_B4, ponderacionABBProb);

    return {metricaPrimerExp, metricaSegundoExp, metricaTercerExp, metricaCuartoExp};
}

int main()
{
    // Crear TSV
    ofstream data_tsv;
    data_tsv.open("data.tsv");
    data_tsv << "i\tN\tM\tnExperimento\ttiempoABB\ttiempoSplay\tcPromABB\tcPromSplay\n"; // TSV Header

    // Ejecutar los experimentos
    // desde 0.1 hasta 1
    for (float i = 0.2; i <= 0.3; i += 0.1)
    {
        cout << "=== EJECUTANDO EXPERIMENTOS ITERACION " << i << " ===" << endl;

        int N = pow(10, 6) * i;
        int M = 100 * N;

        vector<Metrics> resultados = ejecutarExperimentos(N, M);
        // Primer experimento
        double tABB = resultados[0].tiempoBusquedaABB;
        double tSplay = resultados[0].tiempoBusquedaSplay;
        double cPromABB = tABB / M;
        double cPromSplay = tSplay / M;
        data_tsv << i << "\t" << N << "\t" << M << "\t1\t" << tABB << "\t" << tSplay << "\t" << cPromABB << "\t" << cPromSplay << "\n";

        // Segundo experimento
        tABB = resultados[1].tiempoBusquedaABB;
        tSplay = resultados[1].tiempoBusquedaSplay;
        cPromABB = tABB / M;
        cPromSplay = tSplay / M;
        data_tsv << i << "\t" << N << "\t" << M << "\t2\t" << tABB << "\t" << tSplay << "\t" << cPromABB << "\t" << cPromSplay << "\n";

        // Tercer experimento
        tABB = resultados[2].tiempoBusquedaABB;
        tSplay = resultados[2].tiempoBusquedaSplay;
        cPromABB = tABB / M;
        cPromSplay = tSplay / M;
        data_tsv << i << "\t" << N << "\t" << M << "\t3\t" << tABB << "\t" << tSplay << "\t" << cPromABB << "\t" << cPromSplay << "\n";

        // Cuarto experimento
        tABB = resultados[3].tiempoBusquedaABB;
        tSplay = resultados[3].tiempoBusquedaSplay;
        cPromABB = tABB / M;
        cPromSplay = tSplay / M;
        data_tsv << i << "\t" << N << "\t" << M << "\t4\t" << tABB << "\t" << tSplay << "\t" << cPromABB << "\t" << cPromSplay << "\n";
    }

    data_tsv.close();
    printf("Finalizado\n");
    return 0;
}
