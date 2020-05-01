#include "Base64.h"

void Base64Coder::init()
{
  buf = 0;
  bits = 0;
  pad = 0;
}

void Base64Coder::encode(uint8_t c)
{
  // shift c according to bits in the buffer
  uint16_t tmp = uint16_t(c) << (16 - 8 - bits);
  buf |= tmp;
  bits += 8;
  ++pad %= 3;
}

char Base64Coder::eget()
{
  if (bits < 6)
    return '\0';

  // take next 6 bits and convert
  uint8_t c = (buf >> (16 - 6));
  if      (c < 26)  c += ('A' - 0);
  else if (c < 52)  c += ('a' - 26);
  else if (c < 62)  c += ('0' - 52);
  else if (c == 62) c = '+';
  else c = '/';

  // remove them from the buffer
  buf <<= 6;
  bits -= 6;

  return c;
}

char Base64Coder::finalize()
{
  // get final (up to 6) bits from the buffer
  if (bits)
  {
    bits = 6;
    return eget();
  }
  // pading so that the total number of base64 chars
  // is dividable by 3
  if (pad++ % 3)
  {
    return '=';
  }
  return '\0';
}

bool Base64Coder::decode(char c)
{
  // padding or invalid char?
  if ('=' == c || c  > 'z') return false;
  // else reverse the encoding
  else if (c >= 'a') c -= ('a' - 26);
  else if (c >= 'A') c -= ('A' - 0);
  else if (c >= '0') c -= ('0' - 52);
  else if (c == '+') c = 62;
  else if (c == '/') c = 63;

  // put 6 decoded bits into the buffer
  buf <<= 6;
  buf |= c;
  bits += 6;
  
  // if there are at least 8 bits in the buffer
  // return true (i.e. dget() will return a byte) 
  return bits >= 8;
}

uint8_t Base64Coder::dget()
{
  if (bits < 8)
    return '\0';

  // remove 8 bits from buffer
  uint8_t tmp = buf >> (bits - 8);
  buf &= ((1 << (bits - 8)) - 1);
  bits -= 8;
  return tmp;
}
