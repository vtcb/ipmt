#include <fstream>
#include <iostream>
#include <string>

#include "encoder.h"
#include "index.h"
#include "magic.h"
#include "input_parser.h"

#include "suffix_tree.h"
#define dbg(x) std::cerr << ">>> " << x << std::endl;
#define _ << ", " <<

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  InputParser input_parser;
  input_parser.parse(argc, argv);

  if (input_parser.help()) {
    dbg("PLEASE HELP ME!");
    return 0;
  }

  if (input_parser.mode() == "index") {
    std::vector<std::string> file_list = input_parser.fileList();
    if (file_list.empty()) {
      std::cout << "File list can't be empty." << std::endl;
      // usage
      exit(1);
    }

    for (const std::string& file_name : file_list) {
      std::ifstream file(file_name);
      std::string text = std::string( (std::istreambuf_iterator<char>(file) ),
                                      (std::istreambuf_iterator<char>()     ) );
      Index *index = input_parser.index();
      Encoder *encoder = input_parser.encoder();

      index->build(text);

      Magic(index, encoder).save("test.idx", text);
    }
  } else if (input_parser.mode() == "search") {
    std::vector<std::string> file_list = input_parser.fileList();
    if (file_list.empty()) {
      std::cout << "File list can't be empty." << std::endl;
      // usage
      exit(1);
    }

    for (const std::string& file_name : file_list) {
      Magic magic;
      std::string text = magic.open(file_name);
      ((SuffixTree*) magic.getIndex())->traverse(text);
      dbg(magic.getIndex()->search("x", text));
      dbg(magic.getIndex()->search("a", text));
      dbg(magic.getIndex()->search("ab", text));
      dbg(magic.getIndex()->search("abc", text));
    }
  } else {
    std::cout << "Invalid execution mode." << std::endl;
    // TODO(bolado): Show USAGE
    exit(1);
  }

  // // Suffix tree test
  // auto st = SuffixTree();
  // // std::string text = "abcabxabcd$";
  // std::string text = "abcabxabcd$";
  // st.build(text);
  // st.traverse(text);

  // auto saver = Magic(&st, new LZ77Encoder());
  // saver.save("test.idx", text);

  // auto opener = Magic();
  // dbg("T: " << opener.open("test.idx"));
  // ((SuffixTree*)opener.getIndex())->traverse(text);

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
