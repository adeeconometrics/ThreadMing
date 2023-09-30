#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

template <typename T>
struct ThreadPool {
public:
    ThreadPool(): m_size(5) {}
    ThreadPool(std::size_t t_size): m_size(t_size) {}
    ThreadPool(const ThreadPool&) = default;
    ThreadPool(ThreadPool&&) = default;
    ~ThreadPool() = default;

    auto push(const T& t_item) -> void {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_cond.wait(lock, [this]() { return m_queue.size() < m_size; });

      m_queue.push(t_item);
      lock.unlock();
      m_cond.notify_one();
    }

    auto pop() -> T {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_cond.wait(lock, [this]() { return !m_queue.empty(); });

      const T item = m_queue.front();
      m_queue.pop();

      lock.unlock();
      m_cond.notify_all();

      return item;
    }
    
    auto size() -> std::size_t {
      std::lock_guard<std::mutex> lock(m_mutex);
      return m_size;
    }

    auto front() -> T {
      std::lock_guard<std::mutex> lock(m_mutex);
      return m_queue.front();
    }

private:
    std::size_t m_size;
    std::mutex m_mutex;
    std::queue<T> m_queue;
    std::condition_variable m_cond;
};

#endif // __THREADPOOL_H__