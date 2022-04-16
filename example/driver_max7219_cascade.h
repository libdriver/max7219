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
 * @file      driver_max7219_cascade.h
 * @brief     driver max7219 cascade header file
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

#ifndef DRIVER_MAX7219_CASCADE_H
#define DRIVER_MAX7219_CASCADE_H

#include "driver_max7219_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup max7219_example_driver
 * @{
 */

/**
 * @brief max7219 cascade example matrix cascade length definition
 */
#define  MATRIX_CASCADE_LENGTH 4        /**< cascade 4 */

/**
 * @brief max7219 cascade example default definition
 */
#define MAX7219_CASCADE_DEFAULT_DECODE           MAX7219_DECODE_CODEB_DIGITS_NONE        /**< set no decode */
#define MAX7219_CASCADE_DEFAULT_MODE             MAX7219_MODE_NORMAL                     /**< set normal mode */
#define MAX7219_CASCADE_DEFAULT_TEST_MODE        MAX7219_DISPLAY_TEST_MODE_OFF           /**< set test mode off */
#define MAX7219_CASCADE_DEFAULT_INTENSITY        MAX7219_INTENSITY_31_32                 /**< set intensity 31/32 */
#define MAX7219_CASCADE_DEFAULT_SCAN_LIMIT       MAX7219_SCAN_LIMIT_DIGIT_0_7            /**< set scan limit digit 0-7 */

extern uint8_t g_matrix[MATRIX_CASCADE_LENGTH][8];        /**< global matrix */

/**
 * @brief  cascade example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t max7219_cascade_init(void);

/**
 * @brief  cascade example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t max7219_cascade_deinit(void);

/**
 * @brief  cascade example update
 * @return status code
 *         - 0 success
 *         - 1 update failed
 * @note   none
 */
uint8_t max7219_cascade_update(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
