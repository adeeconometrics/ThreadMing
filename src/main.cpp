#include "../include/ThreadPool.hpp"

#include <thread>
#include <iostream>

auto main() -> int {
    ThreadPool<std::size_t> q(10);

    std::thread t1([&q]()-> void {
        for(std::size_t i = 0; i < 10; i++){
            q.push(i);
            std::cout << "element pushed: " << i << std::endl;
        }
    });

    std::thread t2([&q]() -> void {
      for (std::size_t i = 0; i < 10; i++) {
        const unsigned long element = q.pop();
        std::cout << "element popped: " << element << std::endl;
      }
    });

    t1.join();
    t2.join();

    return 0;
}