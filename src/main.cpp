#include "../include/ThreadPool.hpp"

#include <thread>
#include <iostream>


auto main() -> int {
    const int size = 10;
    ThreadPool<int> q{10};

    std::thread t1([&]()-> void {
        for(std::size_t i = 0; i <size; i++){
            q.push(i);
            std::cout << "element pushed: " << i << std::endl;
        }
    });

    std::thread t2([&q, &size]() -> void {
      for (int i = 0; i < size; i++) {
        const int element = q.pop();
        std::cout << "element popped: " << element << std::endl;
      }
    });

    t1.join();
    t2.join();

    return 0;
}