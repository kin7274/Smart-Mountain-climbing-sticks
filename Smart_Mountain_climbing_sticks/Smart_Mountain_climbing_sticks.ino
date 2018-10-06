          /////////////////////////////////////////////////////
          ////          등산스틱 아두이노 소스             ////
          /////////////////////////////////////////////////////         ///////////
          ////          D3231(RTC)                         ////        //////////
          ////          ISD1820(녹음음성모듈)              ////       /////////
          ////          monochrome oled                    ////      ////////
          ////          GPS모듈                            ////    ////////
          /////////////////////////////////////////////////////   ///////
          ////  D2 -> GPS모듈.RX                           ////  //////
          ////  D3 -> GPS모듈.TX                           //// //////
          ////  D4 : 버튼1 : 소리ON                        //////////
          ////  D5 : 버튼2 : GPS, 문자 전송                /////////
          ////  D6 -> 녹음음성모듈.사운드 녹음             ////////
          ////  D7 -> 녹음음성모듈.사운드 재생             ///////
          ////  D8 -> 임시 LED                             /////
          ////  D9 -> DATA                                 ////
          ////  D10 -> CLK                                 ////
          ////  D11 -> DC                                  ////
          ////  D12 -> CS                                  ////
          ////  D13 -> RST                                 ////
          ////  RTC(3.3v) SDA, SDL핀 사용                  ////
          /////////////////////////////////////////////////////
// GPS용
#include <SoftwareSerial.h>
// RTC
#include <DS3231.h>
SoftwareSerial GPS(3,2);
DS3231 rtc(SDA, SCL);

// 버튼1 : 소리ON
const int buttonPin = 4;
// 버튼2 : GPS, 문자 전송
const int buttonPin2 = 5;
// 버튼 초기값
int buttonState = 0;
int buttonState2 = 0;

// 녹음모듈 재생핀
const int PLAYE = 6;
// 녹음모듈 녹음핀
// 호랑이울음소리 한번 제대로 넣고 핀 지워도 무방할듯..?
const int REC = 7;

// 데이터 송수신 확인용 LED
const int ledPin =  8;

// 설정
void setup() {
  Serial.begin(9600);
  // GPS통신속도
  GPS.begin(9600);
  // RTC가즈아ㅏ
  rtc.begin();
  pinMode(buttonPin, INPUT); 
  pinMode(buttonPin2, INPUT);  
  pinMode (REC,OUTPUT);
  pinMode (PLAYE,OUTPUT);
  pinMode(ledPin, OUTPUT);
}

// 메인
void loop() {
  // 버튼값 READ
 buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);
  // 버튼1이 HIGH라면
  if(buttonState == HIGH){
    // 소리ON
        Serial.print("SOUND ON");
        digitalWrite(PLAYE,HIGH);
        delay(10);
        digitalWrite(PLAYE,LOW);
        delay(1000);
  } else {
    //
  }
  // 버튼2가 HIGH라면
  if(buttonState2 == HIGH){
      // RTC값 플로팅
    Serial.print("Time:  ");
    Serial.print(rtc.getTimeStr());
    Serial.print("Date: ");
    Serial.print(rtc.getDateStr());
    // LED ON
    Serial.println("LED ON");
    digitalWrite(ledPin, HIGH);
    delay(1000);
  } else {
    // 아니라면 LED OFF
    digitalWrite(ledPin, LOW);
  }
}



