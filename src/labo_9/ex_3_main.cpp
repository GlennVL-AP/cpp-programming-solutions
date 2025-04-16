import animals;
import std;

int main()
try
{
    Cat const cat{"cat"};
    Dog const dog{"dog"};
    GoldFish const goldfish{"goldfish"};
    Canary const canary{"canary"};

    talk(cat);
    talk(dog);
    talk(goldfish);
    talk(canary);

    walk(cat);
    walk(dog);

    swim(goldfish);

    fly(canary);

    return 0;
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
