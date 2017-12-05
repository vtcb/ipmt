#ifndef IPMT_SUFFIX_ARRAY_H
#define IPMT_SUFFIX_ARRAY_H

#include <vector>
#include <string>

#include "index.h"

class SuffixArray : public Index {
public:
  void build(const std::string& text);
  int search(const std::string& pattern, const std::string& text);
  std::string serialize() const;
  unsigned int deserialize(const std::string& code, unsigned int offset = 0);
  std::string magic() const;

private:
  std::vector<int> arr;

  void naive(const std::string& text);

  std::vector<int> sais(const std::string& text);
  std::vector<int> sais(const std::string& text, const std::string& alphabet);
  std::vector<int> buildBuckets(
      const std::string& text, const std::vector<int>& code, int alphabet_size, bool end);
  std::vector<int> encodeAlphabet(const std::string& alphabet);
  int encodeChar(unsigned char ch, const std::vector<int>& code);

  void print(const std::string& text) const;
};

#endif /* IPMT_SUFFIX_ARRAY_H */
