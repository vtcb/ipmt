#ifndef IPMT_ENCODER_H
#define IPMT_ENCODER_H

#include "int_encoder.h"

class Encoder {
public:
  virtual std::string encode(const std::string& text) = 0;
  virtual std::string decode(const std::string& code) = 0;

protected:
  IntEncoder int_encoder;
};

#endif /* IPMT_ENCODER_H */
