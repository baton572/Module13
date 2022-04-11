#include <iostream>
#include <vector>

#define SIZE 10
#define VERYBIGINT 1000000000

class Graph {
public:
    Graph()
    {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                matrix[i][j] = 0;
        vertexCount = 0;
    };
    // добавление вершины
    void addVertex(int vnumber);
    // добавление ребра
    void addEdge(int v1, int v2, int weight);
    // удаление вершины
    void delVertex(int vnumber);
    // удаление ребра
    void delEdge(int v1, int v2);

    void depth(int start);
    void depthInner(int current, bool visited[]);
    void width(int start);

    int findPathCount(int from, int to);
    int findMinPath(int from, int to);
    void depthPaths(int current, int to, int& n, int& pathMin, int pathLength, bool visited[]);

private:
    bool edgeExists(int v1, int v2);
    bool vertexExists(int v);

    int matrix[SIZE][SIZE]; // матрица смежности

    int vertexes[SIZE] = { 0 }; // хранилище вершин
    int vertexCount; // количество добавленных вершин
};

void Graph::addVertex(int vnumber)
{
    vertexes[vertexCount++] = vnumber;
}

void Graph::addEdge(int v1, int v2, int weight)
{
    matrix[v1][v2] = weight;
    matrix[v2][v1] = weight;
}

void Graph::depth(int start)
{
    bool visited[SIZE]; // список посещенных вершин
    for (int i = 0; i < SIZE; i++)
        visited[i] = false; // инициализируем как непосещенные
    depthInner(start, visited); // запуск алгоритма 

    std::cout << std::endl;
}

void Graph::depthInner(int current, bool visited[])
{
    std::cout << "v" << current << " -> "; // вывод текущей
    visited[current] = true; // помечаем как посещенную
    for (int i = 0; i < SIZE; i++)
    {
        if (edgeExists(current, i) && !visited[i])
            depthInner(i, visited); // если существует ребро и вершина не посещалась, то пройдем по нему в смежную вершину

    }
}

int Graph::findPathCount(int from, int to)
{
    int n = 0;
    int pathMin = VERYBIGINT;
    int path = 0;
    //
    bool visited[SIZE]; // список посещенных вершин
    for (int i = 0; i < SIZE; i++)
        visited[i] = false; // инициализируем как непосещенные
    depthPaths(from, to, n, pathMin, path, visited); // запуск алгоритма 
    //
    std::cout << std::endl;
    return n;
}

int Graph::findMinPath(int from, int to)
{
    int n = 0;
    int pathMin = VERYBIGINT;
    int path = 0;
    //
    bool visited[SIZE]; // список посещенных вершин
    for (int i = 0; i < SIZE; i++)
        visited[i] = false; // инициализируем как непосещенные
    depthPaths(from, to, n, pathMin, path, visited); // запуск алгоритма 
    //
    return pathMin;
}

void Graph::depthPaths(int current, int to, int& n, int& pathMin, int pathLength, bool visited[])
{
    if (current == to)
    {
        // если дошли до второй вершины, увеличиваем счётчик путей
        // и выходим
        ++n;
        //
        if (pathLength < pathMin)
            pathMin = pathLength;
        return;
    }
    visited[current] = true; // отмечаем как посещенную
    for (int i = 0; i < SIZE; i++)
    {
        if (edgeExists(current, i) && !visited[i])
        {
            pathLength += matrix[current][i];
            //
            depthPaths(i, to, n, pathMin, pathLength, visited);
            //
            pathLength -= matrix[current][i];
        }
    }
    // отмечаем, что путь уже не содержит эту вершину
    visited[current] = false;
}

/* Для проверки, существует ли ребро, нужно посмотреть значение элемента матрицы смежности с индексами номеров вершин (если есть ребро, он отличен от 0).*/
bool Graph::edgeExists(int v1, int v2)
{
    return matrix[v1][v2] != 0;
}

/*Для проверки, существует ли вершина, нужно проверить, есть ли ее номер в массиве vertexes.*/
bool Graph::vertexExists(int vnumber)
{
    for (int i = 0; i < vertexCount; i++)
        if (vertexes[i] == vnumber)
            return true;
    return false;
}

void Graph::delVertex(int vnumber)
{
    // обнуляем столбец и строку матрицы
    for (int i = 0; i < SIZE; i++)
    {
        matrix[i][vnumber] = 0;
        matrix[vnumber][i] = 0;
    }
    // удаляем вершину из списка вершин
    int foundIndex = -1;
    for (int i = 0; i < vertexCount; i++)
    {
        if (vertexes[i] == vnumber)
            foundIndex = i;
    }
    --vertexCount;
    for (int i = foundIndex; i < vertexCount; i++)
    {
        vertexes[i] = vertexes[i + 1];
    }
}

void Graph::delEdge(int v1, int v2)
{
    matrix[v1][v2] = 0;
    matrix[v2][v1] = 0;
}

void Graph::width(int start)
{
    int queue_to_visit[SIZE]; // очередь вершин для обхода
    int queueCount = 0;

    bool visited[SIZE]; // список посещенных вершин
    for (int i = 0; i < SIZE; i++)
        visited[i] = false;

    queue_to_visit[queueCount++] = start; // кладем в очередь начальную вершину
    while (queueCount > 0)
    {
        // взятие из очереди вершины
        int current = queue_to_visit[0];
        queueCount--;
        for (int i = 0; i < queueCount; i++)
        {
            queue_to_visit[i] = queue_to_visit[i + 1];
        }
        visited[current] = true;
        std::cout << "v" << current << " -> ";
        // поиск смежных вершин и добавление их в очередь
        for (int i = 0; i < SIZE; i++)
        {
            bool alreadyAdded = false;
            for (int j = 0; j < queueCount; j++)
                if (queue_to_visit[j] == i)
                {
                    alreadyAdded = true;
                    break;
                }
            if (!alreadyAdded && edgeExists(current, i) && !visited[i])
                queue_to_visit[queueCount++] = i;
        }
    }
    std::cout << std::endl;
}

class Tree { // класс дерево

    struct Node { // структура узла
        Node(int _number, Node* _parent = nullptr) :
            number(_number),
            parent(_parent),
            childCount(0)
        { }
        ~Node()
        {
            for (int i = 0; i < childCount; i++)
            {
                delete children[i];
            }
        }

        int number; // номер мершины

        Node* parent; // родительская вершина
        Node* children[SIZE]; // список дочерних вершин
        int childCount; // количество детей

        void delChild(Node* child);
        void addChild(Tree::Node* newChild)
        {
            children[childCount++] = newChild;
        }
    };

public:
    Tree() {
        root = nullptr;
    }

    ~Tree() {
        if (root != nullptr)
        {
            delete root; // должны почистить за собой память

        }
    }

    void setRoot(int number);
    void addNode(int parentNumber, int newNodeNumber);

    void delNode(int nodeNumber);
    void dummy(int nodeNumber);

private:
    Node* getNodeByNumber(int number, Node* current);
    Node* root;
};

void Tree::setRoot(int number)
{
    if (root != nullptr)
    {
        // удаляем корень, если он был
        delete root;
        root = nullptr;
    }
    root = new Node(number); // устанавливаем новый корень
}

void Tree::addNode(int parentNumber, int newNodeNumber)
{
    Node* parentNode = getNodeByNumber(parentNumber, root); // нашли родителя
    Node* newNode = new Node(newNodeNumber, parentNode); // создали новую
    parentNode->addChild(newNode); // добавили к родителю
}

Tree::Node* Tree::getNodeByNumber(int number, Node* current)
{
    if (current->number == number)
        return current; // если нашли вершину с нужным узлом, возвращаем
    for (int i = 0; i < current->childCount; i++)
    {
        // обходим в глубину, пока не найдем искомую
        Node* found = getNodeByNumber(number, current->children[i]);
        if (found)
            return found;
    }
    return nullptr;
}
// удаление узла
void Tree::delNode(int number)
{
    Node* node = getNodeByNumber(number, root); // нашли вершину для удаления
    if (node)
    {
        Node* parent = node->parent; // нашли ее родителя
        if (parent)
        {
            // перебросили всех детей удаляемой вершины её родителю
            for (int i = 0; i < node->childCount; i++)
                parent->addChild(node->children[i]);
            // указали, что у удаляемой вершины, больше нет детей
            node->childCount = 0;
            // удалили вершину
            parent->delChild(node);
        }
    }
}
void Tree::Node::delChild(Node* child)
{
    int foundIndex = -1;
    for (int i = 0; i < childCount; i++)
    {
        if (children[i] == child)
            foundIndex = i; // нашли индекс удаляемой вершины в массиве
    }
    //
    delete children[foundIndex]; // удалили вершину
    childCount--; // удалили ее из массива
    //
    for (int i = foundIndex; i < childCount; i++)
        children[i] = children[i + 1];
}

class BinaryTree {
public:
    struct Node { // структура узла
        Node(int d, Node* p = nullptr);
        ~Node();
        Node* parent; // родительский узел

        Node* leftChild; // левый узел
        Node* rightChild; // правый узел

        int data; // данные - целое число
    };

    BinaryTree();
    ~BinaryTree();

    void addInt(int newdata);

    Node* findNodeByData(int finddata);
    void delInt(int deldata);
    void symmetricWalk(int output_array[]);
    void f(Node* current, int output_array[], int& size);


    //friend Table print(BinaryTree& tree);

private:
    void setNewChild(Node* child, Node* newChild = nullptr);
    void delNodeWithOneChild(Node* delNode);
    void delLeaf(Node* leaf);
    // проверка является ли узел листом        
    bool isLeaf(Node* check);
    // проверка, являтся ли узел корневым
    bool isRoot(Node* check);
    Node* root; // корневой узел
};

BinaryTree::Node::Node(int d, Node* p) :
    data(d), parent(p) {
    leftChild = nullptr;
    rightChild = nullptr;
}
//
BinaryTree::Node::~Node() {
    // чистим за собой память
    if (rightChild != nullptr)
        delete rightChild;
    if (leftChild != nullptr)
        delete leftChild;
}
//
BinaryTree::BinaryTree() {
    root = nullptr;
}
//
BinaryTree::~BinaryTree() {
    if (root != nullptr)
    {
        delete root;
    }
}
void BinaryTree::addInt(int newdata) {
    if (root == nullptr) {
        // если дерево пустое, то новый элемент станет корнем
        root = new Node(newdata);
    }
    else {
        Node* current = root; // начинаем с корня
        Node* newNode = nullptr;
        while (newNode == nullptr) {
            if (current->data >= newdata) {
                // если элемент меньше текущего, идем влево
                if (current->leftChild != nullptr) {
                    current = current->leftChild;
                    continue;
                }
                // если левого узла нет, то нашли место для нового элемента
                newNode = new Node(newdata, current);
                current->leftChild = newNode;
            }
            else {
                // если элемент меньше текущего, идем вправо
                if (current->rightChild != nullptr) {
                    current = current->rightChild;
                    continue;
                }
                // если правого узла нет, то нашли место для нового элемента
                newNode = new Node(newdata, current);
                current->rightChild = newNode;
            }
        }
    }
}
// проверка является ли узел листом        
bool BinaryTree::isLeaf(Node* check) {
    return check->leftChild == nullptr
        && check->rightChild == nullptr;
}

// проверка, являтся ли узел корневым
bool BinaryTree::isRoot(Node* check) {
    return check == root;
}

// поиск, возвращает указатель на найденный элемент
BinaryTree::Node* BinaryTree::findNodeByData(int finddata) {
    BinaryTree::Node* found = nullptr;
    //
    auto current = root;
    while (current != nullptr) {
        if (finddata < current->data)
            current = current->leftChild;
        else if (finddata > current->data)
            current = current->rightChild;
        else {
            found = current;
            break;
        }
    }
    //
    return found;
}
//
void BinaryTree::delLeaf(Node* leaf) {
    if (leaf->parent->leftChild == leaf)
        leaf->parent->leftChild = nullptr;
    else
        leaf->parent->rightChild = nullptr;
    delete leaf;
}
// удаление элемента
void BinaryTree::delInt(int deldata) {
    auto current = findNodeByData(deldata);
    if (current) {
        if (isLeaf(current)) {
            delLeaf(current);
            return;
        }
        if (current->leftChild && !current->rightChild) {
            auto newCurrent = current->leftChild;
            if (current->parent) {
                if (current->parent->leftChild == current)
                    current->parent->leftChild = newCurrent;
                else
                    current->parent->rightChild = newCurrent;
            }
            newCurrent->parent = current->parent;
        }
        else if (!current->leftChild && current->rightChild) {
            auto newCurrent = current->rightChild;
            if (current->parent) {
                if (current->parent->leftChild == current)
                    current->parent->leftChild = newCurrent;
                else
                    current->parent->rightChild = newCurrent;
            }
            newCurrent->parent = current->parent;
        }
        else {
            auto newCurrent = current->leftChild;
            if (newCurrent) {
                while (newCurrent->rightChild != nullptr) {
                    newCurrent = newCurrent->rightChild;
                }
                newCurrent->parent = current->parent;
                newCurrent->rightChild = current->rightChild;
                if (current->rightChild)
                    current->rightChild->parent = newCurrent;
                if (!isRoot(current))
                    current->parent->rightChild = newCurrent;
                else
                    root = newCurrent;
            }
        }
        current->leftChild = nullptr;
        current->rightChild = nullptr;
        delete current;
    }
}

// симметричный обход
void BinaryTree::symmetricWalk(int output_array[]) {
    // положите в output_array[] элементы дерева в порядке их обхода
    // в итоге должен получиться отсортированный массив по возрастанию
    // Ваш код должен быть здесь
    if (root) {
        int size = 0;
        f(root, output_array, size); // запуск алгоритма 
    }
}

void BinaryTree::f(Node* current, int output_array[], int& size)
{
    if (current->leftChild)
        f(current->leftChild, output_array, size);
    //
    output_array[size++] = current->data;
    //
    if (current->rightChild)
        f(current->rightChild, output_array, size);
}

int main()
{
    //Graph g;
    //g.addVertex(0);
    //g.addVertex(1);
    //g.addVertex(2);
    //g.addVertex(3);
    //g.addVertex(4);
    //g.addVertex(5);
    //g.addVertex(6);
    //g.addVertex(7);
    //g.addVertex(8);

    //g.addEdge(0, 1, 1);
    //g.addEdge(0, 2, 1);
    //g.addEdge(0, 3, 1);
    //g.addEdge(2, 5, 1);
    //g.addEdge(1, 4, 1);
    //g.addEdge(4, 3, 1);
    //g.addEdge(5, 3, 1);
    //g.addEdge(4, 7, 1);
    //g.addEdge(3, 6, 1);
    //g.addEdge(3, 7, 1);
    //g.addEdge(3, 8, 1);
    //g.addEdge(5, 8, 1);
    //g.addEdge(8, 6, 1);
    //g.addEdge(7, 6, 1);

    ////g.depth(7);

    ////g.width(7);

    //int paths = g.findPathCount(7, 2);
    //int pathLen = g.findMinPath(7, 2);

    //Tree tree;
    //tree.setRoot(2);

    //tree.addNode(2, 3);
    //tree.addNode(2, 0);
    //tree.addNode(2, 1);
    //tree.addNode(1, 4);
    //tree.addNode(4, 5);

    //tree.delNode(3);

    BinaryTree bTree;

    bTree.addInt(50);
    bTree.addInt(30);
    bTree.addInt(70);
    bTree.addInt(90);
    bTree.addInt(100);
    bTree.addInt(69);
    bTree.addInt(68);

    //bTree.delInt(1);

    int array[15];

    bTree.symmetricWalk(array);

    return 0;
}
