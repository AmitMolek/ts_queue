#ifndef AM_ts_queue_HPP
#define AM_ts_queue_HPP

#include <queue>
#include <mutex>

namespace am {
    namespace tsq {

        // Shortcuts
        #define LOCK_GUARD(m) std::lock_guard<std::mutex> lg(m);
        #define LOCK_GUARDS(m1, m2) std::lock_guard<std::mutex> lg1(m1); \
                                   std::lock_guard<std::mutex> lg2(m2);

        /**
         * @brief A container giving thread-safe FIFO behavior
         * 
         * @tparam T Type of element.
         * @tparam Container Type of underlying container, defaults to std::queue<T>.
         * 
         * This is an adaptor. It holds another container, and provides 
         * a wrapper interface to that container.
         * 
         * The seconds template parameter defines the type of the underlying 
         * container. It defaults to std::queue, but it can be any type
         * that supports @c front, @c back, @c empty, @c size, @c push,
         * @c emplace_back, and @c pop
         */
        template <typename T, typename Container = std::queue<T>>
        class ts_queue {
            public:
                using value_type = typename Container::value_type;
                using reference = typename Container::reference;
                using const_reference = typename Container::const_reference;
                using size_type = typename Container::size_type;
                using container_type = typename Container::container_type;

            private:
                Container c;
                mutable std::mutex lock;

            public:
                ts_queue() : c() {}

                explicit ts_queue(const Container& oc) : c(oc) {}

                explicit ts_queue(Container&& oc) : c(std::move(oc)){}

                ts_queue(const ts_queue& q) : c(q.c) {}

                ts_queue(ts_queue&& q) : c(std::move(q.c)) {}

                /// Returns true if the queue is empty.
                bool empty() const { LOCK_GUARD(lock); return c.empty(); }

                /// Returns the number of elements in the queue.
                size_type size() const { LOCK_GUARD(lock); return c.size(); }

                /// Returns a read/write reference to the data at the front of the queue.
                reference front() { LOCK_GUARD(lock); return c.front(); }

                /// Returns a read-only reference to the data at the front of the queue.
                const_reference front() const { LOCK_GUARD(lock); return c.front(); }

                /// Returns a read/write reference to the data at the back of the queue.
                reference back() { LOCK_GUARD(lock); return c.back(); }

                /// Returns a read-only reference to the data at the back of the queue.
                const_reference back() const { LOCK_GUARD(lock); return c.back(); }

                /**
                 * @brief Add data to the end of the queue.
                 * 
                 * @param x Data to be added
                 */
                void push(const value_type& x) { LOCK_GUARD(lock); c.push(x); }

                void push(value_type&& x) { LOCK_GUARD(lock); c.push(std::move(x)); }

                /**
                 * @brief Construct an element directly into the queue
                 * with no use of a temporary.
                 * 
                 * @tparam Args Types of arguments.
                 * @param args Arguments to be passed to the constructor of the element.
                 */
                template <typename... Args>
                void emplace(Args&&... args) {
                    LOCK_GUARD(lock);
                    c.emplace_back(std::forward<Args>(args)...);
                }

                /**
                 * @brief Removes first element.
                 * 
                 * No data is returned, if you need the first element's 
                 * data, it should be retrieved before calling pop()
                 */
                void pop() { LOCK_GUARD(lock); c.pop(); }
        };

        /**
         * @brief Queue equality comparison.
         * 
         * @tparam T Type of element
         * @tparam Container Type of underlying container.
         * @param x A queue
         * @param y A queue of the same type as @a x
         * @return true iff the size and elements of the queues are equal.
         */
        template <typename T, typename Container>
        inline bool operator==(const ts_queue<T, Container>& x, const ts_queue<T, Container>& y){
            LOCK_GUARDS(x.lock, y.lock);
            return x.c == y.c;
        }

        /**
         * @brief Queue ordering relation.
         * 
         * @tparam T Type of element
         * @tparam Container Type of underlying container.
         * @param x A queue
         * @param y A queue of the same type as @a x
         * @return true iff @a x is lexicographically less than @a y
         */
        template <typename T, typename Container>
        inline bool operator<(const ts_queue<T, Container>& x, const ts_queue<T, Container>& y){
            LOCK_GUARDS(x.lock, y.lock);
            return x.c < y.c;
        }

        /// Based on operator==
        template <typename T, typename Container>
        inline bool operator!=(const ts_queue<T, Container>& x, const ts_queue<T, Container>& y){
            LOCK_GUARDS(x.lock, y.lock);
            return !(x == y);
        }

        /// Based on operator<
        template <typename T, typename Container>
        inline bool operator>(const ts_queue<T, Container>& x, const ts_queue<T, Container>& y){
            LOCK_GUARDS(x.lock, y.lock);
            return y < x;
        }

        /// Based on operator<
        template <typename T, typename Container>
        inline bool operator<=(const ts_queue<T, Container>& x, const ts_queue<T, Container>& y){
            LOCK_GUARDS(x.lock, y.lock);
            return !(y < x);
        }

        /// Based on operator<
        template <typename T, typename Container>
        inline bool operator>=(const ts_queue<T, Container>& x, const ts_queue<T, Container>& y){
            LOCK_GUARDS(x.lock, y.lock);
            return !(x < y);
        }

    };

};

#endif