#include "encoder.h"

#include <string>

std::string Encoder::uintToBytes(uint32_t value) {
  std::string bytes;
  bytes += static_cast<unsigned char>(value >> 24);
  bytes += static_cast<unsigned char>(value >> 16);
  bytes += static_cast<unsigned char>(value >>  8);
  bytes += static_cast<unsigned char>(value >>  0);
  return bytes;
}

uint32_t Encoder::bytesToUint(const std::string& bytes, int offset) {
  return (static_cast<uint32_t>(static_cast<unsigned char>(
            bytes[offset + 0])) << 24)
       + (static_cast<uint32_t>(static_cast<unsigned char>(
            bytes[offset + 1])) << 16)
       + (static_cast<uint32_t>(static_cast<unsigned char>(
            bytes[offset + 2])) <<  8)
       + (static_cast<uint32_t>(static_cast<unsigned char>(
            bytes[offset + 3])) <<  0);
}
