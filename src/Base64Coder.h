#include <stdint.h>

class Base64Coder {
  uint16_t buf;  // holds bits to be converted from/to base64
  uint8_t bits;  // number of bits in the buffer
  uint8_t pad;   // number of padding bytes
public:
  Base64Coder() = default;
  void init();

  void encode(uint8_t c);
  char eget();
  char finalize();

  bool decode(char c);
  uint8_t dget();
};
