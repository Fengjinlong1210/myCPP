// 确定两个字符串是否接近
// 如果可以使用以下操作从一个字符串得到另一个字符串，则认为两个字符串 接近 ：

// 操作 1：交换任意两个 现有 字符。
// 例如，abcde -> aecdb
// 操作 2：将一个 现有 字符的每次出现转换为另一个 现有 字符，并对另一个字符执行相同的操作。
// 例如，aacabb -> bbcbaa（所有 a 转化为 b ，而所有的 b 转换为 a ）
// 你可以根据需要对任意一个字符串多次使用这两种操作。

// 给你两个字符串，word1 和 word2 。如果 word1 和 word2 接近 ，就返回 true ；否则，返回 false 。


//也就是判断字符种类是否相同，字符出现的次数是否相同

class Solution {
public:
    bool closeStrings(string word1, string word2) 
    {
        vector<int> arr1(26, 0);
        vector<int> arr2(26, 0);
        for(auto & ch : word1)
        {
            arr1[ch - 'a']++;
        }
        for(auto & ch : word2)
        {
            arr2[ch - 'a']++;
        }
        //判断字符出现的次数和字符种类是否一样
        for(int i = 0; i < 26; ++i)
        {
            if(arr1[i] + arr2[i] == 0) continue;//都为零，跳过
            if(arr1[i] == 0 || arr2[i] == 0) return false;//如果一个存在一个不存在，错误
        }
        sort(arr1.begin(), arr1.end(), greater());
        sort(arr2.begin(), arr2.end(), greater());
        for(int i = 0; i < 26; ++i)
        {
            if(arr1[i] != arr2[i]) return false;
        }
        return true;
    }
};