#include <iostream>
#include <string>

#include "LZ77_encoder.h"

#define dbg(x) std::cerr << ">>> " << x << std::endl;
#define _ << ", " <<

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  auto encoder = LZ77Encoder();
  std::string text = "aacabcc";
  std::string encoded = encoder.encode(text);
  std::string decoded = encoder.decode(encoded);

  dbg(text);
  dbg(encoded);
  dbg(decoded);

  return 0;
}
