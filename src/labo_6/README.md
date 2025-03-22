# Labo 6 Exercises

1. Werk het `Animal` voorbeeld verder uit. Implementeer `Dog`, `Cat`, `Bear` en `Hamster`. Vraag aan de gebruiker in een lusje welk dier hij wil maken tot de invoer `stop` is. Sla de dieren op in een `std::vector`. Maak een functie `animal_says()` die als argument een dier krijgt en voor dat dier dan de `speak()` method aanroept. Roep voor elk dier in de lijst de `animal_says()` functie op.
2. In `Labo 5 / Oefening 3` heb je de directe dependency van de `Application` klasse op de `MySqlDatabase` klasse opgelost. Voeg nu ook een `PostgreSQLDatabase` klasse toe. Vraag aan de gebruiker welke database hij wil aanmaken. Maak dan de applicatie aan met de gewenste soort database.
3. Maak een `Vector3D` klasse. Deze bevat 3 doubles `x`, `y` en `z`. Zorg ervoor dat het mogelijk is om:
   * Vectoren met elkaar te vergelijken (`==` en `!=`).
   * Vectoren bij elkaar op te tellen (`+=` en `+`).
   * Vectoren van elkaar af te trekken (`-=` en `-`).
   * Een vector te vermenigvuldigen met een getal (`*=` en `*`).
   * De array operator te gebruiken om een waarde terug te krijgen en te wijzigen (`vector[0] = 5.5`).
   * Denk er zelf eens over na of er nog nuttige operators of andere functies zouden zijn om toe te voegen.
