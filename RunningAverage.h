#pragma once
//
//    FILE: RunningAverage.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.6
//    DATE: 2011-01-30
// PURPOSE: Arduino library to calculate the running average by means of a circular buffer
//     URL: https://github.com/RobTillaart/RunningAverage
//
//  The library stores N individual values in a circular buffer,
//  to calculate the running average.


#include "Arduino.h"


#define RUNNINGAVERAGE_LIB_VERSION    (F("0.4.6"))


class RunningAverage
{
public:
  explicit RunningAverage(const uint16_t size);
  ~RunningAverage();

  void     clear();
  void     add(const float value)    { addValue(value); };
  void     addValue(const float value);
  void     fillValue(const float value, const uint16_t number);
  float    getValue(const uint16_t position);

  float    getAverage();            //  iterates over all elements.
  float    getFastAverage() const;  //  reuses previous calculated values.

  //  return statistical characteristics of the running average
  float    getStandardDeviation() const;
  float    getStandardError() const;

  //  returns min/max added to the data-set since last clear
  float    getMin() const { return _min; };
  float    getMax() const { return _max; };

  //  returns min/max from the values in the internal buffer
  float    getMinInBuffer() const;
  float    getMaxInBuffer() const;

  //  return true if buffer is full
  bool     bufferIsFull() const { return _count == _size; };

  float    getElement(uint16_t index) const;

  uint16_t getSize() const { return _size; }
  uint16_t getCount() const { return _count; }

  //  use not all elements just a part from 0..partial-1
  //  (re)setting partial will clear the internal buffer.
  void     setPartial(const uint16_t partial = 0);  // 0 ==> use all
  uint16_t getPartial()   { return _partial; };


  //  get some stats from the last count additions.
  float    getAverageLast(uint16_t count);
  float    getMinInBufferLast(uint16_t count);
  float    getMaxInBufferLast(uint16_t count);

  //       Experimental 0.4.3
  float    getAverageSubset(uint16_t start, uint16_t count);


protected:
  uint16_t _size;
  uint16_t _count;
  uint16_t _index;
  uint16_t _partial;
  float    _sum;
  float*   _array;
  float    _min;
  float    _max;
};


class RA_Weight : public RunningAverage
{
public:
  RA_Weight(const uint16_t size) : RunningAverage(size)
  {
    _weight = (float *) malloc(_size * sizeof(float));
    if (_weight == NULL) _size = 0;
    _sumWeight = 0;
  }


  ~RA_Weight()
  {
    if (_weight) free(_weight);
  }


  void addValue(const float value, const float weight = 1.0)
  {
    if ((_array == NULL) || (_weight == NULL))
    {
      return;
    }
    _sumWeight -= _weight[_index];
    _weight[_index] = weight;
    _sumWeight += _weight[_index];

    _sum -= _array[_index];
    _array[_index] = value;
    _sum += _array[_index];

    _index++;

    if (_index == _partial) _index = 0;  //  faster than %

    //  handle min max
    if (_count == 0) _min = _max = value;
    else if (value < _min) _min = value;
    else if (value > _max) _max = value;

    //  update count as last otherwise if ( _count == 0) above will fail
    if (_count < _partial) _count++;
  }


  //  returns the average of the data-set added so far, NAN if no elements.
  float getAverage()
  {
    if (_count == 0)
    {
      return NAN;
    }
    //  OPTIMIZE local variable for sums.
    _sumValues = 0;
    _sumWeight = 0;
    for (uint16_t i = 0; i < _count; i++)
    {
      _sumValues += _array[i];
      _sumWeight += _weight[i];
    }
    return _sumValues / _sumWeight;   //  multiplication is faster ==> extra admin
  }


  float getFastAverage() const
  {
    if (_count == 0)
    {
      return NAN;
    }
    return _sum / _sumWeight;   //  multiplication is faster ==> extra admin
  }


  //  returns the weight of an element if exist, NAN otherwise
  float getWeight(uint16_t index) const
  {
    if (_count == 0)
    {
      return NAN;
    }
    return _weight[index];
  }


  //  what to support ...
  // void fillValue(const float value, const float weight, const uint16_t number)
  // {
    // clear();
    // uint16_t s = number;
    // if (s > _partial) s = _partial;

    // for (uint16_t i = s; i > 0; i--)
    // {
      // addValue(value, weight);
    // }
  // }



protected:
  float * _weight;
  float   _sumValues;
  float   _sumWeight;
};

//  -- END OF FILE --

