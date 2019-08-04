
#include <LiquidCrystal.h>
#include "HX711.h"
float Weight = 0;
int temp;
int humi;//湿度
int tol;//校对码
int j;
LiquidCrystal lcd(12,11,5,4,9,8);      //构造一个LiquidCrystal的类成员。使用数字IO ，12,11,5,4,9,8
unsigned int loopCnt;
int chr[40] = {0};                    //创建数字数组，用来存放40个bit
unsigned long time;
#define pin 7
#define pinkeyTWO 13
#define pinkeyONE 10
/*#define pin_data_type 13*/
void setup()
{
  Init_Hx711();                   //初始化HX711模块连接的IO设置
  lcd.begin(16,2);               //初始化LCD1602
  lcd.print("Welcome to use!"); //液晶显示Welcome to use！
  Serial.begin(9600);
  Serial.print("Welcome to use!\n");
  delay(500);               //延时500ms
  lcd.clear();             //液晶清屏
  Get_Maopi();            //获取毛皮
  pinMode(pinkeyTWO,INPUT);
  pinMode(pinkeyONE,INPUT);
}

void loop()
{
  
   bgn:
  delay(2000);
//设置2号接口模式为：输出
//输出低电平20ms（>18ms）
//输出高电平40μs
  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW);
  delay(20);
  digitalWrite(pin,HIGH);
  delayMicroseconds(40);
  digitalWrite(pin,LOW);
//设置2号接口模式：输入
  pinMode(pin,INPUT);
  //高电平响应信号
  loopCnt=10000;
  while(digitalRead(pin) != HIGH)
  {
    if(loopCnt-- == 0)
    {
//如果长时间不返回高电平，输出个提示，重头开始。
      Serial.println("HIGH");
      goto bgn;
    }
  }
  //低电平响应信号
  loopCnt=30000;
  while(digitalRead(pin) != LOW)
  {
    if(loopCnt-- == 0)
    {
//如果长时间不返回低电平，输出个提示，重头开始。
      Serial.println("LOW");
      goto bgn;
    }
  }
//开始读取bit1-40的数值  
    for(int i=0;i<40;i++)
  {
    while(digitalRead(pin) == LOW)
    {}
//当出现高电平时，记下时间“time”
    time = micros();
    while(digitalRead(pin) == HIGH)
    {}
//当出现低电平，记下时间，再减去刚才储存的time
//得出的值若大于50μs，则为‘1’，否则为‘0’
//并储存到数组里去
    if (micros() - time >50)
    {
      chr[i]=1;
    }else{
      chr[i]=0;
    }
  }
   
//湿度，8位的bit，转换为数值
humi=chr[0]*128+chr[1]*64+chr[2]*32+chr[3]*16+chr[4]*8+chr[5]*4+chr[6]*2+chr[7];
   
//温度，8位的bit，转换为数值
temp=chr[16]*128+chr[17]*64+chr[18]*32+chr[19]*16+chr[20]*8+chr[21]*4+chr[22]*2+chr[23];
  //校对码，8位的bit，转换为数值
tol=chr[32]*128+chr[33]*64+chr[34]*32+chr[35]*16+chr[36]*8+chr[37]*4+chr[38]*2+chr[39];
//输出：温度、湿度、校对码
  Serial.print("temp:");
  Serial.println(temp);
  Serial.print("humi:");
  Serial.println(humi);
  Serial.print("tol:");
  Serial.println(tol);
  Serial.println(pinkeyTWO);
//校对码，我这里没用上
//理论上，湿度+温度=校对码
//如果数值不相等，说明读取的数据有错。

  Weight = Get_Weight();  //计算放在传感器上的重物重量
  Serial.print(float((Weight/1000)),3); //串口显示重量
  Serial.print(" kg\n");  //显示单位
  Serial.print("\n");   //显示单位
  
  lcd.setCursor(0,0);     //设置液晶开始显示的指针位置，0列0行，人类理解的第一行
  lcd.print(" Tep : ");
  lcd.print((float)temp,2);
  lcd.print(" C");

  lcd.setCursor(0,1);       //0列，1行，人类理解的第二行
  lcd.print(" Hum : ");
  lcd.print((float)humi,2);
  lcd.print(" %");
  
  delay(1000);        //延时1000ms            
  lcd.setCursor(0,0);
  lcd.print("Weight:");
  lcd.print(float((Weight/1000)),3);
  lcd.print("Kg");
  /*if(pin_data_type){
        lcd.setCursor(0,1);
        lcd.print("Tube: speed /cm");
  }
  else{
    lcd.setCursor(0,1);
    lcd.print("Tube: distance /cm");
  }*/
  if(digitalRead(pinkeyTWO)==HIGH){
    if(digitalRead(pinkeyONE)==HIGH){
      lcd.setCursor(0,1);
      lcd.print("Follow  Model    ");
    }
    else{
      lcd.setCursor(0,1);
      lcd.print("ObstacleAvoidance ");
    }
  }
   else{
    if(digitalRead(pinkeyONE)==HIGH){
      lcd.setCursor(0,1);
      lcd.print("     Track Model  ");
    }
    else{
      lcd.setCursor(0,1);
      lcd.print("BluetoothControl ");
    }
   }
 //  Serial.print(float(pinkeyTWO)"\n"); 
  delay(300);
}
