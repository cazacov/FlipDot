# Flip-dot Displays with BROSE VM_IIC Controller

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
|       | 4       | Row Low - DATA    |
|       | 5       | Row Low - ENABLE  |
|       | 6       | Row High - DATA   |
|       | 7       | Row High - ENABLE |



## Интерфейс матрицы

Brose flip-dot 60 pinout.

## Выбор матрицы

Хотя контроллер VM_IIC сам оперирует TTL-уровнями, матрица ожидает на входе сингнал размахом до 24V. После защитных диодов и делителей напряжения 24V->5V на блоках резисторов (SOMC1601/1603) сигналы Module Select 1-8 поступают на входы 8-битного компаратора 74HCT688В и сравниваются с выбраным на DIP-ах адресом панели. При совпадении формируется ENABLE для драйвера оси X FP2800A. Пример матрицы с установленным в "1" адресом:

![Brose flip-dot interfaces](./_img/matrix_interfaces.jpg?raw=true "Разъёмы")

Переключатель с адресом матрицы устанавливается в положение OFF, остальные должны оставаться в ON. Для удобства обслуживания, выбраный адрес положено дублировать маркером на корпусе. Тут, например, указано что матрица должна иметь адрес "8" (номер маршрута):

![Brose flip-dot interfaces](./_img/matrix_nr.jpg?raw=true "Nr 8")
