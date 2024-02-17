[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX7219

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max7219/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX7219 / MAX7221は、マイクロプロセッサ（μP）を最大8桁の7セグメント数値LEDディスプレイ、棒グラフディスプレイ、または64個の個別LEDに接続する、コンパクトなシリアル入出力コモンカソードディスプレイドライバです。オンチップには、BCDコードBデコーダー、マルチプレックススキャン回路、セグメントおよびディジットドライバー、および各ディジットを格納する8x8スタティックRAMが含まれています。すべてのLEDのセグメント電流を設定するために必要な外部抵抗は1つだけです。 MAX7221は、SPI™、QSPI™、およびMICROWIRE™と互換性があり、EMIを低減するためのスルーレート制限セグメントドライバーを備えています。便利な4線式シリアルインターフェースがすべての一般的なμPに接続します。個々の数字は、表示全体を書き換えることなくアドレス指定および更新できます。 MAX7219 / MAX7221では、ユーザーは各桁に対してコードBデコードまたはデコードなしを選択することもできます。デバイスには、150μAの低電力シャットダウンモード、アナログおよびデジタル輝度制御、ユーザーが1〜8桁で表示できるスキャン制限レジスタ、およびすべてのLEDを強制的にオンにするテストモードが含まれます。

LibDriver MAX7219は、LibDriverが発売したMAX7219の全機能ドライバーで、デジタルチューブ表示、ドットマトリックス表示、カスケード表示などの機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example cascade](#example-cascade)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver MAX7219のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver MAX7219用のプラットフォームに依存しないSPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver MAX7219ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver MAX7219プログラミング例が含まれています。

/ docディレクトリには、LibDriver MAX7219オフラインドキュメントが含まれています。

/ datasheetディレクトリには、MAX7219データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないSPIバステンプレートを参照して、指定したプラットフォームのSPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

```c
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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/max7219/index.html](https://www.libdriver.com/docs/max7219/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。