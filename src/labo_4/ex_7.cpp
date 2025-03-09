import datetime;
import std;

static_assert(std::is_class_v<datetime::Date>);
static_assert(std::is_standard_layout_v<datetime::Date>);
static_assert(std::is_implicit_lifetime_v<datetime::Date>);
static_assert(std::is_default_constructible_v<datetime::Date>);
static_assert(std::is_trivially_destructible_v<datetime::Date>);
static_assert(std::is_copy_constructible_v<datetime::Date>);
static_assert(std::is_copy_assignable_v<datetime::Date>);
static_assert(std::is_trivially_copyable_v<datetime::Date>);
static_assert(std::is_move_constructible_v<datetime::Date>);
static_assert(std::is_move_assignable_v<datetime::Date>);

int main()
{
}
