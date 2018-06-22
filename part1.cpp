//  part1.cpp
//  Graphs

/*
 1 ЧАСТЬ.
 
 Задание:
 Выделить внутренние полные подмножества графа путём объединения его смежных вершин.
 Информация о графе задана в виде матрицы инциденций или подмножеств смежности.
 Число вершин графа равно или не превосходит n.
 
 Решение 1 части задания для неориентированного графа:
 Граф задан в виде МАТРИЦИ ИНЦИДЕНЦИЙ.
 
 Внутренние полные подмножества графа будем называть кликами.
 
 В теории графов КЛИКОЙ неориентированного графа называется подмножество его вершин,
 любые две из которых соединены ребром. Наша же задача заключается в том, чтобы найти все такие клики в графе.
 
 Примерный алгоритм:
 1. ищем ребро, где первая вершина равна 0, если нуля нет, то +1
 2. берем это ребро и запушиваем в результирующую переменную 0 1
 3. ищем ребро, где первая вершина равна второй вершине из п.2, и пушим в рез 0 1 2
 4. ищем слудующее ребро, где есть вершина равная последней вершине из п.3 0 2
 5. проверяем, совпадают ли элементы из этого ребра с элементами рез
 6. если да, то клика найдена, если нет, то ищем следующую вершину где есть вершина равная последней вершине из п.3
 7. если таковой нет, то очищаем рез и возвращаемся в п.1
 
 
 ЗАМЕЧАНИЕ.
 Данная программа ищет клики максимальной длиной в 3 вершины.
 */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int ** test_graph1()
{
    // Тестовый граф, заданный матрицей инциденций
    int ** matrix = new int *[5];
    matrix[0] = new int[5];
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[0][3] = 1;
    matrix[0][4] = 1;
    matrix[0][5] = 0;
    
    matrix[1] = new int[5];
    matrix[1][0] = 1;
    matrix[1][1] = 1;
    matrix[1][2] = 1;
    matrix[1][3] = 0;
    matrix[1][4] = 0;
    matrix[1][5] = 0;
    
    matrix[2] = new int[5];
    matrix[2][0] = 0;
    matrix[2][1] = 1;
    matrix[2][2] = 0;
    matrix[2][3] = 0;
    matrix[2][4] = 1;
    matrix[2][5] = 0;
    
    matrix[3] = new int[5];
    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 1;
    matrix[3][3] = 1;
    matrix[3][4] = 0;
    matrix[3][5] = 1;
    
    matrix[4] = new int[5];
    matrix[4][0] = 0;
    matrix[4][1] = 0;
    matrix[4][2] = 0;
    matrix[4][3] = 0;
    matrix[4][4] = 0;
    matrix[4][5] = 1;
    
    return matrix;
}

int ** test_graph2()
{
    // Тестовый граф, заданный матрицей инциденций
    int ** matrix = new int *[5];
    matrix[0] = new int[5];
    matrix[0][0] = 1;
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    matrix[0][3] = 0;
    matrix[0][4] = 1;
    matrix[0][5] = 0;
    
    matrix[1] = new int[5];
    matrix[1][0] = 1;
    matrix[1][1] = 0;
    matrix[1][2] = 0;
    matrix[1][3] = 1;
    matrix[1][4] = 0;
    matrix[1][5] = 0;
    
    matrix[2] = new int[5];
    matrix[2][0] = 0;
    matrix[2][1] = 1;
    matrix[2][2] = 0;
    matrix[2][3] = 0;
    matrix[2][4] = 0;
    matrix[2][5] = 1;
    
    matrix[3] = new int[5];
    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 1;
    matrix[3][3] = 0;
    matrix[3][4] = 0;
    matrix[3][5] = 1;
    
    matrix[4] = new int[5];
    matrix[4][0] = 0;
    matrix[4][1] = 0;
    matrix[4][2] = 0;
    matrix[4][3] = 1;
    matrix[4][4] = 1;
    matrix[4][5] = 0;
    
    return matrix;
}

// Функция создания матрицы заданных размеров, с вводом значений с клавиатуры.
int ** create_matrix(int n)
{
    cout << "Input matrix." << endl;
    int ** mat = new int *[n];
    for (size_t i = 0; i < n; i++)
    {
        cout << "Input " << i + 1 << " lines: " << endl;
        mat[i] = new int[n];
        for (size_t j = 0; j < n + 1; j++)
        {
            int a;
            cin >> a;
            mat[i][j] = a;
        }
    }
    cout << endl;
    return mat;
}

// Печатает матрицу.
void print_matrix(int ** mat, int rows)
{
    cout << "Your matrix: " << endl;
    int cols = rows + 1;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

// Функция освобождения памяти, занятой матрицей.
void purge_matrix(int ** mat, int n)
{
    delete[] mat;
}

// Удаляет нули в векторе векторов.
void delete_zero_in_vec(vector<vector<int>>& v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        //vector<int> vn = v[i];
        int
        len = v[i].size();
        auto t = find(v[i].begin(), v[i].end(), 0);
        while (t != v[i].end())
        {
            v[i].erase(t);
            t = find(v[i].begin(), v[i].end(), 0);
        }
        v[i] = v[i];
    }
}

// Добавляет в вектор векторов вершины соответствующие рёбрам
void push_edge(int ** mat, vector<vector<int>>& edge)
{
    for (size_t j = 0; j < edge.size(); j++)
    {
        vector<int> rib;
        for (size_t i = 0; i < edge.size() - 1; i++)
            if (mat[i][j] == 1)
                rib.push_back(i);
        
        edge[j] = rib;
    }
}

void cliques(vector<vector<int>> edge)
{
    vector<vector<int>> edgeR = edge;
    vector<int> res; // здесь будут храниться клики
    
    vector<int> tops; // вершины
    for (size_t t = 0; t < edge.size() - 1; t++)
        tops.push_back(t);
    
    for (auto x : tops)
        for (size_t j = 0; j < edgeR.size(); j++)
        {
            auto t = find(edgeR[j].begin(), edgeR[j].end(), x);
            if (t != edgeR[j].end()) // т.е. нашел такой элемент в edgeR[i]
            {
                //v = edgeR[j];
                res.push_back(edgeR[j][0]);
                res.push_back(edgeR[j][1]); // Добавили в res найденные вершины
                int last = res.back();
                for (size_t k = 0; k < edgeR.size(); k++)
                    if (edgeR[k][0] == last)
                    {
                        res.push_back(edgeR[k][1]);
                        edgeR[k].insert(edgeR[k].begin(), -1); // помечаем, как пройденный
                        break;
                    }
                int first = res.front();
                last = res.back();
                for (size_t k = 0; k < edgeR.size(); k++)
                    if (edge[k][0] == first && edge[k][1] == last)
                    {
                        if (res.size() > 2)
                        {
                            for (auto xx : res)
                                cout << xx + 1 << " ";
                            cout << endl;
                            res.clear();
                            break;
                        }
                    }
                res.clear();
            }
        }
}

int main()
{
    setlocale(LC_ALL, "ru");
    cout << "Input number of vertices: ";
    int n;
    cin >> n;
    int ** matrix = test_graph1();
    //int ** matrix = create_matrix(n);
    print_matrix(matrix, n);
    
    vector<vector<int>> edge(n + 1); // рёбра
    
    // Добавляет в вектор векторов вершины соответствующие рёбрам
    push_edge(matrix, edge);
    
    // Печать вершин
    /*
    for (auto x : edge)
    {
        for (auto xx : x)
            cout << xx + 1 << " ";
        cout << endl;
    }
    cout << endl;
    */
 
    
    cout << "Cliques: " << endl;
    cliques(edge);
    
    purge_matrix(matrix, n); // освобождение памяти, занятой матрицей
    system("pause");
}
