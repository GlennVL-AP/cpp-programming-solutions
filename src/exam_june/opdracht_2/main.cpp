import std;

namespace {

struct Student
{
    std::string name;
    int score;
};

std::vector<Student> read_students()
{
    std::vector<Student> result{};

    std::println("Geef een aantal studenten en scores");
    for (Student student{}; std::cin >> student.name >> student.score;)
    {
        result.push_back(student);
    }

    return result;
}

}

int main()
try
{
    auto students = read_students();

    std::ranges::sort(students, [](Student const& first, Student const& second) {
        return second.score < first.score;
    });

    for (auto const& student : students)
    {
        std::println("{} {}", student.name, student.score);
    }
}
catch (std::exception const& e)
{
    std::cerr << e.what() << "\n";
    return 1;
}
