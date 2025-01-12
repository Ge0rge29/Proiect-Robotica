# Tic-Tac-Toe Game

# Introducere

Acest proiect are ca scop dezvoltarea unui sistem interactiv pentru controlul unui joc.
Proiectul permite utilizatorului să joace clasicul joc de X și O pe un ecran LCD, navigând între pozițiile de pe tablă cu ajutorul unui joystick. După plasarea simbolurilor (X sau O), ecranul afișează mutările, iar la final, declară câștigătorul sau remiza. Scopul jocului e acela de a obtine 3 semne la fel pe 3 casete asezate orizontal, vetical sau pe diagonala.

# Descriere generală

![imgrobo](https://github.com/user-attachments/assets/e62c20b9-60cb-4cdd-8b0d-2a1e03aff2af)


În cadrul acestui proiect, doi jucători vor folosi, pe rând, joystick-ul pentru a naviga pe o tablă de joc. Prin apăsarea butonului de pe joystick, aceștia confirmă mutarea, iar dispozitivul va atribui automat simbolul corespunzător jucătorului activ, în funcție de numărul rundei. După fiecare mutare, sistemul verifică dacă există o combinație câștigătoare. Dacă nu se identifică un câștigător și nu mai există spații libere pe tablă, partida se încheie cu o remiză. La final, un mesaj afișează rezultatul: victoria jucătorului 1 sau 2, ori remiza, în funcție de situație.

# Hardware Design

Schema electrica: https://wokwi.com/projects/417351812325771265

## Lista de piese

- **Microcontroller:** Arduino Uno 
- **Joystick**
- **Ecran LCD:** LCD 128x160 cu SPI
- **Fire de conexiune** 
- **Breadboard**
- **Buton de start**
- **Buzzer**

# Bill of Materials (BOM) pentru Proiectul X și O cu Arduino

| Nr. | Componente/Module       | Descriere                                         | Cantitate | Achiziționat de la               | Link de Achiziție / Datasheet                                      |
|-----|-------------------------|---------------------------------------------------|-----------|---------------------------------|-------------------------------------------------------------------|
| 1   | **Arduino Uno**          | Microcontroller principal                        | 1         | Facultate  |  |
| 2   | **Joystick**             | Joystick 2 axe cu buton integrat                  | 1         | Facultate |     |
| 3   | **LCD 128x160 SPI**      | Ecran LCD cu 128x160 px și interfață SPI          | 1         | optimus digital.ro | https://www.optimusdigital.ro/en/lcds/12392-modul-lcd-de-18-cu-spi-i-controller-st7735-128x160-px.html?gad_source=1&gclid=CjwKCAiAmfq6BhAsEiwAX1jsZwh_IV_gGrMe_jemneTNzMCyaAKME1BIM87AnANaRKASR271lopC7xoCodgQAvD_BwE|
| 4   | **Buton Push**           | Buton tactil pentru start/reset joc               | 1         | Facultate   |            |
| 5   | **Buzzer**               | Dispozitiv pentru generarea de suntete            | 1         | Facultate   |            |
| 6   | **Fire de conexiune**    | Fire pentru conexiuni între module și Arduino     | -     | Facultate   |                                                                 |
| 7   | **Breadboard**           | Placă de testare pentru prototipuri               | 1         | Facultate   |    |

![b2e18c88-8f6d-4cab-b3c5-8a97f4e42b10](https://github.com/user-attachments/assets/e7de5c60-a145-43b6-bd68-501423fdb0e8)


# Descrierea Funcționalității Hardware

În acest proiect, am utilizat mai multe componente hardware care sunt conectate la microcontroller-ul **Arduino Uno**, iar interfețele de comunicare folosite sunt conforme cu cele studiate în laboratoarele cursului. Detaliile componentelor, interfețelor și consumul de energie sunt descrise mai jos.

## 1. Microcontroller: Arduino Uno
**Rol:** Arduino Uno este microcontroller-ul principal care gestionează întreaga logică a jocului și interacțiunea cu componentele externe, cum ar fi joystick-ul și LCD-ul.

**Interfețe:**
- **USART** (Laboratorul 1): Conectarea la calculator se face prin portul USB utilizând protocolul USART (Universal Synchronous Asynchronous Receiver Transmitter), care este folosit pentru comunicarea serială.
- **SPI** (Laboratorul 5): Ecranul LCD 128x160 utilizează protocolul SPI (Serial Peripheral Interface) pentru a comunica cu Arduino, folosind pinii **MISO, MOSI, SCK** și **CS**.

**Consumul de energie:** Arduino Uno consumă aproximativ **50-200mA**, iar alimentarea se face prin USB, care poate oferi **500mA**, suficient pentru alimentarea întregului sistem.

---

## 2. Joystick
**Rol:** Joystick-ul permite utilizatorilor să navigheze pe tabla de joc. Acesta transmite valori analogice pentru axele **X** și **Y** și are un buton care confirmă mutările.

A0 (Arduino) → citește mișcarea pe axa X

A1 (Arduino) → citește mișcarea pe axa Y

**Interfețe:**
- **ADC** (Laboratorul 4): Valorile analogice de pe axele **X** și **Y** sunt citite de Arduino folosind pinii **analogici A0 și A1**, utilizând convertorul analog-digital (ADC) din Arduino.

**Consumul de energie:** Joystick-ul consumă aproximativ **10-20mA**.

---

## 3. Ecran LCD 128x160 SPI
**Rol:** LCD-ul afișează tabla de joc și mesajele despre starea jocului (câștigători sau remiză).

**Interfețe:**
- **SPI** (Laboratorul 5): LCD-ul utilizează protocolul SPI pentru a comunica cu Arduino, folosind pinii **MISO, MOSI, SCK** și **CS**. Componentele grafice și textuale sunt transmise către LCD folosind acest protocol pentru a actualiza afișajul.

VCC → 5V (Arduino)

GND → GND (Arduino)

CS (Chip Select) - Pin D10: Acest pin indică LCD-ului când să răspundă la semnalele SPI.

De ce: CS (Chip Select) este folosit pentru a "selecta" LCD-ul pentru comunicație. Când pinul CS este LOW, LCD-ul primește date, iar când este HIGH, LCD-ul nu răspunde la semnalele SPI.

RST → D9 (Arduino)

A0/DC → D8 (Arduino)

MOSI (Master Out Slave In) - Pin D11: Folosit pentru a transmite date de la Arduino la LCD.

De ce: MOSI (Master Out Slave In) transmite date seriale către LCD, care va folosi aceste date pentru a actualiza ecranul.

SCK (Serial Clock) - Pin D13: Folosit pentru a sincroniza transferul de date între Arduino și LCD.

De ce: SCK trimite semnale de sincronizare care sunt utilizate de LCD pentru a organiza corect datele primite pe MOSI.

Backlight LED - Pin 5V: LED-ul de fundal al ecranului LCD este alimentat cu tensiune de 5V, care este furnizată direct de la Arduino.

**Consumul de energie:** LCD-ul consumă aproximativ **20-40mA**.

---

## 4. Buton de Start/Reset
**Rol:** Butonul permite utilizatorului să înceapă un nou joc sau să reseteze jocul curent.

**Funcționare:**
- Butonul este conectat la pinul digital (**D3**) și folosește rezistența **Pull-Up internă** a Arduino pentru a detecta apăsarea.

## 3. Buzzer

**Rol:**  
Buzzerul este un dispozitiv utilizat pentru a genera sunete, oferind feedback auditiv în timpul jocului. În acest proiect, buzzerul este folosit pentru a marca evenimente importante, cum ar fi câștigarea jocului sau remiza.

**Funcționare:**  
- **Buzzer Pasiv:**  
  - Conversia semnalelor PWM în sunet este realizată prin vibrațiile diafragmei interne, controlate de frecvența semnalului PWM trimis. Aceasta permite controlul complet asupra tonului generat. 

**Interfață:**  
- **PWM (Laboratorul 3):**  
  - Un buzzer **pasiv** necesită semnale PWM pentru a produce sunete de frecvențe diferite. Funcția utilizată în Arduino pentru a genera astfel de semnale este **`tone()`**.
  - 
---
# Software Design

## Software Design

### Mediul de dezvoltare
- **Arduino IDE**: Utilizat pentru scrierea, compilarea și încărcarea codului pe microcontroller. Arduino IDE permite o integrare rapidă cu bibliotecile și perifericele utilizate.

### Biblioteci utilizate
- **Adafruit_GFX**: Bibliotecă utilizată pentru funcții grafice generale, precum desenarea liniilor, dreptunghiurilor și textului.
- **Adafruit_ST7735**: Bibliotecă pentru comunicarea cu ecranul LCD TFT bazat pe driverul ST7735. Aceasta permite desenarea pe ecran și actualizarea rapidă a conținutului.

### Funcționalități implementate
1. **Inițializare hardware**:
   - Configurarea ecranului TFT pentru afișarea informațiilor despre joc.
   - Configurarea joystick-ului pentru navigarea pe tablă.
   - Configurarea buzzerului pentru a oferi feedback auditiv.

2. **Logica jocului**:
   - **Resetează tabla de joc**: Funcția `resetBoard()` curăță tabla înainte de începerea unei noi partide.
   - **Detectarea unei victorii**: Funcția `checkWinner()` verifică dacă unul dintre jucători a câștigat după fiecare mutare.
   - **Detectarea unei remize**: Funcția `isBoardFull()` verifică dacă toate pozițiile de pe tablă sunt ocupate fără a avea un câștigător.
   - **Gestionarea scorurilor**: Scorurile pentru jucătorii `X` și `O` sunt actualizate și afișate după fiecare partidă.

3. **Afișare pe LCD**:
   - **Tabla de joc**: Funcția `displayBoard()` afișează tabla de joc pe ecran, inclusiv grila și simbolurile jucătorilor (`X` și `O`).
   - **Evidențierea poziției cursorului**: Funcția `highlightCursor()` utilizează un chenar roșu pentru a indica poziția curentă a cursorului.
   - **Mesaje despre starea jocului**: Mesaje precum „Felicitări!”, „Remiză!” sau „Apasă START pentru a începe” sunt afișate în momente relevante.

4. **Controlul mutărilor**:
   - **Joystick-ul**: Valorile citite de la joystick (pe axele X și Y) sunt utilizate pentru a deplasa cursorul pe tablă.
   - **Confirmarea mutării**: Apăsarea butonului joystick-ului confirmă poziția dorită pentru simbolul jucătorului curent (`X` sau `O`).

5. **Feedback auditiv**:
   - Funcția `tone()` controlează buzzerul pentru a emite sunete distincte în momente cheie, precum victorie, remiză sau mutare invalidă.

---

**Video**: https://youtube.com/shorts/H3dvkRSxL9o?feature=share

# Rezultate Obținute

1. **Funcționalitatea completă a jocului**: Jocul „X și O” a fost implementat cu succes, permițând doi jucători să participe în mod interactiv.
2. **Afișare vizuală eficientă**: Tabla de joc este clar afișată pe ecranul TFT, cu actualizări în timp real pentru fiecare mutare.
3. **Control intuitiv**: Navigarea pe tablă cu joystick-ul este simplă și intuitivă, iar confirmarea mutării este realizată rapid.
4. **Feedback multimodal**: Utilizarea buzzerului oferă o dimensiune auditivă suplimentară, îmbunătățind experiența utilizatorului.

---

# Concluzii

Proiectul demonstrează utilizarea eficientă a unui microcontroller pentru implementarea unui joc interactiv. Prin integrarea mai multor periferice (joystick, LCD, buzzer) și utilizarea unor tehnici precum PWM și ADC, s-au atins obiectivele stabilite. Jocul este intuitiv și oferă o experiență plăcută utilizatorilor, având un design robust și ușor de extins.

---

# Bibliografie/Resurse

1. **Bibliotecile Adafruit:**
   - [Adafruit_GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
   - [Adafruit_ST7735 Library](https://github.com/adafruit/Adafruit-ST7735-Library)
2. **Documentația Arduino:**
   - [Funcția tone()](https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/)
   - [Funcția analogRead()](https://www.arduino.cc/reference/tr/language/functions/analog-io/analogread/)
3. **Datasheet ST7735: [ST7735.PDF](https://github.com/user-attachments/files/18388526/ST7735.PDF) .**
4. **Tutoriale pentru programarea microcontrolerelor.**



