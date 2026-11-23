#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
}

void loop() {
  delay(2000);  // DHT11 建议至少间隔 2s 读取
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("读取传感器失败！");
    return;
  }

  // 【要求】串口先输出组号
  Serial.print("第12组：");
  Serial.print("温度：");
  Serial.print(t);
  Serial.print(" ℃，湿度：");
  Serial.print(h);
  Serial.println(" %");

  // 温度映射闪烁间隔：15℃→间隔1000ms（慢），35℃→间隔100ms（快）
  int blinkDelay = constrain(map(t, 15, 35, 1000, 100), 100, 1000);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkDelay);
  digitalWrite(LED_BUILTIN, LOW);
  delay(blinkDelay);
}
