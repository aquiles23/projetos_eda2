
#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UAR
#include <stdlib.h>


/*
 * crc16.c
 *
 *  Created on: 18/03/2014
 *      Author: Renato Coral Sampaio
 */

short CRC16(short crc, char data)
{
    const short tbl[256] = {
        0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
        0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
        0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
        0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
        0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
        0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
        0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
        0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
        0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
        0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
        0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
        0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
        0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
        0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
        0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
        0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
        0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
        0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
        0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
        0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
        0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
        0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
        0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
        0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
        0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
        0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
        0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
        0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
        0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
        0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
        0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
        0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040};
    return ((crc & 0xFF00) >> 8) ^ tbl[(crc & 0x00FF) ^ (data & 0x00FF)];
}

short calcula_CRC(unsigned char *commands, int size) {
	int i;
	short crc = 0;
	for(i=0;i<size;i++) {
		crc = CRC16(crc, commands[i]);
	}
	return crc;
}
void printunsignedchar(unsigned char *p_tx_buffer,int n){
    int i2; 
    for(i2=0;i2<4;i2++){
       p_tx_buffer--;	    
       printf("%u\n",*p_tx_buffer);
    }
}    
int   enviaoutros(unsigned char *p_tx_buffer,unsigned char *tx_buffer,unsigned char  *rx_buffer){
           
    int uart0_filestream = -1;
    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);      //Open in non blocking read/write mode
    if (uart0_filestream == -1)
    {
        printf("Erro - Não foi possível iniciar a UART.\n");
    }
    else
    {
        printf("UART inicializada!\n");
    }    
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;     //<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
   
         
    if (uart0_filestream != -1)
    {
        printf("Escrevendo caracteres na UART ...");
	printunsignedchar(p_tx_buffer,4);
        int count = write(uart0_filestream, &tx_buffer[0],(p_tx_buffer - &tx_buffer[0]));
        if (count < 0)
        {
            printf("UART TX error\n");
        }
        else
        {
            printf("escrito.\n");
	    printf(" a quantidade de bytes escritos foi%d\n",count);
    	}
    }
        
    sleep(1);

    int rx_length;//----- CHECK FOR ANY RX BYTES -----
    if (uart0_filestream != -1)
    {
        // Read up to 255 characters from the port if they are there
        rx_length = read(uart0_filestream, (void*)rx_buffer, 255);      //Filestream, buffer to store in, number of bytes to read (max)
        close(uart0_filestream);
     }	 
    return rx_length;
}


int  potencia(int base , int expoente){
    int i;
    for(i=0;i<expoente;i++){
      base=base*base;
    } 	    
}
int  constroi(int comando, unsigned char *rx_buffer,unsigned char *p_tx_buffer,unsigned char *tx_buffer,int inicio){  
 p_tx_buffer = &tx_buffer[inicio];
 *p_tx_buffer++=1;
 *p_tx_buffer++=35; 
 *p_tx_buffer++=comando;
 *p_tx_buffer++=calcula_CRC(p_tx_buffer,3);
 printf("Buffers de memória criados!\n");
 return enviaoutros(p_tx_buffer,tx_buffer,rx_buffer);
 }
float   pedefloat(){
 unsigned char tx_buffer[255];
 unsigned char rx_buffer[255];
 unsigned char *p_tx_buffer; 
 int rx_length; 
 rx_length=constroi(162,rx_buffer,p_tx_buffer,tx_buffer,0); 
 rx_buffer[rx_length] = '\0';
 char  *a;
 int n;
 a=(char*)rx_buffer; 
 return  atof(rx_buffer);
}
int pedeint(){
 unsigned char tx_buffer[255];
 unsigned char rx_buffer[255];
 unsigned char *p_tx_buffer; 
 int rx_length; 
 rx_length=constroi(161,rx_buffer,p_tx_buffer,tx_buffer,0); 
 rx_buffer[rx_length] = '\0';
 int n;
 char *a;
 a=(char*)rx_buffer; 
 int  b=0;
 int i;
 for(i=0;i<rx_length;i++){ 
  b=b+(a[i]-'0')*potencia(10,i);
 }
 printf("%d",b);
 return b;
}
int  constroienvia(unsigned char *rx_buffer,unsigned char *p_tx_buffer,unsigned char *tx_buffer){  
 *p_tx_buffer++ = 5;
 *p_tx_buffer++ = 2;
 *p_tx_buffer++ = 9;
 *p_tx_buffer++ = 1;
 printf("Buffers de memória criados!\n");
 return enviaoutros(p_tx_buffer,tx_buffer,rx_buffer);
 }

int enviaInt(){
 unsigned char tx_buffer[255];
 unsigned char rx_buffer[255];
 unsigned char *p_tx_buffer;

 int rx_length;
 p_tx_buffer=&tx_buffer[0];
 *p_tx_buffer++=4;
 *p_tx_buffer++=177; 
 rx_length=constroienvia(rx_buffer,p_tx_buffer,tx_buffer); 
 rx_buffer[rx_length] = '\0';
 int n;
 char *a;
 a=(char*)rx_buffer; 
 int  b=0;
 int i;
 for(i=0;i<rx_length;i++){ 
  b=b+(a[i]-'0')*potencia(10,i);
 }
 printf("%d",b);
 return b;
}
float enviaFloat(){
 unsigned char tx_buffer[255];
 unsigned char rx_buffer[255];
 unsigned char *p_tx_buffer;

 int rx_length;
 p_tx_buffer=&tx_buffer[0];
 *p_tx_buffer++=4.4;
 *p_tx_buffer++=178; 
 rx_length=constroienvia(rx_buffer,p_tx_buffer,tx_buffer); 
 rx_buffer[rx_length] = '\0';
 int n;
 char *a;
 a=(char*)rx_buffer; 
 float  b=0.0;
 int i;
 for(i=0;i<rx_length;i++){ 
  b=b+(a[i]-'0')*potencia(10,i);
 }
 printf("%f",b);
 return b;
}

void  enviaString(unsigned char *rx_buffer){
 unsigned char tx_buffer[255];
 unsigned char *p_tx_buffer;
 int i; 
 i=0;
 int rx_length;
 p_tx_buffer=&tx_buffer[0];
 while(rx_buffer[i]!='\0'){
  *p_tx_buffer++=rx_buffer[i];
  i++;
 } 
 printf(" o valor da farse e%s",p_tx_buffer);
 *p_tx_buffer++=178; 
 rx_length=constroienvia(rx_buffer,p_tx_buffer,tx_buffer); 
 rx_buffer[rx_length] = '\0';
}
void pedestring(unsigned char *rx_buffer){
 unsigned char tx_buffer[255];
 unsigned char *p_tx_buffer; 
 int rx_length; 
 rx_length=constroi(163,rx_buffer,p_tx_buffer,tx_buffer,0); 
 rx_buffer[rx_length] = '\0'; 
}
void  solicitaString(){
  char *a;
  unsigned char rx_buffer[255];
  pedestring(rx_buffer);
  a=(char*)rx_buffer;
  printf(" o valor de n e%s",a);
}
void mandaString(){
  char *a;
  unsigned char rx_buffer[255];
  printf(" digite uma frase");
  scanf("%s",rx_buffer);
  enviaString(rx_buffer);
  a=(char*)rx_buffer;
  printf(" o valor de n e%s",a);
}
int  main(){
 int b;       
 b=pedeint();
 printf("%f",b);
}

