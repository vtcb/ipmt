#ifndef IPMT_SUFFIX_TREE_H
#define IPMT_SUFFIX_TREE_H

#include <vector>
#include <string>

#include "index.h"
#include "suffix_tree_node.h"

class SuffixTree : public Index {
public:
  void build(const std::string& text);
  void traverse(const std::string& text);
  std::string serialize() const;
  unsigned int deserialize(const std::string& code, unsigned int offset = 0);

private:
  std::vector<SuffixTreeNode> nodes;
  std::vector<int> suffix_links;

  void traverse(int node, int level, const std::string& text);
  int splitNode(int node, unsigned char edge, int length, const std::string& text);
};

#endif /* IPMT_SUFFIX_TREE_H */
