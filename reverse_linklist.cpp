#include <bits/stdc++.h>
using namespace std;

//   Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *reverseBetween(ListNode *head, int left, int right)
{
    ListNode dummy(0, head);
    ListNode *p0 = &dummy;
    for (int i = 0; i < left - 1; i++)
    {
        p0 = p0->next;
    }
    ListNode *pre = nullptr;
    ListNode *cur = p0->next;
    for (int i = left; i < right + 1; i++)
    {
        ListNode *tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    p0->next->next = cur;
    p0->next = pre;
    return dummy.next;
}

ListNode *reverseList(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    ListNode *reversed = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return reversed;
    // ListNode* pre = nullptr;
    // ListNode* cur = head;
    // while(cur)
    // {
    //     ListNode* n = cur->next;
    //     cur->next = pre;
    //     pre = cur;
    //     cur = n;
    // }
    // return pre;
}

ListNode *reverseKGroup(ListNode *head, int k)
{
    ListNode *dummy = new ListNode(-1, head);
    ListNode *p0 = dummy; // Node before the current group

    while (true)
    {
        ListNode *curr = p0->next;
        for (int i = 0; i < k; i++)
        {
            if (!curr)
                return dummy->next;
            curr = curr->next;
        }

        ListNode *prev = nullptr;
        ListNode *current = p0->next;
        for (int i = 0; i < k; i++)
        {
            ListNode *next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        ListNode *tail = p0->next;
        tail->next = current;
        p0->next = prev;
        p0 = tail;
    }

    return dummy->next;
}
