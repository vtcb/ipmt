#include "suffix_tree.h"

#include <iostream>
#include <string>

#include "int_encoder.h"

void SuffixTree::build(const std::string& text) {
  // TODO(bolado): Do not depend on terminator.
  nodes = {SuffixTreeNode()};
  suffix_links = {0};

  int active_node = 0;
  int active_edge = -1;
  int active_length = 0;
  int total_length = 0;
  int remainder = 0;

  for (unsigned int i = 0; i < text.size(); i++) {
    unsigned char ch = text[i];
    remainder++;

    auto pushActiveNode = [&]() {
      if (active_edge == -1) return;
      auto getEdgeLength = [&]() {
        return nodes[nodes[active_node][active_edge]].getLength(text.size());
      };
      while (active_length > getEdgeLength()) {
        active_length -= getEdgeLength();
        active_node = nodes[active_node][text[i - remainder + total_length]];
      }
      if (active_length == getEdgeLength()) {
        active_node = nodes[active_node][active_edge];
        active_edge = -1;
        active_length = 0;
        total_length = 0;
      }
    };

    pushActiveNode();
    bool implicitlyRepresented = active_edge == -1
        ? nodes[active_node].has(ch)
        : ch == text[nodes[nodes[active_node][active_edge]].getBegin() + active_length];
 
    if (implicitlyRepresented) {
      if (active_edge == -1) {
        active_edge = ch;
        active_length = 1;
        total_length = 1;
      } else {
        active_length++;
        total_length++;
      }
    } else {
      int last_split_node = 0;
      int new_split_node = -1;
      for (; remainder; remainder--) {
        pushActiveNode();
        SuffixTreeNode new_node;
        if (active_edge == -1) {
          new_node.setBegin(i - remainder + 1);
          nodes[active_node][ch] = nodes.size();
        } else {
          new_node.setBegin(i);
          int from = splitNode(active_node, active_edge, active_length, text);
          new_split_node = from;
          nodes[from][ch] = nodes.size();

          if (active_node == 0) {
            active_edge = text[i - remainder + 2];
            active_length--;
            total_length--;
            if (active_length == 0) {
              active_edge = -1;
            }
          } else {
            active_node = suffix_links[active_node];
          }
          suffix_links[last_split_node] = new_split_node;
          last_split_node = new_split_node;
        }
        nodes.push_back(std::move(new_node));
        suffix_links.push_back(0);
      }
    }
  }
}

int SuffixTree::splitNode(
    int node, unsigned char edge, int length, const std::string& text) {
  int next_node = nodes[node][edge];
  SuffixTreeNode new_node(nodes[next_node].getBegin());
  new_node.setLength(length);

  nodes[next_node].setBegin(nodes[next_node].getBegin() + length);

  nodes[node][edge] = nodes.size();
  new_node[text[nodes[next_node].getBegin()]] = next_node;

  nodes.push_back(std::move(new_node));
  suffix_links.push_back(0);
  return nodes.size() - 1;
}

std::string SuffixTree::serialize() const {
  std::string code;

  code += IntEncoder::uintToBytes(nodes.size());

  for (const SuffixTreeNode& node : nodes) {
    code += node.serialize();
  }

  return code;
}

unsigned int SuffixTree::deserialize(
    const std::string& code, unsigned int offset) {
  unsigned int initial_offset = offset;

  unsigned int length = IntEncoder::bytesToUint(code, offset);
  offset += 4;

  nodes.assign(length, {});

  for (SuffixTreeNode& node : nodes) {
    offset += node.deserialize(code, offset);
  }

  return offset - initial_offset;
}

void SuffixTree::traverse(const std::string& text) {
  traverse(0, 0, text);
}

void SuffixTree::traverse(int node, int level, const std::string& text) {
  if (nodes[node].getBegin() >= 0) {
    for (int i = 0; i < level; i++) {
      std::cout << "  ";
    }
    std::cout
        << text.substr(
            nodes[node].getBegin(), nodes[node].getLength(text.size()))
        << std::endl;
    }
  // for (unsigned char i : nodes[node]) {
  for (auto i : nodes[node]) {
    int next = nodes[node][i];
    traverse(next, level + 1, text);
  }
}

std::string SuffixTree::magic() const {
  return "SUFT";
}
