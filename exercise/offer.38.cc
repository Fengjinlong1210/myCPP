#include <iostream>
#include <set>
#include <vector>
using namespace std;
//字符串的全排列
class Solution {
public:
    void func(string str, int start)
    {
        if(start == str.size() - 1) //start到达末尾, 后面没有字符可以交换
        {
            res.push_back(str);
            //已经走到了最后
            return;
        }
        //每一层栈帧都有一个set用来记录本层是否重复
        set<char> s;

        for(int i = start; i < str.size(); ++i)
        {
            // 控制哪个字符作为起始字符
            if(s.count(str[i]) != 0) continue;//如果在该栈帧中已经有重复的字符作为了起始字符
                                            //就跳过本次循环
            s.insert(str[i]);       //该栈帧没有字符就插入
            swap(str[start], str[i]);   //交换开始和i指向的字符
            func(str, start + 1);       //交换后, start字符已经固定在这一次循环, 继续向后递归
            swap(str[start], str[i]);   //回溯, 还原位置
        }
    } 
    vector<string> res;
    
    vector<string> permutation(string s) 
    {
        func(s, 0);
        return res;
    }
};