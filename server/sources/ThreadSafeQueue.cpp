/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ThreadSafeQueue.cpp
*/

#include "ThreadSafeQueue.hpp"

template <typename T>
rtype::network::ThreadSafeQueue<T>::ThreadSafeQueue()
{
}

template <typename T>
int rtype::network::ThreadSafeQueue<T>::size()
{
    std::unique_lock<std::mutex> mlock(_mutex);
    int queueSize = _queue.size();

    mlock.unlock();
    return queueSize;
}

template <typename T>
const T &rtype::network::ThreadSafeQueue<T>::front()
{
    std::unique_lock<std::mutex> mlock(_mutex);

    while (_queue.empty()) {
        _condition.wait(mlock);
    }
    return _queue.front();
}

template <typename T>
void rtype::network::ThreadSafeQueue<T>::push_back(const T &toPush)
{
    std::unique_lock<std::mutex> mlock(_mutex);

    _queue.push_back(toPush);
    mlock.unlock();
    _condition.notify_one();
}

template <typename T> bool rtype::network::ThreadSafeQueue<T>::isEmpty()
{
    auto queueSize = size();

    if (queueSize == 0)
        return true;
    return false;
}

template <typename T>
void rtype::network::ThreadSafeQueue<T>::pop()
{
    std::unique_lock<std::mutex> mlock(_mutex);

    while (_queue.empty()) {
        _condition.wait(mlock);
    }
    _queue.pop_front();
}

template class rtype::network::ThreadSafeQueue<rtype::network::Datagram>;
template class rtype::network::ThreadSafeQueue<rtype::network::RtypeDatagram>;