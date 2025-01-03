#include <bits/stdc++.h>
class ACAutomaton {
public:
    static const int CHARSET_SIZE = 26;  // 英文字母

    struct Node {
        Node* children[CHARSET_SIZE];
        bool isEnd = false;
        Node* fail = nullptr; // 失败指针
        char c;
        Node(char c)
        {
            this->c = c;
            for (int i = 0; i < CHARSET_SIZE; ++i) {
                children[i] = nullptr;
            }
        }
        Node()
        {
            for (int i = 0; i < CHARSET_SIZE; ++i) {
                children[i] = nullptr;
            }
        }
    };
        // Node() {
        //     for (int i = 0; i < CHARSET_SIZE; ++i) {
        //         children[i] = nullptr;
        //     }
        //     isEnd = false;
        // }

    Node* root;

    ACAutomaton() {
        root = new Node();
    };

    void insert(std::string s)
    {
        int n = s.size();
        Node* current = root;
        for (int i = 0; i < n; i++) {
            int index = s[i] - 'a';
            if (current->children[index] == nullptr) {
                current->children[index] = new Node(s[i]);
            }
            current = current->children[index];
        }
        current->isEnd = true;
    }

    bool find(std::string s)
    {
        int n = s.size();
        Node* current = root;
        for (int i = 0; i < n; i++) {
            int index = s[i] - 'a';
            if (current->children[index] == nullptr) {
                return false;
            }
            current = current->children[index];
        }
        return current->isEnd;
    }

    void build_fail()
    {
        std::queue<Node*> q;
        q.emplace(root);
        while(!q.empty())
        {
            Node* current = q.front();
            q.pop();
            for (int i = 0; i < CHARSET_SIZE; i++) {
                if (current == nullptr) continue;
                if (current->children[i] == root) 
                {
                    current->children[i]->fail = root;
                }
                else
                {
                    Node* next = current->fail;
                    Node* currentchild = current->children[i];
                    while(next != nullptr)
                    {
                        Node* nextchild = next->children[current->children[i]->c - 'a'];
                        if (nextchild != nullptr) 
                        {
                            current->children[i]->fail = nextchild;
                            break;
                        }
                        next = next->fail;
                    }
                    if (next == nullptr) 
                    {
                        current->children[i]->fail = root;
                    }
                    q.emplace(current->children[i]);
                }
            }
        }
    }

    void search(std::string s)
    {
        int n = s.size();
        Node* current = root;
        for (int i = 0; i < n; i++) {
            int index = s[i] - 'a';
            while (current != nullptr && current->children[index] == nullptr) 
            {
                current = current->fail;
            }
            if (current == nullptr) 
            {
                current = root;
                continue;
            }
            current = current->children[index];
            if (current == nullptr) current = root;
            Node* p = current;
            while (p != nullptr) 
            {
                if (p->isEnd) 
                {
                    std::cout << p->c << " ";
                }
                p = p->fail;
            }
        }
    }


private:
    Node *root = new Node(); // 无意义的根节点
};