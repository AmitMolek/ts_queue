# Thread-Safe Queue Adaptor
## An adaptor that provides a thread-safe FIFO behavior.

This is an adaptor. It holds another container, and provides a wrapper interface to that container.

```
template <typename T, typename Container = std::queue<T>>
```

The seconds template parameter defines the type of the underlying container. It defaults to std::queue, but it can be any type that supports `front`, `back`, `empty`, `size`, `push`, `emplace_back`, and `pop`.

## Example
```cpp
am::tsq::ts_queue<int> q; // Use std::queue
am::tsq::ts_queue<int, Container> q; // Use Container
```