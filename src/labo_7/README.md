# Labo 7 Exercises

1. Herschrijf de `contains_number` functie in het onderstaande code-fragment aan de hand van `std::ranges::any_of`.

   ```c++
   import std;

   bool contains_number(std::vector<int> const& numbers, int value)
   {
       bool found = false;

       for (auto const& number : numbers)
       {
           if (number == value)
           {
               found = true;
               break;
           }
       }

       return found;
   }

   int main()
   {
       std::vector<int> numbers{1, 2, 1, 3, 1, 4, 1, 5 };

       if (contains_number(numbers, 4))
       {
           std::println("Gevonden!");
       }
       else
       {
           std::println("Niet gevonden!");
       }
   }
   ```

2. Schrijf een lambda om het n-de fibonacci getal te berekenen. Om dit te optimaliseren voeg je een cache toe. Voor de cache kan je een `std::unordered_map` gebruiken. Als het getal al in de cache zit, gebruik je die waarde. Indien niet moet je de waarde uitrekenen en in de cache stoppen alvorens ze te returnen.
3. Vraag aan de gebruiker om een aantal getallen in te geven. Voeg ze toe aan een lijst. Filter hem vervolgens zodat enkel nog getallen die deelbaar zijn door 3 overblijven. Bereken van elk van deze getallen de tweede macht. Sorteer de getallen. Doe dit alles zonder de originele lijst te wijzigen. Print het resultaat op het scherm.
4. Genereer een lijst van de getallen van 1 tot en met 75. We zijn niet geinteresseerd in de eerste 25 getallen. Vervang de overige getallen door het n-de fibonacci getal. (`25 -> fibonacci(25)`, ..., `75 -> fibonacci(75)`). Sla de resulterende lijst op in een `std::vector`. Print de vector op het scherm.
5. Vraag een reeks van getallen aan de gebruiker. Bereken het gemiddelde door gebruik te maken van `std::accumulate` en `std::distance`.
