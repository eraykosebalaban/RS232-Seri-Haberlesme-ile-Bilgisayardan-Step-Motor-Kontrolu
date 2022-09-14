#include<16f877.h>

#use delay(clock=4000000)

#use fast_io(b)
#use fast_io(d)

#include<lcd.c>

#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7, parity=N, stop=1)

int i,hiz=500;
char islem=0;

const int yarim_adim[]={0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09}; //Step motor yarým adým dönüþ adýmlarý

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

islem="null"; //islem deðiþkeninin içeriði boþ olarak ayarlanýyor.
islem=getchar(); //rs232'den gelen karakter islem deðiþkenine aktarýlýyor. Yani gelen karakter okunuyor.
putc(islem); //rs232 üzerinden klavyeden girilen karakter ekrana gönderiiliyor.

while(islem=='R' || islem=='r'){

   printf(lcd_putc,"\n\fMotor Saga \nDonuyor...",);
   for(;i<8;i++){ //Step motorun saða dönmesi için for döngüsü baþlatýlýyor.Bunlar Saða dönme deðerleri
   
   output_b(yarim_adim[i]); //Step motor her defasýnda 1 adým ilerlemesini saðlýyoruz
   delay_ms(hiz); //adýmlar arasý süre
   
   if(i==7)
   i=0; //i deðeri 7 olursa sýfýrla
   
if(kbhit())
break; //klavyeden veri alýndýysa döngüden çýk. For döngüsünden

   }
if(kbhit())
break; //klavyeden ver alýndýysa döngüden çýk.While döngüsünden

}

while(islem=='L' || islem=='l'){

   printf(lcd_putc,"\n\fMotor Sola \nDonuyor...");
   for(;i>=0;i--){ //Step motorun sola dönmesi için for döngüsü baþlatýlýyor.Bunlar sola dönme deðerleri
   
   if(i==0)
   i=7; //i deðeri 0 olursa 7 olsun
   
   output_b(yarim_adim[i]); //Step motor her defasýnda 1 adým ilerlemesini saðlýyoruz
   delay_ms(hiz); //adýmlar arasý süre
    
if(kbhit())
break; //klavyeden veri alýndýysa döngüden çýk. For döngüsünden

   }
if(kbhit())

break; //klavyeden ver alýndýysa döngüden çýk.While döngüsünden
 
 }
printf(lcd_putc,"\n\fMotor Duruyor...");
}

}





