import std;
import animals;

namespace {

void speak(Animal const& animal)
{
    animal.speak();
}

std::vector<std::unique_ptr<Animal>> read_animals()
{
    std::vector<std::unique_ptr<Animal>> animals{};

    std::println("Enter some animals to create (stop to end).");
    for (std::string type{}; (std::cin >> type) && (type != "stop");)
    {
        if (type == "dog")
        {
            animals.push_back(std::make_unique<Dog>());
        }
        else if (type == "cat")
        {
            animals.push_back(std::make_unique<Cat>());
        }
        else if (type == "bear")
        {
            animals.push_back(std::make_unique<Bear>());
        }
        else if (type == "hamster")
        {
            animals.push_back(std::make_unique<Hamster>());
        }
        else
        {
            std::println("{} is not a valid animal!", type);
        }
    }

    return animals;
}

} // namespace

int main()
try
{
    for (auto const& animal : read_animals())
    {
        speak(*animal);
    }
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
