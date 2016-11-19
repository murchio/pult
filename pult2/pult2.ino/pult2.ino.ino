#include <VirtualWire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 7
#define TEMPERATURE_PRECISION 9
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress;
bool n;
// перед заливкой отключить моргание 13 пина в
byte addr[8]={0x28,0xFF,0xF7,0xDC,0x81,0x16,0x03,0xC1};
bool addrOk = false;



const byte addr_TN1 = 0; //время направления 1 время МСЕК целое
const byte count_TN1 = 4; //количество байт
const byte addr_TN2 = 4; //время направления 2 время МСЕК целое
const byte count_TN2 = 4; //количество байт
const byte addr_Gmorg = 8; //режим желтого моргающего вкл/выкл
const byte count_Gmorg = 1; //количество байт
const byte addr_geltstart = 9; //желтый моргающий по расписанию время старт целое от 0 до 24 (часы)
const byte count_geltstart = 4; //количество байт
const byte addr_geltiend = 13; //желтый моргающий по расписанию время стоп целое от 0 до 24 (часы)
const byte count_geltiend = 4; //количество байт
const byte addr_oproscherez = 17; //опрос аналоговых входов через время МСЕК, целое
const byte count_oproscherez = 4; //количество байт
const byte addr_koloprosov = 21; // количество опросов для расчета среднего значения аналоговых входов, целое
const byte count_koloprosov  = 4; //количество байт
const byte addr_logEdenica = 25; // значение для логическая единица при измерении аналоговых входов, целое
const byte count_logEdenica = 4; //количество байт
const byte addr_tzm = 29; // период моргания зеленого МСЕК целое
const byte count_tzm = 4; //количество байт
const byte addr_zp = 33; // количество повоторений моргания зеленого, целое
const byte count_zp = 4; //количество байт
const byte addr_tgm = 37; // период моргания желтого МСЕК целый
const byte count_tgm = 4; //количество байт
const byte addr_tg = 41; // Горение желтого при переходе с красного на зеленый
const byte count_tg = 4; //количество байт
const byte addr_ch1 = 51; //канал №1
const byte count_ch1 = 1; //количество байт
const byte addr_ch2 = 52; //канал №2
const byte count_ch2 = 1; //количество байт
const byte addr_ch3 = 53; //канал №3
const byte count_ch3 = 1; //количество байт
const byte addr_ch4 = 54; //канал №4
const byte count_ch4 = 1; //количество байт
const byte addr_ch5 = 55; //канал №5
const byte count_ch5 = 1; //количество байт
const byte addr_ch6 = 56; //канал №6
const byte count_ch6 = 1; //количество байт
const byte addr_ch7 = 57; //канал №7
const byte count_ch7 = 1; //количество байт
const byte addr_ch8 = 58; //канал №8
const byte count_ch8 = 1; //количество байт
const byte addr_ch9 = 59; //канал №9
const byte count_ch9 = 1; //количество байт
const byte addr_ch10 = 60; //канал №=10
const byte count_ch10 = 1; //количество байт
const byte addr_ch11 = 61; //канал №11
const byte count_ch11 = 1; //количество байт
const byte addr_ch12 = 62; //канал №12
const byte count_ch12 = 1; //количество байт
const byte addr_ch13 = 63; //канал №13
const byte count_ch13 = 1; //количество байт
const byte addr_ch14 = 64; //канал №14
const byte count_ch14 = 1; //количество байт
const byte addr_ch15 = 65; //канал №15
const byte count_ch15 = 1; //количество байт
const byte addr_ch16 = 66; //канал №16
const byte count_ch16 = 1; //количество байт

const byte addr_s1 = 201; //канал №1
const byte count_s1 = 1; //количество байт
const byte addr_s2 = 202; //канал №2
const byte count_s2 = 1; //количество байт
const byte addr_s3 = 203; //канал №3
const byte count_s3 = 1; //количество байт
const byte addr_s4 = 204; //канал №4
const byte count_s4 = 1; //количество байт
const byte addr_s5 = 205; //канал №5
const byte count_s5 = 1; //количество байт
const byte addr_s6 = 206; //канал №6
const byte count_s6 = 1; //количество байт
const byte addr_s7 = 207; //канал №7
const byte count_s7 = 1; //количество байт
const byte addr_s8 = 208; //канал №8
const byte count_s8 = 1; //количество байт
const byte addr_s9 = 209; //канал №9
const byte count_s9 = 1; //количество байт
const byte addr_s10 = 210; //канал №=10
const byte count_s10 = 1; //количество байт
const byte addr_s11 = 211; //канал №11
const byte count_s11 = 1; //количество байт
const byte addr_s12 = 212; //канал №12
const byte count_s12 = 1; //количество байт
const byte addr_s13 = 213; //канал №13
const byte count_s13 = 1; //количество байт
const byte addr_s14 = 214; //канал №14
const byte count_s14 = 1; //количество байт
const byte addr_s15 = 215; //канал №15
const byte count_s15 = 1; //количество байт
const byte addr_s16 = 216; //канал №16
const byte count_s16 = 1; //количество байт
const byte addr_daizeleni = 217; //канал №16
const byte count_daizeleni = 1; //количество байт
const byte addr_kill = 218; //канал №16
const byte count_lill = 1; //количество байт

unsigned long TN1;
unsigned long TN2;
int kolsms = 50;
int pausesms = 50; //MSEC

void setup() 
{
  Serial.begin(9600);  
  startradio();
 sendsms(addr_TN2,count_TN2, 30000, 1); //зеленый в направлении 1 - 10 сек
//  sendsms(addr_Gmorg, count_Gmorg, 0,1); // отключить жм
//sendsms(addr_Gmorg, count_Gmorg, 1,1); //включить жм
//sendsms(addr_s1, count_s1, 1,1);  //канал №1 отключить
//sendsms(addr_s16, count_s16, 0,1);  
}
void loop()
{
  delay(5000);

}
void startradio()
{
pinMode(13,OUTPUT);
vw_set_ptt_inverted(true);
vw_set_tx_pin(6);
vw_setup(2000);// скорость передачи данных в Kbps  
}
void sendsms(int addr,int count, unsigned long data, bool ie)
{
  for (int i = 0; i <kolsms; i++)
 {
  n=!n;
  delay(pausesms);
  digitalWrite(13,n);
  //uint8_t *controller;
  String str = "3!z}";
  if (ie) str += "Ia";
  else str += "Ea";
  str += String(addr) + 'c' + String(count) + 'd' + String(data);
  char controller[str.length()];
  str.toCharArray(controller,str.length()+1);
  for(int i = 0;i<str.length();i++)
  {
    Serial.write(controller[i]);
  }
  Serial.println("");
  vw_send((uint8_t *)controller, strlen(controller));
  vw_wait_tx(); // ждем, пока отправится все сообщение
 }
}

