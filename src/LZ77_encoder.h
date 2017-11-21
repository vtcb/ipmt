#ifndef IPMT_LZ77_ENCODER_H
#define IPMT_LZ77_ENCODER_H

#include <string>

#include "encoder.h"

class LZ77Encoder : public Encoder {
public:
  LZ77Encoder(uint32_t buffer_size = 256) : buffer_size(buffer_size) {}
  std::string encode(const std::string& text);
  std::string decode(const std::string& code);

private:
  uint32_t buffer_size;
};

#endif /* IPMT_LZ77_ENCODER_H */
