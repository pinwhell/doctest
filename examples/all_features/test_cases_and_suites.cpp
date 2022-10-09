#include <doctest/doctest.h>

#include "header.h"

static int doStuff() {
    int a = 5;
    a += 2;
    // asserts and other doctest functionality can be used in user code if checked for a testing context
    // AND they can also be used without such checks - see "asserts_used_outside_of_tests.cpp"
    if(doctest::is_running_in_test)
        CHECK(a == 7);

    return a;
}

TEST_CASE("an empty test that will succeed - not part of a test suite") {}

TEST_CASE("should fail because of an exception") {
    doStuff();

    throw_if(true, 0);
}

TEST_SUITE("scoped test suite") {
    TEST_CASE("part of scoped") {
        FAIL("");
    }

    TEST_CASE("part of scoped 2") {
        FAIL("");
    }
}

TEST_SUITE_BEGIN("some TS"); // begin "some TS"

TEST_CASE("part of some TS") {
    FAIL("");
}

TEST_SUITE_END(); // ends "some TS"

TEST_CASE_FIXTURE(SomeFixture, "fixtured test - not part of a test suite") {
    data /= 2;
    CHECK(data == 85);
}

DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
DOCTEST_CLANG_SUPPRESS_WARNING_PUSH
DOCTEST_CLANG_SUPPRESS_WARNING("-Wreserved-id-macro")
DOCTEST_CLANG_SUPPRESS_WARNING("-Wunused-macros")
#define __mulodi4(a, b, c) a * b
DOCTEST_CLANG_SUPPRESS_WARNING_POP
#include <chrono>
#include <thread>
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

TEST_CASE("normal test in a test suite from a decorator" * doctest::test_suite("ts1") *
          doctest::timeout(0.000001)) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));
    MESSAGE("failing because of the timeout decorator!");
}

TEST_CASE("another normal test in a test suite from a decorator" * doctest::test_suite("ts1") *
    doctest::timeout(10)) {
    CHECK(42 == 42);
}

static bool shouldSkip() { return false; }

TEST_SUITE("skipped test cases" * doctest::skip()) {
    TEST_CASE("unskipped" * doctest::skip(shouldSkip()) *
              doctest::description("this test has overridden its skip decorator")) {
        FAIL("");
    }
    TEST_CASE("skipped - inherited from the test suite") { FAIL(""); }
}

TEST_SUITE("test suite with a description" * doctest::description("regarding failures")) {
    TEST_CASE("fails - and its allowed" * doctest::may_fail()) { FAIL(""); }
    TEST_CASE("doesn't fail which is fine" * doctest::may_fail()) {}

    TEST_CASE("fails as it should" * doctest::should_fail()) { FAIL(""); }
    TEST_CASE("doesn't fail but it should have" * doctest::should_fail()) {}

    TEST_CASE("fails 1 time as it should" * doctest::expected_failures(1)) { FAIL(""); }
    TEST_CASE("fails more times than it should" * doctest::expected_failures(1)) {
        FAIL_CHECK("");
        FAIL_CHECK("");
    }
}

TEST_CASE("should fail and no output" * doctest::should_fail() * doctest::no_breaks() * doctest::no_output()) { FAIL(""); }
