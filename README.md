# Project Title

Wps

## Table of Contents

- [About](#about)
- [Installing](#installing)

## About <a name = "about"></a>

Russian open source graphic raster editor

## Installing <a name = "installing"></a>

1. Пройти регистрацию и скачать QT https://www.qt.io/

2. При установке .exe войти в аккаунт. 

3. Слева внизу настройки. Ручная настройка прокси сервера - ставим proxy.quterussia.ru и порт 31031

![alt text](Trash/123.png)

4. Дальше простро устанавливаем и ожидаем..

PS. Так же у вас должен быть установлен CMake, MSVC 2022 64amd. Базовые расширения дл Qt в VScode. Так же для себя можно установить кучу разных классных расширений для упрощени работы)

5. В видео "Запуск" показан момент ошибки с rainbowlabel.h. Это из-за того, что для этого кастомного файла со стилями нужно прописать путь, так как мы компилируем файл "Canvas.ui"