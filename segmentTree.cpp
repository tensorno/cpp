#include <bits/stdc++.h>

class SegmentTree
{
public:
    struct Node
    {
        int left;
        int right;
        int val;
        int lazy;
        Node(int l, int r, int v, int lz) : left(l), right(r), val(v), lazy(lz) {}
    };

    
}