#ifndef IPMT_INDEX_H
#define IPMT_INDEX_H

class Index {
public:
  virtual void build(const std::string& text) = 0;
  virtual std::string serialize() const = 0;
  virtual unsigned int deserialize(const std::string& code, unsigned int offset = 0) = 0;
  virtual std::string magic() const = 0;
};

#endif /* IPMT_INDEX_H */
