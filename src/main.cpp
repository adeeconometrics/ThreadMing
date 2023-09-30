#include "../include/ThreadPool.hpp"
#include "../include/Utils.hpp"

#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

auto process(const std::size_t id, std::mutex &mtx) -> size_t {
  std::unique_lock<std::mutex> lock(mtx);
  std::cout << "Starting: " << id << std::endl;
  lock.unlock();

  const int seconds = int(std::rand() % 5); // make seeded
  std::this_thread::sleep_for(std::chrono::seconds(seconds)); 

  return id;
}

auto main() -> int {
  const int size = 20;
  std::mutex mtx;
  // Timer t;

  ThreadPool<std::shared_future<std::size_t>> futures{
      std::thread::hardware_concurrency() - 1};

  std::thread t1([&futures,&size, &mtx]() -> void {
    for (std::size_t i = 0; i < size; i++) {
      // futures.push(i);
      std::shared_future<std::size_t> f = std::async(
          std::launch::async, std::ref(process), i, std::ref(mtx));
      futures.push(f);
      std::cout << "element pushed: " << i << std::endl;
    }
  });

  std::thread t2([&futures, &size]() -> void {
    for (std::size_t i = 0; i < size; i++) {
      std::shared_future<std::size_t> f = futures.pop();
      const auto element = f.get();

      std::cout << "element popped: " << element << std::endl;
    }
  });

  t1.join();
  t2.join();

  return 0;
}