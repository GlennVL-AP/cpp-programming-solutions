export module logger;

import std;

export class Logger
{
public:
    Logger() = default;
    virtual ~Logger() = default;

    Logger(Logger const&) = delete;
    Logger& operator=(Logger const&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    virtual void log(std::string msg) const = 0;
};

export class ConsoleLogger : public Logger
{
public:
    void log(std::string msg) const override { std::println("Log: {}", msg); }
};
