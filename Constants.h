#ifndef _CONSTANTS_H
#define _CONSTANTS_H

//game speed
const int FPS = 60; //frame rate
const float MOVE_SPEED = -3.6f; //screen view move speed

//camera
const float MOVE_OUT_OFF_SCREEN = -12; //speed to move player back on screen from +y
const int MAX_TOP_PIXELS = 450; //keep players within screen top
const int MAX_BOTTOM_PIXELS = 350; //keep players within screen bottom
const int MAX_RIGHT_PIXELS = 425; //keep players within screen right
const int MAX_LEFT_PIXELS = 480; //keep players within screen left

//tiles
const int LEVEL_HEIGHT = 2000; //map dim height
const int LEVEL_WIDTH = 25; //map dim width

//starting location
const float VIEW_START_LOCATION = LEVEL_HEIGHT * 48 - 500; //starting location for camera view
const float PLAYER_START_LOCATION = VIEW_START_LOCATION + 500; //starting location for players

//sounds
const int GUN_SOUND_RATE = 90; //milliseconds
const int HIT_SOUND_RATE = 80; //milliseconds

//enemies
const int MAX_ON_SCREEN_ENEMIES = 10; //max enemies
const float ENEMY_X_VEL = 1.5; //x velocity movement speed
const float ENEMY_Y_VEL = 1.0; //y velocity movement speed
const int ENEMY_CREATE_RATE_EASY = 2; //seconds
const float ENEMY_CREATE_RATE_HARD = 1.6f; //seconds
const int MIG51S_HEALTH = 150; //hit points
const int SU37K_HEALTH = 30; //hit points
const int MIG51_HEALTH = 40; //hit points
const int MIG51S_SCORE = 50; //score points
const int SU37K_SCORE = 10; //score points
const int MIG51_SCORE = 20; //score points

//weapons
const int ENEMY_BULLET_VEL = 5; //pixel velocity
const int ENEMY_FIRE_RATE = 1000; //milliseconds

//boss
const int BOSS1_HEALTH = 2000; //starting health for boss
const int BOSS2_HEALTH = 3000; //starting health for boss
const int BOSS1_HEALTH_HARD = 4000; //starting health for boss
const int BOSS2_HEALTH_HARD = 6000; //starting health for boss
const int BOSS_FIRE_RATE = 6000; //milliseconds
const int BOSS_FIRE_RATE_HARD = 4000; //milliseconds
const int TOTAL_BULLETS_FIRED = 32; //bullets

//player
const int PLAYER_X_VEL = 8; //x velocity movement speed
const int PLAYER_Y_VEL = 8; //y velocity movement speed
const int PLAYER_STARTING_LIVES = 5;
const int PLAYER_HEALTH = 100; //hit points
const int INVINCIBILITY_TIME = 5; //seconds
const int INCREASE_LIVES_SCORE = 1000; //points

//weapons
const int HOMING_GUN_BULLETS = 800; //total bullets for homing gun
const int DUAL_GUN_BULLETS = 300; //total bullets for dual gun
const int HOMING_GUN_DAMAGE = 5;
const int DUAL_GUN_DAMAGE = 15;
const int MACHINE_GUN_DAMAGE = 10;
const int MISSILE_DAMAGE = 100;
const int ENEMY_GUN_DAMAGE = 25;
const int FIRE_RATE = 50; //milliseconds
const int BULLET_VEL = -20; //pixel velocity
const int MISSILE_FIRE_RATE = 5; //seconds
const int MISSILE_VEL = -25; //pixel velocity
const int SMOKE_FRAME_RATE = 70; //milliseconds
const int STARTING_MISSILES = 3;

//items
const int HEAL_ITEM = 50; //hit points

//misc
const int FONT_SIZE = 25; //ttf font size

//particles
const int PARTICLE_LIFETIME = 300; //milliseconds
const unsigned int PARTICLES_SMALL_EXPLOSION = 400; //total particles
const unsigned int PARTICLES_MEDIUM_EXPLOSION = 2500; //total particles
const unsigned int PARTICLES_BIG_EXPLOSION = 5000; //total particles

//controls
enum joyStickAxix{joyUp = -100, joyDown = 100, joyRight = 100, joyLeft = -100}; //joystick axis directions
enum joyStick{A = 6, B = 8, Z = 7, Start = 9}; //joystick buttons

#endif