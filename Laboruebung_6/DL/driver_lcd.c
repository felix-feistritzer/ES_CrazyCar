#include "driver_lcd.h"

extern USCIB1_SPICOM spiCom;
uint8_t LCD_Pos_Array[3];

void Driver_LCD_WriteCommand(uint8_t *data, uint8_t len)
{
    uint8_t i;
    while(spiCom.Status.TxSuc == 0);
    LCD_COMMAND;

    for (i = 0; i < len; i++)
    {
        spiCom.TxData.Data[i] = *data;
        data++;
    }

    spiCom.TxData.len = len;
    spiCom.TxData.cnt = 0;
    HAL_USCIB1_Transmit();
}

void Driver_LCD_SetPosition(uint8_t page, uint8_t column)
{
    LCD_Pos_Array[0] = page;
    LCD_Pos_Array[1] = (column >> 4);
    LCD_Pos_Array[2] = column & 0x0F;

    Driver_LCD_WriteCommand(LCD_Pos_Array, 3);

    while (spiCom.Status.TxSuc == 0);
}

void Driver_LCD_Clear(void)
{
    uint8_t i;
    uint8_t j;
    for (i = 0; (SET_PAGE + i) <= LAST_PAGE; i++)
    {
        Driver_LCD_SetPosition(SET_PAGE + i, 0);
        LCD_DATA;

        for (j = 0; j < LCD_MAX_COL; j++)
        {
            spiCom.TxData.Data[j] = 0xFF;
        }

        spiCom.TxData.len = LCD_MAX_COL;
        HAL_USCIB1_Transmit();

    }
}

void Driver_LCD_Init(void)
{
    LCD_BL_ON;

    LCD_RESET_LOW;
    __delay_cycles(500000);
    LCD_RESET_HIGH;

    uint8_t LCD_Cmd_Array[9] = {CMD_LCD_RESET,
                                CMD_LCD_BIAS,
                                CMD_ADC_SEL_NORMAL,
                                CMD_COMMON_REVERSE,
                                CMD_RES_RATIO,
                                CMD_ELEC_VOL_MODE,
                                CMD_ELEC_VOL_VALUE,
                                CMD_POWER_CONT,
                                CMD_DISPLAY_ON};

    Driver_LCD_WriteCommand(LCD_Cmd_Array, 9);

    while (spiCom.Status.TxSuc == 0);

    Driver_LCD_Clear();
}
