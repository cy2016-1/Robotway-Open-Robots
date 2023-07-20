void motor_pin_init(){
  for( int i=0;i<motor_pin_count;i++){
    pinMode(motor_pin[i],OUTPUT);
    delay(2);
    digitalWrite( motor_pin[i], LOW );
    delay(2);
  }
}

void Motor_Acceleration_Move(int _mode, int _input_acc){
  //Serial.println( MOTOR_SPEEDS / (Motor_ACCELERATION*100) );
  switch( _mode ){
    case 1: 
          for( int i=0; i<=MOTOR_SPEEDS; i++){
            motor_speed(0,i);
            motor_speed(2,i);
            motor_speed(4,i);
            motor_speed(6,i);
            //Serial.println( MOTOR_SPEEDS / (Motor_ACCELERATION*100) )
            delay( MOTOR_SPEEDS / (Motor_ACCELERATION*100)  );
          }
          //Serial.println("end");
          break;
    case 2: 
          for( int i=0; i<=MOTOR_SPEEDS; i++){
            motor_speed(1,i);
            motor_speed(3,i);
            motor_speed(5,i);
            motor_speed(7,i);
            //Serial.println( MOTOR_SPEEDS / (Motor_ACCELERATION*100) )
            delay( MOTOR_SPEEDS / (Motor_ACCELERATION*100)  );
          }
          //Serial.println("end");
          break; 
    case 3: 
          for( int i=0; i<=MOTOR_SPEEDS; i++){
            motor_speed(0,i);
            motor_speed(3,i);
            motor_speed(5,i);
            motor_speed(6,i);
            //Serial.println( MOTOR_SPEEDS / (Motor_ACCELERATION*100) )
            delay( MOTOR_SPEEDS / (Motor_ACCELERATION*100)  );
          }
          //Serial.println("end");
          break; 
    case 4: 
          for( int i=0; i<=MOTOR_SPEEDS; i++){
            motor_speed(1,i);
            motor_speed(2,i);
            motor_speed(4,i);
            motor_speed(7,i);
            //Serial.println( MOTOR_SPEEDS / (Motor_ACCELERATION*100) )
            delay( MOTOR_SPEEDS / (Motor_ACCELERATION*100)  );
          }
          //Serial.println("end");
          break;
    default: break;            
  }
}

void Motor_Go(int _input_mode){
  switch(_input_mode)
  {
    case FORWARD:
                //Motor_Acceleration_Move(1,Motor_ACCELERATION);
                motor_speed(1,MOTOR_SPEEDS);motor_speed(0,0);
                motor_speed(2,MOTOR_SPEEDS);motor_speed(3,0);
                motor_speed(4,MOTOR_SPEEDS);motor_speed(5,0);
                motor_speed(7,MOTOR_SPEEDS);motor_speed(6,0);
                break;
    case BACK:
                //Motor_Acceleration_Move(2,Motor_ACCELERATION);
                motor_speed(0,MOTOR_SPEEDS);motor_speed(1,0);
                motor_speed(3,MOTOR_SPEEDS);motor_speed(2,0);
                motor_speed(5,MOTOR_SPEEDS);motor_speed(4,0);
                motor_speed(6,MOTOR_SPEEDS);motor_speed(7,0);               
                break;
    case TURN_LEFT:
                motor_speed(0,MOTOR_SPEEDS);motor_speed(1,0);
                motor_speed(2,MOTOR_SPEEDS);motor_speed(3,0);
                motor_speed(5,MOTOR_SPEEDS);motor_speed(4,0);
                motor_speed(7,MOTOR_SPEEDS);motor_speed(6,0);
                break;
    case TURN_RIGHT:
                motor_speed(1,MOTOR_SPEEDS);motor_speed(0,0);
                motor_speed(3,MOTOR_SPEEDS);motor_speed(2,0);
                motor_speed(4,MOTOR_SPEEDS);motor_speed(5,0);
                motor_speed(6,MOTOR_SPEEDS);motor_speed(7,0);
                break;
    case LEFT_TRANSLATION:
                //Motor_Acceleration_Move(3,Motor_ACCELERATION);
                motor_speed(0,MOTOR_SPEEDS);motor_speed(1,0);
                motor_speed(2,MOTOR_SPEEDS);motor_speed(3,0);
                motor_speed(4,MOTOR_SPEEDS);motor_speed(5,0);
                motor_speed(6,MOTOR_SPEEDS);motor_speed(7,0);
                break;
    case RIGHT_TRANSLATION:
                //Motor_Acceleration_Move(4,Motor_ACCELERATION);
                motor_speed(1,MOTOR_SPEEDS);motor_speed(0,0);
                motor_speed(3,MOTOR_SPEEDS);motor_speed(2,0);
                motor_speed(5,MOTOR_SPEEDS);motor_speed(4,0);
                motor_speed(7,MOTOR_SPEEDS);motor_speed(6,0);
                break;
    case STOP:
                motor_speed(1,0);motor_speed(0,0);
                motor_speed(2,0);motor_speed(3,0);
                motor_speed(4,0);motor_speed(5,0);
                motor_speed(6,0);motor_speed(7,0);
                break;
    default: break;            
  }
}



//void Motor_Go(int _input_mode){
//  switch(_input_mode)
//  {
//    case FORWARD:
//                //Motor_Acceleration_Move(1,Motor_ACCELERATION);
//                motor_speed(0,MOTOR_SPEEDS);motor_speed(1,0);
//                motor_speed(2,MOTOR_SPEEDS);motor_speed(3,0);
//                motor_speed(4,MOTOR_SPEEDS);motor_speed(5,0);
//                motor_speed(6,MOTOR_SPEEDS);motor_speed(7,0);
//                break;
//    case BACK:
//                //Motor_Acceleration_Move(2,Motor_ACCELERATION);
//                motor_speed(1,MOTOR_SPEEDS);motor_speed(0,0);
//                motor_speed(3,MOTOR_SPEEDS);motor_speed(2,0);
//                motor_speed(5,MOTOR_SPEEDS);motor_speed(4,0);
//                motor_speed(7,MOTOR_SPEEDS);motor_speed(6,0);                
//                break;
//    case TURN_LEFT:
//                motor_speed(0,MOTOR_SPEEDS);motor_speed(1,0);
//                motor_speed(2,MOTOR_SPEEDS);motor_speed(3,0);
//                motor_speed(5,MOTOR_SPEEDS);motor_speed(4,0);
//                motor_speed(7,MOTOR_SPEEDS);motor_speed(6,0);
//                break;
//    case TURN_RIGHT:
//                motor_speed(1,MOTOR_SPEEDS);motor_speed(0,0);
//                motor_speed(3,MOTOR_SPEEDS);motor_speed(2,0);
//                motor_speed(4,MOTOR_SPEEDS);motor_speed(5,0);
//                motor_speed(6,MOTOR_SPEEDS);motor_speed(7,0);
//                break;
//    case LEFT_TRANSLATION:
//                //Motor_Acceleration_Move(3,Motor_ACCELERATION);
//                motor_speed(0,MOTOR_SPEEDS);motor_speed(1,0);
//                motor_speed(3,MOTOR_SPEEDS);motor_speed(2,0);
//                motor_speed(5,MOTOR_SPEEDS);motor_speed(4,0);
//                motor_speed(6,MOTOR_SPEEDS);motor_speed(7,0);
//                break;
//    case RIGHT_TRANSLATION:
//                //Motor_Acceleration_Move(4,Motor_ACCELERATION);
//                motor_speed(1,MOTOR_SPEEDS);motor_speed(0,0);
//                motor_speed(2,MOTOR_SPEEDS);motor_speed(3,0);
//                motor_speed(4,MOTOR_SPEEDS);motor_speed(5,0);
//                motor_speed(7,MOTOR_SPEEDS);motor_speed(6,0);
//                break;
//    case STOP:
//                motor_speed(1,0);motor_speed(0,0);
//                motor_speed(2,0);motor_speed(3,0);
//                motor_speed(4,0);motor_speed(5,0);
//                motor_speed(6,0);motor_speed(7,0);
//                break;
//    default: break;            
//  }
//}

void motor_speed(int _input_pin, int _input_speed){
  analogWrite(motor_pin[_input_pin],_input_speed);
}
