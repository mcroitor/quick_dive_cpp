/**
 * В файле записан список студентов в следующем формате:
 *
 * - каждая строка представляет одного студента;
 * - в строке, разделенные точкой с запятой, содержатся имя студента, 
 *   фамилия студента, оценка за тест.
 *
 * Прочитать данные из файла, выбрать всех, у кого проходной балл 
 * (оценка больше `5`) и вывести на экран в табличном виде,
 * в порядке убывания оценки.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <format>

const std::string_view LINE_FORMAT = "{:<16} {:<16} {:>5}";

struct TestInfo {
    std::string name;
    std::string surname;
    float grade;
};

std::ostream& operator<<(std::ostream& os, const TestInfo& ti) {
    os << std::format(LINE_FORMAT, ti.name, ti.surname, ti.grade);
    return os;
}

std::istream& operator>>(std::istream& is, TestInfo& ti) {
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream iss(line);
        std::getline(iss, ti.name, ';');
        std::getline(iss, ti.surname, ';');
        iss >> ti.grade;
    }
    return is;
}

int main() {
    std::ifstream file("students.txt");
    if (!file.is_open()) {
        std::cerr << "Error: file not found\n";
        return 1;
    }

    std::vector<TestInfo> students;
    std::copy(
        std::istream_iterator<TestInfo>(file),
        std::istream_iterator<TestInfo>(),
        std::back_inserter(students));

    std::cout << std::format(LINE_FORMAT, "Name", "Surname", "Grade") << '\n';

    std::sort(
        students.begin(),
        students.end(), 
        [](const TestInfo& a, const TestInfo& b) {
            return a.grade > b.grade;
        });

    std::copy_if(
        students.begin(), 
        students.end(), 
        std::ostream_iterator<TestInfo>(std::cout, "\n"), [](const TestInfo& ti) {
            return ti.grade > 5;
        });

    return 0;
}