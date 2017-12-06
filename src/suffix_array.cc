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
  int lo = 0;
  int hi = arr.size() - 1;
  int lower = -1;
  // print(text);
  dbg("T: " << text);

  // return text[arr[200]] == 'A';

  // auto lcp = [](const char *a, const char *b) {
  //   int x = 0;
  //   while (*a && *b && *a == *b) x++, a++, b++;
  //   return x;
  // };

  // std::vector<int> Llcp(arr.size());
  // std::vector<int> Rlcp(arr.size());


  // auto lcp_suff = [&](i, j) {
  //   int n = text.size();
  //   int l = pattern.size();
  //   int lcp = 0
  //   for (int k = l - 1; k >= 0; k--) {
  //     if (i >= n || j >= n) break;
  //     if P[k][i]==P[k][j]:
  //         lcp += (2**k)
  //         i += (2**k)
  //         j += (2**k)
  //   return lcp;
  // }

  // auto fillLlcpRlcp = [&](int l, int r) {
  //   if (r - l > 1) {
  //     h = (l + r) / 2;
  //     Llcp[h] = lcp_suff(sa[l], sa[h]);
  //     Rlcp[h] = lcp_suff(sa[r], sa[h]);
  //     fillLlcpRlcp(l, h);
  //     fillLlcpRlcp(h, r);
  //   }
  // };

  auto check = [&](int mid) {
    const char *a = text.c_str() + arr[mid];
    const char *b = pattern.c_str();
    while (*a && *b && *a == *b) a++, b++;
    return *b == 0 ? 0 : static_cast<unsigned char>(*a) - static_cast<unsigned char>(*b);
    // return strncmp(
    //     text.c_str() + arr[mid],
    //     pattern.c_str(),
    //     pattern.size());;
  };

  while (lo < hi) {
    int mid = lo + (hi - lo) / 2;

    // int k = lcp(pattern.c_str(), text.c_str() + arr[lo]);
    // int l = lcp(text.c_str() + arr[lo], text.c_str() + arr[mid]);

    // if (k < l) {
    //   lo = mid + 1;
    // } else {

    // }

    if (check(mid) >= 0) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  dbg("CHECK: " << lo _ arr[lo] _ text[arr[lo]] _ check(lo))
  if (check(lo)) return 0;
  lower = lo;

  hi = arr.size() - 1;
  while (lo < hi) {
    int mid = lo + (hi - lo) / 2;

    if (check(mid) > 0) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  if (check(hi)) hi--;
  return hi - lower + 1;
}

void SuffixArray::print(const std::string& text) const {
  std::cout << "SUFFIX ARRAY" << std::endl;
  int cnt = 0;
  for (int suf : arr) {
    std::cout << cnt << ": '" << text.substr(suf, 10) << "'" << std::endl;
    cnt++;
    if (cnt == 15) {
      break;
    }
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
