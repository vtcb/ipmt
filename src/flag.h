#ifndef IPMT_FLAG_H
#define IPMT_FLAG_H

#include <string>
#include <vector>

class FlagBase {
public:
  virtual bool hasName(const char *)  = 0;
  virtual bool hasShortcut(char)      = 0;
  virtual bool needsValue()           = 0;
  virtual void setValue(const char *) = 0;
  virtual void setValue()             = 0;
  virtual bool isSet()                = 0;
};

template<class T> class Flag : public FlagBase {
public:
  Flag(const char *name, char shortcut, const T& value);
  bool hasName(const char *name);
  bool hasShortcut(char shortcut);
  bool needsValue();
  void setValue(const char *arg);
  void setValue();
  bool isSet();
  T getValue();

private:
  const char *name;
  char shortcut;
  T value;
  bool set;
};

#endif /* IPMT_FLAG_H */
