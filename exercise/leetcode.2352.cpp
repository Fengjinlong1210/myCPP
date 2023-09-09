// 给你一个下标从 0 开始、大小为 n x n 的整数矩阵 grid ，返回满足 Ri 行和 Cj 列相等的行列对 (Ri, Cj) 的数目。

// 如果行和列以相同的顺序包含相同的元素（即相等的数组），则认为二者是相等的。
//利用哈希表存储所有的行，然后取出所有的列于哈希表中的元素进行比较，如果相等计数器+1
class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) 
    {
        int n = grid.size();
        map<vector<int>, int> cnt;
        //将所有的行放入哈希表中
        for(auto& row : grid)
        {
            cnt[row]++;
        }

        int ret = 0;
        //取出所有的列于哈希表中的元素比较
        for(int i = 0; i < n; ++i)
        {
            vector<int> tmp;
            for(int j = 0; j < n; ++j)
            {
                tmp.push_back(grid[j][i]);
            }
            //取出了一整行
            if(cnt.count(tmp))
            {
                ret += cnt[tmp];
            }
        }
        return ret;
    }
};