//https://aistudio.google.com/app/prompts?state=%7B%22ids%22%3A%5B%221xvAYeJY7V4tiai-bUaCl4xQptk5xy7cd%22%5D%2C%22action%22%3A%22open%22%2C%22userId%22%3A%22109127705709246180048%22%2C%22resourceKeys%22%3A%7B%7D%7D&usp=drive_link
// Sayyed Mohammad Hossein Mazhari
// CA4 Q1
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> visited_nodes;
vector<vector<int>> ground_paths;
vector<vector<int>> sky_paths;

void explore(int node) {
    visited_nodes[node] = 1;
    for (int neighbor : sky_paths[node]) {
        if (!visited_nodes[neighbor]) {
            explore(neighbor);
        }
    }
}

void initialize_graphs(int node_count) {
    for (int i = 0; i < node_count + 1; ++i) {
        ground_paths.push_back({});
        sky_paths.push_back({});
        visited_nodes.push_back(0);
    }
}

void read_ground_paths(int edge_count) {
    for (int i = 0; i < edge_count; ++i) {
        int u, v;
        cin >> u >> v;
        ground_paths[u].push_back(v);
        ground_paths[v].push_back(u);
    }
}

bool check_empty_ground_paths(int node_count) {
    for (int i = 1; i < node_count + 1; ++i) {
        if (ground_paths[i].empty()) {
            cout << 0 << endl;
            return true;
        }
    }
    return false;
}

void build_sky_paths(int node_count) {
    for (auto& path : ground_paths) {
        sort(path.begin(), path.end());
    }

    for (int i = 1; i < node_count + 1; ++i) {
        int pointer = 0;
        for (int j = 1; j < node_count + 1; ++j) {
            if (i == j) continue;

            if (pointer == ground_paths[i].size()) {
                sky_paths[i].push_back(j);
                continue;
            }

            if (ground_paths[i][pointer] == j) {
                pointer++;
            } else {
                sky_paths[i].push_back(j);
            }
        }
        ground_paths[i].clear(); 
    }
}

int count_components(int node_count) {
    int components_count = 0;
    for (int i = 1; i < node_count + 1; ++i) {
        if (!visited_nodes[i]) {
            explore(i);
            components_count++;
        }
    }
    return components_count;
}


int main() {
    int node_count, edge_count;
    cin >> node_count >> edge_count;

    initialize_graphs(node_count);
    read_ground_paths(edge_count);

    if (check_empty_ground_paths(node_count)) {
        return 0;
    }

    build_sky_paths(node_count);
    int components_count = count_components(node_count);

    cout << components_count - 1 << endl;
    return 0;
}