#include <bits/stdc++.h>
using namespace std;

typedef struct Node
{
    int val;
    Node *next;
    Node *prev;
} Node;

class Linklist
{
public:
    Node *head;
    Linklist()
    {
        head = new Node;
        head->next = nullptr;
        head->prev = nullptr;
        head->val = 0;
    }
    // void init()
    // {
    //     head = new Node;
    //     head->next = nullptr;
    //     head->prev = nullptr;
    //     head->val = 0;
    // }
    // void head_insert(int val)
    // {
    //     Node *p=new Node;
    //     p->next=head->next;
    //     p->prev=head;
    //     p->val=val;
    //     head->next=p;
    //     p->next->prev=p;
    // }
    void head_insert(int val)
    {
        Node *p = new Node;
        p->next = head->next;
        p->prev = head;

        if (head->next != nullptr)
        { // 空指针不运行
            p->next->prev = p;
        }

        head->next = p;
        p->val = val;
    }

    void tail_insert(int val)
    {
        Node *p = new Node;
        p->next = nullptr;
        p->val = val;
        Node *cur = head;
        while (cur->next != nullptr)
        {
            cur = cur->next;
        }
        cur->next = p;
        p->prev = cur;
    }

    void remove(int val)
    {
        Node *cur = head->next;
        while (cur != nullptr && cur->val != val)
        {
            cur = cur->next;
        }
        if (cur != nullptr)
        {
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            delete cur;
        }
    }
    void print()
    {
        Node *cur = head->next;
        while (cur != nullptr)
        {
            cout << cur->val << " ";
            cur = cur->next;
        }
    }
    ~Linklist()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main()
{
    Linklist *test = new Linklist();
    for (int i = 0; i < 10; i++)
        test->tail_insert(i);
    test->print();
    cout << endl;
    test->remove(5);
    test->print();
    delete test;
    return 0;
}
