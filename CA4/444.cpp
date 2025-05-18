//https://chatgpt.com/share/676d95f9-fd40-800e-b379-89c2151c3e34
//Sayyed Mohammad Hossein Mazhari 
//CA4 Q4

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct Edge {
    int u, v, w, index;
};

struct DSU {
    vector<int> parent, size;
    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (size[x] < size[y]) swap(x, y);
            parent[y] = x;
            size[x] += size[y];
            return true;
        }
        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].index = i + 1;
    }


    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    
    long long min_mst_cost = 0;
    DSU min_dsu(n);
    for (const auto& edge : edges) {
        if (min_dsu.unite(edge.u, edge.v)) {
            min_mst_cost += edge.w;
        }
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        unordered_set<int> required_edges;
        for (int j = 0; j < k; ++j) {
            int edge_index;
            cin >> edge_index;
            required_edges.insert(edge_index);
        }

       
        long long current_mst_cost = 0;
        DSU current_dsu(n);
        int required_count = 0;
        bool possible = true;

        
        for (const auto& edge : edges) {
            if (required_edges.find(edge.index) != required_edges.end()) {
                if (current_dsu.unite(edge.u, edge.v)) {
                    current_mst_cost += edge.w;
                    required_count++;
                }
            }
        }

        
        for (const auto& edge : edges) {
            if (required_edges.find(edge.index) == required_edges.end()) {
                if (current_dsu.unite(edge.u, edge.v)) {
                    current_mst_cost += edge.w;
                }
            }
        }

        
        if (required_count == k && current_mst_cost == min_mst_cost) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}