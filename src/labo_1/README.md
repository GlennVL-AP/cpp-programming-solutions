# Labo 1 Exercises

## Exercise 1

1. Clone <https://gitlab.apstudent.be/cpp-programming/devcontainers-labo-1.git>
2. Open `exercise_1` with `vscode` or `clion`
3. Start devcontainer
4. Try compiling and running the two examples

```c++
// main.cpp before C++20

#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
}
```

```c++
// main.cpp in C++23

import std;

int main()
{
    std::println("Hello, world!");
}
```

## Exercise 2

1. Clone <https://gitlab.apstudent.be/cpp-programming/devcontainers-labo-1.git>
2. Open `exercise_2` with `vscode` or `clion`
3. Start devcontainer
4. Try configuring and building the project
5. Try running the project

```c++
// helloworld.cpp

export module helloworld;

import std;

export void hello()
{
    std::println("Hello, world!");
}
```

```c++
// main.cpp

import helloworld;

int main()
{
    hello();
}
```

## Exercise 3

1. Clone <https://gitlab.apstudent.be/cpp-programming/devcontainers-labo-1.git>
2. Open exercise_3 with vscode or clion
3. Try configuring and building the project
4. Run clang-format in helloworld.cpp
5. Solve the clang-tidy error in the Hello function
6. Add `// NOLINT(bugprone-exception-escape)` to the `main` function (this is a violation we can't fix yet)
