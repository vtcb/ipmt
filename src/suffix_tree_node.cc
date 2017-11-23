#include "suffix_tree_node.h"

SuffixTreeNode::SuffixTreeNode(int begin, int end)
    : next(256, -1), begin(begin), end(end) {}

bool SuffixTreeNode::has(unsigned char ch) const {
  return next[ch] != -1;
}

int& SuffixTreeNode::operator [](unsigned char ch) {
  return next[ch];
}

int SuffixTreeNode::getBegin() const {
  return begin;
}

int SuffixTreeNode::getEnd() const {
  return end;
}

int SuffixTreeNode::getLength(int text_end) const {
  return (end == -1 ? text_end : end + 1) - begin;
}

void SuffixTreeNode::setBegin(int begin) {
  this->begin = begin;
}

void SuffixTreeNode::setEnd(int end) {
  this->end = end;
}

void SuffixTreeNode::setLength(int length) {
  end = begin + length - 1;
}
