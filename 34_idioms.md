# Идиомы программирования

Идиомой программирования называется стандартный способ написания кода, который является наиболее эффективным и удобным для решения определенной задачи. Идиомы программирования обычно являются частью языка программирования и включают в себя стандартные шаблоны, алгоритмы и структуры данных. Идиомы программирования можно назвать низкоуровневыми паттернами проектирования[^1], которые используются для решения конкретных задач.

## Базовые идиомы

### Инкремент и декремент

Одной из стандартных задач программирования является подсчет (элементов, выполненых операций и т.д.). Стандартное решение этой задачи является введение переменной - счетчика и увеличение (уменьшение) ее значения на единицу. В ряде языков для этого используется форма:

```basic
i = i + 1
```

В `C`-подобных языках для этой задачи используется оператор инкремента `++`:

```cpp
i++;
```

Соответственно, для уменьшения значения переменной используется оператор декремента `--`:

```cpp
i--;
```

### Swap

```cpp
tmp = a;
a = b;
b = tmp;
```

### Вечный цикл

```cpp
while (true) {
    // ...
}
```

## RAII

RAII (Resource Acquisition Is Initialization) - это идиома программирования, которая заключается в том, что ресурсы должны быть выделены в конструкторе объекта и освобождены в деструкторе. Это позволяет гарантировать, что ресурсы будут освобождены в случае исключения или выхода из блока.

```cpp
class File {
public:
    File(const std::string& filename) : file(fopen(filename.c_str(), "r")) {
        if (!file) {
            throw std::runtime_error("Failed to open file");
        }
    }

    ~File() {
        fclose(file);
    }

    void read() {
        // ...
    }

private:
    FILE* file;
};
```

## Pimpl

```cpp
class Widget {
public:
    Widget();
    ~Widget();

    void doSomething();

private:
    class Impl;
    std::unique_ptr<Impl> impl;
};

class Widget::Impl {
public:
    void doSomething() {
        // ...
    }
};

Widget::Widget() : impl(std::make_unique<Impl>()) {}

Widget::~Widget() = default;

void Widget::doSomething() {
    impl->doSomething();
}
```

## Copy-and-swap

```cpp
class Widget {
public:
    Widget() : data(nullptr), size(0) {}

    Widget(const Widget& other) : data(new char[other.size]), size(other.size) {
        std::copy(other.data, other.data + size, data);
    }

    Widget& operator=(Widget other) {
        std::swap(data, other.data);
        std::swap(size, other.size);
        return *this;
    }

    ~Widget() {
        delete[] data;
    }

private:
    char* data;
    size_t size;
};
```

## Статическая инициализация

```cpp
class Singleton {
public:
    static Singleton& instance() {
        static Singleton instance;
        return instance;
    }

    void doSomething() {
        // ...
    }

private:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
```

## Библиография

[^1]: [Паттерны программирования](https://ru.wikipedia.org/wiki/Шаблон_проектирования)
