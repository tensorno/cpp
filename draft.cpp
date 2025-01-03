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

void swap(int *a, int *b)
{
    a, b = b, a;
}

int main()
{
    //
    int a = 1;
    int b = 2;
    cout << a << " " << b << endl;
    swap(a, b);
    cout << a << " " << b << endl;
    // cout<<count(7)<<endl;
    return 0;
}

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
public:
    ListNode *mergeNodes(ListNode *head)
    {
        ListNode* cur = head;
        ListNode* pre = nullptr;
        int sum = 0;
        while (cur != nullptr)
        {
            ListNode* temp = cur;
            sum+= temp->val;
            cur = cur->next;
            if (temp->val == 0)
            {
                if(pre == nullptr)
                {
                    pre = cur;
                    temp->next = cur;
                }
                else
                {
                    pre->next = temp;
                    pre->val = sum;
                    temp->next = cur;
                    pre = temp;
                }
                sum = 0;
            }
        }
        cur = new ListNode(0, nullptr);
        cur->next = head;
        while(cur->next != nullptr)
        {
            if(cur->next->val == 0)
            {
                cur->next = cur->next->next;
            }
            else
            {
                cur = cur->next;
            }
            cur = cur->next;
        }
        return head;
    }
};