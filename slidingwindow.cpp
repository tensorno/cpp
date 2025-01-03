#include <bits/stdc++.h>
using namespace std;

class slidingWindow
{
public:
    int slidingWindow_fixedlength(string s, int k)
    { // 固定长度的滑动窗口
        char cs[] = {'a', 'e', 'i', 'o', 'u'};
        int n = s.size();
        int ans = 0;
        int cur = 0;
        int left = 0;
        int right = 0;
        while (right < n)
        {
            while (right - left < k && right < n)
            {
                if (find(begin(cs), end(cs), s[right]) != end(cs))  // if (judge(xx)替换
                    cur++;
                right++;
            }
            ans = max(ans, cur);
            if (find(begin(cs), end(cs), s[left]) != end(cs))   // if (judge(xx)替换
                cur--;
            left++;
        }
        return ans;
    }
}