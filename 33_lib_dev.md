# Создание библиотек

- [Создание библиотек](#создание-библиотек)
  - [Особенности создания библиотек](#особенности-создания-библиотек)
  - [Импорт / экспорт](#импорт--экспорт)
  - [Сборка библиотек](#сборка-библиотек)
  - [Библиография](#библиография)

## Особенности создания библиотек

Создание библиотек программирования в целом напоминает создание обычных приложений, однако есть определённые тонкости.

В заголовочном файле библиотеки описываются ресурсы, предназначенные для экспорта (то есть для использования программами). Эти ресурсы называются интерфейсом библиотеки (или программным интерфейсом библиотеки — `API` от `Application Programming Interface`).

Рассмотрим пример заголовочного файла статической библиотеки, описывающей работу с комплексными числами.

```cpp
#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <string>

class complex {
    double _real, _imaginary;
public:
    complex(double = 0, double = 0);
    complex(const complex&);
    ~complex();

    void operator +=(const complex&);
    void operator -=(const complex&);
    void operator *=(const complex&);
    void operator /=(const complex&);

    complex& operator = (const complex&);
    complex& operator = (const double&);

    const double& real() const;
    const double& imaginary() const;
    void swap(complex&);
    std::string toString() const;
    double module() const;
    complex conjugate() const;
};

complex operator + (const complex&, const complex&);
complex operator - (const complex&, const complex&);
complex operator * (const complex&, const complex&);
complex operator / (const complex&, const complex&);

std::ostream& operator << (std::ostream&, const complex&);
bool operator == (const complex&, const complex&);

complex pow(const complex&, const complex&);
double abs(const complex&);

#endif /* COMPLEX_H */
```

Как видно, это обычное объявление класса.

Заголовочные файлы могут включаться в проект несколько раз. Это может вызывать избыточное определение типов данных и переменных, что приведёт к ошибкам компиляции. Именно поэтому описание ресурсов библиотек в заголовочных файлах заключается между директивами препроцессора:

```cpp
#ifndef CONSTANT_NAME
#define CONSTANT_NAME

//...

#endif
```

Эти директивы на этапе препроцессирования программного кода позволяют включать определения ресурсов только один раз.

Современные компиляторы позволяют использовать вместо конструкции ветвления препроцессора конструкцию

```cpp
#pragma once
```

Это является предписанием компилятору подключать данный файл только один раз.

Реализация объявленных в заголовочном файле ресурсов происходит, как обычно, в файле `cpp`.

```cpp
#include "complex.h"
#include <sstream>
#include <cmath>

complex::complex(double r, double im): _real(r), _imaginary(im) {}
complex::complex(const complex& c): _real(c._real), _imaginary(c._imaginary) {}
complex::~complex() {}

void complex::operator +=(const complex& c) {
    _real += c._real;
    _imaginary += c._imaginary;
}
void complex::operator -=(const complex& c) {
    _real -= c._real;
    _imaginary -= c._imaginary;
}
void complex::operator *=(const complex& c) {
    double real = _real * c._real - _imaginary * c._imaginary;
    double imaginary = _real * c._imaginary + _imaginary * c._real;
    _real = real;
    _imaginary = imaginary;
}
void complex::operator /=(const complex& c) {
    double denominator = c._real * c._real + c._imaginary * c._imaginary;
    double real = (_real * c._real + _imaginary * c._imaginary) / denominator;
    double imaginary = (_imaginary * c._real - _real * c._imaginary) / denominator;
    _real = real;
    _imaginary = imaginary;
}

complex& complex::operator =(const complex& c) {
    _real = c._real;
    _imaginary = c._imaginary;
    return *this;
}
complex& complex::operator =(const double& d) {
    _real = d;
    _imaginary = 0;
    return *this;
}

const double& complex::real() const { return _real; }
const double& complex::imaginary() const { return _imaginary; }
void complex::swap(complex& c) {
    std::swap(_real, c._real);
    std::swap(_imaginary, c._imaginary);
}
std::string complex::toString() const {
    std::ostringstream strcout;
    strcout << _real << " + i*( " << _imaginary << " )";
    return strcout.str();
}
double complex::module() const {
    return std::sqrt(_real * _real + _imaginary * _imaginary);
}
complex complex::conjugate() const {
    return complex(_real, -_imaginary);
}

// extern class interface
complex operator + (const complex& c1, const complex& c2) {
    complex tmp(c1);
    tmp += c2;
    return tmp;
}
complex operator - (const complex& c1, const complex& c2) {
    complex tmp(c1);
    tmp -= c2;
    return tmp;
}
complex operator * (const complex& c1, const complex& c2) {
    complex tmp(c1);
    tmp *= c2;
    return tmp;
}
complex operator / (const complex& c1, const complex& c2) {
    complex tmp(c1);
    tmp /= c2;
    return tmp;
}

std::ostream& operator << (std::ostream& os, const complex& c) {
    os << c.toString();
    return os;
}
bool operator == (const complex& c1, const complex& c2) {
    return ((c1.real() == c2.real()) && (c1.imaginary() == c2.imaginary()));
}

complex pow(const complex&, const complex&) {
    complex result;
    return result;
}
double abs(const complex& c) {
    return c.module();
}
```

## Импорт / экспорт

В случае разработки динамических библиотек их создание может происходить аналогично созданию статических библиотек. Особенностью в данном случае будет только выбор типа проекта. Библиотека может использоваться неявно (то есть через подключение заголовочного файла и указание использования файла импорта библиотеки). Для использования функций библиотеки необходимо явно указать, к каким функциям может получить доступ зависимая от данной библиотеки программа. Для этого используется специальная конструкция языка `__declspec(dllexport)`, указывающая, что функция (класс) доступна для использования. Ниже представлен пример заголовочного файла, в котором описан класс комплексного числа. Этот класс предназначен для экспорта.

```cpp
#pragma once
#include <iostream>
#include <string>

#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT complex
{
    double _real, _imaginary;
public:
    complex(double = 0, double = 0);
    complex(const complex&);
    ~complex(void);

    complex& operator = (const complex&);
    const double& real() const;
    const double& imaginary() const;
    std::string toString() const;

    void operator += (const complex&);
};

DLLEXPORT bool operator == (const complex&, const complex&);
DLLEXPORT complex operator + (const complex&, const complex&);
DLLEXPORT std::ostream& operator << (std::ostream&, const complex&);
DLLEXPORT int min(int, int);
```

Файл реализации библиотеки не изменяется.

Описанный класс можно использовать только в C++ проектах. Для создания библиотек, совместимых с языком C, необходимо заголовочные файлы писать в стиле C (без использования классов, шаблонов и других специфичных для C++ конструкций). Также желательно в макросе `DLLEXPORT` приписать модификатор `extern "C"` — это позволяет при компиляции библиотеки сохранить оригинальные имена экспортируемых ресурсов (некоторые компиляторы "кодируют" имена функций и классов).

Использование динамической библиотеки, созданной таким образом, не будет возможно в других, отличных от C/C++, языках программирования. Это связано с тем, что в языках Pascal, Basic и др. функции получают параметры слева направо, тогда как в C/C++ параметры передаются справа налево. Для создания совместимой с этой группой языков библиотеки используется модификатор `__stdcall` (или эквивалент `__pascal`), который меняет порядок передачи параметров функции.

В ОС Windows динамические библиотеки могут также иметь точку входа — функцию `DllMain`:

```cpp
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            // A process is loading the DLL.
            break;
        case DLL_THREAD_ATTACH:
            // A process is creating a new thread.
            break;
        case DLL_THREAD_DETACH:
            // A thread exits normally.
            break;
        case DLL_PROCESS_DETACH:
            // A process unloads the DLL.
            break;
    }
    return TRUE;
}
```

## Сборка библиотек

Самый простой способ создания библиотек — выбор соответствующего проекта в среде программирования. Все современные среды программирования предлагают проекты как статических, так и динамических библиотек.

Сборка библиотек программирования при помощи компилятора `GNU GCC`, так же, как и обычных программ, происходит в несколько этапов:

1. Компиляция исходных файлов в объектные файлы;
2. Компоновка объектных файлов в библиотеку.

Следующий `Makefile` демонстрирует процесс создания библиотеки программирования:

```makefile
BINDIR = bin # directory for binary files
SRCDIR = src # directory for source files
OBJDIR = obj # directory for object files
INCDIR = include # directory for header files
LIBDIR = lib # directory for library files, third-party libraries

# compiler
CC = g++
# compiler flags
CXXFLAGS = -O2 -std=c++20 -I $(INCDIR)
# linker flags
LDFLAGS = -L $(LIBDIR)

# source files
SRC = $(wildcard $(SRCDIR)/*.cpp)
# object files
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

# library name
LIB = library

all: prepare $(LIB)-static $(LIB)-shared

static: prepare $(LIB)-static

shared: prepare $(LIB)-shared

prepare:
    mkdir -p $(OBJDIR) $(BINDIR)

clean:
    rm -f $(OBJDIR)/*.o $(BINDIR)/*

help:
    @echo "Usage:"
    @echo "make        - build library"
    @echo "make static - build static library"
    @echo "make shared - build shared library"
    @echo "make clean  - remove build artifacts"
    @echo "make help   - show help"

$(LIB)-shared: $(OBJ)
    $(CC) -shared $(OBJ) -o $(BINDIR)/lib$(LIB).so $(LDFLAGS)

$(LIB)-static: $(OBJ)
    ar rcs $(BINDIR)/lib$(LIB).a $(OBJ)

# compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
    $(CC) -c $< $(CXXFLAGS) -o $@
```

## Библиография

1. [Библиотека (программирование), Wikipedia](https://ru.wikipedia.org/wiki/Библиотека_(программирование))
2. [Создание библиотек DLL на C и C++ в Visual Studio, microsoft.com](https://learn.microsoft.com/ru-ru/cpp/build/dlls-in-visual-cpp?view=msvc-170)
3. [dlopen, Linux Manual page](https://www.man7.org/linux/man-pages/man3/dlopen.3.html)
4. [Wheeler David, Dynamically Loaded (DL) Libraries](https://dwheeler.com/program-library/Program-Library-HOWTO/)
