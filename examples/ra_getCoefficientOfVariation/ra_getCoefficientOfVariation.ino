//
//    FILE: ra_getCoefficientOfVariation.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: show working of runningAverage
//     URL: https://github.com/RobTillaart/RunningAverage


#include "RunningAverage.h"


RunningAverage myRA(10);
int samples = 0;

void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);

  myRA.clear();  //   explicitly start clean

  for (int i = 0; i < 10; i++)
  {
    myRA.add(i * 0.01 + 1 );
    Serial.print(myRA.getCount());
    Serial.print("\t");
    Serial.print(myRA.getAverage(), 3);
    Serial.print("\t");
    Serial.print(myRA.getStandardDeviation(), 3);
    Serial.print("\t");
    Serial.print(myRA.getStandardDeviation() / myRA.getAverage(), 3);
    Serial.print("\t");
    Serial.println(myRA.getCoefficientOfVariation(), 3);
  }
  Serial.println();
}


void loop(void)
{
  long rn = random(0, 1000);
  myRA.addValue(rn * 0.1);
  samples++;

  Serial.print(samples);
  Serial.print("\t Running Average: ");
  Serial.print(myRA.getAverage(), 3);
  Serial.print("\t");
  Serial.print(myRA.getStandardDeviation(), 3);
  Serial.print("\t");
  Serial.print(myRA.getStandardDeviation() / myRA.getAverage(), 3);
  Serial.print("\t");
  Serial.println(myRA.getCoefficientOfVariation(), 3);

  if (samples >= 300)
  {
    samples = 0;
    myRA.clear();
    Serial.println();
  }
  delay(10);
}


//  -- END OF FILE --
