给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。

题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。

请不要使用除法，且在 O(n) 时间复杂度内完成此题。

返回的数组中，每个位置都是当前下标之前所有数字的乘积、乘上当前下标后所有数字的乘积
所以可以创建两个数组，一个保存从左到右的乘积，一个保存从右到左的乘积，然后一一相乘得到返回的数组

方法一 左右乘积数组
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int> left(n, 1);
        vector<int> right(n, 1);
        for(int i = 1; i < n; ++i)
        {
            left[i] = left[i - 1] * nums[i - 1];
        }
        for(int i = n - 2; i >= 0; --i)
        {
            right[i] = right[i + 1] * nums[i + 1];
        }
        vector<int> ret(n, 1);
        for(int i = 0; i < n; ++i)
        {
            ret[i] = left[i] * right[i];
        }
        return ret;
    }
};


方法二

将右数组用整数代替，每次迭代乘上后面的数
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int> left(n, 1);
        for(int i = 1; i < n; ++i)
        {
            left[i] = left[i - 1] * nums[i - 1];
        }
        int right = 1;
        for(int i = n - 1; i >= 0; --i)
        {
            //ans[i] = left[i] * right[i]
            //right[i] = right[i + 1] * nums[i];
            left[i] = left[i] * right;
            right *= nums[i];
        }

        return left;
    }
};