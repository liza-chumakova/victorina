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

#include <ezButton.h>

enum VictorinaState {
  VictorinaStateIdle = 0,
  VictorinaStateGarland,
  VictorinaStateTest,
  VictorinaStateWaitingForWinner,
  VictorinaStateDisplayWinner
};

const int PARTICIPANT_1_LED = 13;
const int PARTICIPANT_2_LED = 12;
const int PARTICIPANT_3_LED = 11;
const int PRESENTER_EXTRA_LED = 10;
const int PRESENTER_KEY_1 = A4;
const int PRESENTER_KEY_2 = A5;
const int PARTICIPANT_1_KEY = A1;
const int PARTICIPANT_2_KEY = A2;
const int PARTICIPANT_3_KEY = A3;



static unsigned long TheGarlandNextSwitchTimeMs = 0;
static VictorinaState TheVictorinaState = VictorinaStateIdle;
static int TheGarlandActiveLED = 0;
static unsigned long TheOldButtonState = 1;
static ezButton ThePresenterButton1(PRESENTER_KEY_1);
static ezButton ThePresenterButton2(PRESENTER_KEY_2);

static void update_LEDs();
static void loop_500ms();
static void handle_button_press();
static void loop_idle();
static void loop_garland();
static void loop_test();
static void loop_waiting_for_winner();
static void loop_display_winner();

void setup() {
  // put your setup code here, to run once:
  pinMode(PARTICIPANT_1_LED, OUTPUT);
  pinMode(PARTICIPANT_2_LED, OUTPUT);
  pinMode(PARTICIPANT_3_LED, OUTPUT);
  pinMode(PRESENTER_EXTRA_LED, OUTPUT);
  pinMode(PRESENTER_KEY_2, INPUT);
  pinMode(PRESENTER_KEY_1, INPUT);
  pinMode(PARTICIPANT_1_KEY, INPUT);
  pinMode(PARTICIPANT_2_KEY, INPUT);
  pinMode(PARTICIPANT_3_KEY, INPUT);
  ThePresenterButton1.setDebounceTime(50);
  ThePresenterButton2.setDebounceTime(50);
}

void loop()
{
  if (VictorinaStateIdle == TheVictorinaState)
  {
    loop_idle();
  }
  else if (VictorinaStateGarland == TheVictorinaState)
  {
    loop_garland();
  }
  else if (VictorinaStateTest == TheVictorinaState)
  {
    loop_test();
  }
  else if (VictorinaStateWaitingForWinner == TheVictorinaState)
  {
    loop_waiting_for_winner();
  }
  else if (VictorinaStateDisplayWinner == TheVictorinaState)
  {
    loop_display_winner();
  }
}

void loop_500ms()
{
  if (0 == TheGarlandActiveLED)
  {
    digitalWrite(PARTICIPANT_1_LED, LOW);
    digitalWrite(PARTICIPANT_2_LED, HIGH);
    digitalWrite(PARTICIPANT_3_LED, HIGH);
    digitalWrite(PRESENTER_EXTRA_LED, HIGH);
    TheGarlandActiveLED = 1;
  }
  else if (1 == TheGarlandActiveLED)
  {
    digitalWrite(PARTICIPANT_1_LED, HIGH);
    digitalWrite(PARTICIPANT_2_LED, LOW);
    digitalWrite(PARTICIPANT_3_LED, HIGH);
    digitalWrite(PRESENTER_EXTRA_LED, HIGH);
    TheGarlandActiveLED = 2;
  }
  else if (2 == TheGarlandActiveLED)
  {
    digitalWrite(PARTICIPANT_1_LED, HIGH);
    digitalWrite(PARTICIPANT_2_LED, HIGH);
    digitalWrite(PARTICIPANT_3_LED, LOW);
    digitalWrite(PRESENTER_EXTRA_LED, HIGH);
    TheGarlandActiveLED = 0;
  }
}

void handle_button_press()
{
}

void loop_idle()
{
  // Даём возможность первой кнопке обработать то, что ей надо
  ThePresenterButton1.loop();

  // Проверим, надо ли переходить в другие состояния
  if (ThePresenterButton1.isPressed())
  {
    TheVictorinaState = VictorinaStateGarland;
  }

  digitalWrite(PARTICIPANT_1_LED, HIGH);
  digitalWrite(PARTICIPANT_2_LED, HIGH);
  digitalWrite(PARTICIPANT_3_LED, HIGH);
  digitalWrite(PRESENTER_EXTRA_LED, LOW);
}

void loop_garland()
{
  // Даём возможность первой кнопке обработать то, что ей надо
  ThePresenterButton1.loop();

  // Проверим, надо ли переходить в другие состояния
  if (ThePresenterButton1.isPressed())
  {
    TheVictorinaState = VictorinaStateTest;
  }

  const int timeNow = millis();
  if(0 == TheGarlandNextSwitchTimeMs || TheGarlandNextSwitchTimeMs <= timeNow)
  {
    loop_500ms();
    TheGarlandNextSwitchTimeMs = timeNow + 250;
  }
}

void loop_test()
{
  // Даём возможность первой кнопке обработать то, что ей надо
  ThePresenterButton1.loop();

  // Проверим, надо ли переходить в другие состояния
  if (ThePresenterButton1.isPressed())
  {
    TheVictorinaState = VictorinaStateWaitingForWinner;
  }

  digitalWrite(PARTICIPANT_1_LED, digitalRead(PARTICIPANT_1_KEY));
  digitalWrite(PARTICIPANT_2_LED, digitalRead(PARTICIPANT_2_KEY));
  digitalWrite(PARTICIPANT_3_LED, digitalRead(PARTICIPANT_3_KEY));
}

void loop_waiting_for_winner()
{
  digitalWrite(PARTICIPANT_1_LED, HIGH);
  digitalWrite(PARTICIPANT_2_LED, HIGH);
  digitalWrite(PARTICIPANT_3_LED, HIGH);
  digitalWrite(PRESENTER_EXTRA_LED, HIGH);
}

void loop_display_winner()
{
  // Даём возможность первой и второй кнопкам обработать то, что им надо
  ThePresenterButton1.loop();
  ThePresenterButton2.loop();
}
