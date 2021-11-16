
[![Arduino CI](https://github.com/RobTillaart/RunningAverage/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RunningAverage/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RunningAverage/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RunningAverage/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RunningAverage/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RunningAverage/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RunningAverage.svg?maxAge=3600)](https://github.com/RobTillaart/RunningAverage/releases)


# RunningAverage

Arduino library to calculate the running average by means of a circular buffer.


## Description

The RunningAverage object gives a running average of the last N floating point numbers, 
giving them all equal weight.
This is done by adding new data to an internal circular buffer, removing the oldest and 
replace it by the newest. 
The size of the internal buffer can be set in the constructor.

By keeping track of the **\_sum** the runningAverage can be calculated fast (only 1 division)
at any time. This is done with **getFastAverage()**. 
However the constant adding and subtracting when adding new elements possibly introduces an ever increasing error. 
In tests adding up to 1500000 numbers this error was always small. But that is no proof.
In version 0.2.16 a fix was added that uses the calculation of the sum in **getAverage()** to 
update the internal **\_sum**.


## Interface

### Constructor

- **RunningAverage(uint16_t size)** allocates dynamic memory, one float (4 bytes) per element. 
No default size (yet).
- **~RunningAverage()** destructor to free the memory allocated.


### Basic

- **void clear()** empties internal buffer.
- **void add(float value)** wrapper for **addValue()**
- **void addValue(float value)** adds a new value to the object, if internal buffer is full, the oldest element is removed.
- **void fillValue(float value, uint16_t number)**  adds number elements of value. Good for initializing the system to z certain starting average.
- **float getValue(uint16_t position)** returns element at **position**. [expailn better]
- **float getAverage()** iterates over all elements to get the average, slower but accurate
- **float getFastAverage()** reuses previous calculated values, therefore faster. Accuracy can drift.


### Extended functions

- **float getStandardDeviation()** returns the standard deviation of the current content. 
Needs more than one element to be calculable.
- **float getStandardError()** returns the standard error of the current content.
- **float getMin()** returns minimum since last clear, does not need to be in the buffer any more.
- **float getMax()** returns maximum since last clear, does not need to be in the buffer any more.
- **float getMinInBuffer()** returns minimum in the internal buffer.
- **float getMaxInBuffer()** returns maximum in the internal buffer.


### Admin functions

- **bool bufferIsFull()** returns true if buffer is full.
- **float getElement(uint16_t index)** get element directly from internal buffer. (debug)
- **uint16_t getSize()** returns the size of the internal array.
- **uint16_t getCount()** returns the number of slots used of the internal array.


## Partial

- **void setPartial(uint16_t partial = 0)** use only a part of the internal array. 
Allows to change the weight and history factor. 
0 ==> use all == default.
- **uint16_t getPartial()** returns the set value for partial.


## Operation

See examples


## Future 

- add error handling  (important?)
- default size for constructor
- update documentation, explain better.
- create a double based derived class? Template class?

- check for optimizations.
- clear(bool zero = true)  to suppress setting all to 0. ??
-  

