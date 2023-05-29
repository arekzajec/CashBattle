#include "Timer.hpp"

#include <iostream>

void Timer::thread_fcn() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        mut.lock();
        if (running) {
            if (sec_left > 0) 
                sec_left--;
        }
        mut.unlock();
    }
}

void Timer::run() {
    mut.lock();
    running = true;
    mut.unlock();
    if (!inner_thread) 
        inner_thread = new std::thread(&Timer::thread_fcn,this);
}
