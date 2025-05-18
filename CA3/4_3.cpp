// Sayyed Mohammad Hossein Mazhari 
// CA3 Q4
//https://chatgpt.com/share/67462bfd-863c-800e-b273-4328da5d8dc1
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

bool is_exploitable(int n, const vector<int>& h, const vector<int>& e, const vector<vector<int>>& adj) {
    for (int s = 0; s < n; ++s) {
        bool found = false;
        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                if (min(e[u], e[v]) < h[s]) continue;

                vector<bool> visited(n, false);
                function<bool(int, int)> dfs = [&](int u, int p) {
                    visited[u] = true;
                    if (u == v) return true;
                    for (int neighbor : adj[u]) {
                        if (neighbor != p && !visited[neighbor]) {
                            if (dfs(neighbor, u)) return true;
                        }
                    }
                    return false;
                };

                if (dfs(u, -1) && visited[s]) {
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> h(n);
    int max_h = 0;
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
        max_h = max(max_h, h[i]);
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    long long min_wood = -1;
    int low = max_h, high = 1001;

    long long power_adjustment = 1LL << (n - 2);

    while (low < high) {
        int mid = low + (high - low) / 2;
        long long current_wood = 0;
        vector<int> e(n);
        for (int i = 0; i < n; ++i) {
            e[i] = max(h[i], mid);
            current_wood += e[i];
        }

        if (is_exploitable(n, h, e, adj)) {
            min_wood = (min_wood == -1) ? current_wood : min(min_wood, current_wood);
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    cout << min_wood - power_adjustment << endl;

    return 0;
}