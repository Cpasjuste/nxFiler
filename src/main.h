//
// Created by cpasjuste on 12/04/18.
//

#ifndef NXFILER_MAIN_H
#define NXFILER_MAIN_H

int KEYS[]{
        // UP, DOWN, LEFT, RIGHT, COINS (SELECT), START, ..., // QUIT
        KEY_JOY_UP_DEFAULT, KEY_JOY_DOWN_DEFAULT, KEY_JOY_LEFT_DEFAULT, KEY_JOY_RIGHT_DEFAULT,
        KEY_JOY_COIN1_DEFAULT, KEY_JOY_START1_DEFAULT,
        KEY_JOY_FIRE1_DEFAULT, KEY_JOY_FIRE2_DEFAULT, KEY_JOY_FIRE3_DEFAULT,
        KEY_JOY_FIRE4_DEFAULT, KEY_JOY_FIRE5_DEFAULT, KEY_JOY_FIRE6_DEFAULT,
        0
        // 13, 15, 12, 14, 10, 11, 0, 1, 2, 3, 7, 6, 0 // QUIT
};

#ifdef __SWITCH__
#define SCR_W 1280
#define SCR_H 720
#endif

#endif //NXFILER_MAIN_H