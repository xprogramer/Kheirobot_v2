#include "Kheirobot_v2.h"


/** 
   Constructor.
 */
Kheirobot_v2::Kheirobot_v2()
{
    // attach the right leg's servos with the corresponding pins
    s_right_1_.servo.attach(R1_PIN);
    s_right_2_.servo.attach(R2_PIN);
    s_right_3_.servo.attach(R3_PIN);
    s_right_4_.servo.attach(R4_PIN);
    // attach the right leg's servos with the corresponding pins
    s_left_1_.servo.attach(L1_PIN);
    s_left_2_.servo.attach(L2_PIN);
    s_left_3_.servo.attach(L3_PIN);
    s_left_4_.servo.attach(L4_PIN);
    
    pinMode(LED, OUTPUT); // configure the LED indicator as output
    _state = 0;
    _delay = _SERVO_DELAY;
    initialize(); // initialize the servos' positions
}


/** 
   function to initialize the servos' initial positions.
 */
void Kheirobot_v2::initialize()
{
    // initialize the initial angles of the right servo
    s_right_1_.curr_pos = s_right_1_.init_pos = 85;
    s_right_2_.curr_pos = s_right_2_.init_pos = 170;
    s_right_3_.curr_pos = s_right_3_.init_pos = 125;
    s_right_4_.curr_pos = s_right_4_.init_pos = 95;
    // initialize the initial angles of the left servo
    s_left_1_.curr_pos = s_left_1_.init_pos = 85;
    s_left_2_.curr_pos = s_left_2_.init_pos = 25;
    s_left_3_.curr_pos = s_left_3_.init_pos = 66;
    s_left_4_.curr_pos = s_left_4_.init_pos = 100;
    
    s_right_1_.servo.write(s_right_1_.init_pos);
    s_left_1_.servo.write(s_left_1_.init_pos);
    s_right_2_.servo.write(s_right_2_.init_pos);
    s_left_2_.servo.write(s_left_2_.init_pos);
    s_right_3_.servo.write(s_right_3_.init_pos);
    s_left_3_.servo.write(s_left_3_.init_pos);
    s_right_4_.servo.write(s_right_4_.init_pos);
    s_left_4_.servo.write(s_left_4_.init_pos);  
    _state = 0;
}


/** 
   function to do a first step of walking forward.
 */
void Kheirobot_v2::first_step_forward()
{
    move_servos(s_right_1_, s_left_1_, 20, _delay);//delay(10);
    move_servos(s_right_4_, s_left_4_, -20, _delay);//delay(10);
    move_servos(s_right_4_, -10, _delay);//delay(10);
    move_servos(s_right_1_, -5, _delay);//delay(10);
    move_servos(s_left_2_, s_left_3_, 30, _delay);//delay(10);
    move_servos(s_right_4_, 10, _delay);//delay(10);
    move_servos(s_right_1_, 5, _delay);//delay(10);
    move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, -20, _delay);//delay(10);
    _state = 1;
}


/** 
   function to walk forward by doing a right step.
 */
void Kheirobot_v2::forward_right()
{
    move_servos(s_right_1_, s_left_1_, -10, _delay);//delay(20);
    move_servos(s_right_4_, s_left_4_, 10, _delay);//delay(10); 
    move_servos(s_left_4_, 10, _delay);//delay(10);
    move_servos(s_right_2_, s_right_3_, -30, _delay);//delay(10);
    move_servos(s_left_4_, 5, _delay);//delay(10);
    move_servos(s_left_2_, s_left_3_, -30, _delay);//delay(10);
    
    move_servos(s_right_1_, s_left_1_, 10, _delay);//delay(20);
    move_servos(s_right_4_, s_left_4_, -10, _delay);//delay(10);
    move_servos(s_left_4_, -15, _delay);//delay(10);  
    _state = 2;
}


/** 
   function to walk forward by doing a left step.
 */
void Kheirobot_v2::forward_left()
{
    move_servos(s_right_1_, s_left_1_, 20, _delay);//delay(10);
    move_servos(s_right_4_, s_left_4_, -20, _delay);//delay(10);
    move_servos(s_right_4_, -5, _delay);
    move_servos(s_left_2_, s_left_3_, 30, _delay);//delay(10);
    move_servos(s_right_4_, -5, _delay);
    move_servos(s_right_2_, s_right_3_, 30, _delay);//delay(10);
    move_servos(s_right_4_, 10, _delay);//delay(10);
    move_servos(s_right_1_, s_left_1_, -20, _delay);//delay(20);
    move_servos(s_right_4_, s_left_4_, 20, _delay);//delay(10); 
    _state = 3;
}


/** 
   function to walk backward by doing a right step.
 */
void Kheirobot_v2::backward_right()
{
    move_servos(s_right_1_, s_left_1_, -10, _delay);//delay(20);
    move_servos(s_right_4_, s_left_4_, 10, _delay);//delay(10); 
    move_servos(s_left_4_, 10, _delay);//delay(10);
    move_servos(s_right_2_, s_right_3_, 30, _delay);//delay(10);
    move_servos(s_left_4_, 5, _delay);//delay(10);
    move_servos(s_left_2_, s_left_3_, 30, _delay);//delay(10);
    move_servos(s_right_1_, s_left_1_, 10, _delay);//delay(20);
    move_servos(s_right_4_, s_left_4_, -10, _delay);//delay(10);
    move_servos(s_left_4_, -15, _delay);//delay(10);
    _state = 3;
}


/** 
   function to walk backward by doing a left step.
 */
void Kheirobot_v2::backward_left()
{
    move_servos(s_right_1_, s_left_1_, 20, _delay);//delay(20);
    move_servos(s_right_4_, s_left_4_, -20, _delay);//delay(10);
    move_servos(s_right_4_, -10, _delay);//delay(10);
    move_servos(s_left_2_, s_left_3_, -30, _delay);//delay(10);
    move_servos(s_right_2_, s_right_3_, -30, _delay);//delay(10);
    move_servos(s_right_4_, 10, _delay);//delay(10);
    move_servos(s_right_4_, s_left_4_, 20, _delay);//delay(10);
    move_servos(s_right_1_, s_left_1_, -20, _delay);//delay(20);
    _state = 2;
}


/** 
   function to return to idle from walking state.
 */
void Kheirobot_v2::idle_from_right()
{
    if(_state == 2) {
      move_servos(s_right_1_, s_left_1_, 10, _delay);delay(10);
      move_servos(s_right_2_, s_right_3_, 40, _delay);delay(10);
      move_servos(s_right_1_, s_left_1_, -10, _delay);delay(10);
      move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, 20, _delay);delay(10);  
      
      _state = 0;
    }
}


/** 
   function to return to idle from walking state.
 */
void Kheirobot_v2::idle_from_left()
{
    if(_state == 3 || _state == 1) {
      move_servos(s_right_1_, s_left_1_, -10, _delay);delay(10);
      move_servos(s_left_2_, s_left_3_, -40, _delay);delay(10);
      move_servos(s_left_2_, 5, _delay);delay(10);
      move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, -20, _delay);delay(10);
      _state = 0;
    }
}


/** 
   function to lift front the right leg.
 */
void Kheirobot_v2::lift_front_right()
{
    idle_from_right();
    idle_from_left();
    
    if(_state == 0) {
      move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, -20, _delay);delay(10);
      move_servos(s_right_1_, s_left_1_, 20, _delay);delay(10);
      move_servos(s_left_4_, 5, _delay);delay(10);
      move_servos(s_left_2_, -30, _delay);delay(10);
      move_servos(s_right_2_, -90, _delay);delay(50);
      move_servos(s_right_2_, -60, _delay);delay(50);
      _state = 4;
    }
}


/** 
   function to return to idle from frontal lifting of the right leg.
 */
void Kheirobot_v2::down_front_right()
{
    if(_state == 4) {
      move_servos(s_right_2_, -60, _delay);delay(50);
      move_servos(s_right_2_, -90, _delay);delay(50);
      move_servos(s_left_2_, -30, _delay);delay(10);
      move_servos(s_left_4_, 5, _delay);delay(10);
      move_servos(s_right_1_, s_left_1_, 20, _delay);delay(10);
      move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, 20, _delay);delay(10);
      _state = 0;
    }
}


/** 
   function to lift front the left leg.
 */
void Kheirobot_v2::lift_front_left()
{
    idle_from_right();
    idle_from_left();
    
    if(_state == 0) {
      move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, 20, _delay);delay(10);
      move_servos(s_right_4_, s_left_4_, -10, _delay);delay(10);
      move_servos(s_right_2_, 10, _delay);delay(10);
      move_servos(s_right_3_, -10, _delay);delay(10);
      move_servos(s_left_2_, 90, _delay);
      move_servos(s_left_2_, 60, _delay);  
      _state = 6;
    }
}


/** 
   function to return to idle from frontal lifting of the left leg.
 */        
void Kheirobot_v2::down_front_left()
{
    if(_state == 6) {
      move_servos(s_left_2_, -90, 7);delay(10);
      move_servos(s_left_2_, -60, 7);delay(10);
      move_servos(s_right_3_, 10, _delay);delay(10);
      move_servos(s_right_2_, -10, 7);delay(10);
      move_servos(s_right_4_, s_left_4_, 10, _delay);delay(10);
      move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, -20, _delay);
      _state = 0;
    }
}


/** 
   function to lift back the right leg.
 */
void Kheirobot_v2::lift_back_right()
{
    idle_from_right();
    idle_from_left();
    
    if(_state == 0) {
      move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, -20, _delay);delay(10);
      move_servos(s_right_1_, s_left_1_, 20, _delay);delay(10);
      move_servos(s_left_2_, 120, _delay);delay(10);
      move_servos(s_right_2_, 10, _delay);
      _state = 5;
    }
}


/** 
   function to return to idle from back lifting of the right leg.
 */    
void Kheirobot_v2::down_back_right()
{
    if(_state == 5) {
      move_servos(s_right_2_, -10, _delay);delay(10);
      move_servos(s_left_2_, -120, _delay);delay(10);
      move_servos(s_right_1_, s_left_1_, -20, _delay);delay(10);
      move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, 20, _delay);
      _state = 0;
    }
}


/** 
   function to lift back the left leg.
 */
void Kheirobot_v2::lift_back_left()
{
    idle_from_right();
    idle_from_left();
    
    if(_state == 0) {
      move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, 20, _delay);delay(10);
      move_servos(s_right_4_, s_left_4_, -10, _delay);delay(10);
      move_servos(s_right_1_, s_left_1_, -20, _delay);delay(10);
      move_servos(s_right_2_, -120, _delay);delay(10);
      move_servos(s_left_2_, -10, _delay);
      _state = 7;
    }
}


/** 
   function to return to idle from back lifting of the left leg.
 */   
void Kheirobot_v2::down_back_left()
{
    if(_state == 7) {
      move_servos(s_left_2_, 10, _delay);delay(10);
      move_servos(s_right_2_, 120, _delay);delay(10);
      move_servos(s_right_1_, s_left_1_, 20, _delay);delay(10);
      move_servos(s_right_4_, s_left_4_, 10, _delay);delay(10);
      move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, -20, _delay);
      _state = 0;
    }
}


/** 
   function to shoot something with the right leg from idle state.
 */   
void Kheirobot_v2::shoot_right()
{
    move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, -20, _delay);delay(10);
    move_servos(s_right_1_, s_left_1_, 20, _delay);delay(10);
    move_servos(s_right_2_, 10, 3);
    delay(500);
    move_servos(s_right_2_, -60, 1);
    delay(500);
    move_servos(s_right_2_, 50, 3);
    move_servos(s_right_1_, s_left_1_, -20, _delay);
    move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, 20, _delay);
}


/** 
   function to shoot something with the left leg from idle state.
 */ 
void Kheirobot_v2::shoot_left()
{
    move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, 25, _delay);delay(10);
    move_servos(s_right_4_, s_left_4_, -5, _delay);
    move_servos(s_right_1_, s_left_1_, -20, _delay);delay(10);
    move_servos(s_left_2_, -10, 3);
    delay(500);
    move_servos(s_left_2_, 60, 2);
    delay(500);
    move_servos(s_left_2_, -50, 3);
    move_servos(s_right_1_, s_left_1_, 20, _delay);
    move_servos(s_right_4_, s_left_4_, 5, _delay);
    move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, -25, _delay);
}


/** 
   function to shoot something with the right leg from the walking state.
 */ 
void Kheirobot_v2::shoot_right_walk()
{
    move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, -15, _delay);delay(10);
    move_servos(s_right_1_, s_left_1_, -15, _delay);delay(10);
    move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, -10, _delay);delay(10);
    move_servos(s_right_4_, s_left_4_, 10, _delay);delay(10);
    move_servos(s_right_4_, 20, _delay);delay(10);
    move_servos(s_left_2_, s_left_3_, -40, 1);delay(10);
    move_servos(s_right_1_, s_left_1_, 20, _delay);delay(10);
    move_servos(s_right_2_, 10, 3);
    delay(500);
    move_servos(s_right_2_, -60, 1);
    delay(500);
    move_servos(s_right_2_, 50, 3);
    move_servos(s_right_1_, s_left_1_, -10, _delay);
    move_servos(s_right_4_, s_left_4_, -20, _delay);

    _state = 0;
}


/** 
   function to shoot something with the left leg from the walking state.
 */ 
void Kheirobot_v2::shoot_left_walk()
{
    move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, 20, _delay);delay(10);
    move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, 30, _delay);delay(10);
    move_servos(s_right_4_, s_left_4_, -5, _delay);
    move_servos(s_right_1_, s_left_1_, -20, _delay);delay(10);
    move_servos(s_right_2_, s_right_3_, 30, 1);delay(10);
    move_servos(s_left_2_, -10, 3);
    delay(500);
    move_servos(s_left_2_, 60, 1);
    delay(500);
    move_servos(s_left_2_, -50, 3);
    move_servos(s_right_1_, s_left_1_, 20, _delay);
    move_servos(s_right_4_, s_left_4_, 5, _delay);
    move_servos_reverse(s_right_1_, s_left_1_, s_right_4_, s_left_4_, -30, _delay);

    _state = 0;
}


/** 
   function to split the robot.
 */ 
void Kheirobot_v2::split()
{
    if(_state == 0) {
        move_servos_reverse(s_left_1_, s_right_4_, s_right_1_, s_left_4_, 70, _delay);
        _state = 8;
    }
    else if(_state == 8) {
        move_servos_reverse(s_left_1_, s_right_4_, s_right_1_, s_left_4_, -70, _delay);
        _state = 0;
    }
}


/** 
   function to bend the robot.
 */ 
void Kheirobot_v2::bend()
{
    if(_state == 0) {
        move_servos_reverse(s_left_2_, s_left_5_, s_right_2_, s_left_5_, 100, _delay);
        _state = 9;
    }
    else if(_state == 9) {
        move_servos_reverse(s_left_2_, s_left_5_, s_right_2_, s_left_5_, -100, _delay);
        _state = 0;
    }
}

