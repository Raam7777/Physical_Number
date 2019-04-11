#include <iostream>
#include <sstream>
#include "Unit.h"
#include "PhysicalNumber.h"

using namespace std;
using namespace ariel;

PhysicalNumber::PhysicalNumber(double _value, Unit _unit)
{
  value = _value;
  unit = _unit;
}

PhysicalNumber::PhysicalNumber(const PhysicalNumber& other)
{
  value = other.value;
  unit = other.unit;
}

PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& other) const
{
  if(this->unit/3 != other.unit/3)
  {
    throw "diffrent unit";
  }
  double v = unit_value[unit]*(this->value/double(unit_value[this->unit]) + other.value/double(unit_value[other.unit]));
  return PhysicalNumber(v, this->unit);
}

PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& other) const
{
  if(this->unit/3 != other.unit/3)
  {
    throw "diffrent unit";
  }
  double v = unit_value[unit]*(this->value/double(unit_value[this->unit]) - other.value/double(unit_value[other.unit]));
  return PhysicalNumber(v, this->unit);
}

PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& other)
{
  if(this->unit/3 != other.unit/3)
  {
    throw "diffrent unit";
  }
  double v = unit_value[unit]*(this->value/double(unit_value[this->unit]) + other.value/double(unit_value[other.unit]));
  this->value = v;
  return *this;
}

PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& other)
{
  if(this->unit/3 != other.unit/3)
  {
    throw "diffrent unit";
  }
  double v = unit_value[unit]*(this->value/double(unit_value[this->unit]) - other.value/double(unit_value[other.unit]));
  this->value = v;
  return *this;
}


const PhysicalNumber PhysicalNumber::operator+() const
{
  return PhysicalNumber(this->value, this->unit);
}

const PhysicalNumber PhysicalNumber::operator-() const
{
  return PhysicalNumber(-(this->value), this->unit);
}


bool ariel::operator==(const PhysicalNumber& left, const PhysicalNumber& right)
{
  if(left.unit/3 != right.unit/3)
  {
    throw "diffrent unit";
  }
  double v = unit_value[right.unit]*(left.value/double(unit_value[left.unit]));
  return v == right.value;
}

bool ariel::operator<=(const PhysicalNumber& left, const PhysicalNumber& right)
{
  if(left.unit/3 != right.unit/3)
  {
    throw "diffrent unit";
  }
  double v = unit_value[right.unit]*(left.value/double(unit_value[left.unit]));
  return v <= right.value;
}

bool ariel::operator>=(const PhysicalNumber& left, const PhysicalNumber& right)
{
  if(left.unit/3 != right.unit/3)
  {
    throw "diffrent unit";
  }
  double v = unit_value[right.unit]*(left.value/double(unit_value[left.unit]));
  return v >= right.value;
}

bool ariel::operator<(const PhysicalNumber& left, const PhysicalNumber& right)
{
  if(left.unit/3 != right.unit/3)
  {
    throw "diffrent unit";
  }
  double v = unit_value[right.unit]*(left.value/double(unit_value[left.unit]));
  return v < right.value;
}

bool ariel::operator>(const PhysicalNumber& left, const PhysicalNumber& right)
{
  if(left.unit/3 != right.unit/3)
  {
    throw "diffrent unit";
  }
  double v = unit_value[right.unit]*(left.value/double(unit_value[left.unit]));
  return v > right.value;
}

bool ariel::operator!=(const PhysicalNumber& left, const PhysicalNumber& right)
{
  return !(left == right);
}


PhysicalNumber& PhysicalNumber::operator++()
{
  ++this->value;
  return (*this);
}

PhysicalNumber& PhysicalNumber::operator--()
{
  --this->value;
  return (*this);
}

const PhysicalNumber PhysicalNumber::operator++(int _value){
  PhysicalNumber temp = *this;
  ++this->value;
  return temp;
}
const PhysicalNumber PhysicalNumber::operator--(int _value){
  PhysicalNumber temp = *this;
  ++this->value;
  return temp;
}

ostream& ariel::operator<<(ostream& stream, const PhysicalNumber& other)
{
  return stream << other.value << "[" << unit_name[other.unit] << "]";
}


istream& ariel::operator>>(istream& stream, PhysicalNumber& other)
{
  string _value, _unit, is;
  stream>>is;
  _value = is.substr(0, is.find("["));
  other.value = stod(_value);
  _unit = is.substr(is.find("[")+1, is.length() - is.find("[")-2);
  for(int i=0; i<9; i++) {
    if(unit_name[i] == _unit) {
      other.unit = (Unit)i;
    }
  }

  return stream;
}
