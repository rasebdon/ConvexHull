#include <utest.h>
#include <geometry.h>

UTEST_MAIN();

UTEST(foo, bar) {
  Vector2 a = Vector2(1, 2);
  Vector2 b = Vector2(1, 2);
  ASSERT_TRUE(a.x == b.x);
}