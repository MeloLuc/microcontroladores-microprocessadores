/* ########################################################################

   PICsim - PIC simulator http://sourceforge.net/projects/picsim/

   ########################################################################

   Copyright (c) : 2015  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */


#define LENA  PORTEbits.RE1   // Enable (E)

// Seleção: a informação é um comando(RS=0) ou dado (RS=1)
#define LDAT  PORTEbits.RE2   // RS
#define LPORT PORTD  // Porta de "dados" (DB7-DB0)


#define L_ON	0x0F  // habilita LCD
#define L_OFF	0x08  // desabilita LCD
#define L_CLR	0x01  // limpa LCD
#define L_L1	0x80  // posiciona cursor na primeira linha
#define L_L2	0xC0  // posiciona cursor na segunda linha
#define L_CR	0x0F  // cursor visível		
#define L_NCR	0x0C  // cursor invisível

#define L_CFG   0x28  // configura LCD: 4-bit, 2 linhas, 5*7 pixels

#define print_lcd   lcd_str
#define atraso_ms   __delay_ms

void lcd_init(void);
void lcd_cmd(unsigned char val); 
void lcd_dat(unsigned char val);
void lcd_str(const char* str);

