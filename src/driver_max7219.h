/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_max7219.h
 * @brief     driver max7219 header file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-22
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/22  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/12/05  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_MAX7219_H
#define DRIVER_MAX7219_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup max7219_driver max7219 driver function
 * @brief    max7219 driver modules
 * @{
 */

/**
 * @addtogroup max7219_cascade_driver
 * @{
 */

/**
 * @brief max7219 max cascade size definition
 */
#ifndef MAX7219_MAX_CASCADE_SIZE
    #define MAX7219_MAX_CASCADE_SIZE 128        /**< 128 cascade */
#endif

/**
 * @}
 */

/**
 * @addtogroup max7219_base_driver
 * @{
 */

/**
 * @brief max7219 segment enumeration definition
 */
typedef enum
{
    MAX7219_SEGMENT_A  = (1 << 6),        /**< segment A */
    MAX7219_SEGMENT_B  = (1 << 5),        /**< segment B */
    MAX7219_SEGMENT_C  = (1 << 4),        /**< segment C */
    MAX7219_SEGMENT_D  = (1 << 3),        /**< segment D */
    MAX7219_SEGMENT_E  = (1 << 2),        /**< segment E */
    MAX7219_SEGMENT_F  = (1 << 1),        /**< segment F */
    MAX7219_SEGMENT_G  = (1 << 0),        /**< segment G */
    MAX7219_SEGMENT_DP = (1 << 7),        /**< segment DP */
} max7219_segment_t;

/**
 * @brief max7219 code b font enumeration definition
 */
typedef enum
{
    MAX7219_CODEB_FONT_0     = 0x00,        /**< code b font 0 */
    MAX7219_CODEB_FONT_1     = 0x01,        /**< code b font 1 */
    MAX7219_CODEB_FONT_2     = 0x02,        /**< code b font 2 */
    MAX7219_CODEB_FONT_3     = 0x03,        /**< code b font 3 */
    MAX7219_CODEB_FONT_4     = 0x04,        /**< code b font 4 */
    MAX7219_CODEB_FONT_5     = 0x05,        /**< code b font 5 */
    MAX7219_CODEB_FONT_6     = 0x06,        /**< code b font 6 */
    MAX7219_CODEB_FONT_7     = 0x07,        /**< code b font 7 */
    MAX7219_CODEB_FONT_8     = 0x08,        /**< code b font 8 */
    MAX7219_CODEB_FONT_9     = 0x09,        /**< code b font 9 */
    MAX7219_CODEB_FONT_LINE  = 0x0A,        /**< code b font line */
    MAX7219_CODEB_FONT_E     = 0x0B,        /**< code b font e */
    MAX7219_CODEB_FONT_H     = 0x0C,        /**< code b font h */
    MAX7219_CODEB_FONT_L     = 0x0D,        /**< code b font l */
    MAX7219_CODEB_FONT_P     = 0x0E,        /**< code b font p */
    MAX7219_CODEB_FONT_BLACK = 0x0F,        /**< code b font black */
} max7219_codeb_font_t;

/**
 * @brief max7219 no decode font enumeration definition
 */
typedef enum
{
    MAX7219_NO_DECODE_FONT_0     = 0x7E,        /**< no decode font 0 */
    MAX7219_NO_DECODE_FONT_1     = 0x30,        /**< no decode font 1 */
    MAX7219_NO_DECODE_FONT_2     = 0x6D,        /**< no decode font 2 */
    MAX7219_NO_DECODE_FONT_3     = 0x79,        /**< no decode font 3 */
    MAX7219_NO_DECODE_FONT_4     = 0x33,        /**< no decode font 4 */
    MAX7219_NO_DECODE_FONT_5     = 0x5B,        /**< no decode font 5 */
    MAX7219_NO_DECODE_FONT_6     = 0x5F,        /**< no decode font 6 */
    MAX7219_NO_DECODE_FONT_7     = 0x70,        /**< no decode font 7 */
    MAX7219_NO_DECODE_FONT_8     = 0x7F,        /**< no decode font 8 */
    MAX7219_NO_DECODE_FONT_9     = 0x7B,        /**< no decode font 9 */
    MAX7219_NO_DECODE_FONT_LINE  = 0x01,        /**< no decode font line */ 
    MAX7219_NO_DECODE_FONT_E     = 0x4F,        /**< no decode font e */
    MAX7219_NO_DECODE_FONT_H     = 0x37,        /**< no decode font h */
    MAX7219_NO_DECODE_FONT_L     = 0x0E,        /**< no decode font l */
    MAX7219_NO_DECODE_FONT_P     = 0x67,        /**< no decode font p */
    MAX7219_NO_DECODE_FONT_BLACK = 0x00,        /**< no decode font black */
} max7219_no_decode_font_t;

/**
 * @brief max7219 scan limit enumeration definition
 */
typedef enum
{
    MAX7219_SCAN_LIMIT_DIGIT_0_0 = 0x00,        /**< scan limit digit 0 - 0 */
    MAX7219_SCAN_LIMIT_DIGIT_0_1 = 0x01,        /**< scan limit digit 0 - 1 */
    MAX7219_SCAN_LIMIT_DIGIT_0_2 = 0x02,        /**< scan limit digit 0 - 2 */
    MAX7219_SCAN_LIMIT_DIGIT_0_3 = 0x03,        /**< scan limit digit 0 - 3 */
    MAX7219_SCAN_LIMIT_DIGIT_0_4 = 0x04,        /**< scan limit digit 0 - 4 */
    MAX7219_SCAN_LIMIT_DIGIT_0_5 = 0x05,        /**< scan limit digit 0 - 5 */
    MAX7219_SCAN_LIMIT_DIGIT_0_6 = 0x06,        /**< scan limit digit 0 - 6 */
    MAX7219_SCAN_LIMIT_DIGIT_0_7 = 0x07,        /**< scan limit digit 0 - 7 */
} max7219_scan_limit_t;

/**
 * @brief max7219 intensity enumeration definition
 */
typedef enum
{
    MAX7219_INTENSITY_1_32  = 0x00,        /**< intensity 1 / 32 */
    MAX7219_INTENSITY_3_32  = 0x01,        /**< intensity 3 / 32 */
    MAX7219_INTENSITY_5_32  = 0x02,        /**< intensity 5 / 32 */
    MAX7219_INTENSITY_7_32  = 0x03,        /**< intensity 7 / 32 */
    MAX7219_INTENSITY_9_32  = 0x04,        /**< intensity 9 / 32 */
    MAX7219_INTENSITY_11_32 = 0x05,        /**< intensity 11 / 32 */
    MAX7219_INTENSITY_13_32 = 0x06,        /**< intensity 13 / 32 */
    MAX7219_INTENSITY_15_32 = 0x07,        /**< intensity 15 / 32 */
    MAX7219_INTENSITY_17_32 = 0x08,        /**< intensity 17 / 32 */
    MAX7219_INTENSITY_19_32 = 0x09,        /**< intensity 19 / 32 */
    MAX7219_INTENSITY_21_32 = 0x0A,        /**< intensity 21 / 32 */
    MAX7219_INTENSITY_23_32 = 0x0B,        /**< intensity 23 / 32 */
    MAX7219_INTENSITY_25_32 = 0x0C,        /**< intensity 25 / 32 */
    MAX7219_INTENSITY_27_32 = 0x0D,        /**< intensity 27 / 32 */
    MAX7219_INTENSITY_29_32 = 0x0E,        /**< intensity 29 / 32 */
    MAX7219_INTENSITY_31_32 = 0x0F,        /**< intensity 31 / 32 */
} max7219_intensity_t;

/**
 * @brief max7219 mode enumeration definition
 */
typedef enum
{
    MAX7219_MODE_SHUT_DOWN = 0x00,        /**< shut down mode */
    MAX7219_MODE_NORMAL    = 0x01,        /**< normal mode */
} max7219_mode_t;

/**
 * @brief max7219 display test mode enumeration definition
 */
typedef enum
{
    MAX7219_DISPLAY_TEST_MODE_OFF = 0x00,        /**< test mode off */
    MAX7219_DISPLAY_TEST_MODE_ON  = 0x01,        /**< test mode on */
} max7219_display_test_mode_t;

/**
 * @brief max7219 decode enumeration definition
 */
typedef enum
{
    MAX7219_DECODE_CODEB_DIGITS_NONE = 0x00,        /**< decode code b digits none */
    MAX7219_DECODE_CODEB_DIGITS_0    = 0x01,        /**< decode code b digits 0 */
    MAX7219_DECODE_CODEB_DIGITS_3_0  = 0x0F,        /**< decode code b digits 3 - 0 */
    MAX7219_DECODE_CODEB_DIGITS_7_0  = 0xFF,        /**< decode code b digits 7 - 0 */
} max7219_decode_t;

/**
 * @brief max7219 digital enumeration definition
 */
typedef enum
{
    MAX7219_DIGITAL_0 = 0x01,        /**< digital 0 */
    MAX7219_DIGITAL_1 = 0x02,        /**< digital 1 */
    MAX7219_DIGITAL_2 = 0x03,        /**< digital 2 */
    MAX7219_DIGITAL_3 = 0x04,        /**< digital 3 */
    MAX7219_DIGITAL_4 = 0x05,        /**< digital 4 */
    MAX7219_DIGITAL_5 = 0x06,        /**< digital 5 */
    MAX7219_DIGITAL_6 = 0x07,        /**< digital 6 */
    MAX7219_DIGITAL_7 = 0x08,        /**< digital 7 */
} max7219_digital_t;

/**
 * @}
 */

/**
 * @addtogroup max7219_cascade_driver
 * @{
 */

/**
 * @brief max7219 cascade command enumeration definition
 */
typedef enum
{
    MAX7219_CASCADE_COMMAND_CASCADE      = 0x00,        /**< cascade command */
    MAX7219_CASCADE_COMMAND_DIGIT_0      = 0x01,        /**< digit 0 command */
    MAX7219_CASCADE_COMMAND_DIGIT_1      = 0x02,        /**< digit 1 command */
    MAX7219_CASCADE_COMMAND_DIGIT_2      = 0x03,        /**< digit 2 command */
    MAX7219_CASCADE_COMMAND_DIGIT_3      = 0x04,        /**< digit 3 command */
    MAX7219_CASCADE_COMMAND_DIGIT_4      = 0x05,        /**< digit 4 command */
    MAX7219_CASCADE_COMMAND_DIGIT_5      = 0x06,        /**< digit 5 command */
    MAX7219_CASCADE_COMMAND_DIGIT_6      = 0x07,        /**< digit 6 command */
    MAX7219_CASCADE_COMMAND_DIGIT_7      = 0x08,        /**< digit 7 command */
    MAX7219_CASCADE_COMMAND_DECODE       = 0x09,        /**< decode command */
    MAX7219_CASCADE_COMMAND_INTENSITY    = 0x0A,        /**< intensity command */
    MAX7219_CASCADE_COMMAND_SCAN_LIMIT   = 0x0B,        /**< scan limit command */
    MAX7219_CASCADE_COMMAND_SHUT_DOWN    = 0x0C,        /**< shut down command */
    MAX7219_CASCADE_COMMAND_DISPLAY_TEST = 0x0F,        /**< display test command */
} max7219_cascade_command_t;

/**
 * @brief max7219 cascade structure definition
 */
typedef struct max7219_cascade_s
{
    max7219_cascade_command_t command;        /**< cascade command */
    uint8_t data;                             /**< cascade data */
} max7219_cascade_t;

/**
 * @}
 */

/**
 * @addtogroup max7219_base_driver
 * @{
 */

/**
 * @brief max7219 handle structure definition
 */
typedef struct max7219_handle_s
{
    uint8_t (*spi_init)(void);                                            /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                          /**< point to a spi_deinit function address */
    uint8_t (*spi_write_cmd)(uint8_t *buf, uint16_t len);                 /**< point to a spi_write_cmd function address */
    uint8_t (*spi_write)(uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to a spi_write function address */
    void (*delay_ms)(uint32_t us);                                        /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                      /**< point to a debug_print function address */
    uint8_t buf[MAX7219_MAX_CASCADE_SIZE * 2];                            /**< cascade buffer */
    uint8_t inited;                                                       /**< inited flag */
} max7219_handle_t;

/**
 * @brief max7219 info structure definition
 */
typedef struct max7219_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} max7219_info_t;

/**
 * @}
 */

/**
 * @defgroup max7219_link_driver max7219 link driver function
 * @brief    max7219 link driver modules
 * @ingroup  max7219_driver
 * @{
 */

/**
 * @brief     initialize max7219_handle_t structure
 * @param[in] HANDLE pointer to a max7219 handle structure
 * @param[in] STRUCTURE max7219_handle_t
 * @note      none
 */
#define DRIVER_MAX7219_LINK_INIT(HANDLE, STRUCTURE)          memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE pointer to a max7219 handle structure
 * @param[in] FUC pointer to a spi_init function address
 * @note      none
 */
#define DRIVER_MAX7219_LINK_SPI_INIT(HANDLE, FUC)            (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE pointer to a max7219 handle structure
 * @param[in] FUC pointer to a spi_deinit function address
 * @note      none
 */
#define DRIVER_MAX7219_LINK_SPI_DEINIT(HANDLE, FUC)          (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_write function
 * @param[in] HANDLE pointer to a max7219 handle structure
 * @param[in] FUC pointer to a spi_write function address
 * @note      none
 */
#define DRIVER_MAX7219_LINK_SPI_WRITE(HANDLE, FUC)           (HANDLE)->spi_write = FUC

/**
 * @brief     link spi_write_cmd function
 * @param[in] HANDLE pointer to a max7219 handle structure
 * @param[in] FUC pointer to a spi_write_cmd function address
 * @note      none
 */
#define DRIVER_MAX7219_LINK_SPI_WRITE_COMMAND(HANDLE, FUC)   (HANDLE)->spi_write_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a max7219 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_MAX7219_LINK_DELAY_MS(HANDLE, FUC)            (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a max7219 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_MAX7219_LINK_DEBUG_PRINT(HANDLE, FUC)         (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup max7219_base_driver max7219 base driver function
 * @brief    max7219 base driver modules
 * @ingroup  max7219_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a max7219 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t max7219_info(max7219_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a max7219 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t max7219_init(max7219_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a max7219 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t max7219_deinit(max7219_handle_t *handle);

/**
 * @brief     set the display content
 * @param[in] *handle pointer to a max7219 handle structure
 * @param[in] digital set part
 * @param[in] data set data
 * @return    status code
 *            - 0 success
 *            - 1 set display failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max7219_set_display(max7219_handle_t *handle, max7219_digital_t digital, uint8_t data);

/**
 * @brief     set the content matrix
 * @param[in] *handle pointer to a max7219 handle structure
 * @param[in] *matrix pointer to a content matrix
 * @return    status code
 *            - 0 success
 *            - 1 set matrix failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max7219_set_matrix(max7219_handle_t *handle, uint8_t matrix[8]);

/**
 * @brief     set the decode mode
 * @param[in] *handle pointer to a max7219 handle structure
 * @param[in] decode decode mode
 * @return    status code
 *            - 0 success
 *            - 1 set decode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max7219_set_decode(max7219_handle_t *handle, max7219_decode_t decode);

/**
 * @brief     set the chip mode
 * @param[in] *handle pointer to a max7219 handle structure
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max7219_set_mode(max7219_handle_t *handle, max7219_mode_t mode);

/**
 * @brief     set the chip mode
 * @param[in] *handle pointer to a max7219 handle structure
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max7219_set_mode(max7219_handle_t *handle, max7219_mode_t mode);

/**
 * @brief     set the display test mode
 * @param[in] *handle pointer to a max7219 handle structure
 * @param[in] mode display test mode
 * @return    status code
 *            - 0 success
 *            - 1 set display test mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max7219_set_display_test_mode(max7219_handle_t *handle, max7219_display_test_mode_t mode);

/**
 * @brief     set the display intensity
 * @param[in] *handle pointer to a max7219 handle structure
 * @param[in] intensity display intensity
 * @return    status code
 *            - 0 success
 *            - 1 set intensity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max7219_set_intensity(max7219_handle_t *handle, max7219_intensity_t intensity);

/**
 * @brief     set the scan limit
 * @param[in] *handle pointer to a max7219 handle structure
 * @param[in] limit scan limit
 * @return    status code
 *            - 0 success
 *            - 1 set scan limit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max7219_set_scan_limit(max7219_handle_t *handle, max7219_scan_limit_t limit);

/**
 * @}
 */

/**
 * @defgroup max7219_cascade_driver max7219 cascade driver function
 * @brief    max7219 cascade driver modules
 * @ingroup  max7219_driver
 * @{
 */

/**
 * @brief     set the cascade data
 * @param[in] *handle pointer to a max7219 handle structure
 * @param[in] *cascade pointer to a cascade structure
 * @param[in] len cascade length
 * @return    status code
 *            - 0 success
 *            - 1 set cascade failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max7219_set_cascade(max7219_handle_t *handle, max7219_cascade_t *cascade, uint16_t len);

/**
 * @}
 */

/**
 * @defgroup max7219_extern_driver max7219 extern driver function
 * @brief    max7219 extern driver modules
 * @ingroup  max7219_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a max7219 handle structure
 * @param[in] reg chip register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max7219_set_reg(max7219_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
