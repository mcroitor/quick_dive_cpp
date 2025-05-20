# Конструкторы и операторы

## Цель

В рамках данной работы студент научится переопределять операторы, а также ознакомится с вариантами определения и использования конструкторов.

Кроме того, данная работа подготовит проект к использованию стандартной библиотеки C++.

## Задание

Задание выполняется на основе предыдущей лабораторной работы.

### Создание ветки lab03

Откройте консольное окно и перейдите в папку `SnakeGame`. Получите последние изменения проекта, выполнив команды:

```bash
# выбрать основную ветку
git checkout main
# получить последние изменения
git pull
```

Создайте ветку, в которой вы будете выполнять задание:

```bash
# создать ветку и переключиться на неё
git checkout -B lab03
```

### Обновление класса `Point`

Измените заголовочный файл `point.hpp` следующим образом:

```cpp
#pragma once

#include <iostream>

struct Point{
   int x;
   int y;

   Point(int _x = 0, int _y = 0);
   Point(const Point& other);

   Point& operator = (const Point& other);
   bool operator == (const Point& other) const;
};

std::istream& operator >> (std::istream& in, Point& point);
std::ostream& operator << (std::ostream& out, const Point& point);
```

Измените файл `point.cpp` следующим образом:

```cpp
#include "point.hpp"

Point::Point(int _x, int _y) : x(_x), y(_y) {}

Point::Point(const Point &other) : x(other.x), y(other.y) {}

Point& Point::operator=(const Point &other)
{
    if (this == &other) return *this;
    x = other.x;
    y = other.y;
    return *this;
}

bool Point::operator==(const Point &other) const
{
    return x == other.x && y == other.y;
}

std::istream& operator >> (std::istream& in, Point& point){
    int x, y;
    in >> x >> y;
    point = Point(x, y);
    return in;
}

std::ostream& operator << (std::ostream& out, const Point& point){
    out << point.x << " " << point.y;
    return out;
}
```

### Обновление класса `Apple`

Измените заголовочный файл `apple.hpp` следующим образом:

```cpp
#pragma once

#include <iostream>
#include "point.hpp"

class Apple {
   Point _position;
public:
   Apple();
   Apple(const Point& position);
   Apple(const Apple& other);
   Point GetPosition() const;

   Apple& operator = (const Apple& other);
   bool operator == (const Apple& other) const;
};

std::istream& operator >> (std::istream& in, Apple& apple);
std::ostream& operator << (std::ostream& out, const Apple& apple);
```

Измените файл `apple.cpp` следующим образом:

```cpp
#include "apple.hpp"

Apple::Apple() : _position(0, 0) {}

Apple::Apple(const Point &position) : _position(position) {}

Apple::Apple(const Apple &other) : _position(other.GetPosition()) {}

Point Apple::GetPosition() const
{
    return _position;
}

Apple& Apple::operator = (const Apple& other){
    if (this == &other) return *this;
    _position = other.GetPosition();
    return *this;
}
bool Apple::operator == (const Apple& other) const{
    return GetPosition() == other.GetPosition();
}

std::istream& operator >> (std::istream& in, Apple& apple){
    Point position;
    in >> position;
    apple = Apple(position);
    return in;
}

std::ostream& operator << (std::ostream& out, const Apple& apple){
    out << apple.GetPosition();
    return out;
}
```

### Обновление класса `Board`

Измените заголовочный файл `board.hpp` следующим образом:

```cpp
#pragma once

#include <iostream>

class Board {
   int _width;
   int _height;
public:
   Board(int width = 20, int height = 20);
   Board(const Board& other);
   int GetWidth() const;
   int GetHeight() const;

   Board& operator = (const Board& other);
   bool operator == (const Board& other) const;
};

std::istream& operator >> (std::istream& in, Board& board);
std::ostream& operator << (std::ostream& out, const Board& board);
```

Измените файл `board.cpp` следующим образом:

```cpp
#include "board.hpp"

Board::Board(int width, int height) : _width(width), _height(height) {}

Board::Board(const Board &other) : _width(other.GetWidth()), _height(other.GetHeight()) {}

int Board::GetWidth() const
{
    return _width;
}

int Board::GetHeight() const
{
    return _height;
}

Board& Board::operator=(const Board &other)
{
    if (this == &other) return *this;
    _width = other.GetWidth();
    _height = other.GetHeight();
    return *this;
}

bool Board::operator==(const Board &other) const
{
    return GetWidth() == other.GetWidth() && GetHeight() == other.GetHeight();
}

std::istream &operator>>(std::istream &in, Board &board)
{
    int width, height;
    in >> width >> height;
    board = Board(width, height);
    return in;
}

std::ostream &operator<<(std::ostream &out, const Board &board)
{
    out << board.GetWidth() << " " << board.GetHeight();
    return out;
}
```

### Обновление класса `Direction`

Измените заголовочный файл `direction.hpp` следующим образом:

```cpp
#pragma once

#include <iostream>

enum class Direction {
   Top, Left, Right, Bottom
};

std::ostream& operator<<(std::ostream& out, const Direction& direction);
```

Измените файл `direction.cpp` следующим образом:

```cpp
#include "direction.hpp"

std::ostream& operator<<(std::ostream& out, const Direction& direction){
    switch (direction)
    {
    case Direction::Top:
        out << "Top";
        break;
    case Direction::Left:
        out << "Left";
        break;
    case Direction::Right:
        out << "Right";
        break;
    case Direction::Bottom:
        out << "Bottom";
        break;
    default:
        break;
    }
    return out;
}
```

### Абстрактный класс AbstractPainter

Создайте заголовочный файл `abstract_painter.hpp`:

```cpp
#pragma once

#include "point.hpp"

struct AbstractPainter {
   virtual void DrawImage(Point topLeft, Point bottomRight, char** image) = 0;
   virtual void WriteText(Point position, const char* text) = 0;
};
```

### Обновление класса `Painter`

Измените заголовочный файл `painter.hpp` следующим образом:

```cpp
#pragma once

#include "abstract_painter.hpp"

class Painter: public AbstractPainter {
public:
   void DrawImage(Point topLeft, Point bottomRight, char** image) override;
   void WriteText(Point position, const char* text) override;
};
```

### Проверка

Проверьте корректность работы программы, выполнив сборку проекта из командной строки:

```bash
make
```

### Фиксирование изменений

Зафиксируйте изменения в локальном репозитории и отправьте их на GitHub:

```bash
git add .
git commit -m "feat(lab03): add constructors and operators"
git push origin lab03
```

Создайте запрос на включение изменений в основную ветку проекта (Pull Request).

## Представление

Для представления результата прикрепите ссылку на репозиторий GitHub к заданию в Moodle.

## Оценивание

- `1p` — реализация конструкторов;
- `1p` — реализация оператора присваивания;
- `2p` — реализация операторов сравнения;
- `2p` — реализация операторов ввода и вывода;
- `2p` — реализация базового абстрактного класса;
- `2p` — защита работы;
- `-1p` — за каждый день просрочки сдачи работы;
- `-5p` — за плагиат.
