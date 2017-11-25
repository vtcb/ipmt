#ifndef IPMT_MAGIC_H
#define IPMT_MAGIC_H

#include <string>

#include "index.h"
#include "encoder.h"

class Magic {
public:
  Magic(Index *index = nullptr, Encoder *encoder = nullptr);

  void save(const std::string& file_name, const std::string& text);
  std::string open(const std::string& file_name);

  Index *getIndex() const;
  Encoder *getEncoder() const;

private:
  Index *index;
  Encoder *encoder;

  std::string MAGIC = "IPMT";
};

#endif /* IPMT_MAGIC_H */
