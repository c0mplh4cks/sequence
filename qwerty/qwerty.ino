#include <Keyboard.h>
#include "layout.h"
#include "oled.h"


int state[layers][vertical][horizontal];
int grid[vertical][horizontal];
int prev[vertical][horizontal];
int layer = 0;


void setup() {
  for (int i=0; i<horizontal; i++) {
    pinMode(horz[i], INPUT);
  }
  for (int i=0; i<vertical; i++) {
    pinMode(vert[i], OUTPUT);
  }
  for (int l=0; l<layers; l++) {
    for (int r=0; r<vertical; r++) {
      for (int c=0; c<horizontal; c++) {
        state[l][r][c] = 0;
      }
    }
  }

  oled_setup();
  Keyboard.begin();
  Serial.begin(9600);
  delay(100);
  oled.clearDisplay();

  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 10);
  oled.println("Sequence");
  oled.setCursor(0, 20);
  oled.println("by c0mplh4cks");
  oled.display();
}


bool pressed(int r, int c) {
    if (grid[r][c] == 1) {
      return true;
    }
    return false;
}


bool press(int r, int c) {
  if (grid[r][c] == 1 && prev[r][c] == 0) {
    return true;
  }
  return false;
}


bool release(int r, int c) {
  if (grid[r][c] == 0 && prev[r][c] == 1) {
    return true;
  }
  return false;
}


void raw() {
  for (int r=0; r<vertical; r++) {
    digitalWrite(vert[r], HIGH);

    for (int c=0; c<horizontal; c++) {
      prev[r][c] = grid[r][c];
      grid[r][c] = digitalRead(horz[c]);
    }

    digitalWrite(vert[r], LOW);
  }
}


void rise(int new_layer) {
  for (int r=0; r<vertical; r++) {
    for (int c=0; c<horizontal; c++) {

      if (state[layer][r][c]) {
        bool b = false;
        for (int m=0; m<modifiers; m++) {
          if (layout[layer][r][c] == modifier[m]) {
            b = true;
          }
        }
        if (b == false) {
          Keyboard.release(layout[layer][r][c]);
          state[layer][r][c] = 0;
        }
      }

    }
  }
  layer = new_layer;
}


void clean() { // clear after layer off
  for (int l=0; l<layers; l++) {
    for (int r=0; r<vertical; r++) {
      for (int c=0; c<horizontal; c++) {
        if ((state[l][r][c] == 1) && (layout[l][r][c] != layout[0][r][c])) {
          Keyboard.release(layout[l][r][c]);
          state[l][r][c] == 0;
        }
      }
    }
  }
  layer = 0;
}


void loop() {
  raw();

  if (press(4, 7)) {
    rise(1);
  } else if (release(4, 7)) {
    clean();
  }
  /* layer manager */
  /*if (layer == 0 && press(3, 7)) {
    layer = 1;
  } else if (layer == 1 && press(3, 6)) {
    layer = 2;

  } else if (layer == 2 && press(3, 6) && pressed(3, 7)) {
    clean();
  } else if (layer == 1 && release(3, 7)) {
    clean();
  }*/

  /* press or release */
  for (int r=0; r<vertical; r++) {
    for (int c=0; c<horizontal; c++) {
      int p = prev[r][c];
      int n = grid[r][c];

      if (n-p == 1) {
        Keyboard.press(layout[layer][r][c]);
        state[layer][r][c] = 1;
        //Serial.println(String(r) + " " + String(c));
      } else if (n-p == -1) {
        Keyboard.release(layout[layer][r][c]);
        state[layer][r][c] = 0;
      }
    }
  }

  delay(10);
}
