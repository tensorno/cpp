#include <bits/stdc++.h>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    

};

// 中序遍历
void recoverTree(TreeNode *root)
{
    // 二叉搜索树 中序遍历是一个递增
    // 左 中 右
    // 二叉树的中序遍历为例，无论是递归或是迭代，为了在遍历完左节点（也可以是左子树）时，仍能回到父节点
    // 就是在左子树上的最后一个遍历到的节点添加一个路线 就是左子树上的最右边节点添加一个路径指向了root节点
    // 如果说已经有了这个关系说明了已经遍历了左子树 那么我们就访问右子树
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