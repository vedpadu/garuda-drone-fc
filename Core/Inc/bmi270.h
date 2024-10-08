#ifndef INC_BMI270_H_
#define INC_BMI270_H_

#include "stm32f4xx_hal.h"
// TODO: pin file?
#include "main.h"
#include "tim.h"
#include "spi.h"
#include "gpio.h"

#define CS_Pin_BMI270 SPI1_CS_Pin
#define CS_GPIO_Port_BMI270 GPIOA

// 12 bytes for all the accel and gyro data and 2 bytes for first two dummy bytes
#define BMI_DATA_BUF_SIZE 14

extern uint8_t bmi270_spi_working;
extern uint8_t bmi270_init_working;
extern uint8_t bmi270_ready;
extern int countGyros;
extern uint8_t bmi270_data_read_buf[BMI_DATA_BUF_SIZE];

// not a complete list
typedef enum {
    BMI270_REG_CHIP_ID = 0x00,
    BMI270_REG_ERR_REG = 0x02,
    BMI270_REG_STATUS = 0x03,
    BMI270_REG_ACC_DATA_X_LSB = 0x0C,
    BMI270_REG_GYR_DATA_X_LSB = 0x12,
    BMI270_REG_SENSORTIME_0 = 0x18,
    BMI270_REG_SENSORTIME_1 = 0x19,
    BMI270_REG_SENSORTIME_2 = 0x1A,
    BMI270_REG_EVENT = 0x1B,
    BMI270_REG_INT_STATUS_0 = 0x1C,
    BMI270_REG_INT_STATUS_1 = 0x1D,
    BMI270_REG_INTERNAL_STATUS = 0x21,
    BMI270_REG_TEMPERATURE_LSB = 0x22,
    BMI270_REG_TEMPERATURE_MSB = 0x23,
    BMI270_REG_FIFO_LENGTH_LSB = 0x24,
    BMI270_REG_FIFO_LENGTH_MSB = 0x25,
    BMI270_REG_FIFO_DATA = 0x26,
	BMI270_REG_CAS = 0x3c,
    BMI270_REG_ACC_CONF = 0x40,
    BMI270_REG_ACC_RANGE = 0x41,
    BMI270_REG_GYRO_CONF = 0x42,
    BMI270_REG_GYRO_RANGE = 0x43,
    BMI270_REG_AUX_CONF = 0x44,
    BMI270_REG_FIFO_DOWNS = 0x45,
    BMI270_REG_FIFO_WTM_0 = 0x46,
    BMI270_REG_FIFO_WTM_1 = 0x47,
    BMI270_REG_FIFO_CONFIG_0 = 0x48,
    BMI270_REG_FIFO_CONFIG_1 = 0x49,
    BMI270_REG_SATURATION = 0x4A,
    BMI270_REG_INT1_IO_CTRL = 0x53,
    BMI270_REG_INT2_IO_CTRL = 0x54,
    BMI270_REG_INT_LATCH = 0x55,
    BMI270_REG_INT1_MAP_FEAT = 0x56,
    BMI270_REG_INT2_MAP_FEAT = 0x57,
    BMI270_REG_INT_MAP_DATA = 0x58,
    BMI270_REG_INIT_CTRL = 0x59,
    BMI270_REG_INIT_DATA = 0x5E,
    BMI270_REG_ACC_SELF_TEST = 0x6D,
    BMI270_REG_GYR_SELF_TEST_AXES = 0x6E,
    BMI270_REG_PWR_CONF = 0x7C,
    BMI270_REG_PWR_CTRL = 0x7D,
    BMI270_REG_CMD = 0x7E,
} bmi270Register_e;

uint8_t bmi270_read_register(uint8_t rgstr, uint8_t* out_buf);
void bmi270_write_register(uint8_t rgstr, uint8_t data);
uint8_t* bmi270_burst_read(uint8_t rgstr, uint8_t* out_buf, uint16_t size, uint32_t timeout);
void bmi270_burst_transmit(uint8_t* transmit_buf, uint32_t timeout, uint16_t size);
void bmi270_cs_high();
void bmi270_cs_low();

void bmi270_read_data();
int16_t bmi270_get_CAS();

void bmi270_init();
void bmi270_configure_settings();
void bmi270_configure_EXTI();
void bmi270_enable_SPI();

float bmi270_lsb_to_mps2(int16_t val, float g_range, uint8_t bit_width);
float bmi270_lsb_to_dps(int16_t val, float dps, uint8_t bit_width);

#endif
