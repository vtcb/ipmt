#include "magic.h"

#include <fstream>
#include <string>
#include <stdexcept>

#include "index.h"
#include "encoder.h"

#include "suffix_array.h"
#include "LZ77_encoder.h"

#include <iostream>
#define dbg(x) std::cerr << ">>> " << x << std::endl;
#define _ << ", " <<

Magic::Magic(Index *index, Encoder *encoder)
    : index(index), encoder(encoder) {
}

void Magic::save(const std::string& file_name, const std::string& text) {
  std::ofstream file(file_name, std::fstream::binary);
  std::string text_code = encoder->encode(text);
  std::string index_code = encoder->encode(index->serialize());

  auto writeToFile = [&](const std::string& str) {
    file.write(str.c_str(), str.size());
  };

  writeToFile(MAGIC);
  writeToFile(index->magic());
  writeToFile(encoder->magic());

  writeToFile(IntEncoder::uintToBytes(text_code.size()));
  writeToFile(text_code);
  writeToFile(index_code);

  file.close();
}

std::string Magic::open(const std::string& file_name) {
  std::ifstream file(file_name, std::fstream::binary);
  unsigned int text_size;
  std::string text;
  char buffer[5]; buffer[4] = '\0';

  file.read(buffer, 4);
  if (MAGIC.compare(buffer) != 0) {
    throw std::runtime_error("Not a valid index file.");
  }

  // TODO(bolado): Check for index type.
  file.read(buffer, 4);
  index = new SuffixArray();

  // TODO(bolado): Check for encoder type.
  file.read(buffer, 4);
  encoder = new LZ77Encoder();
  
  file.read(buffer, 4);
  text_size = IntEncoder::bytesToUint(buffer);

  text.resize(text_size);
  file.read(&text[0], text_size);
  text = std::move(encoder->decode(text));

  index->deserialize(
      encoder->decode(
          std::string( (std::istreambuf_iterator<char>(file) ),
                       (std::istreambuf_iterator<char>()   ) )));

  return text;
}

Index *Magic::getIndex() const {
  return index;
}

Encoder *Magic::getEncoder() const {
  return encoder;
}
