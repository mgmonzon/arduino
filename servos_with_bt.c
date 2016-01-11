#include <Servo.h>

Servo myServo1;
Servo myServo2;
Servo myServo3;

typedef struct  {
   Servo servo_id;
   int s_speed ;
   int current_pos ;
   int minpos ;
   int maxpos ;
} v_servo_t;

v_servo_t v_servos[5];

void initialize_servo(int i_initial_pos, int i_servo_id ) {
  v_servos[i_servo_id].servo_id.writeMicroseconds(i_initial_pos);
}


void setup() {
  // put your setup code here, to run once:

  v_servos[1].servo_id.attach(3) ;
  v_servos[1].s_speed = 25 ;
  v_servos[1].current_pos = 500 ;
  v_servos[1].minpos = 500 ;
  v_servos[1].maxpos = 1625; 
  
  v_servos[2].servo_id.attach(5) ; 
  v_servos[2].s_speed = 25 ;
  v_servos[2].current_pos = 0 ;
  v_servos[2].minpos = 0 ;
  v_servos[2].maxpos = 2000;


initialize_servo( v_servos[1].current_pos, 1);
initialize_servo( v_servos[2].current_pos, 2); 
   Serial.begin(9600);
}


void move_servo (int i_steps , int i_servo_id ){
  int v_new_position ;
  
  
  v_new_position = v_servos[i_servo_id].current_pos + ( i_steps * v_servos[i_servo_id].s_speed ) ;

  if (v_new_position > v_servos[i_servo_id].maxpos) {
    v_new_position = v_servos[i_servo_id].maxpos ;
  }

  if (v_new_position < v_servos[i_servo_id].minpos) {
    v_new_position = v_servos[i_servo_id].minpos ;
  }

  v_servos[i_servo_id].current_pos = v_new_position;
  v_servos[i_servo_id].servo_id.writeMicroseconds(v_new_position);
  delay(300);
}

void loop() {
  int v_bt_state ;
  if (Serial.available()>0){
      v_bt_state = Serial.read();
      if (v_bt_state == 'a') {
        move_servo(10, 1);
        Serial.print(v_bt_state );
        Serial.print("-1-");
      };
      if (v_bt_state == 'd') {
        move_servo(-10, 1);
        Serial.print(v_bt_state);
        Serial.print("-2-");
      };
      if (v_bt_state == 'l') {
        move_servo(10, 2);
        Serial.print(v_bt_state);
        Serial.print("-3-");
      };
      if (v_bt_state == 'r') {
        move_servo(-10, 2);
        Serial.print(v_bt_state);
        Serial.print("-4-");
      };
      //v_bt_state = 0 ;
  };
  
  //for (int x=1 ; x<15 ; x++ ) {
  //  move_servo(1, 1);
  //}

  //delay(5000);

  //for (int x=1 ; x<15 ; x++ ) {
  //  move_servo(-1, 1);
  //}
 
}
