# Tic-Tac-Toe Game

# Introducere

Acest proiect are ca scop dezvoltarea unui sistem interactiv pentru controlul unui joc.
Proiectul permite utilizatorului să joace clasicul joc de X și O pe un ecran LCD, navigând între pozițiile de pe tablă cu ajutorul unui joystick. După plasarea simbolurilor (X sau O), ecranul afișează mutările, iar la final, declară câștigătorul sau remiza. Scopul jocului e acela de a obtine 3 semne la fel pe 3 casete asezate orizontal, vetical sau pe diagonala.

# Descriere generală

![Untitled Diagram drawio](https://github.com/user-attachments/assets/ce33b2aa-4faa-4ba8-8934-0709f6315798)


În cadrul acestui proiect, doi jucători vor folosi, pe rând, joystick-ul pentru a naviga pe o tablă de joc. Prin apăsarea butonului de pe joystick, aceștia confirmă mutarea, iar dispozitivul va atribui automat simbolul corespunzător jucătorului activ, în funcție de numărul rundei. După fiecare mutare, sistemul verifică dacă există o combinație câștigătoare. Dacă nu se identifică un câștigător și nu mai există spații libere pe tablă, partida se încheie cu o remiză. La final, un mesaj afișează rezultatul: victoria jucătorului 1 sau 2, ori remiza, în funcție de situație.

# Hardware Design

## Lista de piese

- **Microcontroller:** Arduino Uno 
- **Joystick**
- **Ecran LCD:** LCD 128x160 cu SPI
- **Fire de conexiune** 
- **Breadboard**
- **Buton de start** 

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


