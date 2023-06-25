#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<pair<int,int>>> graph;
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        graph = vector<vector<pair<int,int>>>(n,vector<pair<int,int>>());
        for(int i = 0;i<edges.size();i++)
        {
            int x = edges[i][0];
            int y = edges[i][1];
            graph[x].push_back({y,i});
            graph[y].push_back({x,i});
        }
        vector<int> dist = dijstra(source,edges);
        for(int i = 0;i<n;i++) cout<<dist[i]<<" ";
        return {{}};
    }

    vector<int> dijstra(int start,vector<vector<int>>& edges)
    {
        int n = graph.size();
        vector<bool> vis(n,false);
        vector<int> dist(n,INT_MAX/2);
        dist[start] = 0;
        for(int i = 0;i<n;i++)
        {
            int index = -1;
            for(int j = 0;j<n;j++)
            {
                if(!vis[j]&&(index==-1||dist[j]<dist[index])) index = j;
            }
            vis[index] = true;
            // for(int j = 0;j<n;j++) dist[j] = min(dist[j],dist[index] + graph[index][j]);
            for(int j = 0;j<n;j++)
            {
                int point = graph[index][j].first;
                int dd = edges[graph[index][j].second][2];
                if(dd == -1) dd = 1;
                dist[j] = min(dist[j],dist[index] + dd);
            }
        }
        return dist;
    }
};

int main()
{
    Solution* s = new Solution();
    return 0;
}