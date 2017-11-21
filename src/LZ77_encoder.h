#ifndef IPMT_LZ77_ENCODER_H
#define IPMT_LZ77_ENCODER_H

#include <string>

#include "encoder.h"

class LZ77Encoder : public Encoder {
public:
  std::string encode(const std::string& text);
  std::string decode(const std::string& text);
};

#endif /* IPMT_LZ77_ENCODER_H */
