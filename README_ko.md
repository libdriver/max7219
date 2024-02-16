[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX7219

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max7219/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX7219/MAX7221은 마이크로프로세서(μP)를 최대 8자리의 7세그먼트 숫자 LED 디스플레이, 막대 그래프 디스플레이 또는 64개의 개별 LED에 인터페이스하는 소형 직렬 입/출력 공통 음극 디스플레이 드라이버입니다. 포함된 온칩에는 BCD 코드 B 디코더, 다중 스캔 회로, 세그먼트 및 디지트 드라이버, 각 디지트를 저장하는 8x8 정적 RAM이 있습니다. 모든 LED에 대한 세그먼트 전류를 설정하려면 하나의 외부 저항만 필요합니다. MAX7221은 SPI™, QSPI™ 및 MICROWIRE™와 호환되며 EMI를 줄이기 위해 슬루레이트가 제한된 세그먼트 드라이버가 있습니다. 편리한 4-와이어 직렬 인터페이스는 모든 공통 μP에 연결됩니다. 개별 숫자는 전체 디스플레이를 다시 쓰지 않고도 주소를 지정하고 업데이트할 수 있습니다. MAX7219/MAX7221은 또한 사용자가 각 디지트에 대해 코드 B 디코딩 또는 무디코딩을 선택할 수 있도록 합니다. 이 장치에는 150μA 저전력 셧다운 모드, 아날로그 및 디지털 밝기 제어, 사용자가 1~8자리를 표시할 수 있는 스캔 제한 레지스터, 모든 LED를 강제로 켜는 테스트 모드가 포함됩니다.

LibDriver MAX7219는 LibDriver에서 출시한 MAX7219의 전체 기능 드라이버입니다. 디지털 튜브 디스플레이, 도트 매트릭스 디스플레이, 캐스케이드 디스플레이 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example cascade](#example-cascade)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver MAX7219의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver MAX7219용 플랫폼 독립적인 SPI버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver MAX7219드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver MAX7219프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver MAX7219오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 MAX7219데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인SPI버스 템플릿을 참조하여 지정된 플랫폼에 대한 SPI버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/max7219/index.html](https://www.libdriver.com/docs/max7219/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.