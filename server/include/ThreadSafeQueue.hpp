/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** ThreadSafeQueue
*/

#ifndef RTYPE_THREADSAFEQUEUE_HPP
#define RTYPE_THREADSAFEQUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include "network/datagram/Datagram.hpp"
#include "RtypeDatagram.hpp"

namespace rtype {
    namespace network {
        /*!
         * @class ThreadSafeQueue
         * @brief Templated Class that encapsulate a std::deque. Thread safe
         */
        template <typename T>
        class ThreadSafeQueue {
        public:
            /*!
             * Constructor of the ThreadSafeQueue class
             */
            explicit ThreadSafeQueue();
            /*!
             * Destructor of the ThreadSafeQueue class
             */
            ~ThreadSafeQueue() = default;
            /*!
             * return the first templated element of the queue
             * @return a reference to a Templated object
             */
            const T &front();
            /*!
             * pop the first element of the queue
             */
            void pop();
            /*!
             * add a templated element to the end of the queue
             * @param toPush the element to add
             */
            void push_back(const T &toPush);
            /*!
             * return the number element in the queue
             * @return a integer
             */
            int size();
            /*!
             * return true if the queue is empty, otherwise false
             * @return a boolean
             */
            bool isEmpty();
        private:
            std::deque<T> _queue; /*!< queue of templated object */
            std::condition_variable _condition; /*!< condition variable to handle thread */
            std::mutex _mutex; /*!< mutex to lock or unlock queue */
        };
    }
}

#endif