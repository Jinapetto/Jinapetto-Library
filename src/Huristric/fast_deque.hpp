#pragma once
#include <bits/stdc++.h>
using namespace std;

// ランダムアクセス不要の高速 deque（リングバッファ実装）
//   - 容量は 2 冪、インデックスはビットマスクで包む（剰余なし）
//   - head/tail は生のカウンタ（マスクは buf アクセス時のみ）。size = tail - head
//     符号なし演算なのでカウンタが 32bit で一周しても正しく動く
//   - 要素は連続メモリ上。push/pop/front/back は分岐最小・全 inline
//   - 対応: push_back/front, emplace_back/front, pop_back/front, front, back,
//           size, empty, clear, reserve
//   ※ ランダムアクセス([], at, iterator)は非対応
template <class T>
struct fast_deque {
    T* buf;
    uint32_t cap, mask, head, tail;

    explicit fast_deque(uint32_t c = 16) {
        cap = 2;
        while (cap < c) cap <<= 1;
        mask = cap - 1;
        head = tail = 0;
        buf = (T*)::operator new(sizeof(T) * cap);
    }
    ~fast_deque() {
        clear();
        ::operator delete(buf);
    }
    fast_deque(const fast_deque&) = delete;
    fast_deque& operator=(const fast_deque&) = delete;
    fast_deque(fast_deque&& o) noexcept
        : buf(o.buf), cap(o.cap), mask(o.mask), head(o.head), tail(o.tail) {
        o.buf = nullptr; o.cap = o.mask = o.head = o.tail = 0;
    }
    fast_deque& operator=(fast_deque&& o) noexcept {
        if (this != &o) {
            clear(); ::operator delete(buf);
            buf = o.buf; cap = o.cap; mask = o.mask; head = o.head; tail = o.tail;
            o.buf = nullptr; o.cap = o.mask = o.head = o.tail = 0;
        }
        return *this;
    }

    inline uint32_t size()  const { return tail - head; }
    inline bool     empty() const { return head == tail; }

    inline T&       front()       { return buf[head & mask]; }
    inline const T& front() const { return buf[head & mask]; }
    inline T&       back()        { return buf[(tail - 1) & mask]; }
    inline const T& back()  const { return buf[(tail - 1) & mask]; }

    inline void push_back(const T& v) {
        if (__builtin_expect(tail - head == cap, 0)) grow();
        ::new (buf + (tail & mask)) T(v);
        tail++;
    }
    inline void push_front(const T& v) {
        if (__builtin_expect(tail - head == cap, 0)) grow();
        head--;
        ::new (buf + (head & mask)) T(v);
    }
    template <class... Args>
    inline void emplace_back(Args&&... args) {
        if (__builtin_expect(tail - head == cap, 0)) grow();
        ::new (buf + (tail & mask)) T(forward<Args>(args)...);
        tail++;
    }
    template <class... Args>
    inline void emplace_front(Args&&... args) {
        if (__builtin_expect(tail - head == cap, 0)) grow();
        head--;
        ::new (buf + (head & mask)) T(forward<Args>(args)...);
    }
    inline void pop_front() {
        buf[head & mask].~T();
        head++;
    }
    inline void pop_back() {
        tail--;
        buf[tail & mask].~T();
    }

    inline void clear() {
        if constexpr (!is_trivially_destructible<T>::value)
            for (uint32_t i = head; i != tail; i++) buf[i & mask].~T();
        head = tail = 0;
    }
    void reserve(uint32_t c) { while (cap < c) grow(); }

private:
    void grow() {
        uint32_t ncap = cap << 1;
        T* nbuf = (T*)::operator new(sizeof(T) * ncap);
        uint32_t n = tail - head, h = head & mask;
        if constexpr (is_trivially_copyable<T>::value) {
            uint32_t r = cap - h;
            if (n <= r) {
                memcpy(nbuf, buf + h, sizeof(T) * n);
            } else {
                memcpy(nbuf, buf + h, sizeof(T) * r);
                memcpy(nbuf + r, buf, sizeof(T) * (n - r));
            }
        } else {
            for (uint32_t i = 0; i < n; i++) {
                ::new (nbuf + i) T(move(buf[(h + i) & mask]));
                buf[(h + i) & mask].~T();
            }
        }
        ::operator delete(buf);
        buf = nbuf; cap = ncap; mask = ncap - 1;
        head = 0; tail = n;
    }
};
