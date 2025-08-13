#include <hash_functions.hpp>
#include <bitset>
uint64_t Hasher::hash_a(const std::string &s){
  uint64_t fnvPrime = 16777619;
  uint64_t hash = 2166136261;

  for(int i =0 ;i<s.size();i++){
    unsigned char charCode = s[i];
    unsigned int firstOctet = charCode & 0xFF;
    hash = hash ^ firstOctet;
    hash = (hash * fnvPrime);  // Multiply by FNV prime
    hash = hash & 0xFFFFFFFF; 

    // Extract the second octet (high byte) and update hash
    unsigned int secondOctet = charCode >> 8;
    hash = hash ^ secondOctet;
    hash = (hash * fnvPrime);  

    hash = hash & 0xFFFFFFFF;
  }
  return hash;
}

uint64_t Hasher::hash_b(const std::string &s) {
  std::hash<std::string> hasher;
  size_t hash_value = hasher(s);
  return static_cast<uint64_t>(hash_value);
}