#include <stdio.h>
#include <string.h>

#include "CANFrame.hpp"

CAN::Frame::Frame(const uint32_t id) : id(id) {
  memset(this->data, 0, sizeof(this->data) / sizeof(uint8_t));
  memset(this->str, '\0', sizeof(this->str) / sizeof(char));
  data[0] = id & 0xFF;
  data[1] = (id >> 8) & 0xFF;
  data[2] = (id >> 16) & 0xFF;
  data[3] = (id >> 24) & 0xFF;
  this->updateStr();
}

CAN::Frame::~Frame() {
  memset(this->data, 0, sizeof(this->data) / sizeof(uint8_t));
  memset(this->str, '\0', sizeof(this->str) / sizeof(char));
}

void CAN::Frame::setUint8(const uint8_t value, const uint8_t pos) {
  this->data[pos + 4] = value;
  this->updateStr();
}

const char * CAN::Frame::c_str() const {
  return this->str;
}

uint32_t CAN::Frame::getId() const {
  return this->id;
}

const uint8_t * CAN::Frame::c_data() const {
  return this->data;
}

void CAN::Frame::updateStr() {
  sprintf(this->str, "0x%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", this->data[0], this->data[1], this->data[2], this->data[3], this->data[4], this->data[5], this->data[6], this->data[7], this->data[8], this->data[9], this->data[10], this->data[11]);
}
