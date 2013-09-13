#include <iostream>
#include <tr1/unordered_map>
#include <vector>

template<typename T, typename D>
struct TrieNode {
    typedef std::tr1::unordered_map<T, TrieNode*> Map;
    ~TrieNode();

    bool m_flag; //标识一个串的结尾
    D* m_data; 
    Map* m_children;
};


template<typename T, typename D = long>
class Trie {
public: 
    typedef TrieNode<T, D> Node;
    Trie();
    ~Trie();

    template<typename Iterator>
    void add(Iterator begin, Iterator end, const D* data = NULL);

    template<typename Iterator>
    Iterator has_longest(Iterator begin, Iterator end) const;
    

private:
    template<typename Iterator>
    void add(Iterator begin, Iterator end, Node* node, const D* data);

    void destroy(Node* node);

    TrieNode<T, D>* m_root;
};

