# CAN Bus Simulator (C++)

Un simulator al protocolului CAN Bus (Controller Area Network) implementat în C++, care demonstrează comunicarea între module electronice (ECU-uri) dintr-un vehicul modern.

## Ce este CAN Bus

CAN Bus este protocolul de comunicare folosit în toate vehiculele moderne pentru a permite modulelor electronice (ECU-uri) să comunice între ele pe o magistrală comună, fără un computer central. Fiecare modul "ascultă" toate mesajele de pe magistrală și le procesează doar pe cele relevante pentru el.

## Arhitectura proiectului

```
CANBusSimulator/
├── CMakeLists.txt
├── CANMessage.h / .cpp       # Structura unui mesaj CAN (id, data, sender)
├── CANNode.h                 # Clasa abstracta de baza pentru orice ECU
├── CanBus.h / .cpp           # Magistrala — distribuie mesaje la toate nodurile
├── EngineECU.h / .cpp        # ECU motor — trimite RPM si temperatura
├── ABSNode.h / .cpp          # ECU ABS — trimite starea sistemului de franare
├── Dashboard.h / .cpp        # Dashboard — primeste si afiseaza toate datele
└── CANBusSimulator.cpp       # main() — scenariul de simulare
```

## Cum functioneaza

Sistemul urmeaza un flux simplu de tip broadcast:

```
EngineECU::sendData()
        ↓
CanBus::sendMessage()     ← magistrala primeste mesajul
        ↓
┌───────────────────────────────┐
↓               ↓               ↓
EngineECU    ABSNode       Dashboard
receive()    receive()     receive()
(filtreaza   (filtreaza    (afiseaza
dupa ID)     dupa ID)      tot)
```

Fiecare nod primește **toate** mesajele de pe magistrală, dar reacționează doar la cele cu ID-ul relevant pentru el.

## Concepte OOP demonstrate

| Concept | Unde apare |
|---|---|
| **Abstractizare** | `CANNode` — clasă abstractă cu metode virtuale pure |
| **Moștenire** | `EngineECU`, `ABSNode`, `Dashboard` derivă din `CANNode` |
| **Polimorfism** | `CanBus` apelează `receiveMessage()` pe pointeri `CANNode*` — fiecare nod reacționează diferit |
| **Încapsulare** | Date private în `CANMessage`, accesate doar prin getteri `const` |

## Structura unui mesaj CAN

```cpp
CANMessage(int id, std::vector<uint8_t> data, std::string senderName);
```

- **ID** — identifică tipul de date (ex: `0x100` = date motor, `0x200` = date ABS)
- **Data** — până la 8 bytes de date brute (conform standardului CAN)
- **SenderName** — numele nodului care a trimis mesajul

## Nodurile simulate

### EngineECU (ID: 0x100)
Trimite turația motorului (RPM) și temperatura, encodate în 4 bytes:
```
[RPM_high][RPM_low][TEMP_high][TEMP_low]
```
Ascultă mesajele ABS (ID 0x200) și reacționează la ele.

### ABSNode (ID: 0x200)
Trimite starea sistemului ABS (activ/inactiv) într-un singur byte.
Ascultă mesajele motorului (ID 0x100) și actualizează starea internă.

### Dashboard
Ascultă **toate** mesajele și decodează datele pentru afișare:
- ID 0x100 → afișează RPM și temperatură
- ID 0x200 → afișează starea ABS

## Output exemplu

```
=== EngineECU trimite date ===
[ABSNode] Mesaj primit de la: EngineECU, ID: 256, ABS activ: Da
[Dashboard] Mesaj primit de la: EngineECU, RPM: 3500, Temp: 90.5C

=== ABSNode trimite date ===
[EngineECU] Mesaj primit de la: ABSNode, ID: 512
[Dashboard] Mesaj primit de la: ABSNode, ID: 512, ABS activ: Da
```

## Tehnologii folosite

- **C++17**
- **STL** — `std::vector`, `std::string`, `std::uint8_t`
- **CMake** — sistem de build
- **OOP** — abstractizare, moștenire, polimorfism, încapsulare

## Compilare

### Cerințe
- Visual Studio 2022 cu suport CMake
- sau orice compilator C++17 (g++, clang++)

### Build
```powershell
mkdir build && cd build
cmake ..
cmake --build .
```

## Extensii viitoare

- `CVNode` — nod care integrează sistemul de detecție a somnolenței și trimite starea șoferului pe bus
- Buffer intern în `CanBus` cu `std::queue` pentru procesare asincronă
- Logging într-un fișier CSV cu istoricul mesajelor
- Simulare delay între mesaje (timing real CAN)

## De ce acest proiect

Proiectul simulează arhitectura internă a rețelei CAN dintr-un vehicul modern — exact tipul de sistem cu care lucrează inginerii software la companii precum Continental, Aptiv sau Bosch. Demonstrează înțelegerea protocoalelor de comunicare automotive și aplicarea principiilor OOP în context embedded/automotive.
