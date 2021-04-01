/**
 * @file BooleanLogic.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __BOOLEANLOGIC__H__
#define __BOOLEANLOGIC__H__

#include <Arduino.h>

class ResetSet
{
private:
    bool aux;
public:
    bool out(bool set, bool reset){
        if(set) aux = true;
        if(reset) aux = false;
        return aux;
    }
};

class SetReset
{
private:
    bool aux;
public:
    bool out(bool set, bool reset){
        if(reset) aux = false;
        if(set) aux = true;
        return aux;
    }
};

class TimerPulse
{
private:
    unsigned long prevMillis;
    bool aux;
public:
    bool out(int time){
        if(prevMillis == 0){
            prevMillis = millis();
            aux = 0;
        }
        if(millis() - prevMillis >= time){
            aux = true;
            prevMillis = 0;
        }
        return aux;
    }
};

class Task
{
private:
    TimerPulse taskTimer;
public:
    void out(int time, void (*task)()){
        if(taskTimer.out(time)){
            task();
        }
    }
};

#endif  //!__BOOLEANLOGIC__H__