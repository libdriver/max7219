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
 * @file      driver_max7219_cascade.c
 * @brief     driver max7219 cascade source file
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

#include "driver_max7219_cascade.h"

static max7219_handle_t gs_handle;                                 /**< max7219 handle */
static max7219_cascade_t gs_cascade[MATRIX_CASCADE_LENGTH];        /**< global cascade structure */
uint8_t g_matrix[MATRIX_CASCADE_LENGTH][8];                        /**< global matrix */

/**
 * @brief  cascade example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t max7219_cascade_init(void)
{
    uint8_t res; 
    uint32_t i;
    
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
    for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_DECODE;
        gs_cascade[i].data = MAX7219_CASCADE_DEFAULT_DECODE;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_LENGTH);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set cascade failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* max7219 set default mode */
    for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_SHUT_DOWN;
        gs_cascade[i].data = MAX7219_CASCADE_DEFAULT_MODE;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_LENGTH);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set cascade failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* max7219 set default display test */
    for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_DISPLAY_TEST;
        gs_cascade[i].data = MAX7219_CASCADE_DEFAULT_TEST_MODE;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_LENGTH);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set cascade failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* max7219 set default intensity */
    for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_INTENSITY;
        gs_cascade[i].data = MAX7219_CASCADE_DEFAULT_INTENSITY;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_LENGTH);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set cascade failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* max7219 set default scan limit */
    for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_SCAN_LIMIT;
        gs_cascade[i].data = MAX7219_CASCADE_DEFAULT_SCAN_LIMIT;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_LENGTH);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set cascade failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  cascade example update
 * @return status code
 *         - 0 success
 *         - 1 update failed
 * @note   none
 */
uint8_t max7219_cascade_update(void)
{
    uint8_t res;
    uint32_t i, j;
    
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
        {
            gs_cascade[i].command = (max7219_cascade_command_t)(j + 1);
            gs_cascade[i].data = g_matrix[i][j];
        }
        
        /* set cascade */
        res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_LENGTH);
        if (res != 0)
        {
            return 1;
        }
    }
    
    return 0;
}

/**
 * @brief  cascade example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t max7219_cascade_deinit(void)
{
    uint8_t res; 
    uint32_t i;
    
    /* max7219 set default mode */
    for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_SHUT_DOWN;
        gs_cascade[i].data = MAX7219_MODE_SHUT_DOWN;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_LENGTH);
    if (res != 0)
    {
        return 1;
    }
    res = max7219_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

