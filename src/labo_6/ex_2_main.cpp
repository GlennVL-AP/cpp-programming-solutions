import std;
import logger;
import database;

namespace {

class Application
{
public:
    Application(Logger& logger, Database& database) : logger_{logger}, database_{database} {}

    void run()
    {
        database_.get().connect();
        logger_.get().log("connected!");
        database_.get().query("SELECT something FROM somehwere;");
        logger_.get().log("query executed!");
    }

private:
    std::reference_wrapper<Logger> logger_;
    std::reference_wrapper<Database> database_;
};

} // namespace

int main()
try
{
    std::unique_ptr<Database> database{};
    std::println("Which database do you want to create? (mysql or postgresql) ");
    if (std::string database_type{}; (std::cin >> database_type) && (database_type == "postgresql"))
    {
        database = std::make_unique<PostgreSqlDatabase>();
    }
    else
    {
        database = std::make_unique<MySqlDatabase>();
    }

    ConsoleLogger logger{};
    Application app{logger, *database};
    app.run();
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
