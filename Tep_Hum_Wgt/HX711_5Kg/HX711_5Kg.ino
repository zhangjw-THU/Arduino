#include "HX711.h"
float Weight = 0;
#define pin 4
void setup()
{
	Init_Hx711();				//初始化HX711模块连接的IO设置

	Serial.begin(9600);
	Serial.print("Welcome to use!\n");

	//delay(1000);
	Get_Maopi();		//获取毛皮
  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW);
  delay(1000);
}

void loop()
{
	Weight = Get_Weight();	//计算放在传感器上的重物重量
	Serial.print(float((Weight/1000)),3);	//串口显示重量
	Serial.print(" kg\n");	//显示单位
	Serial.print("\n");		//显示单位
  if(Weight>0){
      digitalWrite(pin,LOW);
      Serial.print(digitalRead(pin));}
  else{
      digitalWrite(pin,HIGH);}
	delay(1000);				//延时1s

}
