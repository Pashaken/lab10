#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Структура для хранения ребра графа
struct Edge {
    int u, v, cost;

    // Оператор для сортировки по стоимости
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

//Функция сравнения для финального вывода
bool compareEdgesForOutput(const Edge& a, const Edge& b) {
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

//DSU
struct DSU {
    vector<int> parent;
    
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
    }

    //Сортируем ребра по стоимости
    sort(edges.begin(), edges.end());

    DSU dsu(n);
    vector<Edge> result;
    long long total_cost = 0;

    //Алгоритм Крускала
    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            result.push_back(edge);
            total_cost += edge.cost;
            if (result.size() == (size_t)(n - 1)) {
                break;
            }
        }
    }

    //Сортировка ответа по текущему первому числу, затем по второму
    sort(result.begin(), result.end(), compareEdgesForOutput);

    //Вывод результатов
    cout << result.size() << " " << total_cost << "\n";
    for (const auto& edge : result) {
        cout << edge.u << " " << edge.v << " " << edge.cost << "\n";
    }

    return 0;
}
