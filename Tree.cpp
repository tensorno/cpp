#include <bits/stdc++.h>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    

};

// �������
void recoverTree(TreeNode *root)
{
    // ���������� ���������һ������
    // �� �� ��
    // ���������������Ϊ���������ǵݹ���ǵ�����Ϊ���ڱ�������ڵ㣨Ҳ��������������ʱ�����ܻص����ڵ�
    // �������������ϵ����һ���������Ľڵ����һ��·�� �����������ϵ����ұ߽ڵ����һ��·��ָ����root�ڵ�
    // ���˵�Ѿ����������ϵ˵�����Ѿ������������� ��ô���Ǿͷ���������
    TreeNode* predecessor = nullptr;
    while (root != nullptr)
    {
        if (root->left != nullptr)
        {
            predecessor = root->left;
            while (predecessor->right != nullptr && predecessor->right != root)
            {
                predecessor = predecessor->right;
            }
            if (predecessor->right == nullptr)
            {
                predecessor->right = root;
                root = root->left;
            }
            else
            {
                predecessor->right = nullptr;
                root = root->right;
            }
        }
        else
        {
            root = root->right;
        }
    }
}