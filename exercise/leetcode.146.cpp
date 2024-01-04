#include <iostream>
#include <unordered_map>

using namespace std;

class Node
{
public:
    Node()
        :_key(0), _value(0), _prev(nullptr), _next(nullptr)
    {}

    Node(int key, int value)
        :_key(key), _value(value), _prev(nullptr), _next(nullptr)
    {}
    
    int _key;
    int _value;
    Node* _prev;
    Node* _next;

};

class LRUCache 
{
private:
    unordered_map<int, Node*> _cache;
    int _size;
    int _capacity;
    Node* _head;
    Node* _tail;

public:
    LRUCache(int capacity) 
        :_size(0), _capacity(capacity)
    {
        _head = new Node;
        _tail = new Node;
        _head->_next = _tail;
        _tail->_prev = _head;
    }
    
    int get(int key) 
    {
        //如果不存在，返回-1
        if(_cache.count(key) == 0)
        {
            return -1;
        }
        // 存在时，返回该节点的value, 然后更新该节点的使用情况, 把该节点移动到链表头部
        Node* tmp = _cache[key];
        moveToHead(tmp);
        return tmp->_value;
    }
    
    void put(int key, int value) 
    {
        //如果节点存在，就更新节点位置和节点的值
        if(_cache.count(key))
        {
            Node* tmp = _cache[key];
            tmp->_value = value;
            moveToHead(tmp);
        }
        //如果节点不存在，需要判断cache的大小，如果已经满了，就在头部新增一个节点，删除尾部节点；如果没满就直接在头部添加
        else
        {
            Node* newnode = new Node(key, value);
            _cache[key] = newnode;
            if(_size < _capacity)
            {
                addToHead(newnode);
                _size++;
            }
            else
            {
                addToHead(newnode);
                Node* removed = removeTail();
                _cache.erase(removed->_key);
            }
        }
    }

    //将一个节点移动到链表头部
    void moveToHead(Node* node)
    {
        node->_prev->_next = node->_next;
        node->_next->_prev = node->_prev;
        addToHead(node);
    }

    //在链表头部新增一个节点
    void addToHead(Node* node)
    {
        node->_next = _head->_next;
        node->_next->_prev = node;
        node->_prev = _head;
        _head->_next = node;
    }

    //删除一个节点
    void remove(Node* node)
    {
        node->_prev->_next = node->_next;
        node->_next->_prev = node->_prev;
    }

    //删除尾部节点
    Node* removeTail()
    {
        Node* tail = _tail->_prev;
        remove(tail);
        return tail;
    }
};