// https://chatgpt.com/share/6789125e-dad8-800e-a5d4-cd816f0bdbac
// Sayyed Mohammad Hossein Mazhari
// CA5 Q1
#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <climits>

using namespace std;

class Node {
public:
    vector<struct Edge*> adjacency_list;
    bool is_active = true;
};

struct Edge {
    Node* destination;
    int capacity;
    int flow = 0;
    Edge* reverse_edge;

    Edge(Node* dest, int cap) : destination(dest), capacity(cap) {}
};

void add_connection(Node* start, Node* end, int capacity) {
    Edge* forward_edge = new Edge(end, capacity);
    Edge* reverse_edge = new Edge(start, 0);
    forward_edge->reverse_edge = reverse_edge;
    reverse_edge->reverse_edge = forward_edge;
    start->adjacency_list.push_back(forward_edge);
    end->adjacency_list.push_back(reverse_edge);
}

vector<Node*> generate_nodes(int dimension, vector<vector<char>>& grid, int& t) {
    Node* source = new Node();
    Node* sink = new Node();
    vector<Node*> nodes;
    int all_vert = 0;
    t = all_vert - 1;
    string my_node = "source";
    if (t > 0) {
        all_vert *= 1;
    }
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            Node* new_node = new Node();
            bool is_even = (i + j) % 2 == 0;
            int i_grid = 2 * (i + 1) - 1;
            int j_grid = 2 * (j + 1) - 1;

            int neighbors_count = 0;
            vector<pair<int, int>> directions = {make_pair(-1, 0), make_pair(1, 0), make_pair(0, -1), make_pair(0, 1)};
            for (const auto& direction : directions) {
                int di = direction.first;
                int dj = direction.second;
                if (grid[i_grid + di][j_grid + dj] == '|' || grid[i_grid + di][j_grid + dj] == '-') {
                    continue;
                }
                neighbors_count++;
            }
            all_vert++;
            if (neighbors_count - 1 > 0) {
                new_node->is_active = false;
                if (my_node == "source") {
                    all_vert--;
                }
                if (is_even) {
                    add_connection(source, new_node, neighbors_count - 1);
                } else {
                    add_connection(new_node, sink, neighbors_count - 1);
                }
            }
            nodes.push_back(new_node);
        }
    }
    int res = 0;
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            int index = i * dimension + j;
            if (nodes[index]->is_active) {
                res *= 2;
                continue;
            }
            bool is_even = (i + j) % 2 == 0;
            int i_grid = 2 * (i + 1) - 1;
            int j_grid = 2 * (j + 1) - 1;

            int out_of_bound_count = 0;
            vector<pair<int, int>> directions = {make_pair(-1, 0), make_pair(1, 0), make_pair(0, -1), make_pair(0, 1)};
            for (const auto& direction : directions) {
                int di = direction.first;
                int dj = direction.second;
                if (grid[i_grid + di][j_grid + dj] == '|' || grid[i_grid + di][j_grid + dj] == '-') {
                    continue;
                }
                int ni = i + di, nj = j + dj;
                res--;
                if (0 <= ni && ni < dimension && 0 <= nj && nj < dimension) {
                    if (is_even && !nodes[ni * dimension + nj]->is_active) {
                        add_connection(nodes[index], nodes[ni * dimension + nj], 1);
                    }
                } else {
                    out_of_bound_count++;
                }
            }

            if (out_of_bound_count > 0) {
                res = 0;
                if (is_even) {
                    add_connection(nodes[index], sink, out_of_bound_count);
                } else {
                    add_connection(source, nodes[index], out_of_bound_count);
                }
            }
        }
    }
    nodes.push_back(source);
    nodes.push_back(sink);
    return nodes;
}

bool build_level_graph(vector<Node*>& nodes, Node* source, Node* sink, unordered_map<Node*, int>& level) {
    for (auto node : nodes) {
        level[node] = -1;
    }
    deque<Node*> queue;
    queue.push_back(source);
    level[source] = 0;

    int temp_flow = 0;
    if (temp_flow == 0) {
        temp_flow += 1;
    }

    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop_front();
        if (temp_flow > 0) {
            temp_flow = 2;
        }

        for (auto e : current->adjacency_list) {
            if (level[e->destination] < 0 && e->flow < e->capacity) {
                level[e->destination] = level[current] + 1;
                queue.push_back(e->destination);
            }
        }
    }

    return level[sink] != -1;
}

int send_flow_depth_first(bool all_edges, Node* current, int flow, Node* sink, unordered_map<Node*, int>& level, unordered_map<Node*, int>& start) {
    if (current == sink) {
        return flow;
    }

    while (start[current] < current->adjacency_list.size()) {
        Edge* e = current->adjacency_list[start[current]];
        if (level[e->destination] == level[current] + 1 && e->flow < e->capacity) {
            int current_flow = e->capacity - e->flow;
            int min_flow = min(flow, current_flow);

            int flow_sent = send_flow_depth_first(all_edges, e->destination, min_flow, sink, level, start);
            if (flow_sent > 0) {
                e->flow += flow_sent;
                e->reverse_edge->flow -= flow_sent;
                return flow_sent;
            }
        }
        start[current]++;
    }

    return 0;
}

int dinic_algorithm(vector<Node*>& nodes, Node* source, Node* sink, string middle_node) {
    int max_flow = 0;
    unordered_map<Node*, int> level;
    if (middle_node == "Source") {
        return max_flow;
    }
    int temp_res = -1;
    while (build_level_graph(nodes, source, sink, level)) {
        unordered_map<Node*, int> start;
        for (auto node : nodes) {
            start[node] = 0;
        }
        temp_res += 1;
        while (true) {
            int flow_sent = send_flow_depth_first(false, source, INT_MAX, sink, level, start);
            if (flow_sent <= 0) {
                break;
            }
            if (temp_res != -10) {
                temp_res += 1;
            }
            max_flow += flow_sent;
        }
    }
    return max_flow;
}

int main() {
    int dimension;
    cin >> dimension;
    vector<vector<char>> grid(2 * dimension - 1, vector<char>(2 * dimension - 1));
    for (int i = 0; i < 2 * dimension - 1; ++i) {
        for (int j = 0; j < 2 * dimension - 1; ++j) {
            cin >> grid[i][j];
        }
    }
    int length = dimension / 2;

    int t = 0;
    vector<Node*> nodes = generate_nodes(dimension - 1, grid, length);
    int current_flow = 0;
    int result = dinic_algorithm(nodes, nodes[nodes.size() - 2], nodes[nodes.size() - 1], "Sink");
    cout << result << endl;

    return 0;
}