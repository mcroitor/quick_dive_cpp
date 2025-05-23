# Основы языка C++

- [Основы языка C++](#основы-языка-c)
  - [Элементы языка](#элементы-языка)
    - [константы](#константы)
    - [идентификаторы](#идентификаторы)
    - [ключевые слова](#ключевые-слова)
    - [специальные символы](#специальные-символы)
    - [комментарии](#комментарии)
  - [Базовые типы и переменные](#базовые-типы-и-переменные)
    - [Целые числа](#целые-числа)
    - [Действительные числа](#действительные-числа)
    - [Логический тип](#логический-тип)
    - [Переменные](#переменные)
  - [Базовые структуры](#базовые-структуры)
    - [Ветвления](#ветвления)
    - [Выбор](#выбор)
    - [Циклы](#циклы)
      - [Цикл со счетчиком](#цикл-со-счетчиком)
      - [Цикл с предусловием](#цикл-с-предусловием)
      - [Цикл с постусловием](#цикл-с-постусловием)
    - [Функции](#функции)
  - [Управление памятью](#управление-памятью)
    - [Указатели](#указатели)
    - [Ссылки](#ссылки)
    - [Выделение и освобождение памяти](#выделение-и-освобождение-памяти)
    - [Массивы](#массивы)
  - [Библиография](#библиография)

## Элементы языка

Язык С++ (как и любой другой язык) определяется следующими элементами:

- __константы__ - определяют данные программы;
- __идентификаторы__ - позволяют назвать хранилища данных и алгоритмы для их использования;
- __ключевые слова__ - зарезервированные языком слова, предназначенные для описания программ;
- __специальные символы__ - символы пунктуации, имеющие специальное значение, в зависимости от контекста;
- __комментарии__ - блоки текста, не транслируемые в бинарный код, предназначенные для пояснения кода программы.

### константы

Константами являются неизменяемые величины и могут быть представлены числом (целым или действительным), символом или последовательностью символов (строкой).

Примеры констант:

- `1`, `-12l`, `0b0010011`, `01237`, `0xab` - целые числа
- `1.0`, `-2.32e+05`, `1.0e-5` - действительные числа
- `'a'`, `'U'`, `'\n'`, `'\0xa3'`, `'\200'` - символы
- `"this is a string"`, `""`, `"\13\255\32\32"` - строка символов

### идентификаторы

Идентификаторы это имена переменных, функций, констант и пользовательских типов данных.

Идентификатор представляется последовательностью символов, используемых для обозначения:

- Идентификатор состоит из одного или более символов;
- Идентификатор может начинаться с символа подчеркивания или с буквы латинского алфавита;
- После первого символа в идентификаторе может идти символ подчеркивания, буквы латинского алфавита или цифра.
- Нельзя использовать ключевые слова в качестве идентификаторов.

Символы прописных букв и заглавных являются различными! ( `sample` != `Sample` )

Примеры:

- `sample`
- `_my_variable`
- `THIS_IS_A_CONSTANT`
- `MyVariable10`

### ключевые слова

В версии С89 определено 32 ключевых слова.

- __auto__ — Указание компилятору вывести тип переменной на основании типа присваемого значения
- __break__ — Оператор выхода из цикла
- __case__ — Оператор указания варианта выбора (используется вместе с _switch_)
- __char__ — Символьный тип данных
- __const__ — Объекты типа _const_ не могут быть изменены программой во время её выполнения
- __continue__ — Оператор продолжения цикла с пропуском оставшихся операторов до конца блока
- __default__ — Оператор выбора по умолчанию
- __do__ — Оператор цикла с постусловием без счётчика
- __double__ — Тип данных с плавающей запятой двойной точности
- __else__ — Условный оператор "иначе"
- __enum__ — Пользовательский тип данных "перечисляемый тип"
- __extern__ — Спецификатор типа для указания компилятору внешней привязки переменной
- __float__ — Тип данных с плавающей запятой
- __for__ — Оператор цикла с предусловием, с счётчиком
- __goto__ — Оператор безусловного перехода
- __if__ — Условный оператор "если"
- __int__ — Целочисленный тип данных
- __long__ — Модификатор типа данных для определения длинных переменных
- __register__ — Спецификатор типа для хранения переменной в регистрах процессора
- __return__ — Оператор для возврата из функции значения
- __short__ — Модификатор типа данных для определения коротких переменных
- __signed__ — Модификатор типа данных для определения знаковых переменных
- __sizeof__ — Оператор служащий для определения размера типа данных во время компиляции
- __static__ — Указывает компилятору хранить локальную переменную во время всего жизненного цикла программы
- __struct__ — Пользовательский тип данных "структура"
- __switch__ — Оператор выбора
- __typedef__ — Оператор для создания нового имени типа данных
- __union__ — Пользовательский тип данных "объединение"
- __unsigned__ — Модификатор типа данных для определения беззнаковых переменных
- __void__ — Пустой тип данных
- __volatile__ — Квалификатор типа сообщает компилятору, что значение переменной может быть изменено средствами, заданными в программе неявным образом
- __while__ — Оператор цикла с предусловием, без счётчика

В языке C++ содержатся все ключевые слова, определенные в версии _С89_, а также следующие[^1]:

- __asm__ — Ключевое слово для вставки одной или нескольких инструкций ассемблера
- __bool__ — Логический тип данных
- __catch__ — Блок программы которая содержит ту часть программы, которая обрабатывает ошибку
- __class__ — Пользовательский тип данных "класс"
- __const_cast__ — Оператор приведения типа, используется для явного переопределения модификаторов _const_ и/или _volatile_
- __delete__ — Оператор освобождает память на которую указывает аргумент
- __dynamic_cast__ — Оператор приведения типа, проверяет законность выполнения заданной операции приведения типа
- __explicit__ — Конструктор, определённый с помощью спецификатора _explicit_, будет использоваться только в том случае, если инициализация в точности совпадает с тем, что задано конструктором
- __export__ — Ключевое слово, позволяющее другим файлам использовать шаблон, объявленный в другом файле путём задания лишь его объявления.
- __false__ — Логическая константа, имеющую значение "ложь".
- __friend__ — Ключевое слово определяет дружественные функции или классы
- __inline__ — Спецификатор используемый для помещения тела функции непосредственно в текст программы
- __mutable__ — Спецификатор типа позволяет члену некоторого объекта переопределить свойство постоянства
- __namespace__ — Ключевое слово для создания пространства имён
- __new__ — Оператор выделяет динамическую память и возвращает указатель соответствующего типа на эту область памяти
- __operator__ — Ключевое слово operator используется для создания перегруженных функций-операторов
- __private__ — Спецификатор доступа "приватный", определяющий способ наследования базового класса
- __protected__ — Спецификатор доступа "защищённый", определяющий способ наследования базового класса
- __public__ — Спецификатор доступа "открытый", определяющий способ наследования базового класса
- __reinterpret_cast__ — Оператор приведения типа, переводит один тип в совершенно другой
- __static_cast__ — Оператор приведения типа, выполняет не полиморфное приведение типов
- __template__ — Ключевое слово _template_ используется для создания обобщённых функций и классов
- __this__ — Используется для обозначения указателей на объект, который сгенерировал обращение к функции-члену
- __throw__ — Оператор _throw_ генерирует исключение
- __true__ — Логическая константа, имеющую значение "истина"
- __try__ — Блок программы которая содержит ту часть программы, которая предназначена для обработки ошибок
- __typeid__ — Оператор _typeid_ возвращает ссылку на объект _type\_info_, описывающий тип объекта, к которому принадлежит оператор _typeid_
- __typename__ — Ключевое слово, которое можно использовать вместо ключевого слова _class_ в объявлении template или для обозначения неопределённого типа
- __using__ — Переносит переменную из определённого пространства имён в глобальную область видимости переменных
- __virtual__ — Спецификатор типа определяющий виртуальные функции
- __wchar_t__ — Символьный двухбайтовый тип данных

### специальные символы

Знаки пунктуации и специальные символы в наборе символов языка C имеют различные применения, от организации текста программы до определения задач, выполняемых компилятором или скомпилированной программой.

В С++ используются следующие специальные символы:

- `( )`
- `[ ]`
- `{ }`
- `*`
- `,`
- `:`
- `=`
- `;`
- `...`
- `#`

Эти знаки не определяют операции, подлежащие выполнению и могут иметь различный смысл, в зависимости от контекста.

Некоторые знаки пунктуации также являются операторами языка.

### комментарии

В исходном коде можно писать как однострочные комментарии, так и многострочные.

Однострочный комментарий начинается с `//` и считается до конца строки.

Многострочный комментарий определяется метками `/*` `*/`, между которыми можно написать любое количество строк текста.

Комментарии широко используются не только для объяснения программного кода, но также и для создания технической документации. Существует ряд приложений (Doxygen, JavaDoc и др.), которые анализируют комментарии и создают документацию в формате HTML, PDF или другом. Также, современные IDE используют комментарии для генерирования всплывающих подсказок к коду.

## Базовые типы и переменные

Каждая программа предназначена для обработки данных. Данные являются числами, строками или комбинацией чисел и строк (составные данные). Соответственно, для хранения данных и работы с ними используются специальные «хранилища» – _переменные_.

Переменная является идентификатором, обозначающим некоторую область в памяти. Каждая переменная имеет свой тип.

Базовые типы: целые числа, действительные числа, логический тип.

Тип определяет, какие значения может иметь переменная и сколько байт в памяти она будет занимать.

### Целые числа

- __char__ - представляет один символ. Занимает в памяти 1 байт. Может хранить любое значение из диапазона от -128 до 127. Переменным типа char можно присвоить один символ в одинарных кавычках.
- __unsigned char__ - представляет один символ. Занимает в памяти 1 байт (8 бит). Может хранить значение из диапазона от 0 до 255.
- __short__ -  представляет целое число в диапазоне от –32768 до 32767. Занимает в памяти обычно 2 байта.
- __int__ - представляет целое число. В зависимости от архитектуры процессора может занимать 2, 4 или 8 байт.
- __long long__ - представляет целое число в диапазоне от `-9 223 372 036 854 775 808` до `+9 223 372 036 854 775 807`. Занимает в памяти 8 байт.

Любое десятичное число рассматривается по умолчанию как значение типов `int` / `long int` / `long long int` (в зависимости от размера) и при присвоении переменным другим типов будет выполняться преобразование.

Чтобы указать, что число явным образом представляет определенный тип, к числу добавляется определенный суффикс:

- `unsigned int` – `u` или `U`
- `long int` – `l` или `L`
- `unsigned long int` – `ul` или `UL`
- `long long` – `ll` или `LL`
- `unsigned long long` – `ull` или `ULL`

### Действительные числа

- __float__ - представляет вещественное число одинарной точности с плавающей точкой в диапазоне `-3.4E+38` до `3.4E+38`. В памяти занимает 4 байта.
- __double__ - представляет вещественное число двойной точности с плавающей точкой в диапазоне `-1.7E+308` до `1.7E+308`. В памяти занимает 8 байт.
- __long double__ - представляет вещественное число двойной точности с плавающей точкой. В памяти занимает от 96 до 128 бит, в зависимости от реализации компилятора и архитектуры процессора.

### Логический тип

В языке С++ для логических значений существует специальный тип — __bool__. Допустимыми значениями этого типа являются только `true` и `false`, при этом других значений у переменной данного типа быть не может.

Переменная типа __bool__ может занимать в памяти ровно 1 байт.

Тип bool совместим с типом __int__ по присваиванию в обе стороны, при этом `true` переходит в `1`, `false` — в `0`.

При обратном приведении любое число, не равное нулю — переходит в `true`, `0` — в `false`.

Значения логического типа являются результатом выполнения операций сравнения или составленных из сравнений выражений.

В С++ определены следующие операции сравнения:

| оператор | пример |
| -------- | ------ |
| Меньше   | X < Y |
| Больше   | X > Y |
| Меньше или равно | X <= Y |
| Больше или равно | X >= Y |
| Равно    | X == Y |
| Не равно | X != Y |

В языке C++ существует 3 логические операции

- `&&` - операция И (конъюнкция)
- `||` - операция ИЛИ (дизъюнкция)
- `!` – операция НЕ (отрицание)

Логические операции позволяют составить из нескольких простых логических выражений одно более сложное.

| A | B | A && B | A \|\| B | !A |
| ----- | ----- | ------ | ------ | ----- |
| true | true | true | true | false |
| true | false | false | true | false |
| false | true | false | true | true |
| false | false | false | false | true  |

### Переменные

При объявлении переменной сначала указывается её тип, потом, через пробельный символ (символы), название переменной.

```cpp
int variable;
```

Можно определить сразу несколько переменных одного типа, перечислив их через запятую.

```cpp
int a, b, c;
```

Переменную можно сразу инициализировать, присвоив ей значение по умолчанию.

```cpp
int x = 0, y = x;
char chr1 = 10, chr2 = 'x';
```

## Базовые структуры

Простейшая программа на С++ выглядит следующим образом:

```cpp
int main() {
   return 0;
}
```

Простейшая программа на С++ состоит из функции main, называемой точкой входа[^2].

Функция main возвращает целое число – код завершения программы. Возвращаемое значение `0` интерпретируется операционной системой как успешное завершение программы, а любое другое значение - как ошибка.

Также точка входа может принимать входные параметры - аргументы программы, передаваемые при запуске (например, в командной строке).

```cpp
/**
 * @file minimal.cpp
 * @brief Простейшая программа на C++
 * @details g++ minimal.cpp -o minimal
 */
int main(int argc, char** argv) {
   return 0;
}
```

Первый параметр _argc_ содержит количество аргументов командной строки, второй параметр _argv_ представляет собой массив строк, представляющий сами аргументы. Для понимания работы с аргументами точки входа рекомендуется рассмотреть и выполнить следующий код:

```cpp
/**
 * @file args.cpp
 * @brief Программа, которая выводит аргументы командной строки
 * @details g++ args.cpp -o args
 */
#include <iostream>

int main(int argc, char **argv) {
  for(int i = 0; i < argc; ++i) {
    std::cout << "argv[ " << i << " ] = " << argv[i] << std::endl;
  }
  return 0;
}
```

Можно убедиться, что первым аргументом будет имя исполняемого файла.

### Ветвления

Ветвление является одним из базовых блоков программирования. Оно позволяет выполнять тот или иной код, в зависимости от условия (логическое выражение).

Если блок команд после __else__ пустой, то он может пропускаться.

Если блок команд в условии состоит из одной команды, фигурные скобки могут быть пропущены.

Полный синтаксис ветвления выглядит следующим образом:

```cpp
if(/* условие */) {
    // блок команд 1
}
else {
    // блок команд 2
}
```

Однако могут встречаться и укороченные (упрощенные) формы, в зависимости от сложности конструкции:

```cpp
// блок команд содержит одну команду, фигурные скобки опущены, не рекомендуется
if(/* условие */)
    // команда 1
else
    // команда 2

// нет команд для альтернативного выполнения, блок else пропущен
if(/* условие */) {
    // блок команд
}
```

### Выбор

Конструкция __switch__ / __case__ позволяет сравнить некоторое выражение с набором значений.
После ключевого слова __switch__ в скобках идет сравниваемое выражение. Значение этого выражения последовательно сравнивается со значениями после оператора __сase__. И если совпадение будет найдено, то будет выполняться определенный блок __сase__ и все последующие за ним (если не стоит __break__).

```cpp
switch( /* выражение */) {
   case /* значение_1 */: /* инструкции_1 */;
   case /* значение_2 */: /* инструкции_2 */;
   // ...................
   case /* значение_N */: /* инструкции_N */;
   default: /* инструкции */;
}
```

### Циклы

Циклы являются одной из базовых конструкций языка, позволяющей выполнить ряд одних и тех же команд несколько раз.

В языке C++ существует 3 вида операторов цикла:

- цикл for;
- цикл while с предусловием;
- цикл do…while с постусловием.

Любой из вышеприведенных операторов цикла может быть заменен другим.

Начиная со стандарта С++11 введен цикл «для каждого» (for each).

#### Цикл со счетчиком

Часто возникает необходимость выполнить одну и ту же последовательность действий несколько (N) раз. Для этого используются циклы со счетчиком:

```cpp
for(/* инициализация счетчика */; /* условие */; /* изменение счетчика */) {
    // тело цикла
}
```

_Инициализатор_ выполняется один раз при начале выполнения цикла и представляет установку начальных условий, как правило, это инициализация счетчиков - специальных переменных, которые используются для контроля за циклом.

_Условие_ представляет условие, при соблюдении которого выполняется цикл. Как правило, в качестве условия используется операция сравнения, и если она возвращает ненулевое значение (то есть условие истинно), то выполняется тело цикла, а затем выполняется итерация.

_Итерация_ выполняется после каждого завершения блока цикла и задает изменение параметров цикла. Обычно здесь происходит увеличение счетчиков цикла.

#### Цикл с предусловием

Цикл __while__ с предусловием позволяет выполнить одну и ту же последовательность действий пока проверяемое условие истинно. При этом условие записывается до тела цикла и проверяется до выполнения тела цикла.

```cpp
while (/* условие */) {
    // тело цикла
}
```

#### Цикл с постусловием

Цикл __while__ с постусловием отличается от цикла с предусловием тем, что сначала выполняется блок цикла, а потом проверяется условие. Если условие истинно, то цикл будет выполнен еще раз, и так до тех пор, пока условие будет истинно.

```cpp
do {
    // тело цикла
}
while (/* условие */);

```

### Функции

Во многих случаях возникает необходимость выполнить ряд команд несколько раз в разных участках кода. В этом случае эти команды можно выделить в отдельный блок, присвоить им имя и использовать по имени.

Функция это именованный блок программного кода. Функция может иметь входные параметры, позволяющие при работе с функцией передавать аргументы (значения, для вычислений).

Имя функции должно отражать / описывать её назначение.

```cpp
/* тип возвращаемого значения */ /* имя функции */(/* параметры */) {
   // тело функции
}
```

Функция может вызываться из любого количества мест в программе. Значения, передаваемые функции, являются аргументами, типы которых должны быть совместимы с типами параметров в определении функции.

```cpp
int sum (int a, int b) {
   return a + b;
}

int value = sum(5, 10);
```

> Термин _аргумент_ относится к значению, которое используется при вызове функции. Переменная, которая принимает этот аргумент, называется _параметром_. Функции, которые принимают аргументы, называются _параметризованными функциями_. [Шилдт][^3]

## Управление памятью

Программы, при работе, используют два вида памяти: стек (__stack__) и куча (__heap__).

Стек (__stack__) - фиксированная память, выделяемая при компиляции. В нее записываятся объявления переменных и изменение размещения переменных в памяти при работе программы невозможно.

Куча (__heap__) - динамическая память, в которой можно выделять участки памяти в процессе работы программы.

### Указатели

Языки С / C++ предлагают специализированный тип данных: указатель на область памяти определённого типа. Значение переменной данного типа представляет собой целое число, которое представляет собой адрес памяти. Размер памяти, на которую указывает данный указатель, определяется прописанным типом данных [^4].

Объявление указателя выполняется указанием типа, потом пишется специальный знак `*`, после которого пишется имя переменной.

```cpp
// <type> * <pointer_name>;
int * sampleIntPointer;
char * sampleCharPointer;
```

В примере `sampleIntPointer` может содержать адрес участка памяти в 4 байта.

Чтобы проинициализировать указатель, в переменную необходимо записать адрес ячейки памяти. Взятие адреса переменной выполняется при помощи специального символа `&`.

Пример работы с указателями:

```cpp
/**
 * @file pointer.cpp
 * @brief Пример работы с указателями
 * @details g++ pointer.cpp -o pointer
 */
#include <iostream>

int main() {
    int coolValue = 256;
    int * intPtr = &coolValue;
    char * charPtr = (char*)&coolValue;

    std::cout << "Cool value = " << coolValue << std::endl;
    std::cout << "pointer of cool value = " << intPtr << std::endl;
    std::cout << "access value by pointer = " << *intPtr << std::endl;
    std::cout << "first byte = " << (int)*charPtr << std::endl;
    std::cout << "second byte = " << (int)*(charPtr + 1) << std::endl;
    std::cout << "third byte = " << (int)*(charPtr + 2) << std::endl;
    std::cout << "fourth byte = " << (int)*(charPtr + 3) << std::endl;

    return 0;
}
```

Поведение ссылки похоже на поведение константного указателя.

### Ссылки

Память для локальных переменных выделяется в стеке, в эту выделенную память можно записать значение. Иногда возникает необходимость ввести переменную, которая будет псевдонимом для другой переменной. Псевдоним переменной называется _ссылка_ и объявляется при помощи символа `&` (амперсанд).

Пример объявления ссылки:

```cpp
int a = 10;
int& another_ref_a = a;
```

> Ссылка всегда инициализируется, и инициализируется другой переменной.

```cpp
/**
 * @file reference.cpp
 * @brief Пример работы со ссылками
 * @details g++ reference.cpp -o reference
 */
#include <iostream>

int main() {
    int value = 10;
    int &ref = value;

    std::cout << "value: " << value << ", reference = " << ref << std::endl;
    value = 12;
    std::cout << "value: " << value << ", reference = " << ref << std::endl;
    ref = 15;
    std::cout << "value: " << value << ", reference = " << ref << std::endl;
    return 0;
}
```

Исходя из примера, ссылка представляет собой псевдоним существующей переменной, поэтому изменение значения переменной изменяет значение ссылки.

Чаще всего ссылка используется при объявлении параметров функций, чтобы избежать копирования значений.

> Ссылка по поведению похожа на константный указатель.

### Выделение и освобождение памяти

В языке C++ для выделения и освобождения памяти используются операторы `new` и `delete`.

Оператор `new` выделяет память для объекта и возвращает указатель на этот объект. Оператор `delete` освобождает память, выделенную для объекта.

```cpp
int * intPtr = new int;
*intPtr = 10;
std::cout << *intPtr << std::endl;
delete intPtr;
```

### Массивы

Массивом называется структура данных, которая позволяет хранить в себе несколько элементов одного типа. Для объявления массива необходимо указать тип данных, имя массива и количество элементов в квадратных скобках. Доступ к элементам массива осуществляется при помощи индекса элемента в квадратных скобках.

```cpp
int sampleArray[10];
sampleArray[0] = 10;
sampleArray[10] = 20; // eroare!!! indexul este mai mare sau egal decât dimensiunea vectorului
```

Массив может быть размещен в памяти динамически с помощью оператора `new`, в этом случае он называется динамическим массивом. После использования динамического массива память должна быть правильно освобождена с помощью оператора `delete`.

```cpp
int * sampleArray = new int[10];
sampleArray[0] = 10;

// delete[] используется для освобождения памяти, выделенной для массива
// удаление массива sampleArray через delete приведет к ошибке
delete[] sampleArray;
```

## Библиография

[^1]: [C++ Keywords](https://en.cppreference.com/w/cpp/keyword)
[^2]: [Main function](https://en.cppreference.com/w/cpp/language/main_function)
[^3]: [Shildt] Herbert Schildt. C++: The Complete Reference, 4th Edition. McGraw-Hill Education, 2003. ISBN: 978-0-07-223215-8
[^4]: [Pointer declaration](https://en.cppreference.com/w/cpp/language/pointer)
