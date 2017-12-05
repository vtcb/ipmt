#include "input_parser.h"

#include <algorithm>
#include <fstream>
#include <locale>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "suffix_array.h"
#include "LZ77_encoder.h"

Flag<std::string> FLAG_MODE     ("mode",        'm', "");
Flag<std::string> FLAG_INDEX    ("indextype",   'i', "");
Flag<std::string> FLAG_ENCODER  ("compression", 'z', "");
Flag<std::string> FLAG_PATTERN  ("pattern",     'p', "");
Flag<bool>        FLAG_COUNT    ("count",       'c', false); // ?
Flag<bool>        FLAG_HELP     ("help",        'h', false);

void InputParser::parse(int argc, char *argv[]) {
  FLAG_PARSER.addFlag(&FLAG_MODE);
  FLAG_PARSER.addFlag(&FLAG_INDEX);
  FLAG_PARSER.addFlag(&FLAG_ENCODER);
  FLAG_PARSER.addFlag(&FLAG_PATTERN);
  FLAG_PARSER.addFlag(&FLAG_COUNT);
  FLAG_PARSER.addFlag(&FLAG_HELP);
  FLAG_PARSER.parse(argc, argv);
}

bool InputParser::help() {
  return FLAG_HELP.getValue();
}

std::string InputParser::mode() {
  return FLAG_MODE.getValue();
}

std::vector<std::string> InputParser::patternList() {
  std::vector<std::string> pattern_list;
  if (FLAG_MODE.getValue() == "index") {
    return pattern_list;
  }

  if (FLAG_PATTERN.isSet()) {
    std::ifstream pattern_file(FLAG_PATTERN.getValue());
    std::string line;
    while (std::getline(pattern_file, line)) {
      if (line != "") {
        pattern_list.push_back(line);
      }
    }
  } else if (!FLAG_PARSER.getArgs().empty()) {
    pattern_list.push_back(FLAG_PARSER.getArgs()[0]);
  }
  return pattern_list;
}

std::vector<std::string> InputParser::fileList() {
  std::vector<std::string> file_list;
  std::vector<std::string> args = FLAG_PARSER.getArgs();
  bool begin = FLAG_PATTERN.isSet() || FLAG_MODE.getValue() == "index";
  for (unsigned int i = begin ? 0 : 1; i < args.size(); i++) {
    file_list.push_back(args[i]);
  }
  return file_list;
}

Index *InputParser::index() {
  return new SuffixArray();
}

Encoder *InputParser::encoder() {
  return new LZ77Encoder();
}
