//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2020-12-03
// PURPOSE: unit tests for runningAverage
//          https://github.com/RobTillaart/RunningAverage
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)

#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "RunningAverage.h"


unittest_setup()
{
}

unittest_teardown()
{
}

unittest(test_zero_elements)
{
  RunningAverage myRA(10);
  myRA.clear();

  int size = myRA.getSize();
  assertEqual(10, size);

  int cnt = myRA.getCount();
  assertEqual(0, cnt);

  float x = myRA.getAverage();
  assertEqual(0, x);
}

unittest(test_min_max)
{
  RunningAverage myRA(10);
  myRA.clear();

  for (int i = -5; i < 6; i++)
  {
    myRA.addValue(i);
  }

  float mi = myRA.getMin();
  assertEqual(-5, mi);
  float ma = myRA.getMax();
  assertEqual(5, ma);

  mi = myRA.getMinInBuffer();
  assertEqual(-4, mi);
  ma = myRA.getMaxInBuffer();
  assertEqual(5, ma);
}

unittest(test_buffer_full)
{
  RunningAverage myRA(10);
  myRA.clear();
  assertFalse(myRA.bufferIsFull());

  for (int i = 0; i < 9; i++)
  {
    myRA.addValue(i);
    assertFalse(myRA.bufferIsFull());
  }

  myRA.addValue(42);
  assertTrue(myRA.bufferIsFull());
}


unittest_main()

// --------
