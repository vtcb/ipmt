#ifndef PMT_HELP_H
#define PMT_HELP_H

#include <iostream>

const char *USAGE =
"Usage: ipmt index [OPTION]... [TEXTFILE]...\n"
"       ipmt search [OPTION]... [PATTERN] [INDEXFILE]...\n"
"       ipmt search [OPTION]... -p [PATTERNFILE] [INDEXFILE]...\n";

// TODO(bolado): Write this.
const char *DESCRIPTION =
"IPMT -- Indexed Pattern Matching Tool\n"
"Index mode: Index and compress a textfile.\n"
"Search mode: Search pattern occurences using pre-processed index.\n";

const char *OPTIONS =
"Options:\n"
"  -h, --help        Display this text\n"
"  -i, --indextype   Specify index type [Index mode only]\n"
"  -z, --compression Specify compression algorithm [Index mode only]\n"
"  -p, --pattern     Specify file to get patterns from [Search mode only]\n";

// TODO(bolado): Handle stdout versus stderr.
class Help {
public:
  static void help() {
    output(USAGE, DESCRIPTION, OPTIONS);
  }

  static void usage() {
    output(USAGE);
  }

  static void options() {
    output(OPTIONS);
  }

private:
  template<typename T, typename... Args>
  static void output(T message, Args... args) {
    std::cout << message;
    output(args...);
  }
  template<typename T>
  static void output(T message) {
    std::cout << message;
  }
};

#endif /* PMT_HELP_H */
