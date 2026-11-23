#include <RTClib.h>
#include <TM1637Display.h>

// 引脚定义
#define CLK 10
#define DIO 9

TM1637Display display(CLK, DIO);
RTC_DS1307 rtc;

// 组号，改成你自己的
int groupNum = 12;

void setup() {
  Serial.begin(9600);
  display.setBrightness(0x0f); // 亮度 0~15

  if (!rtc.begin()) {
    Serial.println("找不到RTC模块！");
    while (1);
  }

  // 下面这行只在第一次设置时间的时候打开，设置完注释掉！
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now = rtc.now();
  int minute = now.minute();

  // 串口输出组号
  Serial.print("组号：");
  Serial.println(groupNum);

  // TM1637显示：组号:分钟 （带冒号）
  display.showNumberDecEx(groupNum * 100 + minute, 0b01000000, true, 4);

  delay(1000);
}
