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
    int cut(TreeNode* root)
    {
        if(!root)
            return 0;
        int leftval = cut(root->left);
        int rightval = cut(root->right);

        if(root->left && leftval == 0)
        {
            root->left = nullptr;
        }
        if(root->right && rightval == 0)
        {
            root->right = nullptr;
        }
        
        return leftval + rightval + root->val;
    }

    TreeNode* pruneTree(TreeNode* root) 
    {

        int ret = cut(root);
        if(ret == 0) return nullptr;
        return root;
    }
};