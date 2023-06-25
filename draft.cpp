#include <bits/stdc++.h>
using namespace std;
int count(int num)
{
    int cnt = 0;
    while (num)
    {
        num = num & (num - 1);
        cnt++;
    }
    return cnt;
}

int main()
{
    cout<<count(7)<<endl;
    return 0;
}