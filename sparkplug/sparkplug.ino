#include "configs/default/config.h"
#include "src/spark.h"

void setup()
{
  Serial.begin(9600);
  delay(250);
  Serial.flush();

  sparkInitialize();
}

void loop() {
  sparkUpdate(); }
