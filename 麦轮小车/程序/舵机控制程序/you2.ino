#include <PS2X_lib.h>
#include <Servo.h>  
#define PS2_DAT        13
#define PS2_CMD        12
#define PS2_SEL        11
#define PS2_CLK        10
#define pressures   false
#define rumble      false
PS2X ps2x;
int pinRelay = 3; 
int error = 0;
//int speed = 0;
byte type = 0;
byte vibrate = 0;

void (* resetFunc) (void) = 0;
//以上为手柄配置
Servo myservo;// 定义舵机对象
Servo myservo1;// 定义舵机对象
Servo myservo2;// 定义舵机对象


void setup() {
  pinMode(pinRelay, OUTPUT);
  Serial.begin(115200);
  delay(300);
  myservo.attach(9);// 设置舵机控制针脚接数字9引脚
  myservo1.attach(8);
  myservo2.attach(7);// 设置舵机控制针脚接数字9引脚

  type = ps2x.readType();
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
     error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  if (error == 1)
    return;
 
  if (type == 2) {
    ps2x.read_gamepad();
    if (ps2x.Button(PSB_L1))
      Serial.println("L1 is being held");
    if (ps2x.Button(PSB_R1))
      Serial.println("R1 is being held");     

  }
  else {
    ps2x.read_gamepad(false, vibrate);

    if (ps2x.Button(PSB_TRIANGLE)) {
       Serial.print("left held this hard: ");
       Serial.println(ps2x.Analog(PSB_L1), DEC);
       Serial.print("---------顺时针 ");
       myservo.write(90);
       myservo1.write(90);
       myservo2.write(180);
       
      }
  else if (ps2x.Button(PSB_CIRCLE)) {
       Serial.print("left held this hard: ");
       Serial.println(ps2x.Analog(PSB_R2), DEC);
       Serial.print("---------顺时针 ");
       myservo.write(60);
       myservo1.write(65);
       myservo2.write(65);
       
      }
 
     else if (ps2x.Button(PSB_SQUARE)) {
       Serial.print("right held this hard: ");
       Serial.println(ps2x.Analog(PSB_R1), DEC);
       Serial.print("---------逆时针 ");
       myservo.write(120);
       myservo1.write(120);
       myservo2.write(120);
   
     
     }
  }
}
