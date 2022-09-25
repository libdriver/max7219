### 1. Chip

#### 1.1 Chip Info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

spi pin: SCK/MISO/MOSI/CS  PA5/PA6/PA7/PA4.

### 2. Shell

#### 2.1 Shell Parameter

baud rate: 115200.

data bits : 8.

stop bits: 1.

parity: none.

flow control: none.

### 3. MAX7219

#### 3.1 Command Instruction

​          max7219 is a basic command which can test all max7219 driver function:

​           -i        show max7219 chip and driver information.

​           -h       show max7219 help.

​           -p       show max7219 pin connections of the current board.

​           -t (display | matrix_cascade)

​           -t display        run max7219 display test.

​           -t matrix_cascade        run max7219 matrix cascade test.

​           -c (basic (-init | -deinit | -num <number> | -matrix <pattern> ) | cascade (-init | -deinit | -matirx <pattern>) )

​           -c basic -init        run max7219 basic init function.

​           -c basic -deinit        run max7219 basic deinit function.

​           -c basic -num <number>        run max7219 basic number display function. number length must be 8. each number can be "0" - "9".

​           -c basic -matirx <pattern>        run max7219 basic matirx display function. matirx can be "-", "|" or "+".

​           -c cascade -init        run max7219 cascade init function.

​           -c cascade -deinit        run max7219 cascade deinit function.

​           -c cascade -matirx <pattern>        run max7219 cascade matirx display function. matirx can be "-", "|" or "+".

#### 3.2 Command Example

```shell
max7219 -i

max7219: chip is Maxim Integrated MAX7219.
max7219: manufacturer is Maxim Integrated.
max7219: interface is SPI.
max7219: driver version is 2.0.
max7219: min supply voltage is 4.0V.
max7219: max supply voltage is 5.5V.
max7219: max current is 320.00mA.
max7219: max temperature is 85.0C.
max7219: min temperature is -40.0C.
```

```shell
max7219 -p

max7219: SCK connected to GPIOA PIN5.
max7219: MOSI connected to GPIOA PIN7.
max7219: CS connected to GPIOA PIN4.
```

```shell
max7219 -t display

max7219: chip is Maxim Integrated MAX7219.
max7219: manufacturer is Maxim Integrated.
max7219: interface is SPI.
max7219: driver version is 2.0.
max7219: min supply voltage is 4.0V.
max7219: max supply voltage is 5.5V.
max7219: max current is 320.00mA.
max7219: max temperature is 85.0C.
max7219: min temperature is -40.0C.
max7219: start display test.
max7219: display test.
max7219: code display.
max7219: no decode display.
max7219: intensity test.
max7219: intensity 31/32.
max7219: intensity 21/32.
max7219: intensity 11/32.
max7219: intensity 1/32.
max7219: scan limit test.
max7219: scan limit 0-7.
max7219: scan limit 0-6.
max7219: scan limit 0-5.
max7219: scan limit 0-4.
max7219: scan limit 0-3.
max7219: scan limit 0-2.
max7219: scan limit 0-1.
max7219: scan limit 0-0.
max7219: finish display test.
```

```shell
max7219 -t matrix_cascade

max7219: chip is Maxim Integrated MAX7219.
max7219: manufacturer is Maxim Integrated.
max7219: interface is SPI.
max7219: driver version is 2.0.
max7219: min supply voltage is 4.0V.
max7219: max supply voltage is 5.5V.
max7219: max current is 320.00mA.
max7219: max temperature is 85.0C.
max7219: min temperature is -40.0C.
max7219: start matrix cascade test.
max7219: set rows display.
max7219: set column display.
max7219: set cross.
max7219: set mixed pattern display.
max7219: power off all.
max7219: finish matrix cascade test.
```

```shell
max7219 -c basic -init

max7219: init successful.
```

```shell
max7219 -c basic -deinit

max7219: deinit successful.
```

```shell
max7219 -c basic -num 12345678

max7219: set display 12345678.
```

```shell
max7219 -c basic -matrix +

max7219: set pattern +.
```

```shell
max7219 -c cascade -init

max7219: init successful.
```

```shell
max7219 -c cascade -deinit

max7219: deinit successful.
```

```shell
max7219 -c cascade -matrix +

max7219: set pattern +.
```

```shell
max7219 -h

max7219 -i
	show max7219 chip and driver information.
max7219 -h
	show max7219 help.
max7219 -p
	show max7219 pin connections of the current board.
max7219 -t display
	run max7219 display test.
max7219 -t matrix_cascade
	run max7219 matrix cascade test.
max7219 -c basic -init
	run max7219 basic init function.
max7219 -c basic -deinit
	run max7219 basic deinit function.
max7219 -c basic -num <number>
	run max7219 basic number display function.number length must be 8.each number can be "0"-"9".
max7219 -c basic -matirx <pattern>
	run max7219 basic matirx display function.matirx can be "-", "|" or "+".
max7219 -c cascade -init
	run max7219 cascade init function.
max7219 -c cascade -deinit
	run max7219 cascade deinit function.
max7219 -c cascade -matirx <pattern>
	run max7219 cascade matirx display function.matirx can be "-", "|" or "+".
```

