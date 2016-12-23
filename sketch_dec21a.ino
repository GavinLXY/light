#include <Servo.h>
Servo myservo;
#include <Adafruit_NeoPixel.h> /*引用”Adafruit_NeoPixel.h”文件。引用的意思有点象“复制-粘贴”。include文件提供了一种很方便的方式共享了很多程序共有的信息。*/
#define PIN 8                       /*定义了控制LED的引脚，6表示Microduino的D6引脚，可通过Hub转接出来，用户可以更改 */
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
 //该函数第一个参数控制串联灯的个数，第二个是控制用哪个pin脚输出，第三个显示颜色和变化闪烁频率

#define Light_PIN A0  //光照传感器接AO引脚
#define buzzer_pin 6
#define SERVOPIN SDA

#define Light_value1 400
#define Light_value2 800


int sensorValue;

int pos = 0;

void setup()                                //创建无返回值函数
 {
  Serial.begin(115200);               //初始化串口通信，并将波特率设置为115200
  strip.begin();                             //准备对灯珠进行数据发送
  strip.show();                              //初始化所有的灯珠为关的状态

 
  myservo.attach(SERVOPIN);


}
void loop()                                  //无返回值loop函数
 {
  sensorValue = analogRead(Light_PIN);             //光检测
  Serial.println(sensorValue);                                
 if (sensorValue >= Light_value1 && sensorValue < Light_value2)
  //若光强大于400小于600
  {
    for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  {
  strip.setPixelColor(0, strip.Color(0, 0, 0));//灭
  strip.show();  //LED显示
  delay(1000);  //延迟1秒输出
  }
 
  }
  else if(sensorValue < Light_value1)                          //若光强小于400
 {
  strip.setPixelColor(0, strip.Color(255, 0, 0));//红光
  strip.show();   //LED显示
  delay(1000);  //延迟1秒输出
 }
 else if (sensorValue>=Light_value2)
 
  {
  tone(buzzer_pin, 300);
  delay(1000);
  noTone(buzzer_pin);//tone（)产生的声音在此结束
  }
 }
