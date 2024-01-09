// #include <iostream>

// #include <gtest/gtest.h>

// #include "lib/HTTPRequest.hpp"
// #include "lib/nlohmann/json.hpp"

// using json = nlohmann::json;

// TEST(Basic, GTest_test)
// {
//   EXPECT_EQ(3, 3);
// }

// TEST(Http, GTest_test)
// {
//   http::Request request{"http://httpbin.org/get?test=test"};

//   const auto response = request.send("GET");
//   json jsn = json::parse(std::string{response.body.begin(), response.body.end()});

//   EXPECT_EQ(jsn["args"]["test"], "test");
// }