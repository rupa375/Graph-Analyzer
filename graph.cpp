#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

class Graph {
    int V;
    vector<vector<pair<int,int>>> adj; // (node, weight)

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w, bool undirected=true) {
        adj[u].push_back({v,w});
        if(undirected)
            adj[v].push_back({u,w});
    }

    // BFS
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS Traversal: ";

        while(!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for(auto it : adj[node]) {
                if(!visited[it.first]) {
                    visited[it.first] = true;
                    q.push(it.first);
                }
            }
        }
        cout << endl;
    }

    // DFS
    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << node << " ";

        for(auto it : adj[node]) {
            if(!visited[it.first]) {
                DFSUtil(it.first, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS Traversal: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // Dijkstra
    void dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while(!pq.empty()) {
            int node = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            for(auto it : adj[node]) {
                int adjNode = it.first;
                int weight = it.second;

                if(d + weight < dist[adjNode]) {
                    dist[adjNode] = d + weight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }

        cout << "Dijkstra shortest paths from " << src << ":\n";
        for(int i = 0; i < V; i++) {
            cout << "Node " << i << " -> " << dist[i] << endl;
        }
    }

    // Prim's Algorithm
    void primMST() {
        vector<int> key(V, INT_MAX);
        vector<bool> mst(V, false);

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        key[0] = 0;
        pq.push({0,0});

        int totalWeight = 0;

        while(!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if(mst[u]) continue;

            mst[u] = true;
            totalWeight += key[u];

            for(auto it : adj[u]) {
                int v = it.first;
                int weight = it.second;

                if(!mst[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.push({key[v], v});
                }
            }
        }

        cout << "Total weight of MST: " << totalWeight << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v weight):\n";
    for(int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int choice;
    do {
        cout << "\n--- Graph Menu ---\n";
        cout << "1. BFS\n2. DFS\n3. Dijkstra\n4. Prim MST\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int start;

        switch(choice) {
            case 1:
                cout << "Start node: ";
                cin >> start;
                g.BFS(start);
                break;

            case 2:
                cout << "Start node: ";
                cin >> start;
                g.DFS(start);
                break;

            case 3:
                cout << "Source node: ";
                cin >> start;
                g.dijkstra(start);
                break;

            case 4:
                g.primMST();
                break;
        }

    } while(choice != 5);

    return 0;
}