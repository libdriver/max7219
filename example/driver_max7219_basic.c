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
 * @file      driver_max7219_basic.c
 * @brief     driver max7219 basic source file
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

#include "driver_max7219_basic.h"

static max7219_handle_t gs_handle;        /**< max7219 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t max7219_basic_init(void)
{
    uint8_t res; 
    
    /* link functions */
    DRIVER_MAX7219_LINK_INIT(&gs_handle, max7219_handle_t);
    DRIVER_MAX7219_LINK_SPI_INIT(&gs_handle, max7219_interface_spi_init);
    DRIVER_MAX7219_LINK_SPI_DEINIT(&gs_handle, max7219_interface_spi_deinit);
    DRIVER_MAX7219_LINK_SPI_WRITE_COMMAND(&gs_handle, max7219_interface_spi_write_cmd);
    DRIVER_MAX7219_LINK_SPI_WRITE(&gs_handle, max7219_interface_spi_write);
    DRIVER_MAX7219_LINK_DELAY_MS(&gs_handle, max7219_interface_delay_ms);
    DRIVER_MAX7219_LINK_DEBUG_PRINT(&gs_handle, max7219_interface_debug_print);
    
    /* max7219 init */
    res = max7219_init(&gs_handle);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: init failed.\n");
        
        return 1;
    }
    
    /* max7219 set default decode */
    res = max7219_set_decode(&gs_handle, MAX7219_BASIC_DEFAULT_DECODE);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set decode failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* max7219 set default mode */
    res = max7219_set_mode(&gs_handle, MAX7219_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set mode failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* max7219 set default display test mode */
    res = max7219_set_display_test_mode(&gs_handle, MAX7219_BASIC_DEFAULT_TEST_MODE);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display test mode failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* max7219 set default intensity */
    res = max7219_set_intensity(&gs_handle, MAX7219_BASIC_DEFAULT_INTENSITY);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set intensity failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* max7219 set default scan limit */
    res = max7219_set_scan_limit(&gs_handle, MAX7219_BASIC_DEFAULT_SCAN_LIMIT);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set scan limit failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set the matrix
 * @param[in] *matrix points to a content matrix
 * @return    status code
 *            - 0 success
 *            - 1 set matrix failed
 * @note      none
 */
uint8_t max7219_basic_set_matrix(uint8_t matrix[8])
{
    /* set matrix */
    if (max7219_set_matrix(&gs_handle, matrix) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     basic example set the display
 * @param[in] digital is the set part
 * @param[in] data is the set data
 * @return    status code
 *            - 0 success
 *            - 1 set display failed
 * @note      none
 */
uint8_t max7219_basic_set_display(max7219_digital_t digital, uint8_t data)
{
    /* set display */
    if (max7219_set_display(&gs_handle, digital, data) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t max7219_basic_deinit(void)
{
    /* close max7219 */
    if (max7219_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
