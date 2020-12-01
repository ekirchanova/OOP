#pragma once
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
namespace thread_pool {
    class ThreadPool {
    public:
        explicit ThreadPool(std::size_t threads
            = (std::max)(2u, std::thread::hardware_concurrency()));
        template<class F, class... Args>
        decltype(auto) alloc(F&& f, Args&&... args);
        ThreadPool(ThreadPool&& cur)noexcept;
        ThreadPool& operator =(ThreadPool&& cur)noexcept;
        size_t max_size()const;
        ~ThreadPool();
    private:
        std::vector< std::thread > workers;

        std::queue< std::function<void()> > tasks;

        //std::mutex queue_mutex;
       // std::condition_variable condition;
       // bool stop;
    };

    // the constructor just launches some amount of workers
    inline ThreadPool::ThreadPool(size_t threads):workers(std::vector<std::thread>(threads)),tasks(std::queue< std::function<void()> >())
    {
        ;

    }
    inline ThreadPool::ThreadPool(ThreadPool&& cur)noexcept:workers(std::move(cur.workers)),tasks(std::move(tasks))
    {
    }
    inline ThreadPool& ThreadPool:: operator =(ThreadPool&& cur)noexcept
    {
        workers = std::move(workers);
        tasks = std::move(cur.tasks);
        return *this;
    }
    // add new work item to the pool
    template<class F, class... Args>
    decltype(auto) ThreadPool::alloc(F&& f, Args&&... args)
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = /*std::make_shared< */std::packaged_task<return_type()> (
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

        std::future<return_type> res = task.get_future();
        //{
        //   // std::unique_lock<std::mutex> lock(queue_mutex);

        //    /*if (stop)
        //        throw std::runtime_error("alloc on stopped ThreadPool"*/

        //    //tasks.emplace([task]() { (*task)(); });
        //    for (size_t i = 0; i < workers.size(); ++i) {
        //        if (workers[i].joinable())
        //        {
        //           std::thread Thread(std::move(task));
        //            workers.emplace(workers.begin() + i, std::move(Thread));
        //          
        //            workers[i].join();
        //        }
        //    	
        //    }
        //}
       // condition.notify_one();
        std::thread sumThread(std::move(task));
        sumThread.join();
        return res;
    }
    inline size_t ThreadPool::max_size() const
    {
        return workers.size();
    }

    inline ThreadPool::~ThreadPool()
    {
        /* {
             std::unique_lock<std::mutex> lock(queue_mutex);
             stop = true;
         }
         condition.notify_all();*/
        /*for (std::thread& worker : workers)
            worker.join();*/
    }
}
#endif