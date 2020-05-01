# Base64Coder
A tiny Base64 encode/decoder library for the Arduino with minimal memory requirements.

## How it works
See [https://en.wikipedia.org/wiki/Base64](Wikipedia on Base64) for details. This library aims to minimize memory consumption by encoding a given message byte by byte.

### Encoding
Encoding a message is done by calling `Base64Coder::encode(uint8_t)` consequently with all bytes of the message. After each call `encode(uint8_t)` you must call `char Base64Coder::eget()` to read the Base64 encoded symbols. Call as often as needed until it returns '\0'. For each byte put into the encoder, `eget()` will return one or two Base64 symbols.
After all message bytes have been encoded, call `char Base64Coder::finalize()` until it returns '\0'. This may yield the last Base64 symbol and will add (up to 2) neccessary padding symbols.

### Decoding
Decoding a string of Base64 symbols is done by calling `bool Base64Coder::decode(char)` consequently with all symbols of the encoded message. `Base64Coder::decode(char)` returns true, if enough symbols have been decoded to produce the next byte of the decoded message.
Call `uint8_t Base64Coder::dget()` to get the next decoded message byte.

## Tutorial
Place the Base64Coder library folder in your `<arduinosketchfolder>/libraries/` folder. You may need to create the libraries subfolder if its your first library. Restart the IDE.

To use it in your code, construct an instace of the coder with
```C++
#include <Base64Coder.h>  
Base64Coder coder;
```

Before encodung or decoding, initialize via `coder.init();`

See `Base64Test.ino` example for more details on how to encode and decode a message. 


