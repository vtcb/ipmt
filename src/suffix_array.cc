#include "suffix_array.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include "int_encoder.h"

void SuffixArray::build(const std::string& text) {
  // naive(text);
  arr = sais(text + "$");
}

std::vector<int> SuffixArray::sais(const std::string& text) {
  std::string alphabet = text;
  sort(alphabet.begin(), alphabet.end());
  alphabet.resize(unique(alphabet.begin(), alphabet.end()) - alphabet.begin());

  return sais(text, alphabet);
}

std::vector<int> SuffixArray::sais(const std::string& text, const std::string& alphabet) {
  char L_TYPE = 'L';
  char S_TYPE = 'S';

  int n = text.size();
  std::string       types(n, L_TYPE);
  std::vector<bool> lms  (n, false);
  std::vector<int>  sa   (n, -1);
  std::vector<int> alphabet_code = encodeAlphabet(alphabet);

  auto induceS = [&]() {
    std::vector<int> buckets = buildBuckets(text, alphabet_code, alphabet.size(), true);
    for (int i = n - 1; i > 0; i--) {
      if (sa[i] == 0 || types[sa[i] - 1] == L_TYPE) continue;
      int ch = encodeChar(text[sa[i] - 1], alphabet_code);
      sa[buckets[ch]] = sa[i] - 1;
      buckets[ch]--;
    }
  };

  auto induceL = [&]() {
    std::vector<int> buckets = buildBuckets(text, alphabet_code, alphabet.size(), false);
    for (int i = 0; i < n; i++) {
      if (sa[i] == 0 || types[sa[i] - 1] == S_TYPE) continue;
      int ch = encodeChar(text[sa[i] - 1], alphabet_code);
      sa[buckets[ch]] = sa[i - 1];
      buckets[ch]++;
    }
  };

  types.back() = S_TYPE;
  lms.back() = true;

  for (int i = n - 2; i >= 0; i--) {
    types[i] = text[i] == text[i + 1] ? types[i + 1] : text[i] < text[i + 1] ? S_TYPE : L_TYPE;
    lms[i + 1] = types[i] == L_TYPE && types[i + 1] == S_TYPE;
  }

  std::vector<int> buckets = buildBuckets(text, alphabet_code, alphabet.size(), false);
  for (int i = 0; i < n; i++) {
    if (!lms[i]) continue;
    int ch = encodeChar(text[i], alphabet_code);
    sa[buckets[ch]] = i;
    buckets[ch]--;
  }

  induceL();
  induceS();

  int idx = 0;
  for (int i = 0; i < n; i++) {
    if (!lms[sa[i]]) continue;
    sa[idx++] = sa[i];
  }

  int nseg = 0;
  std::vector<std::pair<int, int>> text_red;
  for (int i = 0; i < idx; i++) {
    if (i == 0) {
      text_red.push_back({sa[i], nseg});
      continue;
    }
    bool diff = false;
    int d = 0;
    while (true) {
      if (d > 0 && lms[sa[i - 1] + d] && lms[sa[i] + d]) {
        break;
      }
      if (   (lms[sa[i - 1] + d] && !lms[sa[i] + d])
          || text[sa[i] + d] != text[sa[i - 1] + d]
          || types[sa[i] + d] != types[sa[i - 1] + d]) {
        diff = true;
        break;
      }
      d++;
    }
    if (diff) {
      nseg++;
    }
    text_red.push_back({sa[i], nseg});
  }
  sort(text_red.begin(), text_red.end());

  std::vector<int> new_sa;
  if (nseg < idx) {
    std::string new_alphabet;
    for (int i = 0; i < nseg; i++) {
      new_alphabet.push_back(i);
    }

    std::string new_text;
    new_text.reserve(text_red.size());
    for (unsigned int i = 0; i < text_red.size(); i++) {
      new_text.push_back(text_red[i].second);
    }

    new_sa = sais(new_text, new_alphabet);
  } else {
    new_sa.assign(-1, idx);
    for (int i = 0; i < idx; i++) {
      new_sa[text_red[i].second] = i;
    }
  }

  // new_sa should be used in sortLms.

  sa.assign(n, -1);
  buckets = buildBuckets(text, alphabet_code, alphabet.size(), true);

  auto sortLms = [&]() {
    std::vector<int> buckets = buildBuckets(text, alphabet_code, alphabet.size(), false);
    std::vector<std::pair<std::string, int>> lms_suf;
    for (int i = 0; i < n; i++) {
      if (!lms[i]) continue;
      lms_suf.push_back({text.substr(i), i});
    }
    sort(lms_suf.begin(), lms_suf.end());
    sa.assign(n, -1);
    for (auto it : lms_suf) {
      int i = it.second;
      int ch = encodeChar(text[i], alphabet_code);
      sa[buckets[ch]++] = i;
    }
  };

  sortLms();
  induceL();
  induceS();

  return sa;
}



// def sort_lms(txt, typ, lms, ab):
//     n = len(txt)
//     buck = buckets(txt, ab, end=False)
//     lmssuf = []
//     for i in range(n):
//         if lms[i]:
//             lmssuf.append((txt[i:], i))
//     lmssuf.sort()
//     sa = n*[-1]
//     for (ss, i) in lmssuf:
//         sa[buck[char_rank(ab,txt[i])]] = i
//         buck[char_rank(ab, txt[i])] += 1
//     return sa 


//     SA = sort_lms(txt, typ, lms, ab)
//     print_SA(SA, ab, txt, typ, lms)
//     induce_L(txt, SA, typ, ab, lms)
//     print_SA(SA, ab, txt, typ, lms)
//     induce_S(txt, SA, typ, ab, lms)
//     print_SA(SA, ab, txt, typ, lms)
//     return SA

std::vector<int> SuffixArray::encodeAlphabet(const std::string& alphabet) {
  std::vector<int> code(256, -1);
  int idx = 0;

  for (unsigned char ch : alphabet) {
    if (code[ch] == -1) {
      code[ch] = idx++;
    }
  }

  return code;
}

int SuffixArray::encodeChar(unsigned char ch, const std::vector<int>& code) {
  return code[ch];
}

std::vector<int> SuffixArray::buildBuckets(
    const std::string& text, const std::vector<int>& code, int alphabet_size, bool end) {
  std::vector<int> buckets(alphabet_size, 0);
  for (unsigned int i = 0; i < text.size(); i++) {
    buckets[encodeChar(text[i], code)]++;
  }
  int cum = 0;
  for (int i = 0; i < alphabet_size; i++) {
    cum += buckets[i];
    buckets[i] = end ? cum - 1 : cum - buckets[i];
  }
  return buckets;
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
  int matches = 0;

  for (int suf : arr) {
    matches += pattern == text.substr(suf, pattern.size());
  }

  return matches;
}

void SuffixArray::print(const std::string& text) const {
  std::cout << "SUFFIX ARRAY" << std::endl;
  for (int suf : arr) {
    std::cout << text.substr(suf) << std::endl;
  }
}

std::string SuffixArray::serialize() const {
  std::string code;

  code += IntEncoder::uintToBytes(arr.size());

  for (int suf : arr) {
    code += IntEncoder::uintToBytes(suf);
  }

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
