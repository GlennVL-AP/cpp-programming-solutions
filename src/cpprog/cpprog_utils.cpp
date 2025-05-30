export module cpprog:utils;

import std;

namespace cpprog {

export struct ExpectError final : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

export constexpr void expect(
    std::predicate auto&& cond,
    std::string_view msg,
    std::source_location const location = std::source_location::current()
)
{
    if (!cond()) [[unlikely]]
    {
        throw ExpectError{std::format(
            "ExpectError @ {}({}:{}) `{}`: {}",
            location.file_name(),
            location.line(),
            location.column(),
            location.function_name(),
            msg
        )};
    }
}

export struct NarrowingError final : std::exception
{
    [[nodiscard]] char const* what() const noexcept override { return "NarrowingError"; }
};

export template <typename TO, typename FROM>
[[nodiscard]] constexpr TO narrow_cast(FROM value)
{
    auto const result = static_cast<TO>(value);
    if (static_cast<FROM>(result) != value) { throw NarrowingError{}; }
    return result;
}

} // namespace cpprog
