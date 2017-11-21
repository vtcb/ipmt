#ifndef IPMT_LZ77_ENCODER_H
#define IPMT_LZ77_ENCODER_H

#include <string>
#include <utility>

#include "encoder.h"

class LZ77Encoder : public Encoder {
public:
  LZ77Encoder(unsigned int buffer_size = 256) : buffer_size(buffer_size) {}
  std::string encode(const std::string& text);
  std::string decode(const std::string& code);

private:
  std::pair<unsigned int, unsigned int>
      bestMatch(const std::string& text, unsigned int at);
  unsigned int buffer_size;
};

#endif /* IPMT_LZ77_ENCODER_H */
