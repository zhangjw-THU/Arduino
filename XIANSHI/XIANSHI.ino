#include <LiquidCrystal.h>
//LiquidCrystal lcd(12,11,5,4,3,2);  //定义脚位 
LiquidCrystal lcd(10,9,7,6,5,8);  //定义显示屏接脚位
#include <dht11.h>
#include <Wire.h>
dht11 DHT;
#define DHT11_PIN 4
void setup()                                                                                     
{
  lcd.begin(16,2); //设置LCD显示的数目。16 X 2：16格2行。 
Serial.begin(9600);// 设置串口波特率9600
//串口输出”Type, status, Humidity(%), Temperature(C)”
Serial.println("Type,\tHumidity(%),\tTemperature(C)");
}
void loop()
{
int chk;//chk用于存储DHT11传感器的数据
Serial.print("DHT11 \t");
//读取DHT11传感器的数据
chk = DHT.read(DHT11_PIN);
switch(chk)
{
caseDHTLIB_OK:
Serial.print("OK,\t");
break;
caseDHTLIB_ERROR_CHECKSUM:
Serial.print("Checksum error,\t");
break;
caseDHTLIB_ERROR_TIMEOUT:
Serial.print("Time out error,\t");
break;
Serial.print("Unknown error,\t");
break;
}
//串口显示温湿度值
Serial.print(DHT.humidity,1);
Serial.print("\t");
Serial.println(DHT.temperature,1);
//  lcd.setCursor(0,1);  //将闪烁的光标设置到column 0, line 1 (注释：从0开始数起，line 0是显示第一行，line 1是第二行。)
//  lcd.print(millis()/1000); //开机后屏幕现实以秒几时的时间
lcd.setCursor(0,0); 
lcd.print("Humidity(%)");//在lcd第一行显示"Humidity(%)"
lcd.print(DHT.humidity,1);
lcd.setCursor(0,1);
lcd.print("Temperature(C)");//在lcd第二行显示"Temperature(C)"
lcd.print(DHT.temperature,1);
delay(1000);
}
