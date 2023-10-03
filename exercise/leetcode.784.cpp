给定一个字符串 s ，通过将字符串 s 中的每个字母转变大小写，我们可以获得一个新的字符串。

返回 所有可能得到的字符串集合 。以 任意顺序 返回输出。

class Solution {
public:
    vector<string> ret;
    string path;

    void dfs(string& s, int i)
    {
        if(i == s.size())
        {
            ret.push_back(s);
            return;
        }

            if(isalpha(s[i]))
            {
                //因为大写与小写之间相差了32，而32的二进制是0010 0000
                //只需异或32即可改变32对应的二进制位
                //如果是A, 即65  0100 0001, 转换到a 0110 0001
                s[i] ^= 32;
                dfs(s, i + 1);
                s[i] ^= 32;
                dfs(s, i + 1);
            }
            else
            {
                path += s[i];
                dfs(s, i + 1);
            }
        
    }

    vector<string> letterCasePermutation(string s) 
    {
        dfs(s, 0);
        return ret;

    }
};