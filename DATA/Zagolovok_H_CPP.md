# Файлы заголовков (C++)

Имена элементов программы, таких как переменные, функции, классы и т. д., должны быть объявлены до их использования. Например, вы не можете просто написать x = 42 без первого объявления "x".
```CPP
int x; // declaration
x = 42; // use x
```
Объявление сообщает компилятору, является intли элемент , функциейdouble, или class другой вещью. Кроме того, каждое имя должно быть объявлено (прямо или косвенно) в каждом CPP-файле, в котором он используется. При компиляции программы каждый CPP-файл компилируется независимо в единицу компиляции. Компилятор не знает, какие имена объявляются в других единицах компиляции. Это означает, что если вы определяете класс или функцию или глобальную переменную, необходимо указать объявление этой вещи в каждом дополнительном CPP-файле, который использует его. Каждое объявление этой вещи должно быть точно идентичным во всех файлах. Небольшое несоответствие приведет к ошибкам или непреднамеренное поведение, когда компоновщик пытается объединить все единицы компиляции в одну программу.
Чтобы свести к минимуму потенциал ошибок, C++ принял соглашение об использовании файлов заголовков для хранения объявлений. Вы делаете объявления в файле заголовка, а затем используйте директиву #include в каждом CPP-файле или другом файле заголовка, который требует этого объявления. Директива #include вставляет копию файла заголовка непосредственно в CPP-файл перед компиляцией.

`Примечание
В Visual Studio 2019 функция модулей C++20 представлена в качестве улучшения и окончательной замены файлов заголовков . Дополнительные сведения см. в разделе "Общие сведения о модулях в C++".
`
## Пример

В следующем примере показан общий способ объявления класса и его использования в другом исходном файле. Начнем с файла заголовка, my_class.h. Он содержит определение класса, но обратите внимание, что определение является неполным; Функция-член do_something не определена:

```CPP
// my_class.h
namespace N
{
    class my_class
    {
    public:
        void do_something();
    };

}
```
Затем создайте файл реализации (обычно с расширением CPP или аналогичного расширения). Мы вызовем файл `my_class.cpp` и предоставим определение для объявления члена. Мы добавим директиву #include для файла `"my_class.h"`, чтобы объявление my_class вставлялось в этот момент в CPP-файле, и мы включаем `<iostream>` в объявление. `std::cout` Обратите внимание, что кавычки используются для файлов заголовков в том же каталоге, что и исходный файл, а для заголовков стандартной библиотеки используются угловые скобки. Кроме того, многие заголовки стандартной библиотеки не имеют расширения H или других файлов.
В файле реализации можно использовать `using` инструкцию, чтобы избежать необходимости квалифицировать каждую упоминание `"my_class"` или `"cout"` с `"N::"` или `"std::"`.
Не помещайте `using` инструкции в файлы заголовков!

```CPP
// my_class.cpp
#include "my_class.h" // header in local directory
#include <iostream> // header in standard library

using namespace N;
using namespace std;

void my_class::do_something()
{
    cout << "Doing something!" << endl;
}
```
Теперь мы можем использовать my_class в другом CPP-файле. Мы `#include` файл заголовка, чтобы компилятор извлекал объявление. Все, что компилятор должен знать, является то, что `my_class` является классом, который имеет общедоступную `do_something()` функцию-член.

```C++
// my_program.cpp
#include "my_class.h"

using namespace N;

int main()
{
    my_class mc;
    mc.do_something();
    return 0;
}
```
После завершения компиляции каждого CPP-файла в OBJ-файлы он передает OBJ-файлы компоновщику. При слиянии компоновщика файлов объектов он находит точно одно определение для my_class; он находится в OBJ-файле, создаваемом для `my_class.cpp`, и сборка завершается успешно.

## Включение охранников

Как правило, файлы заголовков имеют параметр include guard или директиву `#pragma once` , чтобы убедиться, что они не вставляются несколько раз в один CPP-файл.
```C++
// my_class.h
#ifndef MY_CLASS_H // include guard
#define MY_CLASS_H

namespace N
{
    class my_class
    {
    public:
        void do_something();
    };
}

#endif /* MY_CLASS_H */
```

## Что нужно поместить в файл заголовка
Так как файл заголовка может быть включен несколькими файлами, он не может содержать определения, которые могут создавать несколько определений одного имени. Следующие действия не допускаются или считаются очень плохой практикой.

* Встроенные определения типов в пространстве имен или глобальных область
* Определения функций, отличных от встроенных
* Определения переменных, отличные от const
* Агрегатные определения
* Безымянные пространства имен
* Директивы `using`

`using` Использование директивы не обязательно приведет к ошибке, но может вызвать проблему, так как она приносит пространство имен в область в каждом CPP-файле, который прямо или косвенно включает этот заголовок.

## Пример файла заголовка
В следующем примере показаны различные виды объявлений и определений, которые разрешены в файле заголовка:
```C++
// sample.h
#pragma once
#include <vector> // #include directive
#include <string>

namespace N  // namespace declaration
{
    inline namespace P
    {
        //...
    }

    enum class colors : short { red, blue, purple, azure };

    const double PI = 3.14;  // const and constexpr definitions
    constexpr int MeaningOfLife{ 42 };
    constexpr int get_meaning()
    {
        static_assert(MeaningOfLife == 42, "unexpected!"); // static_assert
        return MeaningOfLife;
    }
    using vstr = std::vector<int>;  // type alias
    extern double d; // extern variable

#define LOG   // macro definition

#ifdef LOG   // conditional compilation directive
    void print_to_log();
#endif

    class my_class   // regular class definition,
    {                // but no non-inline function definitions

        friend class other_class;
    public:
        void do_something();   // definition in my_class.cpp
        inline void put_value(int i) { vals.push_back(i); } // inline OK

    private:
        vstr vals;
        int i;
    };

    struct RGB
    {
        short r{ 0 };  // member initialization
        short g{ 0 };
        short b{ 0 };
    };

    template <typename T>  // template definition
    class value_store
    {
    public:
        value_store<T>() = default;
        void write_value(T val)
        {
            //... function definition OK in template
        }
    private:
        std::vector<T> vals;
    };

    template <typename T>  // template declaration
    class value_widget;
}
```