
# Thread-Safe Bloom Filter Implementation

A high-performance, thread-safe Bloom filter implementation in C++ featuring atomic operations, singleton pattern, and custom hash functions for optimal concurrent access. 

*I did this project basically coz I wanted to do some multithreading in C++ and use C++ other than just doing algorithm problems.*

## Features

- **Thread-Safe**: Full concurrent support with atomic operations
- **Singleton Pattern**: Global access with lazy initialization
- **Lock-Free Operations**: Insert and lookup operations use atomic fetch_or and load
- **Custom Hash Functions**: Dual hashing with FNV-1a and std::hash
- **Memory Efficient**: Bit-packed storage with 64-bit atomic blocks
- **High Performance**: Zero-copy atomic operations with relaxed memory ordering

## Architecture

### Thread Safety Design

```cpp
class BloomFilter {
private:
    std::vector<std::unique_ptr<std::atomic<uint64_t>>> bit_array;
    static std::unique_ptr<BloomFilter> instance;
    static std::mutex mtx;
    
    // Thread-safe singleton initialization
    static BloomFilter* getInstance(size_t m_bits, size_t k_hashes);
    
    // Lock-free operations
    void Insert(const std::string &s);
    bool Contains(const std::string &s);
};
````

### Key Components

1. **Atomic Bit Array**: Each 64-bit block is wrapped in `std::atomic<uint64_t>` for lock-free bit manipulation
2. **Singleton Pattern**: Thread-safe lazy initialization with mutex protection
3. **Dual Hash Functions**: Reduces clustering and improves distribution
4. **Relaxed Memory Ordering**: Optimized for performance while maintaining correctness

## 🛡️ Thread Safety Guarantees

### Concurrency Model

* **Multiple Readers**: Unlimited concurrent `Contains()` calls
* **Multiple Writers**: Unlimited concurrent `Insert()` calls
* **Reader-Writer**: `Contains()` and `Insert()` can execute concurrently
* **Singleton Safety**: Instance creation is protected by mutex

### Atomic Operations

* `fetch_or()`: Atomically sets bits without race conditions
* `load()`: Atomically reads 64-bit blocks
* `memory_order_relaxed`: Optimal performance for independent operations

### Memory Safety

* No data races on bit manipulation
* ABA problem eliminated through atomic operations
* Memory ordering guarantees prevent reordering issues

## Performance Characteristics

| Operation  | Time Complexity | Space Complexity | Thread Safety     |
| ---------- | --------------- | ---------------- | ----------------- |
| Insert     | O(k)            | O(1)             | ✅ Lock-free       |
| Contains   | O(k)            | O(1)             | ✅ Lock-free       |
| Initialize | O(m/64)         | O(m/64)          | ✅ Mutex protected |

Where:

* `k` = number of hash functions
* `m` = number of bits in the filter

## Usage Example

```cpp
#include "bloom_filter.hpp"

int main() {
    // Get singleton instance (thread-safe initialization)
    BloomFilter* filter = BloomFilter::getInstance(1000000, 3);
    
    // Insert items (thread-safe)
    filter->Insert("hello");
    filter->Insert("world");
    filter->Insert("bloom");
    
    // Check membership (thread-safe)
    bool exists1 = filter->Contains("hello");  // true
    bool exists2 = filter->Contains("missing"); // false (or true - false positive)
    
    return 0;
}
```

## Benchmark Results

**Test Parameters:**

* `m` = 2^20 bits ~ 1e6 bits
* `k` = 6 hash functions
* Dataset size = 100000 strings

**Output:**

```
garv found!
linus found!
gavr not found!
Insertion: 63.4592 ms
Lookup: 62.1632 ms
```

Insertion and lookup performance are nearly identical due to both operations computing `k` hashes and touching `k` bits.

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Configuration

### Optimal Parameters

* **False Positive Rate**: `p ≈ (1 - e^(-kn/m))^k`
* **Optimal k**: `k = (m/n) * ln(2)`
* **Memory Usage**: `m` bits total

Where:

* `n` = expected number of elements
* `m` = number of bits in filter
* `k` = number of hash functions
* `p` = desired false positive probability

## Thread Safety Analysis

### Race Condition Prevention

1. **Bit Setting Race**: Atomic `fetch_or` ensures multiple threads can safely set the same bit
2. **Read-Write Race**: Atomic `load` provides consistent reads during concurrent writes
3. **Memory Reordering**: `memory_order_relaxed` prevents compiler/CPU reordering while maintaining performance

### Lock-Free Benefits

* **No Deadlocks**: No mutexes in hot paths
* **High Scalability**: Performance scales with CPU cores
* **Low Latency**: No blocking or context switching
* **Progress Guarantee**: Operations always complete in bounded time

## License

MIT License - see LICENSE file for details.

---

**Note**: This implementation prioritizes performance and thread safety. For applications requiring exact membership testing, consider using a traditional hash table or set instead.





