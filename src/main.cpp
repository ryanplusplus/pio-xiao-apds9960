#include <Arduino.h>
#include <Adafruit_APDS9960.h>

extern "C" {
#include <stddef.h>
#include "tiny_timer.h"
#include "tiny_time_source.h"
#include "tiny_heartbeat.h"
}

static tiny_timer_group_t timer_group;
static Adafruit_APDS9960 sensor;

void setup()
{
  Serial.begin(9600);

  sensor.begin();
  sensor.enableProximity(true);
  sensor.enableGesture(true);

  tiny_timer_group_init(&timer_group, tiny_time_source_init());
  tiny_heartbeat_init(&timer_group, 1000);
}

void loop()
{
  tiny_timer_group_run(&timer_group);

  switch(sensor.readGesture()) {
    case APDS9960_DOWN:
      Serial.println("v");
      break;

    case APDS9960_UP:
      Serial.println("^");
      break;

    case APDS9960_LEFT:
      Serial.println("<");
      break;

    case APDS9960_RIGHT:
      Serial.println(">");
      break;
  }
}
