#include <bits/stdc++.h>
using namespace std;


// 实现01背包

// 有N件物品和一个容量为V的背包。第i件物品的重量是w[i]，价值是v[i]。

int knapsack(vector<int> weights, vector<int> values, int V)
{
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(V + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= V; j++)
        {
            if (j < weights[i - 1])
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + values[i - 1]);
            }
        }
    }
    return dp[n][V];
}

// memoization
int knapsack_memoization(vector<int> weights, vector<int> values, int V)
{
    int n = weights.size();
    vector<vector<int>> memo(n + 1, vector<int>(V + 1, -1));
    function<int(int, int)> dp = [&](int i, int j) -> int {
        if (i == 0 || j == 0)
        {
            return 0;
        }
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }
        if (j < weights[i - 1])
        {
            memo[i][j] = dp(i - 1, j);
        }
        else
        {
            memo[i][j] = max(dp(i - 1, j), dp(i - 1, j - weights[i - 1]) + values[i - 1]);
        }
        return memo[i][j];
    };
    return dp(n, V);
}


int main()
{
    vector<int> weights = {1, 2, 3};
    vector<int> values = {6, 10, 12};
    int V = 5;
    cout << knapsack(weights, values, V) << endl;
    cout << knapsack_memoization(weights, values, V) << endl;
    return 0;
}