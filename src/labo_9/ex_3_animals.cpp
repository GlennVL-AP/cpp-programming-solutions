export module animals;

import std;

export class Cat
{
public:
    explicit Cat(std::string name) : name_{std::move(name)} {}

    void talk() const { std::println("Cat({})::talk", name_); }
    void walk() const { std::println("Cat({})::walk", name_); }

private:
    std::string name_;
};

export class Dog
{
public:
    explicit Dog(std::string name) : name_{std::move(name)} {}

    void talk() const { std::println("Dog({})::talk", name_); }
    void walk() const { std::println("Dog({})::walk", name_); }

private:
    std::string name_;
};

export class GoldFish
{
public:
    explicit GoldFish(std::string name) : name_{std::move(name)} {}

    void talk() const { std::println("GoldFish({})::talk", name_); }
    void swim() const { std::println("GoldFish({})::swim", name_); }

private:
    std::string name_;
};

export class Canary
{
public:
    explicit Canary(std::string name) : name_{std::move(name)} {}

    void talk() const { std::println("Canary({})::talk", name_); }
    void fly() const { std::println("Canary({})::fly", name_); }

private:
    std::string name_;
};

template <typename T>
concept Talker = requires(T const& animal)
{
    { animal.talk() };
};

template <typename T>
concept Walker = requires(T const& animal)
{
    { animal.walk() };
};

template <typename T>
concept Swimmer = requires(T const& animal)
{
    { animal.swim() };
};

template <typename T>
concept Flyer = requires(T const& animal)
{
    { animal.fly() };
};

export void talk(Talker auto const& animal)
{
    animal.talk();
}

export void walk(Walker auto const& animal)
{
    animal.walk();
}

export void swim(Swimmer auto const& fish)
{
    fish.swim();
}

export void fly(Flyer auto const& bird)
{
    bird.fly();
}
