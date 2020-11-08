#include "catch2/catch.hpp"
#include "ts_queue.hpp"

namespace tsq = am::tsq;

TEST_CASE("ts_queue: empty", ".empty()"){
    tsq::ts_queue<int> q;
    tsq::ts_queue<int>::size_type iterations = 20;

    REQUIRE(q.empty() == true);

    for (tsq::ts_queue<int>::size_type i = 0; i < iterations; i++){
        q.push(1);
    }
    REQUIRE(q.empty() == false);
    for (tsq::ts_queue<int>::size_type i = 0; i < iterations; i++){
        q.pop();
    }
    REQUIRE(q.empty() == true);
}

TEST_CASE("ts_queue: size", ".size()"){
    tsq::ts_queue<int> q;
    tsq::ts_queue<int>::size_type iterations = 20;

    REQUIRE(q.size() == 0);

    for (tsq::ts_queue<int>::size_type i = 0; i < iterations; i++){
        q.push(1);
        REQUIRE(q.size() == (i+1));
    }
    REQUIRE(q.size() == iterations);
    for (tsq::ts_queue<int>::size_type i = 0; i < iterations; i++){
        q.pop();
        REQUIRE(q.size() == (iterations-i-1));
    }
}