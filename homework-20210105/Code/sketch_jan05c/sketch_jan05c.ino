/*
 * HW: 期未報告-使用Arduino UNO 的串列通訊（Arduino IDE 的序列埠監看視窗）來輸入指定的值，來控制LED燈的亮法
 * Code:ZangmenHsu
 * Date:2021/01/05
*/
int LED[]={3,5,6,9}; //正向:用陣列定義LED燈的接腳(共4支腳)
int LED_x[]={9,6,5,3}; //反向:用陣列定義LED燈的接腳(共4支腳)
int array_num;
int intput_num=0; //預定窗口要輸入值

//PWM(0~255)控制(0 ==> 127 ==> 255)
void led_pwm(int kx){
  analogWrite(kx,0); //PWM值=0
    delay(300); //delay 300ms
    analogWrite(kx,127); //PWM值=127
    delay(300); //delay 300ms
    analogWrite(kx,255); //PWM值=255
    delay(300); //delay 300ms
}

//亮指定的LED燈
void led_view(int kv){
  digitalWrite(kv,LOW); //LED燈亮(LOW)
  delay(100); //delay 500ms
  digitalWrite(kv,HIGH); //LED燈暗(HIGH)
  delay(100); //delay 500ms
}

//LED燈全関
void led_clear(int kc){
  digitalWrite(kc,HIGH); //LED燈全関
}

//接腳&開始的設定 
void setup() {
  // put your setup code here, to run once:
  for(array_num =0;array_num<=4;array_num++){
    pinMode(LED[array_num],OUTPUT); //把所有的LED燈全部設輸出
    led_clear(LED[array_num]);//把LED燈全部関掉(HIGH)
  }
  Serial.begin(9600); //串列通訊的鮑率:9600bps
}

//要做的動作
void loop() {
  // put your main code here, to run repeatedly:    
  if(Serial.available()>0){
    intput_num = Serial.read(); //定義從窗口輸入的值
    if(intput_num=='0'){
       Serial.write("Output 0 LED All ON \n");
       //LED燈亮的順序:1,2,3,4
       for ( array_num =0 ; array_num<4 ; array_num++){
          led_view(LED[array_num]);
          delay(300);
       }
       //LED燈亮的順序:4,3,2,1
       for ( array_num =0 ; array_num < 4 ; array_num++){
          led_view(LED_x[array_num]);
          delay(300);
        }
    }else if(intput_num == '1'){
       Serial.write("Output 1 : LED 1 ON \n");
       led_view(LED[0]);
    }else if(intput_num == '2'){
       Serial.write("Output 2 : LED 2 ON\n");
       led_view(LED[1]);
    }else if(intput_num == '3'){
       Serial.write("Output 3 : LED 3 ON\n");
       led_view(LED[2]);
    }else if(intput_num == '4'){
       Serial.write("Output 4 : LED 4 ON\n");
       led_view(LED[3]);
    }else if(intput_num == '5'){
       Serial.write("Output 5 : ALL LED Using PWM Control\n");
       for(array_num =0;array_num < 4;array_num++){
         led_pwm(LED[array_num]);
       }
    }
  } 
}
