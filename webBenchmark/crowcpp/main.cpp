#include "iostream"
#include "vector"
#include "utility"

#include "string"
#include "crow.h"
#include "cstdlib"
#include "time.h"

int main()
{
    crow::SimpleApp app;
    srand(time(0));
    app.loglevel(crow::LogLevel::Warning);

    CROW_ROUTE(app, "/")
    ([]()
     {
    const int cnt = 5000;
    int result = 0;
    for (int i = 0; i < cnt; i++)
    {
        result += rand() % 100;
    }
    return crow::json::wvalue{{"randomSum", result}}; });

    app.port(3000).multithreaded().run();
}