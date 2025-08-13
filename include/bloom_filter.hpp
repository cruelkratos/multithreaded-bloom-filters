#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <atomic>
#include <memory>


class BloomFilter{
  private:
  size_t m_bits;
  size_t k_hashes;
  std::vector<std::unique_ptr<std::atomic<uint64_t>>> bit_array;
  size_t hash_i(const std::string &item , size_t i) const;

  public:
  BloomFilter(size_t m_bits , size_t k_hashes);
  void Insert(const std::string &s);
  bool Contains(const std::string &s);
};