#ifndef IPMT_ENCODER_H
#define IPMT_ENCODER_H

#include "int_encoder.h"

// TODO(bolado): Make it static or singleton.
class Encoder {
public:
  virtual std::string encode(const std::string& text) = 0;
  virtual std::string decode(const std::string& code) = 0;
  virtual std::string magic() const = 0;
};

#endif /* IPMT_ENCODER_H */
