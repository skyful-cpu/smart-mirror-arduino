#include <SoftwareSerial.h>

// hc06 모듈의 RX / TX가 연결된 핀
unsigned const int rx_pin = 2;
unsigned const int tx_pin = 3;

// IoT 관련 변수
char* iot[] = {"light", "boiler", "fan"}; // IoT 종류
int iot_pin[] = {8, 9, 10, 11, 12, 13}; // IoT가 연결된 핀
// int switch_pin[] = {11, 12, 13}; // 스위치가 연결된 핀
int iot_init_state[] = {1, 1, 1, 1, 1, 1}; // (임시) IoT 초기 상태
int iot_len = sizeof(iot_pin) / sizeof(int); // IoT 개수

// hc06 모듈 객체 생성
SoftwareSerial hc06(rx_pin, tx_pin);

// IoT 제어 커맨드 함수
void ControlIot(int cmd);

void setup() {
  // IoT 초기 설정
  for (int i = 0; i < iot_len; i++) {
    pinMode(iot_pin[i], iot_init_state[i]);
    digitalWrite(iot_pin[i], iot_init_state[i]);
  }

  // Serial / hc06 설정
  Serial.begin(9600);
  hc06.begin(9600);
}

void loop() {
  // Flask -> Arduino IoT 제어 신호 수신
  if (hc06.available()) {
    int cmd = hc06.read();
    delay(100);
    ControlIot(cmd);
  }

  /*
  //220719 추가
  for (int i = 0; i < iot_len; i++) {
    if (digitalRead(switch_pin[i]) == LOW)
      digitalWrite(iot_pin[i], HIGH);
    else
      digitalWrite(iot_pin[i], LOW); 
  }
  */

  //SendInitState();
}

void ControlIot(int cmd) {
  if (cmd == 'i')
    SendInitState();
  else if (cmd == '1') {
    digitalWrite(iot_pin[0], HIGH);
  }
  else if (cmd == '0') {
    digitalWrite(iot_pin[0], LOW);
  }
  else if (cmd == '3') {
    digitalWrite(iot_pin[1], HIGH);
  }
  else if (cmd == '2') {
    digitalWrite(iot_pin[1], LOW);
  }
  else if (cmd == '5') {
    digitalWrite(iot_pin[2], HIGH);
  }
  else if (cmd == '4') {
    digitalWrite(iot_pin[2], LOW);
  }
  else if (cmd == '7') {
    digitalWrite(iot_pin[3], HIGH);
  }
  else if (cmd == '6') {
    digitalWrite(iot_pin[3], LOW);
  }
  else if (cmd == '9') {
    digitalWrite(iot_pin[4], HIGH);
  }
  else if (cmd == '8') {
    digitalWrite(iot_pin[4], LOW);
  }
  else if (cmd == 'v') {
    digitalWrite(iot_pin[5], LOW);
  }
  else {}
}

/* void sendInitState()
웹 페이지 최초 접속 시 Flask로부터 신호를 받아
IoT의 초기 상태를 전송해준다
*/
void SendInitState() {
  for (int i = 0; i < iot_len; i++) {
    if (digitalRead(iot_pin[i]) == 1) {
      hc06.write(" on");
      Serial.println("on");
    }
    else {
      hc06.write(" off");
      Serial.println("off");
    }
    
    delay(100);
  }

  hc06.write("q");
}
