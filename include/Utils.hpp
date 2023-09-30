#ifndef __UTILS_H__
#define __UTILS_H__

#include <chrono>
#include <iostream>

class Timer {
public:
  Timer() : start_time(std::chrono::high_resolution_clock::now()) {}
  ~Timer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        end_time - start_time)
                        .count();
    std::cout << "Elapsed time: " << duration << "ms \n";
  }

private:
  std::chrono::high_resolution_clock::time_point start_time;
};

#endif // __UTILS_H__