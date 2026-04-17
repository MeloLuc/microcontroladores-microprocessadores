
#ifndef DISPLAY_7S_H
#define	DISPLAY_7S_H

// Protótipos do decodificador

// Decodificador BCD 7 Segmentos para o display direito
unsigned char display7s_dir(unsigned char digito);

// Decodificador BCD 7 Segmentos para o display direito
unsigned char display7s_esq(unsigned char digito);

// Driver do display 7 segmentos
void display7s(unsigned char digito);

#endif	

