#include "flag.h"

#include <cstring>
#include <sstream>

template<class T> Flag<T>::Flag(const char *name, char shortcut, const T& value)
    : name(name),
      shortcut(shortcut),
      value(value),
      set(false) {}

template<class T> bool Flag<T>::hasName(const char *name) {
  return strcmp(this->name, name) == 0;
}

template<class T> bool Flag<T>::hasShortcut(char shortcut) {
  return this->shortcut == shortcut;
}

template<class T> bool Flag<T>::needsValue() {
  return true;
}

template<class T> void Flag<T>::setValue(const char *arg) {
  std::stringstream ss(arg);
  ss >> this->value;
  this->set = true;
}

template<class T> void Flag<T>::setValue() {}

template<class T> bool Flag<T>::isSet() {
  return this->set;
}

template<class T> T Flag<T>::getValue() {
  return this->value;
}

template<> bool Flag<bool>::needsValue() {
  return false; 
}

template<> void Flag<bool>::setValue() {
  this->value = true;
  this->set = true;
}

template class Flag<int>;
template class Flag<std::string>;
template class Flag<bool>;
