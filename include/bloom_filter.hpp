#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <atomic>
#include <memory>
#include <mutex>


class BloomFilter{
  private:
  size_t m_bits;
  size_t k_hashes;
  static std::unique_ptr<BloomFilter> instance;  
  static std::mutex mtx;  
  std::vector<std::unique_ptr<std::atomic<uint64_t>>> bit_array;
  size_t hash_i(const std::string &item , size_t i) const;
  BloomFilter(size_t m_bits , size_t k_hashes);

  public:
  BloomFilter(const BloomFilter&) = delete;
  BloomFilter& operator=(const BloomFilter&) = delete;
  void Insert(const std::string &s);
  bool Contains(const std::string &s);
  static BloomFilter* getInstance(size_t m_bits = 1<<10, size_t k_hashes = 3);
};