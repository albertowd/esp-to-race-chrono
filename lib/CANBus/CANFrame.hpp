#ifndef __CAN_FRAME_HPP
#define __CAN_FRAME_HPP

#include <cstdint>

namespace CAN
{
  class Frame
  {
  private:
    char str[27];
    uint32_t id;
    uint8_t data[12];

    Frame() = delete;
    Frame(const Frame &) = delete;
    void updateStr();

  public:
    Frame(const uint32_t id);
    ~Frame();

    uint32_t getId() const;
    void setUint8(const uint8_t value, const uint8_t pos);
    const char *c_str() const;
    const uint8_t *c_data() const;
  };
}

#endif
