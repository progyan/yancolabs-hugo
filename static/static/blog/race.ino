#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define X  A1
#define Y  A0
#define Z  12

int pos = 0;
int obsX[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
int obsY[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
int moneyX = -1;
int moneyY = -1;
int score = 0;
int bulletX = -1;
int bulletY = -1;
int targetX = -1;
int targetY = -1;
int kitX = -1;
int kitY = -1;
int bombX = -1;
int bombY = -1;
float spd = 25;
int lifes = 3;
char msg0[5] = "";
char msg1[5] = "";
char msg2[5] = "";
bool gameOver = false;
bool needToEmit = false;
int nitroLeft = 0;
int metersLeft = 5000;

LiquidCrystal_I2C lcd(0x38, 20, 4);

void addObstacle(int y) {
  for (int i = 0; i < 8; i++) {
    if (obsY[i] == -1) {
      obsY[i] = y;
      obsX[i] = 19;
      break;
    }
  }
}

void printScore() {
  char str[4];
  sprintf(str, "%04d", score);
  lcd.setCursor(16, 3);
  lcd.print(str);
}

void printMoney() {
  if (moneyY != -1) {
    lcd.setCursor(moneyX, moneyY);
    lcd.print("*");
    if (moneyX > 0) {
      moneyX--;
    } else {
      moneyX = -1;
      moneyY = -1;
    }
  }
}

void printBomb() {
  if (bombY != -1) {
    lcd.setCursor(bombX, bombY);
    lcd.print("o");
    if (bombX > 0) {
      bombX--;
    } else {
      bombX = -1;
      bombY = -1;
    }
  }
}

void printRepairKit() {
  if (kitY != -1) {
    lcd.setCursor(kitX, kitY);
    lcd.print("?");
    if (kitX > 0) {
      kitX--;
    } else {
      kitX = -1;
      kitY = -1;
    }
  }
}

void printTarget() {
  if (targetY != -1) {
    lcd.setCursor(targetX, targetY);
    lcd.print("@");
    if (targetX > 0) {
      targetX--;
    } else {
      targetX = -1;
      targetY = -1;
    }
  }
}

void printFinish() {
  if (metersLeft < 20 and metersLeft >= 0) {
    for (int i = 0; i < 4; i++) {
      lcd.setCursor(metersLeft, i);
      lcd.print("%");
    }
  }
  if (metersLeft < -6) {
    gameOver = true;
  }
}

void printObstacles() {
  for (int i = 0; i < 8; i++) {
    if (obsY[i] != -1) {
      lcd.setCursor(obsX[i], obsY[i]);
      lcd.print("#");
      if (obsX[i] > 0) {
        obsX[i]--;
      } else {
        obsX[i] = -1;
        obsY[i] = -1;
      }
    }
  }
}

void printCar() {
  lcd.setCursor(0, pos);
  if (lifes == 3)
    lcd.print("C:>");
  else if (lifes == 2)
    lcd.print("C:)");
  else if (lifes == 1)
    lcd.print("C:/");
  else
    lcd.print("C;&");
}

void addMoney(int y) {
  if (moneyY != -1) {
    return;
  }
  for (int i = 0; i < 8; i++) {
    if (obsY[i] == y and obsX[i] == 19) {
      return;
    }
  }
  moneyX = 19;
  moneyY = y;
}

void addTarget(int y) {
  if (targetY != -1) {
    return;
  }
  for (int i = 0; i < 8; i++) {
    if (obsY[i] == y and obsX[i] == 19) {
      return;
    }
  }
  if (moneyY == y and moneyX == 19) {
    return;
  }
  targetX = 19;
  targetY = y;
}

void addRepairKit(int y) {
  if (kitY != -1) {
    return;
  }
  for (int i = 0; i < 8; i++) {
    if (obsY[i] == y and obsX[i] == 19) {
      return;
    }
  }
  if ((moneyY == y and moneyX == 19) or (targetX == 19 and targetY == y)) {
    return;
  }
  kitX = 19;
  kitY = y;
}

void addBomb(int y) {
  if (bombY != -1) {
    return;
  }
  for (int i = 0; i < 8; i++) {
    if (obsY[i] == y and obsX[i] == 19) {
      return;
    }
  }
  if ((moneyY == y and moneyX == 19) or (targetX == 19 and targetY == y) or (kitX == 19 and kitY == y)) {
    return;
  }
  bombX = 19;
  bombY = y;
}

void updatePosition() {
  int y = analogRead(Y);

  if (y < 300 and pos > 0) {
    pos--;
  } else if (y > 900 and pos < 3) {
    pos++;
  }
}

void handleMoneyCollision() {
  if (moneyX < 3 and moneyY == pos) {
    score += 50;
    moneyX = -1;
    moneyY = -1;
    tone(7, 1760, 100);
    strcpy(msg0, "+50 ");
  }
}

void handleKitCollision() {
  if (kitX < 3 and kitY == pos) {
    switch (random(3)) {
      case 0: 
        if (lifes < 3) {
          lifes += 1;
          strcpy(msg0, "HEAL");
        }
        break;
      case 1:
        score += 300;
        strcpy(msg0, "+300");
        break;
      case 2:
        nitroLeft += 80;
        strcpy(msg0, "NITR");
        break;
    }
    kitX = -1;
    kitY = -1;
    tone(7, 1397, 200);
  }
}


void handleObstacleCollision() {
  for (int i = 0; i < 8; i++) {
    if (obsX[i] < 3 and obsY[i] == pos) {
      lifes--;
      tone(7, 55, 200);
      if (lifes < 1) {
        gameOver = true;
        gameOverHandler();
      }
      obsX[i] = -1;
      obsY[i] = -1;
    }
  }
  if (targetX < 3 and targetY == pos) {
    lifes--;
    tone(7, 55, 200);
    if (lifes < 1) {
      gameOver = true;
      gameOverHandler();
    }
    targetX = -1;
    targetY = -1;
  }
  if (bombX < 3 and bombY == pos) {
    lifes = 0;
    tone(7, 59, 200);
    gameOver = true;
    gameOverHandler();
    bombX = -1;
    bombY = -1;
  }
}

void gameOverHandler() {
  if (score > getHighScore()) {
    saveHighScore();
  }
}

void saveHighScore() {
  EEPROM.write(0, score / 100);
  EEPROM.write(1, score % 100);
}

int getHighScore() {
  return EEPROM.read(0) * 100 + EEPROM.read(1) + 1;
}

void gameOverScreen() {
  lcd.clear();
  if (metersLeft > 0) {
    lcd.setCursor(5, 0);
    lcd.print("GAME OVER!");
  } else {
    lcd.setCursor(6, 0);
    lcd.print("YOU WIN!");
  }
  lcd.setCursor(0, 2);
  lcd.print("SCORE:");
  char str[4];
  sprintf(str, "%04d", score);
  lcd.setCursor(16, 2);
  lcd.print(str);
  lcd.setCursor(0, 3);
  if (score == getHighScore()) {
    lcd.print("It's a new highscore");
  } else {
    lcd.print("HIGHSCORE:");
    sprintf(str, "%04d", getHighScore());
    lcd.setCursor(16, 3);
    lcd.print(str);
  }
  for(int i = 0; i < 150; i++) {
    delay(20);
    if(digitalRead(8)) {
      needToEmit = true;
      return;
    }
  }
  lcd.clear();
  if (metersLeft > 0) {
    lcd.setCursor(5, 0);
    lcd.print("GAME OVER!");
  } else {
    lcd.setCursor(6, 0);
    lcd.print("YOU WIN!");
  }
  lcd.setCursor(0, 2);
  lcd.print("To play again, press");
  lcd.setCursor(3, 3);
  lcd.print("the red button");
  for(int i = 0; i < 250; i++) {
    delay(20);
    if(digitalRead(8)) {
      needToEmit = true;
      return;
    }
  }
}

void readySteadyGo() {
  lcd.clear();
  lcd.setCursor(7, 1);
  lcd.print("READY?");
  tone(7, 880, 300);
  delay(1000);
  lcd.setCursor(6, 1);
  lcd.print("STEADY...");
  tone(7, 880, 300);
  delay(1000);
  lcd.setCursor(6, 1);
  lcd.print("  GO!!!  ");
  tone(7, 1760, 300);
  delay(1000);
}

void printBullet() {
  if (bulletY != -1) {
    lcd.setCursor(bulletX, bulletY);
    lcd.print("-");
    if (bulletX < 19) {
      bulletX++;
    } else {
      bulletX = -1;
      bulletY = -1;
    }
  }
}

void emitBullet() {
  if (bulletY == -1){
    if (score > 79) {
      bulletX = 3;
      bulletY = pos;
      score -= 80;
      tone(7, 3340, 100);
      lcd.setCursor(16, 2);
      strcpy(msg0, "-80");
    } else {
      lcd.setCursor(4, 0);
      lcd.print("not enough power");
    }
  }
}

void handleBulletCollision() {
  if ((bombX == bulletX or bombX == bulletX - 1) and bombY == bulletY and bulletY != -1) {
    bulletX = -1;
    bulletY = -1;
    targetX = -1;
    targetY = -1;
    score += 300;
    for (int i = 0; i < 8; i++){
      obsX[i] = -1;
      obsY[i] = -1;
    }
    targetX = -1;
    targetY = -1;
    moneyX = -1;
    moneyY = -1;
    bombX = -1;
    bombY = -1;
    kitX = -1;
    kitY = -1;
    tone(7, 196, 100);
    strcpy(msg0, "BOOM");
  }
  if ((targetX == bulletX or targetX == bulletX - 1) and targetY == bulletY and bulletY != -1) {
    bulletX = -1;
    bulletY = -1;
    targetX = -1;
    targetY = -1;
    score += 160;
    tone(7, 196, 100);
    strcpy(msg0, "+160");
  }
  for (int i = 0; i < 8; i++) {
    if ((obsX[i] == bulletX or obsX[i] == bulletX - 1) and obsY[i] == bulletY and bulletY != -1) {
      bulletX = -1;
      bulletY = -1;
      obsX[i] = -1;
      obsY[i] = -1;
      tone(7, 185, 100);
    }
  }
}

void resetStats() {
  gameOver = false;
  score = 0;
  pos = 0;
  for (int i = 0; i < 8; i++) {
    obsX[i] = -1;
    obsY[i] = -1;
  }
  moneyX = -1;
  moneyY = -1;
  bulletX = -1;
  bulletY = -1;
  spd = 30;
  lifes = 3;
  needToEmit = false;
}

void printMessage() {
  lcd.setCursor(16, 0);
  lcd.print(msg2);
  lcd.setCursor(16, 1);
  lcd.print(msg1);
  lcd.setCursor(16, 2);
  lcd.print(msg0);
  strcpy(msg2, msg1);
  strcpy(msg1, msg0);
  strcpy(msg0, "");
}

void pauseGame() {
  if (digitalRead(9) == HIGH) {
    lcd.clear();
    lcd.setCursor(4, 1);
    lcd.print("GAME PAUSED.");
    lcd.noBacklight();
    while (digitalRead(9) == HIGH){delay(10);}
    while (digitalRead(9) == LOW){delay(10);}
    lcd.backlight();
    readySteadyGo();
  }
}

void burnNitro() {
  if (nitroLeft > 0) {
    nitroLeft--;
  }
}

void startScreen() {
  lcd.setCursor(4, 1);
  lcd.print("YANCOLABS");
  lcd.setCursor(8, 2);
  lcd.print("presents");
  delay(3000);
  lcd.clear();
  delay(1000);
  lcd.setCursor(2, 1);
  lcd.print("the LCD RACER");
  lcd.setCursor(12, 2);
  lcd.print("arcade");
  delay(2000);
  lcd.clear();
  delay(2000);
  lcd.setCursor(1, 0);
  lcd.print("C:>- LcdRacer -<:D");
  lcd.setCursor(1, 2);
  lcd.print("Red button to play");
  lcd.setCursor(0, 3);
  lcd.print("Rules in the program");
  while (true) {
    delay(20);
    if(digitalRead(8)) {
      return;
    }
  }
}

void tickDelay() {
  for(int i = 0; i < 10; i++) {
    if (nitroLeft > 0) {
      delay(spd * 2 / 3);
    } else {
      delay(spd);
    }
    if(digitalRead(8)) {
      needToEmit = true;
    }
  }
}

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(7, OUTPUT);
  startScreen();
  //Serial.begin(9600); /////////////////
}
 
void loop() {
  randomSeed(analogRead(0));
  readySteadyGo();
  while (true) {
    if (gameOver) {
      gameOverScreen();
      if (needToEmit) {
        resetStats();
        break;
      }
    } else {
      handleMoneyCollision();
      handleObstacleCollision();
      handleBulletCollision();
      handleKitCollision();
      burnNitro();
      
      updatePosition();
    
      lcd.clear();
      printObstacles();
      printMoney();
      printTarget();
      printRepairKit();
      printBomb();
      printFinish();
      printCar();
      printBullet();
      printScore();
      printMessage();

      if (metersLeft > 36) {
        if (random(4) == 1) {
          addObstacle(random(4));
        }
        if (random(20) == 1) {
          addMoney(random(4));
        }
        if (random(60) == 1) {
          addTarget(random(4));
        }
        if (random(180) == 1) {
          addRepairKit(random(4));
        } 
        if (random(150) == 1) {
          addBomb(random(4));
        }
      }
      if (needToEmit) {
        emitBullet();
        needToEmit = false;
      }

      pauseGame();
      
      tickDelay();

      spd = 25 - score / 250;
      
      score += 1;

      metersLeft--;

      //Serial.println(metersLeft); /////////////
    }
  }
}
