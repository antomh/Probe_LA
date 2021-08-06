------
# Probe_LA
------
ver.0.18
------------------------------
Updates:
 - доработана функция Callback'а таймеров для корректной обработки данных и получения значения ширины импульса
 
ver.0.17а
------------------------------
Updates:
 - небольшие доработки
 
ver.0.17
------------------------------
Updates:
 - немного изменена структура проекта, добавлена рабочая утилита по взаимодействию со щупом, переименованы папки
 - закончено добавление кода [*kozlov-dev*](https://github.com/kozlov-dev)
 
ver.0.16a
------------------------------
Updates:
 - незначительные доработки
 
ver.0.16
------------------------------
Updates:
 - изменена функция инициализации структуры DevNVRAM при старте устройства
 - написана и протестирована команда получения чек-суммы калибровочной таблицы
 - прочие изменения
 
ver.0.15
------------------------------
Updates:
 - исправление некоторых ошибок и незначительные улучшения
 
ver.0.14
------------------------------
Updates:
 - добавлена функция начальной инициализации калибровочной таблицы, проверки, есть ли таблица в памяти, чтения таблица из памяти
 - доработана функция записи калибровочной таблицы в оперативную память
 - начат процесс добавления кода, сделанного [*kozlov-dev*](https://github.com/kozlov-dev)
 
ver.0.13
------------------------------
Updates:
 - доделан обработчик кнопок
 - протестирована запись в FLASH память с помощью утилиты управления

ver.0.12
------------------------------
Updates:
 - ВНИМАНИЕ !
   В этой версии был перегенерирован проект в CubeIDE, если будут какие-либо ошибки - смотреть, что могло перезатереться.
 - продолжена работа над обработчиками нажатий кнопок, протестирована первая версия обработки

ver.0.11
------------------------------
Updates:
 - организован пакетны прием данных по USB, проведено тестирование
 - начата работа над написанием обработчиков нажатий кнопок по прерыванию
 
ver.0.10
------------------------------
Updates:
 - продуман и переделан формат приема данных по USB, сделаны необходимые заготовки для написания функционала приема данных по USB
 
ver.0.09
------------------------------
Updates:
 - добавлены файлы с функциями для расчета значения CRC
 - начата переделка функции обработки приема пакета данных по USB
 
ver.0.08
------------------------------
Updates:
 - доработана и проверена функция записи во флеш-память, также они выделены в отдельный модуль .c и .h файлов

ver.0.07
------------------------------
Updates:
 - проведены доработки функции записи во флеш-память

ver.0.06
------------------------------
Updates:
 - код подчищен от предупреждений, изменена инициализация USB: контакт DP был подтянут к питанию, теперь ни к чему (NOPULL)

v0.05
------------------------------
Реализация с записанной калибровочной таблицей во flash
