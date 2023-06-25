//树状数组更新时候只更新包含这一元素的区间；求前n项和时，通过将区间进行组合，得到从1到n的区间，然后对所有用到的区间求和。

class Treenum
{
    //tree[i]里面存储(i-lowerbit(i),i]的值
    int tree[100100];
    int n = 10000;
    //lowbit(x) 是返回 x 的最后一位1及其后面0或空组成的二进制数
    int lowbit(int x)
    {
        return x & -x;
    }
    int query(int x)
    {
        int ans = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ans += tree[i];
        return ans;
    }
    //那么如何更新呢，大家会发现更新就是一个“爬树”的过程
    //每一步都把从右边起一系列连续的1变为0，再把这一系列1的前一位0变为1。这看起来像是一个进位的过程对吧？
    // 实际上，每一次加的正是lowerbit(i)
    void update(int x, int u)
    {
        for (int i = x; i <= n; i += lowbit(i))
            tree[i] += u;
    }
};
