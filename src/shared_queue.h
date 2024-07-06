#ifndef SHARED_QUEUE_H
#define SHARED_QUEUE_H

#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>

// To be raised when next is called while the SharedQueue is empty and closed.
class QueueClosedAndEmptyException : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Queue is closed and empty";
    }
};

// This class is inspired by the in-class Udacity MessageQueue and also by this
// StackOverflow post: https://stackoverflow.com/questions/68055538/how-to-share-mutex-condition-variable-and-queue-between-two-classes-c
template <class T>
class SharedQueue
{
public:
    // Pushes an element to the back of the queue.
    void push(T &&elem)
    {
        std::lock_guard<std::mutex> guard(_mutex);
        std::cout << "Received an element" << "\n";

        _queue.push_back(std::move(elem));
        std::cout << "Queue size: " << _queue.size() << "\n";
        _cond.notify_one();
    }

    // Gets and pops an element from the front of the queue.
    T next()
    {
        std::unique_lock<std::mutex> uLock(_mutex);
        _cond.wait(uLock, [this]
                   { return !_queue.empty() || _closed; });

        if (_queue.empty())
        {
            std::cout << "Queue is empty and closed." << "\n";
            throw QueueClosedAndEmptyException();
        }

        std::cout << "Grabbing an element" << "\n";

        T elem = std::move(_queue.front());
        _queue.pop_front();
        std::cout << "Queue size: " << _queue.size() << "\n";

        return elem;
    }

    // Closes the queue, which signals the queue to raise the next time it
    // becomes empty.
    void close()
    {
        std::lock_guard<std::mutex> guard(_mutex);
        _closed = true;
        std::cout << "Closing queue\n";
        std::cout << "Queue size: " << _queue.size() << "\n";
        _cond.notify_all();
    }

private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _queue;
    bool _closed{false};
};

#endif
