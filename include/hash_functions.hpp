#pragma once
#include <string>


class Hasher{
  public:
  static uint64_t hash_a(const std::string &s);
  static uint64_t hash_b(const std::string &s);
};