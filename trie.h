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

    template<typename V>
    void add(const V& v, const D* data = NULL);

    template<typename V>
    typename V::const_iterator has_longest(const V& v) const;
    

private:
    template<typename V>
    void add(typename V::const_iterator begin, typename V::const_iterator end, Node* node, const D* data);
    void destroy(Node* node);

    TrieNode<T, D>* m_root;
};

