给定一个二进制数组 nums 和一个整数 k，如果可以翻转最多 k 个 0 ，则返回 数组中连续 1 的最大个数 。
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) 
    {
        //右指针主动向后移动,左指针被动移动
        //左右指针维护了一个滑动窗口, 滑动窗口内部0的个数不能超过k
        //当右 - 左最大时就是要返回的结果
        int left = 0;
        int right = 0;
        int zeros = 0;
        int max = 0;
        for(; right < nums.size(); ++right)
        {
            if(nums[right] == 0)
                ++zeros;
            while(zeros > k)
            {
                //此时滑动窗口中的0已经超过k, 要让左指针向右移动,排除一些0来满足条件
                if(nums[left++] == 0)   
                {
                    --zeros;
                }
            }
            if(right - left + 1 > max)
            {
                max = right - left + 1;
            }
        }
        return max;
    }
};