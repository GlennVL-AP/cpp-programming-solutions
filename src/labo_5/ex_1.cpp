import std;

struct A
{
    void print() const { std::println("A::print"); } // NOLINT(readability-convert-member-functions-to-static)
};

struct B : A
{
    B() = default;
    virtual ~B() = default;

    B(B const&) = delete;
    B& operator=(B const&) = delete;
    B(B&&) = delete;
    B& operator=(B&&) = delete;

    virtual void print() const { std::println("B::print"); }
};

struct C : B
{
    void print() const override { std::println("C::print"); }
};

struct D : B
{
    void print() const override { std::println("D::print"); }
};

struct E : D
{
    void print() const override { std::println("E::print"); }
};

int main()
try
{
    A const aaa{};
    aaa.print();
    B const bbb{};
    bbb.print();
    C const ccc{};
    ccc.print();
    D const ddd{};
    ddd.print();
    E const eee{};
    eee.print();

    A const& a_b = bbb;
    a_b.print();
    B const& b_c = ccc;
    b_c.print();
    B const& b_d = ddd;
    b_d.print();
    B const& b_e = eee;
    b_e.print();
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
