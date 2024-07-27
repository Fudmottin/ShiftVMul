#include <iostream>
#include <vector>
#include <random>
#include <chrono>

inline int mul_by_two(int a) {
    int result;
    asm("imul $2, %1, %0\n\t"  // Multiply %1 by 2 and store the result in %0
        : "=r"(result)         // Output
        : "r"(a)               // Input
        : "cc");               // Clobbered
    return result;
}

inline int shift_by_one(int a) {
    int result;
    asm("shl $1, %1\n\t"       // Shift left by 1
        "mov %1, %0\n\t"       // Move the result to the output variable
        : "=r"(result)         // Output
        : "r"(a)               // Input
        : "cc");               // Clobbered
    return result;
}

int main() {
    std::vector<int> vec(10'000'000);

    // Fill vec with 10,000,000 random integer values using full range of ints
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    
    for (auto& e : vec) {
        e = dis(gen);
    }

    int i = 0;

    // Time the execution of the loop using mul_by_two and output time in microseconds
    auto start = std::chrono::high_resolution_clock::now();
    for (auto e : vec) {
        i = mul_by_two(e);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by mul_by_two: " << duration << " microseconds" << std::endl;

    // Time the execution of the loop using shift_by_one and output time in microseconds
    start = std::chrono::high_resolution_clock::now();
    for (auto e : vec) {
        i = shift_by_one(e);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by shift_by_one: " << duration << " microseconds" << std::endl;

    return 0;
}
