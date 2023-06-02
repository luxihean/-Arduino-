#include <PS2X_lib.h>


#define PS2_DAT        13  //14    
#define PS2_CMD        12  //15
#define PS2_SEL        11  //16
#define PS2_CLK        10  //17

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x;

//说明：线连接好后，ps2手柄，前车往前移动，后-车往后移动....

int error = 0;
byte type = 0;
byte vibrate = 0;

void (* resetFunc) (void) = 0;
// 电机控制引脚；
#define IN1 9
#define IN2 2
#define IN3 3
#define IN4 4
#define IN5 5
#define IN6 6
#define IN7 7
#define IN8 8

void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);

  Serial.begin(115200);
  delay(300) ;


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
  if (error == 1)
    return;

  if (type == 2) {

    ps2x.read_gamepad();          //read controller

    if (ps2x.ButtonPressed(GREEN_FRET))
      Serial.println("Green Fret Pressed");
    if (ps2x.ButtonPressed(RED_FRET))
      Serial.println("Red Fret Pressed");
    if (ps2x.ButtonPressed(YELLOW_FRET))
      Serial.println("Yellow Fret Pressed");
    if (ps2x.ButtonPressed(BLUE_FRET))
      Serial.println("Blue Fret Pressed");
    if (ps2x.ButtonPressed(ORANGE_FRET))
      Serial.println("Orange Fret Pressed");


    if (ps2x.ButtonPressed(STAR_POWER))
      Serial.println("Star Power Command");

    if (ps2x.Button(UP_STRUM))         //will be TRUE as long as button is pressed
      Serial.println("Up Strum");
    if (ps2x.Button(DOWN_STRUM))
      Serial.println("DOWN Strum");


    if (ps2x.Button(PSB_START))                  //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if (ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");
    if (ps2x.Button(PSB_L1))
      Serial.println("L1 is being held");
    if (ps2x.Button(PSB_R1))
      Serial.println("R1 is being held");     

    if (ps2x.Button(ORANGE_FRET)) // print stick value IF TRUE
    {
      Serial.print("Wammy Bar Position:");
      Serial.println(ps2x.Analog(WHAMMY_BAR), DEC);
    }
  }

  else { //DualShock Controller

    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed

    if (ps2x.Button(PSB_START)){                  //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    }else if (ps2x.Button(PSB_SELECT)){
      Serial.println("Select is being held");
    }else if (ps2x.Button(PSB_PAD_RIGHT)) {        // 右
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      Serial.print("---------右转 ");
       digitalWrite(IN1, HIGH);
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
       digitalWrite(IN5, LOW);
       digitalWrite(IN6, HIGH);
       digitalWrite(IN7, LOW);
       digitalWrite(IN8, HIGH);
    }else if (ps2x.Button(PSB_PAD_UP)) {   // 前
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      Serial.print("---------前进 ");
       digitalWrite(IN1, HIGH);
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
       digitalWrite(IN5, LOW);
       digitalWrite(IN6, HIGH);
       digitalWrite(IN7, HIGH);
       digitalWrite(IN8, LOW);     
    }else if (ps2x.Button(PSB_PAD_DOWN)) {   // 后
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      Serial.print("---------后退 ");
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
       digitalWrite(IN5, HIGH);
       digitalWrite(IN6, LOW);
       digitalWrite(IN7, LOW);
       digitalWrite(IN8, HIGH);   
    }else if (ps2x.Button(PSB_PAD_LEFT)) {  // 后
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      Serial.print("---------左转 ");
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
       digitalWrite(IN5, HIGH);
       digitalWrite(IN6, LOW);
       digitalWrite(IN7, HIGH);
       digitalWrite(IN8, LOW);
    }else if (ps2x.Button(PSB_L1)) {//左平移 
      Serial.print("Left pan held this hard: ");
      Serial.print("---------左平移 ");
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
       digitalWrite(IN5, LOW);
       digitalWrite(IN6, HIGH);
       digitalWrite(IN7, LOW);
       digitalWrite(IN8, HIGH);
    }else if (ps2x.Button(PSB_R1)) {//左平移 
      Serial.print("Right pan held this hard: ");
      Serial.print("---------右平移 ");
       digitalWrite(IN1, HIGH);
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
       digitalWrite(IN5, HIGH);
       digitalWrite(IN6, LOW);
       digitalWrite(IN7, HIGH);
       digitalWrite(IN8, LOW);
     }else if (ps2x.Button(PSB_PAD_RIGHT)) {// 右前45°
      if(ps2x.Button(PSB_PAD_UP)){
      Serial.print("Right-UP held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT&&PSB_PAD_UP), DEC);
      Serial.print("---------右前45°");
       digitalWrite(IN1, HIGH);
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
       digitalWrite(IN5, LOW);
       digitalWrite(IN6, LOW);
       digitalWrite(IN7, LOW);
       digitalWrite(IN8, HIGH);
      }
     }else if (ps2x.Button(PSB_PAD_RIGHT)) {// 右后45°
      if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("Right-DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT&&PSB_PAD_DOWN), DEC);
      Serial.print("---------右后45°");
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
       digitalWrite(IN5, LOW);
       digitalWrite(IN6, HIGH);
       digitalWrite(IN7, LOW);
       digitalWrite(IN8, LOW);
      }
     }else if (ps2x.Button(PSB_PAD_LEFT)) {// 左前45°
      if(ps2x.Button(PSB_PAD_UP)){
      Serial.print("Left-UP held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT&&PSB_PAD_UP), DEC);
      Serial.print("---------左前45°");
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
       digitalWrite(IN5, HIGH);
       digitalWrite(IN6, LOW);
       digitalWrite(IN7, LOW);
       digitalWrite(IN8, LOW);
      }
     }else if (ps2x.Button(PSB_PAD_LEFT)) {// 左后45°
      if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("Left-DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT&&PSB_PAD_DOWN), DEC);
      Serial.print("---------左后45°");
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
       digitalWrite(IN5, LOW);
       digitalWrite(IN6, LOW);
       digitalWrite(IN7, HIGH);
       digitalWrite(IN8, LOW);
      }          
    }else if(ps2x.Button(PSB_SELECT)){   // SELECT
      digitalWrite(IN1, LOW);  //停
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      digitalWrite(IN5, LOW);
      digitalWrite(IN6, LOW);
      digitalWrite(IN7, LOW);
      digitalWrite(IN8, LOW);     
    }else{   // 没有任何操作，停止电机转动
      digitalWrite(IN1, LOW);  //停
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      digitalWrite(IN5, LOW);
      digitalWrite(IN6, LOW);
      digitalWrite(IN7, LOW);
      digitalWrite(IN8, LOW);   
    }

    vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on
    //how hard you press the blue (X) button

    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
      if (ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if (ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
      if (ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if (ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
      if (ps2x.Button(PSB_GREEN))
        Serial.println("Triangle pressed");
    }

    if (ps2x.ButtonPressed(PSB_RED))            //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");

    if (ps2x.ButtonReleased(PSB_PINK))            //will be TRUE if button was JUST released
      Serial.println("Square just released");

    if (ps2x.NewButtonState(PSB_BLUE))           //will be TRUE if button was JUST pressed OR released
      Serial.println("X just changed");


    if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC);
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC);
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC);
    }

  }

  delay(50);

}
