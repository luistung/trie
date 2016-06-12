#-*- coding:utf8 -*-
import sys

class Trie:
    def __init__(self):
        self.root = {'children':{}, 'stop':False}

    def add(self, key):
        p = self.root
        for k in key:
            if k not in p['children']: 
                p['children'][k] = {'children':{}, 'stop':False}
            p = p['children'][k]
        if p['stop']: raise KeyError
        p['stop'] = True

    def load(self, l):
        '''用list初始化'''
        for key in l:
            self.add(key)

    def findAllPrefix(self, s):
        '''找到所有s的前缀'''
        p = self.root
        ret = []
        prefix = []
        for k in s:
            prefix.append(k)
            if k not in p['children']: break
            p = p['children'][k]
            if p['stop']:
                ret.append(prefix[:])
        return ret

    def findAll(self, s):
        '''mpm'''
        ret = []
        for i in xrange(len(s)):
            ret.extend(self.findAllPrefix(s[i:]))
        return ret
        
if __name__ == '__main__':
    part = [u'北京', u'北京站', u'上海']
    trie = Trie()
    trie.load(part)
    for i in trie.findAll(u'北京站到上海南'):
        print u''.join(i)
    
