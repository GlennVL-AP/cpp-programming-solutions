export module database;

import std;

export class Database
{
public:
    Database() = default;
    virtual ~Database() = default;

    Database(Database const&) = delete;
    Database& operator=(Database const&) = delete;
    Database(Database&&) = delete;
    Database& operator=(Database&&) = delete;

    virtual void connect() = 0;
    virtual void query(std::string query) = 0;
};

export class MySqlDatabase : public Database
{
public:
    void connect() override { std::println("Connecting to MySQL database!"); }
    void query(std::string query) override { std::println("Executing MySQL query {}", query); }
};
