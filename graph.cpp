#include <bits/stdc++.h>
using namespace std;

class Graph
{
    vector<vector<pair<int,int>>> graph;
    Graph(int n, vector<vector<int>> edges) // egdes: [[0,1,2],[0,2,3]]  -> graph: [[[1,2],[2,3]]]
    {
        graph.resize(n);
        for(auto edge: edges)
        {
            graph[edge[0]].push_back(make_pair(edge[1], edge[2]));
        }
    }

    void addEdge(vector<int> edge)
    {
        graph[edge[0]].push_back(make_pair(edge[1], edge[2]));
    }

    int shortestPath(int src, int dest)  
    {
        int n = graph.size();
        vector<int> dist(graph.size(), INT_MAX/2);  // dist[i] stores the shortest path to node i
        dist[src] = 0;
        vector<bool> visited(graph.size(), false);
        for(int i =0; i<n; i++)
        {
            int index = -1;
            for(int j = 0; j<n; j++)
            {
                if(!visited[j] && (index == -1 || dist[j] < dist[index]))
                    index = j;
            }
            visited[index] = true;
            for(int j = 0; j<graph[index].size(); j++)
            {
                dist[j] = min(dist[j], dist[index] + graph[index][j].second);
            }
        }
        if(dist[dest] == INT_MAX/2) return -1;
        return dist[dest];
    }
};


class Graph_matrix
{
    vector<vector<int>> graph;
    Graph_matrix(int n, vector<vector<int>>& edges) {
        graph = vector<vector<int>>(n,vector<int>(n,INT_MAX/2));
        for(auto edge:edges)
        {
            graph[edge[0]][edge[1]] = edge[2];
        }
    }
    
    void addEdge(vector<int> edge) {
        graph[edge[0]][edge[1]] = edge[2];
    }

    int shortestPath(int src, int dest)
    {
        int n = graph.size();
        vector<int> dist(graph.size(), INT_MAX/2);
        dist[src] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, src});
        while(!pq.empty())
        {
            pair<int, int> temp = pq.top();
            pq.pop();
            int start = temp.second;
            int len = temp.first;
            if(len>dist[start]) continue;  // if the length is greater than the shortest path till now, then ignore
            for(int j = 0;j<n;j++)
            {
                if(graph[start][j]==0) continue;
                if(dist[j] > dist[start] + graph[start][j])
                {
                    dist[j] = dist[start] + graph[start][j];
                    pq.push({dist[j], j});
                }
            }
        }
        if(dist[dest] == INT_MAX/2) return -1;
        return dist[dest];
    }
};

