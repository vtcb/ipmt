#ifndef IPMT_SUFFIX_ARRAY_H
#define IPMT_SUFFIX_ARRAY_H

#include <vector>
#include <string>

#include "index.h"

class SuffixArray : public Index {
public:
  void build(const std::string& text);
  int search(const std::string& pattern, const std::string& text);
  void traverse(const std::string& text);
  std::string serialize() const;
  unsigned int deserialize(const std::string& code, unsigned int offset = 0);
  std::string magic() const;

private:
  std::vector<int> arr;

  void print(const std::string& text) const;
};

#endif /* IPMT_SUFFIX_ARRAY_H */
