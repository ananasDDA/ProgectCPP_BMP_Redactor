## Using Clang in Visual Studio Code (RU version)

В этом уроке вы настраиваете Visual Studio Code на macOS для использования компилятора и отладчика Clang/LLVM.

После настройки VS Code вы скомпилируете и отладите программу C++ в VS Code. Это руководство не научит вас Clang или языку C++. Для этих предметов в Интернете доступно много хороших ресурсов.

Если у вас возникнут какие-либо проблемы, не стесняйтесь подать заявку на этот учебник в [VS Code documentation repository](https://github.com/microsoft/vscode-docs/issues).

## [Prerequisites](https://code.visualstudio.com/docs/cpp/config-clang-mac#_prerequisites)
(Предворительные требования)

Чтобы успешно пройти это руководство, вы должны выполнить следующие действия:
1. Установить [Visual Studio Code on macOS](https://code.visualstudio.com/docs/setup/mac).
2. Установить [C++ extension for VS Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools). Вы можете установить расширение C/C++, выполнив поиск по запросу "C++" в представлении "Расширения". (⇧⌘X).

![[Pasted image 20240422143837.png]]

## [Ensure Clang is installed](https://code.visualstudio.com/docs/cpp/config-clang-mac#_ensure-clang-is-installed)
(Проверка установки Clang)

Clang, возможно, уже установлен на вашем Mac. Чтобы убедиться, что это так, откройте окно терминала macOS и введите следующую команду:

```shell
clang --version
```

Если Clang не установлен, введите следующую команду, чтобы установить инструменты разработчика командной строки, которые включают Clang:

```shell
xcode-select --install
```

## [Create Hello World app](https://code.visualstudio.com/docs/cpp/config-clang-mac#_create-hello-world-app)

В терминале macOS создайте пустую папку под названием `progects`, где вы можете хранить все свои проекты VS Code, затем создайте подпапку под названием `helloworld`, перейдите в нее и откройте VS Code в этой папке, введя следующие команды в окне терминала:

```shell
mkdir projects
cd projects
mkdir helloworld
cd helloworld
code .
```

Команда `code .` открывает VS Code в текущей рабочей папке, которая становится вашим "рабочим пространством". По мере прохождения учебника в папке `.vscode` в вашем рабочем пространстве создаются три файла:
- `tasks.json` (compiler build settings)
- `launch.json` (debugger settings)
- `c_cpp_properties.json` (compiler path and IntelliSense settings)

### [Add a hello world source code file](https://code.visualstudio.com/docs/cpp/config-clang-mac#_add-a-hello-world-source-code-file)

В строке заголовка проводника файлов нажмите кнопку "Новый файл" и назовите файл `helloworld.cpp`.

![[Pasted image 20240422145636.png]]

Вставьте следующий исходный код:

``` cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}
```

Теперь нажмите ⌘S, чтобы сохранить файл. Обратите внимание, что ваши файлы перечислены в представлении проводника файлов (⇧⌘E) на боковой панели VS Code:

![[https://github.com/ananasDDA/ProgectCPP_BMP_Redactor/commit/Pasted image 20240422145847.png]]

Вы также можете включить автоматическое сохранение ([Auto Save](https://code.visualstudio.com/docs/editor/codebasics#_save-auto-save)) для автоматического сохранения изменений в файле, выбрав **File** > **Auto Save**. Вы можете узнать больше о других представлениях в документации по пользовательскому интерфейсу VS Code [User Interface documentation](https://code.visualstudio.com/docs/getstarted/userinterface).

> **Примечание:** При сохранении или открытии файла C++ вы можете увидеть уведомление от расширения C/C++ о доступности версии Insiders, которая позволяет тестировать новые функции и исправления. Вы можете проигнорировать это уведомление, выбрав > `X` (**Clear Notification**).

## [Explore IntelliSense](https://code.visualstudio.com/docs/cpp/config-clang-mac#_explore-intellisense)
(https://learn.microsoft.com/ru-ru/visualstudio/ide/visual-cpp-intellisense?view=vs-2022)

[IntelliSense](https://code.visualstudio.com/docs/editor/intellisense) Это инструмент, который поможет вам быстрее и эффективнее кодировать, добавляя функции редактирования кода, такие как завершение кода, информация о параметрах, быстрая информация и списки участников.

Чтобы увидеть IntelliSense в действии, наведите на `vector` или `string`, чтобы увидеть информацию об их типе. Если вы введете `msg`. в строке 10, вы можете увидеть список завершения рекомендуемых функций-членов для вызова, все сгенерированные IntelliSense:

![[Pasted image 20240422150622.png]]

Вы можете нажать клавишу `Tab`, чтобы вставить выбранный элемент. Затем, когда вы добавляете открывающую скобку, отображается информация об аргументах, которые требуется функции.

Если `IntelliSense` еще не настроен, откройте палитру команд (⇧⌘P) и введите **Select IntelliSense Configuration**. В раскрывающемся списке компиляторов выберите Использовать `clang++` для настройки. Более подробную информацию можно найти в документации по конфигурации [IntelliSense configuration documentation](https://code.visualstudio.com/docs/cpp/configure-intellisense).

## [Run helloworld.cpp](https://code.visualstudio.com/docs/cpp/config-clang-mac#_run-helloworldcpp)

Помните, что расширение C++ использует компилятор C++, установленный на вашем компьютере, для создания вашей программы. Убедитесь, что у вас установлен компилятор C++, такой как Clang, прежде чем пытаться запустить и отладить `helloworld.cpp` в VS Code.
1. Открыть `helloworld.cpp` чтобы это был активный файл
2. Нажмите кнопку воспроизведения в правом верхнем углу редактора.

![[Pasted image 20240422151316.png]]

3. Выберите **C/C++: clang++ build and debug active file** из списка обнаруженных компиляторов в вашей системе.

![[Pasted image 20240422151407.png]]

Вас просят выбрать компилятор только при первом запуске `helloworld.cpp`. Этот компилятор является компилятором по умолчанию, установленным в файле `tasks.json`.

4. После успешной сборки выходные данные вашей программы появятся в интегрированной **Debug Console**.

![[Pasted image 20240422151538.png]]

**Поздравляем! Вы только что запустите свою первую программу C++ в VS Code!**

### [Understanding tasks.json](https://code.visualstudio.com/docs/cpp/config-clang-mac#_understanding-tasksjson)

При первом запуске программы расширение **C++** создает `tasks.json`, расположенный в папке `.vscode` вашего проекта. tasks.json хранит конфигурации сборки.

Вот пример файла`tasks.json` на macOS:

```json
{
  "tasks": [
    {
      "type": "cppbuild",
      "label": "C/C++: clang++ build active file",
      "command": "/usr/bin/clang++",
      "args": [
        "-fcolor-diagnostics",
        "-fansi-escape-codes",
        "-g",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}"
      ],
      "options": {
        "cwd": "${fileDirname}"
      },
      "problemMatcher": ["$gcc"],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "detail": "Task generated by Debugger."
    }
  ],
  "version": "2.0.0"
}
```

> **Примечание**: Вы можете узнать больше о переменных `tasks.json` в [variables reference](https://code.visualstudio.com/docs/editor/variables-reference).

В настройке `command` указывается программа для запуска. В данном случае это `clang++`.

Массив `args` определяет аргументы командной строки, которые передаются в `clang++`. Эти аргументы должны быть указаны в порядке, ожидаемом компилятором.

Эта задача указывает компилятору C++ взять активный файл `(${file})`, скомпилировать его и создать выходной файл (-o switch) в текущем каталоге `(${fileDirname})` с тем же именем, что и активный файл, но без расширения файла `(${fileBasenameNoExtension})`. Этот процесс создает `helloworld`.

Значение `label` - это то, что вы видите в списке задач, который основан на ваших личных предпочтениях.

Значение `detail` - это описание задачи в списке задач. Обновите эту строку, чтобы отличить ее от аналогичных задач.

Значение `problemMatcher` выбирает выходной парсер для поиска ошибок и предупреждений в выходных данных компилятора. Для clang++ сопоставление проблем `$gcc` создает наилучшие результаты.

С этого момента кнопка воспроизведения (play button) всегда читается с `tasks.json`, чтобы понять, как собрать и запустить вашу программу. Вы можете определить несколько задач сборки в `tasks.json`, и какая задача помечена по умолчанию, используется кнопкой воспроизведения. Если вам нужно изменить компилятор по умолчанию, вы можете запустить **Tasks: Configure Default Build Task** в командной палитре. Кроме того, вы можете изменить файл `tasks.json` и удалить значение по умолчанию, заменив этот сегмент:

```json
    "group": {
        "kind": "build",
        "isDefault": true
    },
```

с этим:

```json
  "group": "build",
```

### [Modifying tasks.json](https://code.visualstudio.com/docs/cpp/config-clang-mac#_modifying-tasksjson)

Вы можете изменить свой tasks.json для создания нескольких файлов C++, используя такой аргумент, как `"${workspaceFolder}/*.cpp"` вместо `"${file}"`. Это создает все файлы .cpp в вашей текущей папке. Вы также можете изменить имя выходного файла, заменив `"${fileDirname}/${fileBasenameNoExtension}"` на жестко закодированный файл (например, `"${workspaceFolder}/myProgram.out"`).

## [Debug helloworld.cpp](https://code.visualstudio.com/docs/cpp/config-clang-mac#_debug-helloworldcpp)

Чтобы отладить ваш код
1. Вернитесь в `helloworld.cpp`, чтобы это был активный файл.
2. Установите точку останова, нажав на поле редактора или используя F9 в текущей строке.

![[Pasted image 20240422152732.png]]

3. В раскрывающемся списке рядом с кнопкой воспроизведения выберите **Debug C/C++ File**.

![[Pasted image 20240422152822.png]]

4. Выберите **C/C++: clang++ build and debug active file** из списка обнаруженных компиляторов в вашей системе (вам будет предложено выбрать компилятор только при первом запуске или отладке `helloworld.cpp`).

![[Pasted image 20240422152921.png]]

5. Вы увидите, как задача выполняется, и печатает вывод в окне терминала.

![[Pasted image 20240422153028.png]]

Кнопка воспроизведения имеет два режима: **Run C/C++ File** and **Debug C/C++ File**. По умолчанию используется последний режим. Если вы видите значок отладки на кнопке воспроизведения, вы можете выбрать кнопку воспроизведения для отладки, а не выбирать пункт выпадающего меню.

## [Explore the debugger](https://code.visualstudio.com/docs/cpp/config-clang-mac#_explore-the-debugger)

Прежде чем вы начнете просматривать код, давайте обратим внимание на несколько изменений в пользовательском интерфейсе:
* Интегрированный терминал отображается в нижней части редактора исходного кода. На вкладке **Debug Console** вы видите выходные данные, которые указывают на то, что отладчик запущен и работает.
* Редактор выделяет строку, в которой вы установили точку останова перед запуском отладчика:

![[Pasted image 20240422154323.png]]

* В представлении **Run and Debug** в баре активности отображается информация об отладке.
* В верхней части редактора кода появляется панель управления отладкой. Вы можете перемещать это по экрану, схватив точки с левой стороны.

	![[Pasted image 20240422154606.png]]

## [Step through the code](https://code.visualstudio.com/docs/cpp/config-clang-mac#_step-through-the-code)

Теперь вы готовы начать просматривать код.
1. Выберите значок **Step over** на панели управления отладкой, чтобы подсветилась инструкция `for (const string& word : msg)`

	![[Pasted image 20240422155000.png]]

	Команда **Step Over** пропускает все внутренние вызовы функций в `vector` и `string` классах, которые вызываются при создании и инициализации переменной `msg`. Обратите внимание на изменение в окне переменных. Содержание `msg` видно, потому что это утверждение завершено.

2. Нажмите **Step over** снова, чтобы перейти к следующему оператору (про пропуск всего внутреннего кода, который выполняется для инициализации цикла). Теперь в окне **Variables** отображается информация о переменной цикла.
3. Нажмите **Step over** еще раз, чтобы выполнить инструкцию `cout`.
4. Если хотите, вы можете продолжать нажимать **Step over** до тех пор, пока все слова в векторе не будут напечатаны на консоли. Но если вам интересно, попробуйте нажать кнопку **Step Into**, чтобы просмотреть исходный код в стандартной библиотеке C++!

## [Set a watch](https://code.visualstudio.com/docs/cpp/config-clang-mac#_set-a-watch)

Возможно, вы захотите отслеживать значение переменной по мере выполнения вашей программы. Вы можете сделать это, установив watch на переменную.

1. Поместите точку вставки внутри петли. В окне **Watch** выберите знак плюса и введите слово в текстовом поле. Это имя переменной цикла. Теперь просмотрите окно Watch по мере того, как вы проходите через цикл.

	![[Pasted image 20240424042839.png]]

2. Добавьте еще один watch, добавив этот оператор перед циклом: `int i = 0;`. Затем внутри цикла добавьте это утверждение: `++i;`. Теперь добавьте watch для `i`, как вы делали на предыдущем шаге.
3. Чтобы быстро просмотреть значение любой переменной во время паузы выполнения, вы можете наведите на нее курсор с помощью указателя мыши.

	![[Pasted image 20240424043149.png]]

## [Customize debugging with launch.json](https://code.visualstudio.com/docs/cpp/config-clang-mac#_customize-debugging-with-launchjson)

При отладке (debug) с помощью кнопки воспроизведения или `F5`, расширение C++ создает конфигурацию динамической отладки на лету.

Бывают случаи, когда вы хотите настроить конфигурацию отладки, например, указать аргументы для передачи программе во время выполнения. Вы можете создать пользовательские конфигурации отладки в файле `launch.json`.

Чтобы создать `launch.json`, выберите **Add Debug Configuration** в раскрывающемся меню кнопки воспроизведения.

![[Pasted image 20240424043554.png]]

Затем вы увидите раскрывающийся список для различных предопределенных конфигураций отладки. Выберите **C/C++: clang++ build and debug active file** (сборка и отладка активного файла).

![C++ debug configuration dropdown](https://code.visualstudio.com/assets/docs/cpp/clang-mac/build-and-debug-active-file.png)

VS Code создает файл `launch.json`, который выглядит примерно так:

```json
{
  "configurations": [
    {
      "name": "C/C++: clang++ build and debug active file",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}/${fileBasenameNoExtension}",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "lldb",
      "preLaunchTask": "C/C++: clang++ build active file"
    }
  ],
  "version": "2.0.0"
}
```

Настройка program указывает программу, которую вы хотите отлаживать. Здесь он установлен на активную папку файла `${fileDirname}` и активное имя файла `${fileBasenameNoExtension}`, который, если `helloworld.cpp` является активным файлом, будет `helloworld`. Свойство `args` представляет собой массив аргументов для передавания программе во время выполнения.

По умолчанию расширение C++ не добавляет никаких точек останова к исходному коду, а значение `stopAtEntry` установлено в `false`.

Измените значение `stopAtEntry` на `true`, чтобы заставить отладчик остановиться на основном методе при запуске отладки.

Убедитесь, что значение `preLaunchTask` соответствует метке задачи сборки в файле `tasks.json`.
	Отныне кнопка воспроизведения и `F5` будут считываться из вашего файла `launch.json` при запуске программы для отладки.

## [Adding additional C/C++ settings](https://code.visualstudio.com/docs/cpp/config-clang-mac#_adding-additional-cc-settings)

Для большего контроля над расширением **C/C++** создайте файл `c_cpp_properties.json`, который позволяет изменять такие настройки, как путь к компилятору, включать пути, по которым C++ standard компилируется (например, C++17) и многое другое.

Просмотрите пользовательский интерфейс конфигурации C/C++, выполнив команду C/C++: **C/C++: Edit Configurations (UI)** из палитры команд (⇧⌘P).

![[Pasted image 20240424045322.png]]

Откроется страница конфигураций C/C++

![[Pasted image 20240424045358.png]]

Visual Studio Code помещает эти настройки в `.vscode/c_cpp_properties.json`. Если вы откроете этот файл напрямую, он должен выглядеть примерно так:

```json
{
  "configurations": [
    {
      "name": "Mac",
      "includePath": ["${workspaceFolder}/**"],
      "defines": [],
      "macFrameworkPath": [
        "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks"
      ],
      "compilerPath": "/usr/bin/clang",
      "cStandard": "c11",
      "cppStandard": "c++17",
      "intelliSenseMode": "macos-clang-arm64"
    }
  ],
  "version": 4
}
```

Вам нужно изменить настройку **Include path** только в том случае, если ваша программа включает в себя файлы заголовков, которых нет в вашем рабочем пространстве или в стандартном пути библиотеки.

### [Compiler path](https://code.visualstudio.com/docs/cpp/config-clang-mac#_compiler-path)

Расширение использует настройку `compilerPath` для вывода пути к файлам заголовков стандартной библиотеки C++. Когда расширение знает, где найти эти файлы, оно может предоставить такие функции, как интеллектуальное завершение и **Go to Definition** навигацию (навигацию по определению).

Расширение C/C++ пытается заполнить `compilerPath` местоположением компилятора по умолчанию на основе того, что он находит в вашей системе. Заказ поиска `compilerPath`:
* Ваш PATH для имен известных компиляторов. Порядок отображения компиляторов в списке зависит от вашего PATH.
* Затем ищется hard-coded Xcode paths (жестко закодированные пути Xcode), такие как `/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/`

Для получения дополнительной информации смотри [ntelliSense configuration documentation](https://code.visualstudio.com/docs/cpp/configure-intellisense).

### [Mac framework path](https://code.visualstudio.com/docs/cpp/config-clang-mac#_mac-framework-path)

На экране конфигурации C/C++ прокрутите вниз и разверните **Advanced Settings** и убедитесь, что **Mac framework path** указывает на системные заголовочные файлы. Например:
`/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks`

## [Troubleshooting](https://code.visualstudio.com/docs/cpp/config-clang-mac#_troubleshooting)
*Ошибочки*
### [Compiler and linking errors](https://code.visualstudio.com/docs/cpp/config-clang-mac#_compiler-and-linking-errors)

Наиболее распространенная причина ошибок (например, undefined _main или попытка связать с файлом, созданным для неизвестного неподдерживаемого формата файла, и т. д.) возникает, когда `helloworld.cpp` не является активным файлом при запуске сборки или отладки. Это связано с тем, что компилятор пытается скомпилировать что-то, что не является исходным кодом, например, файл `launch.json`, `tasks.json` или `c_cpp_properties.json`.

Если вы видите ошибки сборки с упоминанием "C++11 extensions", вы, возможно, не обновили свою задачу сборки `tasks.json`, чтобы использовать аргумент clang++ `--std=c++17`. По умолчанию clang++ использует стандарт C++98, который не поддерживает инициализацию, используемую в `helloworld.cpp`. Обязательно замените все содержимое вашего файла `tasks.json` блоком кода, предоставленным в разделе  [Run helloworld.cpp](https://code.visualstudio.com/docs/cpp/config-clang-mac#_run-helloworldcpp)

### [Terminal won't launch for input](https://code.visualstudio.com/docs/cpp/config-clang-mac#_terminal-wont-launch-for-input)

В macOS Catalina и далее у вас может возникнуть проблема, когда вы не можете ввести ввод, даже после установки `"externalConsole": true`. Откроется окно терминала, но на самом деле оно не позволяет вводить какие-либо данные.

* The issue is currently tracked [#5079](https://github.com/microsoft/vscode-cpptools/issues/5079).

Обходной путь заключается в том, чтобы VS Code запустил терминал один раз. Вы можете сделать это, добавив и заполнив эту задачу в своем `tasks.json`:

```json
{
  "label": "Open Terminal",
  "type": "shell",
  "command": "osascript -e 'tell application \"Terminal\"\ndo script \"echo hello\"\nend tell'",
  "problemMatcher": []
}
```

Вы можете запустить эту конкретную задачу с помощью **Terminal** > **Run Task...** и выбрать **Open Terminal**.

После того, как вы примете запрос разрешения, при отладке должна появиться внешняя консоль.

## [Next steps](https://code.visualstudio.com/docs/cpp/config-clang-mac#_next-steps)

- Explore the [VS Code User Guide](https://code.visualstudio.com/docs/editor/codebasics).
- Review the [Overview of the C++ extension](https://code.visualstudio.com/docs/languages/cpp)
- Create a new workspace, copy your .json files to it, adjust the necessary settings for the new workspace path, program name, and so on, and start coding!