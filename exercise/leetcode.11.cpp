盛最多水的容器
给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。

找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

//采用双指针解决
//开始时, 计算整个容器能装的体积, 体积取决于较短的边长
//然后不断向内缩
//内缩规则: 将短边的变长向内收, 然后更新最大值
//如果缩长边, 那么短边是不变的, 体积只会变小
class Solution {
public:
    int maxArea(vector<int>& height) 
    {
        int front = 0;
        int back = height.size() - 1;
        size_t max = 0;
        while(front < back)
        {
            size_t volume = (back - front) * min(height[front], height[back]);
            if(volume > max)
                max = volume;
            if(height[front] < height[back]) 
                ++front;
            else
                --back;
        }
        return max;
    }
};