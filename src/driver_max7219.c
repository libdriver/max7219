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
 * @file      driver_max7219.c
 * @brief     driver max7219 source file
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
  
#include "driver_max7219.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Maxim Integrated MAX7219"        /**< chip name */
#define MANUFACTURER_NAME         "Maxim Integrated"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        4.0f                              /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                              /**< chip max supply voltage */
#define MAX_CURRENT               320.0f                            /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                            /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                             /**< chip max operating temperature */
#define DRIVER_VERSION            2000                              /**< driver version */

/**
 * @brief chip register definition
 */
#define MAX7219_REG_DECODE              0x09        /**< decode register */
#define MAX7219_REG_INTENSITY           0x0A        /**< intensity register */
#define MAX7219_REG_SCAN_LIMIT          0x0B        /**< scan limit register */
#define MAX7219_REG_SHUT_DOWN           0x0C        /**< shut down register */
#define MAX7219_REG_DISPLAY_TEST        0x0F        /**< display test register */

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
uint8_t max7219_set_display(max7219_handle_t *handle, max7219_digital_t digital, uint8_t data)
{
    uint8_t res;
    
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }
    
    res = handle->spi_write(digital, &data, 1);                 /* spi write data */
    if (res != 0)                                               /* check result */
    {
        handle->debug_print("max7219: write failed.\n");        /* write failed */
       
        return 1;                                               /* return error */
    }
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t max7219_set_matrix(max7219_handle_t *handle, uint8_t matrix[8])
{
    uint8_t res;
    uint8_t i;
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    for (i = 0; i < 8; i++)
    {
        res = handle->spi_write(i + 1, &matrix[i], 1);              /* spi write data */
        if (res != 0)                                               /* check result */
        {
            handle->debug_print("max7219: write failed.\n");        /* write failed */
           
            return 1;                                               /* return error */
        }
    }
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t max7219_set_cascade(max7219_handle_t *handle, max7219_cascade_t *cascade, uint16_t len)
{
    uint8_t res;
    uint16_t i;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    if (len > MAX7219_MAX_CASCADE_SIZE)                                                 /* check length */
    {
        handle->debug_print("max7219: len is over MAX7219_MAX_CASCADE_SIZE.\n");        /* write failed */
       
        return 3;                                                                       /* return error */
    }
    
    for (i = 0; i < len; i++)                                                           /* set buf */
    {
        handle->buf[i * 2 + 0] = cascade[i].command;                                    /* set command */
        handle->buf[i * 2 + 1] = cascade[i].data;                                       /* set data */
    }
    res = handle->spi_write_cmd(handle->buf, len * 2);                                  /* write command */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("max7219: write command failed.\n");                        /* write failed */
       
        return 1;                                                                       /* return error */
    }
    
    return 0;                                                                           /* success return 0 */
}

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
uint8_t max7219_set_decode(max7219_handle_t *handle, max7219_decode_t decode)
{
    uint8_t res;
    uint8_t d;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    d = (uint8_t)decode;                                                  /* set the decode */
    res = handle->spi_write(MAX7219_REG_DECODE, (uint8_t *)&d, 1);        /* spi write data */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("max7219: set decode failed.\n");             /* write failed */
       
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t max7219_set_mode(max7219_handle_t *handle, max7219_mode_t mode)
{
    uint8_t res;
    uint8_t m;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    m = (uint8_t)mode;                                                       /* set the mode */
    res = handle->spi_write(MAX7219_REG_SHUT_DOWN, (uint8_t *)&m, 1);        /* spi write data */
    if (res != 0)                                                            /* check result */
    {
        handle->debug_print("max7219: set mode failed.\n");                  /* write failed */
       
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t max7219_set_display_test_mode(max7219_handle_t *handle, max7219_display_test_mode_t mode)
{
    uint8_t res;
    uint8_t m;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    m = (uint8_t)mode;                                                          /* set the mode */
    res = handle->spi_write(MAX7219_REG_DISPLAY_TEST, (uint8_t *)&m, 1);        /* spi write data */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("max7219: set mode failed.\n");                     /* write failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t max7219_set_intensity(max7219_handle_t *handle, max7219_intensity_t intensity)
{
    uint8_t res;
    uint8_t in;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    in = (uint8_t)intensity;                                                  /* set the intensity */
    res = handle->spi_write(MAX7219_REG_INTENSITY, (uint8_t *)&in, 1);        /* spi write data */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("max7219: set intensity failed.\n");              /* write failed */
       
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t max7219_set_scan_limit(max7219_handle_t *handle, max7219_scan_limit_t limit)
{
    uint8_t res;
    uint8_t l;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    l = (uint8_t)limit;                                                       /* set the limit */
    res = handle->spi_write(MAX7219_REG_SCAN_LIMIT, (uint8_t *)&l, 1);        /* spi write data */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("max7219: set scan limit failed.\n");             /* write failed */
       
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t max7219_init(max7219_handle_t *handle)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->debug_print == NULL)                                     /* check debug_print */
    {
        return 3;                                                        /* return error */
    }
    if (handle->spi_init == NULL)                                        /* check spi_init */
    {
        handle->debug_print("max7219: spi_init is null.\n");             /* spi_init is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->spi_deinit == NULL)                                      /* check spi_deinit */
    {
        handle->debug_print("max7219: spi_deinit is null.\n");           /* spi_deinit is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->spi_write_cmd == NULL)                                   /* check spi_write_cmd */
    {
        handle->debug_print("max7219: spi_write_cmd is null.\n");        /* spi_write_cmd is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->spi_write == NULL)                                       /* check spi_write */
    {
        handle->debug_print("max7219: spi_write is null.\n");            /* spi_write is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->delay_ms == NULL)                                        /* check delay_ms */
    {
        handle->debug_print("max7219: delay_ms is null.\n");             /* delay_ms is null */
       
        return 3;                                                        /* return error */
    }
    
    if (handle->spi_init() != 0)                                         /* spi init */
    {
        handle->debug_print("max7219: spi init failed.\n");              /* spi init failed */
       
        return 1;                                                        /* return error */
    }
    handle->inited = 1;                                                  /* flag finish initialization */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t max7219_deinit(max7219_handle_t *handle)
{
    uint8_t res;
    uint8_t mode = (uint8_t)MAX7219_MODE_SHUT_DOWN;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = handle->spi_write(MAX7219_REG_SHUT_DOWN, (uint8_t *)&mode, 1);        /* spi write data */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("max7219: set mode failed.\n");                     /* write failed */
       
        return 4;                                                               /* return error */
    }
    res = handle->spi_deinit();                                                 /* spi deinit */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("max7219: spi deinit failed.\n");                   /* spi deinit failed */
       
        return 1;                                                               /* return error */
    }
    handle->inited = 0;                                                         /* flag close */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t max7219_set_reg(max7219_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                               /* check handle */
    {
        return 2;                                     /* return error */
    }
    if (handle->inited != 1)                          /* check handle initialization */
    {
        return 3;                                     /* return error */
    }
    
    if (handle->spi_write(reg, buf, len) != 0)        /* write data */
    {
        return 1;                                     /* return error */
    }
    else
    {
        return 0;                                     /* success return 0 */
    }
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a max7219 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t max7219_info(max7219_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(max7219_info_t));                        /* initialize max7219 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "SPI", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
