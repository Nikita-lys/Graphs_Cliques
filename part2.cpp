//  part2.cpp
//  Graphs

/*
 2 ЧАСТЬ.
 
 Задание:
 Выделить внутренние полные подмножества графа путём объединения его смежных вершин.
 Информация о графе задана в виде матрицы инциденций или подмножеств смежности.
 Число вершин графа равно или не превосходит n.
 
 Решение 2 части задания для неориентированного графа:
 Граф задан в виде матрицы смежности.
 Для выполнения задания мы воспользуемся алгоритмом Брона — Кербоша.
 
 Алгоритм Брона — Кербоша — метод ветвей и границ для поиска всех клик
 (а также максимальных по включению независимых множеств вершин) неориентированного графа.
 
 В теории графов КЛИКОЙ неориентированного графа называется подмножество его вершин,
 любые две из которых соединены ребром. Наша же задача заключается в том, чтобы найти все такие клики в графе.
 */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int ** test_graph()
{
    // Тестовый граф
    int ** matrix = new int *[5];
    matrix[0] = new int[5];
    matrix[0][0] = 0;
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    matrix[0][3] = 1;
    matrix[0][4] = 0;
    
    matrix[1] = new int[5];
    matrix[1][0] = 1;
    matrix[1][1] = 0;
    matrix[1][2] = 1;
    matrix[1][3] = 1;
    matrix[1][4] = 0;
    
    matrix[2] = new int[5];
    matrix[2][0] = 1;
    matrix[2][1] = 1;
    matrix[2][2] = 0;
    matrix[2][3] = 0;
    matrix[2][4] = 0;
    
    matrix[3] = new int[5];
    matrix[3][0] = 1;
    matrix[3][1] = 1;
    matrix[3][2] = 0;
    matrix[3][3] = 0;
    matrix[3][4] = 1;
    
    matrix[4] = new int[5];
    matrix[4][0] = 0;
    matrix[4][1] = 0;
    matrix[4][2] = 0;
    matrix[4][3] = 1;
    matrix[4][4] = 0;
    
    return matrix;
}

// Функция создания матрицы заданных размеров, с вводом значений с клавиатуры.
int ** create_matrix2(int n)
{
    cout << "Input matrix." << endl;
    int ** mat = new int *[n];
    for (size_t i = 0; i < n; i++)
    {
        cout << "Input " << i + 1 << " lines: " << endl;
        mat[i] = new int[n];
        for (size_t j = 0; j < n; j++)
        {
            int a;
            cin >> a;
            mat[i][j] = a;
        }
    }
    return mat;
}

// Функция печати матрици.
void print_matrix2(int ** mat, int n)
{
    cout << "Your matrix: " << endl;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

// Функция освобождения памяти, занятой матрицей.
void purge_matrix2(int ** mat, int n)
{
    for (size_t i = 0; i < n; i++)
        delete[] mat[i];
    delete[] mat;
}

// Проверка, есть ли такой вектор в векторе векторов
bool compare(vector<vector<int>> vmain, vector<int> v)
{
    if (vmain.size() < 1)
        return false;
    for (size_t i = 0; i < vmain.size(); i++)
    {
        int concurrences = 0; // совпадения
        vector<int> vi = vmain[i];
        if (v.size() == vi.size())
        {
            for (size_t j = 0; j < v.size(); j++)
            {
                if (vi[j] == v[j])
                    ++concurrences;
            }
            if (concurrences == v.size())
                return true;
        }
    }
    return false;
}

bool removable(vector<int> neighbor, vector<int> cover)
{
    bool check = true;
    for (size_t i = 0; i < neighbor.size(); i++)
        if (cover[neighbor[i]] == 0)
        {
            check = false;
            break;
        }
    return check;
}

int max_removable(vector<vector<int> > neighbors, vector<int> cover)
{
    int r = -1, max = -1;
    for (size_t i = 0; i < cover.size(); i++)
    {
        if (cover[i] == 1 && removable(neighbors[i], cover) == true)
        {
            vector<int> temp_cover = cover;
            temp_cover[i] = 0;
            int sum = 0;
            for (size_t j = 0; j < temp_cover.size(); j++)
                if (temp_cover[j] == 1 && removable(neighbors[j], temp_cover) == true)
                    sum++;
            if (sum > max)
            {
                max = sum;
                r = i;
            }
        }
    }
    return r;
}

vector<int> procedure_1(vector<vector<int>> neighbors, vector<int> cover)
{
    vector<int> temp_cover = cover;
    int r = 0;
    while (r != -1)
    {
        r = max_removable(neighbors, temp_cover);
        if (r != -1)
            temp_cover[r] = 0;
    }
    return temp_cover;
}

vector<int> procedure_2(vector<vector<int> > neighbors, vector<int> cover, int k)
{
    int count = 0;
    vector<int> temp_cover = cover;
    int
    i = 0;
    for (size_t i = 0; i < temp_cover.size(); i++)
    {
        if (temp_cover[i] == 1)
        {
            int sum = 0, index;
            for (size_t j = 0; j < neighbors[i].size(); j++)
                if (temp_cover[neighbors[i][j]] == 0)
                {
                    index = j;
                    sum++;
                }
            if (sum == 1 && cover[neighbors[i][index]] == 0)
            {
                temp_cover[neighbors[i][index]] = 1;
                temp_cover[i] = 0;
                temp_cover = procedure_1(neighbors, temp_cover);
                count++;
            }
            if (count > k)
                break;
        }
    }
    return temp_cover;
}

int cover_size(vector<int> cover)
{
    int count = 0;
    for (size_t i = 0; i < cover.size(); i++)
        if (cover[i] == 1)
            count++;
    return count;
}


int main()
{
    setlocale(LC_ALL, "ru");
    
    int s, min, edge;
    cout << "Input number of vertices: ";
    int n;
    cin >> n;
    
    //int ** matrix = create_matrix2(n);
    int ** matrix = test_graph();
    print_matrix2(matrix, n);
    
    cout << "Cliques: " << endl;
    vector<vector<int>> vec, graph;
    for (size_t i = 0; i < n; i++)
    {
        vector<int> row; // ряд
        for (size_t j = 0; j < n; j++)
        {
            // infile >> edge; // если работаем с файлом
            edge = matrix[i][j]; // элемент в матрице
            if (edge == 0)
                row.push_back(1);
            else
                row.push_back(0);
        }
        graph.push_back(row);
    }
    
    vector<vector<int> > neighbors; // соседи
    
    // цикл создаёт матрицу соседей
    for (size_t i = 0; i < graph.size(); i++)
    {
        vector<int> neighbor;
        for (size_t j = 0; j < graph[i].size(); j++)
            if (graph[i][j] == 1)
                neighbor.push_back(j);
        neighbors.push_back(neighbor);
    }
    
    int k = 0;
    bool found = false;
    
    // процесс нахождения клика
    min = n + 1; // 6
    vector<vector<int> > covers;
    vector<int> allcover;
    for (size_t i = 0; i < graph.size(); i++)
        allcover.push_back(1);
    
    int counter = 0;
    for (size_t i = 0; i < allcover.size(); i++)
    {
        if (found)
            break;
        counter++; // счётчик
        vector<int> cover = allcover;
        cover[i] = 0;
        cover = procedure_1(neighbors, cover);
        s = cover_size(cover);
        if (s < min)
            min = s;
        if (s <= k)
        {
            vector<int> v;
            for (size_t j = 0; j < cover.size(); j++)
                if (cover[j] == 0)
                    v.push_back(j + 1);
            
            // проверка и вывод
            bool test = compare(vec, v);
            if (!test)
            {
                vec.push_back(v);
                for (auto x : v)
                    cout << x << " ";
                cout << endl;
            }
            v.clear();
            
            covers.push_back(cover);
            found = true;
            break;
        }
        for (size_t j = 0; j < n - k; j++)
            cover = procedure_2(neighbors, cover, j);
        s = cover_size(cover);
        if (s < min)
            min = s;
        
        vector<int> v;
        for (size_t j = 0; j < cover.size(); j++)
            if (cover[j] == 0)
                v.push_back(j + 1);
        
        // проверка и вывод
        if (!compare(vec, v))
        {
            vec.push_back(v);
            for (auto x : v)
                cout << x << " ";
            cout << endl;
        }
        v.clear();
        
        covers.push_back(cover);
        if (s <= k)
        {
            found = true;
            break;
        }
    }
    
    // парные пересечения
    for (size_t p = 0; p < covers.size(); p++)
    {
        if (found)
            break;
        for (size_t q = p + 1; q < covers.size(); q++)
        {
            if (found)
                break;
            counter++;
            
            vector<int> cover = allcover;
            for (size_t r = 0; r < cover.size(); r++)
                if (covers[p][r] == 0 && covers[q][r] == 0)
                    cover[r] = 0;
            cover = procedure_1(neighbors, cover);
            s = cover_size(cover);
            if (s < min)
                min = s;
            if (s <= k)
            {
                vector<int> v;
                for (size_t j = 0; j < cover.size(); j++)
                    if (cover[j] == 0)
                        v.push_back(j + 1);
                
                // проверка и вывод
                if (!compare(vec, v))
                {
                    vec.push_back(v);
                    for (auto x : v)
                        cout << x << " ";
                    cout << endl;
                }
                v.clear();
                
                found = true;
                break;
            }
            for (size_t j = 0; j < k; j++)
                cover = procedure_2(neighbors, cover, j);
            s = cover_size(cover);
            if (s < min)
                min = s;
            
            vector<int> v;
            for (size_t j = 0; j < cover.size(); j++)
                if (cover[j] == 0)
                    v.push_back(j + 1);
            
            // проверка и вывод
            if
                (!compare(vec, v))
            {
                vec.push_back(v);
                for (auto x : v)
                    cout << x << " ";
                cout << endl;
            }
            v.clear();
            
            if (s <= k)
            {
                found = true;
                break;
            }
        }
    }
    
    purge_matrix2(matrix, n);
    system("pause");
}
