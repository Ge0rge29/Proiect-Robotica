# Tic-Tac-Toe Game

# Introducere

Acest proiect are ca scop dezvoltarea unui sistem interactiv pentru controlul unui joc.
Proiectul permite utilizatorului să joace clasicul joc de X și O pe un ecran LCD, navigând între pozițiile de pe tablă cu ajutorul unui joystick. După plasarea simbolurilor (X sau O), ecranul afișează mutările, iar la final, declară câștigătorul sau remiza. Scopul jocului e acela de a obtine 3 semne la fel pe 3 casete asezate orizontal, vetical sau pe diagonala.

# Descriere generală

![Screenshot 2024-12-15 170358](https://github.com/user-attachments/assets/10d03291-4875-4780-a525-f9c9b0b1c29c)



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

# Bill of Materials (BOM) pentru Proiectul X și O cu Arduino

| Nr. | Componente/Module       | Descriere                                         | Cantitate | Achiziționat de la               | Link de Achiziție / Datasheet                                      |
|-----|-------------------------|---------------------------------------------------|-----------|---------------------------------|-------------------------------------------------------------------|
| 1   | **Arduino Uno**          | Microcontroller principal                        | 1         | Facultate  |  |
| 2   | **Joystick**             | Joystick 2 axe cu buton integrat                  | 1         | Facultate |     |
| 3   | **LCD 128x160 SPI**      | Ecran LCD cu 128x160 px și interfață SPI          | 1         | optimus digital.ro | https://www.optimusdigital.ro/en/lcds/12392-modul-lcd-de-18-cu-spi-i-controller-st7735-128x160-px.html?gad_source=1&gclid=CjwKCAiAmfq6BhAsEiwAX1jsZwh_IV_gGrMe_jemneTNzMCyaAKME1BIM87AnANaRKASR271lopC7xoCodgQAvD_BwE|
| 4   | **Buton Push**           | Buton tactil pentru start/reset joc               | 1         | Facultate   |            |
| 5   | **Rezistență 220Ω**      | Rezistență pentru buton și LED                    | -         | Facultate   |            |
| 6   | **Fire de conexiune**    | Fire pentru conexiuni între module și Arduino     | -     | Facultate   |                                                                 |
| 7   | **Breadboard**           | Placă de testare pentru prototipuri               | 1         | Facultate   |    |

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

**Interfețe:**
- Butonul este conectat la un pin digital (**D3**) și folosește rezistența **Pull-Up internă** a Arduino pentru a detecta apăsarea.


# Software Design

## Software Design

### Mediul de dezvoltare
- **Arduino IDE**: Utilizat pentru scrierea, compilarea și încărcarea codului pe microcontroller.

### Biblioteci utilizate
- **LiquidCrystal_I2C**: Pentru comunicarea cu ecranul LCD prin protocolul I2C.

### Funcționalități implementate
1. **Inițializare hardware**:
   - Configurarea joystick-ului și a ecranului LCD.

2. **Logica jocului**:
   - Validarea mutărilor efectuate.
   - Detectarea unei victorii sau a unei remize.

3. **Afișare pe LCD**:
   - Actualizarea tabloului de joc după fiecare mutare.
   - Afișarea mesajelor despre starea jocului (victorie, remiză).

4. **Controlul mutărilor**:
   - Jucătorii utilizează joystick-ul pentru a naviga pe tablă.
   - Confirmarea mutării prin apăsarea butonului.
  
 # Rezultate Obținute

 # Concluzii

 # Bibliografie/Resurse


