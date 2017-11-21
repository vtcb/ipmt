#include "LZ77_encoder.h"

#include <string>

#define LZ77_0 '%'
#define LZ77_1 '$'

std::string LZ77Encoder::encode(const std::string& text) {
  std::string code;

  for (unsigned int i = 0; i < text.size(); i++) {
    if (i && text[i] == text[i - 1]) {
      code.push_back(LZ77_1);
      code += uintToBytes(1);
      code += uintToBytes(1);
      continue;
    }
    code.push_back(LZ77_0);
    code += text[i];
  }

  return code;
}

std::string LZ77Encoder::decode(const std::string& code) {
  std::string text;

  for (unsigned int i = 0; i < code.size();) {
    switch (code[i]) {
      case LZ77_0:
        text += code[i + 1];
        i += 1 + 1;
        break;
      case LZ77_1:
        do {
          uint32_t length = bytesToUint(code, i + 1);
          uint32_t offset = bytesToUint(code, i + 5);
          for (uint32_t j = text.size() - offset; length; j++, length--) {
            text += text[j];
          }
        } while (false);
        i += 1 + 4 + 4;
        break;
      default:
        // TODO(bolado): Report invalid code.
        i++;
    }
  }

  return text;
}
