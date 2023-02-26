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
#include <getopt.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief     max7219 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t max7219(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"matrix", required_argument, NULL, 1},
        {"number", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    char num[9] = {0};
    char mat[2] = {0};
    uint8_t num_flag = 0;
    uint8_t mat_flag = 0; 
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* matrix */
            case 1 :
            {
                /* set the matrix */
                if (strcmp("+", optarg) == 0)
                {
                    mat[0] = '+';
                    mat_flag = 1;
                }
                else if (strcmp("|", optarg) == 0)
                {
                    mat[0] = '|';
                    mat_flag = 1;
                }
                else if (strcmp("-", optarg) == 0)
                {
                    mat[0] = '-';
                    mat_flag = 1;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* num */
            case 2 :
            {
                /* set the num */
                if (strlen(optarg) != 8)
                {
                    return 5;
                }
                memset(num, 0, sizeof(char) * 9);
                strcpy(num, optarg);
                num_flag = 1;
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_display", type) == 0)
    {
        uint8_t res;
        
        /* run display test */
        res = max7219_display_test();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: display test failed.\n");
            
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_cascade", type) == 0)
    {
        uint8_t res;
        
        /* run cascade test */
        res = max7219_matrix_cascade_test();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: matrix cascade failed.\n");
            
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_basic-init", type) == 0)
    {
        uint8_t res;
        
        /* basic init */
        res = max7219_basic_init();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: basic init failed.\n");
            
            return 1;
        }
        
        /* output */
        max7219_interface_debug_print("max7219: init successful.\n");
        
        /* spi deinit */
        res = max7219_interface_spi_deinit();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: basic deinit failed.\n");
            
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_basic-deinit", type) == 0)
    {
        uint8_t res;
        
        /* basic init */
        res = max7219_basic_init();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: basic init failed.\n");
            
            return 1;
        }
        
        /* basic deinit */
        res = max7219_basic_deinit();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: basic deinit failed.\n");
            
            return 1;
        }
        
        /* output */
        max7219_interface_debug_print("max7219: deinit successful.\n");
        
        return 0;
    }
    else if (strcmp("e_basic-num", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        uint32_t len = strlen(num);
        const max7219_no_decode_font_t display[] = {MAX7219_NO_DECODE_FONT_0, MAX7219_NO_DECODE_FONT_1,
                                                    MAX7219_NO_DECODE_FONT_2, MAX7219_NO_DECODE_FONT_3,
                                                    MAX7219_NO_DECODE_FONT_4, MAX7219_NO_DECODE_FONT_5,
                                                    MAX7219_NO_DECODE_FONT_6, MAX7219_NO_DECODE_FONT_7,
                                                    MAX7219_NO_DECODE_FONT_8, MAX7219_NO_DECODE_FONT_9
                                                   };
        
        /* check the flag */
        if (num_flag != 1)
        {
            return 5;
        }
        
        /* basic init */
        res = max7219_basic_init();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: basic init failed.\n");
            
            return 1;
        }
        
        /* loop */
        for (i = 0; i < 8; i++)
        {
            uint8_t s;
            
            if (i < len)
            {
                s = num[i] - '0';
                s = (s > 9) ? 9 : s;
                res = max7219_basic_set_display((max7219_digital_t)(i + 1), display[s]);
                if (res != 0)
                {
                    max7219_interface_debug_print("max7219: set display failed.\n");
                    
                    return 1;
                }
            }
            else
            {
                res = max7219_basic_set_display((max7219_digital_t)(i + 1), display[0]);
                if (res != 0)
                {
                    max7219_interface_debug_print("max7219: set display failed.\n");
                    
                    return 1;
                }
            }
        }
        
        /* output */
        max7219_interface_debug_print("max7219: set display %s.\n", num);
        
        /* spi deinit */
        res = max7219_interface_spi_deinit();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: basic deinit failed.\n");
            
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_basic-matrix", type) == 0)
    {
        uint8_t res;
        uint8_t matrix[8];
        
        /* check the flag */
        if (mat_flag != 1)
        {
            return 5;
        }
        
        /* check the matrix */
        if (strncmp("+", mat, 1) == 0)
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
        else if (strncmp("|", mat, 1) == 0)
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
        else if (strncmp("-", mat, 1) == 0)
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
            return 5;
        }
        
        /* basic int */
        res = max7219_basic_init();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: basic init failed.\n");
            
            return 1;
        }
        
        /* set the matrix */
        res = max7219_basic_set_matrix(matrix);
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: set matrix failed.\n");
            
            return 1;
        }
        
        /* spi deinit */
        res = max7219_interface_spi_deinit();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: basic deinit failed.\n");
            
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_cascade-init", type) == 0)
    {
        uint8_t res;
        
        /* cascade init */
        res = max7219_cascade_init();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: cascade init failed.\n");
            
            return 1;
        }
        
        /* output */
        max7219_interface_debug_print("max7219: init successful.\n");
        
        /* spi deinit */
        res = max7219_interface_spi_deinit();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: basic deinit failed.\n");
            
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_cascade-deinit", type) == 0)
    {
        uint8_t res;
        
        /* cascade init */
        res = max7219_cascade_init();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: cascade init failed.\n");
            
            return 1;
        }
        
        /* cascade deinit */
        res = max7219_cascade_deinit();
        if (res != 0)
        {
            max7219_interface_debug_print("max7219: cascade deinit failed.\n");
            
            return 1;
        }
        
        /* output */
        max7219_interface_debug_print("max7219: deinit successful.\n");
        
        return 0;
    }
    else if (strcmp("e_cascade-matrix", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        uint32_t j;
        
        /* check the flag */
        if (mat_flag != 1)
        {
            return 5;
        }
        
        if (strncmp("+", mat, 1) == 0)
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
            
            /* cascade init */
            res = max7219_cascade_init();
            if (res != 0)
            {
                max7219_interface_debug_print("max7219: cascade init failed.\n");
                
                return 1;
            }
            
            /* cascade update */
            res = max7219_cascade_update();
            if (res != 0)
            {
                max7219_interface_debug_print("max7219: cascade update failed.\n");
                
                return 1;
            }
            
            /* output */
            max7219_interface_debug_print("max7219: set pattern +.\n");
            
            /* spi deinit */
            res = max7219_interface_spi_deinit();
            if (res != 0)
            {
                max7219_interface_debug_print("max7219: basic deinit failed.\n");
                
                return 1;
            }
            
            return 0;
        }
        else if (strncmp("-", mat, 1) == 0)
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
            
            /* cascade init */
            res = max7219_cascade_init();
            if (res != 0)
            {
                max7219_interface_debug_print("max7219: cascade init failed.\n");
                
                return 1;
            }
            
            /* cascade update */
            res = max7219_cascade_update();
            if (res != 0)
            {
                max7219_interface_debug_print("max7219: cascade update failed.\n");
                
                return 1;
            }
            
            /* output */
            max7219_interface_debug_print("max7219: set pattern -.\n");
            
            /* spi deinit */
            res = max7219_interface_spi_deinit();
            if (res != 0)
            {
                max7219_interface_debug_print("max7219: basic deinit failed.\n");
                
                return 1;
            }
            
            return 0;
        }
        else if (strncmp("|", mat, 1) == 0)
        {
            for (j = 0; j < 8; j++)
            {
                for (i = 0; i < MATRIX_CASCADE_LENGTH; i++)
                {
                    g_matrix[i][j] = 0xAA;
                }
            }
            
            /* cascade init */
            res = max7219_cascade_init();
            if (res != 0)
            {
                max7219_interface_debug_print("max7219: cascade init failed.\n");
                
                return 1;
            }
            
            /* cascade deinit */
            res = max7219_cascade_update();
            if (res != 0)
            {
                max7219_interface_debug_print("max7219: cascade update failed.\n");
                
                return 1;
            }
            
            /* output */
            max7219_interface_debug_print("max7219: set pattern |.\n");
            
            /* spi deinit */
            res = max7219_interface_spi_deinit();
            if (res != 0)
            {
                max7219_interface_debug_print("max7219: basic deinit failed.\n");
                
                return 1;
            }
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        max7219_interface_debug_print("Usage:\n");
        max7219_interface_debug_print("  max7219 (-i | --information)\n");
        max7219_interface_debug_print("  max7219 (-h | --help)\n");
        max7219_interface_debug_print("  max7219 (-p | --port)\n");
        max7219_interface_debug_print("  max7219 (-t display | --test=display)\n");
        max7219_interface_debug_print("  max7219 (-t cascade | --test=cascade)\n");
        max7219_interface_debug_print("  max7219 (-e basic-init | --example=basic-init)\n");
        max7219_interface_debug_print("  max7219 (-e basic-deinit | --example=basic-deinit)\n");
        max7219_interface_debug_print("  max7219 (-e basic-num | --example=basic-num) --number=<num>\n");
        max7219_interface_debug_print("  max7219 (-e basic-matrix | --example=basic-matrix) --matrix=<- | | | +>\n");
        max7219_interface_debug_print("  max7219 (-e cascade-init | --example=cascade-init)\n");
        max7219_interface_debug_print("  max7219 (-e cascade-deinit | --example=cascade-deinit)\n");
        max7219_interface_debug_print("  max7219 (-e cascade-matrix | --example=cascade-matrix) --matrix=<- | | | +>\n");
        max7219_interface_debug_print("\n");
        max7219_interface_debug_print("Options:\n");
        max7219_interface_debug_print("  -e <basic-init | basic-deinit | basic-num | basic-matrix | cascade-init | cascade-deinit\n");
        max7219_interface_debug_print("     | cascade-matrix>, --example=<basic-init | basic-deinit | basic-num | basic-matrix\n");
        max7219_interface_debug_print("     | cascade-init | cascade-deinit | cascade-matrix>\n");
        max7219_interface_debug_print("                                    Run the driver example.\n");
        max7219_interface_debug_print("  -h, --help                        Show the help.\n");
        max7219_interface_debug_print("  -i, --information                 Show the chip information.\n");
        max7219_interface_debug_print("      --matrix=<- | | | +>          Set the matrix pattern.\n");
        max7219_interface_debug_print("      --number=<num>                Set the display number, number length must be 8\n");
        max7219_interface_debug_print("                                    and each number can be \"0\" - \"9\"\n");
        max7219_interface_debug_print("  -p, --port                        Display the pin connections of the current board.\n");
        max7219_interface_debug_print("  -t <display | cascade>, --test=<display | cascade>\n");
        max7219_interface_debug_print("                                    Run the driver test.\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        max7219_info_t info;
        
        /* print max7219 info */
        max7219_info(&info);
        max7219_interface_debug_print("max7219: chip is %s.\n", info.chip_name);
        max7219_interface_debug_print("max7219: manufacturer is %s.\n", info.manufacturer_name);
        max7219_interface_debug_print("max7219: interface is %s.\n", info.interface);
        max7219_interface_debug_print("max7219: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        max7219_interface_debug_print("max7219: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        max7219_interface_debug_print("max7219: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        max7219_interface_debug_print("max7219: max current is %0.2fmA.\n", info.max_current_ma);
        max7219_interface_debug_print("max7219: max temperature is %0.1fC.\n", info.temperature_max);
        max7219_interface_debug_print("max7219: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        max7219_interface_debug_print("max7219: SCK connected to GPIO11(BCM).\n");
        max7219_interface_debug_print("max7219: MOSI connected to GPIO10(BCM).\n");
        max7219_interface_debug_print("max7219: CS connected to GPIO8(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = max7219(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        max7219_interface_debug_print("max7219: run failed.\n");
    }
    else if (res == 5)
    {
        max7219_interface_debug_print("max7219: param is invalid.\n");
    }
    else
    {
        max7219_interface_debug_print("max7219: unknown status code.\n");
    }

    return 0;
}
