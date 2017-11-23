#include <iostream>
#include <string>

#include "suffix_tree.h"
#include "LZ77_encoder.h"

#define dbg(x) std::cerr << ">>> " << x << std::endl;
#define _ << ", " <<

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  // Suffix tree test
  auto st = SuffixTree();
  // std::string text = "abcabxabcd$";
  std::string text = "abcabxabcd$";
  st.build(text);
  st.traverse(text);

  // // Encoder test
  // auto encoder = LZ77Encoder();
  // // std::string text = "aacaacabcabaaac";
  // std::string text = "aaaaaaaaaaaaaaaaaaaa";
  // std::string encoded = encoder.encode(text);
  // std::string decoded = encoder.decode(encoded);

  // dbg(text);
  // dbg(encoded _ encoded.length());
  // dbg(decoded _ decoded.length());

  return 0;
}
