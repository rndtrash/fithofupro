# FiThoFuPro

## Установка

### Из репозитория

TODO

### Из исходников

#### Установка зависимостей

Для Ubuntu/Debian:
```
sudo apt install build-essential cmake qtbase5-dev
```

#### Сборка программы

1. В корневой папке репозитория создайте папку build (удалите и пересоздайте, если она уже существует)

2. В созданной папке выполните следующую команду:
```
cmake ..
```

3. Запустите сборку командой `make`

#### Создание .DEB пакета

В папке build выполните следующую команду:
```
cpack -G DEB -D CPACK_DEBIAN_PACKAGE_MAINTAINER=TO_BE_FILLED
```

## F.A.Q.

**Q.** Почему в коде приложения встречаются и русские, и английские сообщения/комментарии/etc?

**A.** Мне пока впадлу реализовывать систему перевода приложения под системный язык (даже если в Qt это делается легко и просто) до того, как приложение будет выполнять свою функцию, так что пусть пока будет так, но я стремлюсь к исправлению сего братан-момента!

## Лицензия

FiThoFuPro - fight with your procrastination using non-effective methods!
Copyright (C) 2021 Ivan Kuzmenko

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
