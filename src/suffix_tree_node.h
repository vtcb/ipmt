#ifndef IPMT_SUFFIX_TREE_NODE_H
#define IPMT_SUFFIX_TREE_NODE_H

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

private:
  std::vector<int> next;
  int begin;
  int end;
};

#endif /* IPMT_SUFFIX_TREE_NODE_H */
