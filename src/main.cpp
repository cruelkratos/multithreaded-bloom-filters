#include "bloom_filter.hpp"
#include "benchmark.hpp"
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
  Benchmark b(100000);
  b.generate_keys();
  double insert_time = b.measure([&](const std::string &key) {
        obj->Insert(key);
    });

    double lookup_time = b.measure([&](const std::string &key) {
        obj->Contains(key);
    });

    std::cout << "Insertion: " << insert_time << " ms\n";
    std::cout << "Lookup: " << lookup_time << " ms\n";
}