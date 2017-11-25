#include <fstream>
#include <iostream>
#include <string>

#include "encoder.h"
#include "index.h"
#include "help.h"
#include "magic.h"
#include "input_parser.h"

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  InputParser input_parser;
  input_parser.parse(argc, argv);

  if (input_parser.help()) {
    Help::help();
    return 0;
  }

  if (input_parser.mode() == "index") {
    std::vector<std::string> file_list = input_parser.fileList();
    if (file_list.empty()) {
      std::cout << "File list can't be empty." << std::endl;
      Help::usage();
      exit(1);
    }

    for (const std::string& file_name : file_list) {
      std::ifstream file(file_name);
      std::string text = std::string( (std::istreambuf_iterator<char>(file) ),
                                      (std::istreambuf_iterator<char>()     ) );
      Index *index = input_parser.index();
      Encoder *encoder = input_parser.encoder();

      index->build(text);

      Magic(index, encoder).save(file_name + ".idx", text);
    }
  } else if (input_parser.mode() == "search") {
    std::vector<std::string> file_list = input_parser.fileList();
    std::vector<std::string> pattern_list = input_parser.patternList();

    if (file_list.empty()) {
      std::cout << "File list can't be empty." << std::endl;
      Help::usage();
      exit(1);
    }

    int matches = 0;
    for (const std::string& file_name : file_list) {
      Magic magic;
      std::string text = magic.open(file_name);
      for (const std::string& pattern : pattern_list) {
        matches += magic.getIndex()->search(pattern, text);
      }
    }
    std::cout << "Matches: " << matches << std::endl;
  } else {
    std::cout << "Invalid execution mode." << std::endl;
    Help::usage();
    exit(1);
  }

  return 0;
}
