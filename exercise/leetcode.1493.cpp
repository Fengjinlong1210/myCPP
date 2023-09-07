
// 给你一个二进制数组 nums ，你需要从中删掉一个元素。

// 请你在删掉元素的结果数组中，返回最长的且只包含 1 的非空子数组的长度。

// 如果不存在这样的子数组，请返回 0 。
class Solution {
public:
    int longestSubarray(vector<int>& nums) 
    {
        int max = 0;
        int left = 0;
        int right = 0;;
        int zeros = 0;
        for (; right < nums.size(); right++) {
            if(nums[right] == 0) zeros++;
            while(zeros > 1)
            {
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

        return max - 1;

    }
};