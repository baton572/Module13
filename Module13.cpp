#include <iostream>

#define SIZE 10
#define VERYBIGINT 1000000000

template <typename T>
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
    void addVertex(T t);
    // добавление ребра
    void addEdge(T t1, T t2, int weight = 1);
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

    void findMinDistancesFloyd(int notFarther);

private:
    bool edgeExists(int v1, int v2);
    bool vertexExists(int v);

    int matrix[SIZE][SIZE]; // матрица смежности

    int vertexes[SIZE] = { 0 }; // хранилище вершин
    int vertexCount; // количество добавленных вершин
    T params[SIZE] = { "" };
};

void Graph<int>::addVertex(int vnumber)
{
    vertexes[vertexCount++] = vnumber;
}

template <typename T> void Graph<T>::addVertex(T t)
{
    params[vertexCount] = t;
    vertexes[vertexCount] = vertexCount++;
}

void Graph<int>::addEdge(int v1, int v2, int weight)
{
    matrix[v1][v2] = weight;
    matrix[v2][v1] = weight;
}

template <typename T> void Graph<T>::addEdge(T t1, T t2, int weight)
{
    int i = 0;
    int j = 0;
    //
    for (i; i < SIZE; ++i)
    {
        if (params[i] == t1)
            break;
    }
    for (j; j < SIZE; ++j)
    {
        if (params[j] == t2)
            break;
    }
    if ((i < SIZE) && (j < SIZE))
    {
        matrix[i][j] = weight;
        matrix[j][i] = weight;
    }
}

template <typename T> void Graph<T>::depth(int start)
{
    bool visited[SIZE]; // список посещенных вершин
    for (int i = 0; i < SIZE; i++)
        visited[i] = false; // инициализируем как непосещенные
    depthInner(start, visited); // запуск алгоритма 

    std::cout << std::endl;
}

template <typename T> void Graph<T>::depthInner(int current, bool visited[])
{
    std::cout << "v" << current << " -> "; // вывод текущей
    visited[current] = true; // помечаем как посещенную
    for (int i = 0; i < SIZE; i++)
    {
        if (edgeExists(current, i) && !visited[i])
            depthInner(i, visited); // если существует ребро и вершина не посещалась, то пройдем по нему в смежную вершину

    }
}

template <typename T> int Graph<T>::findPathCount(int from, int to)
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

template <typename T> int Graph<T>::findMinPath(int from, int to)
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

template <typename T> void Graph<T>::depthPaths(int current, int to, int& n, int& pathMin, int pathLength, bool visited[])
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
template <typename T> bool Graph<T>::edgeExists(int v1, int v2)
{
    return matrix[v1][v2] != 0;
}

/*Для проверки, существует ли вершина, нужно проверить, есть ли ее номер в массиве vertexes.*/
template <typename T> bool Graph<T>::vertexExists(int vnumber)
{
    for (int i = 0; i < vertexCount; i++)
        if (vertexes[i] == vnumber)
            return true;
    return false;
}

template <typename T> void Graph<T>::findMinDistancesFloyd(int notFarther)
{
    int weights[SIZE][SIZE]; // матрица путей
    // инициализаци матрицы
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == j)
            {
                weights[i][j] = 0; // путь до самой себя равен 0
            }
            else {
                if (!edgeExists(i, j))
                {
                    weights[i][j] = VERYBIGINT; // если ребра нет
                }
                else {
                    weights[i][j] = matrix[i][j]; // если ребро есть
                }
            }
        }
    }

    for (int k = 0; k < vertexCount; k++) // итерации по k
    {
        int ck = vertexes[k]; // возьмем номер вершины
        for (int i = 0; i < vertexCount; i++)
        {
            if (i == k)
                continue;
            int ci = vertexes[i];
            for (int j = 0; j < vertexCount; j++)
            {
                if (j == k)
                    continue;
                int cj = vertexes[j];
                if (weights[ci][ck] + weights[ck][cj] < weights[ci][cj]) {
                    // пересчет мматрицы путей
                    weights[ci][cj] = weights[ci][ck] + weights[ck][cj];
                }
            }
        }
    }

    for (int i = 0; i < vertexCount; ++i)
    {
        for (int j = i + 1; j < vertexCount; ++j)
        {
            if (weights[i][j] <= notFarther)
                std::cout << params[i] << " - " << params[j] << std::endl;
        }
    }
}

int main()
{
    Graph< std::string > g;

    g.addVertex("Friend0");
    g.addVertex("Friend1");
    g.addVertex("Friend2");
    g.addVertex("Friend3");
    g.addVertex("Friend4");
    g.addVertex("Friend5");
    g.addVertex("Friend6");
    g.addVertex("Friend7");
    g.addVertex("Friend8");

    g.addEdge("Friend0", "Friend1");
    g.addEdge("Friend0", "Friend2");
    g.addEdge("Friend0", "Friend3");
    g.addEdge("Friend1", "Friend4");
    g.addEdge("Friend2", "Friend5");
    //g.addEdge("Friend3", "Friend4");
    //g.addEdge("Friend3", "Friend5");
    //g.addEdge("Friend3", "Friend6");
    //g.addEdge("Friend3", "Friend7");
    //g.addEdge("Friend3", "Friend8");
    g.addEdge("Friend4", "Friend7");
    g.addEdge("Friend5", "Friend8");
    //g.addEdge("Friend6", "Friend7");
    g.addEdge("Friend6", "Friend8");

    g.findMinDistancesFloyd(3);
    return 0;
}