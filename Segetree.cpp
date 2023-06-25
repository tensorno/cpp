class Segetree
{
    //https://leetcode.cn/problems/range-module/solution/by-lfool-eo50/
    class Node
    {
        public:
            Node* left;
            Node* right;
            int val;
            int add;
    };
    public:
        //对l-r更新需要+val
        //node start-end
        void update(Node* node,int start,int end,int l,int r,int val)
        {
            if(l<=start&&end<=r)
            {
                node->val += val * (end - start + 1);
                node->add += val;
                return;
            }
            int mid = start + end >>1;
            pushdown(node,mid-start + 1,end - mid);
            if(l<=mid) update(node->left,start,mid , l, r ,val); // [start, mid] 和 [l, r] 可能有交集，遍历左孩子区间
            if(mid + 1<=r) update(node->right,mid + 1, end, l, r ,val); // [mid + 1, end] 和 [l, r] 可能有交集，遍历右孩子区间
            pushup(node);
        }

        void pushup(Node* node)
        {
            node->val = node->left->val + node->right->val;
        }

        int query(Node* node,int start, int end,int l ,int r)
        {
            if(l<=start&&end<=r) return node->val;
            int mid = start + end >> 1;
            
            pushdown(node,mid-start + 1,end - mid);
            int ans = 0;
            if(l<=mid) ans += query(node->left,start,mid , l, r);
            if(mid + 1<=r) ans += query(node->right,mid + 1, end, l, r );
            return ans;
        }

        void pushdown(Node* node,int leftnum, int rightnum)
        {
            if(node->left==nullptr) node->left = new Node();
            if(node->right==nullptr) node->right = new Node();
            if (node->add == 0) return ;
            node->left->val += node->add * leftnum; 
            node->right->val += node->add * rightnum;
            node->left->add += node->add;
            node->right->add += node->add;
            node->add = 0;
        }


};