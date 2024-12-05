#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <format>
#include <ranges>

struct date_t
{
    int year;
    int month;
    int day;

    std::string to_string() const
    {
        return std::format("{:04}{:02}{:02}", year, month, day);
    }
};

date_t operator"" _dt(unsigned long long int data)
{
    date_t date;
    date.day = data % 100;
    date.month = (data / 100) % 100;
    date.year = data / 10000;
    return date;
}

struct Student
{
    std::string firstname;
    std::string lastname;
    date_t birth_date;
};

struct Comparer
{
    std::string name;
    Comparer(std::string_view str) : name(str) {}
    bool operator()(const Student &student) const
    {
        return student.firstname == name;
    }
};

int main()
{
    std::vector<Student> students = {
        {"Alexandru", "Russu", 20040512_dt},
        {"Alexei", "Kovalenko", 20030921_dt},
        {"Alexei", "Costiuc", 20040101_dt},
        {"Iulia", "Bronovitcaia", 20041115_dt},
        {"Daniela", "Cemodanova", 20050629_dt},
        {"Maxim", "Cosarciuc", 20040220_dt},
    };

    std::string firstname;
    std::cout << "enter a name: ";
    std::cin >> firstname;

    /*
    std::vector<Student> result;
        std::copy_if(
            students.begin(),
            students.end(),
            std::back_inserter(result),
            [firstname](const Student &student)
            { return student.firstname == firstname; });
    */

    auto result = students | 
            std::views::filter([firstname](const Student &student) { return student.firstname == firstname; }) |
            std::views::reverse;

    std::cout << std::format("| {:<12} | {:<12} | {:>12} |\n", "Last Name", "First Name", "Birth Year");
    std::cout << std::format("| {:<12} | {:<12} | {:>12} |\n", std::string(12, '='), std::string(12, '='), std::string(12, '='));
    for (auto student : result)
    {
        std::cout << std::format("| {:<12} | {:<12} | {:>12} |\n", student.lastname, student.firstname, student.birth_date.to_string());
    }
    return 0;
}