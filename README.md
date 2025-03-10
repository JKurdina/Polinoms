# Лабораторная работа: Мономы и полиномы

## Описание
Данная лабораторная работа представляет собой реализацию класса для работы с полиномами. Полиномы представлены в виде списка мономов, где каждый моном содержит коэффициенты и степени переменных \(x\), \(y\) и \(z\). В программе реализованы основные операции над полиномами, такие как сложение, вычитание, умножение, а также вычисление значения полинома для заданных значений переменных.

## Основные компоненты

### 1. Структура `Monom`
- Представляет моном (одночлен) в полиноме.
- Содержит:
  - `coef` — коэффициент монома.
  - `s` и `s_minus` — степени \(x\), \(y\) и \(z\).
- Методы для получения степеней:
  - `getX()`, `getY()`, `getZ()`.

### 2. Класс `Polinom`
Основные методы:
- **`add(Monom monom)`**: Добавляет моном в полином с сохранением порядка.
- **`addLast(Monom monom)`**: Добавляет моном в конец списка.
- **`clean()`**: Очищает полином, удаляя все мономы.
- **`calculate(int x, int y, int z)`**: Вычисляет значение полинома для заданных значений переменных.
- **Операторы**:
  - `+`, `-`, `*` — сложение, вычитание и умножение полиномов.
  - `==`, `!=` — сравнение полиномов.
  - `<<`, `>>` — ввод и вывод полинома.
