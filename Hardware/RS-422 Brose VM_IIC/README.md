# BROSE VM_IIC Flip-dot Display Controller

Может управлять до 8 матрицами разрешением до 28x20 каждая. 

Внешний интерфейс - I2C поврех RS-422.
Интрефейс матрицы - 60-контактный разъём Brose.

Контроллер представляет собой расширение шины через I2C подключённое к драйверам оси Y на двух микросхемах Brose 2840 (аналог FP2800A). Драйверы оси X находятся на самих матрицах и упаравляются сигналами Column - xxx и Module Select 1-8.

![Fahrtzielnazeige](./_img/rear.jpg?raw=true "Fahrtzielnazeige")

Разъёмы: 
- 4-х полюсный управление (SDA A/B, SCL A/B)
- Питание 24V
- Подсветка 24V

## Управление

![Flipdot controller VM-IIC](./_img/vm-iic.png?raw=true "Контроллер VM-IIC")

## Расширение шины через I²C

| Адрес | Бит     | Сигнал            |
|------ |-------- | ----------------- |
| 0x40  | 0       | Module Select 8   |
|       | 1       | Module Select 7   |
|       | 2       | Module Select 6   |
|       | 3       | Module Select 5   |
|       | 4       | Module Select 4   |
|       | 5       | Module Select 3   |
|       | 6       | Module Select 2   |
|       | 7       | Module Select 1   |
| 0x42  | 0       | -                 |
|       | 1       | Column - B1       |
|       | 2       | Column - B0       |
|       | 3       | Column - A2       |
|       | 4       | Column - A1       |
|       | 5       | Column - A0       |
|       | 6       | Column - DATA     |
|       | 7       | Row - A2          |
| 0x44  | 0       | Row - A1          |
|       | 1       | Row - A0          |
|       | 2       | Row - B1          |
|       | 3       | Row - B0          |
|       | 4       | Row 1-14 - DATA   |
|       | 5       | Row 1-14 - ENABLE |
|       | 6       | Row 15-20 - DATA  |
|       | 7       | Row 15-20 - ENABLE|



## Интерфейс матрицы

### Brose flip-dot 60 pinout.

### Драйверы рядов

Контроллер поддерживает до 20 рядов, для каждый на разъём матрицы выведены пины SETx и RESETx. Одну из микросхем драйверов FP2800A разработчики использовали по-полной, вторая отвечает за ряды с номерами 15-20.

| Сигнал  | Драйвер | Выход |
|-------- |-------- | ----- |
| SET 1   | IC1     | 0A    |
| SET 2   | IC1     | 0B    |
| SET 3   | IC1     | 0C    |
| SET 4   | IC1     | 0D    |
| SET 5   | IC1     | 0E    |
| SET 6   | IC1     | 0F    |
| SET 7   | IC1     | 0G    |
| SET 8   | IC1     | 2A    |
| SET 9   | IC1     | 2B    |
| SET10   | IC1     | 2C    |
| SET11   | IC1     | 2D    |
| SET12   | IC1     | 2E    |
| SET13   | IC1     | 2F    |
| SET14   | IC1     | 2G    |
| SET15   | IC13    | 0A    |
| SET16   | IC13    | 0B    |
| SET17   | IC13    | 0C    |
| SET18   | IC13    | 0D    |
| SET19   | IC13    | 0E    |
| SET20   | IC13    | 0F    |
| RESET 1 | IC1     | 1A    |
| RESET 2 | IC1     | 1B    |
| RESET 3 | IC1     | 1C    |
| RESET 4 | IC1     | 1D    |
| RESET 5 | IC1     | 1E    |
| RESET 6 | IC1     | 1F    |
| RESET 7 | IC1     | 1G    |
| RESET 8 | IC1     | 3A    |
| RESET 9 | IC1     | 3B    |
| RESET10 | IC1     | 3C    |
| RESET11 | IC1     | 3D    |
| RESET12 | IC1     | 3E    |
| RESET13 | IC1     | 3F    |
| RESET14 | IC1     | 3G    |
| RESET15 | IC13    | 1A    |
| RESET16 | IC13    | 1B    |
| RESET17 | IC13    | 1C    |
| RESET18 | IC13    | 1D    |
| RESET19 | IC13    | 1E    |
| RESET20 | IC13    | 1F    |


## Выбор матрицы

Хотя контроллер VM_IIC сам оперирует TTL-уровнями, матрица ожидает на входе управляющий сигнал амплитудой до 24V. После защитных диодов и делителей напряжения 24V->5V на блоках резисторов (SOMC1601/1603) сигналы Module Select 1-8 поступают на входы 8-битного компаратора 74HCT688В и сравниваются с выбраным на DIP-ах адресом панели. При совпадении формируется ENABLE для драйвера оси X FP2800A. Пример матрицы с установленным в "1" адресом:

![Brose flip-dot interfaces](./_img/matrix_interfaces.jpg?raw=true "Разъёмы")

Переключатель с адресом матрицы устанавливается в положение OFF, остальные должны оставаться в ON. Для удобства обслуживания, выбраный адрес положено дублировать маркером на корпусе. Тут, например, указано что матрица должна иметь адрес "8" (номер маршрута):

![Brose flip-dot interfaces](./_img/matrix_nr.jpg?raw=true "Nr 8")
