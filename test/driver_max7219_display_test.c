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
 * @file      driver_max7219_display_test.c
 * @brief     driver max7219 display test source file
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

#include "driver_max7219_display_test.h"

static max7219_handle_t gs_handle;        /**< max7219 handle */

/**
 * @brief  display test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t max7219_display_test(void)
{
    uint8_t res;
    max7219_info_t info;

    /* link functions */
    DRIVER_MAX7219_LINK_INIT(&gs_handle, max7219_handle_t);
    DRIVER_MAX7219_LINK_SPI_INIT(&gs_handle, max7219_interface_spi_init);
    DRIVER_MAX7219_LINK_SPI_DEINIT(&gs_handle, max7219_interface_spi_deinit);
    DRIVER_MAX7219_LINK_SPI_WRITE_COMMAND(&gs_handle, max7219_interface_spi_write_cmd);
    DRIVER_MAX7219_LINK_SPI_WRITE(&gs_handle, max7219_interface_spi_write);
    DRIVER_MAX7219_LINK_DELAY_MS(&gs_handle, max7219_interface_delay_ms);
    DRIVER_MAX7219_LINK_DEBUG_PRINT(&gs_handle, max7219_interface_debug_print);

    /* max7219 info */
    res = max7219_info(&info);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: get info failed.\n");

        return 1;
    }
    else
    {
        /* print chip information */
        max7219_interface_debug_print("max7219: chip is %s.\n", info.chip_name);
        max7219_interface_debug_print("max7219: manufacturer is %s.\n", info.manufacturer_name);
        max7219_interface_debug_print("max7219: interface is %s.\n", info.interface);
        max7219_interface_debug_print("max7219: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        max7219_interface_debug_print("max7219: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        max7219_interface_debug_print("max7219: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        max7219_interface_debug_print("max7219: max current is %0.2fmA.\n", info.max_current_ma);
        max7219_interface_debug_print("max7219: max temperature is %0.1fC.\n", info.temperature_max);
        max7219_interface_debug_print("max7219: min temperature is %0.1fC.\n", info.temperature_min);
    }

    /* start display test */
    max7219_interface_debug_print("max7219: start display test.\n");

    /* max7219 init */
    res = max7219_init(&gs_handle);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: init failed.\n");

        return 1;
    }

    /* max7219 set scan limit */
    res = max7219_set_scan_limit(&gs_handle, MAX7219_SCAN_LIMIT_DIGIT_0_7);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set scan limit failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* max7219 set intensity */
    res = max7219_set_intensity(&gs_handle, MAX7219_INTENSITY_31_32);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set intensity failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* max7219 set display test mode */
    res = max7219_set_display_test_mode(&gs_handle, MAX7219_DISPLAY_TEST_MODE_OFF);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display test mode failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* max7219 set decode */
    res = max7219_set_decode(&gs_handle, MAX7219_DECODE_CODEB_DIGITS_NONE);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set decode failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* max7219 set mode */
    res = max7219_set_mode(&gs_handle, MAX7219_MODE_NORMAL);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set mode failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* display test */
    max7219_interface_debug_print("max7219: display test.\n");

    /* max7219 set display test mode */
    res = max7219_set_display_test_mode(&gs_handle, MAX7219_DISPLAY_TEST_MODE_ON);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display test mode failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* max7219 set display test mode */
    res = max7219_set_display_test_mode(&gs_handle, MAX7219_DISPLAY_TEST_MODE_OFF);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display test mode failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* code display */
    max7219_interface_debug_print("max7219: code display.\n");

    /* max7219 set decode */
    res = max7219_set_decode(&gs_handle, MAX7219_DECODE_CODEB_DIGITS_7_0);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set decode failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_0, MAX7219_CODEB_FONT_0|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_1, MAX7219_CODEB_FONT_1);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_2, MAX7219_CODEB_FONT_2|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_3, MAX7219_CODEB_FONT_3);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_4, MAX7219_CODEB_FONT_4|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_5, MAX7219_CODEB_FONT_5);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_6, MAX7219_CODEB_FONT_6|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_7, MAX7219_CODEB_FONT_7);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_0, MAX7219_CODEB_FONT_8|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_1, MAX7219_CODEB_FONT_9);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_2, MAX7219_CODEB_FONT_LINE|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_3, MAX7219_CODEB_FONT_E);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_4, MAX7219_CODEB_FONT_H|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_5, MAX7219_CODEB_FONT_L);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_6, MAX7219_CODEB_FONT_P|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_7, MAX7219_CODEB_FONT_BLACK);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* no decode display */
    max7219_interface_debug_print("max7219: no decode display.\n");

    /* max7219 set decode */
    res = max7219_set_decode(&gs_handle, MAX7219_DECODE_CODEB_DIGITS_NONE);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set decode failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_0, MAX7219_NO_DECODE_FONT_0);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_1, MAX7219_NO_DECODE_FONT_1|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_2, MAX7219_NO_DECODE_FONT_2);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_3, MAX7219_NO_DECODE_FONT_3|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_4, MAX7219_NO_DECODE_FONT_4);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_5, MAX7219_NO_DECODE_FONT_5|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_6, MAX7219_NO_DECODE_FONT_6);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_7, MAX7219_NO_DECODE_FONT_7|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_0, MAX7219_NO_DECODE_FONT_8);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_1, MAX7219_NO_DECODE_FONT_9|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_2, MAX7219_NO_DECODE_FONT_LINE);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_3, MAX7219_NO_DECODE_FONT_E|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_4, MAX7219_NO_DECODE_FONT_H);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_5, MAX7219_NO_DECODE_FONT_L|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_6, MAX7219_NO_DECODE_FONT_P);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }
    res = max7219_set_display(&gs_handle, MAX7219_DIGITAL_7, MAX7219_NO_DECODE_FONT_BLACK|MAX7219_SEGMENT_DP);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* intensity test */
    max7219_interface_debug_print("max7219: intensity test.\n");

    /* intensity 31/32 */
    max7219_interface_debug_print("max7219: intensity 31/32.\n");

    /* max7219 set intensity */
    res = max7219_set_intensity(&gs_handle, MAX7219_INTENSITY_31_32);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set intensity failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* intensity 21/32 */
    max7219_interface_debug_print("max7219: intensity 21/32.\n");

    /* max7219 set intensity */
    res = max7219_set_intensity(&gs_handle, MAX7219_INTENSITY_21_32);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set intensity failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* intensity 11/32 */
    max7219_interface_debug_print("max7219: intensity 11/32.\n");

    /* max7219 set intensity */
    res = max7219_set_intensity(&gs_handle, MAX7219_INTENSITY_11_32);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set intensity failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* intensity 1/32 */
    max7219_interface_debug_print("max7219: intensity 1/32.\n");

    /* max7219 set intensity */
    res = max7219_set_intensity(&gs_handle, MAX7219_INTENSITY_1_32);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set intensity failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* max7219 set intensity */
    res = max7219_set_intensity(&gs_handle, MAX7219_INTENSITY_31_32);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set intensity failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* scan limit test */
    max7219_interface_debug_print("max7219: scan limit test.\n");

    /* scan limit 0-7 */
    max7219_interface_debug_print("max7219: scan limit 0-7.\n");

    /* max7219 set scan limit */
    res = max7219_set_scan_limit(&gs_handle, MAX7219_SCAN_LIMIT_DIGIT_0_7);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set scan limit failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* scan limit 0-6 */
    max7219_interface_debug_print("max7219: scan limit 0-6.\n");

    /* max7219 set scan limit */
    res = max7219_set_scan_limit(&gs_handle, MAX7219_SCAN_LIMIT_DIGIT_0_6);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set scan limit failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* scan limit 0-5 */
    max7219_interface_debug_print("max7219: scan limit 0-5.\n");

    /* max7219 set scan limit */
    res = max7219_set_scan_limit(&gs_handle, MAX7219_SCAN_LIMIT_DIGIT_0_5);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set scan limit failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* scan limit 0-4 */
    max7219_interface_debug_print("max7219: scan limit 0-4.\n");

    /* max7219 set scan limit */
    res = max7219_set_scan_limit(&gs_handle, MAX7219_SCAN_LIMIT_DIGIT_0_4);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set scan limit failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* scan limit 0-3 */
    max7219_interface_debug_print("max7219: scan limit 0-3.\n");

    /* max7219 set scan limit */
    res = max7219_set_scan_limit(&gs_handle, MAX7219_SCAN_LIMIT_DIGIT_0_3);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set scan limit failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* scan limit 0-2 */
    max7219_interface_debug_print("max7219: scan limit 0-2.\n");

    /* max7219 set scan limit */
    res = max7219_set_scan_limit(&gs_handle, MAX7219_SCAN_LIMIT_DIGIT_0_2);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set scan limit failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* scan limit 0-1 */
    max7219_interface_debug_print("max7219: scan limit 0-1.\n");

    /* max7219 set scan limit */
    res = max7219_set_scan_limit(&gs_handle, MAX7219_SCAN_LIMIT_DIGIT_0_1);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set scan limit failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* scan limit 0-0 */
    max7219_interface_debug_print("max7219: scan limit 0-0.\n");

    /* max7219 set scan limit */
    res = max7219_set_scan_limit(&gs_handle, MAX7219_SCAN_LIMIT_DIGIT_0_0);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set scan limit failed.\n");
        (void)max7219_deinit(&gs_handle);

        return 1;
    }

    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);

    /* finish display test */
    max7219_interface_debug_print("max7219: finish display test.\n");
    (void)max7219_deinit(&gs_handle);

    return 0;
}
