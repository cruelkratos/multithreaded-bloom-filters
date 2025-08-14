#include <hash_functions.hpp>
#include <murmur3.h>
#include <bitset>
#include <cstdint>

uint64_t Hasher::hash_a(const std::string &s){
  uint64_t fnvPrime = 16777619;
  uint64_t hash = 2166136261;

  for(size_t i = 0; i < s.size(); i++){
    unsigned char charCode = s[i];
    hash = hash ^ charCode;
    hash = (hash * fnvPrime);
    hash = hash & 0xFFFFFFFF; 
  }
  return hash;
}

uint64_t Hasher::hash_b(const std::string &s) {
  std::hash<std::string> hasher;
  uint64_t out[2]; 
  MurmurHash3_x64_128(s.data(), static_cast<int>(s.size()), 0x12345678, out);
  return out[0]; // first 64 bits
}