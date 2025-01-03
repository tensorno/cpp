#include <bits/stdc++.h>
using namespace std;
//ʹ���ڽӱ��dijstra�㷨������ʹ����priorityqueue
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
//ʹ���ڽӱ��disjtra�㷨����������
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
        /*���ֱ���ڶ���һ���߽����޸ģ��ܿ��ܵ�����ԭ�ȵ����·�����仯
        �Ӷ��ò�����Ҫ�Ľ��
        ���� Dijkstra �㷨��֤ÿ���õ��ĵ�����·�������յ����·
        ���԰��� Dijkstra  �㷨������/�ߵ�˳��ȥ�޸ģ��Ͳ������ȷ�������·����Ӱ�졣
        ����һ����Ҫ�޸ĵı�x-y,���Կ���3������
        ������㵽x������ͨ��Dijkstra���������
        ���x - y����������Ҫ��õ�
        �����y - �յ㣬���Դӵ�һ���е�dijkstra�õ�(���ʽ��ֻ�� y �ڴ�source �� destination�����·�ϲų��������y�������·�ϣ��޸�edge����������·����Ӱ��)
        �õ�һ��ʵ�����޸�0-2�����ߵ�ʱ�����Կ��Կ�������0-1����·������
        �޸�0-2�����߲�û�жԺ�������̱����κ�Ӱ�죬��Ϊ�����߶����·����������㡣
        ���յõ�һ�����̣�
        changedist[x] + edge + dist[destination] - dist[y] = target
        edge = target -  dist[destination](ǰ���ⲿ����һ����ֵ) + dist[y] - changedist[x]

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