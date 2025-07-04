# Многопоточное программирование

- [Многопоточное программирование](#многопоточное-программирование)
  - [Понятия многопоточного программирования](#понятия-многопоточного-программирования)
  - [Потоки](#потоки)
  - [Работа с системой и потоками](#работа-с-системой-и-потоками)
  - [Проблема разделения данных между потоками](#проблема-разделения-данных-между-потоками)
    - [Мьютексы](#мьютексы)
    - [Атомарные переменные и операции](#атомарные-переменные-и-операции)
  - [Асинхронное программирование](#асинхронное-программирование)
  - [Параллельные алгоритмы](#параллельные-алгоритмы)
  - [Библиография](#библиография)

## Понятия многопоточного программирования

__Программой__ называется последовательность инструкций, сохраненной в файле, исполняемом или интерпретируемом. __Процесс__ - непосредственное выполнение программы (её инструкций). Также процессом иногда называют совокупность исполняемой программы со связанными с ней ресурсами: адресным пространством, глобальными переменными, открытыми файлами и т.д. В рамках одного процесса может работать один или несколько _потоков_.

__Потоком выполнения__ (или __нитью__, en. __thread__) называется наименьшая исполняемая операционной системой единица. Реализация потоков выполнения и процессов в разных операционных системах отличается друг от друга, но в большинстве случаев поток выполнения находится внутри процесса. Несколько потоков выполнения могут существовать в рамках одного и того же процесса и совместно использовать ресурсы, такие как память, тогда как процессы не разделяют этих ресурсов. В частности, потоки выполнения разделяют последовательность инструкций процесса (его код) и его контекст — значения переменных (регистров процессора и стека вызовов), которые они имеют в любой момент времени.

Возможность операционной системы (и процессора) выполнять несколько потоков одновременно называется __многопоточностью__. Современные компьютеры позволяют выполнять сразу несколько операций за счет нескольких ядер процессора.

__Параллельный алгоритм__ это алгоритм, который может быть реализован по частям на множестве различных вычислительных устройств с последующим объединением полученных результатов и получением корректного результата. Примером параллельного алгоритма является сложение и умножение матриц.

Термин _параллельно_ совсем не означает одновременность в буквальном смысле. Две задачи выполняются _параллельно_, если они происходят в течение одного и того же периода времени.

__Параллельным программированием__ (или __многопоточным программированием__) называется метод написания программ, при котором решение задачи разделяется на несколько независимых подзадач, каждая из которых будет выполняться одновременно с другими, на различных процессорах (ядрах) в рамках одного физического или виртуального компьютера.

__Распределенным программированием__ называется метод написания программ, при котором решение задачи разделяется на несколько независимых подзадач, каждая из которых будет выполняться одновременно с другими, на различных компьютерах, физических или виртуальных.

При проектировании параллельных алгоритмов необходимо выполнять следующие шаги:

- __декомпозиция__ - процесс разбиения задачи и её решения на части;
- __связь__ - определение взаимодействий между частями решения задачи;
- __синхронизация__ - координация порядка выполнения частей решения задачи.

Потоки, выполняющиеся параллельно, могут иметь во владении свою память, однако также они имеют доступ к общей памяти, называемой __разделяемой памятью__ (en. shared memory).

Начиная со стандарта языка __C++11__ язык предлагает поддержку многопоточного программирования. C++ поддерживает следующие элементы параллельного программирования (классификация по стандартам):

- __C++11__
  - модель памяти
  - атомарные переменные
  - потоки
  - мьютексы и блокировщики
  - локальные данные потока
  - задания
- __C++14__
  - блокировщики чтения / записи
- __C++17__
  - параллельные алгоритмы
- __C++20__
  - атомарные умные указатели
  - потоки с ожиданием
  - защёлки и барьеры
  - семафоры общего вида
  - сопрограммы

## Потоки

Работа с потоками в языке C++ определена в заголовочном файле `<thread>`. Создание потока определяется через объявление объекта класса `std::thread`, в качестве параметра конструктора класса указывается функция, которая будет запускаться в дочернем потоке, а также, возможно, параметры данной функции.

Простейший пример создания дочернего потока продемонстрирован ниже:

```cpp
/**
  * @file thread_example.cpp
  * @brief Пример создания потока
  * @details g++ -std=c++11 thread_example.cpp -o thread_example
  */
#include <thread>
#include <iostream>

void hello() {
    std::cout << "hello!";
}
int main() {
    std::thread t(hello);
    t.join();
    return 0;
}
```

В данном примере создаётся поток, в котором выполняется функция `hello`, а главная программа ожидает завершения дочернего потока (`t.join();`). Если не ожидать завершения дочернего потока, то выполнение программы не определено (и обычно завершается падением дочернего потока с ошибкой).

Начиная со стандарта __C++20__ можно создавать автоматически присоединяемые потоки, используя класс `std::jthread`.

```cpp
/**
  * @file jthread_example.cpp
  * @brief Пример создания потока
  * @details g++ -std=c++20 jthread_example.cpp -o jthread_example
  */
#include <thread>
#include <iostream>

void hello() {
    std::cout << "hello from " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::jthread t(hello);
    return 0;
}
```

## Работа с системой и потоками

Для эффективной работы с операционной системой необходимо знать её конфигурацию. В частности, при работе с потоками выполнения полезно знать, сколько ядер доступно операционной системе. Стандартная библиотека C++, для получения информации о количестве ядер, доступных операционной системе, предлагает использовать функцию:

```cpp
std::thread::hardware_concurrency();
```

Данная функция возвращает количество ядер процессора, доступных операционной системе. Если количество ядер неизвестно, функция возвращает 0.

Кроме того, для работы с потоками в стандартной библиотеке C++ предусмотрены следующие методы:

- `std::this_thread::get_id()` - возвращает идентификатор текущего потока;
- `std::this_thread::sleep_for(<time duration>)` - приостанавливает выполнение текущего потока на `<time duration>` времени. Время задаётся в виде объекта класса `std::chrono::duration`;
- `std::this_thread::sleep_until(<time point>)` - приостанавливает выполнение текущего потока до момента времени `<time point>`. Время задаётся в виде объекта класса `std::chrono::time_point`.

Пример использования методов:

```cpp
/**
  * @file 23_threads_01.cpp
  * @brief Пример работы с потоками
  * @details g++ -std=c++11 23_threads_01.cpp -o 23_threads_01
  */
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int main() {
    unsigned int total_threads = std::thread::hardware_concurrency();
    std::cout << "threads: " << total_threads << std::endl;
    if(total_threads == 0) {
        std::cout << "unknown number of threads, exit" << std::endl;
        return 1;
    }

    std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;

    std::vector<std::thread> threads;

    for(unsigned int i = 0; i < total_threads; ++i) {
        threads.push_back(std::thread([i]() {
            std::cout << "thread id: " << std::this_thread::get_id() << " started" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(i));
            std::cout << "thread id: " << std::this_thread::get_id() << " finished" << std::endl;
        }));
    }
    for(unsigned int i = 0; i < total_threads; ++i) {
        threads[i].join();
    }
    return 0;
}
```

## Проблема разделения данных между потоками

Одной из проблем параллельного программирования является взаимодействие потоков с общей памятью. Если два потока имеют доступ к одному и тому же участку памяти, то они могут мешать друг другу, меняя значение, хранимое в данном сегменте памяти. Проблема, когда результат выполнения операций в двух или более потоках зависит от их порядка выполнения, называется __состоянием гонки__.

Решения проблемы гонки:

- заключить структуру данных в механизм защиты, который гарантирует изменение объекта только захватившим его потоком;
- переписать структуру данных таким образом, чтобы исключить гонку (программирование без блокировок).

### Мьютексы

__Мьютекс__ (от en. mutual exclusion - взаимное исключение) - простейший объект (примитив синхронизации), позволяющий помечать все фрагменты кода к одной и той же структуре данных с целью предотвращения состояния гонки.

Мьютекс объявлен в заголовочном файле `<mutex>`, называется `std::mutex`. Блокирование / разблокирование структуры выполняется при помощи вызова методов `lock` / `unlock`, однако прямое их использование не рекомендуется. Вместо этого рекомендуется использовать класс `std::lock_guard`, который автоматически блокирует мьютекс при создании объекта и разблокирует его при уничтожении.

```cpp
/**
  * @file mutex_example.cpp
  * @brief Пример использования мьютекса
  * @details g++ -std=c++11 mutex_example.cpp -o mutex_example
  */
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

using vector = std::vector<int>;

std::mutex locker;

void populate_vector(vector& v, size_t size) {
    std::lock_guard<std::mutex> lg(locker);
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    while(size > 0) {
        v.push_back(size);
        --size;
    }
}

void find_value(const vector& v, size_t value) {
    std::lock_guard<std::mutex> lg(locker);
    auto it = std::find(v.begin(), v.end(), value);
    it == v.end()
        ? std::cout << "not found!" << std::endl
        : std::cout << "found!" << std::endl;
}

int main() {
    vector v;
    std::jthread t_populate(populate_vector, std::ref(v), 10);
    std::jthread t_find2(find_value, std::cref(v), 7);
    return 0;
}
```

### Атомарные переменные и операции

Операция называется __атомарной__, если она не может быть выполнена частично: она либо выполняется целиком, либо не выполняется. Атомарная операция может быть выполнена только одним потоком одновременно.

Атомарность может обеспечиваться аппаратно или программно. В первом случае используются специальные машинные инструкции, атомарность которых гарантируется процессором. Во втором случае используются средства синхронизации, которые блокируют разделяемый ресурс с целью выполнения над ним операции. _Блокировка является атомарной операцией_.

__Атомарный тип данных__ - тип данных, операции с которым являются атомарными.

Определения стандартных атомарных типов даны в заголовочном файле `<atomic>`.

## Асинхронное программирование

__Асинхронное программирование__ - это способ организации программы, при котором некоторые операции выполняются не в том порядке, в котором они были вызваны. Вместо того, чтобы ждать завершения операции, программа продолжает работу, а операция завершается в фоновом режиме.

В стандарте C++11 введен класс `std::future`, который позволяет получить результат выполнения асинхронной операции. Класс `std::future` представляет собой объект, который хранит результат асинхронной операции и предоставляет методы для проверки завершения операции и получения результата. Асинхронная операция реализуется при помощи функции `std::async`, которая принимает в качестве параметров функцию, которую необходимо выполнить асинхронно, и аргументы этой функции.

```cpp
/**
  * @file async_example.cpp
  * @brief Пример использования асинхронного программирования
  * @details g++ -std=c++11 async_example.cpp -o async_example
  */
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int main() {
    std::future<int> f = std::async([]() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;
    });
    std::cout << "waiting..." << std::endl;
    std::cout << f.get() << std::endl;
    return 0;
}
```

## Параллельные алгоритмы

В стандарт C++17 добавлены параллельные версии некоторых алгоритмов. Они представлены в виде дополнительных переопределений функций, работающих с диапазонами, например `std::find`, `std::transform` или `std::reduce`. У параллельных версий такая же сигнатура, что и у "обычных" однопоточных, за исключением добавления нового первого параметра, определяющего политику выполнения.

```cpp
std::vector<int> my_data;
std::sort(std::execution::par,my_data.begin(),my_data.end());
```

Политика выполнения `std::execution::par` указывает стандартной библиотеке, что данный вызов разрешено выполнять в качестве алгоритма параллельных вычислений с задействованием сразу нескольких потоков. Следует отметить, что это разрешение, а не требование — библиотека вольна по-прежнему выполнять код в одном потоке.

Политики выполнения объявлены в заголовочном файле `<execution>`.

Стандартом предусмотрены следующие политики выполнения:

- `std::execution::sequenced_policy` с объявленным объектом `std::execution::seq` - _последовательная политика_ (sequenced policy) не является политикой параллелизма: ее использование заставляет реализацию выполнять все операции в потоке, где была вызвана функция, то есть без распараллеливания. Но все же это политика выполнения, в силу чего она оказывает такое же влияние на алгоритмическую сложность и на выдачу исключений, как и все другие стандартные политики.
- `std::execution::parallel_policy` с объявленным объектом `std::execution::par` - _параллельная политика_ (parallel policy) предоставляет основное параллельное выполнение сразу в нескольких потоках. Операции можно выполнять либо в потоке, вызвавшем алгоритм, либо в потоках, созданных библиотекой. Операции, выполняемые в конкретном потоке, должны выполняться в определенном порядке и не перемежаться, но точный порядок не определен и от вызова к вызову может варьироваться. Конкретная операция будет выполняться в фиксированном потоке на протяжении всего времени.
- `std::execution::parallel_unsequenced_policy` с объявленным объектом `std::execution::par_unseq` - _политика параллельного неупорядоченного выполнения_ (parallel unsequenced policy) предоставляет библиотеке наибольший масштаб распараллеливания алгоритма в обмен на предъявление строжайших требований к итераторам, значениям и вызываемым объектам, используемым с алгоритмом.
- `std::execution::unsequenced_policy` с объявленным объектом `std::execution::unseq` - _неупорядоченная политика_ (unsequenced policy) предоставляет библиотеке наибольший масштаб распараллеливания алгоритма в обмен на предъявление строжайших требований к итераторам, значениям и вызываемым объектам, используемым с алгоритмом.

Пример использования параллельного алгоритма:

```cpp
std::vector<int> vec ={3, 2, 1, 4, 5, 6, 10, 8, 9, 4};

std::sort(vec.begin(), vec.end());                            // sequential as ever
std::sort(std::execution::seq, vec.begin(), vec.end());       // sequential
std::sort(std::execution::par, vec.begin(), vec.end());       // parallel
std::sort(std::execution::par_unseq, vec.begin(), vec.end()); // parallel and vectorized
```

## Библиография

1. [Concurrency support library, cppreference.com](https://en.cppreference.com/w/cpp/thread)
2. [About Processes and Threads, Microsoft](https://learn.microsoft.com/en-us/windows/win32/procthread/about-processes-and-threads)
3. [MaxRokatansky, Multithreading, habr.com](https://habr.com/ru/companies/otus/articles/549814/)
4. [Многопоточность, https://cpp-kt.github.io](https://cpp-kt.github.io/cpp-notes/26_multithreading.html)
5. [Rainer Grimm, Multithreading with C++17 and C++20, moderncpp.com](https://www.modernescpp.com/index.php/multithreading-in-c-17-and-c-20/)
