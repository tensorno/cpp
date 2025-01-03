#include <bits/stdc++.h>
using namespace std;
//使用邻接表的dijstra算法，并且使用了priorityqueue
class Graph {
public:
    vector<vector<pair<int,int>>> graph;
    Graph(int n, vector<vector<int>>& edges) {
        graph.resize(n);
        for(auto i:edges)
        {
            graph[i[0]].push_back({i[1],i[2]});
        }
    }
    
    void addEdge(vector<int> i) {
        graph[i[0]].push_back({i[1],i[2]});
    }
    
    int shortestPath(int node1, int node2) {
        int n = graph.size();
        vector<int> dist(n,INT_MAX/2);
        dist[node1] = 0;
        auto cmp = [](pair<int, int> a, pair<int, int> b) {
        return a.first > b.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        pq.push({0,node1});
        while(!pq.empty())
        {
            pair<int,int> tmp = pq.top();
            pq.pop();
            int mindist = tmp.first;
            int start = tmp.second;
            if(mindist>dist[start]) continue;
            for(auto edge:graph[start])
            {
                int end = edge.first;
                int newdist = mindist + edge.second;
                if(newdist<dist[end])
                {
                    dist[end] = newdist;
                    pq.push({newdist,end});
                }
            }
        }
        if(dist[node2]==INT_MAX/2) return -1;
        return dist[node2];
    }
};
//使用邻接表的disjtra算法，并且朴素
using namespace std;
class Matrix
{
public:
    vector<vector<int>> graph;
    Matrix(int n, vector<vector<int>>& edges) {
        graph = vector<vector<int>>(n,vector<int>(n,INT_MAX/2));
        for(auto edge:edges)
        {
            graph[edge[0]][edge[1]] = edge[2];
        }
    }
    
    void addEdge(vector<int> edge) {
        graph[edge[0]][edge[1]] = edge[2];
    }
    
    int shortestPath(int node1, int node2) {
        int n = graph.size();
        vector<int> dist(n,INT_MAX/2);
        dist[node1] = 0;
        vector<bool> vis(n,false);
        for(int i = 0;i<n;i++)
        {
            int index = -1;
            for(int j = 0;j<n;j++)
            {
                if(!vis[j]&&(index==-1||dist[j]<dist[index])) index = j;
            }
            vis[index] = true;
            for(int j = 0;j<n;j++) dist[j] = min(dist[j],dist[index] + graph[index][j]);
        }
        if(dist[node2]==INT_MAX/2) return -1;
        return dist[node2];
    }
};

using namespace std;
class Solution {
public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        vector<vector<pair<int,int>>> graph(n,vector<pair<int,int>>());
        for(int i = 0;i<edges.size();i++)
        {
            int x = edges[i][0],y = edges[i][1];
            graph[x].emplace_back(y,i);
            graph[y].emplace_back(x,i);
        }
        auto dijstra = [&]()->vector<int>{
            vector<int> dist(n,INT_MAX/2);
            dist[source] = 0;
            vector<int> vis(n,false);
            for(int i = 0;i<n;i++)
            {
                int index = -1;
                for(int j = 0;j<n;j++)
                {
                    if(!vis[j]&&(index==-1||dist[j]<dist[index])) index = j;
                }
                vis[index] = true;
                for(auto[next,j]:graph[index])
                {
                    int d = edges[j][2];
                    if(d<0) d = 1;
                    dist[next] = min(dist[next],dist[index] + d);
                }
            }
            return dist;
        };
        vector<int> dist = dijstra();
        if(dist[destination]>target) return {};
        /*如果直接在对于一条边进行修改，很可能导致这原先的最短路发生变化
        从而得不到想要的结果
        由于 Dijkstra 算法保证每次拿到的点的最短路就是最终的最短路
        所以按照 Dijkstra  算法遍历点/边的顺序去修改，就不会对已确定的最短路产生影响。
        对于一条需要修改的边x-y,可以考虑3个部分
        首先起点到x，这是通过Dijkstra可以算出来
        其次x - y，是我们需要求得的
        最后是y - 终点，可以从第一次中的dijkstra得到(这个式子只有 y 在从source 到 destination的最短路上才成立，如果y不在最短路上，修改edge并不会对最短路产生影响)
        用第一个实例，修改0-2这条边的时候，明显可以看到不在0-1这条路径上面
        修改0-2这条边并没有对后续的最短边有任何影响，因为后续走对最短路不经过这个点。
        最终得到一个方程：
        changedist[x] + edge + dist[destination] - dist[y] = target
        edge = target -  dist[destination](前面这部分是一个定值) + dist[y] - changedist[x]

        */
        auto change = [&]()->vector<int>{
            int fix = target - dist[destination];
            vector<int> changedist(n,INT_MAX/2);
            changedist[source] = 0;
            vector<int> vis(n,false);
            for(int i = 0;i<n;i++)
            {
                int index = -1;
                for(int j = 0;j<n;j++)
                {
                    if(!vis[j]&&(index==-1||changedist[j]<changedist[index])) index = j;
                }
                vis[index] = true;
                for(auto[next,j]:graph[index])
                {
                    int d = edges[j][2];
                    if(d<0) d = 1;
                    if(edges[j][2]<0)
                    {
                        int tmp = fix + dist[next] - changedist[index];
                        if(tmp>d) 
                        {
                            d = tmp;
                            edges[j][2] = d;
                        }
                    }
                    changedist[next] = min(changedist[next],changedist[index] + d);
                }
            }
            return changedist;
        };
        vector<int> changedist = change();
        if(changedist[destination]<target) return {};
        for(auto &i:edges)
        {
            if(i[2]==-1) i[2] = 1;
        }
        return edges;
    }
};