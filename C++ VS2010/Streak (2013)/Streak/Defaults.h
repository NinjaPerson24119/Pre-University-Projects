//Stars
color default_stars_color = color(1.f,1.f,1.f);

//Ship defaults
enum TEAM { GREEN, RED };
enum RECOIL_EFFECT { NONE, RECOIL, RETURNING };

float const default_round = 0.2f;
float const default_ship_size = 20.f;
float const default_ship_recoilspeed = 1.f;
int const default_ship_shot = 14;
int const default_ship_lives = 3;
int const default_ship_maxlives = 7;
int const default_ship_damage = 10;
float const default_laser_coolmod = 20.f; //(SECONDS)
float const default_ship_health = 100;
float const default_ship_lowesthealth = 50;
float const default_laser_speed = 2.f;
float const default_ship_maxbloom = 20;
float const default_ship_ivcb = 2*SCREEN_FPS; //Powerup defaults

//Powerup defaults
enum POWERUP_TYPE { IVCB, DUAL, SPEED, LIFE };

int const default_powerup_chance = 50;
float const default_powerup_bloom = 0.04f;
float const default_powerup_speed = 0.04f;
float const default_powerup_size = default_ship_size/2;
float const default_powerup_thick = 1.f;
float const default_ivcb_cycles = 10*SCREEN_FPS;
color const default_ivcb_color(0.f,0.f,1.f);
float const default_dual_cycles = 10*SCREEN_FPS;
color const default_dual_color(1.f,1.f,0.f);
float const default_speed_multiplier = 1.2f;
float const default_speed_cycles = 10*SCREEN_FPS;
color const default_speed_color(1.f,0.f,1.f);
float const default_life_cycles = 3*SCREEN_FPS;
color const default_life_color = color(0.2f,1.f,0.2f);

//Controller defaults
enum FORMATION { BLOCK, CHECKER, GRID, HORIZONTAL, VERTICAL };

float const default_com_speed = 0.5f;
float const default_spacing = 8.f;
int const default_firechance = 100;
float const default_forward = 0.f;
int const default_difficulty = 0;
int const default_difficultycurve = 5;
int const formation_count = 5;
color const default_wave = color(1.f,1.f,0.f);

//Game handler
float const default_interval_time = 2*SCREEN_FPS;