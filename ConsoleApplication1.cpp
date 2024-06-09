#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;//mohsen habeb _ mohammad slman
    vector<int> disc, low, parent;
    vector<bool> isArticulationPoint;
    vector<pair<int, int>> bridges;
    int time;
    int componentCount;

    void dfs(int u, stack<pair<int, int>>& edgeStack) {//mnar alo_ noor salloum
        disc[u] = low[u] = time++;
        int children = 0;
        for (int v : adj[u]) {
            if (disc[v] == -1) {
                children++;
                parent[v] = u;
                edgeStack.push({ u, v });
                dfs(v, edgeStack);
                low[u] = min(low[u], low[v]);
                if ((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u])) {
                    isArticulationPoint[u] = true;
                }
                if (low[v] > disc[u]) {
                    bridges.push_back({ u, v });
                }
            }
            else if (v != parent[u]) {//essam badran _ mohammad madaniah
                low[u] = min(low[u], disc[v]);
                if (disc[v] < disc[u]) {
                    edgeStack.push({ u, v });
                }
            }
        }
    }

    void dfs2(int u, vector<bool>& visited) {//leen mansour _ nahla abd alhamed
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs2(v, visited);
            }
        }
    }

public:
    Graph(int V) : V(V), adj(V), disc(V, -1), low(V, -1), parent(V, -1), isArticulationPoint(V, false), time(0), componentCount(0) {}//ali ahmad _ abd allah rhejah

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool is2VertexStronglyBiconnected() {//mahmoud helloani _ maged arab
        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                stack<pair<int, int>> edgeStack;
                dfs(i, edgeStack);

                vector<pair<int, int>> edges;
                while (!edgeStack.empty()) {
                    edges.push_back(edgeStack.top());
                    edgeStack.pop();
                }

                for (auto& edge : edges) {
                    int u = edge.first;
                    int v = edge.second;
                    adj[u].push_back(v);
                    adj[v].push_back(u);
                }
            }
        }

        for (bool b : isArticulationPoint) {
            if (b) {
                return false;
            }
        }

        vector<bool> visited(V, false);
        dfs2(0, visited);

        for (bool v : visited) {
            if (!v) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    bool is2VertexStronglyBiconnected = g.is2VertexStronglyBiconnected();

    if (is2VertexStronglyBiconnected) {
        cout << "The directed graph is 2-vertex strongly biconnected." << endl;
    }
    else {
        cout << "The directed graph is not 2-vertex strongly biconnected." << endl;
    }

    return 0;
}


