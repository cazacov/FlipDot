# BROSE VM_IIC Flip-dot Display Controller

Может управлять до 8 матрицами разрешением до 28x20 каждая. 

- Внешний интерфейс - I2C поверх RS-422.
- Интрефейс матрицы - 60-контактный разъём Brose.

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
| 0x40  | 0       | X Enable Matrix 8 |
|       | 1       | X Enable Matrix 7 |
|       | 2       | X Enable Matrix 6 |
|       | 3       | X Enable Matrix 5 |
|       | 4       | X Enable Matrix 4 |
|       | 5       | X Enable Matrix 3 |
|       | 6       | X Enable Matrix 2 |
|       | 7       | X Enable Matrix 1 |
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

<img src="./_img/Matrix-connector-60pins.png?raw=true" alt="Brose 60 pinout" width="356" height="530">

### Драйверы рядов

Контроллер поддерживает до 20 рядов, для каждый на разъём матрицы выведены пины SETx и RESETx. Одну из микросхем драйверов FP2800A разработчики использовали по-полной, вторая отвечает за ряды с номерами 15-20.

| Сигнал    | Драйвер | Выход |
|---------- |-------- | ----- |
| Y-SET 1   | IC1     | 0A    |
| Y-SET 2   | IC1     | 0B    |
| Y-SET 3   | IC1     | 0C    |
| Y-SET 4   | IC1     | 0D    |
| Y-SET 5   | IC1     | 0E    |
| Y-SET 6   | IC1     | 0F    |
| Y-SET 7   | IC1     | 0G    |
| Y-SET 8   | IC1     | 2A    |
| Y-SET 9   | IC1     | 2B    |
| Y-SET10   | IC1     | 2C    |
| Y-SET11   | IC1     | 2D    |
| Y-SET12   | IC1     | 2E    |
| Y-SET13   | IC1     | 2F    |
| Y-SET14   | IC1     | 2G    |
| Y-SET15   | IC13    | 0A    |
| Y-SET16   | IC13    | 0B    |
| Y-SET17   | IC13    | 0C    |
| Y-SET18   | IC13    | 0D    |
| Y-SET19   | IC13    | 0E    |
| Y-SET20   | IC13    | 0F    |
| Y-RESET 1 | IC1     | 1A    |
| Y-RESET 2 | IC1     | 1B    |
| Y-RESET 3 | IC1     | 1C    |
| Y-RESET 4 | IC1     | 1D    |
| Y-RESET 5 | IC1     | 1E    |
| Y-RESET 6 | IC1     | 1F    |
| Y-RESET 7 | IC1     | 1G    |
| Y-RESET 8 | IC1     | 3A    |
| Y-RESET 9 | IC1     | 3B    |
| Y-RESET10 | IC1     | 3C    |
| Y-RESET11 | IC1     | 3D    |
| Y-RESET12 | IC1     | 3E    |
| Y-RESET13 | IC1     | 3F    |
| Y-RESET14 | IC1     | 3G    |
| Y-RESET15 | IC13    | 1A    |
| Y-RESET16 | IC13    | 1B    |
| Y-RESET17 | IC13    | 1C    |
| Y-RESET18 | IC13    | 1D    |
| Y-RESET19 | IC13    | 1E    |
| Y-RESET20 | IC13    | 1F    |


## Выбор матрицы

Хотя контроллер VM_IIC сам оперирует TTL-уровнями, матрица ожидает на входе управляющий сигнал амплитудой до 24V. После защитных диодов и делителей напряжения 24V->5V на блоках резисторов (SOMC1601/1603) сигналы Module Select 1-8 поступают на входы 8-битного компаратора 74HCT688В и сравниваются с выбраным на DIP-ах адресом панели. При совпадении формируется ENABLE для драйвера оси X FP2800A. Пример матрицы с установленным в "1" адресом:

![Brose flip-dot interfaces](./_img/matrix_interfaces.jpg?raw=true "Разъёмы")

Переключатель с адресом матрицы устанавливается в положение OFF, остальные должны оставаться в ON. Для удобства обслуживания, выбраный адрес положено дублировать маркером на корпусе. Тут, например, указано что матрица должна иметь адрес "8" (номер маршрута):

![Brose flip-dot interfaces](./_img/matrix_nr.jpg?raw=true "Nr 8")

## Фото

<img src="./_img/board_front.jpg?raw=true" alt="VM_IIC board front" width="900" height="600">

<img src="./_img/board_back.jpg?raw=true" alt="VM_IIC board front" width="900" height="600">