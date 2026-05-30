# Сопровождение проекта. Написание документации. Написание тестов

## Цель

В рамках данной работы студент знакомится с требованиями к сопровождению кода.

## Задание

Задание выполняется на основе предыдущей лабораторной работы, в ветке `lab06`.

### Создание ветки lab06

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
git checkout -B lab06
```

### Документирование кода с помощью Doxygen

Установите Doxygen. В среде MSYS2 выполните:

```bash
pacman -S mingw-w64-x86_64-doxygen
```

Создайте конфигурационный файл Doxygen в корне проекта:

```bash
doxygen -g Doxyfile
```

В файле `Doxyfile` измените следующие параметры:

```text
PROJECT_NAME           = "SnakeGame"
OUTPUT_DIRECTORY       = docs
INPUT                  = src
RECURSIVE              = YES
GENERATE_HTML          = YES
GENERATE_LATEX         = NO
```

Добавьте Doxygen-комментарии к каждому заголовочному файлу. Например, для `src/point.hpp`:

```cpp
/**
 * @file point.hpp
 * @brief Класс для представления точки на игровом поле.
 * @author Имя Фамилия
 * @date 2025
 */

#pragma once

/**
 * @brief Точка на двумерном игровом поле.
 */
struct Point {
    int x; ///< Координата X
    int y; ///< Координата Y

    /**
     * @brief Конструктор точки.
     * @param x Координата X.
     * @param y Координата Y.
     */
    Point(int x = 0, int y = 0);

    /**
     * @brief Оператор сравнения.
     * @param other Другая точка.
     * @return true, если точки равны.
     */
    bool operator==(const Point& other) const;
};
```

Аналогичным образом добавьте документацию к файлам `apple.hpp`, `board.hpp`, `direction.hpp`, `snake.hpp`, `game_engine.hpp`, `abstract_painter.hpp`, `ui_painter.hpp`.

Сгенерируйте документацию:

```bash
doxygen Doxyfile
```

Убедитесь, что в папке `docs/html/` появился файл `index.html`.

### Обновление файла README.md

Файл `README.md` в корне репозитория должен содержать следующие разделы:

```markdown
# SnakeGame

## Описание задачи

Консольная / графическая реализация игры «Змейка» на языке C++.

## Правила игры

- Змейка движется по полю и поедает яблоки.
- После поедания яблока длина змейки увеличивается на 1.
- Игра заканчивается, если змейка врезается в стену или в саму себя.

## Зависимости

- Компилятор: g++ (MinGW-w64), стандарт C++17
- Среда разработки: VS Code + MSYS2
- Библиотеки: SFML (графический режим)

## Сборка

```bash
make
```

Исполняемый файл появится в папке `bin/`.

## Запуск тестов

```bash
make test
```

### Написание модульных тестов с Catch2

Создайте папку `tests`:

```bash
mkdir tests
```

Скачайте заголовочный файл Catch2 (одиночный заголовок):

```bash
# в папке tests
curl -L https://github.com/catchorg/Catch2/releases/download/v3.5.3/catch_amalgamated.hpp -o tests/catch_amalgamated.hpp
curl -L https://github.com/catchorg/Catch2/releases/download/v3.5.3/catch_amalgamated.cpp -o tests/catch_amalgamated.cpp
```

Создайте файл `tests/test_point.cpp`:

```cpp
#include "catch_amalgamated.hpp"
#include "../src/point.hpp"

TEST_CASE("Point default constructor", "[Point]") {
    Point p;
    REQUIRE(p.x == 0);
    REQUIRE(p.y == 0);
}

TEST_CASE("Point parametrized constructor", "[Point]") {
    Point p(3, 5);
    REQUIRE(p.x == 3);
    REQUIRE(p.y == 5);
}

TEST_CASE("Point equality operator", "[Point]") {
    Point a(1, 2);
    Point b(1, 2);
    Point c(3, 4);
    REQUIRE(a == b);
    REQUIRE_FALSE(a == c);
}
```

Создайте файл `tests/test_snake.cpp`:

```cpp
#include "catch_amalgamated.hpp"
#include "../src/snake.hpp"

TEST_CASE("Snake initial length", "[Snake]") {
    Snake snake;
    snake.Init(Point(5, 5));
    REQUIRE(snake.Length() == 1);
}

TEST_CASE("Snake grows after eating", "[Snake]") {
    Snake snake;
    snake.Init(Point(5, 5));
    int before = snake.Length();
    snake.Grow();
    REQUIRE(snake.Length() == before + 1);
}
```

Напишите аналогичные тесты для классов `Apple`, `Board` и `Direction`.

### Обновление файла сборки

Добавьте в `Makefile` правила для сборки и запуска тестов:

```makefile
TESTDIR = tests
TESTBIN = $(BINDIR)/tests.exe
TESTOBJS = $(OBJDIR)/catch_amalgamated.o \
           $(OBJDIR)/test_point.o \
           $(OBJDIR)/test_snake.o

$(OBJDIR)/catch_amalgamated.o:
	$(CC) $(CXXFLAGS) -c $(TESTDIR)/catch_amalgamated.cpp -o $(OBJDIR)/catch_amalgamated.o

$(OBJDIR)/test_point.o:
	$(CC) $(CXXFLAGS) -c $(TESTDIR)/test_point.cpp -o $(OBJDIR)/test_point.o

$(OBJDIR)/test_snake.o:
	$(CC) $(CXXFLAGS) -c $(TESTDIR)/test_snake.cpp -o $(OBJDIR)/test_snake.o

$(TESTBIN): $(TESTOBJS) $(DLLS)
	$(CC) $(TESTOBJS) -o $(TESTBIN) $(LDFLAGS)

test: $(TESTBIN)
	$(TESTBIN)
```

Проверьте, что тесты собираются и проходят:

```bash
make test
```

### Фиксирование изменений

Зафиксируйте изменения в локальном репозитории и отправьте их на GitHub:

```bash
git add .
git commit -m "feat(lab06): add doxygen docs and unit tests"
git push origin lab06
```

Создайте запрос на включение изменений в основную ветку проекта (Pull Request).

## Представление

Для представления результата прикрепите ссылку на репозиторий GitHub к заданию в Moodle.

## Оценивание

- `3 балла` - использование системы документирования кода;
- `2 балла` - описание проекта в файле `README.md`;
- `3 балла` - наличие модульных тестов;
- `2 балла` - защита работы;
- `-1 балл` - за каждый день просрочки сдачи работы;
- `-5 баллов` - за плагиат.

## Рубрика оценивания

| Критерий | Макс. | 0% | 25% | 50% | 75% | 100% |
| -------- | :---: | --- | --- | --- | --- | ---- |
| Документирование кода | 3 | Комментариев нет | Документированы 1–2 файла | Документирована половина файлов | Большинство файлов документировано, есть пропуски | Все файлы полностью документированы |
| Описание проекта в README.md | 2 | README отсутствует | Есть README, но без требуемых разделов | Часть разделов присутствует | Все разделы есть, но описание неполное | README полностью заполнен по требованиям |
| Модульные тесты | 3 | Тестов нет | Есть 1–2 теста | Тесты покрывают часть классов | Большинство классов покрыто, есть ошибки | Все классы данных покрыты тестами, тесты проходят |
| Защита работы | 2 | Не явился / не знаком с кодом | Знаком поверхностно, не может объяснить решения | Объясняет код, допускает существенные ошибки | Понимает работу, допускает незначительные ошибки | Уверенно отвечает на все вопросы |
