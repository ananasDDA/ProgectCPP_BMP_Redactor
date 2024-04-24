# Internal documentation
(Объяснение работы приложения)

# НУЖНО СДЕЛАТЬ:
Постановка задачи
...
на уровне компании должна возникнуть потребность в моей программе
гост 34.602

функционалтные требования к проекту

какую задачу я решаю

полноценный процесс проектирования

взаимодействие между функциями

UML диаграмма классов



```
├── CMakeLists.txt
├── Color.cpp
├── color.h
├── Image.cpp
├── image.h
├── image_processor.cpp
├── ImageProcessor.h
├── Parser.cpp
├── Parser.h
├── Reader.cpp
├── Reader.h
├── Writer.cpp
├── Writer.h
├── filter.cpp
├── filter.h
├── Utils.h
└── test_script
    ├── data
    │   ├── flag.bmp
    │   ├── flag_crop.bmp
    │   ├── flag_edge.bmp
    │   ├── flag_edge_edge.bmp
    │   ├── flag_gs.bmp
    │   ├── flag_neg.bmp
    │   ├── flag_sharp.bmp
    │   ├── lenna.bmp
    │   ├── lenna_blur.bmp
    │   ├── lenna_blur_blur.bmp
    │   ├── lenna_crop.bmp
    │   ├── lenna_crop_crop.bmp
    │   ├── lenna_gs.bmp
    │   ├── lenna_gs_gs.bmp
    │   ├── lenna_neg.bmp
    │   ├── lenna_neg_neg.bmp
    │   ├── lenna_sharp.bmp
    │   └── lenna_sharp_sharp.bmp
    └── test_image_processor.py
```

## CMakeLists.txt
Файл `CMakeLists.txt` является основным конфигурационным файлом для системы автоматизации сборки проектов CMake. Cодержит инструкции по сборке проекта, включая компиляцию исходного кода и линковку.
```
add_executable(
    image_processor
    image_processor.cpp
        filter.cpp
        Parser.cpp
        Reader.cpp
        Writer.cpp
        Color.cpp
        Image.cpp
)
```
В общем, `CMakeLists.txt` описывает структуру проекта и определяет, как именно должен происходить процесс сборки. CMake обрабатывает этот файл, чтобы сгенерировать соответствующие make-файлы или другие конфигурации для систем сборки, в зависимости от конкретной операционной системы и предпочитаемого компилятора.


## Color
`Color.cpp` и `color.h` - реализация и заголовочный файл для класса или функций, связанных с обработкой цвета в изображениях.

### color.h
```cpp
#ifndef CPP_HSE_COLOR_H
#define CPP_HSE_COLOR_H
```
- `#ifndef CPP_HSE_COLOR_H` и `#define CPP_HSE_COLOR_H` - это директивы препроцессора, которые предотвращают повторное включение содержимого файла. Если `CPP_HSE_COLOR_H` еще не определен, то содержимое файла будет включено и определено. Это называется "include guard".
```cpp
#pragma once
```
- `#pragma once` - это нестандартная, но широко поддерживаемая директива препроцессора, которая служит той же цели, что и include guards, предотвращая повторное включение файла.
```cpp
#include <cstdint>
```
- `#include <cstdint>` - включает стандартный заголовочный файл, который предоставляет фиксированные размеры целочисленных типов, такие как `uint8_t`.
```cpp
struct Color {
    Color() = default;
    Color(uint8_t in_blue, uint8_t in_green, uint8_t in_red);

    void SetColor(uint8_t in_blue, uint8_t in_green, uint8_t in_red);

    uint8_t blue;
    uint8_t green;
    uint8_t red;
};
```
- `struct Color` - определение структуры с именем `Color`. Структуры в C++ используются для группировки переменных разных типов под одним именем.

- Внутри `struct Color`:
  - `Color() = default;` - это объявление конструктора по умолчанию, который компилятор сгенерирует автоматически.
  - `Color(uint8_t in_blue, uint8_t in_green, uint8_t in_red);` - это объявление конструктора, который принимает три аргумента типа `uint8_t`, представляющие синий, зеленый и красный компоненты цвета соответственно.
  - `void SetColor(uint8_t in_blue, uint8_t in_green, uint8_t in_red);` - это объявление метода `SetColor`, который будет использоваться для установки значений цветовых компонентов.
  - `uint8_t blue;`, `uint8_t green;`, `uint8_t red;` - это объявления членов структуры, которые хранят значения синего, зеленого и красного компонентов цвета. Тип `uint8_t` означает, что каждый компонент цвета представлен 8-битным беззнаковым целым числом, что дает диапазон значений от 0 до 255.

```cpp
#endif  // CPP_HSE_COLOR_H
```
- `#endif  // CPP_HSE_COLOR_H` - это конец условия include guard, который начинается с `#ifndef`.

### Color.cpp
Реализация конструктора и метода для структуры `Color`, объявленной в файле `color.h`. Вот подробное описание кода:
```cpp
#include "color.h"
```
`#include "color.h"` - эта строка подключает заголовочный файл `color.h`, который содержит объявление структуры `Color`. Это необходимо, чтобы код в `color.cpp` мог использовать структуру `Color`.

```cpp
Color::Color(uint8_t in_blue, uint8_t in_green, uint8_t in_red) : blue(in_blue), green(in_green), red(in_red) {
}
```
`Color::Color(uint8_t in_blue, uint8_t in_green, uint8_t in_red) : blue(in_blue), green(in_green), red(in_red) {}` - это определение конструктора для структуры `Color`. Конструктор принимает три параметра: `in_blue`, `in_green`, и `in_red`, каждый из которых представляет собой цветовой компонент (синий, зеленый, и красный соответственно) типа `uint8_t`. В теле конструктора используется список инициализации для непосредственного присваивания этих значений членам структуры `blue`, `green`, и `red`. Тело конструктора пусто, так как все операции проводятся в списке инициализации.
```cpp
void Color::SetColor(uint8_t in_blue, uint8_t in_green, uint8_t in_red) {
    blue = in_blue;
    green = in_green;
    red = in_red;
}
```
`void Color::SetColor(uint8_t in_blue, uint8_t in_green, uint8_t in_red) {` - это определение метода `SetColor`, который используется для установки новых значений цветовых компонентов объекта `Color`. Этот метод также принимает три параметра: `in_blue`, `in_green`, и `in_red`.
- Внутри метода `SetColor`:
      - `blue = in_blue;` - присваивает значение `in_blue` члену структуры `blue`.
      - `green = in_green;` - присваивает значение `in_green` члену структуры `green`.
      - `red = in_red;` - присваивает значение `in_red` члену структуры `red`.

**Kод позволяет создавать объекты структуры `Color` с конкретными значениями цветовых компонентов, используя конструктор, а также изменять значения этих компонентов для существующих объектов с помощью метода `SetColor`**


## Image
`Image.cpp` и `image.h` - реализация и заголовочный файл для класса, который представляет изображение и может включать методы для загрузки, сохранения и манипуляции с изображением.

### image.h
```cpp
#ifndef IMAGE_H
#define IMAGE_H
```
`#ifndef IMAGE_H` и `#define IMAGE_H` - это директивы препроцессора, которые предотвращают повторное включение содержимого файла. Если `IMAGE_H` еще не определен, то содержимое файла будет включено и определено. Это называется "include guard".
```cpp
#include <cstdint>
#include <cstddef>
#include <vector>

#include "color.h"
```
`#include <cstdint>`, `#include <cstddef>`, `#include <vector>`, `#include "color.h"` - эти строки подключают стандартные заголовочные файлы и заголовочный файл `color.h`, который содержит объявление структуры `Color` для работы с цветом в изображении.
```cpp
class Image {
public:
    Image() = default;
    Image(size_t in_width, size_t in_height);
    Image(const std::vector<std::vector<Color>>& pixels);  // NOLINT
    Image(const Image& other);
    ~Image() = default;

    size_t GetWidth() const;
    size_t GetHeight() const;
    const std::vector<std::vector<Color>>& GetPixels() const;
    Color& GetPixel(size_t x, size_t y);
    const Color& GetPixel(size_t x, size_t y) const;
    void SetPixel(size_t x, size_t y, const Color& color);

private:
    size_t width_ = 0;
    size_t height_ = 0;
    std::vector<std::vector<Color>> pixs_;  // NOLINT

    void CheckHeightAndWidth(size_t x, size_t y) const;
};
```
`class Image {` и соответствующий `};` - это объявление класса `Image`.
- Внутри класса `Image`:
      - `public:` - это область доступа, определяющая, что все члены, объявленные после нее, будут доступны извне класса.
      - `Image() = default;` - это объявление конструктора по умолчанию, который компилятор сгенерирует автоматически.
      - `Image(size_t in_width, size_t in_height);` - это объявление конструктора, который принимает два параметра `in_width` и `in_height` типа `size_t`, представляющие ширину и высоту изображения соответственно.
      - `Image(const std::vector<std::vector<Color>>& pixels);` - это объявление конструктора, который принимает двумерный вектор `pixels` типа `std::vector<std::vector<Color>>`, представляющий пиксели изображения.
      - `Image(const Image& other);` - это объявление конструктора копирования, который принимает другой объект типа `Image` и создает копию этого объекта.
      - `~Image() = default;` - это объявление деструктора по умолчанию, который компилятор сгенерирует автоматически.
      - `size_t GetWidth() const;` - это объявление метода `GetWidth`, который возвращает ширину изображения.
      - `size_t GetHeight() const;` - это объявление метода `GetHeight`, который возвращает высоту изображения.
      - `const std::vector<std::vector<Color>>& GetPixels() const;` - это объявление метода `GetPixels`, который возвращает ссылку на двумерный вектор пикселей изображения.
      - `Color& GetPixel(size_t x, size_t y);` - это объявление метода `GetPixel`, который возвращает ссылку на пиксель с координатами `(x, y)` и позволяет изменять его.
      - `const Color& GetPixel(size_t x, size_t y) const;` - это объявление метода `GetPixel`, который возвращает константную ссылку на пиксель с координатами `(x, y)` и предотвращает его изменение.
      - `void SetPixel(size_t x, size_t y, const Color& color);` - это объявление метода `SetPixel`, который устанавливает пиксель с координатами `(x, y)` равным переданному цвету `color`.
      - `private:` - это область доступа, определяющая, что все члены, объявленные после нее, будут доступны только внутри класса.
      - `size_t width_ = 0;` и `size_t height_ = 0;` - это объявления приватных членов класса `width_` и `height_`, которые представляют ширину и высоту изображения соответственно, и инициализируются значением по умолчанию 0.
      - `std::vector<std::vector<Color>> pixs_;` - это объявление приватного члена класса `pixs_` типа `std::vector<std::vector<Color>>`, который представляет пиксели изображения.
      - `void CheckHeightAndWidth(size_t x, size_t y) const;` - это объявление приватного метода `CheckHeightAndWidth`, которому передаются координаты `(x, y)` и который проверяет, что эти координаты находятся в пределах ширины и высоты изображения.

```cpp
#endif  // IMAGE_H
```
`#endif  // IMAGE_H` - это конец условия include guard

**Kод позволяет создавать объекты структуры `Color` с конкретными значениями цветовых компонентов, используя конструктор, а также изменять значения этих компонентов для существующих объектов с помощью метода `SetColor`**


### Image.cpp
```cpp
#include "image.h"
#include "color.h"
#include <stdexcept>
```
`#include "image.h"` подключает заголовочный файл `image.h`. Этот файл содержит объявление класса `Image` и его методов, которые относятся к обработке и хранению информации об изображениях. Использование кавычек (`" "`) указывает на то, что компилятор сначала будет искать этот файл в текущей директории или в директориях, указанных для поиска пользовательских заголовочных файлов.
`#include "color.h"` подключает заголовочный файл `color.h`. Этот файл содержит объявление класса `Color` и его методов, которые используются для работы с цветами пикселей изображения. Так же, как и в предыдущем случае, кавычки указывают на поиск файла в локальных директориях проекта.
`#include <stdexcept>` подключает стандартный заголовочный файл `stdexcept`, который является частью стандартной библиотеки C++. Этот файл содержит объявления стандартных классов исключений, которые могут быть использованы для обработки ошибок в программе. В отличие от предыдущих директив, использование угловых скобок (`< >`) указывает на то, что компилятор будет искать этот файл в стандартных путях поиска библиотек компилятора.
```cpp
Image::Image(size_t in_width, size_t in_height)
    : width_(in_width), height_(in_height), pixs_(in_height, std::vector<Color>(in_width)) {
}
```
Конструктор `Image::Image(size_t in_width, size_t in_height)` инициализирует объект `Image` с заданной шириной и высотой. Он также создает двумерный вектор `pixs_` размером `in_height` на `in_width`, представляющий пиксели изображения.

```cpp
Image::Image(const std::vector<std::vector<Color>>& pixels)
    : width_(pixels.empty() ? 0 : pixels[0].size()), height_(pixels.size()), pixs_(pixels) {
}
```
Конструктор `Image::Image(const std::vector<std::vector<Color>>& pixels)` инициализирует объект `Image` с помощью переданного вектора `pixels`. Он определяет ширину и высоту изображения на основе размеров вектора `pixels` и копирует его содержимое в двумерный вектор `pixs_`.

```cpp
Image::Image(const Image& other) = default;
```
Конструктор копирования `Image::Image(const Image& other)` создает копию объекта `Image`.

```cpp
size_t Image::GetWidth() const {
    return width_;
}
```
Метод `Image::GetWidth()` возвращает ширину изображения.

```cpp
size_t Image::GetHeight() const {
    return height_;
}
```
Метод `Image::GetHeight()` возвращает высоту изображения.

```cpp
const std::vector<std::vector<Color>>& Image::GetPixels() const {
    return pixs_;
}
```
Метод `Image::GetPixels()` возвращает ссылку на двумерный вектор `pixs_`, представляющий пиксели изображения.

```cpp
Color& Image::GetPixel(size_t x, size_t y) {
    CheckHeightAndWidth(x, y);
    return pixs_[x][y];
}
```
Метод `Image::GetPixel(size_t x, size_t y)` возвращает ссылку на пиксель с координатами `(x, y)` в изображении. Он также проверяет, что переданные координаты находятся в пределах изображения.

```cpp
const Color& Image::GetPixel(size_t x, size_t y) const {
    CheckHeightAndWidth(x, y);
    return pixs_[x][y];
}
```
Метод `Image::GetPixel(size_t x, size_t y) const` (константная версия) аналогичен предыдущему методу, но предназначен для работы с константными объектами `Image`.

```cpp
void Image::SetPixel(size_t x, size_t y, const Color& color) {
    CheckHeightAndWidth(x, y);
    pixs_[x][y] = color;
}
```
Метод `Image::SetPixel(size_t x, size_t y, const Color& color)` устанавливает значение пикселя с координатами `(x, y)` в переданный `color`. Он также проверяет, что переданные координаты находятся в пределах изображения.

```cpp
void Image::CheckHeightAndWidth(size_t x, size_t y) const {
    if (x >= height_ || y >= width_) {
        throw std::out_of_range("Picture out of range");
    }
}
```
Метод `Image::CheckHeightAndWidth(size_t x, size_t y) const` осуществляет проверку, что переданные координаты `(x, y)` находятся в пределах размеров изображения. Если координаты выходят за пределы, генерируется исключение `std::out_of_range`.


## Image_Processor
`ImageProcessor.h` и `image_processor.cpp` - заголовочный файл и его реализация для класса, который отвечает за применение фильтров к изображениям.

### ImageProcessor.h
```cpp
#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
```
`#ifndef IMAGEPROCESSOR_H` и `#define IMAGEPROCESSOR_H` - это директивы препроцессора, которые предотвращают повторное включение содержимого файла. Если `IMAGEPROCESSOR_H` еще не определен, то содержимое файла будет включено и определено. Это называется "include guard".

```cpp
#include "Reader.h"
#include "Utils.h"
#include "Parser.h"
#include "Writer.h"
#include "color.h"
#include "image.h"
#include "filter.h"
```
`#include "Reader.h"`, `#include "Utils.h"`, `#include "Parser.h"`, `#include "Writer.h"`, `#include "color.h"`, `#include "image.h"`, `#include "filter.h"` - эти строки подключают заголовочные файлы, которые содержат объявления классов, функций и структур данных, используемых в коде `ImageProcessor.h`.

```cpp
std::vector<parse::Token> GetTokens(int argc, char** argv);  // NOLINT
```
`std::vector<parse::Token> GetTokens(int argc, char** argv);` - это объявление функции `GetTokens`, которая принимает два параметра: `argc` и `argv`, которые представляют количество аргументов командной строки и массив аргументов командной строки соответственно. Функция возвращает вектор объектов `parse::Token`, который представляет собой последовательность токенов, полученных из аргументов командной строки.

```cpp
Image GetImage(const std::string& path);
```

`Image GetImage(const std::string& path);` - это объявление функции `GetImage`, которая принимает один параметр `path` типа `std::string`, представляющий путь к файлу изображения. Функция возвращает объект `Image`, который представляет собой загруженное изображение.

```cpp
void WriteImage(const Image& image, const std::string& path);
```

`void WriteImage(const Image& image, const std::string& path);` - это объявление функции `WriteImage`, которая принимает два параметра: `image` типа `const Image&`, представляющий изображение, которое нужно записать, и `path` типа `const std::string&`, представляющий путь для сохранения изображения. Функция записывает изображение в указанный файл.

```cpp
Image ApplyFilters(Image& image, const std::vector<parse::Token>& tokens);
```

`Image ApplyFilters(Image& image, const std::vector<parse::Token>& tokens);` - это объявление функции `ApplyFilters`, которая принимает два параметра: `image` типа `Image&`, представляющий изображение, к которому нужно применить фильтры, и `tokens` типа `const std::vector<parse::Token>&`, представляющий последовательность токенов фильтров. Функция применяет указанные фильтры к изображению и возвращает измененное изображение.

```cpp
#endif  // IMAGEPROCESSOR_H
```

### image_processor.cpp
```cpp
#include <iostream>
#include "ImageProcessor.h"
```
`#include <iostream>` включает стандартную библиотеку ввода-вывода, которая используется для вывода сообщений об ошибках.
`#include "ImageProcessor.h"` включает объявление классов и функций, относящихся к обработке изображений, включая функцию `parse::Parse`, классы `Image`, `parse::Token` и функции для чтения/записи изображений.

```cpp
int main(int argc, char* argv[]) {
    try {
        std::vector<parse::Token> tokens = parse::Parse(argc, argv);
        Image img = GetImage(tokens[1].name);
        img = ApplyFilters(img, tokens);  // NOLINT

        WriteImage(img, tokens[2].name);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
```
**Главная функция `main`:**
- Принимает аргументы командной строки `argc` и `argv[]`, где `argc` - количество аргументов, а `argv` - массив строк с аргументами.
- В блоке `try` вызывает функцию `parse::Parse`, чтобы разобрать аргументы командной строки на токены, представляющие собой команды и параметры для обработки изображения.
- Загружает изображение с помощью `GetImage`, используя путь из второго токена.
- Применяет фильтры к изображению с помощью функции `ApplyFilters`.
- Сохраняет обработанное изображение в файл, используя путь из третьего токена.
- В случае возникновения исключений (`std::exception`), выводит сообщение об ошибке в стандартный поток ошибок (`std::cerr`).

**Вспомогательные функции**
```cpp
std::vector<parse::Token> GetTokens(int argc, char** argv) {  // NOLINT
    std::vector<parse::Token> tokens = parse::Parse(argc, argv);
    if (tokens.size() < 2) {
        throw std::invalid_argument("Expected more arguments");
    }
    return tokens;
}
```
- `GetTokens`: анализирует аргументы командной строки и проверяет наличие необходимого минимума аргументов.
(`NOLINT` - комментарий, используемый для указания инструментам статического анализа кода (например, linters), что данную строку следует игнорировать.)

```cpp
Image GetImage(const std::string& path) {
    reading_and_writing::Reader reader(path);
    Image img = reader.Read();
    return img;
}
```
- `GetImage`: создаёт экземпляр класса для чтения изображений (`reading_and_writing::Reader`) и загружает изображение из файла.

```cpp
void WriteImage(const Image& image, const std::string& path) {
    reading_and_writing::Writer writer(path);
    writer.Write(image);
}
```
- `WriteImage`: создаёт экземпляр класса для записи изображений (`reading_and_writing::Writer`) и сохраняет обработанное изображение в файл.

```cpp
Image ApplyFilters(Image& image, const std::vector<parse::Token>& tokens) {
    for (size_t i = 3; i < tokens.size(); ++i) {
        image = filters::CreateFilter(tokens[i])->Apply(image);
    }
    return image;
}
```
- `ApplyFilters`: применяет фильтры к изображению в соответствии с токенами, начиная с четвёртого (индекс 3), создавая и применяя фильтры с помощью фабрики фильтров `filters::CreateFilter`.


## Parser
`Parser.cpp` и `Parser.h` - реализация и заголовочный файл для класса или функций парсинга, возможно, для анализа аргументов командной строки или конфигурационных файлов.

### Parser.h
Объявление заголовочного файла `Parser.h`, который определяет функционал для разбора аргументов командной строки в контексте обработки изображений. Давайте разберем его по частям:

```cpp
#ifndef PARSER_H
#define PARSER_H
```
`#ifndef PARSER_H` / `#define PARSER_H` / `#endif` – эти директивы препроцессора используются для предотвращения многократного включения содержимого этого файла в один и тот же файл исходного кода. Если `PARSER_H` не определен, код между `#ifndef` и `#endif` включается и `PARSER_H` определяется, что предотвращает повторное включение.

```cpp
#include <string>
#include <vector>
```
`#include <string>` и `#include <vector>` – директивы включения заголовочных файлов стандартной библиотеки C++, необходимых для работы с классом `std::string` и шаблоном класса `std::vector` соответственно.

```cpp
namespace parse {
```
`namespace parse { ... }` – объявление пространства имен `parse`, которое используется для группировки функций и структур, связанных с разбором аргументов, чтобы избежать возможных конфликтов имен в разных частях программы.

```cpp
struct Token {
    std::string name;
    std::vector<std::string> args;
    void Clear();
    bool Empty() const;
};
```
Внутри пространства имен объявлена структура `Token`, которая представляет собой токен (или элемент) аргументов командной строки. Структура содержит два поля:
  - `std::string name` – строка для хранения имени токена.
  - `std::vector<std::string> args` – вектор строк для хранения аргументов, связанных с этим токеном.
  - Методы `void Clear();` и `bool Empty() const;` предназначены для очистки и проверки пустоты токена соответственно. Видимо, `Clear` служит для обнуления или очистки данных внутри `Token`, а `Empty` возвращает `true`, если токен не содержит данных.

```cpp
std::vector<Token> Parse(int argc, char* argv[]);
}  // namespace parse
```
`std::vector<Token> Parse(int argc, char* argv[]);` – объявление функции `Parse`, которая принимает количество аргументов `argc` и массив аргументов `argv[]`, переданных в командной строке, и возвращает вектор токенов. Эта функция является основной для разбора аргументов командной строки и их преобразования в структурированный формат токенов для дальнейшей обработки.

```cpp
#endif  // PARSER_H
```
**Файл `Parser.h` представляет собой интерфейс для модуля разбора аргументов командной строки, который может быть использован в программе для обработки изображений или в любой другой программе, где необходимо анализировать и обрабатывать входные данные командной строки.**

### Parser.cpp
**код представляет собой реализацию функционала, объявленного в заголовочном файле `Parser.h`, для разбора аргументов командной строки в структурированный формат.**

```cpp
#include "Parser.h"
#include "iostream"
```
- `#include "Parser.h"` включает объявления структуры `Token` и функции `Parse`, определенные ранее.
- `#include "iostream"` включает стандартную библиотеку ввода-вывода для работы с потоками ввода/вывода. (изб)

```cpp
namespace parse {
```
Весь код обернут в пространство имен `parse`, чтобы изолировать его от остальной части программы и избежать возможных конфликтов имен.

```cpp
bool Token::Empty() const {
    return name.empty() && args.empty();
}
void Token::Clear() {
    name.clear();
    args.clear();
}
```
 Методы структуры `Token`
- `bool Token::Empty() const` проверяет, пуст ли токен, то есть не содержит ли он имени и аргументов.
- `void Token::Clear()` очищает данные токена, удаляя все содержимое из `name` и `args`.

```cpp
std::vector<Token> Parse(int argc, char* argv[]) {
    std::vector<Token> tokens;
    Token curr;
    for (size_t i = 0; i < static_cast<size_t>(argc); ++i) {
        std::string str(argv[i]);
        if (i <= 2) {
            curr.name = str;
            tokens.push_back(curr);
            curr.Clear();
        } else {
            if (str.front() == '-') {
                if (!curr.Empty()) {
                    tokens.push_back(curr);
                    curr.Clear();
                }
                curr.name = str;
            } else {
                curr.args.push_back(str);
            }
        }
    }
    if (!curr.Empty()) {
        tokens.push_back(curr);
    }
    return tokens;
}
```
Функция `Parse`
Функция `Parse(int argc, char* argv[])` анализирует аргументы командной строки и преобразует их в вектор токенов.

**Работает она следующим образом:**
1. Создается вектор `tokens` для хранения результатов разбора.
2. Создается временный токен `curr` для сбора информации о текущем токене.
3. В цикле перебираются все аргументы командной строки. Аргументы преобразуются в строки C++ (`std::string`).
4. Первые три аргумента (`i <= 2`) считаются отдельными токенами с именами, но без аргументов.
5. Если строка начинается с `-`, это считается началом нового токена. Если у `curr` уже есть имя (токен не пуст), он добавляется в `tokens`, и `curr` очищается. Имя нового токена устанавливается.
6. Если строка не начинается с `-`, она считается аргументом для текущего токена и добавляется в его список аргументов.
7. После завершения цикла, если последний токен не пуст, он добавляется в вектор `tokens`.
8. Возвращается вектор токенов.

```cpp
}  // namespace parse
```
- Код делает предположение о том, что первые три аргумента являются отдельными токенами
- Токены без префикса `-` идентифицируются как аргументы предыдущего токена с префиксом.
**код представляет собой базовую реализацию парсера аргументов командной строки, которая может быть адаптирована или расширена в зависимости от требований конкретной задачи.**


## Reader
`Reader.cpp` и `Reader.h` - реализация и заголовочные файлы для классов или функций, отвечающих за чтение и изображений соответственно.

### Reader.h
**Код представляет собой объявление класса `Reader`**
```cpp
#ifndef READER_H
#define READER_H
```
Защита от многократного включения
- `#ifndef READER_H` / `#define READER_H` / `#endif` – эти директивы препроцессора препятствуют многократному включению одного и того же заголовочного файла, что предотвращает возможные ошибки компиляции, связанные с повторным объявлением классов или функций.

```cpp
#include <string>
#include <fstream>
#include <cerrno>
#include "Utils.h"
#include "image.h"
```
- `#include <string>` – включает стандартную библиотеку строк C++, необходимую для использования строковых объектов.
- `#include <fstream>` – включает библиотеку для работы с файловыми потоками, позволяя открывать файлы для чтения данных.
- `#include <cerrno>` – включает объявления для системных кодов ошибок.
- `#include "Utils.h"` и `#include "image.h"` – включает заголовочные файлы, содержащие вспомогательные функции и объявления, связанные с обработкой изображений, соответственно.

```cpp
namespace reading_and_writing {
class Reader {
```
Объявление класса `Reader`
- Класс `Reader` предназначен для чтения изображений из файлов. Он объявлен с одним конструктором и двумя методами.
```cpp
public:
    Reader(const std::string &path);  // NOLINT

    Image Read();
```
- `Reader(const std::string &path);` – конструктор класса, который принимает путь к файлу изображения. Комментарий `// NOLINT` используется для инструкции статическому анализатору кода игнорировать определенную проверку стиля или предупреждение для этой строки.
- `Image Read();` – метод, возвращающий объект `Image` после чтения изображения из файла. Этот метод, вероятно, использует внутреннее состояние объекта `Reader` (например, путь к файлу), чтобы открыть файл, прочитать данные изображения и преобразовать их в объект `Image`.

```cpp
private:
    std::string path_;

    size_t BytesToNum(unsigned char *bytes);
};
```
- В приватной секции класса объявлены:
    - `std::string path_;` – переменная для хранения пути к файлу изображения.
    - `size_t BytesToNum(unsigned char *bytes);` – приватный метод для преобразования байтов в числовое значение. Метод может использоваться для чтения числовых данных из файла изображения, например, для получения размеров изображения или других метаданных.

```cpp
const size_t GetPaddingSize(size_t width);
}  // namespace reading_and_writing
```
Вспомогательная функция- `const size_t GetPaddingSize(size_t width);` – глобальная функция в пространстве имен `reading_and_writing`, которая, вычисляет размер заполнения (padding) для строк изображения. В контекстах некоторых форматов изображений, таких как BMP, строки данных изображения могут требовать дополнения до определенной границы (например, кратной4 байтам).

```cpp
#endif  // READER_H
```
Класс `Reader` и вспомогательная функция `GetPaddingSize` предназначены для использования в процессе чтения изображений из файлов. Класс читает данные из файла, указанного при создании объекта, и предоставляет методы для преобразования этих данных в объект `Image`, который может быть использован далее в программе для обработки или отображения изображения.


### Reader.cpp
**Kод реализует класс `Reader`, который предназначен для чтения BMP изображений из файла в объект `Image`. Он содержится в файле `Reader.cpp` и использует объявления из `Reader.h` и `image.h`.**
```cpp
#include "Reader.h"
#include "image.h"
```
- `#include "Reader.h"` включает содержимое файла `Reader.h` в текущий файл исходного кода. `Reader.h` содержит объявления класса `Reader`, который используется для чтения данных изображения из файла.
- `#include "image.h"` включает содержимое файла `image.h` в текущий файл исходного кода. `image.h` предположительно содержит объявления, связанные с обработкой и представлением изображений, такие как класс `Image`

```cpp
reading_and_writing::Reader::Reader(const std::string &path) {
    path_ = path;
}
```
Конструктор класса `Reader` принимает путь к файлу изображения и сохраняет его в член класса `path_` для последующего использования при чтении файла.

```cpp
const size_t reading_and_writing::GetPaddingSize(size_t width) {
    return (image::utils::PADDING_SIZE - (width * image::utils::BYTES_PER_PIXEL) % image::utils::PADDING_SIZE) %
           image::utils::PADDING_SIZE;
}
```
Функция `GetPaddingSize` вычисляет размер заполнения (padding) для строки пикселей в BMP файле. BMP формат требует, чтобы размер каждой строки в байтах был кратен четырём. Функция использует размеры и константы, определённые в пространстве имен `image::utils`.

```cpp
size_t reading_and_writing::Reader::BytesToNum(unsigned char *bytes) {
    size_t number = *bytes;

    for (size_t i = 0; i < image::utils::SHIFT_VALUES.size(); ++i) {
        number += *(bytes + i + 1) << image::utils::SHIFT_VALUES[i];
    }
    return number;
}
```
Метод `BytesToNum` преобразует массив байтов в числовое значение `size_t`, используя сдвиги, заданные в `image::utils::SHIFT_VALUES`. Он предназначен для чтения числовых значений из заголовков BMP файла.

```cpp
Image reading_and_writing::Reader::Read() {
    unsigned char bmp_header[image::utils::BMP_HEADER_SIZE];
    unsigned char dib_header[image::utils::DIB_HEADER_SIZE];

    std::fstream img;
    img.open(path_, std::ios::in | std::ios::binary);
    if (!img.is_open()) {
        throw std::invalid_argument(std::string("Can't open file") + path_);
    }
    if (errno == EACCES) {
        throw std::invalid_argument(std::string("Permission denied to open file") + path_);
    }
    img.read(reinterpret_cast<char *>(bmp_header), image::utils::BMP_HEADER_SIZE);
    if (bmp_header[0] != image::utils::BMP_SIGNATURE[0] || bmp_header[1] != image::utils::BMP_SIGNATURE[1]) {
        throw std::invalid_argument(std::string("Not a BMP file") + path_);
    }
```
Метод `Read` открывает файл изображения для чтения в бинарном режиме, затем читает и проверяет заголовки BMP файла, чтобы убедиться, что файл действительно является BMP изображением. Метод читает размеры изображения из заголовка, создаёт объект `Image` с этими размерами, затем читает пиксели изображения, применяя необходимое заполнение, и возвращает объект `Image` с прочитанным изображением.

```cpp
    try {
        img.read(reinterpret_cast<char *>(dib_header), image::utils::DIB_HEADER_SIZE);
        size_t width = BytesToNum(dib_header + image::utils::WIDTH_POSITION);
        size_t height = BytesToNum(dib_header + image::utils::HEIGHT_POSITION);
        Image image(width, height);
        std::vector<std::vector<Color>> data(height);
        std::vector<Color> row(width);
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                unsigned char pix[image::utils::BYTES_PER_PIXEL];
                img.read(reinterpret_cast<char *>(pix), image::utils::BYTES_PER_PIXEL);
                row[j].SetColor(static_cast<uint8_t>(pix[0]), static_cast<uint8_t>(pix[1]),
                                static_cast<uint8_t>(pix[2]));
            }
            data[i] = row;
            img.ignore(GetPaddingSize(width));  // NOLINT
        }
        image = Image(data);
        img.close();
        return image;

    } catch (std::exception &e) {
        throw std::invalid_argument("Error reading file " + path_ + "\n" + static_cast<std::string>(e.what()));
    }
}
```
Обработка исключений
В методе `Read` используется конструкция `try-catch` для обработки исключений, связанных с ошибками чтения файла. Если во время чтения файла возникает ошибка, генерируется исключение `std::invalid_argument` с сообщением об ошибке.

**Подробное объяснение алгоритма обработки ошибок:**
- Kод читает изображение из файла и преобразует его в объект `Image`, представляющий изображение в программе.
    по шагам:
    1. **Чтение DIB заголовка**: Сначала код пытается прочитать DIB (Device Independent Bitmap) заголовок из файла. DIB заголовок содержит важную информацию об изображении, такую как его размеры (ширина и высота). Эти данные читаются в массив `dib_header`, после чего из этого массива извлекаются ширина и высота изображения с помощью функции `BytesToNum`.
    2. **Создание объекта `Image`**: После получения размеров изображения создается объект `Image` с этими размерами.

    3. **Инициализация структуры для хранения данных изображения**: Создается вектор `data`, состоящий из векторов объектов `Color`, который будет хранить цвет каждого пикселя изображения. Каждый вектор `Color` представляет собой одну строку изображения.

    4. **Чтение пикселей изображения**: Во вложенных циклах происходит чтение каждого пикселя изображения. Для каждого пикселя читается фиксированное количество байтов, равное `image::utils::BYTES_PER_PIXEL` (обычно это 3 байта для формата RGB). Считанные байты представляют цвет пикселя (красный, зеленый и синий компоненты). После чтения эти значения присваиваются соответствующему пикселю в строке `row`.

    5. **Пропуск дополнения**: BMP формат требует, чтобы каждая строка пикселей была выровнена до размера, кратного 4 байтам. После чтения каждой строки пикселей код пропускает ненужные байты дополнения, используя метод `ignore` потока `img`. Размер пропускаемого дополнения определяется функцией `GetPaddingSize`.

    6. **Заполнение данных изображения**: После чтения всех пикселей строки `row` добавляется в вектор `data`, представляющий собой все данные изображения.

    7. **Создание объекта `Image` с данными**: Создается новый объект `Image`, инициализированный считанными данными изображения.

    8. **Закрытие файла**: Файл изображения закрывается.

    9. **Возвращение объекта `Image`**: Возвращается объект `Image`, содержащий все данные считанного изображения.

    В случае возникновения исключения в процессе чтения файла (например, если файл не может быть открыт или прочитан), исключение перехватывается в блоке `catch`, и генерируется новое исключение `std::invalid_argument` с сообщением об ошибке, содержащим путь к файлу и описание исходной ошибки. Это исключение затем может быть обработано вызывающим кодом.


**Kод представляет собой эффективную реализацию чтения BMP файлов, используя детальное понимание структуры BMP файла и обеспечивая надёжную обработку ошибок и исключений.**


## Writer
`Writer.cpp` и `Writer.h` - реализация и заголовочные файлы для классов или функций, отвечающих за запись изображений соответственно.

### Writer.h
```cpp
#ifndef WRITER_H
#define WRITER_H
```
Эти строки защищают заголовочный файл от повторного включения. Если `WRITER_H` уже определен, содержимое файла не будет обработано повторно. Это предотвращает проблемы при компиляции, связанные с многократным включением одного и того же заголовочного файла.

```cpp
#include <fstream>
#include <string>
#include <algorithm>
#include "image.h"
#include "Reader.h"
#include <utility>
#include "Utils.h"
```
Здесь подключаются стандартные библиотеки и пользовательские заголовочные файлы, необходимые для работы класса `Writer`. Например, `<fstream>` используется для работы с файлами, `<string>` для работы со строками, а `"image.h"` и `"Reader.h"` содержат определения, связанные с обработкой изображений.

```cpp
namespace reading_and_writing {
class Writer {
```
Объявление класса Writer
Класс `Writer` объявлен в пространстве имен `reading_and_writing`, что помогает избежать конфликтов имен в больших проектах.

```cpp
public:
    Writer(std::string path);  // NOLINT
    void Write(const Image& image);
```
Конструктор класса принимает путь к файлу (`std::string path`) в качестве аргумента. Этот путь используется для открытия файла и записи изображения. `NOLINT` возможно указывает на то, что в этой строке не следует проверять стиль кода линтерами.
Метод `Write` принимает константную ссылку на объект `Image` и записывает его содержимое в файл. Это основной метод класса, предназначенный для выхода информации.

```cpp
private:
    void WriteBMPHeader(unsigned char* bmp_header, size_t size);
    void WriteDIBHeader(unsigned char* dib_header, size_t width, size_t height);

    template <typename T>
    void NumToBytes(T num, unsigned char* bytes);

    std::string path_;
};
}  // namespace reading_and_writing
```
Приватные методы
Эти методы используются внутри класса для записи различных частей BMP файла, таких как заголовок BMP, заголовок DIB и преобразование чисел в массив байтов соответственно.
Это переменная экземпляра, хранящая путь к файлу, в который будет производиться запись.

```cpp
#endif  // WRITER_H
```
**Kласс `Writer` предназначен для записи изображений, в формате BMP. Он предоставляет интерфейс для записи объектов `Image` в файл, используя заданный путь.**


### Writer.cpp
**код реализует функциональность класса `Writer`, который был объявлен в `Writer.h`, для записи изображений в формате BMP.**

```cpp
#include "Writer.h"
```
Подключение заголовочного файла `Writer.h` к текущему файлу

```cpp
reading_and_writing::Writer::Writer(std::string path) : path_(std::move(path)) {
}
```
Конструктор класса `Writer` инициализирует член `path_`, который хранит путь к файлу, в который будет записано изображение. Использование `std::move` предотвращает ненужное копирование строки, передавая владение строкой `path_`.

```cpp
template <typename T>
void reading_and_writing::Writer::NumToBytes(T num, unsigned char* bytes) {
    *bytes = num;
    for (size_t i = 0; i < image::utils::SHIFT_VALUES.size(); ++i) {
        *(bytes + i + 1) = (num >> image::utils::SHIFT_VALUES[i]) & 0xFF;  // NOLINT
    }
}
```
Этот шаблонный метод преобразует число `num` в массив байтов `bytes`. Используется для записи числовых значений в заголовки BMP и DIB. В цикле происходит побитовый сдвиг `num` на значения из `image::utils::SHIFT_VALUES` и маскирование, чтобы получить отдельные байты числа.

```cpp
void reading_and_writing::Writer::WriteBMPHeader(unsigned char* bmp_header, size_t size) {
    bmp_header[image::utils::FORMAT_FIRST_POSITION] = image::utils::BMP_SIGNATURE[0];
    bmp_header[image::utils::FORMAT_SECOND_POSITION] = image::utils::BMP_SIGNATURE[1];
    NumToBytes(size, bmp_header + image::utils::SIZE_POSITION);
    bmp_header[image::utils::PIXS_ARRAY_OFFSET_POSITION] =
        image::utils::BMP_HEADER_SIZE + image::utils::DIB_HEADER_SIZE;
}
```
Этот метод записывает заголовок BMP файла в массив `bmp_header`. Он устанавливает сигнатуру файла, размер файла и смещение до начала массива пикселей.

```cpp
void reading_and_writing::Writer::WriteDIBHeader(unsigned char* dib_header, size_t width, size_t height) {
    dib_header[image::utils::DIB_HEADER_SIZE_POSITION] = image::utils::DIB_HEADER_SIZE;
    NumToBytes(width, dib_header + image::utils::WIDTH_POSITION);
    NumToBytes(height, dib_header + image::utils::HEIGHT_POSITION);
    dib_header[image::utils::CNT_OF_PLANES_POSITION] = image::utils::CNT_OF_PLANES;
    dib_header[image::utils::BITS_PER_PIXEL_POSITION] = image::utils::BITS_PER_PIXEL;
}
```
Этот метод записывает DIB (Device Independent Bitmap) заголовок, который содержит основную информацию об изображении, такую как размеры, количество бит на пиксель и т.д.

```cpp
void reading_and_writing::Writer::Write(const Image& image) {
    std::ofstream img;
    img.open(path_, std::ios::out | std::ios::binary);
    if (!img.is_open()) {
        throw std::invalid_argument(std::string("Can't open file") + path_);
    }
    const size_t size = image::utils::BMP_HEADER_SIZE + image::utils::DIB_HEADER_SIZE +
                        image.GetWidth() * image.GetHeight() * image::utils::BYTES_PER_PIXEL +
                        GetPaddingSize(image.GetWidth()) * image.GetHeight();
    unsigned char bmp_header[image::utils::BMP_HEADER_SIZE] = {};
    std::fill(bmp_header, bmp_header + image::utils::BMP_HEADER_SIZE, 0);
    WriteBMPHeader(bmp_header, size);

    unsigned char dib_header[image::utils::DIB_HEADER_SIZE] = {};
    std::fill(dib_header, dib_header + image::utils::DIB_HEADER_SIZE, 0);
    WriteDIBHeader(dib_header, image.GetWidth(), image.GetHeight());

    img.write(reinterpret_cast<char*>(bmp_header), image::utils::BMP_HEADER_SIZE);
    img.write(reinterpret_cast<char*>(dib_header), image::utils::DIB_HEADER_SIZE);

    unsigned char empty_pix[image::utils::BYTES_PER_PIXEL] = {0, 0, 0};
    for (size_t i = 0; i < image.GetHeight(); i++) {
        for (size_t j = 0; j < image.GetWidth(); j++) {
            auto blue = static_cast<unsigned char>(image.GetPixel(i, j).blue);
            auto green = static_cast<unsigned char>(image.GetPixel(i, j).green);
            auto red = static_cast<unsigned char>(image.GetPixel(i, j).red);
            unsigned char pix[] = {blue, green, red};
            img.write(reinterpret_cast<char*>(pix), image::utils::BYTES_PER_PIXEL);
        }
        img.write(reinterpret_cast<char*>(empty_pix), GetPaddingSize(image.GetWidth()));  // NOLINT
    }
    img.close();
```
Метод `Write` открывает файл с использованием пути `path_` для бинарной записи. Если файл не может быть открыт, выбрасывается исключение. Затем метод вычисляет размер файла и заполняет заголовки BMP и DIB. После этого записывает эти заголовки в файл.

Далее, в цикле, метод записывает каждый пиксель изображения в файл. Для каждого пикселя сначала происходит преобразование его составляющих (синего, зеленого, красного) в формат BMP, затем запись в файл. После записи всех пикселей строки добавляется паддинг (дополнение до размера, кратного4 байтам), если это необходимо.
**Подробное описание работы функции:**
1. **Открытие файла для записи**: Создается объект `std::ofstream` с именем `img`. Затем вызывается метод `open` с путем `path_` и флагами `std::ios::out | std::ios::binary` для открытия файла на запись в бинарном режиме.

2. **Проверка успешности открытия файла**: Если файл не удалось открыть, выбрасывается исключение `std::invalid_argument` с сообщением, указывающим на проблему с открытием файла.

3. **Вычисление размера файла**: Вычисляется размер файла на основе размеров заголовков BMP и DIB, ширины и высоты изображения, количества байтов на пиксель и размера дополнения (паддинга) для каждой строки пикселей.

4. **Создание и запись заголовка BMP**: Создается массив `bmp_header` для хранения заголовка BMP файла, затем заполняется нулями с помощью функции `std::fill`. Метод `WriteBMPHeader` вызывается для записи информации в заголовок BMP, который затем записывается в файл с помощью метода `write`.

5. **Создание и запись заголовка DIB**: Создается массив `dib_header` для хранения заголовка DIB, который также заполняется нулями. Метод `WriteDIBHeader` вызывается для записи информации в заголовок DIB, который затем записывается в файл.

6. **Запись пикселей изображения**: Во вложенных циклах происходит запись каждого пикселя изображения в файл. Компоненты цвета (синий, зеленый и красный) извлекаются из пикселя и записываются в массив `pix`, который затем записывается в файл. Каждый пиксель записывается в виде 3 байтов (по одному байту на каждый цвет).

7. **Запись дополнения**: После записи каждой строки пикселей добавляется паддинг (дополнение до размера, кратного 4 байтам), если это необходимо. Размер паддинга определяется функцией `GetPaddingSize`, а сам паддинг записывается в виде массива нулевых байтов `empty_pix`.

8. **Закрытие файла**: После записи всего изображения файл закрывается с помощью метода `close`.

В результате выполнения функции `Write` объект `Image` записывается в файл в формате BMP. Эта функция предоставляет интерфейс для сохранения объектов `Image` в файлы, используя заданный путь и формат.

**Kод представляет собой реализацию записи изображения в формате BMP. Он включает в себя создание и запись заголовков файла и информации об изображении, а также самого изображения по пикселям. Это достаточно низкоуровневая операция, требующая точного соответствия формату BMP.**


## Filter
`filter.cpp` и `filter.h` - реализация и заголовочный файл для классов или функций, реализующих различные фильтры для изображений.

### filter.h
**Объявление базового класса `Filter` и нескольких производных от него классов, предназначенных для применения различных фильтров к изображениям. Используется для описания интерфейсов и реализаций фильтров изображений.**

```cpp
#ifndef FILTER_H
#define FILTER_H
```
Эти директивы предотвращают повторное включение содержимого файла `filter.h` при компиляции, что может произойти, если он включается из разных мест в проекте.

```cpp
#include <algorithm>
#include <memory>
#include <vector>

#include "image.h"
#include "Parser.h"
```
Подключаются заголовочные файлы стандартной библиотеки C++ и пользовательские заголовочные файлы. Это необходимо для работы с алгоритмами, умными указателями, контейнерами, а также с классами `Image` и `Parser`, которые, предоставляют функциональность для работы с изображениями и разбора входных данных соответственно.

```cpp
namespace filters {
class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;
    virtual Image Apply(const Image& image) const = 0;

protected:
    template <typename T>
    std::vector<T> GetPixel(const std::vector<std::vector<T>>& matrix, const Image& image, size_t, size_t y) const;
};
```
`Filter` — это базовый класс для всех фильтров. Конструктор и деструктор объявлены как `default`, что означает использование стандартных реализаций. Метод `Apply` — это чисто виртуальный метод, который должен быть переопределен в производных классах для применения фильтра к изображению. Также имеется защищенный шаблонный метод `GetPixel`, предназначенный для использования в производных классах.

**Производные классы Filter**
Каждый из этих классов представляет собой конкретный фильтр (например, увеличение резкости, обрезка, преобразование в градации серого, негатив, обнаружение границ). В этих классах переопределен метод `Apply` для реализации соответствующего преобразования изображения

```cpp
class Sharpening : public Filter {  // NOLINT
public:
    Image Apply(const Image& image) const override;
};
```

```cpp
class Crop : public Filter {
public:
    Crop(size_t width, size_t height);
    Image Apply(const Image& image) const override;

private:
    size_t width_;
    size_t height_;
};
```

```cpp
class Grayscale : public Filter {
public:
    Image Apply(const Image& image) const override;
};
```

```cpp
class Negative : public Filter {
public:
    Image Apply(const Image& image) const override;
};
```

```cpp
class EdgeDetection : public Filter {
public:
    EdgeDetection(double threshold);  // NOLINT

    Image Apply(const Image& image) const override;  // NOLINT

private:
    const double threshold_ = 0;
};
```

```cpp
uint8_t MyClamp(int color, uint8_t max_color);

std::unique_ptr<filters::Filter> CreateFilter(const parse::Token& name);
```
**Вспомогательные функции и методы**
`MyClamp` — функция для ограничения значения цвета заданными границами.
`CreateFilter` — функция, вероятно, создает экземпляр фильтра на основе некоторого токена, полученного в результате разбора входных данных.

```cpp
}  // namespace filters

#endif  // FILTER_H
```
**Kод описывает систему фильтров для применения к изображениям. Базовый класс `Filter` определяет интерфейс, который должны реализовать все конкретные фильтры, а производные классы реализуют конкретные виды преобразований. Это позволяет легко расширять функциональность приложения за счет добавления новых фильтров.**

### filter.cpp

**В файле определены различные классы фильтров, а также функции для их применения к изображению:**
   - `filters::Sharpening`: Фильтр резкости. Применяет матрицу свертки к изображению для увеличения резкости.   - `filters::EdgeDetection`: Фильтр обнаружения границ. Применяет матрицу свертки для выделения границ объектов на изображении с заданным порогом. - `filters::Crop`: Фильтр обрезки. Обрезает изображение до указанных ширины и высоты.
   - `filters::Grayscale`: Фильтр оттенков серого. Преобразует цветное изображение в черно-белое, используя взвешенное среднее значений RGB.
   - `filters::Negative`: Фильтр негатива. Инвертирует цвета изображения (вычитает значения RGB из максимального значения цвета).

**Определены вспомогательные функции:**
- `filters::Filter::GetPixel`: Используется для получения значения пикселя после применения матрицы свертки.
- `filters::MyClamp`: Ограничивает значение цвета в заданном диапазоне (обычно от 0 до 255).

**Также определена функция для создания фильтра:**
- Функция `filters::CreateFilter` принимает токен (содержащий имя фильтра и аргументы, связанные с фильтром) и создает соответствующий объект фильтра. Эта функция проверяет, что аргументы для каждого фильтра корректны и создает объекты фильтров с помощью `std::make_unique`. Если указано неизвестное имя фильтра, функция генерирует исключение `std::invalid_argument`.

**Разберем код подробнее:**

```cpp
#include "filter.h"
#include "Utils.h"
#include "iostream"
```
Подключение заголовочных файлов `filter.h` и `Utils.h`, которые содержат объявления классов и функций, необходимых для работы программы. Также происходит включение стандартной библиотеки ввода-вывода `iostream`, котор позволяет использовать функции ввода и вывода данных из консоли.

```cpp
template <typename T>
std::vector<T> filters::Filter::GetPixel(const std::vector<std::vector<T>>& matrix, const Image& image, size_t x,
                                         size_t y) const {
    T blue = 0;
    T green = 0;
    T red = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.front().size(); ++j) {
            blue += image
                        .GetPixel(std::clamp(x + i - 1, static_cast<size_t>(0), image.GetHeight() - 1),
                                  std::clamp(y + j - 1, static_cast<size_t>(0), image.GetWidth() - 1))
                        .blue *
                    matrix[i][j];
            red += image
                       .GetPixel(std::clamp(x + i - 1, static_cast<size_t>(0), image.GetHeight() - 1),
                                 std::clamp(y + j - 1, static_cast<size_t>(0), image.GetWidth() - 1))
                       .red *
                   matrix[i][j];
            green += image
                         .GetPixel(std::clamp(x + i - 1, static_cast<size_t>(0), image.GetHeight() - 1),
                                   std::clamp(y + j - 1, static_cast<size_t>(0), image.GetWidth() - 1))
                         .green *
                     matrix[i][j];
        }
    }
    return {blue, green, red};
}
```
**Метод `GetPixel` класса `filters::Filter`, который принимает матрицу значений типа `T`, объект изображения `Image`, а также координаты `x` и `y`. В методе происходит вычисление нового пикселя изображения, используя весовую матрицу `matrix` для применения фильтра.**

1. Инициализируются переменные `blue`, `green` и `red` для хранения суммарных значений цветовых каналов пикселя.
2. Далее происходит двойной цикл `for`, перебирающий элементы матрицы `matrix`.
3. Для каждого элемента матрицы вычисляются новые значения цветовых каналов `blue`, `green` и `red` путем умножения значения пикселя изображения на соответствующий элемент матрицы и суммирования результатов.
4. При этом координаты пикселя изображения корректируются с помощью `std::clamp` для обработки граничных случаев (например, когда пиксель находится на краю изображения).
5. Наконец, метод возвращает вектор из значений `blue`, `green` и `red`, представляющих новый пиксель изображения, обработанный фильтром.

**Данный метод выполняет операцию применения фильтра к пикселю изображения на основе весовой матрицы `matrix` и возвращает новое значение цветовых каналов для этого пикселя.**

```cpp
uint8_t filters::MyClamp(int color, uint8_t max_color = 255) {  // NOLINT
    if (color < 0) {
        return 0;
    } else if (color > max_color) {
        return max_color;
    }
    return static_cast<uint8_t>(color);
}
```
**Функция `MyClamp` в пространстве имен `filters`, которая выполняет операцию "зажатия" (clamping) значения `color` в диапазоне от 0 до `max_color`.**

1. Функция принимает два аргумента: `color` типа `int` и `max_color` типа `uint8_t` со значением по умолчанию 255.
2. Если значение `color` меньше 0, функция возвращает 0, чтобы не допустить отрицательные значения.
3. Если значение `color` больше `max_color`, то функция возвращает `max_color`, чтобы не превысить максимальное значение цвета.
4. В противном случае, функция преобразует значение `color` в тип `uint8_t` (беззнаковый 8-битный целочисленный тип) и возвращает его.

**Функция `MyClamp` обеспечивает ограничение значения `color` в интервале от 0 до `max_color`, чтобы гарантировать корректность цветового представления и предотвратить переполнение или отрицательные значения.**

```cpp
Image filters::Sharpening::Apply(const Image& image) const {
    std::vector<std::vector<Color>> new_data(image.GetHeight(), std::vector<Color>(image.GetWidth()));
    const std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            int sum_blue = 0;
            int sum_green = 0;
            int sum_red = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    size_t i = std::clamp(static_cast<int>(y) + dy, 0, static_cast<int>(image.GetHeight()) - 1);
                    size_t j = std::clamp(static_cast<int>(x) + dx, 0, static_cast<int>(image.GetWidth()) - 1);

                    Color pixel = image.GetPixel(i, j);
                    int kernel_value = matrix[dy + 1][dx + 1];

                    sum_blue += pixel.blue * kernel_value;
                    sum_green += pixel.green * kernel_value;
                    sum_red += pixel.red * kernel_value;
                }
            }

            Color& new_pixel = new_data[y][x];
            new_pixel.blue = MyClamp(sum_blue);
            new_pixel.green = MyClamp(sum_green);
            new_pixel.red = MyClamp(sum_red);
        }
    }

    return {new_data};
}
```
**Kод реализует метод `Apply` класса `filters::Sharpening`, который применяет фильтр увеличения резкости к изображению. Вот шаг за шагом, что происходит в коде:**
1. Создается двумерный вектор `new_data` для хранения пикселей обработанного изображения. Размеры `new_data` соответствуют размерам исходного изображения `image`.
2. Задается матрица `matrix` размером 3x3, которая используется для фильтра увеличения резкости. Элементы матрицы определяют, как исходные пиксели будут комбинироваться для получения нового значения пикселя.
3. В двойном цикле `for` перебираются все пиксели исходного изображения по их координатам `x` и `y`. Для каждого пикселя:
   - Инициализируются переменные `sum_blue`, `sum_green` и `sum_red` для хранения суммарных значений цветовых компонентов, которые будут вычислены с использованием матрицы свертки.
   - Во вложенных циклах `for` перебираются соседние пиксели относительно текущего пикселя `x`, `y`, используя смещения `dx` и `dy` от -1 до 1. Для каждого соседнего пикселя:
     - Рассчитывается его позиция `(i, j)` с учетом границ изображения.
     - Получается значение пикселя `pixel` из исходного изображения.
     - Из матрицы `matrix` выбирается соответствующий весовой коэффициент `kernel_value`.
     - Суммируются произведения значений цветовых компонентов пикселя на весовой коэффициент, обновляя `sum_blue`, `sum_green` и `sum_red`.

4. Для каждого цветового канала нового пикселя (`new_pixel`) значения `sum_blue`, `sum_green` и `sum_red` корректируются функцией `MyClamp`, чтобы гарантировать, что они находятся в допустимом диапазоне (от 0 до максимального значения цвета). Это предотвращает переполнение и обеспечивает корректное отображение цветов.
5. Создается и возвращается новый объект `Image`, инициализированный обработанными данными `new_data`.

В результате, метод `Apply` применяет фильтр увеличения резкости к исходному изображению, усиливая границы и контрастные переходы, что делает изображение более четким.

```cpp
filters::EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {
}  // NOLINT
```
Определяется конструктор класса `filters::EdgeDetection`, который принимает один параметр `threshold` типа `double`. Этот конструктор инициализирует член данных `threshold_` класса значением, переданным в параметре `threshold`. Это означает, что при создании объекта класса `EdgeDetection`, ему можно задать пороговое значение для обнаружения границ в изображении. Комментарий `// NOLINT` указывает на то, что в этой строке кода анализатор кода (линтер) не должен выдавать предупреждений или ошибок.

```cpp
Image filters::EdgeDetection::Apply(const Image& image) const {
    std::vector<std::vector<double>> gs_data(image.GetHeight(), std::vector<double>(image.GetWidth()));
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            Color old_value = image.GetPixel(i, j);
            double pixel = 0.299f * old_value.red + 0.587f * old_value.green + 0.114f * old_value.blue;  // NOLINT
            gs_data[i][j] = pixel;
        }
    }
    const std::vector<std::vector<double>> matrix = {{0.0f, -1.0f, 0.0f}, {-1.0f, 4.0f, -1.0f}, {0.0f, -1.0f, 0.0f}};
    std::vector<std::vector<double>> edge_data(image.GetHeight(), std::vector<double>(image.GetWidth(), 0));

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            double sum_color = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    size_t i = std::clamp(static_cast<int>(y) + dy, 0, static_cast<int>(image.GetHeight()) - 1);
                    size_t j = std::clamp(static_cast<int>(x) + dx, 0, static_cast<int>(image.GetWidth()) - 1);

                    double kernel_value = matrix[dy + 1][dx + 1];
                    sum_color += gs_data[i][j] * kernel_value;
                }
            }
            edge_data[y][x] = sum_color;
        }
    }
    Image result(image.GetWidth(), image.GetHeight());
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Color new_color = (edge_data[y][x] > threshold_)  // NOLINT
                                  ? Color(image::utils::MAX_COLOR, image::utils::MAX_COLOR, image::utils::MAX_COLOR)
                                  : Color(0, 0, 0);
            result.SetPixel(y, x, new_color);  // NOLINT
        }
    }
    return result;
}
```
**Kод реализует метод `Apply` в классе `filters::EdgeDetection`, который применяет фильтр обнаружения краев к изображению. Вот шаги, которые он выполняет:**
1. Вначале создается двумерный вектор `gs_data` для хранения изображения в оттенках серого, размер которого соответствует размеру входного изображения. Затем для каждого пикселя исходного изображения вычисляется его яркость путем линейной комбинации его красного, зеленого и синего компонентов с весами 0.299, 0.587 и 0.114 соответственно. Эти значения записываются в `gs_data`.
2. Задается матрица `matrix` для выделения краев. Эта матрица представляет собой оператор, который усиливает резкие переходы интенсивности и тем самым помогает выявить края в изображении.
3. Создается вектор `edge_data` для хранения данных после применения матрицы свертки. Для каждого пикселя изображения в оттенках серого вычисляется свертка с использованием матрицы `matrix`, путем суммирования произведений значений соответствующих пикселей из `gs_data` и весов из `matrix`. Результаты записываются в `edge_data`.
4. На основе полученных данных создается новое изображение `result` того же размера, что и исходное. Для каждого пикселя в `edge_data` проверяется, превышает ли его значение заданный порог `threshold_`. Если да, пиксель в новом изображении делается белым (максимальное значение интенсивности для всех цветовых каналов), в противном случае — черным. Это позволяет выделить края, превышающие пороговое значение, на фоне остальной части изображения.
5. Возвращается новое изображение `result`, в котором края выделены в соответствии с заданным порогом.

**Mетод `Apply` обнаруживает края в изображении, преобразуя его в оттенки серого, применяя матрицу свертки для выделения краев и используя пороговую обработку для создания конечного изображения, где края отличаются от остальных участков.**

```cpp
filters::Crop::Crop(size_t width, size_t height) : width_(width), height_(height) {
}
Image filters::Crop::Apply(const Image& image) const {
    Image new_image(std::min(width_, image.GetWidth()), std::min(height_, image.GetHeight()));
    for (size_t i = image.GetHeight() - std::min(height_, image.GetHeight()); i < image.GetHeight(); ++i) {
        std::vector<Color> row(std::min(width_, image.GetWidth()));
        for (size_t j = 0; j < std::min(width_, image.GetWidth()); ++j) {
            new_image.SetPixel(i - (image.GetHeight() - std::min(height_, image.GetHeight())), j, image.GetPixel(i, j));
        }
    }
    return new_image;
}
```
**Kод реализует класс `filters::Crop` и его методы. Класс `filters::Crop` предназначен для обрезки изображений. Вот подробное объяснение того, что происходит в коде:**

1. Конструктор класса `filters::Crop` принимает два параметра: `width` и `height` типа `size_t`, которые определяют ширину и высоту области обрезки. Эти значения сохраняются в члены данных `width_` и `height_`.
2. Метод `Apply` принимает ссылку на константный объект `Image` и возвращает новый объект `Image` после обрезки. В этом методе происходит следующее:
   - Создается новый объект `Image` с размерами, равными минимальным значениям между заданными шириной/высотой и шириной/высотой исходного изображения.
   - Затем во внешнем цикле `for` перебираются строки исходного изображения от `image.GetHeight() - std::min(height_, image.GetHeight())` до `image.GetHeight()`. Таким образом, обрезка происходит снизу изображения.
   - Во внутреннем цикле `for` перебираются столбцы исходного изображения от 0 до `std::min(width_, image.GetWidth())`. Таким образом, обрезка происходит слева изображения.
   - Для каждой пары индексов `(i, j)` копируется пиксель из исходного изображения в новое изображение с соответствующим смещением строки.
   - В конце метод возвращает новое обрезанное изображение.

**Mетод `Apply` класса `filters::Crop` обрезает исходное изображение до указанных размеров, начиная с левого нижнего угла, и возвращает новое обрезанное изображение.**

```cpp
Image filters::Grayscale::Apply(const Image& image) const {
    Image result = image;
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            auto& pixel = result.GetPixel(i, j);
            uint8_t gray =
                static_cast<uint8_t>(0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue);  // NOLINT
            pixel = Color(gray, gray, gray);
        }
    }
    return result;
}
```
Kод описывает метод `Apply` класса `filters::Grayscale`, который преобразует цветное изображение в оттенки серого (градации серого). Вот шаг за шагом, что происходит в данном методе:

1. Создается новый объект `Image` с именем `result`, который является копией исходного изображения `image`. Это делается для того, чтобы модифицировать и возвращать новое изображение, не изменяя оригинальное.
2. С помощью двух вложенных циклов `for` происходит итерация по всем строкам (по индексу `i`) и столбцам (по индексу `j`) изображения.
3. **Преобразование пикселя в оттенок серого:**
   - Для каждой пары индексов `(i, j)` получается ссылка на текущий пиксель `pixel` в изображении `result`.
   - Используя коэффициенты, соответствующие восприятию яркости человеческим глазом (0.299 для красного, 0.587 для зеленого и 0.114 для синего), вычисляется значение яркости `gray`. Вычисление производится путем умножения каждого цветового компонента на его коэффициент и последующего суммирования результатов.
   - Полученное значение `gray` затем приводится к типу `uint8_t` (беззнаковое целое 8-битное), чтобы соответствовать диапазону значений цветового компонента изображения.
   - Сформированный цвет `Color(gray, gray, gray)` устанавливается для текущего пикселя, что приводит к тому, что все три цветовых компонента (красный, зеленый и синий) имеют одинаковую интенсивность, создавая эффект оттенка серого.
4. После обработки всех пикселей, изображение `result`, теперь в оттенках серого, возвращается из метода.

Комментарий `// NOLINT` используется для того, чтобы указать статическому анализатору кода (линтеру) игнорировать предупреждения на этой строке.

```cpp
Image filters::Negative::Apply(const Image& image) const {
    Image result = image;
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            auto& pixel = result.GetPixel(i, j);
            pixel.red = 255 - pixel.red;      // NOLINT
            pixel.green = 255 - pixel.green;  // NOLINT
            pixel.blue = 255 - pixel.blue;    // NOLINT
        }
    }
    return result;
}
```
**Kод является реализацией метода `Apply` класса `Negative`, который принадлежит пространству имен `filters`. Этот метод применяет фильтр негатива к изображению. Вот пошаговое объяснение того, что происходит в коде:**
1. **Создание копии исходного изображения**:
    - `Image result = image;`
    Эта строка создаёт новый объект `result`, который является копией переданного изображения `image`. Копирование необходимо, чтобы не изменять исходное изображение, а работать с его копией.
2. **Перебор всех пикселей изображения**:
    - Внешний цикл `for (size_t i = 0; i < image.GetHeight(); ++i)` перебирает все строки (высоту) изображения.
    - Внутренний цикл `for (size_t j = 0; j < image.GetWidth(); ++j)` перебирает все столбцы (ширину) каждой строки.
    - Вместе эти два цикла позволяют обойти каждый пиксель изображения.
3. **Применение фильтра негатива к каждому пикселю**: - `auto& pixel = result.GetPixel(i, j);`
    Для каждого пикселя по координатам `(i, j)` получаем ссылку на объект `pixel`, который содержит компоненты цвета (красный, зелёный, синий).

    - `pixel.red = 255 - pixel.red;`
    - `pixel.green = 255 - pixel.green;`
    - `pixel.blue = 255 - pixel.blue;` Для каждой компоненты цвета пикселя (красной, зелёной, синей) значение инвертируется. Формула `255 - pixel.<color>` обращает значение цвета. Например, если красная компонента имела значение 0 (полностью черная), она станет 255 (полностью красная), и наоборот. Это и создаёт эффект негатива, когда тёмные цвета становятся светлыми, а светлые — тёмными.
4. **Возврат обработанного изображения**:
    - После обработки всех пикселей возвращается изменённое изображение `result`, которое теперь содержит эффект негатива.

**Mетод `Apply` преобразует каждый пиксель исходного изображения в его негативный аналог, сохраняя размер и форму изображения, изменяя только его цвета.**

```cpp
std::unique_ptr<filters::Filter> filters::CreateFilter(const parse::Token& token) {
    const std::string& filter = token.name;
    if (filter == "-sharp") {
        if (!token.args.empty()) {
            throw std::invalid_argument("The sharpening filter does not accept any arguments");
        }
        return std::make_unique<filters::Sharpening>();
    } else if (filter == "-crop") {
        if (token.args.size() != 2) {
            throw std::invalid_argument("The crop filter requires exactly two arguments: width and height");
        }
        try {
            size_t width = std::stoull(token.args[0]);
            size_t height = std::stoull(token.args[1]);
            return std::make_unique<filters::Crop>(width, height);
        } catch (const std::exception& e) {
            throw std::invalid_argument("Invalid argument for crop filter. Both width and height need to be numbers.");
        }
    } else if (filter == "-gs") {
        if (!token.args.empty()) {
            throw std::invalid_argument("The grayscale filter does not accept any arguments");
        }
        return std::make_unique<filters::Grayscale>();
    } else if (filter == "-neg") {
        if (!token.args.empty()) {
            throw std::invalid_argument("The negative filter does not accept any arguments");
        }
        return std::make_unique<filters::Negative>();
    } else if (filter == "-edge") {
        if (token.args.size() != 1) {
            throw std::invalid_argument("The edge detection filter requires exactly one argument: threshold");
        }
        try {
            double threshold = std::stod(token.args[0]);
            return std::make_unique<filters::EdgeDetection>(image::utils::MAX_COLOR * threshold);
        } catch (const std::exception& e) {
            throw std::invalid_argument("Invalid argument for edge detection filter. Threshold needs to be a number.");
        }
    } else {
        throw std::invalid_argument("Unknown filter: " + filter);
    }
}
```
**Kод представляет собой реализацию функции `CreateFilter` в пространстве имен `filters`. Эта функция создаёт и возвращает умный указатель `std::unique_ptr` на объект фильтра в зависимости от переданного токена.**

#### Вот пошаговое объяснение того, что происходит в коде:

1. **Извлечение имени фильтра из токена**:
    - `const std::string& filter = token.name;`
    Здесь извлекается имя фильтра из объекта `token` и сохраняется в переменную `filter`.

2. **Проверка и создание объекта фильтра в зависимости от имени**:
    - `if (filter == "-sharp") { ... } else if (filter == "-crop") { ... } else if (filter == "-gs") { ... } else if (filter == "-neg") { ... } else if (filter == "-edge") { ... } else { ... }`
    Здесь происходит проверка имени фильтра и выполнение соответствующих действий в зависимости от его значения.

3. **Создание объекта фильтра и возврат умного указателя**:
    - `return std::make_unique<filters::Sharpening>();`
    В случае, если имя фильтра совпадает с определённым, создаётся объект соответствующего фильтра с помощью функции `std::make_unique`, и возвращается умный указатель `std::unique_ptr` на этот объект.

4. **Обработка ошибок и выброс исключений**:
    - Внутри каждого блока `if` проверяются дополнительные условия, связанные с аргументами фильтра.
    - Если условия не выполняются, выбрасывается исключение `std::invalid_argument` с соответствующим сообщением об ошибке.

5. **Обработка неизвестного фильтра**:
    - В блоке `else` выбрасывается исключение `std::invalid_argument` с сообщением "Unknown filter: " и именем неизвестного фильтра.

#### Общая структура
- `std::unique_ptr<filters::Filter>`: Функция возвращает уникальный указатель на объект типа `Filter`. Использование уникального указателя обеспечивает автоматическое управление памятью, предотвращая утечки памяти и являясь частью идиомы RAII (Resource Acquisition Is Initialization).

- `filters::CreateFilter(const parse::Token& token)`: Это объявление функции, которая принимает объект `token` типа `parse::Token`. Этот объект содержит два поля: `name`, представляющее собой имя фильтра, и `args`, являющееся вектором аргументов, необходимых для создания фильтра.

**Логика выбора фильтра**
1. **Определение типа фильтра**:
    - `const std::string& filter = token.name;` извлекает имя фильтра из токена.

2. **Условия для создания конкретных фильтров**:
    - Для каждого типа фильтра (`-sharp`, `-crop`, `-gs`, `-neg`, `-edge`) установлены специфические условия, включая проверку аргументов, необходимых для его создания.

3. **Условия и исключения**:
    - Если аргументы токена не соответствуют требованиям создаваемого фильтра, функция выбрасывает исключение `std::invalid_argument` с соответствующим сообщением. Это предотвращает создание фильтра с неправильными или недостающими данными.

4. **Создание фильтра**:
    - При успешном прохождении проверок аргументов для указанного фильтра используется `std::make_unique` для создания уникального указателя на новый экземпляр соответствующего класса фильтра.
    - Например, `return std::make_unique<filters::Crop>(width, height);` создаёт фильтр обрезки с заданными шириной и высотой.

#### Проверки и исключения

- В коде активно используются проверки аргументов для гарантии создания фильтра с корректными параметрами. Если аргументы не удовлетворяют условиям, функция генерирует исключение `std::invalid_argument`, что позволяет обработать ошибку на более высоком уровне.

- В блоке `catch` для фильтра `-crop` и `-edge` отлавливаются исключения, возникающие при попытке преобразования строковых аргументов в числа. Если преобразование не удаётся, генерируется `std::invalid_argument

**Возврат и неизвестные фильтры**
- Если все проверки пройдены успешно, функция возвращает умный указатель на созданный объект фильтра.
- Если имя фильтра не соответствует ни одному из известных, функция генерирует исключение `std::invalid_argument` с сообщением о неизвестном фильтре.


**Функция `CreateFilter` принимает токен, извлекает имя фильтра, создаёт объект соответствующего фильтра и возвращает умный указатель на этот объект. Если происходит ошибка в процессе проверки имени или аргументов фильтра, выбрасывается исключение с соответствующим сообщением об ошибке**

## Utils
`Utils.h` - заголовочный файл для вспомогательных функций, которые могут использоваться в разных частях проекта.

```cpp
#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <vector>

namespace image::utils {
const size_t BITS_PER_PIXEL = 24;
const int BITS_PER_PIXEL_POSITION = 14;
const int BMP_HEADER_SIZE = 14;
const int BYTES_PER_PIXEL = 3;
const size_t CNT_OF_PLANES = 1;
const size_t CNT_OF_PLANES_POSITION = 12;
const int DIB_HEADER_SIZE = 40;
const int DIB_HEADER_SIZE_POSITION = 0;
const int FORMAT_FIRST_POSITION = 0;
const int FORMAT_SECOND_POSITION = 1;
const int FILE_SIZE_POSITION = 2;
const int HEIGHT_POSITION = 8;
const int PADDING_SIZE = 4;
const int PIXS_ARRAY_OFFSET_POSITION = 10;  // NOLINT
const int PIXELS_SIZE = 24;
const int SIZE_POSITION = 2;
const int WIDTH_POSITION = 4;
const int MAX_COLOR = 255;

const std::vector<char> BMP_SIGNATURE = {'B', 'M'};
const std::vector<size_t> SHIFT_VALUES = {8, 16, 24};
}  // namespace image::utils

#endif  // UTILS_H
```
**Kод представляет собой заголовочный файл `Utils.h`, который содержит объявления констант и переменных, используемых в остальной части проекта для обработки изображений, в частности, для работы с форматом изображений BMP (Bitmap). Давайте рассмотрим каждый элемент в этом файле более детально:**

### Защита от повторного включения
- `#ifndef UTILS_H`, `#define UTILS_H`, и `#endif` используются для предотвращения повторного включения содержимого файла при многократном его подключении, что может привести к ошибкам компиляции.

### Подключение необходимых заголовков
- `#include <cstddef>` включает определения общих типов и макросов, таких как `size_t`.
- `#include <vector>` подключает функциональность контейнера `vector` из стандартной библиотеки C++, который используется для работы с массивами данных.

### Объявление пространства имён
- `namespace image::utils { ... }` определяет пространство имён `image::utils`, которое используется для группировки логически связанных констант и переменных, чтобы избежать конфликтов имен и улучшить организацию кода.

### Константы
В файле объявлены следующие константы, которые используются для работы с изображениями в формате BMP:- **Константы размеров и позиций**:
    - `BITS_PER_PIXEL`, `BITS_PER_PIXEL_POSITION`, `BMP_HEADER_SIZE`, `BYTES_PER_PIXEL`, `CNT_OF_PLANES`, `CNT_OF_PLANES_POSITION`, `DIB_HEADER_SIZE`, `DIB_HEADER_SIZE_POSITION`, `FORMAT_FIRST_POSITION`, `FORMAT_SECOND_POSITION`, `FILE_SIZE_POSITION`, `HEIGHT_POSITION`, `PADDING_SIZE`, `PIXS_ARRAY_OFFSET_POSITION`, `PIXELS_SIZE`, `SIZE_POSITION`, `WIDTH_POSITION` представляют собой значения, связанные с размером и структурой BMP файла, такие как размеры заголовков, позиции определённых данных в файлах, количество бит на пиксель и так далее.

- **`MAX_COLOR`**: Максимальное значение для компоненты цвета (255 для 8-битного цвета), используется для обработки цветовых значений в изображении.

- **Массивы**:
    - `BMP_SIGNATURE`: Содержит сигнатуру файла BMP ('B', 'M'), которая используется для идентификации BMP файлов.
    - `SHIFT_VALUES`: Содержит значения сдвига (8, 16, 24), используемые при работе с цветовыми компонентами пикселей.

Эти константы и массивы используются для создания, обработки и анализа изображений в формате BMP, включая чтение и запись файлов, обработку заголовков файлов, и управление цветовыми значениями пикселей. Они предоставляют необходимую информацию о структуре данных BMP и поддерживают обработку изображений в соответствии со стандартом BMP.


## Test_script
`test_script` - каталог, содержащий скрипты и данные для тестирования функциональности проекта. В нем находится:

### `data/test_data_files` - каталог с тестовыми данными (с тестовыми изображениями).

### `test_image_processor.py` - скрипт на Python для автоматизированного тестирования работы приложения, в частности, тестирования применения фильтров к изображениям.

```python3
script.py
...
```

**Этот тестовый скрипт автоматизирует процесс проверки корректности работы приложения по обработке изображений, применяя разные фильтры с различными параметрами к выбранным изображениям и сравнивая полученные результаты с ожидаемыми. Он помогает разработчикам убедиться в том, что изменения в коде не нарушили работу существующей функциональности и что новые функции работают как ожидается.**