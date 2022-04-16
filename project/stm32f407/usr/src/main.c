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
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-03-22
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/22  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_max7219_basic.h"
#include "driver_max7219_cascade.h"
#include "driver_max7219_display_test.h"
#include "driver_max7219_matrix_cascade_test.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "shell.h"
#include <math.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */

/**
 * @brief     max7219 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t max7219(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            max7219_info_t info;
            
            /* print max7219 info */
            max7219_info(&info);
            max7219_interface_debug_print("max7219: chip is %s.\n", info.chip_name);
            max7219_interface_debug_print("max7219: manufacturer is %s.\n", info.manufacturer_name);
            max7219_interface_debug_print("max7219: interface is %s.\n", info.interface);
            max7219_interface_debug_print("max7219: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            max7219_interface_debug_print("max7219: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            max7219_interface_debug_print("max7219: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            max7219_interface_debug_print("max7219: max current is %0.2fmA.\n", info.max_current_ma);
            max7219_interface_debug_print("max7219: max temperature is %0.1fC.\n", info.temperature_max);
            max7219_interface_debug_print("max7219: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            max7219_interface_debug_print("max7219: SCK connected to GPIOA PIN5.\n");
            max7219_interface_debug_print("max7219: MOSI connected to GPIOA PIN7.\n");
            max7219_interface_debug_print("max7219: CS connected to GPIOA PIN4.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show max7219 help */
            
            help:
            
            max7219_interface_debug_print("max7219 -i\n\tshow max7219 chip and driver information.\n");
            max7219_interface_debug_print("max7219 -h\n\tshow max7219 help.\n");
            max7219_interface_debug_print("max7219 -p\n\tshow max7219 pin connections of the current board.\n");
            max7219_interface_debug_print("max7219 -t display\n\trun max7219 display test.\n");
            max7219_interface_debug_print("max7219 -t matrix_cascade\n\trun max7219 matrix cascade test.\n");
            max7219_interface_debug_print("max7219 -c basic -init\n\trun max7219 basic init function.\n");
            max7219_interface_debug_print("max7219 -c basic -deinit\n\trun max7219 basic deinit function.\n");
            max7219_interface_debug_print("max7219 -c basic -num <number>\n\trun max7219 basic number display function.number length must be 8."
                                          "each number can be \"0\"-\"9\".\n");
            max7219_interface_debug_print("max7219 -c basic -matirx <pattern>\n\trun max7219 basic matirx display function."
                                          "matirx can be \"-\", \"|\" or \"+\".\n");
            max7219_interface_debug_print("max7219 -c cascade -init\n\trun max7219 cascade init function.\n");
            max7219_interface_debug_print("max7219 -c cascade -deinit\n\trun max7219 cascade deinit function.\n");
            max7219_interface_debug_print("max7219 -c cascade -matirx <pattern>\n\trun max7219 cascade matirx display function."
                                          "matirx can be \"-\", \"|\" or \"+\".\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 3)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* display test */
            if (strcmp("display", argv[2]) == 0)
            {
                uint8_t res;
                
                res = max7219_display_test();
                if (res != 0)
                {
                    max7219_interface_debug_print("max7219: display test failed.\n");
                    
                    return 1;
                }
                
                return 0;
            }
            else if (strcmp("matrix_cascade", argv[2]) == 0)
            {
                uint8_t res;
                
                res = max7219_matrix_cascade_test();
                if (res != 0)
                {
                    max7219_interface_debug_print("max7219: matrix cascade failed.\n");
                    
                    return 1;
                }
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run functions */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic test */
            if (strcmp("basic", argv[2]) == 0)
            {
                uint8_t res;
                
                if (strcmp("-init", argv[3]) == 0)
                {
                    res = max7219_basic_init();
                    if (res != 0)
                    {
                        max7219_interface_debug_print("max7219: basic init failed.\n");
                        
                        return 1;
                    }
                    max7219_interface_debug_print("max7219: init successful.\n");
                    
                    return 0;
                }
                else if (strcmp("-deinit", argv[3]) == 0)
                {
                    res = max7219_basic_deinit();
                    if (res != 0)
                    {
                        max7219_interface_debug_print("max7219: basic deinit failed.\n");
                        
                        return 1;
                    }
                    max7219_interface_debug_print("max7219: deinit successful.\n");
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* cascade test */
            else if (strcmp("cascade", argv[2]) == 0)
            {
                uint8_t res;
                
                if (strcmp("-init", argv[3]) == 0)
                {
                    res = max7219_cascade_init();
                    if (res != 0)
                    {
                        max7219_interface_debug_print("max7219: cascade init failed.\n");
                        
                        return 1;
                    }
                    max7219_interface_debug_print("max7219: init successful.\n");
                    
                    return 0;
                }
                else if (strcmp("-deinit", argv[3]) == 0)
                {
                    res = max7219_cascade_deinit();
                    if (res != 0)
                    {
                        max7219_interface_debug_print("max7219: cascade deinit failed.\n");
                        
                        return 1;
                    }
                    max7219_interface_debug_print("max7219: deinit successful.\n");
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run functions */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic function */
            if (strcmp("basic", argv[2]) == 0)
            {
                if (strcmp("-num", argv[3]) == 0)
                {
                    uint8_t i;
                    uint8_t res;
                    uint32_t len = strlen(argv[4]);
                    const max7219_no_decode_font_t display[] = {MAX7219_NO_DECODE_FONT_0, MAX7219_NO_DECODE_FONT_1,
                                                                MAX7219_NO_DECODE_FONT_2, MAX7219_NO_DECODE_FONT_3,
                                                                MAX7219_NO_DECODE_FONT_4, MAX7219_NO_DECODE_FONT_5,
                                                                MAX7219_NO_DECODE_FONT_6, MAX7219_NO_DECODE_FONT_7,
                                                                MAX7219_NO_DECODE_FONT_8, MAX7219_NO_DECODE_FONT_9
                                                               };
                    
                    for (i = 0; i < 8; i++)
                    {
                        uint8_t s;
                        
                        if (i < len)
                        {
                            s = argv[4][i] - '0';
                            s = (s > 9) ? 9 : s;
                            res = max7219_basic_set_display((max7219_digital_t)(i+1), display[s]);
                            if (res != 0)
                            {
                                max7219_interface_debug_print("max7219: set display failed.\n");
                                
                                return 1;
                            }
                        }
                        else
                        {
                            res = max7219_basic_set_display((max7219_digital_t)(i+1), display[0]);
                            if (res != 0)
                            {
                                max7219_interface_debug_print("max7219: set display failed.\n");
                                
                                return 1;
                            }
                        }
                    }
                    max7219_interface_debug_print("max7219: set display %s.\n", argv[4]);
                
                    return 0;
                }
                else if (strcmp("-matrix", argv[3]) == 0)
                {
                    uint8_t res;
                    uint8_t matrix[8];
                    
                    if (strcmp("+", argv[4]) == 0)
                    {
                        matrix[0] = 0x18;
                        matrix[1] = 0x18;
                        matrix[2] = 0x18;
                        matrix[3] = 0xFF;
                        matrix[4] = 0xFF;
                        matrix[5] = 0x18;
                        matrix[6] = 0x18;
                        matrix[7] = 0x18;
                        max7219_interface_debug_print("max7219: set pattern +.\n");
                    }
                    else if (strcmp("|", argv[4]) == 0)
                    {
                        matrix[0] = 0xAA;
                        matrix[1] = 0xAA;
                        matrix[2] = 0xAA;
                        matrix[3] = 0xAA;
                        matrix[4] = 0xAA;
                        matrix[5] = 0xAA;
                        matrix[6] = 0xAA;
                        matrix[7] = 0xAA;
                        max7219_interface_debug_print("max7219: set pattern |.\n");
                    }
                    else if (strcmp("-", argv[4]) == 0)
                    {
                        matrix[0] = 0x00;
                        matrix[1] = 0xFF;
                        matrix[2] = 0x00;
                        matrix[3] = 0xFF;
                        matrix[4] = 0x00;
                        matrix[5] = 0xFF;
                        matrix[6] = 0x00;
                        matrix[7] = 0xFF;
                        max7219_interface_debug_print("max7219: set pattern -.\n");
                    }
                    else
                    {
                        max7219_interface_debug_print("max7219: param is invalid.\n");
                        
                        return 5;
                    }
                    res = max7219_basic_set_matrix(matrix);
                    if (res != 0)
                    {
                        max7219_interface_debug_print("max7219: set matrix failed.\n");
                        
                        return 1;
                    }
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* cascade function */
            else if (strcmp("cascade", argv[2]) == 0)
            {
                if (strcmp("-matrix", argv[3]) == 0)
                {
                    uint8_t res;
                    uint32_t i, j;
                    
                    if (strcmp("+", argv[4]) == 0)
                    {
                        for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
                        {
                            g_matrix[i][0] = 0x18;
                        }
                        for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
                        {
                            g_matrix[i][1] = 0x18;
                        }
                        for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
                        {
                            g_matrix[i][2] = 0x18;
                        }
                        for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
                        {
                            g_matrix[i][3] = 0xFF;
                        }
                        for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
                        {
                            g_matrix[i][4] = 0xFF;
                        }
                        for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
                        {
                            g_matrix[i][5] = 0x18;
                        }
                        for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
                        {
                            g_matrix[i][6] = 0x18;
                        }
                        for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
                        {
                            g_matrix[i][7] = 0x18;
                        }
                        res = max7219_cascade_update();
                        if (res != 0)
                        {
                            max7219_interface_debug_print("max7219: cascade update failed.\n");
                            
                            return 1;
                        }
                        max7219_interface_debug_print("max7219: set pattern +.\n");
                        
                        return 0;
                    }
                    else if (strcmp("-", argv[4]) == 0)
                    {
                        for (j = 0; j < 8; j++)
                        {
                            for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
                            {
                                if (j % 2)
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
                        max7219_interface_debug_print("max7219: set pattern -.\n");
                        
                        return 0;
                    }
                    else if (strcmp("|", argv[4]) == 0)
                    {
                        for (j = 0; j < 8; j++)
                        {
                            for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
                            {
                                g_matrix[i][j] = 0xAA;
                            }
                        }
                        res = max7219_cascade_update();
                        if (res != 0)
                        {
                            max7219_interface_debug_print("max7219: cascade update failed.\n");
                            
                            return 1;
                        }
                        max7219_interface_debug_print("max7219: set pattern |.\n");
                        
                        return 0;
                    }
                    else
                    {
                        max7219_interface_debug_print("max7219: param is invalid.\n");
                        
                        return 5;
                    }
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register max7219 fuction */
    shell_init();
    shell_register("max7219", max7219);
    uart1_print("max7219: welcome to libdriver max7219.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("max7219: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("max7219: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("max7219: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("max7219: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("max7219: param is invalid.\n");
            }
            else
            {
                uart1_print("max7219: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
