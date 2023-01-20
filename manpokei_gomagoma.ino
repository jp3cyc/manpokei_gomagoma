#include <Servo.h>  // https://github.com/RoboticsBrno/ServoESP32 が必要。標準ライブラリのservo.hではだめ。

Servo myservo; 

#define ON 1
#define OFF 0

#define AD_PIN 25



int step_min = 1; // 最低1以上
int step_max = 20; // サーボステップの上限。

int start = 10;   // サーボが右端に倒れた角度.10
int end = 160;    // サーボが左端に倒れたときの角度.160

int delay_time = 10;    // サーボの駆動時間。多分もっと必要。ステップ数が大きくなると増えるはず。
int interval  = 50;

int step = 1;   // サーボの駆動ステップ



int state = 0;
int now_angle = 0;

int count =0;

void setup() {
  Serial.begin(115200);
  myservo.attach(33); 
  myservo.write(0);
  delay(1000);
  pinMode(13,OUTPUT);
}

void loop() {


  step = map(analogRead(AD_PIN),4095,0,step_min,step_max); // ADC は0~4095
  // start = map(step, step_min, step_max, start, 80);
  // end = map(step, step_min, step_max, 110, end);
  // interval = map(step, step_min, step_max, 200, 50);


  if(state == 0){ 
    // サーボが左回転時の処理
    myservo.write(now_angle);
    now_angle += step;
 
    if(now_angle>end){
      state =1;
      delay(interval);
      LED(OFF);
    }
  }else{
    // サーボが右回転時の処理
    myservo.write(now_angle);
    now_angle -= step;

    if(now_angle<start){
      state = 0;
      delay(interval);
      LED(ON);

      // 10000回ごとに30分休憩する。（サーボ発熱対策）
      count ++;
      if(count > 10000){
        delay(30*60*1000);
        count = 0;
      }

    }
  }
   
  delay(delay_time);

}


void LED(int _led){
  digitalWrite(13,_led);
}