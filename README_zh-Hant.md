[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX7219

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max7219/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX7219/MAX7221為緊湊的串行輸入/輸出共陰極顯示驅動器，用於連接微處理器(µP)與8位7段LED數碼管顯示器、條形圖顯示器或64個獨立的LED。器件內置BCD B碼譯碼器、多路復用掃描電路、段和位驅動器以及存儲每位數字的8x8靜態RAM。只需一個外部電阻即可設置所有LED的段電流。 MAX7221兼容於SPI™、QSPI™以及MICROWIRE™接口，段驅動器帶有擺率限制，以降低EMI。便利的4線串行接口可以連接所有通用µP。可對每位數字單獨尋址和更新，無需重新寫入整個顯示器。 MAX7219/MAX7221還允許用戶為每位數字選擇B碼譯碼或非譯碼方式。器件具有150µA低功耗關斷模式、模擬和數字亮度控制、允許用戶顯示1至8位數字的掃描限制寄存器以及強制點亮所有LED的測試模式。

LibDriver MAX7219是LibDriver推出的MAX7219的全功能驅動，該驅動提供數碼管顯示，點陣顯示，級聯顯示等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example cascade](#example-cascade)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver MAX7219的源文件。

/interface目錄包含了LibDriver MAX7219與平台無關的SPI總線模板。

/test目錄包含了LibDriver MAX7219驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver MAX7219編程範例。

/doc目錄包含了LibDriver MAX7219離線文檔。

/datasheet目錄包含了MAX7219數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的SPI總線模板，完成指定平台的SPI總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/max7219/index.html](https://www.libdriver.com/docs/max7219/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。