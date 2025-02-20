# scrcpy (v1.18)

[Информация по переводу](#перевод-и-оригинальная-документация)  
[Оригинальная документация 🇬🇧](README.md)  
[Документация на других языках 🇬🇧](README.md#translations)  

Приложение транслирует экран Android устройств на ваш ПК или в иной источник,
например в [виртуальное v4l2 устройство](#перенаправление-на-виртуальное-v4l2-устройство)
(виртуальная веб-камера) и позволяет управлять устройством [через клавиатуру и мышь](#управление-через-окно-трансляции)
(в том числе операции [масштабирования пальцами](#масштабирование-пальцами), копирования,
вставки и синхронизация буферов обмена).
  
Поддерживаются Android устройства подключенные через USB кабель,
[по WiFi сети 🇬🇧][article-tcpip] или удалённый ADB клиент [через SSH](#ssh-тунель).
  
_Root_ доступ на устройстве **не** требуется.
  
Приложение доступно под [_Linux_](#linux), [_Windows_](#windows) и [_macOS_](#macos).

![screenshot](assets/screenshot-debian-600.jpg)

Цели проекта:

 - **легковесность** (нативно, отображает только экран устройства)
 - **производительность** (30~60fps)
 - **качество** (1920×1080 или выше)
 - **низкая задержка** ([35~70ms 🇬🇧][lowlatency])
 - **быстрое время запуска** (~1 секунда до отображения первого кадра)
 - **ненавязчивость** (ничего не устанавливается на устройство)

[lowlatency]: https://github.com/Genymobile/scrcpy/pull/646


# Содержание
  - [ℹ️ Кратко о возможностях](#scrcpy-(v1.18))
  - [📑 Содержание](#содержание)
  - [📱 Требования к устройству](#требования-к-устройству)
  - [📦 Установка](#установка)
    - [▶️ Linux](#linux)
    - [▶️ Windows](#windows)
    - [▶️ macOS](#macos)
  - [🚀 Запуск](#запуск)
  - [⭐️ Дополнительные возможности](#дополнительные-возможности)
    - [🔧 Конфигурация запуска](#конфигурация-запуска)
      - [🖼️ Ограничение разрешения трансляции](#ограничение-разрешения-трансляции)
      - [🎚️ Изменение битрейта](#изменение-битрейта)
      - [🎞️ Ограничение частоты кадров](#ограничение-частоты-кадров)
      - [🔠 Трансляция области экрана](#трансляция-области-экрана)
      - [🔄 Фиксация ориентации видеопотока](#фиксация-ориентации-видеопотока)
      - [🗜️ Изменение кодировки трансляции](#изменение-кодировки-трансляции)
    - [💻 Захват экрана](#захват-экрана)
      - [🔴 Запись трансляции](#запись-трансляции)
      - [🎥 Перенаправление на виртуальное v4l2 устройство](#перенаправление-на-виртуальное-v4l2-устройство)
    - [🔌 Подключение устройства](#подключение-устройства)
      - [📡 Беспроводной способ](#беспроводной-способ)
      - [📱 Трансляция с нескольких устройств](#трансляция-с-нескольких-устройств)
      - [🤖 Автоматическая трансляция при подключении устройства](#автоматическая-трансляция-при-подключении-устройства)
      - [🛡️ SSH тунель](#ssh-тунель)
    - [📌 Настройки окна](#настройки-окна)
      - [🖥️ Заголовок](#заголовок)
      - [📍 Позиционирование и размер](#позиционирование-и-размер)
      - [🖥️ Безрамочность](#безрамочность)
      - [🔝 Поверх всех окон](#поверх-всех-окон)
      - [🖥️ Полный экран](#полный-экран)
      - [🔄 Поворот трансляции в окне](#поворот-трансляции-в-окне)
    - [🛠️ Прочие настройки](#прочие-настройки)
      - [🎮 Запретить управление с окна](#запретить-управление-с-окна)
      - [🖥️ Трансляция с конкретного дисплея](#трансляция-с-конкретного-дисплея)
      - [📴 Не позволять экрану гаснуть](#не-позволять-экрану-гаснуть)
      - [📴 Принудительно погасить или включить экран](#принудительно-погасить-или-включить-экран)
      - [👆 Отображать касания](#отображать-касания)
      - [🖼️ Отключить заставку на ПК](#отключить-заставку-на-пк)
    - [🎮 Управление через окно трансляции](#управление-через-окно-трансляции)
      - [🔄 Вращение экрана устройства](#вращение-экрана-устройства)
      - [✂️ Копирование и вставка](#копирование-и-вставка)
      - [✌️ Масштабирование пальцами](#масштабирование-пальцами)
      - [⌨️ Настройка ввода клавиатуры](#настройка-ввода-клавиатуры)
      - [🔳 Зажатие клавиш](#зажатие-клавиш)
      - [🖱️ Правый и средний клик](#правый-и-средний-клик)
    - [🗃️ Копирование файлов и установка приложений](#копирование-файлов-и-установка-приложений)
      - [📦 Установка приложений](#установка-приложений)
      - [📄 Копирование файла на устройство](#копирование-файла-на-устройство)
    - [📢 Трансляция звука](#трансляция-звука)
  - [🔥 Горячие клавиши](#горячие-клавиши)
  - [🔧 Произвольный путь до ADB и сервера scrcpy](#произвольный-путь-до-adb-и-сервера-scrcpy)
  - [❓️ Почему называется _scrcpy_?](#почему-называется-scrcpy)
  - [🛠️ Как сделать собственную сборку](#как-сделать-собственную-сборку)
  - [✔️ Часто задаваемые вопросы](#часто-задаваемые-вопросы)
  - [👨‍💻 Для разработчиков](#для-разработчиков)
  - [©️ Лицензия](#лицензия)
    - [©️ Перевод](#перевод)
    - [©️ Оригинал](#оригинал)
  - [📑 Статьи](#статьи)
  - [ℹ️ Перевод и оригинальная документация](#перевод-и-оригинальная-документация)

  -----

## Требования к устройству

Устройство должно работать на Android 5.0 или выше (API 21).

Необходимо [включить отладку по USB 🇬🇧][enable-adb] на подключаемых устройствах.

[enable-adb]: https://developer.android.com/studio/command-line/adb.html#Enabling

На некоторых устройствах необходимо [включить дополнительные опции 🇬🇧][control],
чтобы использовать управление клавиатурой и мышью.

[control]: https://github.com/Genymobile/scrcpy/issues/70#issuecomment-373286323


## Установка

<a href="https://repology.org/project/scrcpy/versions"><img src="https://repology.org/badge/vertical-allrepos/scrcpy.svg" alt="Packaging status" align="right"></a>

### Общий способ

 - Linux: `apt install scrcpy`
 - Windows: [скачать приложение 🇬🇧][direct-win64]
 - macOS: `brew install scrcpy`

Компиляция из исходников: [Компиляция 🇬🇧][BUILD] ([упрощённый процесс 🇬🇧][BUILD_simple])

[BUILD]: BUILD.md
[BUILD_simple]: BUILD.md#simple


### Linux

Для Debian (версия уточняется) и Ubuntu (20.04):

```bash
apt install scrcpy
```

Дополнительно, приложение доступно [в виде Snap][Snap] пакета: [`scrcpy` 🇬🇧][snap-link].

[snap-link]: https://snapstats.org/snaps/scrcpy

[snap]: https://ru.wikipedia.org/wiki/Snappy_(%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%B0_%D1%83%D0%BF%D1%80%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F_%D0%BF%D0%B0%D0%BA%D0%B5%D1%82%D0%B0%D0%BC%D0%B8)

Установка в Fedora возможна [через COPR 🇬🇧][COPR] пакет: [`scrcpy` 🇬🇧][copr-link].

[COPR]: https://fedoraproject.org/wiki/Category:Copr
[copr-link]: https://copr.fedorainfracloud.org/coprs/zeno/scrcpy/

Для Arch Linux, [доступен AUR 🇬🇧][AUR] пакет: [`scrcpy` 🇬🇧][aur-link].

[AUR]: https://wiki.archlinux.org/index.php/Arch_User_Repository
[aur-link]: https://aur.archlinux.org/packages/scrcpy/

В Gentoo установка возможна через [Ebuild 🇬🇧][Ebuild]: [`scrcpy` 🇬🇧][ebuild-link].

[Ebuild]: https://wiki.gentoo.org/wiki/Ebuild
[ebuild-link]: https://github.com/maggu2810/maggu2810-overlay/tree/master/app-mobilephone/scrcpy

Кроме прочего, вы всегда можете [собрать приложение вручную 🇬🇧][BUILD] ([упрощённый процесс 🇬🇧][BUILD_simple]).


### Windows

Для Windows подготовлен архив со всеми зависимостями (включая `adb`):

 - [`scrcpy-win64-v1.18.zip`][direct-win64]  
   _(SHA-256: 37212f5087fe6f3e258f1d44fa5c02207496b30e1d7ec442cbcf8358910a5c63)_

[direct-win64]: https://github.com/Genymobile/scrcpy/releases/download/v1.18/scrcpy-win64-v1.18.zip

Если вы используете [Chocolatey 🇬🇧][Chocolatey]:

[Chocolatey]: https://chocolatey.org/

```bash
choco install scrcpy
choco install adb    # если не установлен ADB
```

Если вы используете [Scoop 🇬🇧][Scoop]:

```bash
scoop install scrcpy
scoop install adb    # если не установлен ADB
```

[Scoop]: https://scoop.sh

Если ни один из источников не подходит, попробуйте [собрать приложение вручную 🇬🇧][BUILD].


### macOS

Приложение доступно через [Homebrew 🇬🇧][Homebrew]. Просто выполните в терминале:

[Homebrew]: https://brew.sh/

```bash
brew install scrcpy
```

Дополнительно потребуется `adb`, который должен быть прописан в `PATH`. Если не установлен:

```bash
brew install android-platform-tools
```

В качестве альтернативы возможно использовать [MacPorts 🇬🇧][MacPorts], который автоматически установит и ADB:

```bash
sudo port install scrcpy
```

[MacPorts]: https://www.macports.org/


Дополнительно, всегда доступен вариант с [ручной сборкой проекта 🇬🇧][BUILD].


## Запуск

Подключите Android устройство и выполните:

```bash
scrcpy
```

Возможно указание дополнительных аргументов.
Получить справку по ним можно следующим образом:

```bash
scrcpy --help
```

## Дополнительные возможности

### Конфигурация запсука

#### Ограничение разрешения трансляции

Иногда может быть полезным отображать экран устройства в более низком разрешении
для увеличения производительности.

Чтобы ограничить разрешение трансляции (например, до 1024 по большей стороне),
запустите _scrspy_ с аргументом:

```bash
scrcpy --max-size 1024
scrcpy -m 1024  # краткая версия
```

Таким образом, если разрешение экрана устройства 1920*1080, то трансляция будет
вестись в разрешении 1024*576.


#### Изменение битрейта

Изменение битрейта может быть полезно в некоторых случаях.
Например, при подключении [нескольких устройств](#трансляция-с-нескольких-устройств)
или при использовании [SSH тунеля](#ssh-тунель), когда недостаточная ширина канала
не позволяет корректно передавать данные.

Стандартный битрейт 8Мб/с. Способ установить битрейт в 2Мб/с:

```bash
scrcpy --bit-rate 2M
scrcpy -b 2M  # краткая версия
```

#### Ограничение частоты кадров

Ограничить частоту можно следующим параметром:

```bash
scrcpy --max-fps 15
```

Официальная поддержка появилась начиная с Android 10, но более
старые устройства также могут поддерживать эту функцию.

#### Трансляция области экрана

Возможно настроить трансляцию только конкретной области экрана.

Может быть полезно, например, для трансляции изображения
только для одного глаза из Oculus Go:

```bash
scrcpy --crop 1224:1440:0:0   # область 1224x1440 со сдвигом (0,0)
```

Если указан `--max-size`, масштабирование будет применено после обрезания.


#### Фиксация ориентации видеопотока

Влияет на ориентацию видепотока передаваемого с устройства на компьютер:

```bash
scrcpy --lock-video-orientation     # исходная ориентация (определяется устройством)
scrcpy --lock-video-orientation=0   # 0° (стандартная ориентация)
scrcpy --lock-video-orientation=1   # 270° / -90° (поворот влево)
scrcpy --lock-video-orientation=2   # 180° (разворот)
scrcpy --lock-video-orientation=3   # 90° (поворот вправо)
```

Эти параметры влияют на весь видеопоток, в том числе и на то, что отображается
в окне приложения и на то, что записывается, если ведётся запись.

Отображаемая трансляция в окне приложения может [вращаться отдельно](#поворот-трансляции-в-окне).


#### Изменение кодировки трансляции

Некоторые устройства умеют кодировать видео несколькими способами и некоторые
из них могут вызывать проблемы. Указать конкретную кодировку можно параметром:

```bash
scrcpy --encoder OMX.qcom.video.encoder.avc
```

Для просмотра всех возможных вариантов кодировок укажите неверный параметр,
тогда в тексте ошибки можно будет увидеть все доступные варианты:

```bash
scrcpy --encoder _
```

### Захват экрана

#### Запись трансляции

Вы можете вести параллельную запись трансляции:

```bash
scrcpy --record file.mp4
scrcpy -r file.mkv
```

Либо вести только запись, без трансляции в окне приложения:

```bash
scrcpy --no-display --record file.mp4
scrcpy -Nr file.mkv
# для прекращения записи зажмите Ctrl+C
```

Во время трансляции приложение может [пропускать кадры 🇬🇧][packet delay variation]
для снижения нагрузки. Например, если на экране ничего не менется или изображение
не успевает передаваться. Тем не менее, если ведётся запись, то все
пропущенные кадры будут записаны в любом случае.

[packet delay variation]: https://en.wikipedia.org/wiki/Packet_delay_variation


#### Перенаправление на виртуальное v4l2 устройство

На Linux возможно перенаправлять видеопоток на виртуальное v4l2 устройство.
Таким образом, видеопоток с устройства возможно использовать, например,
в качестве видеопотока веб-камеры.

Для работы установите модуль `v4l2loopback`:

```bash
sudo apt install v4l2loopback-dkms
```

И создайте новое виртуальное v4l2 устройство:

```bash
sudo modprobe v4l2loopback
```

После, созданное устройство будет доступно по пути `/dev/videoN`, где
`N` - номер устройства. Возможно создание нескольких виртуальных устройств.
Более подробную информацию по виртуальным v4l2 устройствам
[можно найти здесь](https://github.com/umlaeute/v4l2loopback#options).

Все доступные v4l2 устройства можно увидеть при помощи одной из команд:

```bash
# требуется пакет v4l-utils
v4l2-ctl --list-devices

# способ не требующий дополнительных пакетов
ls /dev/video*
```

Примеры перенаправления трансляции на виртуальное v4l2 устройство:

```bash
scrcpy --v4l2-sink=/dev/videoN               # отображать в окне и писать в v4l2 устройство
scrcpy --v4l2-sink=/dev/videoN --no-display  # не отображать окно приложения
scrcpy --v4l2-sink=/dev/videoN -N            # краткая версия
```

(замените `N` на идентификатор виртуального устройства, представленного в `ls /dev/video*`)

Перенаправленную трансляцию можно открыть любым v4l2 совместимым инструментом:

```bash
ffplay -i /dev/videoN
vlc v4l2:///dev/videoN   # VLC плеер может добавлять незначительную задержку из-за буфериации
```

Перенаправление может быть полезно для прямой работы с трансляцией через [OBS студию][OBS].

[OBS]: https://obsproject.com/fr


### Подключение устройства

#### Беспроводной способ

_Scrcpy_ для общения с устройством использует `adb`, который поддерживает [удалённое подключение через WiFi][connect]:

1. Подключите смартфон к одной WiFi сети с вашим ПК.
2. Узнайте IP адрес смартфона, для этого перейдите в **Настройки** -> **О телефоне** -> **Состояние**.
   Или воспользуйтесь командой на вашем ПК, когда смартфон подключён по проводу:

    ```bash
    adb shell ip route | awk '{print $9}'
    ```

3. Переведите ADB в беспроводной режим: `adb tcpip 5555`.
4. Подключите ADB через WiFi к смартфону: `adb connect IP_УСТРОЙСТВА:5555` _(замените `IP_УСТРОЙСТВА`)_.
5. Запустите `scrcpy` как обычно.

При таком способе подключения может быть полезным снизить битрейт:

```bash
scrcpy --bit-rate 2M --max-size 800
scrcpy -b2M -m800  # краткая версия
```

[connect]: https://developer.android.com/studio/command-line/adb.html#wireless


#### Трансляция с нескольких устройств

Если несколько устройств подключены и отображаются в `adb devices`, вам необходимо
указать идентификатор конкретного устройства:

```bash
scrcpy --serial 0123456789abcdef
scrcpy -s 0123456789abcdef  # краткая версия
```

Если требуемое устройство подключено через WiFi:

```bash
scrcpy --serial 192.168.0.1:5555
scrcpy -s 192.168.0.1:5555  # краткая версия
```

Таким образом, возможен запуск нескольких экземпляров _scrcpy_ для трансляции разных устройств.

#### Автоматическая трансляция при подключении устройства

Это возможно при помощи [AutoAdb 🇬🇧][AutoAdb]:

```bash
autoadb scrcpy -s '{}'
```

[AutoAdb]: https://github.com/rom1v/autoadb

#### SSH тунель

Можно подключаться к устройствам, подключённым к удалённым сессиям ADB.
Например, если устройство подключено к вашему серверу, вы можете использовать SSH тунель,
чтобы получить доступ к удалённой ADB сессии и прокинуть её на ваш компьютер.

```bash
adb kill-server    # остановка локального ADB сервера
ssh -CN -L5037:localhost:5037 -R27183:localhost:27183 ваш_удалённый_сервер
# оставьте терминал открытым
```

С другого терминала:

```bash
scrcpy
```

Чтобы предотвратить удалённый проброс портов, необходимо пробросить соединение принудительно.
(используйте `-L` вместо `-R`):

```bash
adb kill-server    # остановка локального ADB сервера
ssh -CN -L5037:localhost:5037 -L27183:localhost:27183 your_remote_computer
# оставьте терминал открытым
```

С другого терминала:

```bash
scrcpy --force-adb-forward
```


Как и в случае с беспроводным соединением, может быть полезным снизить качество:

``` bash
scrcpy -b2M -m800 --max-fps 15 # битрейт 2Мб/с, разрешение 800 пикселей и 15 кадров в секунду
```

### Настройка окна

#### Заголовок

По умолчанию, в названии окна отображается модель смартфона.
Можно изменить заголовок на любой другой:

```bash
scrcpy --window-title 'Презентация новой фичи'
```

#### Позиционирование и размер

Позиция и размер окна тоже могут быть утсановлены вами:

```bash
scrcpy --window-x 100 --window-y 100 --window-width 800 --window-height 600
```

#### Безрамочность

Рамка окна и стандартные кнопки управления окном могут быть скрыты:

```bash
scrcpy --window-borderless
```

#### Поверх всех окон

Scrcpy может отображаться в приоритетном режиме поверх других окон:

```bash
scrcpy --always-on-top
```

#### Полный экран

Приложение может быть развёрнуто на весь экран:

```bash
scrcpy --fullscreen
scrcpy -f  # краткая версия
```

Полноэкранный режим может быть переключён во время трансляции комбинацией <kbd>MOD</kbd>+<kbd>f</kbd>.

#### Поворот трансляции в окне

Изображение трансляции в окне приложения можно вращать независимо
от ориентации исходного и записываемого видеопотока:

```bash
scrcpy --rotation 1
```

Возможные значения:
 - `0`: без поворота
 - `1`: 270 / -90 градусов (поворот влево)
 - `2`: 180 градусов (разворот)
 - `3`: 90 градусов (поворот вправо)

Поворот может быть изменён во время трансляции используя комбинацию <kbd>MOD</kbd>+<kbd>←</kbd> _(влево)_
и <kbd>MOD</kbd>+<kbd>→</kbd> _(вправо)_.

В _scrcpy_ есть 3 разных режима поворота:
 - <kbd>MOD</kbd>+<kbd>r</kbd> заставляет устройство принудительно повернуть экран между горизонтальным
   и вертикальным режимами (запущенное приложение может закрыться, если оно не поддерживает
   требуемый режим).
 - [`--lock-video-orientation`](#фиксация-ориентации-видеопотока) влияет на трансляцию и запись
   (видеопоток, передаваемый с устройства). Если включена запись, то она будет повёрнута тоже.
 - `--rotation` (or <kbd>MOD</kbd>+<kbd>←</kbd>/<kbd>MOD</kbd>+<kbd>→</kbd>)
   Поворот только трансляции отображаемой в окне приложения. Это не повлияет на запись.


### Прочие настройки

#### Запретить управление с окна

Возможно запретить управление устройством через трансляцию.
Таким образом станет невозможным использовать клавиатуру и мышь при взаимодействии
с трансляцией. Перетаскивание файлов и копирование с буфера обмена тоже станут недоступны:

```bash
scrcpy --no-control
scrcpy -n
```

#### Трансляция с конкретного дисплея

Если устройство поддерживает несколько дисплеев или к нему подключены дополнительные
мониторы, возможно указать источник для трансляции:

```bash
scrcpy --display 1
```

Список всех источников можно посмотреть командой ниже:

```bash
adb shell dumpsys display   # ищите "mDisplayId=" в результатах выполнения команды
```

Управление на не стандартном дисплее поддерживается только на устройствах с Android 10 и выше.


#### Не позволять экрану гаснуть

Если устройство долго не используется, оно, как правило, гасит экран.
Если это неприемлимо во время вашей трансляции или записи, то такое
поведение может быть предотвращено:

```bash
scrcpy --stay-awake
scrcpy -w # краткая версия
```

После отключения _scrcpy_, устройство снова сможет гасить экран.


#### Принудительно погасить или включить экран

Перед началом трансляции можно погасить экран.
Для этого укажите следующий аргумент:

```bash
scrcpy --turn-screen-off
scrcpy -S # краткая версия
```

Или воспользуйтесь комбинацией <kbd>MOD</kbd>+<kbd>o</kbd> во время трансляции.

Чтоб обратно включить экран воспользуйтесь <kbd>MOD</kbd>+<kbd>Shift</kbd>+<kbd>o</kbd>.

На Android, кнопка `ПИТАНИЯ` всегда включает экран. Если
`ПИТАНИЕ` эмулируется через _scrcpy_ (через правый клик или <kbd>MOD</kbd>+<kbd>p</kbd>),
оно произойдёт с небольшой задержкой.
Физическое нажатие кнопки `ПИТАНИЯ` продолжит работать как обычно и будет управлять экраном.

Если устройство способно переходить в режим сна при погашеном экране, это можно предотвратить:

```bash
scrcpy --turn-screen-off --stay-awake
scrcpy -Sw # краткая версия
```

Таким образом устройство погасит экран, но не будет переходить в режим сна, а трансляция продолжиться
как если бы экран был включён.


#### Отображать касания

Может быть полезно включить отображение касаний во время различных презентаций.
Android позволяет включить эту опцию вручную в _Настройках разработчика_.
Либо _scrcpy_ может сделать это за вас на время трансляции:

```bash
scrcpy --show-touches
scrcpy -t # краткая версия
```

Касания будут работать только для _физических нажатий_ на экран устройства.
Вы не увидите точки касания если будете управлять устройством при помощи мыши
через _scrcpy_.


#### Отключить заставку на ПК

По умолчанию _scrcpy_ не запрещает вашему ПК включать заставку во время трансляции.
Будет неудобно, если во время презентации ваш ноутбук вместо трансляции покажет всем заставку.
Это можно предотвратить:

```bash
scrcpy --disable-screensaver
```


### Управление через окно трансляции

#### Вращение экрана устройства

Нажмите <kbd>MOD</kbd>+<kbd>r</kbd> чтобы переключиться между горизонтальной и вертикальной раскладкой.
Эта функция будет работать только если приложение на устройстве поддерживает нужную раскладку.


#### Копирование и вставка

Буфер обмена автоматически будет синхронизирован с буфером обмена устройства.

Любая <kbd>Ctrl</kbd> комбинация транслируется на устройство. В частности:
 - <kbd>Ctrl</kbd>+<kbd>c</kbd> обычно копирует
 - <kbd>Ctrl</kbd>+<kbd>x</kbd> обычно вырезает
 - <kbd>Ctrl</kbd>+<kbd>v</kbd> обычно вставляет (после синхронизации буферов обмена)

Обычно это работает так, как вы ожидаете.

Но, всё зависит и от приложения, которое запущено на устройстве.
Например, _Termux_ выполняет SIGINT при нажатии <kbd>Ctrl</kbd>+<kbd>c</kbd>, вместо копирования.
_K-9 Mail_ при этой комбинации создаёт новое сообщение.

Чтобы копировать, вырезать и вставить в таких случаях используйте следующие комбинации
(поддерживается только на устройствах с Android 7 и выше):
 - <kbd>MOD</kbd>+<kbd>c</kbd> имитирует копирование
 - <kbd>MOD</kbd>+<kbd>x</kbd> имитирует вырезание
 - <kbd>MOD</kbd>+<kbd>v</kbd> имитирует вставку (после синхронизации буферов обмена)

В дополнение, <kbd>MOD</kbd>+<kbd>Shift</kbd>+<kbd>v</kbd> позволяет имитировать
вставку текста через нажатие клавиш клавиатуры. Может быть полезным в приложениях,
которые не поддерживают вставку совсем. Например _Termux_ или приложения ограничивающие
вставку стандартным способом, скажем, интернет банкинг и различные формы ввода паролей.

Но такой метод работает только для ASCII текста и вставить русский текст не выйдет.

**ВНИМАНИЕ:** Операции вставки будут копировать данные буфера обмена вашего ПК
в буфер устройства, который, доступен для чтения приложениям на устройстве.
Будтье осторожны и не вставляйте приватные данные (например, пароли).
Для безопасной вставки можно воспользоваться способом выше, через эмуляцию клавиш.

Некоторые устройства ведут себя не корректно при попытке установить данные в буфер
обмена через _scrcpy_. В таких случаях используйте `--legacy-paste`, что заставит
<kbd>Ctrl</kbd>+<kbd>v</kbd> и <kbd>MOD</kbd>+<kbd>v</kbd> вставлять текст посимвольно,
аналогично комбинации <kbd>MOD</kbd>+<kbd>Shift</kbd>+<kbd>v</kbd>.

#### Масштабирование пальцами

"Масштабирования пальцами" можно эмулировать комбинацией: <kbd>Ctrl</kbd>+_click-and-move_.

Удерживайте <kbd>Ctrl</kbd> и одновременно зажмите левую кнопку мыши.
Пока удерживается левая кнопка, операции масштабирования и поворота
(если поддерживается приложением) будут работать относительно центра экрана.

_Scrcpy_ генерирует дополнительное событие касания в центре экрана.


#### Настройка ввода клавиатуры

Существует 2 способа эмулировать [события ввода][textevents] с клавиатуры:
 - _события клавиши (key event)_, указывает на нажатие клавиши;
 - _события текста (text event)_, указывает на ввод символа.

По умолчанию, символы вводятся через эмуляцию нажатия клавиш.
Таким образом, вы можете ожидать корректное поведение клавиатуры, например, в играх (WASD клавиши).

Но такой способ [вызывает проблемы][prefertext] в других ситуациях.
Например, невозможность ввести русские символы или несоответствие раскладки
клавиатуры компьютера раскладке устройства.

Проблема может быть решена переключением режима:

```bash
scrcpy --prefer-text
```

(но это сломает управление в играх)

[textevents]: https://blog.rom1v.com/2018/03/introducing-scrcpy/#handle-text-input
[prefertext]: https://github.com/Genymobile/scrcpy/issues/650#issuecomment-512945343


#### Зажатие клавиш

По умолчанию, зажатие клавиши будет генерировать повторяющиеся нажатия.
Это может вызвать проблемы в некоторых играх.

Способ исключить эту проблему:

```bash
scrcpy --no-key-repeat
```


#### Правый и средний клик

По умолчанию, правый клик эмулирует кнопку `НАЗАД` (или `ПИТАНИЕ`), а средний
эмулирует `ДОМОЙ`. Чтобы отключить такое поведение и передавать клавиши
мыши напрямую, воспользуйтесь флагом ниже:

```bash
scrcpy --forward-all-clicks
```


### Копирование файлов и установка приложений

#### Установка приложений

Для установки приложения (файла с расширением `.apk`) перетащите его на экран трансляции.

Это вызовет тихую установку без уведомлений на экране смартфона.
Но вы сможете видеть результат в консоли.


#### Копирование файла на устройство

Перетащите файл (без расширения `.apk`) на экран трансляции и он будет
скопирован в `/sdcard/Download/` на устройстве.

Файл копируется тихо, без информации на эране устройства.
Но вы сможете видеть результат в консоли.

Директорию копирования можно изменить:

```bash
scrcpy --push-target=/sdcard/Movies/
```

Копировать файл с устройства на ПК средствами _scrcpy_ невозможно.
Но вы можете воспользоваться функционалом ADB:

```bash
adb pull путь/на/устройстве путь/на/вашем/ПК
```


### Трансляция звука

_Scrcpy_ не умеет транслировать звук, для этих целей используйте [sndcpy 🇬🇧][sndcpy].

Обратите внимание на [эту ветку обсуждений 🇬🇧][issue #14].

[sndcpy]: https://github.com/rom1v/sndcpy
[issue #14]: https://github.com/Genymobile/scrcpy/issues/14


## Горячие клавиши

В списке далее <kbd>MOD</kbd> - модификатор для горячих клавиш.
По умолчанию это <kbd>Alt</kbd> (левый) или <kbd>Super</kbd> (левый).

Клавиша модификатора может быть изменена при помощи `--shortcut-mod`.
Возможные значения: `lctrl`, `rctrl`, `lalt`, `ralt`, `lsuper` and `rsuper`.
Например:

```bash
# используется правый Ctrl
scrcpy --shortcut-mod=rctrl

# используются левые Ctrl+Alt или левый Super
scrcpy --shortcut-mod=lctrl+lalt,lsuper
```

_<kbd>[Super]</kbd> - это <kbd>Win</kbd> для Windows или <kbd>Cmd</kbd> для macOS._

[Super]: https://ru.wikipedia.org/wiki/Super_(%D0%BA%D0%BB%D0%B0%D0%B2%D0%B8%D1%88%D0%B0)

 | Действие                                    | Горячие клавиши
 | ------------------------------------------- |:-----------------------------
 | Переключить полноэкранный режим             | <kbd>MOD</kbd>+<kbd>f</kbd>
 | Повернуть экран влево                       | <kbd>MOD</kbd>+<kbd>←</kbd> _(влево)_
 | Повернуть экран вправо                      | <kbd>MOD</kbd>+<kbd>→</kbd> _(вправо)_
 | Масштабировать окно 1:1 (pixel-perfect)     | <kbd>MOD</kbd>+<kbd>g</kbd>
 | Масштабировать окно до скрытия чёрных полос | <kbd>MOD</kbd>+<kbd>w</kbd> \| _Двойной левый клик¹_
 | Эмулировать `ДОМОЙ`                         | <kbd>MOD</kbd>+<kbd>h</kbd> \| _Средний клик_
 | Эмулировать `НАЗАД`                         | <kbd>MOD</kbd>+<kbd>b</kbd> \| _Правый клик²_
 | Эмулировать `ПЕРЕКЛЮЧИТЬ_ПРИЛОЖЕНИЕ`        | <kbd>MOD</kbd>+<kbd>s</kbd> \| _Четвёртая кнопка мыши³_
 | Эмулировать `МЕНЮ` (разблокировать экран)   | <kbd>MOD</kbd>+<kbd>m</kbd>
 | Эмулировать `ГРОМКОСТЬ_ВВЕРХ`               | <kbd>MOD</kbd>+<kbd>↑</kbd> _(вверх)_
 | Эмулировать `ГРОМКОСТЬ_ВНИЗ`                | <kbd>MOD</kbd>+<kbd>↓</kbd> _(вниз)_
 | Эмулировать `ПИТАНИЕ`                       | <kbd>MOD</kbd>+<kbd>p</kbd>
 | Включить экран                              | _Правый клик²_
 | Выключить экран (оставить трансляцию)       | <kbd>MOD</kbd>+<kbd>o</kbd>
 | Включить экран                              | <kbd>MOD</kbd>+<kbd>Shift</kbd>+<kbd>o</kbd>
 | Повернуть экран устройства                  | <kbd>MOD</kbd>+<kbd>r</kbd>
 | Раскрыть панель уведомлений                 | <kbd>MOD</kbd>+<kbd>n</kbd> \| _Пятая кнопка мыши³_
 | Раскрыть панель управления                  | <kbd>MOD</kbd>+<kbd>n</kbd>+<kbd>n</kbd> \| _Двойной клик пятой кнопки мыши³_
 | Скрыть панели                               | <kbd>MOD</kbd>+<kbd>Shift</kbd>+<kbd>n</kbd>
 | Копировать в буфер обмена⁴                  | <kbd>MOD</kbd>+<kbd>c</kbd>
 | Вырезать в буфер обмена⁴                    | <kbd>MOD</kbd>+<kbd>x</kbd>
 | Синхронизировать буфера и вставить⁴         | <kbd>MOD</kbd>+<kbd>v</kbd>
 | Эмулировать вставку текста клавиатурой      | <kbd>MOD</kbd>+<kbd>Shift</kbd>+<kbd>v</kbd>
 | Вкл/Выкл счётчик кадров (в консоль)         | <kbd>MOD</kbd>+<kbd>i</kbd>
 | Масштабирование двумя пальцами              | <kbd>Ctrl</kbd>+_Кликнуть и удерживать_

_¹Двойной клик по чёрной рамке скроет её._  
_²Правый клик включит экран если он выключен, либо эмулирует `НАЗАД` если включён._  
_³4 и 5 кнопки мыши если они у вас есть._  
_⁴Только Android 7 и выше._

Горячие клавиши, где присутствует повтор кнопки, сработают если нажать её дважды.
Например, чтобы выполнить "Раскрыть панель управления":

 1. Нажмите и удерживайте <kbd>MOD</kbd>.
 2. Дважды нажмите <kbd>n</kbd>.
 3. Отпустите <kbd>MOD</kbd>.

Все <kbd>Ctrl</kbd>+_клавиша_ комбинации передаются напрямую в устройство, поэтому они
могут обрабатываться конкретным приложением, которое может не позволить выполнять
какие-то действия или обрабатывать их по особому.


## Произвольный путь до ADB и сервера scrcpy

Чтобы использовать файл конкретного _adb_ сервера, укажите путь к нему в переменной окружения `ADB`:

```bash
ADB=/путь/к/adb/серверу scrcpy
```

Чтобы переопределить путь до `scrcpy-server`, настройте его в `SCRCPY_SERVER_PATH` окружениия.
Обратите внимание, `SCRCPY_SERVER_PATH` должен содержать полный путь до `scrcpy-server.jar`.

[useful]: https://github.com/Genymobile/scrcpy/issues/278#issuecomment-429330345


## Почему называется _scrcpy_?

Я поспорил с коллегой, что смогу придумать непроизносимое название, вроде [gnirehtet 🇬🇧][gnirehtet].

[`strcpy` 🇬🇧][`strcpy`] копирует **стр**оку; `scrcpy` копирует **scr**een (прим: Экран).

[gnirehtet]: https://github.com/Genymobile/gnirehtet
[`strcpy`]: http://man7.org/linux/man-pages/man3/strcpy.3.html


## Как сделать собственную сборку?

Смотрите [инструкцию по сборке 🇬🇧][BUILD].


## Часто задаваемые вопросы

Смотрите [Вопрос-Ответ 🇬🇧](FAQ.md).


## Для разработчиков

Прочтите [страницу разработчика 🇬🇧][developers page].

[developers page]: DEVELOP.md


## Лицензия

### Перевод

> Перевод не является официальной Лицензией и предназначен для ознакомительных целей.  
> Для получения официального текста Лицензии воспользуйтесь оригиналом.

    Авторское право 2018 "Дженимобайл" (Genymobile)
    Авторское право 2018-2021 Ромен Вимонт (Romain Vimont)

    Лицензировано Apache 2.0 лицензией ("Лицензия");
    Вы можете использовать этот файл только в соответствии Лицензии.
    Вы можете получить копию оригинальной Лицензии по адресу

        http://www.apache.org/licenses/LICENSE-2.0

    Если иное не требуется действующим законодательством или не
    согласовано в письменной форме, программное обеспечение предоставляется
    на условиях "КАК ЕСТЬ", БЕЗ ПРОЧИХ ГАРАНТИЙ ИЛИ УСЛОВИЙ, явных и
    подразумевающихся.
    Смотрите Лицензию для получения информации о правах и ограничениях
    на конкретных языках, регулируемых действующей Лицензией.

### Оригинал

    Copyright (C) 2018 Genymobile
    Copyright (C) 2018-2021 Romain Vimont

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

## Статьи

- [Введение в scrcpy 🇬🇧][article-intro]
- [Работа с scrcpy через WiFi 🇬🇧][article-tcpip]

[article-intro]: https://blog.rom1v.com/2018/03/introducing-scrcpy/
[article-tcpip]: https://www.genymotion.com/blog/open-source-project-scrcpy-now-works-wirelessly/

## Перевод и оригинальная документация

1. Авторское право на оригинальное программное обеспечение сохраняется за автором
   оригинального программного обеспечения в соответствии с оригинальной Лицензией.
2. Русскоязычная документация может не соответствовать актуальной версии программы.     
3. Перевод не является прямым цитированием автора и не может быть использован для
   регулирования любых юридических вопросов.
4. Перевод может содержать неточности и предназначен для ознакомления.
5. Перевод содержит пометки переводчика и перефразированный текст для облегченного
   понимания носителями русского языка.

Для получения актуальной информации обратитесь к [оригинальной англоязычной документации 🇬🇧](README.md).

Для поддержания перевода в актуальном состоянии и исправления ошибок просьба создавать issue с упоминанием автора перевода.

Перевод на русский выполнил @jkulvich (Кулагин Юрий / Kulagin Yuri)

