/*
 *
 * This is a simple encode / decode example for the base64 library
 * 2019 Daniel Plasa <dplasa@gmail.com>
 *
 */

#include <Base64Coder.h>

#define MESSAGE "Test message!"
#define CHECK   "VGVzdCBtZXNzYWdlIQ=="
char buf[32];

//  base64 encoder/decoder object
Base64Coder coder;

void setup()
{
  Serial.begin(9600);

  //
  // test base64 encoding
  //
  coder.init();

  Serial.println(F("base64 of " MESSAGE " should be " CHECK));
  Serial.print(F("  "));

  // copy the MESSAGE into buf 
  strncpy_P(buf, MESSAGE, sizeof(buf));
  char* s = &(buf[0]);


  // Encoding a message is done by
  //  * Putting the next message byte into the coder by calling 
  //    b64Coder::encode(byte)
  //  * After that read the encoded base64 symbols by calling 
  //    b64Coder::eget()
  //    until eget() returns char '\0'
  //    For each byte put into the encoder, eget() will return one or two base64 symbols
  //  * After all message bytes have been encoded, call
  //    b64Coder::finalize()
  //    until finalize() returns '\0'
  //    This will yield the last base64 symbol and (up to 2) padding symbols.
  while (*s)
  {
    coder.encode(*s++);
    for (char c; (c = coder.eget()); )
      Serial.print(c);
  }
  for (char c; (c = coder.finalize()); )
    Serial.print(c);

  //
  // test base64 decoding
  //
  coder.init();

  Serial.println(F("base64 " CHECK " should decode to " MESSAGE));
  Serial.print(F("  "));

  strncpy_P(buf, CHECK, sizeof(buf));
  s = &(buf[0]);

  // Decoding a base64 string is done by
  //  * Putting the next base64 symbol into the coder by calling 
  //    b64Coder::decode(char)
  //    decode() will return true, if enough symbols have been put into the coder
  //    so that dget() will return a byte of the message
  //  * If decode(char) returns true, calling b64Coder::dget() returns the next message byte
  while (*s)
  {
    if (coder.decode(*s++))
    {
      uint8_t c = coder.dget();
      Serial.print( c );
    }
  }
  Serial.println();
}

void loop() 
{
}
