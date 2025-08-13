#include "bloom_filter.hpp"
#include "hash_functions.hpp"
#include <iostream>
#include <thread>

void insert(BloomFilter* obj, const std::string& data){
  obj->Insert(data);
}

int main(){
  BloomFilter* obj = BloomFilter::getInstance(1<<20,6);
  std::thread t1(insert, obj, "garv");
  std::thread t2(insert, obj, "linus");
  t1.join();
  t2.join();
  if (obj->Contains("garv")) {
    std::cout << "garv found!" << std::endl;
  }
  if (obj->Contains("linus")) {
    std::cout << "linus found!" << std::endl;
  }
  if (!obj->Contains("gavr")) {
    std::cout << "gavr not found!" << std::endl;
  }

}