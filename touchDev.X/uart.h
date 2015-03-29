void UART_Init();

char UART_TX_Empty();

char UART_Data_Ready();
char UART_Read();
char UART_Read_No_Block();

void UART_Read_Text(char *Output, unsigned int length);
void UART_Write(char data);

void UART_Write_Text(char *text);

// functions for printf to work
void putch(char c);
char getch(void);
bit kbhit(void);

