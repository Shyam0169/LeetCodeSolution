/*
 * @Author: zephyrfun
 * @Date: 2021-02-01 21:48:48
 * @LastEditTime: 2021-02-01 22:00:43
 * @LastEditors: zephyrfun
 * @FilePath: \greedy\455_Assign_Cookies.cpp
 */
#include <iostream>
#include <algorithm>
#include <vector>

int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int child_index = 0;
    int cookie_index = 0;
    while(child_index < g.size() && cookie_index < s.size())
    {
        if(g[child_index] <= s[cookie_index])
            child_index += 1;
        cookie_index += 1;
    }
    return child_index;
}