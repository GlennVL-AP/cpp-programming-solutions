# Labo 3 Exercises

1. Het volgende programma heeft een functie die als input een temperatuur in graden celcius krijgt en de temperatuur in graden kelvin teruggeeft. De code zit vol met fouten. Zoek ze en los ze op.

   ```c++
   import std;

   double ctok(double c)      // converts celcius to kelvin
   {
       int k = c + 273.25;
       return int
   }

   int main()
   {
       double c = 0;          // declare input variable
       std::cin >> d;         // retrieve temperature to input variable
       double k = ctok("c");  // convert temperature
       std::Println("{}", k); // print out temperature
   }
   ```

2. Het absoluut nulpunt is `-273.15C`. Voeg hiervoor een preconditie toe in de `ctok()` functie uit de vorige oefening. Vergeet ook niet om exceptions op te vangen in de `main` functie.
3. Voeg aan de vorige oefening een functie toe voor het converteren van kelvin naar celcius.
4. Implementeer het gokspelletje `Bulls and Cows.`. Je maakt een vector met 4 getallen. De gebruiker moet proberen om al de getallen juist te raden, vraag steeds 4 getallen aan de gebruiker tot het gelukt is. Als bijvoorbeeld het te raden getal `1234` is en de gebruiker voert `1359` in, dan print je als output `1 Bull, 1 Cow`. Omdat hij 1 digit juist had en op de juiste plaats (`Bull`) en 1 digit juist had maar op de foute plaats (`Cow`). Het spelletje eindigt als de gebruikt `4 Bull` heeft.
5. Schrijf een programma dat aan de gebruiker vraagt om een reeks woorden in te voeren. Geef als output hoevaak de gebruiker elk woord ingevoerd heeft. Je kan hiervoor gebruik maken van een `std::unordered_map`.
6. Kwadratische functies zijn van de vorm $`ax^2+bx+c=0`$. Om ze op te lossen gebruik je de formule $`x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}`$. Er is echter een probleem, als $`b^2-4ac`$ negatief is faalt de formule (dan zijn er geen nulpunten). Schrijf een functie die kwadratische functies kan oplossen. Vraag aan de gebruiker de waardes voor `a`, `b` en `c`. Print het resultaat op het scherm, informeer de gebruiker als er geen nulpunten zijn. Kan je ook een functie schrijven om te controleren of het resultaat correct is?
