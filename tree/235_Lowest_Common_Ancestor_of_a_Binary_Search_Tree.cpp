/*** 
 * Author: zephyr
 * Date: 2020-12-27 10:18:49
 * LastEditors: zephyr
 * LastEditTime: 2020-12-27 11:20:05
 * FilePath: \tree\235_Lowest_Common_Ancestor_of_a_Binary_Search_Tree.cpp
 */
#include <iostream>
#include <vector>
using namespace std;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
// way 1 : two times traversal with memory usage
void getPath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path)
{
    if(root != target)
    {
        path.emplace_back(root);
        if(root->val > target->val)
        {
            getPath(root->left, target, path);
        }
        else
        {
            getPath(root->right, target, path);
        }
    }
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    vector<TreeNode*> p_path;
    getPath(root, p, p_path);
    p_path.emplace_back(p);
    vector<TreeNode*> q_path;
    getPath(root, q, q_path);
    q_path.emplace_back(q);
    TreeNode* res;
    for(int i = 0; i < p_path.size() && i < q_path.size(); i++)
    {
        if(p_path[i] == q_path[i])
        {
            res = p_path[i];
        }
        else
            break;
    }
    return res;
}

// way 2 : save memory
TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q)
{
    TreeNode* ancestor = root;
    while(true)
    {
        if(p->val < ancestor->val && q->val < ancestor->val)
            ancestor = ancestor->left;
        else if(p->val > ancestor->val && q->val > ancestor->val)
            ancestor = ancestor->right;
        else
            break;
    }
    return ancestor;
}