[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX7219

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max7219/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The MAX7219/MAX7221 are compact, serial input/output common-cathode display drivers that interface microprocessors (μPs) to 7-segment numeric LED displays of up to 8 digits, bar-graph displays, or 64 individual LEDs. Included on-chip are a BCD code-B decoder, multiplex scan circuitry, segment and digit drivers, and an 8x8 static RAM that stores each digit. Only one external resistor is required to set the segment current for all LEDs. The MAX7221 is compatible with SPI™, QSPI™, and MICROWIRE™, and has slewrate-limited segment drivers to reduce EMI. A convenient 4-wire serial interface connects to all common μPs. Individual digits may be addressed and updated without rewriting the entire display. The MAX7219/MAX7221 also allow the user to select code-B decoding or no-decode for each digit. The devices include a 150μA low-power shutdown mode, analog and digital brightness control, a scanlimit register that allows the user to display from 1 to 8 digits, and a test mode that forces all LEDs on.

LibDriver MAX7219 is the full function driver of MAX7219 launched by LibDriver.It provides digital tube display, dot matrix display, cascade display and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example cascade](#example-cascade)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver MAX7219 source files.

/interface includes LibDriver MAX7219 SPI platform independent template.

/test includes LibDriver MAX7219 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver MAX7219 sample code.

/doc includes LibDriver MAX7219 offline document.

/datasheet includes MAX7219 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface SPI platform independent template and finish your platform SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_max7219_basic.h"

uint8_t i;
uint8_t res;
const max7219_no_decode_font_t display[] = {MAX7219_NO_DECODE_FONT_0, MAX7219_NO_DECODE_FONT_1,
                                            MAX7219_NO_DECODE_FONT_2, MAX7219_NO_DECODE_FONT_3,
                                            MAX7219_NO_DECODE_FONT_4, MAX7219_NO_DECODE_FONT_5,
                                            MAX7219_NO_DECODE_FONT_6, MAX7219_NO_DECODE_FONT_7,
                                            MAX7219_NO_DECODE_FONT_8, MAX7219_NO_DECODE_FONT_9 };

res = max7219_basic_init();
if (res != 0)
{
    max7219_interface_debug_print("max7219: basic init failed.\n");

    return 1;
};

...                                            
                                            
for (i = 0; i < 8; i++)
{
    uint8_t s;

    s = 1;
    res = max7219_basic_set_display((max7219_digital_t)(i + 1), display[s]);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");

        return 1;
    }
    
    ...
    
}
                                            
...                                            
                                            
(void)max7219_basic_deinit();

return 0
```

#### example cascade

```C
#include "driver_max7219_cascade.h"

uint8_t res;
uint16_t i, j;

res = max7219_cascade_init();
if (res != 0)
{
    max7219_interface_debug_print("max7219: cascade init failed.\n");

    return 1;
}

...
    
for (j = 0; j < 8; j++)
{
    for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
    {
        if ((j % 2) != 0)
        {
            g_matrix[i][j] = 0xFF;
        }
        else
        {
            g_matrix[i][j] = 0x00;
        }
    }
}
res = max7219_cascade_update();
if (res != 0)
{
    max7219_interface_debug_print("max7219: cascade update failed.\n");

    return 1;
}

...

(void)max7219_cascade_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/max7219/index.html](https://www.libdriver.com/docs/max7219/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.