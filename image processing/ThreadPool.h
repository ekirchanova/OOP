#pragma once
#ifndef THREAD_POOL_H_7ea1ee6b_4f17_4c09_b76b_3d44e102400c
# define THREAD_POOL_H_7ea1ee6b_4f17_4c09_b76b_3d44e102400c
# include <vector>
# include <queue>
# include <memory>
# include <thread>
# include <mutex>
#include <condition_variable>
# include <future>
# include <atomic>
# include <functional>
#include <algorithm>
#include <atomic>
#include <future>
#include <queue>
namespace {
	const size_t DEFAULT_THREADS_COUNT = 8;
}

namespace thread_pool {
    class ThreadPool final {
        std::vector<std::thread> pool;
        size_t pool_size;
        size_t current_size;

        std::queue< std::function<void()> > tasks;
        std::size_t max_queue_size = 100000;

        std::mutex queue_mutex;
        std::condition_variable condition_producers;
        std::condition_variable condition_consumers;

        std::mutex in_flight_mutex;
        std::condition_variable in_flight_condition;
        std::atomic<std::size_t> in_flight;

        void emplace_back_worker(std::size_t worker_number);
    public:

        explicit ThreadPool(std::size_t threads
            = (std::max)(2u, std::thread::hardware_concurrency()));
        ThreadPool(ThreadPool&& cur)noexcept;
        ~ThreadPool();
       ThreadPool& operator =(ThreadPool&& cur)noexcept;
        template< class F, class... Args> decltype(auto) alloc(F&& f, Args&&... args);
        size_t max_size()const;
    };
    //-----------------------------------------------------------------------------------------------------------------

    inline ThreadPool::ThreadPool(std::size_t threads)
        : pool_size(threads)
        , in_flight(0)
    {
        for (std::size_t i = 0; i != threads; ++i)
            emplace_back_worker(i);
    }
    inline ThreadPool::~ThreadPool()
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        condition_consumers.notify_all();
        condition_producers.notify_all();
        pool_size = 0;
        condition_consumers.wait(lock, [this] { return this->pool.empty(); });

    }
    inline size_t ThreadPool::max_size() const {
        return pool_size;
    }

    template<class F, class... Args>
    decltype(auto) ThreadPool::alloc(F&& f, Args&&... args)
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

        std::future<return_type> res = task->get_future();

        std::unique_lock<std::mutex> lock(queue_mutex);
        if (tasks.size() >= max_queue_size)
            condition_producers.wait(lock,
                [this]
                {
                    return tasks.size() < max_queue_size;
                });

        tasks.emplace([task]() { (*task)(); });
        std::atomic_fetch_add_explicit(&in_flight,
            std::size_t(1),
            std::memory_order_relaxed);
        condition_consumers.notify_one();

        return res;


    };
    inline void ThreadPool::emplace_back_worker(std::size_t worker_number)
    {
        pool.emplace_back(
            [this, worker_number]
            {
                for (;;)
                {
                    std::function<void()> task;
                    bool notify;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition_consumers.wait(lock,
                            [this, worker_number] {
                                return !this->tasks.empty()
                                    || pool_size < worker_number + 1; });

                        if (this->tasks.empty()
                            || pool_size < worker_number + 1)
                        {
                            std::thread& last_thread = this->pool.back();
                            std::thread::id this_id = std::this_thread::get_id();
                            if (this_id == last_thread.get_id())
                            {
                                last_thread.detach();
                                this->pool.pop_back();
                                this->condition_consumers.notify_all();
                                return;
                            }
                            else
                                continue;
                        }
                        else if (!this->tasks.empty())
                        {
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                            notify = this->tasks.size() + 1 == max_queue_size
                                || this->tasks.empty();
                        }
                        else
                            continue;
                    }

                    if (notify)
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        condition_producers.notify_all();
                    }

                    task();
                }
            }
            );
    }
}
#endif

