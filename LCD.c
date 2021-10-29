#include<avr/io.h>
#include<util/delay.h>
#include "LCD.h"
#include <Arduino.h>
int static button=0;
int count=0;



void toggle(){
PORTB &= ~(1<<E);
_delay_us(1);
PORTB |= (1<<E);
_delay_us(1);
PORTB &=~(1<<E);
_delay_us(100); // commands needs > 37 us to settle
}



void lcd_print(char sign){

//set to receive data instead of instructions
PORTB |= (1<<RS);
// set sign to send 
PORTD = sign;
toggle();
_delay_us(50);
}
void writeString(char word[])
{
     uint8_t i = 0;                     
    while (word[i] != 0)
    {
        lcd_print(word[i]);
        i++;
        _delay_us(80);  
      if(i==200){
        break;
      }         
    }
    _delay_us(50);
}
void lcd_init(){
  DDRB = 0xFF;
  DDRD=0xFF;

  _delay_ms(50);   // must wait at least 40
  PORTB &=~(1<<RS); //low to accept instructions (R/W is connected Ground)
     //entry mode , set cursor moving direction (left justify) , shift entire display off
  PORTD=(1<<PD3) | (1<<PD2);
  toggle();
  //Function set :DB5, DB4 -> 8BIT MODE , DB3-> 2 LINES DISPLAY
  PORTD = (1<<PD5) | (1<<PD4) | (1<<PD3);
  toggle();
   PORTD= (1<<PD0);
   toggle();
_delay_ms(2);

}


void ClearScreen(){
PORTD= (1<<PD0);
_delay_ms(2);
PORTB &=~(1<<RS);
toggle();
lcd_init();
}



void CursorOn(){
  PORTD=(1<<PD3) |(1<<PD2) | (1<<PD1) ;
   _delay_us(50);
   toggle();
  
}

void CursorOff(){
  PORTD=(1<<PD3) |(1<<PD2);
  PORTD&=~(1<<PD1) ;
   _delay_us(50);
   toggle();
  
}
void cursorBlink(){
PORTD=(1<<PD3) | (1<<PD2) | (1<<PD1) | (1<<PD0);
_delay_us(50);
toggle();
}
void SetCursor(int x, int y){  // x = col , y = row
if(y==1){
for(int i=0; i<x; i++){
PORTD = (1<<PD4) | (1 <<PD2);
_delay_us(40);
toggle();
  }


}
else if(y==2){
int num = 40+x;
for(int i=0; i<num; i++){
PORTD = (1<<PD4);
_delay_us(40);
toggle();
  }
}

}

void ReturnHome(int x){
  for(int i=0; i<x; i++){
PORTD= (1<<PD4);
_delay_us(40);
 toggle();
  }
}


 void Menu1(){

  SetCursor(0,1);
  writeString("Menu");
   SetCursor(-4,2);
  writeString("<   Belysning");
  while (1)
  {
if(PINC & 1 << PC2){
PeeB();
if(button < 1 ){
if(count<100){
  _delay_ms(300);
  Menu2();
  
count++;
}
else{
count = 0;
}
button=1;
}
}
else if(PINC & 1 << PC4){
  PeeB();
_delay_ms(300);
Belysning1();
 }
else{
button=0;
}
    
  }

   
 }


void Menu2(){
  ClearScreen();
  SetCursor(0,1);
  writeString("Menu");
  SetCursor(-4,2);
  writeString("<   Varme       ");
  while (1)
  { 
if(PINC & 1 << PC2){
  _delay_ms(300);
  PeeB();
if(button < 1 ){
if(count<100){
  _delay_ms(300);
  Menu3();
  
count++;
}
else{
count = 0;
}
button=1;
}
}
else if(PINC & 1 << PC4){
_delay_ms(300);
PeeB();
Varme();
 }
else{
button=0;
}
   

  }
  
}

void Menu3(){
  _delay_ms(500);
  ClearScreen();
  SetCursor(0,1);
  writeString("Menu");
   SetCursor(-4,2);
  writeString("    Vitvaror   >");
  while (1)
  {

if(PINC & 1 << PC1){
  _delay_ms(300);
  PeeB();
if(button < 1 ){
if(count<100){
  ClearScreen();
  _delay_ms(300);
  Menu1();
  
count++;
}
else{
count = 0;
}
button=1;
}
}
else if(PINC & 1 << PC4){
_delay_ms(300);
PeeB();
VitVaror();
 }
else{
button=0;
}

  }
  
}

void Varme(){
 
  ClearScreen();
  SetCursor(0,1);
  writeString("Varme");
   SetCursor(-5,2);
  writeString("Golvvarme");
while (1)
{

if(PINC & 1 << PC1){
  _delay_ms(300);
   PeeB();
if(button < 1 ){
if(count<100){
  ClearScreen();
  _delay_ms(300);
  Menu2();
  
count++;
}
else{
count = 0;
}
button=1;
}
}
else if(PINC & 1 << PC2){
  _delay_ms(100);
   PeeB();
   GolvVarmeAktiv();
}
else if(PINC & 1 << PC3){
  _delay_ms(100);
   PeeB();
   GolvVarmeOaktiv();
}
else{
button=0;
}
}
}




void VitVaror(){
  ClearScreen();
  SetCursor(0,1);
  writeString("Vitvaror");
   SetCursor(-8,2);
  writeString("Kaffebryggare");
  while (1)
  {
  
if(PINC & 1 << PC1){
  _delay_ms(300);
  PeeB();
if(button < 1 ){
if(count<100){
  ClearScreen();
  _delay_ms(300);
  Menu3();
  
count++;
}
else{
count = 0;
}
button=1;
}
}
else if(PINC & 1 << PC2){
  _delay_ms(300);
  PeeB();
digitalWrite(13,HIGH);
    ClearScreen();
  SetCursor(0,1);
  writeString("Vitvaror");
   SetCursor(-8,2);
  writeString("Kaffebryggare/Ak");
}
else if(PINC & 1 << PC3){
  _delay_ms(300);
  PeeB();
 digitalWrite(13,LOW);
  ClearScreen();
  SetCursor(0,1);
  writeString("Vitvaror");
   SetCursor(-8,2);
  writeString("Kaffebryggare/Av");
}
else{
button=0;
}
  }

}

void Belysning1(){
 
  ClearScreen();
  SetCursor(0,1);
  writeString("Belysning");
   SetCursor(-9,2);
  writeString("< Vardagsrum   ");
   while (1)
  {

if(PINC & 1 << PC2){
  _delay_ms(300);
  PeeB();
if(button < 1 ){
if(count<100){
  ClearScreen();
  _delay_ms(300);
  Belysning2();
  
count++;
}
else{
count = 0;
}
button=1;
}
}
else if(PINC & 1 << PC4){
  _delay_ms(300);
   PeeB();
  VardagsRum();
 

}

else if(PINC & 1 << PC1){
  _delay_ms(300);
   PeeB();
  ClearScreen();
  Menu1();

}
else{
button=0;
}

  }
  

}

void Belysning2(){
 
  ClearScreen();
  SetCursor(0,1);
  writeString("Belysning");
   SetCursor(-9,2);
  writeString("< Kok   ");
   while (1)
  {

if(PINC & 1 << PC2){
  _delay_ms(300);
   PeeB();
if(button < 1 ){
if(count<100){
  ClearScreen();
  _delay_ms(300);
  Belysning1();
  
count++;
}
else{
count = 0;
}
button=1;
}
}
else if(PINC & 1 << PC4){
  _delay_ms(300);
   PeeB();
  Kok();
}
else if(PINC & 1 << PC1){
  _delay_ms(300);
   PeeB();
  ClearScreen();
  Menu1();

}

else{
button=0;
}

  }
}


void VardagsRum(){

while (1)
{
if(PINC & 1 << PC1){
  _delay_ms(300);
   PeeB();
if(button < 1 ){
if(count<100){
  ClearScreen();
  _delay_ms(300);
  Menu1();
  
count++;
}
else{
count = 0;
}
button=1;
}
}
else if(PINC & 1 << PC3){
  _delay_ms(300);
   PeeB();
  digitalWrite(11,LOW);
 ClearScreen();
  SetCursor(0,1);
  writeString("Belysning");
   SetCursor(-9,2);
  writeString("Vardagsrum/Av   ");
}
else if(PINC & 1 << PC2){
_delay_ms(300);
 PeeB();
digitalWrite(11,HIGH);
  ClearScreen();
  SetCursor(0,1);
  writeString("Belysning");
   SetCursor(-9,2);
  writeString("Vardagsrum/Aktiv  ");
}

else{
button=0;
}

}
}
void PeeB(){
  
  while (1)
  {
    DDRC=255;
   _delay_ms(100);
   DDRC=0;
   break;
  }
  
}
void Kok(){
 while (1)
{
if(PINC & 1 << PC1){
  _delay_ms(300);
   PeeB();
if(button < 1 ){
if(count<100){
  ClearScreen();
  _delay_ms(300);
  Menu1();
  
count++;
}
else{
count = 0;
}
button=1;
}
}
else if(PINC & 1 << PC3){
  _delay_ms(300);
   PeeB();
  digitalWrite(10,LOW);
  ClearScreen();
  SetCursor(0,1);
  writeString("Belysning");
   SetCursor(-9,2);
  writeString("Kok/Av   ");
}
else if(PINC & 1 << PC2){
  _delay_ms(300);
   PeeB();
digitalWrite(10,HIGH);
  ClearScreen();
  SetCursor(0,1);
  writeString("Belysning");
   SetCursor(-9,2);
  writeString("Kok/Aktiv  ");
}

else{
button=0;
}

}

}

void GolvVarmeAktiv(){
digitalWrite(12,HIGH);
  ClearScreen();
  SetCursor(0,1);
  writeString("Varme");
   SetCursor(-5,2);
  writeString("Golvvarme/Aktiv");
}

void GolvVarmeOaktiv(){
 digitalWrite(12,LOW);
    ClearScreen();
  SetCursor(0,1);
  writeString("Varme");
   SetCursor(-5,2);
  writeString("Golvvarme/Av");
}