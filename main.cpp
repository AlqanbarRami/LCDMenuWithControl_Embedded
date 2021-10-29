#include<avr/io.h>
#include<util/delay.h>
extern "C"{
    #include "LCD.h"
}
  
#define RS PB1
#define E PB0


/*
Belysning:

Vardagsrum
Kök
Värme:

Golvvärme
Vitvaror:

Kaffebryggare
*/
/*
  //entry mode , set cursor moving direction (left justify) , shift entire display off
  PORTD=(1<<PD3) | (1<<PD2);
  toggle();
  */


int main(){

   lcd_init();
   Menu1();
    

  
 
  return 0 ;
}