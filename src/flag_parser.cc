#include "flag_parser.h"

#include <string>
#include <vector>
#include "flag.h"

void FlagParser::addFlag(FlagBase* flag) {
  flags.push_back(flag);
}

FlagBase *FlagParser::findByName(const char *name) {
  for (FlagBase *flag : flags) {
    if (flag->hasName(name)) {
      return flag;
    }
  }
  return nullptr;
}

FlagBase *FlagParser::findByShortcut(char shortcut) {
  for (FlagBase *flag : flags) {
    if (flag->hasShortcut(shortcut)) {
      return flag;
    }
  }
  return nullptr;
}

void FlagParser::parse(int argc, char *argv[]) {
  args.clear();

  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];
    if (arg[0] != '-') {
      args.push_back(arg);
      continue;
    }
    if (arg[1] == '\0') continue;

    FlagBase *flag = nullptr;
    if (arg[1] == '-') {
      flag = findByName(arg + 2);
    } else {
      // TODO(bolado): Handle multiple options.
      flag = findByShortcut(arg[1]);
    }

    if (flag == nullptr) {
      // TODO(bolado): Report invalid option.
      continue;
    }

    if (flag->needsValue()) {
      bool hasValue = true;
      hasValue = hasValue && i < argc - 1;
      if (!hasValue) {
        // TODO(bolado): Report missing value.
        continue;
      }
      flag->setValue(argv[++i]);
    } else {
      flag->setValue();
    }
  }
}

const std::vector<std::string>& FlagParser::getArgs() {
  return args;
}
