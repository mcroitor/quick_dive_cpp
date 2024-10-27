# Дополнительные средства стандартной библиотеки С++

- [Дополнительные средства стандартной библиотеки С++](#дополнительные-средства-стандартной-библиотеки-с)
  - [лямбда выражения](#лямбда-выражения)
  - [форматирование строк](#форматирование-строк)
  - [определение литералов](#определение-литералов)
  - [семантика перемещения](#семантика-перемещения)
  - [интервалы (ranges)](#интервалы-ranges)
  - [умные указатели](#умные-указатели)
  - [valarray](#valarray)
  - [variant, optional, any](#variant-optional-any)
  - [регулярные выражения](#регулярные-выражения)
  - [Библиография](#библиография)

## лямбда выражения

Начиная со стандарта `C++11` в языке существует возможность записывать вычисления в компактном виде - в виде __лямбда выражений__.

Синтаксис:

```cpp
[/*capture*/](/*params*/) -> /*type*/ { /*code*/; }
```

```cpp
// именованное лямбда выражение
auto sum = [](int a, int b) {return a + b;};
auto result = sum(a, b);

// объявление лямбда выражения по месту использования
std::cout << [](int a, int b) {return a + b;}(10, 15);
```

По умолчанию лямбда выражения не имеют доступа к внешним переменным, однако, в квадратных скобках можно через запятую перечислить все переменные, которые должны быть доступны в лямбда выражении.

```cpp
int a = 10;

std::cout << [a]{ return a;}();
```

Лямбда выражения могут быть универсальными (generic lambda function) если хотя бы один параметр объявлен как `auto`.

```cpp
int arr[] {1, 2, 3, 4, 5, 6};

std::for_each(arr, arr + 6, [](auto el){ std::cout << el << " ";});
```

## форматирование строк

Начиная со стандарта `C++20` в стандартной библиотеке появилась возможность форматирования строк с помощью функции `std::format`. Функция `std::format` принимает строку форматирования и аргументы, которые будут подставлены в строку. Строка форматирования содержит спецификаторы формата, которые начинаются с символа `{` и заканчиваются символом `}`.

```cpp
#include <format>
#include <iostream>

int main()
{
    std::string name = "John";
    int age = 25;

    std::string result = std::format("Name: {}, Age: {}", name, age);
    std::cout << result << std::endl;
    return 0;
}
```

Спецификаторы формата могут содержать следующие элементы, в порядке их следования:

```text
[[fill]align][sign][#][0][width][.precision][type]
```

- `fill` - символ, который будет использован для заполнения пустого места;
- `align` - выравнивание: `<` - слева, `>` - справа, `^` - по центру;
- `sign` - знак числа: `+` - всегда, `-` - только отрицательные, ` ` - пробел для положительных чисел;
- `#` - альтернативная форма вывода;
- `0` - заполнение нулями;
- `width` - минимальная ширина поля;
- `precision` - количество знаков после запятой;
- `type` - тип данных: `f` - действительное число, `g` - общий формат, `e` - экспоненциальный формат, `x` - шестнадцатеричное число и т. д.

```cpp
#include <format>
#include <iostream>
#include <vector>

int main()
{
  std::vector<std::tuple<std::string, std::string, int>> data = {
    {"John", "Doe", 25},
    {"Jane", "Smith", 30},
    {"Alice", "Brown", 35}
  };

  std::cout << std::format("| {:<10} | {:<10} | {:>3} |", "First", "Last", "Age") << std::endl;
  std::cout << std::format("|{:-^12}|{:-^12}|{:-^5}|", "", "", "") << std::endl;
  for (const auto& [first, last, age] : data)
  {
    std::string result = std::format("| {:<10} | {:<10} | {:>3} |", first, last, age);
    std::cout << result << std::endl;
  }
  return 0;
}
```

## определение литералов

__Литералом__ в программировании называется константа без имени. В С++ существует 6 видов литералов:

- целые числа: `312`, `-1ll`
- действительные числа: `12.29`
- символы: `'a'`
- строки: `"sample"`
- логические значения: `true`
- указатели: `nullptr`

Начиная с `C++11` пользователь может определять собственные литералы, которые позволяют создавать объекты пользовательских типов данных.

```cpp
ReturnType operator "" _a(unsigned long long int);   // Literal operator for user-defined INTEGRAL literal
ReturnType operator "" _b(long double);              // Literal operator for user-defined FLOATING literal
ReturnType operator "" _c(char);                     // Literal operator for user-defined CHARACTER literal
ReturnType operator "" _d(wchar_t);                  // Literal operator for user-defined CHARACTER literal
ReturnType operator "" _e(char16_t);                 // Literal operator for user-defined CHARACTER literal
ReturnType operator "" _f(char32_t);                 // Literal operator for user-defined CHARACTER literal
ReturnType operator "" _g(const char*, size_t);      // Literal operator for user-defined STRING literal
ReturnType operator "" _h(const wchar_t*, size_t);   // Literal operator for user-defined STRING literal
ReturnType operator "" _i(const char16_t*, size_t);  // Literal operator for user-defined STRING literal
ReturnType operator "" _g(const char32_t*, size_t);  // Literal operator for user-defined STRING literal
ReturnType operator "" _r(const char*);              // Raw literal operator
template<char...> ReturnType operator "" _t();       // Literal operator template
```

Имя суффикса для литерала может быть любым разрешенным.

Пример:

```cpp
// volume in liters
using volume_t = long double;

constexpr volume_t operator "" _l(long double volume){
    return volume;
}

constexpr volume_t operator "" _ml(long double volume){
    return 0.001 * volume;
}

constexpr volume_t operator "" _m3(long double volume){
    return 1000.0 * volume;
}

volume_t volume = 12.2_l + 2.1_m3 - 300.0_ml;
```

## семантика перемещения

Под семантикой перемещения понимают набор специализированных средств языка С++, который позволяет избежать издержек на копирование при создании новых объектов. Основные элементы семантики перемещения: конструктор перемещения и перемещающий оператор присваивания.

Семантика перемещения позволяет более эффективный код.

```cpp
my_string a = "hell", b = "o";
my_string result = a + b;
```

В указанном примере в результате сложения двух строк будет создан временный объект, который будет скопирован в переменную `result` и после выполнения операции - разрушен. Однако можно избежать лишнего копирования и разрушения объекта, если перенести временный объект в переменную `result`. Это выполняется перемещающим оператором присваивания. Синтаксис оператора присваивания:

```cpp
T& operator = (T&& other);
```

Пример кода:

```cpp
class my_string {
public:
  my_string& operator=(my_string&& other) {
    if (this != &other) {
      delete[] this->_data;
      this->_data = other._data;
      other._data = nullptr;
    }
    return *this;
  }

private:
  char*_data;
};
```

Можно упростить данную реализацию за счет стандартной функции `std::move`, которая выполняет семантику перемещения объекта:

```cpp
class my_string {
public:
  my_string(my_string&&other): _data(std::move(other)){}

  my_string& operator=(my_string&& other) {
    _data = std::move(other._data);
    return *this;
  }

private:
  char*_data;
};
```

## интервалы (ranges)

Большинство алгоритмов STL оперирует полуинтервалами контейнеров. Поэтому в стандартной библиотеке, начиная со стандарта `C++20`, представлено обобщение интервалов как пары итераторов.

Библиотека диапазонов определена в заголовочном файле `<ranges>`, пространстве имён `std::ranges`, и включает алгоритмы диапазонов, которые применяются к диапазонам активно, и адаптеры диапазонов, которые применяются к представлениям лениво. Адаптеры могут быть объединены в конвейеры, чтобы их действия происходили по мере повторения представления.

Алгоритмы диапазонов являются адаптированными под интервалы стандартными алгоритмами.

Адаптеры диапазонов определены в пространстве имён являются конструкторами диапазонов и определены в пространстве имен `std::ranges::view`.

Некоторые интересные адаптеры интервалов:

- `views::filter` - выборка элементов по свойству
- `views::transform` - изменение каждого элемента
- `views::take` - выборка первых _N_ элементов
- `views::take_while` - выборка элементов пока выполняется условие
- `views::drop` - отбрасывание первых _N_ элементов
- `views::drop_while` - отбрасывание элементов пока выполняется условие

Пример использования:

```cpp
#include <ranges>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto result = numbers | std::views::filter([](int el){ return el % 2 == 0; })
                          | std::views::transform([](int el){ return el * 2; });

    for (auto element : result)
    {
        std::cout << element << " ";
    }
    return 0;
}
```

## умные указатели

Начиная со стандарта `C++11` стандартная библиотека С++ предлагает абстракцию (обертку) над указателями, которые автоматически освобождают память по окончанию использования переменных.

Доступны следующие виды умных указателей:

- `unique_ptr` - при копировании объекта умного указателя `Ptr1` в `Ptr2` владельцем памяти становится `Ptr2`, тогда как `Ptr1` ссылается на `nullptr`.
- `shared_ptr` - при копировании объекта умного указателя `Ptr1` в `Ptr2` обе переменные ссылаются на одну и ту же память; освобождение памяти происходит при удалении обеих переменных.
- `weak_ptr` - _слабая_ ссылка на выделенную память: не может удалять / изменять память и всегда ссылается на память созданную `shared_ptr`.

## valarray

Шаблонный класс `std::valarray` объявлен в заголовочном файле `valarray`. Он позволяет проводить арифметические операции над векторами.

Пример использования:

```cpp
std::valarray<int> a{1, 2, 3};
std::valarray<int> b{1, 2, 3};
std::valarray<int> result = a * 5 + b;
result = result.apply([](int el){ return el - 1; });
for (auto element : result)
{
    std::cout << element << " ";
}
```

## variant, optional, any

Специальные контейнеры `std::variant`, `std::optional`, `std::any` позволяют хранить значения различных типов в одном объекте.

- `std::variant` - альтернатива использованию указателей и ссылок для хранения значений различных типов.
- `std::optional` - контейнер, который может хранить значение или быть пустым.
- `std::any` - контейнер, который может хранить значения любого типа.

Пример использования:

```cpp
#include <optional>
#include <iostream>

std::optional<int> divide(int a, int b)
{
    if (b == 0)
    {
        return std::nullopt;
    }
    return a / b;
}

int main()
{
    auto result = divide(10, 0);

    if (result.has_value())
    {
        std::cout << "Result: " << result.value() << std::endl;
    }
    else
    {
        std::cout << "Division by zero" << std::endl;
    }
    return 0;
}
```

## регулярные выражения

Стандартная библиотека С++ предоставляет возможность работы с регулярными выражениями. Для этого используется класс `std::regex`. Для работы с регулярными выражениями необходимо подключить заголовочный файл `<regex>`.

Следующий пример проверяет, является ли строка валидным email-адресом:

```cpp
#include <regex>
#include <iostream>

int main()
{
    std::string email = "i@love.you";
    std::regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");

    if (std::regex_match(email, pattern))
    {
        std::cout << "Valid email" << std::endl;
    }
    else
    {
        std::cout << "Invalid email" << std::endl;
    }
    return 0;
}
```

В данном примере используется регулярное выражение `(\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+`, которое проверяет, что строка соответствует шаблону email-адреса.

- `(\w+)` - один или более символов буквенно-цифрового символа
- `(\.|_)?` - точка или подчеркивание, необязательно
- `(\w*)` - ноль или более символов буквенно-цифрового символа
- `@` - символ @
- `(\w+)` - один или более символов буквенно-цифрового символа
- `(\.(\w+))+` - одна или более последовательностей точка-один или более символов буквенно-цифрового символа

## Библиография

1. [Standard format specification, cppreference.com](https://en.cppreference.com/w/cpp/utility/format/spec)
2. [User-defined literals, cppreference.com](https://en.cppreference.com/w/cpp/language/user_literal)
3. [Ranges library, cppreference.com](https://en.cppreference.com/w/cpp/ranges)
4. [Smart pointers, cppreference.com](https://en.cppreference.com/w/cpp/memory)
5. [valarray, cppreference.com](https://en.cppreference.com/w/cpp/numeric/valarray)
6. [variant, cppreference.com](https://en.cppreference.com/w/cpp/utility/variant)
7. [optional, cppreference.com](https://en.cppreference.com/w/cpp/utility/optional)
8. [any, cppreference.com](https://en.cppreference.com/w/cpp/utility/any)
9. [Regular expressions, cppreference.com](https://en.cppreference.com/w/cpp/regex)
