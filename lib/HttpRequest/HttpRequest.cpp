
#include <string>
#include <iostream>

#include "lib/HTTPRequest.hpp"
#include "lib/json.hpp"

using namespace std;

void SendRequest(string url, string body)
{
    try
    {
        http::Request request{url};
        const auto response = request.send("POST", body, {{"Content-Type", "application/json"}});
        // std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
    }
    catch (const std::exception &e)
    {
        // std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}