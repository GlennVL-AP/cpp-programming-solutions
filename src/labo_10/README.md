# Labo 10 Exercises

1. Implementeer de `DynamicArray` uit the theorie die gebruik maakt van new en delete en schrijf er unit tests voor.
2. Schrijf een `operator+` om twee dynamic arrays met elkaar op te tellen. De operator maakt een nieuwe array die de elementen van zowel de eerste als de tweede bevat. Hint: je kan deze operator als hidden friend implementeren indien je toegang nodig hebt tot private members van de `DynamicArray klasse`. Een `capacity()` member functie toevoegen kan eventueel ook nuttig zijn. Demonstreer het gebruik van de operator in unit tests.

   ```c++
   template <typename T>
   DynamicArray<T> operator+(DynamicArray<T> const& lhs, DynamicArray<T> const& rhs)
   {
       // ...
   }
   ```

3. Schrijf een `operator+=` om een dynamic array bij een andere op te tellen. De operator voegt de elementen van de tweede array toe aan die van de eerste array. Je zal dus de eerste array moeten vergroten zodat de elementen van de tweede erbij passen. Hint: je kan deze operator als hidden friend implementeren indien je toegang nodig hebt tot private members van de `DynamicArray` klasse. Demonstreer het gebruik van de operator in unit tests.

   ```c++
   template <typename T>
   DynamicArray<T>& operator+=(DynamicArray<T>& lhs, DynamicArray<T> const& rhs)
   {
       // ...

       return lhs;
   }
   ```

4. Doe de vorige oefeningen ook voor de DynamicArray implementatie uit the theorie die gebruik maakt van `std::unique_ptr`. Vond je dit moeilijker of gemakkelijker?
