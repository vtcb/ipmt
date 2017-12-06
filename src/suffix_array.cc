#include "suffix_array.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "int_encoder.h"

#define dbg(x) std::cerr << ">>> " << x << std::endl;
#define _ << ", " <<
void SuffixArray::build(const std::string& text) {
  cp(text);
}

void SuffixArray::cp(const std::string& text) {
  int n = text.size() + 1;
  std::vector<int> sa(n), ra(n), temp(n);
  int lim = std::max(256, n);
  std::vector<int> c(lim, 0);

  auto countSort = [&](int k) {
    c.assign(lim, 0);
    for (int i = 0; i < n; i++) {
      c[i + k < n ? ra[i + k] : 0]++;
    }

    for (int i = 0, sum = 0; i < lim; i++) {
      int t = c[i];
      c[i] = sum;
      sum += t;
    }

    for (int i = 0; i < n; i++) {
      temp[c[sa[i] + k < n ? ra[sa[i] + k] : 0]++] = sa[i];
    }

    sa.swap(temp);
  };

  for (int i = 0; i < n; i++) {
    ra[i] = i == n - 1 ? 0 : static_cast<unsigned char>(text[i]);
    sa[i] = i;
  }

  for (int k = 1; k < n; k <<= 1) {
    dbg("ITER: " << k)
    dbg("CSK");
    countSort(k);
    dbg("CS0");
    countSort(0);
    dbg("TRA");
    int r = 0;
    temp[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
      temp[sa[i]] = 
          (ra[sa[i]] == ra[sa[i - 1]] && ra[sa[i] + k] == ra[sa[i - 1] + k])
          ? r : ++r;
    }
    dbg("SWA");
    ra.swap(temp);
    if (ra[sa[n - 1]] == n - 1) break;
  }

  arr = std::move(sa);
}

void SuffixArray::naive(const std::string& text) {
  arr.resize(text.size() + 1);

  for (unsigned int i = 0; i < arr.size(); i++) {
    arr[i] = i;
  }

  std::sort(arr.begin(), arr.end(), [&](int i, int j) {
    return text.substr(i) < text.substr(j);
  });
}

int SuffixArray::search(const std::string& pattern, const std::string& text) {
  dbg("SEARCH")
  // print(text);
  int lo = 0;
  int hi = arr.size() - 1;
  int lower = -1;

  auto lcp = [](const std::string& a, const std::string& b) {
    unsigned int ans = 0;
    while (ans < a.size() && ans < b.size() && a[ans] == b[ans]) ans++;
    return ans;
  };

  auto check = [&](int mid, int k) {
    return strncmp(
        text.c_str() + arr[mid] + k,
        pattern.c_str() + k,
        pattern.size());;
  };

  unsigned int k = 0;
  unsigned int n = text.size();
  unsigned int m = pattern.size();

  while (lo < hi) {
    int mid = lo + (hi - lo) / 2;

    while (k < m
        && arr[lo] + k < n
        && arr[hi] + k < n
        && text[arr[lo] + k] == text[arr[hi] + k]) {
      // dbg("HEY: " << k _ text[arr[lo] + k] _ pattern[k]);
      if (text[arr[lo] + k] != pattern[k]) return 0;
      k++;
    }
    if (k == m) break;

    if (check(mid, k) >= 0) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  if (check(lo, 0)) return 0;
  lower = lo;

  k = 0;
  hi = arr.size() - 1;
  while (lo < hi) {
    int mid = lo + (hi - lo) / 2;

    while (k < m
        && arr[lo] + k < n
        && arr[hi] + k < n
        && text[arr[lo] + k] == text[arr[hi] + k]) {
      // dbg("HEY: " << k _ text[arr[lo] + k] _ pattern[k]);
      k++;
    }
    if (k == m) break;

    if (check(mid, 0) > 0) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  if (check(hi, 0)) hi--;
  return hi - lower + 1;
}

void SuffixArray::print(const std::string& text) const {
  std::cout << "SUFFIX ARRAY" << std::endl;
  for (int suf : arr) {
    std::cout << text.substr(suf) << std::endl;
  }
}

std::string SuffixArray::serialize() const {
  dbg("SERIALIZE")
  std::string code;

  code += IntEncoder::uintToBytes(arr.size());

  for (int suf : arr) {
    code += IntEncoder::uintToBytes(suf);
  }
  dbg("DONE");

  return code;
}

unsigned int SuffixArray::deserialize(const std::string& code, unsigned int offset) {
  unsigned int initial_offset = offset;

  unsigned int length = IntEncoder::bytesToUint(code, offset);
  offset += 4;

  arr.resize(length);

  for (int& suf : arr) {
    suf = IntEncoder::bytesToUint(code, offset);
    offset += 4;
  }

  return offset - initial_offset;
}

std::string SuffixArray::magic() const {
  return "SARR";
}
