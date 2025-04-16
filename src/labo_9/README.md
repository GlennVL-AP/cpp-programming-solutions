# Labo 9 Exercises

1. In labo 6 hebben we een `Vector3D` klasse gemaakt met als type van de elementen `double`. Breid deze klasse uit met een template parameter voor het element type. Zorg dat enkel types die getallen voorstellen toegelaten zijn (`int`, `double`, ...). Vergeet ook geen unittests te schrijven!
2. Maak een `Matrix` klasse voor een `MxN` matrix met drie template argumenten. Het type voor de elementen (numeriek), en NTTP voor `M` en `N`. Voorzie een aantal nuttige operaties zoals `operator[]`, optellen van matrices, .... Voeg een member functie `row(row_index)` en `column(col_index)` om een kopie van de n-de rij of kolom terug te krijgen in een `std::array`. Maak het ook mogelijk om met andere matrices te vermenigvuldigen waar dit mogelijk is (een `MxN` matrix kan vermenigvuldigd worden met een `NxP` matrix en geeft als resultaat een `MxP` matrix). Maak een `transpose` functie. Voeg ook een functie toe om de determinant te berekenen, die enkel beschikbaar is voor vierkante matrices. Vergeet ook geen unittests te schrijven!
3. Maak voor elk van de volgende dieren een klasse en zorg dat je aan de constructor een naam kan meegeven: `Cat`, `Dog`, `GoldFish`, `Canary`. Voeg aan elk dier een `talk()` member functie toe waarin je iets op het scherm print. Aan `Cat` en `Dog` voeg je ook een member functie `walk()` toe. Aan `GoldFish` een member functie `swim()`. En aan `Canary` een member functie `fly()`. Maak ook 4 functies `talk(animal)`, `walk(animal)`, `swim(animal)` en `fly(animal)` in de globale scope die een template argument krijgen en de betreffende member functie van `animal` aanroepen. Maak gebruik van concepten om enkel argumenten te accepteren die de juiste functie hebben.

   ```c++
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
   ```
