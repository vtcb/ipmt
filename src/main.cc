#include <iostream>
#include <string>

#include "suffix_tree.h"
#include "LZ77_encoder.h"
#include "magic.h"

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

  auto saver = Magic(&st, new LZ77Encoder());
  saver.save("test.idx", text);

  auto opener = Magic();
  dbg("T: " << opener.open("test.idx"));
  ((SuffixTree*)opener.getIndex())->traverse(text);

  // // Encoder test
  // auto encoder = LZ77Encoder();
  // // std::string text = "aacaacabcabaaac";
  // std::string text = "aaaaaaaaaaaaaaaaaaaa";
  // std::string encoded = encoder.encode(text);
  // std::string decoded = encoder.decode(encoded);

  // dbg(text);
  // dbg(encoded _ encoded.length());
  // dbg(decoded _ decoded.length());


  // if (file_name != "") {
  //   std::ifstream ifs(file_name);
  //   text = std::string( (std::istreambuf_iterator<char>(ifs) ),
  //                       (std::istreambuf_iterator<char>()    ) );
  // }

  return 0;
}
