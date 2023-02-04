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
 * @file      driver_max7219_matrix_cascade_test.c
 * @brief     driver max7219 matrix cascade test source file
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

#include "driver_max7219_matrix_cascade_test.h"

static max7219_handle_t gs_handle;                                      /**< max7219 handle */
static max7219_cascade_t gs_cascade[MATRIX_CASCADE_TEST_LENGTH];        /**< global cascade structure */
static uint8_t gs_matrix[MATRIX_CASCADE_TEST_LENGTH][8];                /**< global matrix */

/**
 * @brief  matrix cascade test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t max7219_matrix_cascade_test(void)
{
    uint8_t res;
    uint32_t i, j;
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
    
    /* start matrix cascade test */
    max7219_interface_debug_print("max7219: start matrix cascade test.\n");
    
    /* max7219 init */
    res = max7219_init(&gs_handle);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: init failed.\n");
        
        return 1;
    }
    
    /* set no decode */
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_DECODE;
        gs_cascade[i].data = MAX7219_DECODE_CODEB_DIGITS_NONE;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_TEST_LENGTH);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set cascade failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set intensity */
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_INTENSITY;
        gs_cascade[i].data = MAX7219_INTENSITY_31_32;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_TEST_LENGTH);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set cascade failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set scan limit digit 0-7 */
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_SCAN_LIMIT;
        gs_cascade[i].data = MAX7219_SCAN_LIMIT_DIGIT_0_7;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_TEST_LENGTH);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set cascade failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set display test off */
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_DISPLAY_TEST;
        gs_cascade[i].data = MAX7219_DISPLAY_TEST_MODE_OFF;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_TEST_LENGTH);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display test off failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set power on */
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_SHUT_DOWN;
        gs_cascade[i].data = MAX7219_MODE_NORMAL;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_TEST_LENGTH);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display test off failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rows display */
    max7219_interface_debug_print("max7219: set rows display.\n");
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
        {
            if ((j % 2) != 0)
            {
                gs_matrix[i][j] = 0xFF;
            }
            else
            {
                gs_matrix[i][j] = 0x00;
            }
        }
    }
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
        {
            gs_cascade[i].command = (max7219_cascade_command_t)(j + 1);
            gs_cascade[i].data = gs_matrix[i][j];
        }
        res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_TEST_LENGTH);
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: set display test off failed.\n");
            (void)max7219_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);
    
    /* set column display */
    max7219_interface_debug_print("max7219: set column display.\n");
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
        {
            gs_matrix[i][j] = 0xAA;
        }
    }
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
        {
            gs_cascade[i].command = (max7219_cascade_command_t)(j + 1);
            gs_cascade[i].data = gs_matrix[i][j];
        }
        res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_TEST_LENGTH);
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: set display test off failed.\n");
            (void)max7219_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);
    
    /* set cross */
    max7219_interface_debug_print("max7219: set cross.\n");
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_matrix[i][0] = 0x18;
    }
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_matrix[i][1] = 0x18;
    }
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_matrix[i][2] = 0x18;
    }
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_matrix[i][3] = 0xFF;
    }
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_matrix[i][4] = 0xFF;
    }
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_matrix[i][5] = 0x18;
    }
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_matrix[i][6] = 0x18;
    }
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_matrix[i][7] = 0x18;
    }
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
        {
            gs_cascade[i].command = (max7219_cascade_command_t)(j + 1);
            gs_cascade[i].data = gs_matrix[i][j];
        }
        res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_TEST_LENGTH);
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: set display test off failed.\n");
            (void)max7219_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);
    
    /* set mixed pattern display */
    max7219_interface_debug_print("max7219: set mixed pattern display.\n");
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH/2; i++)
        {
            gs_matrix[i][j] = 0xAA;
        }
        for (i = MATRIX_CASCADE_TEST_LENGTH/2; i < MATRIX_CASCADE_TEST_LENGTH; i++)
        {
            if ((j % 2) != 0)
            {
                gs_matrix[i][j] = 0xFF;
            }
            else
            {
                gs_matrix[i][j] = 0x00;
            }
        }
    }
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
        {
            gs_cascade[i].command = (max7219_cascade_command_t)(j + 1);
            gs_cascade[i].data = gs_matrix[i][j];
        }
        res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_TEST_LENGTH);
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: set display test off failed.\n");
            (void)max7219_deinit(&gs_handle);
            
            return 1;
        }
    }
    
    /* delay 3000 ms */
    max7219_interface_delay_ms(3000);
    max7219_interface_debug_print("max7219: power off all.\n");
    
    /* set power off */
    for (i = 0; i < MATRIX_CASCADE_TEST_LENGTH; i++)
    {
        gs_cascade[i].command = MAX7219_CASCADE_COMMAND_SHUT_DOWN;
        gs_cascade[i].data = MAX7219_MODE_SHUT_DOWN;
    }
    res = max7219_set_cascade(&gs_handle, (max7219_cascade_t *)gs_cascade, MATRIX_CASCADE_TEST_LENGTH);
    if (res != 0)
    {
        max7219_interface_debug_print("max7219: set display test off failed.\n");
        (void)max7219_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish matrix cascade test */
    max7219_interface_debug_print("max7219: finish matrix cascade test.\n");
    (void)max7219_deinit(&gs_handle);
    
    return 0;
}
