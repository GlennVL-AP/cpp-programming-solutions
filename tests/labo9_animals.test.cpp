#include <catch.hpp>

import animals;

TEST_CASE("test animal concepts", "[labo_9][animals]")
{
    Cat const cat{"cat"};
    Dog const dog{"dog"};
    GoldFish const goldfish{"goldfish"};
    Canary const canary{"canary"};

    SECTION("talk")
    {
        talk(cat);
        talk(dog);
        talk(goldfish);
        talk(canary);
    }

    SECTION("walk")
    {
        walk(cat);
        walk(dog);
    }

    SECTION("swim")
    {
        swim(goldfish);
    }

    SECTION("fly")
    {
        fly(canary);
    }
}
