递增的三元子序列
给你一个整数数组 nums ，判断这个数组中是否存在长度为 3 的递增子序列。

如果存在这样的三元组下标 (i, j, k) 且满足 i < j < k ，使得 nums[i] < nums[j] < nums[k] ，返回 true ；否则，返回 false 


保存前两个变量，找到第三个就返回true

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) 
    {
        int n = nums.size();
        if(n < 3) return false;

        int first = nums[0];
        int second = INT_MAX;
        for(int i = 1; i < n; ++i)
        {
            //second前面一定有小于second的数字，所以只要找到大于second的就满足情况
            if(nums[i] > second) return true;
            else if(nums[i] <= first) first = nums[i];
            else second = nums[i];
        }
        //如果second < num, 找到了三元子序列
        //如果second >= num, num可能有几种情况
        // // 1. num小于first，那就更新first，使first尽可能小，找到答案的可能性更大
        // 如果遍历过程中遇到小于 first的元素，
        // 则会用该元素更新 first，虽然更新后的 first出现在 second的后面，但是在 second 
        // 的前面一定存在一个元素 first' 小于 second，
        // 因此当遇到 num>second时，(first',second,num)即为递增的三元子序列。

        // 2. num介于first和second之间，更新second
        return false;
    }
};