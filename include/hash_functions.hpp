#pragma once
#include <string>
#include <cstdint>


class Hasher{
  public:
  static uint64_t hash_a(const std::string &s);
  static uint64_t hash_b(const std::string &s);
};