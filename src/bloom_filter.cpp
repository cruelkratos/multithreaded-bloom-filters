#include<bloom_filter.hpp>
#include<hash_functions.hpp>
#include<vector>
#include<string>
#include<vector>
#include<cassert>

std::unique_ptr<BloomFilter> BloomFilter::instance = nullptr;
std::mutex BloomFilter::mtx;

BloomFilter::BloomFilter(size_t m_bits , size_t k_hashes){
  this->m_bits = m_bits;
  this->k_hashes = k_hashes;
  auto size = (this->m_bits + 63) / 64;

  this->bit_array.reserve(size);
  for (size_t i = 0; i < size; ++i) {
    this->bit_array.emplace_back(std::make_unique<std::atomic<uint64_t>>(0));
  }
}

size_t BloomFilter::hash_i(const std::string &item , size_t i) const {
  assert(i < this->k_hashes);
  auto hash_a = Hasher::hash_a(item);
  auto hash_b = Hasher::hash_b(item);
  auto hash = (hash_a + i*hash_b)%(this->m_bits);
  return hash;
}

void BloomFilter::Insert(const std::string &s){
  for(int i = 0;i<this->k_hashes;i++){
    auto bit_idx = this->hash_i(s,i);
    auto block_idx = bit_idx>>6;
    auto val = bit_idx&63;
    this->bit_array[block_idx]->fetch_or(1ULL << val, std::memory_order_relaxed);
  }
}

bool BloomFilter::Contains(const std::string &s){
  for(int i = 0;i<this->k_hashes;i++){
    auto bit_idx = this->hash_i(s,i);
    auto block_idx = bit_idx>>6;
    auto val = bit_idx&63;
    auto block_val =  this->bit_array[block_idx]->load(std::memory_order_relaxed);
    if ((block_val & (1ULL << val)) == 0) return false;
  }
  return true;
}

BloomFilter* BloomFilter::getInstance(size_t m_bits , size_t k_hashes){
  std::lock_guard<std::mutex> lock(mtx);
  if(!instance){
    instance = std::unique_ptr<BloomFilter>(new BloomFilter(m_bits, k_hashes));
  }
  return instance.get();
}