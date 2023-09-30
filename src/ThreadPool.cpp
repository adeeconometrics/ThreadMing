#include "../include/ThreadPool.hpp"
#include <condition_variable>
#include <mutex>
#include <thread>

template <typename T>
ThreadPool<T>::ThreadPool(std::size_t t_size) : m_size(t_size) {}

template <typename T>
ThreadPool<T>::ThreadPool(const ThreadPool<T> &) : m_size(2) {}

template <typename T> ThreadPool<T>::ThreadPool(ThreadPool<T> &&) : m_size(2) {}

template <typename T> auto ThreadPool<T>::push(const T &t_item) -> void {
  std::unique_lock<std::mutex> lock(m_mutex);
  m_cond.wait(lock, [this]() { return m_queue.size() < m_size; });

  m_queue.push(t_item);
  lock.unlock();
  m_cond.notify_one();
}

template <typename T> auto ThreadPool<T>::pop() -> T {
  std::unique_lock<std::mutex> lock(m_mutex);
  m_cond.wait(lock, [this]() { return !m_queue.empty(); });

  const T item = m_queue.front();
  m_queue.pop();

  lock.unlock();
  m_cond.notify_all();

  return item;
}

template <typename T> auto ThreadPool<T>::size() -> std::size_t {
  std::lock_guard<std::mutex>lock(m_mutex);
  return m_size;
}

template <typename T> auto ThreadPool<T>::front() -> T {
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_queue.front();
}
