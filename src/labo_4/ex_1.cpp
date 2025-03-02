import datetime;
import std;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

static_assert(datetime::is_leap_year(datetime::Year{1600}));
static_assert(not datetime::is_leap_year(datetime::Year{1700}));
static_assert(not datetime::is_leap_year(datetime::Year{1800}));
static_assert(not datetime::is_leap_year(datetime::Year{1900}));
static_assert(datetime::is_leap_year(datetime::Year{2000}));
static_assert(datetime::is_leap_year(datetime::Year{2004}));
static_assert(not datetime::is_leap_year(datetime::Year{2005}));

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

int main()
{
    return 0;
}
