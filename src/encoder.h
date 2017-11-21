#ifndef IPMT_ENCODER_H
#define IPMT_ENCODER_H

#include <string>

class Encoder {
public:
  virtual std::string encode(const std::string& text) = 0;
  virtual std::string decode(const std::string& code) = 0;

protected:
  std::string uintToBytes(uint32_t value);
  uint32_t bytesToUint(const std::string& bytes, int offset = 0);
};

#endif /* IPMT_ENCODER_H */
