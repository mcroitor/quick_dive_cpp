# Алгоритмы

- [Алгоритмы](#алгоритмы)
  - [Понятие алгоритма](#понятие-алгоритма)
    - [Функторы](#функторы)
    - [Предикаты](#предикаты)
    - [Правила именования алгоритмов в STL](#правила-именования-алгоритмов-в-stl)
  - [Алгоритмы, не меняющие данные](#алгоритмы-не-меняющие-данные)
    - [Операции поиска](#операции-поиска)
  - [Алгоритмы, меняющие данные](#алгоритмы-меняющие-данные)
    - [Копирование](#копирование)
    - [Заполнение](#заполнение)
    - [Трансформация](#трансформация)
    - [Удаление](#удаление)
    - [Упорядочивание](#упорядочивание)
    - [Сортировка](#сортировка)
  - [Устройство алгоритмов](#устройство-алгоритмов)
    - [Поиск элемента в коллекции](#поиск-элемента-в-коллекции)
    - [Поиск элемента, удовлетворяющего условию](#поиск-элемента-удовлетворяющего-условию)
    - [Копирование элементов, удовлетворяющих условию](#копирование-элементов-удовлетворяющих-условию)
  - [Примеры использования](#примеры-использования)
    - [Чтение и вывод данных](#чтение-и-вывод-данных)
    - [Поиск первого четного числа в векторе](#поиск-первого-четного-числа-в-векторе)
    - [Чтение, сортировка и поиск](#чтение-сортировка-и-поиск)
  - [Библиография](#библиография)

## Понятие алгоритма

> [!TIP]
> Алгоритм - это конечная последовательность действий, приводящая к желаемому результату.

Реализации алгоритмов стандартной библиотеки С++ очень просты и эффективны. Поэтому полезно уделить некоторое время на чтение исходников.

Все алгоритмы стандартной библиотеки шаблонов отделены от деталей реализации структур данных и используют в качестве параметров типы итераторов. Поэтому они могут работать с определяемыми пользователем структурами данных, когда эти структуры данных имеют типы итераторов, удовлетворяющие предположениям в алгоритмах.

Алгоритмы STL в основном оперируют с контейнерами, и в качестве параметров используют полуинтервалы итераторов.

### Функторы

> [!TIP]
> Функтором называется объект класса, в котором переопределен оператор "круглые скобки".

В объявлении класса можно переопределить оператор `()` (круглые скобки). Если этот оператор в классе переопределен, то объекты этого класса получают свойства функций (их можно использовать как функции). Такие объекты называются функциональными или функторами. Функторы удобно использовать, когда функция должна обладать "памятью", а также в качестве замены указателей на функции.

 > Иногда под функциональным объектом понимают указатель на функцию.

Пример функтора, который меняет значения двух целочисленных переменных и подсчитывает количество вызовов:

```cpp
/**
 * @file swap_functor.cpp
 * @brief Пример использования функционального объекта
 * @details g++ -std=c++20 -o swap_functor swap_functor.cpp
 */
class _swap{
    static size_t counter;
    static void increment() { ++counter; }
public:
    _swap(){}
    void operator ()(int& a, int& b){
        int tmp = a;
        a = b;
        b = tmp;
        increment();
    }
    int getNrCalls() {return counter; }
};

size_t _swap::counter = 0;

int main() {
    _swap swap;
    int a = 3, b = 5;
    swap(a, b);
    return 0;
}
```

### Предикаты

> [!TIP]
> Предикатом называется функция, возвращающая логическое значение.

Алгоритмы STL оперируют унарными и бинарными предикатами.

Пример предиката для проверки четности числа:

```cpp
bool isOdd(int value) {
   return value % 2 == 1;
}
```

### Правила именования алгоритмов в STL

Для некоторых алгоритмов предусмотрены как оперативные версии (то есть результат сохраняется в указанном итераторами сегменте), так и копирующие версии. Решение, включать ли копирующую версию в библиотеку, было основано на рассмотрении эффективности алгоритма. Когда стоимость выполнения операции доминирует над стоимостью копии, копирующая версия не включена. Например, `sort_copy` не включена, так как стоимость сортировки намного значительнее, и пользователи могли бы также делать `copy` перед `sort`.

Копирующая версия алгоритма `algorithm` называется `algorithm_copy` (добавляется суффикс `_copy`). В копирующих алгоритмах не указывается конец второго интервала, так как он может быть вычислен исходя их длины первого интервала.

Кроме того, для некоторых алгоритмов существуют предикатные версии. Алгоритмы, которые берут предикаты, оканчиваются суффиксом `_if` (который следует за суффиксом `_copy` в случае копирующего алгоритма).
  
Класс `Predicate` используется всякий раз, когда алгоритм ожидает функциональный объект, при применении которого к результату разыменования соответствующего итератора возвращается значение, обратимое в `bool`. Другими словами, если алгоритм берёт `Predicate pred` как свой параметр и first как свой параметр итератора, он должен работать правильно в конструкции `if (pred(*first)) {...}`. Предполагается, что функциональный объект pred не применяет какую-либо непостоянную функцию для разыменованного итератора.
  
Класс `BinaryPredicate` используется всякий раз, когда алгоритм ожидает функциональный объект, который при его применении к результату разыменования двух соответствующих итераторов или к разыменованию итератора и типа `T`, когда T - часть сигнатуры, возвращает значение, обратимое в `bool`. Другими словами, если алгоритм берёт `BinaryPredicate binary_pred` как свой параметр и `first1` и `first2` как свои параметры итераторов, он должен работать правильно в конструкции `if (binary_pred(*first, *first2)) {...}`.

`BinaryPredicate` всегда берёт тип первого итератора как свой первый параметр, то есть в тех случаях, когда `T value` - часть сигнатуры, он должен работать правильно в контексте `if (binary_pred (*first, value)) {...}`. Ожидается, что `binary_pred` не будет применять какую-либо непостоянную функцию для разыменованных итераторов.

## Алгоритмы, не меняющие данные

Данные алгоритмы не изменяют коллекции, с которыми работают.

### Операции поиска

Алгоритмы поиска выполняют поиск элементов в коллекциях и возвращают итераторы на найденные элементы. Если элемент не найден, возвращается итератор на конец коллекции.

- `find` - ищет первое вхождение элемента в коллекции.
- `find_if` - ищет первое вхождение элемента, удовлетворяющего предикату.
- `find_if_not` - ищет первое вхождение элемента, не удовлетворяющего предикату.
- `find_end` - ищет последнее вхождение подпоследовательности в коллекции.
- `find_first_of` - ищет первое вхождение любого элемента из одной коллекции в другой.
- `adjacent_find` - ищет два соседних одинаковых элемента.
- `search` - ищет первое вхождение подпоследовательности в коллекции.
- `all_of` - проверяет, что все элементы удовлетворяют предикату.
- `any_of` - проверяет, что хотя бы один элемент удовлетворяет предикату.
- `none_of` - проверяет, что ни один элемент не удовлетворяет предикату.
- `count` - подсчитывает количество элементов, удовлетворяющих предикату.
- `count_if` - подсчитывает количество элементов, удовлетворяющих предикату.
- `mismatch` - ищет первое несовпадение в двух коллекциях.
- `equal` - проверяет равенство двух коллекций.

## Алгоритмы, меняющие данные

Данные алгоритмы изменяют коллекции, с которыми работают, тем или иным способом, например, вставляют новые элементы, удаляют, меняют местами.

### Копирование

- `copy` - копирует элементы из одной коллекции в другую.
- `copy_if` - копирует элементы, удовлетворяющие предикату.
- `copy_n` - копирует первые `n` элементов.
- `copy_backward` - копирует элементы из одной коллекции в другую в обратном порядке.
- `move` - перемещает элементы из одной коллекции в другую.
- `move_backward` - перемещает элементы из одной коллекции в другую в обратном порядке.

### Заполнение

- `fill` - заполняет коллекцию одним значением.
- `fill_n` - заполняет первые `n` элементов одним значением.
- `generate` - заполняет коллекцию значениями, возвращаемыми функциональным объектом.
- `generate_n` - заполняет первые `n` элементов значениями, возвращаемыми функциональным объектом.

### Трансформация

- `transform` - применяет функцию к каждому элементу коллекции.
- `replace` - заменяет все вхождения одного значения другим.
- `replace_if` - заменяет все вхождения элементов, удовлетворяющих предикату, другим значением.
- `replace_copy` - копирует элементы из одной коллекции в другую, заменяя все вхождения одного значения другим.
- `replace_copy_if` - копирует элементы из одной коллекции в другую, заменяя все вхождения элементов, удовлетворяющих предикату, другим значением.

### Удаление

- `remove` - удаляет все вхождения элемента из коллекции.
- `remove_if` - удаляет все вхождения элементов, удовлетворяющих предикату.
- `remove_copy` - копирует элементы из одной коллекции в другую, удаляя все вхождения элемента.
- `remove_copy_if` - копирует элементы из одной коллекции в другую, удаляя все вхождения элементов, удовлетворяющих предикату.
- `unique` - удаляет все последующие дубликаты элементов.
- `unique_copy` - копирует элементы из одной коллекции в другую, удаляя все последующие дубликаты элементов.

### Упорядочивание

- `reverse` - меняет порядок элементов на обратный.
- `rotate` - сдвигает элементы коллекции слева направо. Элементы, уходящие за пределы коллекции, перемещаются в начало.
- `rotate_copy` - копирует элементы из одной коллекции в другую, сдвигая их слева направо. Элементы, уходящие за пределы коллекции, перемещаются в начало.
- `random_shuffle` - перемешивает элементы коллекции случайным образом.
- `shuffle` - перемешивает элементы коллекции случайным образом, используя указанный генератор случайных чисел.
- `shift_left` - сдвигает элементы коллекции влево.
- `shift_right` - сдвигает элементы коллекции вправо.

### Сортировка

- `sort` - сортирует коллекцию.
- `stable_sort` - сортирует коллекцию, сохраняя порядок равных элементов.
- `partial_sort` - частично сортирует коллекцию.
- `is_sorted` - проверяет, отсортирована ли коллекция.
- `is_sorted_until` - находит первый элемент, нарушающий порядок сортировки.
- `nth_element` - перемещает `n`-ый элемент на своё место в отсортированной коллекции.

## Устройство алгоритмов

Алгоритмы STL реализованы в виде шаблонных функций, которые принимают итераторы в качестве параметров. Реализации этих алгоритмов обычно очень просты и эффективны. Следующие примеры показывают устройство некоторых алгоритмов.

### Поиск элемента в коллекции

Производится полный перебор элементов от начального итератора до конечного. Если элемент найден, возвращается итератор на него, иначе возвращается итератор на конец коллекции.

```cpp
template <class InputIterator, class Type>
InputIterator find(InputIterator first, InputIterator last, const Type& value) {
    while(first != last) {
        if(*first == value) {
            return first;
        }
        ++first;
    }
    return last;
}
```

### Поиск элемента, удовлетворяющего условию

Производится полный перебор элементов от начального итератора до конечного. Если элемент, удовлетворяющий условию (предикату), найден, возвращается итератор на него, иначе возвращается итератор на конец коллекции.

```cpp
template <class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred) {
    while(first != last) {
        if(pred(*first)) {
            return first;
        }
        ++first;
    }
    return last;
}
```

### Копирование элементов, удовлетворяющих условию

Производится полный перебор элементов от начального итератора до конечного. Если элемент, удовлетворяющий условию (предикату) найден, он копируется в другую коллекцию.

```cpp
template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator copy_if( InputIterator first1, InputIterator last1,
  OutputIterator first2, Predicate predicate) {
    while(first1 != last1){
        if(predicate(*first1)){
            *first2 = *first1;
            ++ first2;
        }
        ++first1;
    }
    return first2;
}
```

## Примеры использования

### Чтение и вывод данных

Чтение массива целых чисел из стандартного потока в вектор и вывод этого вектора на экран.

```cpp
/**
 * @file read_write_vector.cpp
 * @brief Пример чтения и вывода данных
 * @details g++ -std=c++20 -o read_write_vector read_write_vector.cpp
 */
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main() {
    std::vector<int> v;
    std::copy(
      std::istream_iterator<int>(std::cin),
      std::istream_iterator<int>(),
      std::back_inserter(v));
    
    std::copy(
      v.begin(),
      v.end(),
      std::ostream_iterator<int>(std::cout, " "));
    return 0;
}
```

### Поиск первого четного числа в векторе

Дан вектор целых чисел. Найти первое чётное число.

```cpp
/**
 * @file find_even_number.cpp
 * @brief Пример поиска первого четного числа в векторе
 * @details g++ -std=c++20 -o find_even_number find_even_number.cpp
 */
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    auto it = std::find_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    if(it != v.end()) {
        std::cout << *it << std::endl;
    }
    return 0;
}
```

### Чтение, сортировка и поиск

В файле записан список студентов в следующем формате:

- каждая строка представляет одного студента;
- в строке содержатся имя студента, фамилия студента и оценка за тест. Данные разделены точкой с запятой.

Прочитать данные из файла, выбрать всех, у кого оценка выше проходного балла (то есть больше `5`) и вывести их на экран в табличном виде в порядке убывания оценки.

```cpp
/**
 * @file read_sort_search.cpp
 * @brief Пример чтения, сортировки и поиска
 * @details g++ -std=c++20 -o read_sort_search read_sort_search.cpp
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
        iss >> std::ws >> ti.grade;
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
```

## Библиография

1. [cppreference.com](https://en.cppreference.com/w/cpp/algorithm)
2. [Справочник по стандартной библиотеке C++ (STL), Microsoft](https://learn.microsoft.com/ru-ru/cpp/standard-library/cpp-standard-library-reference)
3. [Скотт Мейерс. Эффективное использование STL](https://www.google.com/search?q=Скотт+Мейерс.+Эффективное+использование+STL)
