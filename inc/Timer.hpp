#ifndef TIMER_HPP
#define TIMER_HPP

#include <thread>
#include <chrono>
#include <mutex>

class Timer {
    int sec_upto;
    int sec_left;
    bool running;
    std::thread * inner_thread;
    std::mutex mut;
    void thread_fcn();
public:
    Timer(int s) : 
        sec_upto(s), 
        sec_left(s), 
        running(false), 
        inner_thread(nullptr) 
    {}
    void run();
    void stop() {mut.lock(); running = false; mut.unlock();}
    void reset() {mut.lock(); sec_left = sec_upto; mut.unlock();}
    int get_sec_left() const {return sec_left;}
    bool is_runnung() const {return running;}
};

#endif