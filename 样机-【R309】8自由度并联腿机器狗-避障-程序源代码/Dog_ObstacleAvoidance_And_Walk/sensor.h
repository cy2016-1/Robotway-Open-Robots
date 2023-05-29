#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <Arduino.h>

#define TRIG_F A5
#define ECHO_F A4
#define TRIG_B 2
#define ECHO_B A3

int sensor_timeout = 2200;

void sensorSetup() {
    pinMode(TRIG_F, OUTPUT);
    pinMode(ECHO_F, INPUT);
    pinMode(TRIG_B, OUTPUT);
    pinMode(ECHO_B, INPUT);
}

float readFront() {
    //给Trig发送一个低高低的短时间脉冲,触发测距
    digitalWrite(TRIG_F, LOW);  //给TRIG_F发送一个低电平
    delayMicroseconds(2);     //等待 2微妙
    digitalWrite(TRIG_F, HIGH); //给TRIG_F发送一个高电平
    delayMicroseconds(10);    //等待 10微妙
    digitalWrite(TRIG_F, LOW);  //给TRIG_F发送一个低电平

    return float(pulseIn(ECHO_F, HIGH, sensor_timeout)); //返回回波等待时间,
}

float readBack()
{
    //给Trig发送一个低高低的短时间脉冲,触发测距
    digitalWrite(TRIG_B, LOW);  //给TRIG_B发送一个低电平
    delayMicroseconds(2);     //等待 2微妙
    digitalWrite(TRIG_B, HIGH); //给TRIG_B发送一个高电平
    delayMicroseconds(10);    //等待 10微妙
    digitalWrite(TRIG_B, LOW);  //给TRIG_B发送一个低电平

    return float(pulseIn(ECHO_B, HIGH, sensor_timeout)); //返回回波等待时间,
}

#endif
