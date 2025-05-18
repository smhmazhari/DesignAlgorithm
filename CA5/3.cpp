#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <limits.h>

using namespace std;

class Edge {
public:
    int to, capacity, flow;
    Edge* rev;

    Edge(int to, int capacity) : to(to), capacity(capacity), flow(0), rev(nullptr) {}
};

class Node {
public:
    string name;
    vector<Edge*> edges;
    bool is_full;

    Node(string name) : name(name), is_full(true) {}
};

Edge* add_edge(Node* u, Node* v, int capacity) {
    Edge* forward_edge = new Edge(v - u, capacity);
    Edge* backward_edge = new Edge(u - v, 0);
    forward_edge->rev = backward_edge;
    backward_edge->rev = forward_edge;
    u->edges.push_back(forward_edge);
    v->edges.push_back(backward_edge);
    return forward_edge;
}

bool bfs_build_level_graph(vector<Node*>& nodes, int source_idx, int sink_idx, vector<int>& level) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    q.push(source_idx);
    level[source_idx] = 0;

    while (!q.empty()) {
        int u_idx = q.front();
        q.pop();
        Node* u = nodes[u_idx];
        for (Edge* e : u->edges) {
            if (level[e->to] < 0 && e->flow < e->capacity) {
                level[e->to] = level[u_idx] + 1;
                q.push(e->to);
            }
        }
    }

    return level[sink_idx] != -1;
}

int send_flow_dfs(vector<Node*>& nodes, int u_idx, int flow, int sink_idx, vector<int>& level, vector<int>& start) {
    if (u_idx == sink_idx) return flow;

    Node* u = nodes[u_idx];
    for (; start[u_idx] < u->edges.size(); ++start[u_idx]) {
        Edge* e = u->edges[start[u_idx]];
        if (level[e->to] == level[u_idx] + 1 && e->flow < e->capacity) {
            int current_flow = e->capacity - e->flow;
            int min_flow = min(flow, current_flow);
            int flow_sent = send_flow_dfs(nodes, e->to, min_flow, sink_idx, level, start);

            if (flow_sent > 0) {
                e->flow += flow_sent;
                e->rev->flow -= flow_sent;
                return flow_sent;
            }
        }
    }
    return 0;
}

int dinic_max_flow(vector<Node*>& nodes, int source_idx, int sink_idx) {
    int max_flow = 0;
    vector<int> level(nodes.size());
    
    while (bfs_build_level_graph(nodes, source_idx, sink_idx, level)) {
        vector<int> start(nodes.size());
        while (int flow_sent = send_flow_dfs(nodes, source_idx, INT_MAX, sink_idx, level, start)) {
            max_flow += flow_sent;
        }
    }

    return max_flow;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> inp(n, vector<int>(m, 0));
    vector<Node*> nodes;
    Node* source = new Node("source");
    Node* sink = new Node("sink");
    int sum_of_sum_row = 0, sum_of_sum_col = 0;
    bool bad_input = false;

    for (int i = 0; i < n; ++i) {
        if (bad_input) {
            string dummy;
            getline(cin, dummy);
            continue;
        }
        int sum_row = 0;
        for (int j = 0; j < m; ++j) {
            string num;
            cin >> num;
            int val = stoi(num.substr(num.find('.') + 1)) % 1000;
            if (val == 0) continue;
            inp[i][j] = val;
            sum_row += val;
        }

        if (sum_row % 1000 != 0 && !bad_input) {
            cout << "NO" << endl;
            bad_input = true;
        }

        if (sum_row != 0) {
            nodes.push_back(new Node("r" + to_string(i)));
            add_edge(source, nodes.back(), sum_row / 1000);
            sum_of_sum_row += sum_row / 1000;
        }
    }

    if (bad_input) return;

    for (int j = 0; j < m; ++j) {
        int sum_col = 0;
        for (int i = 0; i < n; ++i) {
            sum_col += inp[i][j];
        }
        if (sum_col % 1000 != 0) {
            cout << "NO" << endl;
            return;
        }
        if (sum_col != 0) {
            nodes.push_back(new Node("c" + to_string(j)));
            add_edge(nodes.back(), sink, sum_col / 1000);
            sum_of_sum_col += sum_col / 1000;
        }
    }

    if (sum_of_sum_row != sum_of_sum_col) {
        cout << "NO" << endl;
        return;
    }

    vector<vector<Edge*>> result(n, vector<Edge*>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (inp[i][j] != 0) {
                result[i][j] = add_edge(nodes[i], nodes[j + n], inp[i][j]);
            } else {
                result[i][j] = new Edge(0, 0);
            }
        }
    }

    nodes.push_back(source);
    nodes.push_back(sink);
    int max_flow = dinic_max_flow(nodes, nodes.size() - 2, nodes.size() - 1);

    if (max_flow != sum_of_sum_row) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (result[i][j]->capacity == 0) {
                cout << 0 << " ";
            } else {
                if (result[i][j]->flow == 0) {
                    cout << 1 << " ";
                } else {
                    cout << 0 << " ";
                }
            }
        }
        cout << endl;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
