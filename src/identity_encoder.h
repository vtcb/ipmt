#ifndef IPMT_IDENTITY_ENCODER_H
#define IPMT_IDENTITY_ENCODER_H

#include <string>

#include "encoder.h"

class IdentityEncoder : public Encoder {
public:
  IdentityEncoder() {}
  std::string encode(const std::string& text) {
    return text;
  }
  std::string decode(const std::string& code) {
    return code;
  }
  std::string magic() const {
    return "IIII";
  }
};

#endif /* IPMT_IDENTITY_ENCODER_H */
