#define RS PB1
#define E PB0

 // initialition , 2 lines , no specific font 
void lcd_init();  

//To accept the instruction
void toggle();   

 // print char 
void lcd_print(char sign); 

 // print string 
void writeString(char word[]); 

// Clear the display
void ClearScreen(); 

 // turn on the cursor
void CursorOn();  

// turn off the cursor
void CursorOff();  

// to move the cursor , x = column and y= row , both column start with 0 and ends with 15
void SetCursor(int x, int y) ; 

void Menu1();
void Menu2();
void Menu3();
void Belysning1();
void Belysning2();
void Varme(); 
void VitVaror();
void VardagsRum();
void Kok();
void ReturnHome();
void PeeB();
void GolvVarmeAktiv();
void GolvVarmeOaktiv();
 //Extra för test , inte en del av uppgift
void cursorBlink();

