### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

SPI Pin: SCK/MISO/MOSI/CS  PA5/PA6/PA7/PA4.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. MAX7219

#### 3.1 Command Instruction

1. Show max7219 chip and driver information.

   ```shell
   max7219 (-i | --information)
   ```

2. Show max7219 help.

   ```shell
   max7219 (-h | --help)
   ```

3. Show max7219 pin connections of the current board.

   ```shell
   max7219 (-p | --port)
   ```

4. Run max7219 display test.

   ```shell
   max7219 (-t display | --test=display)
   ```

5. Run max7219 matrix cascade test.

   ```shell
   max7219 (-t cascade | --test=cascade)
   ```

6. Run max7219 basic init function.

   ```shell
   max7219 (-e basic-init | --example=basic-init)
   ```

7. Run max7219 basic deinit function.

   ```shell
   max7219 (-e basic-deinit | --example=basic-deinit)
   ```

8. Run max7219 basic number display function, num is the set number, it can be "0" - "9" and it's length must be 8.

   ```shell
   max7219 (-e basic-num | --example=basic-num) --number=<num>
   ```

9. Run max7219 basic matrix display function.

   ```shell
   max7219 (-e basic-matirx | --example=basic-matirx) --matirx=<- | | | +>
   ```

10. Run max7219 cascade init function.

    ```shell
    max7219 (-e cascade-init | --example=cascade-init)
    ```

11. Run max7219 cascade deinit function.

    ```shell
    max7219 (-e cascade-deinit | --example=cascade-deinit)
    ```

12. Run max7219 cascade matirx display function.

    ```shell
    max7219 (-e cascade-matirx | --example=cascade-matirx) --matirx=<- | | | +>
    ```

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
max7219 -t cascade

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
max7219 -e basic-init

max7219: init successful.
```

```shell
max7219 -e basic-deinit

max7219: deinit successful.
```

```shell
max7219 -e basic-num --number=12345678

max7219: set display 12345678.
```

```shell
max7219 -e basic-matirx --matirx=+

max7219: set pattern +.
```

```shell
max7219 -e cascade-init

max7219: init successful.
```

```shell
max7219 -e cascade-deinit

max7219: deinit successful.
```

```shell
max7219 -e cascade-matirx --matirx=+

max7219: set pattern +.
```

```shell
max7219 -h

Usage:
  max7219 (-i | --information)
  max7219 (-h | --help)
  max7219 (-p | --port)
  max7219 (-t display | --test=display)
  max7219 (-t cascade | --test=cascade)
  max7219 (-e basic-init | --example=basic-init)
  max7219 (-e basic-deinit | --example=basic-deinit)
  max7219 (-e basic-num | --example=basic-num) --number=<num>
  max7219 (-e basic-matirx | --example=basic-matirx) --matirx=<- | | | +>
  max7219 (-e cascade-init | --example=cascade-init)
  max7219 (-e cascade-deinit | --example=cascade-deinit)
  max7219 (-e cascade-matirx | --example=cascade-matirx) --matirx=<- | | | +>

Options:
  -e <basic-init | basic-deinit | basic-num | basic-matirx | cascade-init | cascade-deinit
     | cascade-matirx>, --example=<basic-init | basic-deinit | basic-num | basic-matirx
     | cascade-init | cascade-deinit | cascade-matirx>
                                    Run the driver example.
  -h, --help                        Show the help.
  -i, --information                 Show the chip information.
      --matirx=<- | | | +>          Set the matrix pattern.
      --number=<num>                Set the display number, number length must be 8
                                    and each number can be "0" - "9"
  -p, --port                        Display the pin connections of the current board.
  -t <display | cascade>, --test=<display | cascade>
                                    Run the driver test.
```

