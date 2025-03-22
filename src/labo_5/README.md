# Labo 5 Exercises

1. Maak gebruik van de onderstaande code om te experimenteren met override en virtual. Wat kan je hierbij leren over het gebruik van deze keywords? Wat als je het override keyword gebruikt bij een functie die niet eerder als virtual gedefinieerd werd? Waar ontbreekt er een virtuele destructor?

   ```c++
   import std;

   struct A     {         void print() const          { std::println("A::print"); } };
   struct B : A { virtual void print() const          { std::println("B::print"); } };
   struct C : B {         void print() const          { std::println("C::print"); } };
   struct D : B {         void print() const override { std::println("D::print"); } };
   struct E : D {         void print() const override { std::println("E::print"); } };

   int main()
   {
       A const a{}; a.print();
       B const b{}; b.print();
       C const c{}; c.print();
       D const d{}; d.print();
       E const e{}; e.print();

       A const& a_b = b; a_b.print();
       B const& b_c = c; b_c.print();
       B const& b_d = d; b_d.print();
       B const& b_e = e; b_e.print();
   }
   ```

2. Maak een klasse hierarchie van vormpjes. Je basis klasse is een interface met een functie voor de oppervlakte (area) en functie voor de omtrek (circumference). Maak de volgende klasses: Circle (heeft een straal), Square (heef een zijde), Rectangle (heeft een lengte en breedte) die elk hun oppervlakte en omtrek functie implementeren. Toon het gebruik van deze vormpjes in een eenvoudig programmatje.
3. Los de harde dependencies in de Application klasse op door interfaces te introduceren en gebruik te maken van het dependency inversion principe.

   ```c++
   import std;

   class Logger
   {
   public:
       void log(std::string msg) { std::println("Log: {}", msg); }
   };

   class MySqlDatabase
   {
   public:
       void connect() { std::println("Connecting to MySQL database!"); }
       void query(std::string sql_query) { std::println("Executing MySQL query {}", sql_query); }
   };

   class Application
   {
   public:
       void run()
       {
           db_.connect();
           logger_.log("connected!");
           db_.query("SELECT something FROM somehwere;");
           logger_.log("query executed!");
       }

   private:
       Logger logger_{};
       MySqlDatabase db_{};
   };

   int main()
   {
       Application app{};
       app.run();
   }
   ```
