#include "LZ77_encoder.h"

#include <string>
#include <tuple>
#include <utility>

#define LZ77_0 '%'
#define LZ77_1 '$'
#define LZ77_MIN_LENGTH 4

std::string LZ77Encoder::encode(const std::string& text) {
  std::string code;

  for (unsigned int at = 0; at < text.size();) {
    unsigned int best_length, best_offset;
    std::tie(best_length, best_offset) = bestMatch(text, at);

    if (best_length >= LZ77_MIN_LENGTH) {
      code.push_back(LZ77_1);
      code += int_encoder.uintToBytes(best_length);
      code += int_encoder.uintToBytes(best_offset);
      at += best_length;
    } else {
      code.push_back(LZ77_0);
      code += text[at];
      at++;
    }
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
          uint32_t length = int_encoder.bytesToUint(code, i + 1);
          uint32_t offset = int_encoder.bytesToUint(code, i + 5);
          for (unsigned int j = text.size() - offset; length; j++, length--) {
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

std::pair<unsigned int, unsigned int>
    LZ77Encoder::bestMatch(const std::string& text, unsigned int at) {
  unsigned int begin = at <= buffer_size ? 0 : at - buffer_size;
  unsigned int best_length = 0;
  unsigned int best_offset = 0;
  for (unsigned int i = begin; i < at; i++) {
    unsigned int cur_length = 0;
    while (cur_length < buffer_size
        && at + cur_length < text.size()
        && text[i + cur_length] == text[at + cur_length]) {
        cur_length++;
    }
    if (cur_length > best_length) {
      best_length = cur_length;
      best_offset = at - i;
    }
  }
  return std::make_pair(best_length, best_offset);
}
