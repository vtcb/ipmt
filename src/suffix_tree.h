#ifndef IPMT_SUFFIX_TREE_H
#define IPMT_SUFFIX_TREE_H

#include <vector>
#include <string>

#include "index.h"
#include "suffix_tree_node.h"

class SuffixTree : public Index {
public:
  void build(const std::string& text);
  int search(const std::string& pattern, const std::string& text);
  void traverse(const std::string& text);
  std::string serialize() const;
  unsigned int deserialize(const std::string& code, unsigned int offset = 0);
  std::string magic() const;

private:
  std::vector<SuffixTreeNode> nodes;
  std::vector<int> suffix_links;
  std::vector<int> matches;

  void traverse(int node, int level, const std::string& text);
  int splitNode(int node, unsigned char edge, int length, const std::string& text);
  void getMatches();
  int getMatches(int node);
};

#endif /* IPMT_SUFFIX_TREE_H */
