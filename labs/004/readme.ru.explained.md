# Использование стандартной библиотеки С++

## Цель

В рамках данной работы студент знакомится со стандартной библиотекой C++.

## Задание

Задание выполняется на основе предыдущей лабораторной работы, в ветке `lab04`. С целью упрощения работы предлагается выполнять шаги в среде разработки `Visual Studio Code`, с установленным в операционной системе компилятором `MinGW G++`, программой для сборки проектов `make`, а также `GIT`.

### Создание ветки lab04

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
git checkout -B lab04
```

### Замена массивов в стиле C на контейнеры STL

В классе `Snake` заменяется массив фиксированного размера на `std::vector`. Измените заголовочный файл `snake.hpp`:

```cpp
#pragma once

#include <vector>
#include "apple.hpp"
#include "direction.hpp"
#include "point.hpp"

class Snake {
   std::vector<Point> _segments;
public:
   Snake();
   Snake(const Point& position);
   Snake(const Snake& other);

   void Move(Direction direction);
   int GetSize() const;
   Point GetPosition() const;
   void Eat(const Apple& apple);

   Snake& operator=(const Snake& other);
   bool operator==(const Snake& other) const;
};

std::ostream& operator<<(std::ostream& out, const Snake& snake);
```

Измените файл `snake.cpp`:

```cpp
#include "snake.hpp"
#include <algorithm>

Snake::Snake() : _segments({ Point(10, 10) }) {}

Snake::Snake(const Point& position) : _segments({ position }) {}

Snake::Snake(const Snake& other) : _segments(other._segments) {}

void Snake::Move(Direction direction)
{
    Point head = _segments.front();
    switch (direction) {
        case Direction::Top:    head.y -= 1; break;
        case Direction::Bottom: head.y += 1; break;
        case Direction::Left:   head.x -= 1; break;
        case Direction::Right:  head.x += 1; break;
    }
    _segments.insert(_segments.begin(), head);
    _segments.pop_back();
}

int Snake::GetSize() const
{
    return static_cast<int>(_segments.size());
}

Point Snake::GetPosition() const
{
    return _segments.front();
}

void Snake::Eat(const Apple& apple)
{
    _segments.push_back(apple.GetPosition());
}

Snake& Snake::operator=(const Snake& other)
{
    if (this == &other) return *this;
    _segments = other._segments;
    return *this;
}

bool Snake::operator==(const Snake& other) const
{
    return _segments == other._segments;
}

std::ostream& operator<<(std::ostream& out, const Snake& snake)
{
    out << "Snake[" << snake.GetSize() << "] head=" << snake.GetPosition();
    return out;
}
```

### Замена `char*` на `std::string`

Измените файл `abstract_painter.hpp`, заменив `char*` на `std::string`:

```cpp
#pragma once

#include <string>
#include <vector>
#include "point.hpp"

struct AbstractPainter {
   virtual void DrawImage(Point topLeft, Point bottomRight,
                          const std::vector<std::string>& image) = 0;
   virtual void WriteText(Point position, const std::string& text) = 0;
};
```

Измените файл `painter.hpp`:

```cpp
#pragma once

#include "abstract_painter.hpp"

class Painter : public AbstractPainter {
public:
   void DrawImage(Point topLeft, Point bottomRight,
                  const std::vector<std::string>& image) override;
   void WriteText(Point position, const std::string& text) override;
};
```

Измените файл `painter.cpp`:

```cpp
#include "painter.hpp"
#include <iostream>

void Painter::DrawImage(Point topLeft, Point bottomRight,
                        const std::vector<std::string>& image)
{
    for (const auto& row : image) {
        std::cout << row << "\n";
    }
}

void Painter::WriteText(Point position, const std::string& text)
{
    std::cout << text << "\n";
}
```

### Использование алгоритмов STL

Добавьте в `game_engine.cpp` пример использования алгоритмов `std::find` и `std::for_each`:

```cpp
#include "game_engine.hpp"
#include <algorithm>
#include <vector>
#include <iostream>

GameEngine::GameEngine() {}

void GameEngine::Init()
{
    _snake = Snake(Point(10, 10));
    _apple = Apple(Point(5, 5));
    _board = Board(20, 20);
}

void GameEngine::Run()
{
    // пример использования std::vector и алгоритмов
    std::vector<Point> history;
    history.push_back(_snake.GetPosition());

    // std::find — поиск позиции в истории
    Point target(10, 10);
    auto it = std::find(history.begin(), history.end(), target);
    if (it != history.end()) {
        std::cout << "Found: " << *it << "\n";
    }

    // std::for_each — вывод всех позиций
    std::for_each(history.begin(), history.end(), [](const Point& p) {
        std::cout << p << "\n";
    });
}
```

### Использование умных указателей

Измените `game_engine.hpp`, используя `std::unique_ptr` для хранения объекта `Painter`:

```cpp
#pragma once

#include <memory>
#include "apple.hpp"
#include "snake.hpp"
#include "board.hpp"
#include "painter.hpp"

class GameEngine {
   Apple _apple;
   Snake _snake;
   Board _board;
   std::unique_ptr<AbstractPainter> _painter;
public:
   GameEngine();
   void Init();
   void Run();
};
```

В `game_engine.cpp` инициализируйте указатель:

```cpp
GameEngine::GameEngine()
    : _painter(std::make_unique<Painter>())
{}
```

### Сборка и проверка

Обновите `Makefile`, добавив флаг стандарта C++14 или выше:

```makefile
CXXFLAGS = -std=c++17 -Wall

all: SnakeGame

SnakeGame: apple.o board.o direction.o game_engine.o input_handler.o painter.o point.o snake.o main.o
	g++ $(CXXFLAGS) -o Snake.exe $^

%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o *.exe
```

Выполните сборку:

```bash
make clean
make
```

### Фиксирование изменений

```bash
git add .
git commit -m "feat(lab04): use STL containers, algorithms and smart pointers"
git push origin lab04
```

Создайте запрос на включение изменений в основную ветку проекта (Pull Request).

## Представление

Для представления результата прикрепите ссылку на репозиторий GitHub к заданию в Moodle.

## Оценивание

- `2 балла` - использование контейнеров STL;
- `1 балл` - использование `std::string`;
- `1 балл` - потоки ввода/вывода;
- `2 балла` - использование умных указателей / ссылок;
- `2 балла` - использование алгоритмов STL;
- `2 балла` - защита работы;
- `-1 балл` - за каждый день просрочки сдачи работы;
- `-5 баллов` - за плагиат.

## Рубрика оценивания

| Критерий | Макс. | 0% | 25% | 50% | 75% | 100% |
| -------- | :---: | --- | --- | --- | --- | ---- |
| Контейнеры STL | 2 | Массивы в стиле C не заменены | Заменён один массив | Заменена половина массивов | Большинство заменено, есть ошибки | Все массивы заменены контейнерами STL |
| `std::string` | 1 | Используется `char*` везде | Заменено в одном месте | Заменено частично | Заменено в большинстве мест | `char*` полностью заменён на `std::string` |
| Потоки ввода/вывода | 1 | Не используются | Используется `printf`/`scanf` | Есть частичное использование потоков | Потоки используются, но с ошибками | Потоки используются корректно везде |
| Умные указатели / ссылки | 2 | Используются сырые указатели | Умные указатели используются в одном месте | Умные указатели частично заменяют сырые | Используются везде, есть ошибки | Умные указатели и ссылки используются корректно |
| Алгоритмы STL | 2 | Не используются | Используется один алгоритм | Используется два-три алгоритма | Алгоритмы используются широко, есть ошибки | Алгоритмы STL активно и корректно используются |
| Защита работы | 2 | Не явился / не знаком с кодом | Знаком поверхностно, не может объяснить решения | Объясняет код, допускает существенные ошибки | Понимает работу, допускает незначительные ошибки | Уверенно отвечает на все вопросы |
