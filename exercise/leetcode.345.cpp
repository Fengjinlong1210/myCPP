class Solution {
public:
    bool judge(char ch)
    {
        if(ch == 'a' || ch == 'A') return true;
        if(ch == 'e' || ch == 'E') return true;
        if(ch == 'i' || ch == 'I') return true;
        if(ch == 'o' || ch == 'O') return true;
        if(ch == 'u' || ch == 'U') return true;
        return false;
    }

    string reverseVowels(string s) 
    {
        //双指针
        int n = s.size();
        int front = 0;
        int back = n - 1;
        while(front < back)
        {
            while(front < back && !judge(s[front]))
            {
                ++front;
            }
            while(front < back && !judge(s[back]))
            {
                --back;
            }
            swap(s[front], s[back]);
            ++front;
            --back;
        }
        return s;
    }
};