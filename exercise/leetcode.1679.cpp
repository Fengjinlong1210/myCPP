给你一个整数数组 nums 和一个整数 k 。

每一步操作中，你需要从数组中选出和为 k 的两个整数，并将它们移出数组。

返回你可以对数组执行的最大操作数。

//先对数组进行排序, 得到升序数组
//利用双指针, 如果前后相加相等, 计数器++
//不相等, 不断调整指针位置, 直到相等或者指针相遇

class Solution {
public:
    int maxOperations(vector<int>& nums, int k) 
    {
        int ret = 0;
        sort(nums.begin(), nums.end());
        int left = 0;
        int right = nums.size() - 1;
        while(left < right)
        {
            if(nums[left] + nums[right] == k)
            {
                ++ret;
                ++left;
                --right;
            }
            else if(nums[left] + nums[right] < k)
                ++left;
            else
                --right;
        }
        return ret;
    }
};