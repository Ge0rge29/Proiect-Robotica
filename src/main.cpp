#include <Adafruit_GFX.h>      // Biblioteca pentru funcții grafice
#include <Adafruit_ST7735.h>   // Biblioteca pentru LCD cu driver ST7735

// Configurare pini hardware
#define TFT_CS 10   // Pinul CS pentru LCD
#define TFT_RST 9   // Pinul RST pentru LCD
#define TFT_DC 8    // Pinul DC pentru LCD
#define VRx A0      // Pin analogic pentru axa X a joystick-ului
#define VRy A1      // Pin analogic pentru axa Y a joystick-ului
#define SW 2        // Pin digital pentru butonul joystick-ului
#define START_BUTTON 3 // Pin digital pentru butonul de start/reset
#define BUZZER 4     // Pin digital pentru buzzer

// Dimensiuni tabla de joc
#define BOARD_SIZE 3

unsigned long startTime = 0; // Timpul de început al jocului
unsigned long gameDuration = 30000; // Durata maximă a jocului în milisecunde (30 secunde)

bool gameOver = false; // Variabilă pentru a indica starea jocului

int scoreX = 0; // Scor pentru jucătorul X
int scoreO = 0; // Scor pentru jucătorul O

// Variabile globale
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
char board[BOARD_SIZE][BOARD_SIZE]; // Tabla de joc
int currentPlayer = 1;              // Jucătorul curent (1 sau 2)
int cursorX = 0, cursorY = 0;       // Poziția cursorului
bool gameStarted = false;           // Indică dacă jocul a început
unsigned long lastDebounceTime = 0; // Timpul pentru debounce-ul joystick-ului și al butonului
unsigned long debounceDelay = 200;  // Întârziere pentru debounce

// Declarații de funcții
void resetBoard();
void displayBoard();
void highlightCursor();
bool checkWinner();
bool isBoardFull();
void displayWinner(int player);
void displayTie();

// Funcție pentru centrare text pe orizontală
int centerText(const char *text, int textSize) {
  int16_t x1, y1;
  uint16_t w, h;

  // Calculăm dimensiunea textului
  tft.setTextSize(textSize);
  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  // Calculăm coordonata X pentru centrare
  return (128 - w) / 2; // 128 = lățimea ecranului
}

void setup() {
  // Configurare joystick și butoane
  pinMode(SW, INPUT_PULLUP);
  pinMode(START_BUTTON, INPUT_PULLUP);

  // Inițializare LCD
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);

  // Mesaj de bun venit
  tft.setTextColor(ST7735_WHITE);

  // Titlu centrat
  tft.setTextSize(2);
  int x = centerText("Bun venit", 2);
  tft.setCursor(x, 20);
  tft.println("Bun venit");

  x = centerText("la X si O!", 2);
  tft.setCursor(x, 40);
  tft.println("la X si O!");

  // Instrucțiuni centrate
  tft.setTextSize(1);
  x = centerText("Apasa START pentru", 1);
  tft.setCursor(x, 70);
  tft.println("Apasa START pentru");

  x = centerText("a incepe jocul!", 1);
  tft.setCursor(x, 80);
  tft.println("a incepe jocul!");
}

void resetGame() {
  gameStarted = true;    // Marcare că jocul a început
  gameOver = false;      // Resetează starea jocului
  resetBoard();          // Resetează tabla
  tft.fillScreen(ST7735_BLACK);
  displayBoard();        // Reafișează tabla
}

void loop() {
  unsigned long currentTime = millis(); // Timpul curent
  static unsigned long buttonPressTime = 0; // Momentul când butonul este apăsat

  // Verificare apăsare buton START
  if (digitalRead(START_BUTTON) == LOW) { // Butonul este apăsat
    if (buttonPressTime == 0) {
      buttonPressTime = currentTime; // Înregistrăm momentul apăsării
    }

    // Verificăm dacă butonul este apăsat mai mult de 4 secunde
    if (currentTime - buttonPressTime > 4000) {
      resetGame();              // Resetează jocul
      buttonPressTime = 0;      // Resetăm timpul de apăsare
      return;                   // Ieșim din funcție pentru a evita alte actualizări
    }
  } else { // Butonul este eliberat
    if (buttonPressTime != 0 && (currentTime - buttonPressTime < 4000)) {
      // Apăsare scurtă - pornește jocul doar dacă nu a început sau e încheiat
      if (!gameStarted || gameOver) {
        resetGame();
      }
    }
    buttonPressTime = 0; // Resetăm timpul de apăsare
  }

  // Restul logicii jocului
  if (!gameStarted || gameOver) {
    return; // Jocul nu a început sau s-a terminat
  }

  // Control joystick și alte funcții
  int xValue = analogRead(VRx);
  int yValue = analogRead(VRy);

  if (currentTime - lastDebounceTime > debounceDelay) {
    // Mișcări pe axele X și Y
    if (xValue < 300 && cursorX > 0) {
      cursorX--;
      lastDebounceTime = currentTime;
    } else if (xValue > 700 && cursorX < BOARD_SIZE - 1) {
      cursorX++;
      lastDebounceTime = currentTime;
    }

    if (yValue < 300 && cursorY > 0) {
      cursorY--;
      lastDebounceTime = currentTime;
    } else if (yValue > 700 && cursorY < BOARD_SIZE - 1) {
      cursorY++;
      lastDebounceTime = currentTime;
    }
  }

  // Confirmare mutare cu butonul joystick-ului
  if (digitalRead(SW) == LOW && (currentTime - lastDebounceTime > debounceDelay)) {
    if (board[cursorY][cursorX] == ' ') {
      board[cursorY][cursorX] = (currentPlayer == 1) ? 'X' : 'O';
      displayBoard();

      if (checkWinner()) {
        displayWinner(currentPlayer);
        gameOver = true;
      } else if (isBoardFull()) {
        displayTie();
        gameOver = true;
      } else {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
      }
    }
    lastDebounceTime = currentTime;
  }

  // Afișare cursor
  if (!gameOver) {
    highlightCursor();
  }
}




// Resetarea tablei de joc
void resetBoard() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = ' ';
    }
  }
  cursorX = 0;
  cursorY = 0;
  currentPlayer = 1;
}

// Afișare tabla de joc pe LCD cu fundal negru și grilă albă
void displayBoard() {
  // Setăm fundalul negru
  tft.fillScreen(ST7735_BLACK); // Fundal negru

  // Desenăm bordura care înconjoară tabla
  tft.drawRect(5, 5, 120, 120, ST7735_WHITE); // Bordura albă

  // Desenăm grila internă
  for (int i = 1; i < BOARD_SIZE; i++) {
    // Linii orizontale interne
    tft.drawLine(5, i * 40 + 5, 125, i * 40 + 5, ST7735_WHITE);
    // Linii verticale interne
    tft.drawLine(i * 40 + 5, 5, i * 40 + 5, 125, ST7735_WHITE);
  }

  // Desenăm tabla de joc (simbolurile)
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      tft.setCursor(j * 40 + 15, i * 40 + 10);
      tft.setTextSize(3);
      if (board[i][j] == 'X') {
        tft.setTextColor(ST7735_BLUE, ST7735_BLACK); // X - Albastru
      } else if (board[i][j] == 'O') {
        tft.setTextColor(ST7735_YELLOW, ST7735_BLACK); // O - Galben
      } else {
        tft.setTextColor(ST7735_WHITE, ST7735_BLACK); // Fundal gol
      }
      tft.print(board[i][j]);
    }
  }

  // Afișăm scorurile sub tabla de joc
  tft.setTextSize(1);
  tft.setTextColor(ST7735_BLUE); // Scor X - Albastru
  tft.setCursor(10, 130); // Poziție sub tablă
  tft.print("X: ");
  tft.print(scoreX);

  tft.setTextColor(ST7735_YELLOW); // Scor O - Galben
  tft.setCursor(80, 130);
  tft.print("O: ");
  tft.print(scoreO);
}

void resetScoresAndDisplaySeriesWinner(int player) {
  // Curățăm ecranul
  tft.fillScreen(ST7735_BLACK);

  // Mesaj principal: „Seria castigata de”
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1); // Dimensiune text pentru mesaj
  int x = centerText("Seria castigata de", 1);
  tft.setCursor(x, 40);
  tft.println("Seria castigata de");

  // Subtitlu: „Player X!”
  tft.setTextSize(2); // Dimensiune text pentru câștigător
  char message[20];
  sprintf(message, "Player %d!", player);
  x = centerText(message, 2);
  tft.setCursor(x, 60);
  tft.println(message);

  // Menținem mesajul afișat pentru 3 secunde
  delay(3000);

  // Resetăm scorurile
  scoreX = 0;
  scoreO = 0;

  // Resetăm tabla de joc și revenim la starea inițială
  gameStarted = false;
  gameOver = true; // Marcăm că jocul este terminat pentru resetare
  tft.fillScreen(ST7735_BLACK);

  // Mesaj de așteptare pentru jocul următor
  tft.setTextSize(1);
  x = centerText("Apasa START pentru a incepe", 1);
  tft.setCursor(x, 80);
  tft.println("Apasa START pentru a incepe");
}



// Evidențiere cursor cu chenar roșu fără palpitare
void highlightCursor() {
  static int prevCursorX = -1; // Reține poziția anterioară pe X
  static int prevCursorY = -1; // Reține poziția anterioară pe Y

  // Dacă poziția cursorului nu s-a schimbat, nu facem nimic
  if (cursorX == prevCursorX && cursorY == prevCursorY) {
    return;
  }

  // Ștergem chenarul anterior (redesenăm doar conturul alb al celulei)
  if (prevCursorX != -1 && prevCursorY != -1) { // Dacă este validă
    int prevX = prevCursorX * 40 + 5;
    int prevY = prevCursorY * 40 + 5;
    tft.drawRect(prevX, prevY, 40, 40, ST7735_WHITE); // Refacem conturul alb
  }

  // Desenăm noul chenar roșu
  int currentX = cursorX * 40 + 5;
  int currentY = cursorY * 40 + 5;
  tft.drawRect(currentX, currentY, 40, 40, ST7735_RED);

  // Actualizăm poziția anterioară
  prevCursorX = cursorX;
  prevCursorY = cursorY;
}




// Verificare câștigător
bool checkWinner() {
  // Verificare linii
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
      return true;
    }
  }
  // Verificare coloane
  for (int j = 0; j < BOARD_SIZE; j++) {
    if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
      return true;
    }
  }
  // Verificare diagonale
  if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    return true;
  }
  if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
    return true;
  }
  return false;
}

// Verificare dacă tabla este completă
bool isBoardFull() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        return false;
      }
    }
  }
  return true;
}

void displayWinner(int player) {
  gameOver = true; // Marcare joc terminat

  // Actualizăm scorurile
  if (player == 1) {
    scoreX++;
  } else {
    scoreO++;
  }

  // Sunet pentru câștigător:
  tone(BUZZER, 1500, 700); // Frecvență 1500 Hz pentru 700 ms

  // Verificăm dacă un jucător a câștigat seria
  if (scoreX == 5) {
    resetScoresAndDisplaySeriesWinner(1);
    return;
  } else if (scoreO == 5) {
    resetScoresAndDisplaySeriesWinner(2);
    return;
  }

  // Afișăm mesajul pentru câștigătorul partidei
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);

  tft.setTextSize(2); // Dimensiune mai mică pentru a încăpea pe un singur rând
  int x = centerText("Bravo!", 2);
  tft.setCursor(x, 40);
  tft.println("Bravo!");

  // Subtitlu: "Jucatorul X a castigat!"
  char message[20];
  sprintf(message, "Jucatorul %d", player);
  x = centerText(message, 1);
  tft.setCursor(x, 60);
  tft.println(message);

  x = centerText("a castigat!", 1);
  tft.setCursor(x, 70);
  tft.println("a castigat!");
}



// Afișare remiză centrată
void displayTie() {
  gameOver = true; // Marcare joc terminat

// Sunet pentru remiză:
  tone(BUZZER, 800, 400); // Frecvență 800 Hz pentru 400 ms

  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);

  // Mesaj principal
  tft.setTextSize(2);
  int x = centerText("Remiza!", 2);
  tft.setCursor(x, 40);
  tft.println("Remiza!");

  // Subtitlu
  x = centerText("Nimeni nu a castigat.", 1);
  tft.setCursor(x, 60);
  tft.println("Nimeni nu a castigat.");
}


