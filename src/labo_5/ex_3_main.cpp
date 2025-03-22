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
    ConsoleLogger logger{};
    MySqlDatabase database{};
    Application app{logger, database};
    app.run();
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
