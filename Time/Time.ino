#include <LiquidCrystal.h> //LCD1602的库

#include  <Wire.h>  //DS1307需要的库



 



LiquidCrystal lcd1602(12, 11, 5, 4, 9, 8);//设置Arduino与LCD液晶屏的接口





long val=0;

int hour;

int minute;

int second;

void setup()

{

Serial.begin(9600);

Wire.begin(); //初始化总线

DS1307.begin(); //初始化时钟

DS1307.set(RTC_SECOND, 00);  //初始化时钟的时间

DS1307.set(RTC_MINUTE, 30);

DS1307.set(RTC_HOUR, 07);

DS1307.set(RTC_DAY, 07);

DS1307.set(RTC_MONTH, 10);

DS1307.set(RTC_YEAR, 14);

lcd1602.begin(16, 2);//初始化液晶面板

lcd1602.print("time to temperature");//显示文字



delay(1000);

}

void loop ()

{

   /*读取时间与温度传感器数据*/


 

DateTime now = DS1307.now();// 获取当前时间给now实例

hour=now.hour();// 获取当前时间小时

minute=now.minute();// 获取当前时间给分钟

second=now.second();// 获取当前时间给秒

/*把信息输出到LCD上*/


lcd1602.setCursor(0,1) ;//将光标显示在第二行

lcd1602.print(hour);//在LCD第二行上输出hour

lcd1602.print(':');

lcd1602.print(minute);//在LCD上输出minute

lcd1602.print(':');

lcd1602.print(second);//在LCD上输出second

lcd1602.print("     ");//在LCD上输出两个空格

/*与电脑串口通讯，波特率9600*/


  Serial.print("data:");

Serial.print(dateTime.year(), DEC); //传送年份，DEC是十进制的表示的含义

Serial.print('/');

Serial.print(dateTime.month(), DEC); //传送月份

Serial.print('/');

Serial.print(dateTime.day(), DEC); //传送月份中的第几天

Serial.print(' ');//显示一个空格

Serial.print(dateTime.hour(), DEC); //传送小时

Serial.print(':');

Serial.print(dateTime.minute(), DEC); //传送分钟

Serial.print(':');

Serial.print(dateTime.second(), DEC); //传送秒

Serial.print(' ');


delay(500);

 

}

