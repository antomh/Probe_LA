/*
 * dac.c
 *
 *  Created on: Aug 10, 2021
 *      Author: Shein
 */

#include <stm32f1xx_hal.h>

#include <main.h>
#include <ad5322.h>
#include <logic_calibration_table.h>

/*---------------------------------------------------------------------------*/

extern SPI_HandleTypeDef hspi1;

/*---------------------------------------------------------------------------*/


/*
 * @brief   DAC A set volt value
 */
void dac_set_A_volt(struct comparison_parameters *cp, union NVRAM *ram)
{
  cp->set_level_status = ERROR;
  /* Check if volt value is in right range */
  switch (cp->relay_state) {
    case M12:
      if ( cp->dac_A_volt < ram->calibration_table.volt_min_mode_12 ||
           cp->dac_A_volt > ram->calibration_table.volt_max_mode_12 ) {
        return;
      }
    case M27:
      if ( cp->dac_A_volt < ram->calibration_table.volt_min_mode_27 ||
           cp->dac_A_volt > ram->calibration_table.volt_max_mode_27 ) {
        return;
      }
  }
  /* If everything is all right set DAC value */
  cp->dac_A_dgt = volt2dgt( &(ram->calibration_table), cp, CH_A );
  DAC_AD5322_Ch2(&hspi1, cp->dac_A_dgt);
  cp->set_level_status = SUCCESS;
}


/*
 * @brief   DAC B set volt value
 */
void dac_set_B_volt(struct comparison_parameters *cp, union NVRAM *ram)
{
  cp->set_level_status = ERROR;
  /* Check if volt value is in right range */
  switch (cp->relay_state) {
    case M12:
      if ( cp->dac_B_volt < ram->calibration_table.volt_min_mode_12 ||
           cp->dac_B_volt > ram->calibration_table.volt_max_mode_12 ) {
        return;
      }
    case M27:
      if ( cp->dac_B_volt < ram->calibration_table.volt_min_mode_27 ||
           cp->dac_B_volt > ram->calibration_table.volt_max_mode_27 ) {
        return;
      }
  }
  /* If everything is all right set DAC value */
  cp->dac_B_dgt = volt2dgt( &(ram->calibration_table), cp, CH_B );
  DAC_AD5322_Ch2(&hspi1, cp->dac_B_dgt);
  cp->set_level_status = SUCCESS;
}


/*
 * @brief   DAC A and B set volt value
 */
void dac_set_A_B_volt(struct comparison_parameters *cp, union NVRAM *ram)
{
  cp->set_level_status = ERROR;
  /* Check if volt value is in right range */
  switch (cp->relay_state) {
    case M12:
      if ( cp->dac_A_volt < ram->calibration_table.volt_min_mode_12 ||
           cp->dac_A_volt > ram->calibration_table.volt_max_mode_12 ||
           cp->dac_B_volt < ram->calibration_table.volt_min_mode_12 ||
           cp->dac_B_volt > ram->calibration_table.volt_max_mode_12 ) {
        return;
      }
    case M27:
      if ( cp->dac_A_volt < ram->calibration_table.volt_min_mode_27 ||
           cp->dac_A_volt > ram->calibration_table.volt_max_mode_27 ||
           cp->dac_B_volt < ram->calibration_table.volt_min_mode_27 ||
           cp->dac_B_volt > ram->calibration_table.volt_max_mode_27 ) {
        return;
      }
  }
  /* If everything is all right set DAC value */
  cp->dac_A_dgt = volt2dgt( &(ram->calibration_table), cp, CH_A );
  cp->dac_B_dgt = volt2dgt( &(ram->calibration_table), cp, CH_B );
  DAC_AD5322_Ch1Ch2(&hspi1, cp->dac_A_dgt, cp->dac_B_dgt);
  cp->set_level_status = SUCCESS;
}


/*
 * @brief   DAC A set digital value
 */
void dac_set_A_dgt(struct comparison_parameters *cp)
{
  if ( cp->dac_A_dgt >= cp->dac_dgt_val_min &&
       cp->dac_A_dgt <= cp->dac_dgt_val_max) {
    DAC_AD5322_Ch1(&hspi1, cp->dac_A_dgt);
    cp->set_level_status = SUCCESS;
  } else {
    cp->set_level_status = ERROR;
  }
}


/*
 * @brief   DAC B set digital value
 */
void dac_set_B_dgt(struct comparison_parameters *cp)
{
  if ( cp->dac_B_dgt >= cp->dac_dgt_val_min &&
       cp->dac_B_dgt <= cp->dac_dgt_val_max) {
    DAC_AD5322_Ch2(&hspi1, cp->dac_B_dgt);
    cp->set_level_status = SUCCESS;
  } else {
    cp->set_level_status = ERROR;
  }
}


/*
 * @brief   DAC A and B set digital value
 */
void dac_set_A_B_dgt(struct comparison_parameters *cp)
{
  if ( cp->dac_A_dgt >= cp->dac_dgt_val_min &&
       cp->dac_A_dgt <= cp->dac_dgt_val_max &&
       cp->dac_A_dgt >= cp->dac_dgt_val_min &&
       cp->dac_A_dgt <= cp->dac_dgt_val_max ) {
    DAC_AD5322_Ch1Ch2(&hspi1, cp->dac_A_dgt, cp->dac_B_dgt);
    cp->set_level_status = SUCCESS;
  } else {
    cp->set_level_status = ERROR;
  }
}
