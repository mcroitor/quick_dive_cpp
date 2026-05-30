# Создание и использование модулей / библиотек

## Цель

Выполнив данное задание, студент ознакомится с особенностями создания библиотек программирования, а также с их использованием.

## Задание

Задание выполняется на основе предыдущей лабораторной работы, в ветке `lab05`.

### Создание ветки lab05

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
git checkout -B lab05
```

### Структура каталогов проекта

Перед началом работы создайте папки для разделения исходных файлов, объектных файлов и исполняемых:

```bash
mkdir -p src obj bin
```

Переместите все файлы `.cpp` и `.hpp` в папку `src/`. Структура проекта должна принять следующий вид:

```text
SnakeGame/
├── src/          # исходные файлы (.cpp, .hpp)
├── obj/          # объектные файлы (.o)
├── bin/          # библиотеки (.dll) и исполняемый файл
└── Makefile
```

### Создание класса `UiPainter` с библиотекой SFML

Установите библиотеку [SFML](https://www.sfml-dev.org/). В среде MSYS2 выполните:

```bash
pacman -S mingw-w64-x86_64-sfml
```

Создайте файл `src/ui_painter.hpp`:

```cpp
#pragma once

#include "abstract_painter.hpp"
#include <SFML/Graphics.hpp>

class UiPainter : public AbstractPainter {
    sf::RenderWindow& _window;
public:
    explicit UiPainter(sf::RenderWindow& window);

    void DrawImage(Point topLeft, Point bottomRight,
                   const std::vector<std::string>& image) override;
    void WriteText(Point position, const std::string& text) override;
};
```

Создайте файл `src/ui_painter.cpp`:

```cpp
#include "ui_painter.hpp"
#include <SFML/Graphics.hpp>

UiPainter::UiPainter(sf::RenderWindow& window) : _window(window) {}

void UiPainter::DrawImage(Point topLeft, Point bottomRight,
                          const std::vector<std::string>& image)
{
    sf::RectangleShape cell(sf::Vector2f(20.f, 20.f));
    cell.setFillColor(sf::Color::Green);
    for (int y = topLeft.y; y < bottomRight.y; ++y) {
        for (int x = topLeft.x; x < bottomRight.x; ++x) {
            cell.setPosition(static_cast<float>(x * 20),
                             static_cast<float>(y * 20));
            _window.draw(cell);
        }
    }
}

void UiPainter::WriteText(Point position, const std::string& text)
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return;
    sf::Text sfText(text, font, 16);
    sfText.setPosition(static_cast<float>(position.x * 20),
                       static_cast<float>(position.y * 20));
    _window.draw(sfText);
}
```

`UiPainter` заменяет класс `Painter` в приложении. Измените `game_engine.hpp`, чтобы `_painter` инициализировался объектом `UiPainter`:

```cpp
// в main.cpp
#include "game_engine.hpp"
#include "ui_painter.hpp"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "SnakeGame");
    auto painter = std::make_unique<UiPainter>(window);
    GameEngine engine(std::move(painter));
    engine.Init();
    engine.Run();
    return 0;
}
```

### Обновление файла сборки

Определите переменные, в которых будут перечислены все динамические библиотеки, которые будут созданы в рамках данной работы:

```makefile
CC = g++
CXXFLAGS = -std=c++17 -Wall -I src
SRCDIR = src
OBJDIR = obj
BINDIR = bin
APPNAME = Snake.exe
DLLS = $(BINDIR)/apple.dll $(BINDIR)/board.dll $(BINDIR)/direction.dll \
       $(BINDIR)/point.dll $(BINDIR)/snake.dll
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS = -L$(BINDIR) -lapple -lboard -ldirection -lpoint -lsnake $(SFML_LIBS)
```

Для каждого класса определите данных свою библиотеку. Например, измените компиляцию файла `point.cpp` следующим образом:

```makefile
# Point
point.o:
	$(CC) $(CXXFLAGS) $(SRCDIR)/point.cpp -o $(OBJDIR)/point.o -c

$(BINDIR)/point.dll: $(OBJDIR)/point.o
	$(CC) $(OBJDIR)/point.o -shared -o $(BINDIR)/point.dll
```

Подобным образом определите компиляцию для файлов `apple.cpp`, `board.cpp`, `direction.cpp` и `snake.cpp`. Имейте в виду, что классы `Apple` и `Board` зависят от класса `Point`, а класс `Snake` зависит от классов `Point` и `Apple`.

Добавьте правило сборки `UiPainter` из библиотеки SFML:

```makefile
ui_painter.o:
	$(CC) $(CXXFLAGS) $(SRCDIR)/ui_painter.cpp -o $(OBJDIR)/ui_painter.o -c
```

Перепишите сборку проекта следующим образом:

```makefile
$(APPNAME): game_engine.o ui_painter.o main.o $(DLLS)
	$(CC) -o $(BINDIR)/$(APPNAME) \
		$(OBJDIR)/game_engine.o $(OBJDIR)/ui_painter.o $(OBJDIR)/main.o \
		$(LDFLAGS)
```

### Проверка

Соберите проект:

```bash
make
```

Проверьте наличие всех динамических библиотек и исполняемого файла:

```bash
ls -l bin/*
```

### Фиксирование изменений

Зафиксируйте изменения в локальном репозитории и отправьте их на GitHub:

```bash
git add .
git commit -m "feat(lab05): build dynamic libraries"
git push origin lab05
```

Создайте запрос на включение изменений в основную ветку проекта (Pull Request).

## Представление

Для представления результата прикрепите ссылку на репозиторий GitHub к заданию в Moodle.

## Оценивание

- `3 балла` - создание библиотек;
- `3 балла` - использование библиотек;
- `2 балла` - обновление файла сборки;
- `2 балла` - защита работы;
- `-1 балл` - за каждый день просрочки сдачи работы;
- `-5 баллов` - за плагиат.

## Рубрика оценивания

| Критерий | Макс. | 0% | 25% | 50% | 75% | 100% |
| -------- | :---: | --- | --- | --- | --- | ---- |
| Создание библиотек | 3 | Библиотеки не созданы | Создана одна библиотека | Создана половина библиотек | Большинство библиотек создано, есть ошибки | Все библиотеки созданы и работают |
| Использование библиотек | 3 | Сторонняя библиотека не используется | Библиотека подключена, но не используется | Библиотека используется частично | Библиотека используется, есть ошибки | Сторонняя библиотека полноценно интегрирована |
| Обновление файла сборки | 2 | Файл не изменён | Файл изменён, но не собирает проект | Собирает часть библиотек | Собирает все, но без зависимостей | Полноценный `Makefile` с правильными зависимостями |
| Защита работы | 2 | Не явился / не знаком с кодом | Знаком поверхностно, не может объяснить решения | Объясняет код, допускает существенные ошибки | Понимает работу, допускает незначительные ошибки | Уверенно отвечает на все вопросы |
