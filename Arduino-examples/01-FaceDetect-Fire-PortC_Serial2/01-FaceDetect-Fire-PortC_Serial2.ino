
/*
  MIT License

  Copyright (c) 2020 M5Stack

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  V-Function Face Detect example for Arduino:
    <V1.0>  2020-09-07 IAMLIUBO First release base on M5Stack Fire.
*/
#include <M5Stack.h>
#include <Arduino_JSON.h>

// If you want detect more face you should change the array size :)
char result_buf[256] = "";

void setup() {

  M5.begin();

  // Print the result.
  Serial.begin(115200);

  // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
}

void loop() {

  if (Serial2.available() > 0) {
    int recv_len = Serial2.readBytesUntil('\r', result_buf, 256);
    // We need flush the "\r\n\r\n..." bytes
    // Our protocol add some "\r\n"　chartacter at the end of the result.
    Serial2.flush();

    // Serial.print("Face Detect result: ");
    // Serial.println(result_buf);

    JSONVar face_detect_obj = JSON.parse(result_buf);

    // JSON.typeof(jsonVar) can be used to get the type of the var
    if (JSON.typeof(face_detect_obj) == "undefined") {
      Serial.println("Parsing face detect result failed!");
    }
    else
    {
      Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
      Serial.println("M5Stack Face Detect V-Func example");
      if (face_detect_obj.hasOwnProperty("FUNC")) {
        Serial.print("V-Function = ");

        Serial.println((const char*) face_detect_obj["FUNC"]);
      }

      if (face_detect_obj.hasOwnProperty("count")) {
        Serial.print("Face number = ");

        Serial.println((int)face_detect_obj["count"]);
      }


      if (face_detect_obj.hasOwnProperty("0")) {
        Serial.print("Face 1:\r\n");
        Serial.print("\tX:");
        Serial.println((int) face_detect_obj["0"]["x"]);
        Serial.print("\tY:");
        Serial.println((int) face_detect_obj["0"]["y"]);
        Serial.print("\tWidth:");
        Serial.println((int) face_detect_obj["0"]["w"]);
        Serial.print("\tHeight:");
        Serial.println((int) face_detect_obj["0"]["h"]);
        Serial.print("\tWeight:");
        Serial.println(face_detect_obj["0"]["value"]);

        // ... Parse more :)
      }

      Serial.println("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    }

  }
}
