# Создание и использование классов. Многофайловые проекты. Сборка проекта.

## Цель

Выполнив данное задание студент ознакомится с особенностями реализации классов, и взаимодействием с объектами классов. Также студент получит базовые знания по сборке проектов из командной строки.

## Задание

Задание выполняется на основе предыдущей лабораторной работы. С целью упрощения работы предлагается выполнять шаги в среде разработки `Visual Studio Code`, и установленным с операционной среде компилятором `MingW G++`, программа для сборки проектов `make`, а также `GIT`.

### Создание ветки

Откройте консольное окно и перейдите в папку `SnakeGame`. Получите последние изменения проекта, выполнив команды:

```bash
# select default branch
git checkout main
# get last changes
git pull
```

Создайте ветку, в которой вы будете выполнять выполнять задание:

```bash
# create branch and switch to
git checkout -B lab02
```

### Добавление cpp файлов

Для каждого `hpp` файла создайте соответствующий `cpp` файл. Каждый С++ файл должен содержать реализации функций классов, объявленных в заголовочных файлах. Примерные содержания `cpp` файлов.

1. `apple.cpp`

```cpp
#include "apple.hpp"

Apple::Apple() {}
Apple::Apple(const Point &position) {}
Point Apple::GetPosition() const {}
```

2. `board.cpp`

```cpp
#include "board.hpp"

Board::Board(int width, int height) {}
int Board::GetWidth() const {}
int Board::GetHeight() const {}
```

3. `direction.cpp`

```cpp
#include "direction.hpp"
```

4. `game_engine.cpp`

```cpp
#include "game_engine.hpp"

GameEngine::GameEngine() {}
void GameEngine::Init() {}
void GameEngine::Run() {}
```

5. `painter.cpp`

```cpp
#include "painter.hpp"

void Painter::DrawImage(Point topLeft, Point bottomRight, char **image) {}
void Painter::WriteText(Point position, char *text) {}
```

6. `point.cpp`

```cpp
#include "point.hpp"
```

7. `snake.cpp`

```cpp
#include "snake.hpp"

Snake::Snake() {}
Snake::Snake(const Point &_position) {}
void Snake::Move(Direction direction) {}
int Snake::GetSize() const {}
Point Snake::GetPosition() const {}
void Snake::Eat(const Apple &apple) {}
```

Также создайте файл `main.cpp` который будет содержать точку входа:

```cpp
#include "game_engine.hpp"

int main() {
    GameEngine engine;
    engine.Init();
    engine.Run();
    return 0;
}
```

### Компиляция из командной строки

Для проверки работы компилятора, в командной строке перейдите в директорию проекта и выполните следующую команду:

```bash
g++ apple.cpp -o apple.o -c
```

Ключ `-c` указывает компилятору создать объектный файл. В результате выполнения данной команды в директории будет создан файл `apple.o`.

### Создание файла сборки

В директории проекта создайте файл `Makefile` со следующим содержимым:

```makefile
all: SnakeGame

SnakeGame: apple.o board.o direction.o game_engine.o painter.o point.o snake.o main.o
	g++ -o Snake.exe apple.o board.o direction.o game_engine.o painter.o point.o snake.o main.o

apple.o:
	g++ apple.cpp -o apple.o -c

board.o:
	g++ board.cpp -o board.o -c

direction.o:
	g++ direction.cpp -o direction.o -c

game_engine.o:
	g++ game_engine.cpp -o game_engine.o -c

painter.o:
	g++ painter.cpp -o painter.o -c

point.o:
	g++ point.cpp -o point.o -c

snake.o:
	g++ snake.cpp -o snake.o -c

main.o:
	g++ main.cpp -o main.o -c

clean:
	rm -f *.o *.exe
```

В командной строке выполните следующие команды:

```bash
# clean directory from objects and executables
make clean
# build application
make
```

В директории проекта будет создано приложение `Snake.exe` и ряд объектных файлов, с расширением `.o`.

### Публикация ветки и её слияние

```bash
# add all files to tracking
git add *
# check status
git status
# create a commit
git commit -m "first compilation"
# push commit to remote repository
git push
```

После этого вы можете добавить созданную ветку к ветке `main`.

## Представление

При представлении ответа прикрепите ссылку на репозиторий.

## Оценивание

- `2p` - реализация методов типов данных
- `4p` - создание файла сборки
- `1p` - создание файла `.gitignore`
- `1p` - добавление в файл `README.md` способа сборки проекта
- `2p` - добавление файлов `cpp` и файла сборки на GitHub в ветку `lab02`
- `-1p` - за каждый день задержки
- `-5p` - за плагиат
