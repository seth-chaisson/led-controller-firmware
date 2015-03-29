
#include <xc.h> 


void UART_Init()
{
	  CREN =0;     // disable serial port
	
		//baud rate  9600
	  SPBRG = 51; // number from table on page 302
	  BRGH = 0;	   // use these for spbrg value	
	  BRG16 = 0;   //
	  SYNC = 0;    // set to async mode
	  SPEN = 1;	   // enable serial port
      CREN = 1;    // enable recive 
      TXEN = 1;    // enable transmit

}

char UART_TX_Empty()
{
  return TRMT;
}

char UART_Data_Ready()
{
   return RCIF;
}
char UART_Read()
{

  while(!RCIF);
  return RCREG;
}
char UART_Read_No_Block()
{
    int i;

	if( OERR)// if the recive buffer is overrun reset the uart
	{
		i = RCREG;
		i = RCREG;
		UART_Init();

                return 0xff;

		//PORTC = 0XFF;
	}


    if(RCIF)
        return RCREG;
    else
        return 0;
}

void UART_Read_Text(char *Output, unsigned int length)
{
	int i;

	if( OERR)// if the recive buffer is overrun reset the uart
	{
		i = RCREG;
		i = RCREG;
		UART_Init();
		PORTC = 0XFF;
	}

	for(int i=0;i<length;i++)
	{	
		Output[i] = UART_Read();
		if(Output[i] == 'U')
			i =-1; // if a u is recived reset the string
		if(i ==1 ||i ==2 ||i ==3 ||i ==4 ) // the next for bits should be numbers
			if( !(Output[i] <= '9' && Output[i] >='0' ))
				i = -1;                    // if they are not start over
	}
	Output[length] = '\0';    // end string with a null
}

void UART_Write(char data)
{
  while(!TRMT);
  TXREG = data;
}

void UART_Write_Text(char *text)
{
  int i;
  for(i=0;text[i]!='\0';i++)
	  UART_Write(text[i]);
}

// functions for printf to work
void putch(char c)
{
	while(!TRMT);
    TXREG = c;
}
char getch(void)
{
	while(!RCIF);
    return RCREG;
}
bit kbhit(void)
{
	return RCIF;
}

