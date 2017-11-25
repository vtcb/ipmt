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
  std::string code;

  code += IntEncoder::uintToBytes(begin_);
  code += IntEncoder::uintToBytes(end_);

  for (int edge : *this) {
    code += IntEncoder::uintToBytes(edge);
    code += IntEncoder::uintToBytes(next[edge]);
  }
  code += IntEncoder::uintToBytes(-1);

  return code;
}

unsigned int SuffixTreeNode::deserialize(
    const std::string& code, unsigned int offset) {
  unsigned int initial_offset = offset;

  begin_ = IntEncoder::bytesToUint(code, offset);
  end_ = IntEncoder::bytesToUint(code, offset + 4);
  offset += 8;

  for (; offset < code.size();) {
    int edge = IntEncoder::bytesToUint(code, offset);
    offset += 4;
    if (edge == -1) break;
    int node = IntEncoder::bytesToUint(code, offset);
    offset += 4;
    next[edge] = node;
  }

  return offset - initial_offset;
}

SuffixTreeNode::iterator SuffixTreeNode::begin() const {
  iterator it(this, 0);
  if (!has(0)) ++it;
  return it;
}

SuffixTreeNode::iterator SuffixTreeNode::end() const {
  return iterator(this, 256);
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
