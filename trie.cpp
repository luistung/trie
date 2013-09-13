#include "trie.h"

template<typename T, typename D>
Trie<T, D>::Trie() : m_root(new TrieNode<T, D>()) {
}

template<typename T, typename D>
Trie<T, D>::~Trie() {
    if (m_root) {
        destroy(m_root); 
        m_root = NULL;
    }
}

template <typename T, typename D>
template <typename Iterator>
void Trie<T, D>::add(Iterator begin, Iterator end, const D* data) {
    add<Iterator>(begin, end, m_root, data);
}

template <typename T, typename D>
template <typename Iterator>
Iterator Trie<T, D>::has_longest(Iterator begin, Iterator end) const {
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

template <typename T, typename D>
template <typename Iterator>
void Trie<T, D>::add(Iterator begin, Iterator end, Node* node, const D* data) {
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

template<typename T, typename D>
void Trie<T, D>::destroy(Node* node) {
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

#include <iostream>
int main() {
    Trie<std::string> trie;
    std::string strs[100];
    strs[0] = "hello";
    strs[1] = "world";
    trie.add(&strs[0], &strs[2]);
    bool flag  = (trie.has_longest(&strs[0], &strs[2]) == &strs[2]);
    std::cout << flag << std::endl;
}
