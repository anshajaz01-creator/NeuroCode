#pragma once
// Fixed-size worker pool. Jobs run here, never on the HTTP threads.

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace nc {

class ThreadPool {
public:
    explicit ThreadPool(std::size_t workers) {
        if (workers == 0) workers = 1;
        threads_.reserve(workers);
        for (std::size_t i = 0; i < workers; ++i) {
            threads_.emplace_back([this] { workerLoop(); });
        }
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // Stops accepting work, lets running tasks finish, drops tasks still queued.
    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lk(mu_);
            stop_ = true;
        }
        cv_.notify_all();
        for (auto& t : threads_) t.join();
    }

    void submit(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lk(mu_);
            if (stop_) return;
            tasks_.push(std::move(task));
        }
        cv_.notify_one();
    }

private:
    void workerLoop() {
        for (;;) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lk(mu_);
                cv_.wait(lk, [this] { return stop_ || !tasks_.empty(); });
                if (stop_) return;
                task = std::move(tasks_.front());
                tasks_.pop();
            }
            task();
        }
    }

    std::mutex mu_;
    std::condition_variable cv_;
    std::queue<std::function<void()>> tasks_;
    std::vector<std::thread> threads_;
    bool stop_ = false;
};

}  // namespace nc
