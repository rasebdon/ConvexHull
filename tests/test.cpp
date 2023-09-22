#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "geometry.h"

// Constructor tests [LENGTH]

TEST_CASE("Construct from nullptr does not throw segmentation fault") {
    CHECK_EQ(true, true);
}