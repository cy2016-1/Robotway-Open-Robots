#ifndef _GAIT_H_
#define _GAIT_H_

#include <Arduino.h>
#include <math.h>

struct gaitParam {
    float x_origin;
    float y_origin;
    float amp;
    float half_cycle;
    float period;
    float flight_percent;
};

gaitParam forwardGait = {
    .x_origin = -0.05,
    .y_origin = 0.14,
    .amp = -0.02,
    .half_cycle = 0.1,
    .period = 700,
    .flight_percent = 0.6
};

gaitParam forwardGait2 = {
    .x_origin = -0.02,
    .y_origin = 0.14,
    .amp = -0.02,
    .half_cycle = 0.04,
    .period = 700,
    .flight_percent = 0.6};

gaitParam backwardGait = {
    .x_origin = 0.05,
    .y_origin = 0.14,
    .amp = -0.02,
    .half_cycle = -0.1,
    .period = 700,
    .flight_percent = 0.6
};

gaitParam backwardGait2 = {
    .x_origin = 0.02,
    .y_origin = 0.14,
    .amp = -0.02,
    .half_cycle = -0.04,
    .period = 700,
    .flight_percent = 0.6};

gaitParam stepGait = {
    .x_origin = 0,
    .y_origin = 0.14,
    .amp = -0.02,
    .half_cycle = 0.001,
    .period = 700,
    .flight_percent = 0.6
};

void gait(float millis, float offset, float &x, float &y, gaitParam param = backwardGait)
{
    offset = fmod(offset, 1.0);
    float phase = fmod(millis/param.period + offset, 1.0);
    if (phase < param.flight_percent) {
        float dx = param.half_cycle * phase / param.flight_percent;
        float dy = param.amp * sin(M_PI / param.half_cycle * dx);
        x = param.x_origin + dx;
        y = param.y_origin + dy;
    } else {
        x = param.x_origin + param.half_cycle * (1 - phase) / (1 - param.flight_percent);
        y = param.y_origin;
    }
}

#endif
