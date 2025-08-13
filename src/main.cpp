#include "bloom_filter.hpp"
#include "hash_functions.hpp"
#include <iostream>
int main(){
  BloomFilter* obj = new BloomFilter(1<<20,6); 
  obj->Insert("garv");
  obj->Insert("linus");
  if(obj->Contains("garv")){
    std::cout<<"YEs"<<std::endl;
  }
  if(obj->Contains("gavr")){
    std::cout<<"YEs"<<std::endl;
  }
  else{
    std::cout<<"nooo"<<std::endl;
  }
  if(obj->Contains("linus")){
    std::cout<<"YESD"<<std::endl;
  }
  else{
    std::cout<<"NO"<<std::endl;
  }
  if(obj->Contains("liiinusss")){
    std::cout<<"YES D"<<std::endl;
  }
  else{
    std::cout<<"NO"<<std::endl;
  }
}