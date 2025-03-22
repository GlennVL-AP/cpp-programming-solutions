export module animals;

import std;

export class Animal
{
public:
    explicit Animal(std::string name) : name_{std::move(name)} {}

    virtual ~Animal() = default;

    Animal(Animal const&) = delete;
    Animal& operator=(Animal const&) = delete;
    Animal(Animal&&) = delete;
    Animal& operator=(Animal&&) = delete;

    void speak() const { std::println("{} says {}.", name_, speak_impl()); }

private:
    std::string name_;

    [[nodiscard]] virtual std::string speak_impl() const = 0;
};

export class Dog : public Animal
{
public:
    Dog() : Animal("dog") {}

private:
    [[nodiscard]] std::string speak_impl() const override { return "bark"; }
};

export class Cat : public Animal
{
public:
    Cat() : Animal("cat") {}

private:
    [[nodiscard]] std::string speak_impl() const override { return "meow"; }
};

export class Bear : public Animal
{
public:
    Bear() : Animal("bear") {}

private:
    [[nodiscard]] std::string speak_impl() const override { return "roar"; }
};

export class Hamster : public Animal
{
public:
    Hamster() : Animal("hamster") {}

private:
    [[nodiscard]] std::string speak_impl() const override { return "squeak"; }
};
