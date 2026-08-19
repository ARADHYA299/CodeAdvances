#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;


void bfs(vector<vector<int>>& adj,int V ,int src){
	vector<int> dist(V , INT_MAX);
	queue<int> q;
	
	dist[src] = 0;
	
	q.push(src);
	
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		
		for(int neigh : adj[cur]){
			if(dist[neigh] == INT_MAX){
				dist[neigh] = dist[cur] + 1;
				q.push(neigh);
			}
		}
	}
	cout << "Shortest distance from " << src << ":\n";
	
	for(int i=0;i<V;i++){
		cout << "Node " << i << "-->" ;
		
		if(dist[i] == INT_MAX){
			cout << "Unreachable ";
		}
		else {
			cout << dist[i];
		}
		
		cout << endl;
	}
}

int main(){
	
 int V, E;

    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> adj(V);

    cout << "Enter edges:\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;

        // Undirected graph
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int src;

    cout << "Enter source node: ";
    cin >> src;

    bfs(adj, V, src);

    return 0;
	
	
}