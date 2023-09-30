#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
struct ThreadPool {
public:
    ThreadPool(std::size_t t_size);
    ThreadPool(const ThreadPool<T>&);
    ThreadPool(ThreadPool<T>&&);

    ~ThreadPool() = default;

    auto push(const T& t_item) -> void;
    auto pop() -> T;
    auto size() -> std::size_t;
    auto front() -> T;


private:
    std::size_t m_size;
    std::mutex m_mutex;
    std::queue<T> m_queue;
    std::condition_variable m_cond;
};

#endif // __THREADPOOL_H__