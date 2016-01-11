#include <Servo.h>
// #include <string> Check if needed

//Communication between BT and Arduino should be <COMMAND>+<SERVO>+<VALUE>
//COMMAND = 4 Char
//VALUE   = the remanaing of the BT strinc
//i.e
//To move to the servo1 one step the command should be MOV11
//To move to the servo2 three steps the command should be MOV23
//To change a the delay to 500 on the servo 1, the command should be PDL1500  (PDL1 for servo1 and 500 for the new value)
//
// List of properties : All should have a prefix P
// Speed            = SP
// Current Position = PO
// Min Position     = MI
// Max Position     = MX
// Delay            = DL

typedef struct  {
   Servo servo_id;
   int s_speed ;
   int current_pos ;
   int minpos ;
   int maxpos ;
   int s_delay ;
} v_servo_t;

v_servo_t v_servos[5];

void initialize_servo(int i_initial_pos, int i_servo_id ) {
  v_servos[i_servo_id].servo_id.writeMicroseconds(i_initial_pos);
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
  delay(v_servos[i_servo_id].s_delay );
}

void set_servo_property(string i_property, string i_value, string i_servo_id) {
// List of properties
// Speed            = SP
// Current Position = PO
// Min Position     = MI
// Max Position     = MX
// Delay            = DL
int v_value = atoi(i_value.c_str() ) ;
int v_servo_id = atoi(i_servo_id.c_str() )  ;


  if (i_property = 'PSP' ) {
	v_servos[v_servo_id].s_speed = i_value ;
  } ;
  
  if (i_property = 'PPO' ) {
	v_servos[v_servo_id].current_pos = i_value ;
  } ;
  
	if (i_property = 'PMI' ) {
	v_servos[v_servo_id].minpos = i_value ;
  } ;
  
  if (i_property = 'PMX' ) {
	v_servos[v_servo_id].maxpos = i_value; 
  } ;
  
  if (i_property = 'PDL' ) {
	v_servos[v_servo_id].s_delay = i_value; 
  } ;
  
}

void setup() {
  // put your setup code here, to run once:

  v_servos[1].servo_id.attach(3) ;
  v_servos[1].s_speed = 25 ;
  v_servos[1].current_pos = 500 ;
  v_servos[1].minpos = 500 ;
  v_servos[1].maxpos = 1625; 
  v_servos[1].s_delay = 300; 
  
  v_servos[2].servo_id.attach(5) ; 
  v_servos[2].s_speed = 25 ;
  v_servos[2].current_pos = 0 ;
  v_servos[2].minpos = 0 ;
  v_servos[2].maxpos = 2000;
  v_servos[2].s_delay = 300; 


   initialize_servo( v_servos[1].current_pos, 1);
   initialize_servo( v_servos[2].current_pos, 2); 
   Serial.begin(9600);
}



void loop() {
  string v_bt_state ;

  
  if (Serial.available()>0){
      v_bt_state = char(Serial.read() );
	  
	  
	  if (v_bt_state.substr(1,1) = 'P') {
		   set_servo_property(v_bt_state.substr(1,3), v_bt_state.substr(5), v_bt_state.substr(4,1) ) ;
	  };
	  
	  if (v_bt_state.substr(1,4) = 'MOV1')
		  if (v_bt_state == 'MOV11') {
			move_servo(1, 1);
		  };
		  
		  if (v_bt_state == 'MOV1-1') {
			move_servo(-1, 1);
		  };
	  };
	  
	  if (v_bt_state.substr(1,4) = 'MOV2')
		  if (v_bt_state == 'MOV21') {
			move_servo(1, 2);
		  };
		  
		  if (v_bt_state == 'MOV2-1') {
			move_servo(-1, 2);
		  };
	  };
	  
	  //Serial.print(v_bt_state);
	  //Serial.print(v_command);
	  //Serial.print(char(v_servo_id) );
	  //Serial.print(char(v_value) );
	  //Serial.print('------------------');
	  
  };
  

}
