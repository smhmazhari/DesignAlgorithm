//https://chatgpt.com/share/676d9f44-7604-800e-a442-848b2f491c24
//Sayyed Mohammad Hossein Mazhari
//CA4 Q3
#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef long long ll;
struct Edge { int node1; int node2; int index; };
struct Adj { int node; int index; };

const int MAX_WEIGHT = 1e6 + 7;
const int MAX_NODES = 1e5 + 7;

int findParent(int node, vector<int>& parent) {
    if (node == parent[node]) {
        return node;
    }
    return parent[node] = findParent(parent[node], parent);
}

void depthFirstSearch(int node, int callerIndex, int time, vector<bool>& isVisited, vector<int>& discoveryTime, 
                      vector<int>& lowestTime, vector<vector<Adj>>& adjList, vector<string>& edgeAnswer) {
    isVisited[node] = true;
    discoveryTime[node] = time;
    lowestTime[node] = time;
    for (const auto& adj : adjList[node]) {
        int index = adj.index;
        int adjacentNode = adj.node;
        if (!isVisited[adjacentNode]) {
            depthFirstSearch(adjacentNode, index, time + 1, isVisited, discoveryTime, lowestTime, adjList, edgeAnswer);
            lowestTime[node] = min(lowestTime[node], lowestTime[adjacentNode]);
            if (lowestTime[adjacentNode] > discoveryTime[node]) {
                edgeAnswer[index] = "any";
            }
        } else if (index != callerIndex) {
            lowestTime[node] = min(lowestTime[node], discoveryTime[adjacentNode]);
        }
    }
}

int main() {
    ll numNodes, numEdges;
    cin >> numNodes >> numEdges;

    vector<vector<Edge>> weightEdges(MAX_WEIGHT);
    vector<vector<Adj>> adjList(numNodes + 1);
    vector<int> parent(numNodes + 1);
    vector<bool> isVisited(numNodes + 1);
    vector<int> discoveryTime(numNodes + 1);
    vector<int> lowestTime(numNodes + 1);
    vector<string> edgeAnswer(numEdges + 1, "none");

    int u, v, w, maxWeight = 0;
    for (int i = 1; i <= numEdges; i++) {
        cin >> u >> v >> w;
        Edge e = {u, v, i};
        weightEdges[w].push_back(e);
        maxWeight = max(maxWeight, w);
    }

    for (int i = 1; i <= numNodes; i++) {
        parent[i] = i;
    }

    for (int w = 1; w <= maxWeight; w++) {
        if (weightEdges[w].empty()) {
            continue;
        }

        for (const auto& e : weightEdges[w]) {
            int u = e.node1;
            int v = e.node2;
            int i = e.index;
            if (findParent(u, parent) != findParent(v, parent)) {
                adjList[findParent(u, parent)].push_back({findParent(v, parent), i});
                adjList[findParent(v, parent)].push_back({findParent(u, parent), i});
                isVisited[findParent(u, parent)] = false;
                isVisited[findParent(v, parent)] = false;
                edgeAnswer[i] = "at least one";
            }
        }

        for (const auto& e : weightEdges[w]) {
            int u = e.node1;
            int v = e.node2;
            if (!isVisited[findParent(u, parent)]) {
                depthFirstSearch(findParent(u, parent), -1, 0, isVisited, discoveryTime, lowestTime, adjList, edgeAnswer);
            }
            adjList[findParent(u, parent)].clear();
            adjList[findParent(v, parent)].clear();
            parent[findParent(u, parent)] = findParent(v, parent);
        }
    }

    for (int i = 1; i <= numEdges; i++) {
        cout << edgeAnswer[i] << endl;
    }

    return 0;
}
