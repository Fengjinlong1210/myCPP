给定一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。

每条从根节点到叶节点的路径都代表一个数字：

例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
计算从根节点到叶节点生成的 所有数字之和 。

叶节点 是指没有子节点的节点

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int dfs(TreeNode* root, int sum)
    {
        //到根节点时, 逐层返回
        sum = sum * 10 + root->val;
        if(!root->left && !root->right) 
        {
            return sum;
        }
        int ret = 0;
        //ret表示最后一层需要返回的值
        if(root->left)
            ret += dfs(root->left, sum);
        if(root->right)
            ret += dfs(root->right, sum);
        return ret;
    }

    int sumNumbers(TreeNode* root) 
    {
        return dfs(root, 0);
    }
};