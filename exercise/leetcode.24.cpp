/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
//两两交换链表中的节点
class Solution {
public:
    ListNode* swapPairs(ListNode* head) 
    {
        if(!head || !head->next) return head;

        ListNode* tmp = swapPairs(head->next->next);
        ListNode* ret = head->next;
        head->next->next = head;
        head->next = tmp;
        return ret;
    }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) 
    {
        if(!head || !head->next) return head;

        ListNode* cur = head;
        ListNode* nxt = head->next;
        ListNode* ret = nxt;
        ListNode* nnxt = head->next->next;
        ListNode* prev = nullptr;
        int i = 0;
        while(cur && nxt)
        {
            cur->next->next = cur;
            cur->next = nnxt;
            if(i > 0)
                prev->next = nxt;
            prev = cur;
            if(!cur->next || !cur->next->next) break;
            cur = nnxt;
            nxt = cur->next;
            nnxt = nxt->next;

            ++i;
        }
        return ret;
    }
};