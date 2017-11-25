#ifndef IPMT_FLAG_PARSER_H
#define IPMT_FLAG_PARSER_H

#include <string>
#include <vector>
#include "flag.h"

class FlagParser {
public:
  void addFlag(FlagBase* flag);
  FlagBase *findByName(const char *name);
  FlagBase *findByShortcut(char shortcut);
  void parse(int argc, char *argv[]);
  const std::vector<std::string>& getArgs();

private:
  std::vector<FlagBase*> flags;
  std::vector<std::string> args;
};

#endif /* IPMT_FLAG_PARSER_H */