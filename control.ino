#include <BlinkTask.h>
#include <Debouncer.h>
#include <DelayRun.h>
#include <Dimmer.h>
#include <FrequencyTask.h>
#include <Heartbeat.h>
#include <Rotary.h>
#include <SoftPwmTask.h>
#include <SoftTimer.h>
#include <Task.h>
#include <TonePlayer.h>

#define RED 8
#define GREEN 9
#define BLUE 10

void set_color(int r, int g, int b);

void input(Task *t);
void cycle(Task *t);

Task t_input(1, input);
Task t_cycle(200, cycle);

String cmd;
String argv[3];
int cycling = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  SoftTimer.add(&t_input);
  SoftTimer.add(&t_cycle);
}

void input(Task *t){
  if (Serial.available())
  {
    cmd = Serial.readStringUntil(' ');
    argv[0] = Serial.readStringUntil(' ');
    argv[1] = Serial.readStringUntil(' ');
    argv[2] = Serial.readStringUntil(' ');

    cycling = 0;
    if(cmd == "sc")
      set_color(argv[0].toInt(), argv[1].toInt(), argv[2].toInt());
    else if(cmd == "tf")
      set_color(0, 0, 0);
    else if(cmd == "cycle")
      cycling = 1;
    
    //Serial.println("ARGUMENTS: " + String(argv[0].toInt()) + " " + String(argv[1].toInt()) + " " + String(argv[2].toInt()));
  }
}

void set_color(int r, int g, int b)
{
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}

void cycle(Task *t){
  if(cycling){
    set_color(random(0,255), random(0,255), random(0,255));
  }
}

