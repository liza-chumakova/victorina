/*
 * MIT License
 *
 * Copyright (c) 2021 Liza Chumakova
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

enum VictorinaState {
  VictorinaStateNull = 0,
  VictorinaStateIdle,
  VictorinaStateRun1,
  VictorinaStateRun2
};

const int LED1 = 13;
const int LED2 = 12;
const int LED3 = 11;
const int LED4 = 10;

static unsigned long TheVar = 0;
static VictorinaState TheVictorinaState = VictorinaStateNull;

static void loop_500ms();

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long time_now = millis();
  if (TheVar == 0)
  {
    loop_500ms();
    TheVar = time_now + 500;
  }
  else if (time_now >= TheVar)
  {
    loop_500ms();
    TheVar = time_now + 500;
  }
}

void loop_500ms()
{
}
