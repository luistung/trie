#ifndef __TRIE_H
#define __TRIE_H
#include <tr1/unordered_map>

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
    Trie() : m_root(new TrieNode<T, D>()) {
    }

    ~Trie() {
        if (m_root) {
            destroy(m_root); 
            m_root = NULL;
        }
    }


    template<typename Iterator>
    void add(Iterator begin, Iterator end, const D* data = NULL) {
        add<Iterator>(begin, end, m_root, data);
    }

    template<typename Iterator>
    Iterator has_longest(Iterator begin, Iterator end) const {
        Iterator cur = begin;
        Iterator ret = cur;
        typename Node::Map::iterator it;
        Node* node = m_root;

        while (cur != end && node->m_children && (it = node->m_children->find(*cur)) != node->m_children->end()) {
            node = it->second; 
            cur++;
            if (node->m_flag) {
                ret = cur;
            }
        }
        return ret;
    }

    

private:
    template<typename Iterator>
    void add(Iterator begin, Iterator end, Node* node, const D* data) {
        if (begin == end) {
            node->m_flag = true;
            if (data) {
                node->m_data = new D(*data);
            }
            return;
        }
        if (!node->m_children) {
            node->m_children = new typename Node::Map();
        }
        Node* childNode = node->m_children->operator[](*begin);
        if (childNode == NULL) {
            childNode = new Node;
            node->m_children->operator[](*begin) = childNode;
        }
        add<Iterator>(begin + 1, end, childNode, data);
    }


    void destroy(Node* node) {
        if (node->m_data) {
            delete node->m_data;
            node->m_data = NULL;
        }
        if (node->m_children) {
            for (typename Node::Map::iterator it = node->m_children->begin(); it != node->m_children->end(); ++it) {
                if (it->second) {
                    destroy(it->second);
                    it->second = NULL;
                }
            }
            delete node->m_children;
            node->m_children = NULL;
        }
    }


    TrieNode<T, D>* m_root;
};

#endif
