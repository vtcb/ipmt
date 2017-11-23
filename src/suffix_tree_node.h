#ifndef IPMT_SUFFIX_TREE_NODE_H
#define IPMT_SUFFIX_TREE_NODE_H

#include <algorithm>
#include <vector>

class SuffixTreeNode {
public:
  SuffixTreeNode(int begin = -1, int end = -1);

  bool has(unsigned char ch) const;
  int& operator [](unsigned char ch);
  int getBegin() const;
  int getEnd() const;
  int getLength(int text_end) const;
  void setBegin(int begin);
  void setEnd(int end);
  void setLength(int length);

  class iterator {
  public:
    iterator(const SuffixTreeNode* node, int at);

    unsigned char operator * () const;

    iterator operator ++();
    iterator operator ++(int);

    bool operator != (const iterator& it);
  private:
    const SuffixTreeNode* node;
    int at;

    void increment();
  };

  iterator begin() const { return ++iterator(this, 0); }
  iterator end() const { return iterator(this, 256); }

private:
  std::vector<int> next;
  int begin_;
  int end_;
};

#endif /* IPMT_SUFFIX_TREE_NODE_H */
