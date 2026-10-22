# mai-se-labs

Учебный проект по дисциплине «Технологии коллективной разработки информационных систем»
(МАИ, группа М3О-108СВ-26).

## Состав проекта

| Файл | Назначение | Разработчик |
|---|---|---|
| `notes.txt` | рабочие заметки по проекту | person2 |
| `tasks.txt` | список задач проекта | person3 |
| `config.txt` | настройки проекта | person1 |
| `src/text_stats.h` | объявления функций подсчёта частот слов | person2 |
| `src/text_stats.cpp` | реализация подсчёта, сортировки и чтения файла | person2 |
| `src/main.cpp` | консольный интерфейс программы `textstats` | person1 |
| `tests/` | юнит-тесты (GoogleTest) и данные для интеграционного теста | person1 |

## Программа textstats

Считает частоты слов в текстовом файле и выводит заданное число самых частых слов.

```
textstats <файл> [--top N]
```

Пример:

```
$ textstats tests/data/sample.txt --top 3
the: 4
and: 2
dog: 2
```

Особенности: регистр не учитывается, пунктуация по краям слова отбрасывается,
при равной частоте слова сортируются по алфавиту.

## Сборка и запуск

```
cmake -S . -B build
cmake --build build -j
./build/textstats tests/data/sample.txt --top 5
```

## Тесты

```
ctest --test-dir build --output-on-failure
```

Юнит-тесты (`unit_tests`, GoogleTest) проверяют подсчёт слов, нормализацию регистра
и пунктуации, обработку пустого ввода, исключение при отсутствии файла и порядок
сортировки. Интеграционный тест `cli_top` запускает собранную программу на файле
`tests/data/sample.txt` и проверяет вывод.

## Проверка стиля

```
clang-format --dry-run --Werror src/*.cpp src/*.h tests/*.cpp
cppcheck --error-exitcode=1 --enable=warning,performance,portability src tests
```

Если форматирование не совпадает: `clang-format -i src/*.cpp src/*.h tests/*.cpp`.

## Непрерывная интеграция

Файл `.github/workflows/ci.yml` описывает четыре задания:

| Задание | Что проверяет |
|---|---|
| `build` | конфигурация и сборка проекта (артефакт — исполняемый файл) |
| `test` | прогон `ctest`: юнит-тесты и интеграционный тест |
| `lint` | форматирование `clang-format` и статический анализ `cppcheck` |
| `docs` | генерация документации Doxygen и публикация на GitHub Pages (только для `main`) |

Запуск выполняется при каждом `push`, при создании Pull Request в `main`
и вручную (`workflow_dispatch`) — вкладка **Actions**.

## Документация

Генерируется из комментариев Doxygen в `src/` и из этого файла:

```
doxygen Doxyfile
```

Результат — `docs/html/index.html`; при выполнении workflow на ветви `main`
документация публикуется на GitHub Pages.

## Работа с репозиторием

- Удалённый репозиторий: https://github.com/CaBa1983/mai-se-labs
- Основная ветвь: `main`
- Изменения вносятся через ветви: `dev`, `dev1`, `dev2`, `dev3`
- Порядок: правка в своём локальном репозитории → `git add` → `git commit` → `git pull` → `git push`
