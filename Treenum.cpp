//��״�������ʱ��ֻ���°�����һԪ�ص����䣻��ǰn���ʱ��ͨ�������������ϣ��õ���1��n�����䣬Ȼ��������õ���������͡�

class Treenum
{
    //tree[i]����洢(i-lowerbit(i),i]��ֵ
    int tree[100100];
    int n = 10000;
    //lowbit(x) �Ƿ��� x �����һλ1�������0�����ɵĶ�������
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
    //��ô��θ����أ���һᷢ�ָ��¾���һ�����������Ĺ���
    //ÿһ�����Ѵ��ұ���һϵ��������1��Ϊ0���ٰ���һϵ��1��ǰһλ0��Ϊ1���⿴��������һ����λ�Ĺ��̶԰ɣ�
    // ʵ���ϣ�ÿһ�μӵ�����lowerbit(i)
    void update(int x, int u)
    {
        for (int i = x; i <= n; i += lowbit(i))
            tree[i] += u;
    }
};
