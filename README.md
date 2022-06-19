# CEO_project_A

IoT 실습 - 매장 관리 시스템
   
---
### HW
   
   
---
## 로그 기록
   
#### (2022-06-13)
* MG90 Servo Motor 미동작 원인 찾을 필요 있음
   
(참고) Example - ESP8266_MultipleRandomServos   
https://github.com/khoih-prog/ESP8266_ISR_Servo#example-esp8266_multiplerandomservos   
   
   
#### (2022-06-15)
* Servo Motor 동작 성공
* UltraSonic 추가
* Store, Door STATE 동작 추가
* Switch 연결 후 단순 스위치 동작으로 각 STATE 변경
* Servo Motor, Buzzer 동시에 사용 시 동작이 원활하게 되지 않음   
* Buzzer의 tone 사용 후 Servo 동작 불가   
 -> 원인 발견 X   
 
 
* 보드 2개 이용하여 침입자 감지 시그널에 의해 부저가 동작하도록 작성   
**보드 1** : UltraSonic, ServoMotor, Switch   
**보드 2** : Buzzer   
   
   
#### (2022-06-18)
* HW 프레임 제작 완료   
* NodeRed 제작 완료   
* JSON 데이터로 주고 받는 동작 완성   
   
   
