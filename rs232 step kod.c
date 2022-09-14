#include<16f877.h>

#use delay(clock=4000000)

#use fast_io(b)
#use fast_io(d)

#include<lcd.c>

#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7, parity=N, stop=1)

int i,hiz=500;
char islem=0;

const int yarim_adim[]={0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09}; //Step motor yar�m ad�m d�n�� ad�mlar�

void main(){

setup_psp(PSP_DISABLED);
setup_timer_1(T1_DISABLED);
setup_timer_2(T2_DISABLED,0,1);
setup_adc_ports(NO_ANALOGS);
setup_adc(ADC_OFF);
setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);

set_tris_b(0x00);
set_tris_d(0x00);

output_d(0x00);
output_b(0x00);

lcd_init();

printf(lcd_putc,"Islem Seciniz:");
delay_ms(200);
printf(lcd_putc,"\nSag (R) Sol (L)");
delay_ms(200);

while(true){

islem="null"; //islem de�i�keninin i�eri�i bo� olarak ayarlan�yor.
islem=getchar(); //rs232'den gelen karakter islem de�i�kenine aktar�l�yor. Yani gelen karakter okunuyor.
putc(islem); //rs232 �zerinden klavyeden girilen karakter ekrana g�nderiiliyor.

while(islem=='R' || islem=='r'){

   printf(lcd_putc,"\n\fMotor Saga \nDonuyor...",);
   for(;i<8;i++){ //Step motorun sa�a d�nmesi i�in for d�ng�s� ba�lat�l�yor.Bunlar Sa�a d�nme de�erleri
   
   output_b(yarim_adim[i]); //Step motor her defas�nda 1 ad�m ilerlemesini sa�l�yoruz
   delay_ms(hiz); //ad�mlar aras� s�re
   
   if(i==7)
   i=0; //i de�eri 7 olursa s�f�rla
   
if(kbhit())
break; //klavyeden veri al�nd�ysa d�ng�den ��k. For d�ng�s�nden

   }
if(kbhit())
break; //klavyeden ver al�nd�ysa d�ng�den ��k.While d�ng�s�nden

}

while(islem=='L' || islem=='l'){

   printf(lcd_putc,"\n\fMotor Sola \nDonuyor...");
   for(;i>=0;i--){ //Step motorun sola d�nmesi i�in for d�ng�s� ba�lat�l�yor.Bunlar sola d�nme de�erleri
   
   if(i==0)
   i=7; //i de�eri 0 olursa 7 olsun
   
   output_b(yarim_adim[i]); //Step motor her defas�nda 1 ad�m ilerlemesini sa�l�yoruz
   delay_ms(hiz); //ad�mlar aras� s�re
    
if(kbhit())
break; //klavyeden veri al�nd�ysa d�ng�den ��k. For d�ng�s�nden

   }
if(kbhit())

break; //klavyeden ver al�nd�ysa d�ng�den ��k.While d�ng�s�nden
 
 }
printf(lcd_putc,"\n\fMotor Duruyor...");
}

}





