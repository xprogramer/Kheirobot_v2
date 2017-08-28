#ifndef _KHEIROBOT_V2_H
#define _KHEIROBOT_V2_H

#include<Arduino.h>
#include<Servo.h>

#define _SERVO_DELAY 8

#define R1_PIN 5
#define R2_PIN 6
#define R3_PIN 7
#define R4_PIN 8

#define L1_PIN 9
#define L2_PIN 10
#define L3_PIN 11
#define L4_PIN 12

#define LED A3


/*
   define a structure representing the servo's state
 */
typedef struct {
    Servo servo; // instance of the Servo object
    byte init_pos; // initial position
    byte curr_pos; // current position
} _servo_t;



/*
   define a class representing the robot
 */
class Kheirobot_v2 {
    public:
        // instances of the right servos
        _servo_t s_right_1_ , 
                 s_right_2_ , 
                 s_right_3_ , 
                 s_right_4_ , 
                 s_right_5_;
        // instances of the left servos
        _servo_t s_left_1_ , 
                 s_left_2_ , 
                 s_left_3_ , 
                 s_left_4_ , 
                 s_left_5_;
        int _delay; // keeps the delay used to rotate the servos
        int _state; // keeps the state of the robot
                    // 0 : idle
                    // 1 : first step (left forward)
                    // 2 : right forward
                    // 3 : left forward
                    // 4 : right leg up (front)
                    // 5 : right leg up (back)
                    // 6 : left leg up (front)
                    // 7 : left leg up (back)
                    // 8 : splits
                    // 9 : bend
    
    public:
        Kheirobot_v2(); // constructor
        ~Kheirobot_v2(){} // destructor
  
        void initialize(); // initialize the servos' angles
        
        void first_step_forward(); // the first step of walking forward
        void forward_right();  // the right step of walking forward
        void forward_left(); // the left step of walking forward
        
        void backward_right();  // the right step of walking backrward
        void backward_left(); // the left step of walking backrward
        
        void idle_from_right(); // return to idel from walking
        void idle_from_left(); // return to idel from walking

        void lift_front_right(); // lift front the right leg 
        void lift_front_left(); // lift front the left leg 

        void down_front_right(); // return to idle from front lifting of the right leg
        void down_front_left(); // return to idle from front lifting of the left leg

        void lift_back_right(); // lift back the right leg 
        void lift_back_left(); // lift back the left leg 

        void down_back_right(); // return to idle from back lifting of the right leg
        void down_back_left(); // return to idle from back lifting of the left leg

        void shoot_right(); // shoot something with the right leg
        void shoot_left(); // shoot something with the left leg

        void shoot_right_walk(); // shoot something with the right leg from the walking state
        void shoot_left_walk(); // shoot something with the left leg from the walking state

        void split(); // split the robot
        void bend(); // bend the robot
        
            
    private:
        // move a servo with a given angle
        void move_servos(_servo_t&, short, byte);
        // move two servos with the same angle
        void move_servos(_servo_t&, _servo_t&, short, byte);
        // move two servos in reverse order of two other servos
        void move_servos_reverse(_servo_t&, _servo_t&, _servo_t&, _servo_t&, short, byte);
};

#endif

