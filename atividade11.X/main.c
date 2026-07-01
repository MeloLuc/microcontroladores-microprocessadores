/*
 * File:   main.c
 * Author: Lucas Melo Monteiro
 *
 * Created on 28 de Junho de 2026, 22:10
 */

#include "adc.h"
#include "display.h"
#include "lcd.h"
#include "moving_average.h"
#include "system.h"

#define BOTAO_INC   PORTBbits.RB3
#define BOTAO_DEC   PORTBbits.RB4
#define BOTAO_RESET PORTBbits.RB5
#define BOTAO_POWER PORTAbits.RA5
#define HEATER      PORTCbits.RC5 // Pino padrão do Heater/Ventoinha no PICGenios

#define LOOP_DELAY_MS 50U

static moving_average_t temp_filter;
static uint8_t setpoint = 40;
static uint8_t system_on = 0;
static uint8_t heater_state = 0;
static uint8_t display_mode = 0; // 0 = Ref, 1 = Heater

static void prime_filters(void)
{
    uint8_t i;
    for (i = 0U; i < MOVING_AVERAGE_SIZE; i++) {
        (void)moving_average_update(&temp_filter, adc_read(0)); // Canal 0 (AN0)
        __delay_ms(2);
    }
}

void main(void)
{
    uint16_t adc_value;
    uint16_t temp_x10;
    uint16_t display_timer = 0;
    uint16_t lcd_timer = 0;
    
    // Controle de estado para detectar borda de descida dos botões
    uint8_t btn_inc_last = 1, btn_dec_last = 1, btn_reset_last = 1, btn_power_last = 1;

    system_init();
    adc_init();
    lcd_init();

    moving_average_init(&temp_filter);
    prime_filters();
    HEATER = 0;

    while (1) {
        // Leitura analógica e Filtro da Média Móvel
        adc_value = moving_average_update(&temp_filter, adc_read(0));
        
        // Conversão com 1 casa decimal: (ADC * 5000) / 1023 -> mV. Dividido por 10 = Temperatura x10
        temp_x10 = (uint16_t)(((uint32_t)adc_value * 5000UL) / 1023UL);

        // Lógica dos Botões (borda de descida)
        uint8_t btn_power = BOTAO_POWER;
        if (btn_power == 0 && btn_power_last == 1) {
            system_on = !system_on;
        }
        btn_power_last = btn_power;

        uint8_t btn_inc = BOTAO_INC;
        if (btn_inc == 0 && btn_inc_last == 1) {
            if(setpoint < 99) setpoint++;
        }
        btn_inc_last = btn_inc;

        uint8_t btn_dec = BOTAO_DEC;
        if (btn_dec == 0 && btn_dec_last == 1) {
            if(setpoint > 0) setpoint--;
        }
        btn_dec_last = btn_dec;

        uint8_t btn_reset = BOTAO_RESET;
        if (btn_reset == 0 && btn_reset_last == 1) {
            setpoint = 40;
        }
        btn_reset_last = btn_reset;

        // Controle Liga-Desliga com Histerese de 10 graus
        if (system_on) {
            if (temp_x10 <= ((uint16_t)(setpoint - 5) * 10U)) {
                heater_state = 1; // Liga o Heater
            } else if (temp_x10 >= ((uint16_t)(setpoint + 5) * 10U)) {
                heater_state = 0; // Desliga o Heater
            }
        } else {
            heater_state = 0;
        }
        HEATER = heater_state;

        // Alternância da segunda linha do display a cada 2 segundos
        display_timer += LOOP_DELAY_MS;
        if (display_timer >= 2000U) {
            display_mode = !display_mode;
            display_timer = 0;
        }

        // Atualização do LCD
        lcd_timer += LOOP_DELAY_MS;
        if (lcd_timer >= LCD_REFRESH_DELAY_MS) {
            display_show_dashboard(temp_x10, setpoint, heater_state, display_mode, system_on);
            lcd_timer = 0;
        }

        __delay_ms(LOOP_DELAY_MS);
    }
}