#include <Wire.h>
#include "rgb_lcd.h"

#define trigPin1 3
#define echoPin1 2
#define trigPin2 5
#define echoPin2 4
#define trigPin3 7
#define echoPin3 6
#define BUZZER_PIN 8
#define SWITCH_PIN 13

rgb_lcd lcd;

// --- Melodien ---
int start_melody[] = {523, 659, 784, 988, 1047, 0, 784, 988};
int start_durations[] = {8, 8, 8, 8, 4, 8, 8, 2};
int start_size = sizeof(start_durations) / sizeof(start_durations[0]);

int game_melody[] = {
  330, 370, 440, 554, 659, 554, 440, 370,
  440, 494, 554, 659, 740, 659, 554, 494,
  440,   0, 659,   0, 587, 554, 494, 440,
  330, 370, 440, 330, 294, 277, 247, 220
};

int game_melody_2[] = {
  330, 370, 440, 554, 659, 554, 440, 370,
  440, 494, 554, 659, 740, 659, 554, 494
};

int game_durations[] = {
   8, 8, 4, 4, 4, 4, 4, 4,
   4, 8, 8, 4, 4, 4, 4, 4,
   4, 8, 4, 8, 4, 4, 4, 2,
   8, 8, 4, 4, 4, 4, 4, 2
};

int game_durations_2[] = {
   8, 8, 4, 4, 4, 4, 4, 4,
   4, 8, 8, 4, 4, 4, 4, 4
};

int game_size = sizeof(game_durations) / sizeof(game_durations[0]);
int game_size_2 = sizeof(game_durations_2) / sizeof(game_durations_2[0]);

// --- Hilfsfunktionen für Sound ---
void play_drop_effect() {
  for (int f = 1500; f > 300; f -= 40) {
    tone(BUZZER_PIN, f, 20);
    delay(15);
  }
  delay(200);
  noTone(BUZZER_PIN);
}

void play_melody(int melody[], int durations[], int size) {
  for (int note = 0; note < size; note++) {
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}

// --- LCD Hilfsfunktionen ---
int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 20000);
  if (duration == 0) return -1;
  int dist = duration * 0.034 / 2;
  if (dist < 2 || dist > 400) return -1;
  return dist;
}

void showMessageTwoLines(const char *line1, const char *line2, int durationSeconds) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  if (durationSeconds > 0) delay(durationSeconds * 1000);
}

// --- SETUP ---
void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.setRGB(0, 128, 255);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Hello!");
  play_melody(start_melody, start_durations, start_size);

  showMessageTwoLines("Welcome to Alex and", "& Robin's life.", 3);
  showMessageTwoLines("They are a", "couple and live", 2);
  showMessageTwoLines("in the same", "household.", 2);
  showMessageTwoLines("Both are now", "at work.", 3);
}

// --- LOOP ---
void loop() {
  // --- Sequence 1: Alex & Robin ---
  if (digitalRead(SWITCH_PIN) == LOW) {
    lcd.setRGB(0, 128, 255);
    showMessageTwoLines("Send Alex home", "from work.", 3);
    showMessageTwoLines("Insert marble", "on the left.", 0);

    // --- Alex ---
    while (true) {
      int distance2 = measureDistance(trigPin2, echoPin2);
      if (distance2 != -1 && distance2 < 7) {
        showMessageTwoLines("Alex left work.", "", 0);
        play_melody(game_melody_2, game_durations_2, game_size_2);
        showMessageTwoLines("Alex came home.", "", 5);
        break;
      }
      delay(50);
    }

    // --- Robin ---
    showMessageTwoLines("Send Robin home", "from work.", 3);
    showMessageTwoLines("Insert marble", "on the right.", 0);

    while (true) {
      int distance1 = measureDistance(trigPin1, echoPin1);
      int distance3 = measureDistance(trigPin3, echoPin3);

      if (distance1 != -1 && distance1 < 7) {
        // Musik + Text starten GLEICHZEITIG
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Robin left work.");

        unsigned long lastNoteTime = 0;
        unsigned long lastTextSwitch = millis();
        unsigned long lastDropTime = millis();
        unsigned long startTime = millis();
        int melodyIndex = 0;
        bool notePlaying = false;
        bool showFirstText = true;
        int duration = 0;

        while (true) {
          unsigned long now = millis();

          // Textwechsel alle 3 Sekunden
          if (now - lastTextSwitch >= 2000) {
            lcd.clear();
            if (showFirstText) {
              showMessageTwoLines("Pull out the", "cards to see why", 0);
            } else {
              showMessageTwoLines("Robin's trip", "got delayed.", 0);
            }
            showFirstText = !showFirstText;
            lastTextSwitch = now;
          }

          // Musik non-blocking spielen
          if (!notePlaying) {
            duration = 1000 / game_durations[melodyIndex];
            tone(BUZZER_PIN, game_melody[melodyIndex], duration);
            notePlaying = true;
            lastNoteTime = now;
          } 
          else if (now - lastNoteTime >= duration * 1.30) {
            noTone(BUZZER_PIN);
            melodyIndex++;
            notePlaying = false;
            if (melodyIndex >= game_size) melodyIndex = 0;
          }

          // Drop-Effekt alle 2 Sekunden
          if (now - lastDropTime >= 2000) {
            noTone(BUZZER_PIN);
            play_drop_effect();
            lastDropTime = now;
          }

          // Sensor 3 prüfen (Robin kommt heim)
          distance3 = measureDistance(trigPin3, echoPin3);
          if (distance3 != -1 && distance3 < 7) {
            noTone(BUZZER_PIN);
            showMessageTwoLines("Robin came home.", "", 5);
            break;
          }

          // Timeout nach 60 Sekunden
          if (now - startTime >= 60000UL) {
            noTone(BUZZER_PIN);
            showMessageTwoLines("Robin got lost...", "", 4);
            break;
          }
        }
        break; // beendet Robin-Loop
      }
      delay(50);
    }

    // --- Finale Anzeige ---
    lcd.setRGB(255, 0, 0);
    showMessageTwoLines("Whose time got", "stolen?", 5);
    showMessageTwoLines("Switch to round", "2 to continue!", 0);

    // Warten bis Schalter umgelegt wird
    while (digitalRead(SWITCH_PIN) == LOW) {
      delay(100);
    }
  }

  // --- Sequence 2: Duties ---
  else {
    lcd.setRGB(0, 255, 0);
    showMessageTwoLines("How can we make", "it more fair?", 5);
    showMessageTwoLines("Try again with", "marbles & cards.", 5);

    // Endloop: Hinweise wechseln
    while (true) {
      if (digitalRead(SWITCH_PIN) == LOW) break;
      showMessageTwoLines("When done:", "switch power off.", 5);
      showMessageTwoLines("How can we make", "it more fair?", 5);
      showMessageTwoLines("Try again with", "marbles & cards", 5);
    }
  }
}
