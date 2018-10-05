          /////////////////////////////////////////////////////
          ////          등산스틱 아두이노 소스             ////
          /////////////////////////////////////////////////////          ///////////
          ////          D3231(RTC)                         ////         //////////
          ////          ISD1820(녹음음성모듈)              ////        /////////
          ////          monochrome oled                    ////       ////////
          ////          GPS모듈                            ////     ////////
          /////////////////////////////////////////////////////    ///////
          ////  D0, D1 : BLE                               ////   //////
          ////  D2 -> GPS모듈.RX                           ////  //////
          ////  D3 -> GPS모듈.TX                           //// //////
          ////  D4 : 버튼1 : 소리ON                        //////////
          ////  D5 : 버튼2 : GPS, 문자 전송                /////////
          ////  D6 -> 녹음음성모듈.사운드 녹음             ////////
          ////  D7 -> 녹음음성모듈.사운드 재생             ///////
          ////  D8 -> 확인용 LED(임시)                     //////
          ////  D9 -> DATA                                 ////
          ////  D10 -> CLK                                 ////
          ////  D11 -> DC                                  ////
          ////  D12 -> CS                                  ////
          ////  D13 -> RST                                 ////
          ////  RTC(3.3v) SDA, SDL핀 사용                  ////
          /////////////////////////////////////////////////////

// GPS용
#include <SoftwareSerial.h>
#include <TinyGPS.h>
// GPS모듈 핀 정의
#define RXPIN 2
#define TXPIN 3
// GPS통신속도9600 동
#define GPSBAUD 9600
TinyGPS gps;
SoftwareSerial uart_gps(RXPIN, TXPIN);
// GPS데이터 가져오는 메서드
void getgps(TinyGPS &gps);
// RTC
#include <DS3231.h>
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
  uart_gps.begin(GPSBAUD);
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
    // GPS값을 READ
      int c = uart_gps.read();    // load the data into a variable...
      if(gps.encode(c))      // if there is a new valid sentence...
      {
        getgps(gps);         // then grab the data.
      }
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

void getgps(TinyGPS &gps)
{
  float latitude, longitude;
  gps.f_get_position(&latitude, &longitude);
  Serial.print("Lat/Long: "); 
  Serial.print(latitude,5); 
  Serial.print(", "); 
  Serial.println(longitude,5);
  int year;
  byte month, day, hour, minute, second, hundredths;
  gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
  Serial.print("Date: "); Serial.print(month, DEC); Serial.print("/"); 
  Serial.print(day, DEC); Serial.print("/"); Serial.print(year);
  Serial.print("  Time: "); Serial.print(hour, DEC); Serial.print(":"); 
  Serial.print(minute, DEC); Serial.print(":"); Serial.print(second, DEC); 
  Serial.print("."); Serial.println(hundredths, DEC);
  Serial.print("Altitude (meters): "); Serial.println(gps.f_altitude());  
  Serial.print("Course (degrees): "); Serial.println(gps.f_course()); 
  Serial.print("Speed(kmph): "); Serial.println(gps.f_speed_kmph());
  Serial.println();
  unsigned long chars;
  unsigned short sentences, failed_checksum;
  gps.stats(&chars, &sentences, &failed_checksum); 
  writegps(latitude, longitude); 
  delay(3000);  
}



