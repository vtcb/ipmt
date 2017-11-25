#ifndef IPMT_INT_ENCODER_H
#define IPMT_INT_ENCODER_H

#include <string>

class IntEncoder {
public:
  static std::string uintToBytes(uint32_t value);
  static uint32_t bytesToUint(const std::string& bytes, int offset = 0);
};

#endif /* IPMT_INT_ENCODER_H */
