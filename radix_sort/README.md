# Сортировка за линейное время. 

## Формулировка задачи

Ограничение времени:	2 секунды
Ограничение памяти:	150Mb
Ввод:	стандартный ввод или input.txt
Вывод:	стандартный вывод или output.txt

Требуется разработать программу, осуществляющую ввод пар «ключ-значение», их упорядочивание по возрастанию ключа указанным алгоритмом сортировки за линейное время и вывод отсортированной последовательности.
Вариант задания определяется типом ключа (и соответствующим ему методом сортировки) и типом значения:
Поразрядная сортировка.

Тип ключа: телефонные номера, с кодами стран и городов в формате +<код страны> <код города> телефон.

Тип значения: строки переменной длины (до 2048 символов).

## Формат ввода

На каждой непустой строке входного файла располагается пара «ключ-значение», в которой ключ указан согласно заданию, затем следует знак табуляции и указано соответствующее значение.

## Формат вывода

Выходные данные состоят из тех же строк, что и входные, за исключением пустых и порядка следования.

## Пример

| Ввод                               | Вывод                                 |
|------------------------------------|---------------------------------------|
|+7-495-1123212	xGfxrxGGxrxMMMMfrrrG |+7-495-1123212	xGfxrxGGxrxMMMMfrrrG   |
|+375-123-1234567	xGfxrxGGxrxMMMMfrrr|+7-495-1123212	xGfxrxGGxrxMMMMfrr     |
|+7-495-1123212	xGfxrxGGxrxMMMMfrr   |+375-123-1234567	xGfxrxGGxrxMMMMfrrr  |
|+375-123-1234567	xGfxrxGGxrxMMMMfr  |+375-123-1234567	xGfxrxGGxrxMMMMfr    |


