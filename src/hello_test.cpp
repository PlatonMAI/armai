#include "hello.hpp"

#include <userver/utest/utest.hpp>

UTEST(SayHelloTo, Basic) {
  EXPECT_EQ(armai::SayHelloTo("Developer"), "Hello, Developer!\n");
  EXPECT_EQ(armai::SayHelloTo({}), "Hello, unknown user!\n");
}
