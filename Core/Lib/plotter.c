#include "plotter.h"

#include "usart.h"
#include <stdio.h>
#include <string.h>

uint32_t plotter_get_time_us(void) {
    uint32_t cycles = DWT->CYCCNT;
    uint32_t us = cycles / 170; //clock is 170Mhz. us = cycles / clock * 1M
    return us;
}

void plotter_transmit_data(data_point_t* data, size_t size) {
    const uint8_t buffer_size = 128;
    char buffer[buffer_size];
    
    for (size_t i = 0; i < size; i++)
    {
        snprintf(buffer, buffer_size, "%lu %lu\n", data[i].time, data[i].value);
        HAL_UART_Transmit(&hlpuart1, (uint8_t*)buffer, strlen(buffer), 100);
    }
}