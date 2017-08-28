#include "Kheirobot_v2.h"


/** 
   function to rotate a servo with a given angle based on the current 
   position.
   @param servo_t servo: the servo object
   @param short angle: the angle of rotation
   @param byte del: the delay between two angles of rotation
 */
void Kheirobot_v2::move_servos(_servo_t& servo, short angle, byte del)
{
    // if the angle is positive
    if(angle > 0) {
        for(int i = 0; i < angle; i++) {
            servo.servo.write(servo.curr_pos + i);
            delay(del);
        }
    }
    // if the angle is negative
    else {
        for(int i = 0; i > angle; i--) {
            servo.servo.write(servo.curr_pos + i);
            delay(del);
        }
    }

    servo.curr_pos += angle; // add the input angle to the current position

    // not exceed the servo limits 0-180 deg
    if(servo.curr_pos < 0) servo.curr_pos = 0;
    else if (servo.curr_pos > 180) servo.curr_pos = 180;
}



/** 
   function to rotate two servos with the same angle based on their 
   current position.
   @param servo_t servo_1: the first servo object
   @param servo_t servo_2: the second servo object
   @param short angle: the rotation angle of the two servos
   @param byte del: the delay between two angles of rotation
 */
void Kheirobot_v2::move_servos(_servo_t& servo_1, 
                                 _servo_t& servo_2, 
                                 short angle,
                                 byte del)
{        
    // if the angle is positive
    if(angle > 0) {
        for(int i = 0; i < angle; i++) {
            servo_1.servo.write(servo_1.curr_pos + i);
            servo_2.servo.write(servo_2.curr_pos + i);
            delay(del);
        }
    }
    // if the angle is negative
    else {
        for(int i = 0; i > angle; i--) {
            servo_1.servo.write(servo_1.curr_pos + i);
            servo_2.servo.write(servo_2.curr_pos + i);
            delay(del);
        }
    }
    
    servo_1.curr_pos += angle; // add the input angle to servo_1 position
    servo_2.curr_pos += angle; // add the input angle to servo_2 position
    
    // not exceed the servo limits 0-180 deg
    if(servo_1.curr_pos < 0) servo_1.curr_pos = 0;
    else if (servo_1.curr_pos > 180) servo_1.curr_pos = 180;
    
    if(servo_2.curr_pos < 0) servo_2.curr_pos = 0;
    else if (servo_2.curr_pos > 180) servo_2.curr_pos = 180;
}



/** 
   function to rotate two servos (servo_3 and servo_4) in reverse order 
   with two other servos (servo_1 and servo_2).
   @param servo_t servo_1: the 1st servo object
   @param servo_t servo_2: the 2nd servo object
   @param servo_t servo_3: the 3rd servo object
   @param servo_t servo_4: the 4th servo object
   @param short angle: the rotation angle of the two servos
   @param byte del: the delay between two angles of rotation
 */
void Kheirobot_v2::move_servos_reverse(_servo_t& servo_1, 
                                 _servo_t& servo_2, 
                                 _servo_t& servo_3, 
                                 _servo_t& servo_4, 
                                 short angle,
                                 byte del)
{        
    // if the angle is positive
    if(angle > 0) {
        for(int i = 0; i < angle; i++) {
            servo_1.servo.write(servo_1.curr_pos + i);
            servo_3.servo.write(servo_3.curr_pos - i);
            servo_2.servo.write(servo_2.curr_pos + i);
            servo_4.servo.write(servo_4.curr_pos - i);
            delay(del);
        }
    }
    // if the angle is negative
    else {
        for(int i = 0; i > angle; i--) {
            servo_1.servo.write(servo_1.curr_pos + i);
            servo_3.servo.write(servo_3.curr_pos - i);
            servo_2.servo.write(servo_2.curr_pos + i);
            servo_4.servo.write(servo_4.curr_pos - i);
            delay(del);
        }
    }
    
    servo_1.curr_pos += angle; // add the input angle to servo_1 position
    servo_2.curr_pos += angle; // add the input angle to servo_2 position
    servo_3.curr_pos -= angle; // substract the input angle to servo_3 position
    servo_4.curr_pos -= angle; // substract the input angle to servo_4 position
    
    // not exceed the servo limits 0-180 deg
    if(servo_1.curr_pos < 0) servo_1.curr_pos = 0;
    else if (servo_1.curr_pos > 180) servo_1.curr_pos = 180;
    
    if(servo_2.curr_pos < 0) servo_2.curr_pos = 0;
    else if (servo_2.curr_pos > 180) servo_2.curr_pos = 180;

    if(servo_3.curr_pos < 0) servo_3.curr_pos = 0;
    else if (servo_3.curr_pos > 180) servo_3.curr_pos = 180;
    
    if(servo_4.curr_pos < 0) servo_4.curr_pos = 0;
    else if (servo_4.curr_pos > 180) servo_4.curr_pos = 180;
}

