[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX7219
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max7219/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Die MAX7219/MAX7221 sind kompakte, serielle Ein-/Ausgangs-Anzeigetreiber mit gemeinsamer Kathode, die Mikroprozessoren (μPs) mit numerischen 7-Segment-LED-Anzeigen mit bis zu 8 Stellen, Balkendiagrammanzeigen oder 64 einzelnen LEDs verbinden. Auf dem Chip enthalten sind ein BCD-Code-B-Decoder, eine Multiplex-Scan-Schaltung, Segment- und Zifferntreiber und ein statisches 8x8-RAM, das jede Ziffer speichert. Es wird nur ein externer Widerstand benötigt, um den Segmentstrom für alle LEDs einzustellen. Der MAX7221 ist mit SPI™, QSPI™ und MICROWIRE™ kompatibel und verfügt über slewrate-begrenzte Segmenttreiber zur Reduzierung von EMI. Eine bequeme serielle 4-Draht-Schnittstelle verbindet sich mit allen gängigen μPs. Einzelne Ziffern können adressiert und aktualisiert werden, ohne die gesamte Anzeige neu zu schreiben. Beim MAX7219/MAX7221 kann der Benutzer außerdem für jede Ziffer Code-B-Decodierung oder No-Decodierung auswählen. Die Geräte verfügen über einen 150 μA stromsparenden Abschaltmodus, eine analoge und digitale Helligkeitssteuerung, ein Scanlimit-Register, das dem Benutzer die Anzeige von 1 bis 8 Ziffern ermöglicht, und einen Testmodus, der alle LEDs zwangsweise einschaltet.

LibDriver MAX7219 ist der Vollfunktionstreiber von MAX7219, der von LibDriver eingeführt wurde. Er bietet digitale Röhrenanzeige, Punktmatrixanzeige, Kaskadenanzeige und andere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example cascade](#example-cascade)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver MAX7219-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver MAX7219 SPI.

/test enthält den Testcode des LibDriver MAX7219-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver MAX7219-Beispielcode.

/doc enthält das LibDriver MAX7219-Offlinedokument.

/Datenblatt enthält MAX7219-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/max7219/index.html](https://www.libdriver.com/docs/max7219/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.