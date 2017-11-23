#include "suffix_tree_node.h"

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
