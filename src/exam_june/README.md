# Opdrachten examen Juni

## Opdracht 1

Schrijf een programma dat drie gehele getallen inleest van de console input en het kleinste en grootste van de drie weergeeft.

## Opdracht 2

Maak een programma dat een lijst van studenten (naam + score) inleest en ze sorteert op dalende score. Je mag zelf kiezen of je input vraagt of hardcoded data gebruikt.

```c++
struct Student
{
    std::string name;
    int score;
};
```

Vereisten

* Sorteer met `std::ranges::sort` en een lambda
* Druk de gesorteerde lijst af met `std::print`

## Opdracht 3

Schrijf een klasse `Statistics` in de statistics module die een lijst van integers bijhoudt en volgende functies aanbiedt:

* `void add(int number)`: voegt een getal toe aan de lijst
* `int sum() const`: berekent de som van alle getallen in de lijst
* `double average() const`: berekent het gemiddelde van alle getallen in de lijst
* `int max() const`: geeft het grootste getal in de lijst

Voeg unit tests toe aan het `statistics.test.cpp` bestand in de tests map met `Catch2` voor elke functie. Test minstens:

* Het gedrag van een lege lijst
* Het gedrag van een lijst met meerdere elementen

Vereisten

* De `sum`, `average` en `max` functies hebben als preconditie dat de lijst niet leeg is
* Maak gebruik van bestaande algoritmes, schrijf zelf geen lussen
