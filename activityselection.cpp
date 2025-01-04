#include <bits/stdc++.h>
using namespace std;

// 实现活动选择问题
// 有n个活动，每个活动都有一个开始时间和结束时间，求最多能参加多少个活动
// 贪心算法
int activity_selection_greedy(vector<vector<int>> times)
{
    int n = times.size();
    sort(times.begin(), times.end(), [](vector<int> &a, vector<int> &b) {
        return a[1] < b[1];
    });
    int res = 1;
    int end_time = times[0][1];
    for (int i = 1; i < n; i++)
    {
        if (times[i][0] >= end_time)
        {
            res++;
            end_time = times[i][1];
        }
    }
    return res;
}

// 动态规划
int activity_selection(vector<vector<int>> times)
{
    int n = times.size();
    sort(times.begin(), times.end(), [](vector<int> &a, vector<int> &b) {
        return a[1] < b[1];
    });
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for(int length = 1;length<=n;length++)
    {
        for(int start = 1;start<=n-length+1;start++)
        {
            int end = start + length - 1;
            dp[start][end] = 1;
            for(int k = start+1;k<end;k++)
            {
                if(times[k-1][1] <= times[end-1][0] && times[k-1][0] >= times[start-1][1])
                {
                    dp[start][end] = max(dp[start][end], dp[start][k] + dp[k][end] + 1);
                }
            }
        }
    }
    return dp[1][n];
}
int main()
{
    vector<vector<int>> times = {{1, 3}, {2, 4}, {3, 6}, {5, 7}, {6, 8}, {7, 9}};
    cout << activity_selection(times) << endl;
    cout << activity_selection_greedy(times) << endl;
    return 0;
}