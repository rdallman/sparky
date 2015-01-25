// This #include statement was automatically added by the Spark IDE.
#include "SparkTime/SparkTime.h"
#include "SparkButton/SparkButton.h"


SparkButton b = SparkButton();
UDP UDPClient;
SparkTime rtc;

unsigned long currentTime;
uint8_t last_hour, last_minute;
static const uint8_t SPARKY_OFFSET = 6;

void setup() {
  b.begin();
  rtc.begin(&UDPClient, "north-america.pool.ntp.org");
  rtc.setTimeZone(-8); // gmt offset
}

void loop() {
  // TODO only sync these things every day or something, not every minute
  currentTime = rtc.now();
  uint8_t hour = (rtc.hour(currentTime)+SPARKY_OFFSET) % 12;
  if (hour != last_hour) {
    b.ledOff(last_hour);
    last_hour = hour;
  }

  uint8_t minute = ((rtc.minute(currentTime)/5) + SPARKY_OFFSET) % 12; // 5 minute ranges
  if (minute != last_minute) {
    b.ledOff(last_minute);
    last_minute = minute;
  }

  // TODO diff color for hour == minute?
  b.ledOn(hour, 1, 12, 25);
  b.ledOn(minute, 28, 9, 1);

  delay(60 * 1000); // sleep a minute
}
