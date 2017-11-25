#ifndef PMT_INPUT_PARSER_H
#define PMT_INPUT_PARSER_H

#include <string>
#include <vector>

#include "encoder.h"
#include "flag.h"
#include "flag_parser.h"
#include "index.h"

class InputParser {
public:
  void parse(int argc, char *argv[]);
  bool help();
  std::string mode();
  std::vector<std::string> patternList();
  std::vector<std::string> fileList();
  Index *index();
  Encoder *encoder();

private:
  FlagParser FLAG_PARSER;
};

#endif /* PMT_INPUT_PARSER_H */
