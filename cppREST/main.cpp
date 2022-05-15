#include "iostream"
#include "vector"
#include "utility"

#include "string"
#include "crow.h"
#include "cpp_redis/core/client.hpp"

int main()
{
    crow::SimpleApp app;

    cpp_redis::client redisClient;
    redisClient.connect();

    CROW_ROUTE(app, "/health")([](){
        return "Working fine...";
    });

    CROW_ROUTE(app, "/api/blogs").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid body");
        std::string title, content;
        try {
            title = body["title"].s();
            content = body["content"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try {
            redisClient.lpush("titles", { title });
            redisClient.lpush("contents", { content });
            redisClient.sync_commit();
        } catch (const std::runtime_error &ex) {
            return crow::response(500, "Internal Server Error");
        }

        return crow::response(200, "Blog added");
    });

    CROW_ROUTE(app, "/api/blogs")
    ([&]()
    {
        auto r1 = redisClient.lrange("titles", 0, -1);
        auto r2 = redisClient.lrange("contents", 0, -1);
        redisClient.sync_commit();
        r1.wait();
        r2.wait();
        auto r = r1.get().as_array();
        std::vector<std::string> titles(r.size()), contents(r.size());
        std::transform(r.begin(), r.end(), titles.begin(), [](const cpp_redis::reply &rep) { return rep.as_string(); });

        auto rC = r2.get().as_array();
        std::transform(rC.begin(), rC.end(), contents.begin(), [](const cpp_redis::reply &rep) { return rep.as_string(); });

        std::vector<crow::json::wvalue> blogs;
        for (int i = 0; i < titles.size(); i++)
        {
            blogs.push_back(crow::json::wvalue{
                {"title", titles[i]},
                {"content", contents[i]}
            });
        }

        return crow::json::wvalue{{"data", blogs}};
    });

    app.port(3000).multithreaded().run();
}