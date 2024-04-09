# ProgectCPP_BMP_Redactor
### Консольное приложение для редактирования BMP файлов

# Цель проекта:
 обеспечение для пользователя возможностью применять фильтры для BMP файлов

 ### Графические фильтры (image_processor)

В этом проекте требуется реализовать консольное приложение,
позволяющее применять к изображениям различные фильтры,
аналогичные фильтрам в популярных графических редакторах.

## Поддерживаемый формат изображений

Входные и выходные графические файлы должны быть в формате [BMP](http://en.wikipedia.org/wiki/BMP_file_format).

Формат BMP поддерживает достаточно много вариаций, но в этом задании будет использоваться
24-битный BMP без сжатия и без таблицы цветов. Тип используемого `DIB header` - `BITMAPINFOHEADER`.

Пример файла в нужном формате есть в статье на Википедии [в разделе "Example 1"](https://en.wikipedia.org/wiki/BMP_file_format#Example_1)
и в папке [test_script/data](test_script/data).

## Формат аргументов командной строки

Описание формата аргументов командной строки:

`{имя программы} {путь к входному файлу} {путь к выходному файлу}
[-{имя фильтра 1} [параметр фильтра 1] [параметр фильтра 2] ...]
[-{имя фильтра 2} [параметр фильтра 1] [параметр фильтра 2] ...] ...`

### Пример
`./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5`

В этом примере
1. Загружается изображение из файла `input.bmp`
2. Обрезается до изображения с началом в верхнем левом углу и размером 800х600 пикселей
3. Переводится в оттенки серого
4. Применяется размытие с сигмой 0.5
5. Полученное изображение сохраняется в файл `/tmp/output.bmp`

Список фильтров может быть пуст, тогда изображение должно быть сохранено в неизменном виде.
Фильтры применяются в том порядке, в котором они перечислены в аргументах командной строки.

## Фильтры

В формулах далее считаем, что каждая компонента цвета
представлена вещественным числом от 0 до 1. Цвета пикселей
представлены тройками `(R, G, B)`. Таким образом, `(0, 0, 0)` – черный,
`(1, 1, 1)` – белый.

Если фильтр задан матрицей, это означает, что значение каждого из цветов определяется взвешенной суммой
значений этого цвета в соседних пикселях в соответствии с матрицей. При этом целевому пикселю
соответствует центральный элемент матрицы.

Например, для фильтра, заданного матрицей

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D1%20&%202%20&%203%20%5C%5C4%20&%205%20&%206%20%5C%5C7%20&%208%20&%209%20%5C%5C%5Cend%7Bbmatrix%7D)

Значение каждого из цветов целевого пикселя `C[x][y]` будет определяться формулой

```
C[x][y] =
  min(1, max(0,
   1*C[x-1][y-1] + 2*C[x][y-1] + 3*C[x+1][y-1] +
   4*C[x-1][y]   + 5*C[x][y]   + 6*C[x+1][y]   +
   7*C[x-1][y+1] + 8*C[x][y+1] + 9*C[x+1][y+1]
))
```

При обработке пикселей, близких к краю изображения, часть матрицы может выходить за границу изображения.
В таком случае в качестве значения пикселя, выходящего за границу, следует использовать значение ближайшего
к нему пикселя изображения.

### Список базовых фильтров

#### Crop (-crop width height)
Обрезает изображение до заданных ширины и высоты. Используется верхняя левая часть изображения.

Если запрошенные ширина или высота превышают размеры исходного изображения, выдается доступная часть изображения.

#### Grayscale (-gs)
Преобразует изображение в оттенки серого по формуле

![encoding](https://latex.codecogs.com/svg.image?R'%20=%20G'%20=%20B'%20=0.299%20R%20&plus;%200%20.587%20G%20&plus;%200%20.%20114%20B)

#### Negative (-neg)
Преобразует изображение в негатив по формуле

![encoding](https://latex.codecogs.com/svg.image?R'%20=%201%20-%20R,%20G'%20=%201%20-%20G,%20B'%20=%201%20-%20B)

#### Sharpening (-sharp)
Повышение резкости. Достигается применением матрицы

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%205%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

#### Edge Detection (-edge threshold)
Выделение границ. Изображение переводится в оттенки серого и применяется матрица

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%204%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

Пиксели со значением, превысившим `threshold`, окрашиваются в белый, остальные – в черный.

#### Gaussian Blur (-blur sigma)
[Гауссово размытие](https://ru.wikipedia.org/wiki/Размытие_по_Гауссу),
параметр – сигма.

Значение каждого из цветов пикселя `C[x0][y0]` определяется формулой

![encoding](https://latex.codecogs.com/svg.image?C%5Bx_0%5D%5By_0%5D%20%3D%20%5Csum_%7Bx%3D0%2Cy%3D0%7D%5E%7Bwidth-1%2C%20height-1%7DC%5Bx%5D%5By%5D%5Cfrac%7B1%7D%7B2%5Cpi%5Csigma%5E2%7De%5E%7B-%5Cfrac%7B%5Cleft%7Cx_o-x%5Cright%7C%5E2%20%26plus%3B%20%5Cleft%7Cy_o-y%5Cright%7C%5E2%7D%7B2%5Csigma%5E2%7D%7D)

Существуют различные варианты релализации и оптимизации вычисления этого фильтра, описание есть [в Википедии](https://ru.wikipedia.org/wiki/Размытие_по_Гауссу).

## Реализация

Применять сторонние библиотеки для работы с изображениями запрещено.

Старайтесь делать все компоненты программы по возможности более универсальными и не привязанными к специфике конкретной задачи.

Все исключительные ситуации должны корректно обрабатываться с выводом понятного пользователю сообщения об ошибке.
Для этого используйте механизм [исключений](https://en.cppreference.com/w/cpp/language/throw).
Никакие сценарии, включая использование файлов с форматом, не соответствующим спецификации, не должны приводить к падению программы.

Для чтения и записи файлов будем использовать [std::ifstream](https://en.cppreference.com/w/cpp/io/basic_ifstream) и [std::ofstream](https://en.cppreference.com/w/cpp/io/basic_ofstream).

Скорее всего, вам понадобятся следующие компоненты:
- Класс, представляющий изображение и обеспечивающий работу с ним
- Классы для чтения и записи формата BMP
- Фильтры
- Контроллер, управляющий последовательным применением фильтров

Общие части следует выделить через наследование.

Подробный дизайн программы рекомендуется обсудить с преподавателем на семинарах.

# Команда проекта:
* Дорохов Даниил
* Мария Николаева

# Дневник проекта:
На проект выделяется 10 дней
## День 1: Инициализация проекта
- **Цель дня**: создать базовую структуру проекта, настроить среду разработки.
- **Задачи**:
    1. Создать репозиторий на GitHub.
    2. Настроить `.gitignore` для C++ и файлов проекта.
    3. Написать `README.md` с описанием проекта.
    4. Создать базовые директории (`test_script/data` ...).

## День 2: Работа с BMP файлами
- **Цель дня**: реализовать чтение и запись BMP файлов.
- **Задачи**:
    1. Изучить спецификацию формата BMP.
    2. Реализовать структуру `BMPHeader` для работы с заголовками BMP.
    3. Написать функции для чтения и записи BMP файлов (`loadBMP`, `saveBMP`).

## День 3: Реализация фильтра Crop
- **Цель дня**: добавить возможность обрезки изображения.
- **Задачи**:
    1. Разработать алгоритм для обрезки изображений.
    2. Реализовать функцию `crop` для применения фильтра к изображению.
    3. Тестировать функцию на различных изображениях.

## День 4: Реализация фильтра Grayscale
- **Цель дня**: реализовать преобразование изображения в оттенки серого.
- **Задачи**:
    1. Изучить алгоритм преобразования в оттенки серого.
    2. Реализовать функцию `grayscale`.
    3. Провести тестирование функции на разных изображениях.

## День 5: Реализация фильтра Negative
- **Цель дня**: добавить возможность получения негатива изображения.
- **Задачи**:
    1. Изучить алгоритм получения негатива изображения.    2. Реализовать функцию `negative`.
    3. Тестирование функции на разнообразных изображениях.

## День 6: Реализация фильтра Sharpening
- **Цель дня**: реализовать фильтр повышения резкости.
- **Задачи**:
    1. Изучить алгоритм повышения резкости.
    2. Реализовать функцию `sharpening`.
    3. Протестировать на различных изображениях.

## День 7: Реализация фильтра Edge Detection
- **Цель дня**: добавить выделение границ на изображении.
- **Задачи**:
    1. Изучить метод выделения границ.
    2. Реализовать функцию `edgeDetection`.
    3. Провести тестирование на разных изображениях.

## День 8: Разработка CLI
- **Цель дня**: реализовать интерфейс командной строки для работы с фильтрами.
- **Задачи**:
    1. Определить формат аргументов командной строки.
    2. Реализовать парсинг аргументов командной строки.
    3. Реализовать логику применения фильтров в соответствии с аргументами.

## День 9: Тестирование и отладка
- **Цель дня**: обеспечить корректную работу приложения.
- **Задачи**:
    1. Создать тестовые сценарии для каждого фильтра.
    2. Протестировать последовательное применение нескольких фильтров. 3. Отладить обнаруженные проблемы.

## День 10: Документация и рефакторинг
- **Цель дня**: подготовить проект к релизу.
- **Задачи**:
    1. Документировать код и функции.
    2. Провести рефакторинг кода для повышения читаемости и производительности.
    3. Подготовить финальный коммит и релиз версии.


# Aрхитектура проекта:
```
.
├── CMakeLists.txt
├── Color.cpp
├── Image.cpp
├── ImageProcessor.h
├── Parser.cpp
├── Parser.h
├── Reader.cpp
├── Reader.h
├── Utils.h
├── Writer.cpp
├── Writer.h
├── color.h
├── filter.cpp
├── filter.h
├── image.h
├── image_processor.cpp
├── readme.md
└── test_script
    ├── data
    │   ├── test_data_files
    └── test_image_processor.py
```
