//LingShun Lab
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);      //构造一个LiquidCrystal的类成员。使用数字IO ，12,11,5,4,3,2

void setup()
{
  lcd.begin(16,2);    //初始化LCD1602
  lcd.print("Welcome to use!"); //液晶显示Welcome to use！
  delay(1000);      //延时1000ms
  lcd.clear();      //液晶清屏
}

void loop()
{
 
  lcd.setCursor(0,0);     //设置液晶开始显示的指针位置，0列0行，人类理解的第一行
  lcd.print("Hello World!");

  lcd.setCursor(0,1);       //0列，1行，人类理解的第二行
  lcd.print("Zhang JiaWei");
  delay(1000);        //延时1000ms
  lcd.setCursor(0,0);
  lcd.print("Good Job!   "); 
  delay(1000);                //延时1000ms
}
