#include "suffix_tree_node.h"

#include "int_encoder.h"

SuffixTreeNode::SuffixTreeNode(int begin, int end)
    : next(256, -1), begin_(begin), end_(end) {}

bool SuffixTreeNode::has(unsigned char ch) const {
  return next[ch] != -1;
}

int& SuffixTreeNode::operator [](unsigned char ch) {
  return next[ch];
}

int SuffixTreeNode::getBegin() const {
  return begin_;
}

int SuffixTreeNode::getEnd() const {
  return end_;
}

int SuffixTreeNode::getLength(int text_end) const {
  return (end_ == -1 ? text_end : end_ + 1) - begin_;
}

void SuffixTreeNode::setBegin(int begin) {
  this->begin_ = begin;
}

void SuffixTreeNode::setEnd(int end) {
  this->end_ = end;
}

void SuffixTreeNode::setLength(int length) {
  end_ = begin_ + length - 1;
}

std::string SuffixTreeNode::serialize() const {
  IntEncoder encoder;
  std::string code;

  code += encoder.uintToBytes(begin_);
  code += encoder.uintToBytes(end_);

  for (int edge : *this) {
    code += encoder.uintToBytes(edge);
    code += encoder.uintToBytes(next[edge]);
  }
  code += encoder.uintToBytes(-1);

  return code;
}

unsigned int SuffixTreeNode::deserialize(
    const std::string& code, unsigned int offset) {
  IntEncoder encoder;
  unsigned int initial_offset = offset;

  begin_ = encoder.bytesToUint(code, offset);
  end_ = encoder.bytesToUint(code, offset + 4);
  offset += 8;

  for (; offset < code.size();) {
    int edge = encoder.bytesToUint(code, offset);
    offset += 4;
    if (edge == -1) break;
    int node = encoder.bytesToUint(code, offset);
    offset += 4;
    next[edge] = node;
  }

  return offset - initial_offset;
}

SuffixTreeNode::iterator::iterator(const SuffixTreeNode* node, int at)
    : node(node), at(at) {}

unsigned char SuffixTreeNode::iterator::operator * () const {
  return at;
}

SuffixTreeNode::iterator SuffixTreeNode::iterator::operator ++() {
  increment(); return *this;
}

SuffixTreeNode::iterator SuffixTreeNode::iterator::operator ++(int) {
  iterator it = *this;
  increment();
  return it;
}

bool SuffixTreeNode::iterator::operator != (const iterator& it) {
  return at != it.at;
}

void SuffixTreeNode::iterator::increment() {
  do {
    at = std::min(at + 1, 256);
  } while (at < 256 && !node->has(at));
}
