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

// 01背包的近似算法
// 贪心算法 二进似
// 假设时分数背包，每个物品可以取一部分
// opt <= sum(values[0-k]) + (V-sum(weights[0-k]))*values[k+1]/weights[k+1] <= values[k+1] <= sum(values[0-k+1])
// C_g = max(sum(values[0-k]), values[k+1]) >= 1/2sum(values[0-k+1]) >= 1/2opt
// 所以是一个2近似算法
int knapsack_greedy(vector<int> weights, vector<int> values, int V)
{
    int n = weights.size();
    vector<pair<double, int>> value_per_weight(n);
    for (int i = 0; i < n; i++)
    {
        value_per_weight[i] = {values[i] / weights[i], i};
    }
    sort(value_per_weight.begin(), value_per_weight.end(), greater<pair<double, int>>());
    int res = 0;
    for(int i = 0;i<n;i++){
        int index = value_per_weight[i].second;
        if(weights[index]<=V)
        {
            res += values[index];
            V -= weights[index];
        }
        else
        {
            // res += V*value_per_weight[i].first;
            res = max(res, values[index]);
            break;
        }
    }
    return res;
}


int knapsack_ptas(vector<int> weights, vector<int> values, int V)
{
    int n = weights.size();
    int max_value = *max_element(values.begin(), values.end());
    vector<vector<int>> A(n + 1, vector<int>(n * max_value, V+1)); // A[i][j]表示前i个物品，总价值为j的最小重量
    for(int i = 0;i<n * max_value;i++)
    {
        A[0][i] = 0;
    }
    for(int i = 0;i<n+1;i++)
    {
        A[i][0] = 0;
    }
    for(int i = 1;i<n+1;i++)
    {
        for(int j = 0;j<n*max_value;j++)
        {
            if(weights[i-1] > j)
            {
                A[i][j] = A[i-1][j];
            }
            else
            {
                A[i][j] = min(A[i][j], A[i-1][j - values[i-1]] + weights[i-1]);
            }
        }
    }
    int ans = 0;
    for(int i = 0;i<n*max_value;i++)
    {
        if(A[n][i] <= V)
        {
            ans = i;
        }
    }
    return ans;
}


// 01背包的近似算法
// ptas算法
// fptas 算法就是将values进行缩放
// K = epsilon * max_value / n
// values[i] /=  K
// 然后使用ptas算法
// K * profit'(a) <= profit(a)
// K * profit'(a) >= profit(a) - K
// 对于任意i, profit(i) - profit'(i) * K < K
// profit(O) - profit'(O) * K < n*K  (O是未进行缩放的最优解)
// profit(S') >= K*profit'(O) > profit(O) - n * K = OPT - n * K = OPT - epsilon * max_value >= (1-epsilon)OPT
int knapsack_fptas(vector<int> weights, vector<int> values, int V, double epsilon)
{
    int n = weights.size();
    int max_value = *max_element(values.begin(), values.end());
    double K = epsilon * max_value / n;
    for(int i = 0;i<n;i++)
    {
        values[i] = values[i] / K;
    }
    return knapsack_ptas(weights, values, V);
}




int main()
{
    vector<int> weights = {1, 2, 3};
    vector<int> values = {6, 10, 12};
    int V = 5;
    // cout << knapsack(weights, values, V) << endl;
    // cout << knapsack_memoization(weights, values, V) << endl;
    // cout << knapsack_greedy(weights, values, V) << endl;
    cout << knapsack_fptas(weights, values, V, 0.1) << endl;
    return 0;
}