#include <thread>
#include <vector>

void worker_insert(BloomFilter* filter, int start, int end) {
    for(int i = start; i < end; i++) {
        filter->Insert("item_" + std::to_string(i));
    }
}

void worker_lookup(BloomFilter* filter, int start, int end) {
    for(int i = start; i < end; i++) {
        bool found = filter->Contains("item_" + std::to_string(i));
        // Process result...
    }
}

int main() {
    BloomFilter* filter = BloomFilter::getInstance(1000000, 5);
    
    std::vector<std::thread> threads;
    
    for(int i = 0; i < 4; i++) {
        threads.emplace_back(worker_insert, filter, i*1000, (i+1)*1000);
    }
    
    for(int i = 0; i < 4; i++) {
        threads.emplace_back(worker_lookup, filter, i*1000, (i+1)*1000);
    }
    
    // Wait for all threads
    for(auto& t : threads) {
        t.join();
    }
    
    return 0;
}
