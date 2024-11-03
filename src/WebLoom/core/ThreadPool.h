//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef CORE_THREADPOOL_H_
#define CORE_THREADPOOL_H_
#include <condition_variable>   // NOLINT(build/c++11)
#include <functional>
#include <future>               // NOLINT(build/c++11)
#include <memory>
#include <mutex>                // NOLINT(build/c++11)
#include <queue>
#include <thread>               // NOLINT(build/c++11)
#include <utility>
#include <vector>

namespace webloom::core {

class ThreadPool {
 public:
    // Constructor to create and launch threads
    explicit ThreadPool(size_t threads) : stop_(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers_.emplace_back([this] {
                while (true) {
                    std::function<void()> task;

                    // Lock and wait for tasks
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex_);
                        this->condition_.wait(lock, [this] {
                            return this->stop_ || !this->tasks_.empty ();
                            });
                        if (this->stop_ && this->tasks_.empty()) {
                            return;
                        }
                        task = std::move(this->tasks_.front());
                        this->tasks_.pop();
                    }
                    // Execute the task
                    task();
                }
                });
        }
    }

    // Enqueue a task with function pointer
    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) ->
        std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::invoke_result<F, Args...>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>> (
            std::bind(std::forward<F> (f), std::forward<Args> (args)...));

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);

            // Don't allow enqueueing after stopping the pool
            if (stop_) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            tasks_.emplace([task]() { (*task)(); });
        }
        condition_.notify_one();
        return res;
    }

    // Destructor to join all threads
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (std::thread& worker : workers_) {
            worker.join();
        }
    }

 private:
    // Vector of worker threads
    std::vector<std::thread> workers_;

    // Task queue
    std::queue<std::function<void()>> tasks_;

    // Synchronization primitives
    std::mutex queue_mutex_;
    std::condition_variable condition_;

    // Flag to stop the thread pool
    bool stop_;
};

#endif  // CORE_THREADPOOL_H_

}   // namespace webloom::core
