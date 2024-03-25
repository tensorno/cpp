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


void swap(int *a,int *b)
{
    a,b = b,a;
}


int main()
{
    // 
    int a = 1;
    int b = 2;
    cout<<a<<" "<<b<<endl;
    swap(a,b);
    cout<<a<<" "<<b<<endl;
    // cout<<count(7)<<endl;
    return 0;
}