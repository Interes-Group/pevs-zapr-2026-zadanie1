# PEVŠ ZAPR 2026 – Semestrálny projekt 1

# 🚀 MISSION CONTROL – Simulátor vesmírnej výpravy

![C17](https://img.shields.io/badge/language-C17-blue)
![Termín odovzdania](https://img.shields.io/badge/termin-06.11.2026-red)

## Cieľ zadania

Cieľom zadania je implementovať konzolovú aplikáciu (CLI – command line interface) v jazyku C, ktorá simuluje
zásobovanie vesmírnej posádky počas výpravy.

Používateľ pri spustení nastaví parametre misie pomocou pomenovaných argumentov. Program potom simuluje výpravu po
jednotlivých dňoch. V štandardnom režime po každom úspešne simulovanom dni vypíše stav zásob a opýta sa používateľa, či
chce pokračovať. Režim `--non-interactive` vykoná simuláciu automaticky až do jej dokončenia alebo zlyhania. Po ukončení
program vždy vypíše záverečnú štatistiku.

Program pracuje iba s údajmi zadanými pri spustení a počas behu. Program nepoužíva ukladanie údajov do súborov ani na
externé zdroje.

Príklad spustenia:

```bash
./bin/mission --help
```

## Model vesmírnej misie

Misia má posádku, plánovaný počet dní a počiatočné zásoby jedla a kyslíka. Spotreba sa počíta podľa počtu členov
posádky:

- Každý člen posádky spotrebuje **1 jednotku jedla za deň**.
- Každý člen posádky spotrebuje **2 jednotky kyslíka za bežný deň**.
- Ak je zadaný deň so slnečnou búrkou, v tento deň každý člen posádky spotrebuje **4 jednotky kyslíka**.
- Slnečná búrka nemení spotrebu jedla.

Na začiatku každého dňa program skontroluje, či má posádka dostatok zásob na pokrytie celej dennej spotreby. Ak nie,
misia v daný deň zlyhá. Neúplný deň sa nepovažuje za odsimulovaný a jeho spotreba sa od zásob neodpočíta.

Ak sú zásoby dostatočné, program odpočíta spotrebu, označí deň za úspešne odsimulovaný a vypíše denný report. Ak po
tomto dni misia ešte nie je ukončená, program sa v interaktívnom režime opýta, či má pokračovať.

Misia sa môže skončiť jedným z nasledujúcich spôsobov:

- **Úspešne dokončená** – posádka odsimulovala všetky plánované dni.
- **Predčasne ukončená posádkou** – používateľ v interaktívnom režime zvolil, že nechce pokračovať.
- **Zlyhanie pre nedostatok zásob** – pred začiatkom dňa nebolo dostatok jedla alebo kyslíka na jeho dokončenie.

Ak sa zásoby minú presne na konci posledného úspešne odsimulovaného dňa, nejde o zlyhanie. Rozhodujúce je, či sa
podarilo dokončiť všetky plánované dni.

## Funkcionalita

Program musí:

1. Spracovať pomenované argumenty programu.
2. Overiť, či sú zadané všetky povinné argumenty a či majú platné hodnoty.
3. Simulovať misiu po jednotlivých dňoch podľa pravidiel uvedených vyššie.
4. V interaktívnom režime po každom úspešnom dni (okrem posledného plánovaného dňa) umožniť používateľovi pokračovať
   alebo simuláciu ukončiť.
5. V režime `--non-interactive` pokračovať automaticky bez čakania na vstup od používateľa.
6. Po ukončení simulácie vypísať záverečnú štatistiku.
7. Zrozumiteľne informovať používateľa o nesprávnych alebo neúplných argumentoch.

## Vstupy a argumenty

Argumenty možno uviesť v ľubovoľnom poradí. Každý argument s hodnotou musí nasledovať jeho hodnota. Prepínač
`--non-interactive` hodnotu nemá.

### Povinné argumenty

| Argument            | Popis                                      | Platné hodnoty                  |
|---------------------|--------------------------------------------|---------------------------------|
| `--crew POCET`      | Počet členov posádky.                      | Celé číslo od `1` po `100`.     |
| `--days POCET`      | Počet dní, ktoré má misia maximálne trvať. | Celé číslo od `1` po `365`.     |
| `--food MNOZSTVO`   | Počiatočná zásoba jedla v jednotkách.      | Celé číslo od `0` po `1000000`. |
| `--oxygen MNOZSTVO` | Počiatočná zásoba kyslíka v jednotkách.    | Celé číslo od `0` po `1000000`. |

### Voliteľné argumenty

| Argument            | Popis                                                                                                                                                                                                                                                                                                                                         |
|---------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `--solar-storm DEN` | Určí deň misie, počas ktorého nastane slnečná búrka. V tento deň je spotreba kyslíka dvojnásobná oproti bežnej dennej spotrebe. Hodnota musí byť celé číslo od `1` po počet plánovaných dní. Ak argument nie je zadaný, slnečná búrka nenastane. Ak je argument zadaní bez uvedenia dní, slnečná búrka nastane náhodne v jeden deň simulácie. |
| `--non-interactive` | Automaticky pokračuje po každom dni bez otázok pre používateľa. Simulácia sa ukončí po dokončení všetkých plánovaných dní alebo pri nedostatku zásob.                                                                                                                                                                                         |

### Pomocný argument

| Argument | Popis                                                                                                |
|----------|------------------------------------------------------------------------------------------------------|
| `--help` | Vypíše nápovedu s popisom programu, argumentov a ich použitia. Nápoveda musí obsahovať slovo `Help`. |

### Príklady spustenia

Zobrazenie nápovedy:

```bash
./bin/mission --help
```

Interaktívna misia:

```bash
./bin/mission --crew 2 --days 3 --food 6 --oxygen 12
```

Automatická misia bez otázok:

```bash
./bin/mission --crew 2 --days 3 --food 6 --oxygen 12 --non-interactive
```

Misia so slnečnou búrkou v druhý deň:

```bash
./bin/mission --crew 2 --days 3 --food 6 --oxygen 12 --solar-storm 2 --non-interactive
```

Misia so slnečnou búrkou v náhodný deň:

```bash
./bin/mission --crew 2 --days 3 --food 6 --oxygen 12 --solar-storm --non-interactive
```

Argumenty môžu byť uvedené v inom poradí, napríklad:

```bash
./bin/mission --non-interactive --oxygen 12 --days 3 --crew 2 --food 6
```

## Priebeh interaktívnej simulácie

Po úspešnom dokončení dňa program vypíše jeho číslo, spotrebu jedla a kyslíka a zostávajúce zásoby. Ak ešte zostávajú
plánované dni a misia nezlyhala, vypíše otázku:

```text
Pokračovať na ďalší deň? [y/n]:
```

- `y` alebo `Y` – pokračovať v simulácii.
- `n` alebo `N` – ukončiť simuláciu; jej výsledok bude **predčasne ukončená posádkou**.
- Iná odpoveď – vypísať upozornenie a otázku zopakovať.

Ak program na otázku nedostane vstup (napríklad sa ukončí vstupný stream), má bezpečne ukončiť simuláciu ako predčasne
ukončenú a vypísať záverečnú štatistiku.

Po poslednom plánovanom dni sa program už nepýta, či má pokračovať. V režime `--non-interactive` sa otázka nezobrazí ani
raz.

## Denný report a záverečná štatistika

Denný report musí obsahovať aspoň:

- číslo práve simulovaného dňa a počet plánovaných dní,
- informáciu, či v daný deň nastala slnečná búrka,
- spotrebu jedla a kyslíka v daný deň,
- zostávajúce množstvo jedla a kyslíka.

Pri nedostatku zásob program oznámi, že posádka nedokáže dokončiť nasledujúci deň, uvedie chýbajúci zdroj a následne
vypíše záverečnú štatistiku.

Záverečná štatistika musí obsahovať aspoň:

- výsledný stav misie,
- počet úspešne odsimulovaných dní a počet plánovaných dní,
- percentuálnu úspešnosť misie podľa vzorca:

```text
úspešnosť = úspešne odsimulované dni / plánované dni × 100
```

- počiatočné, spotrebované a zostávajúce množstvo jedla,
- počiatočné, spotrebované a zostávajúce množstvo kyslíka.

Spotreba sa vypočíta ako rozdiel medzi počiatočnou a zostávajúcou zásobou. Percentuálna úspešnosť sa vypisuje na dve
desatinné miesta. Pri neúspešnej misii sa percento počíta iba z celých úspešne dokončených dní.

### Ukážka výstupu

Pre príkaz:

```bash
./bin/mission --crew 2 --days 3 --food 6 --oxygen 12 --non-interactive
```

môže výstup vyzerať takto:

```text
====== RIADIACE STREDISKO ======
Posádka: 2
Plánované dni: 3
Slnečná búrka: nie
Režim: neinteraktívny
--------------------------------
DEŇ 1/3
Spotrebované jedlo: 2
Spotrebovaný kyslík: 4
Zostávajúce jedlo: 4
Zostávajúci kyslík: 8
--------------------------------
DEŇ 2/3
Spotrebované jedlo: 2
Spotrebovaný kyslík: 4
Zostávajúce jedlo: 2
Zostávajúci kyslík: 4
--------------------------------
DEŇ 3/3
Spotrebované jedlo: 2
Spotrebovaný kyslík: 4
Zostávajúce jedlo: 0
Zostávajúci kyslík: 0
================================
SÚHRN MISIE
Stav: ÚSPEŠNE DOKONČENÁ
Dokončené dni: 3/3
Úspešnosť: 100.00%
Jedlo: 6 na začiatku, 6 spotrebované, 0 zostáva
Kyslík: 12 na začiatku, 12 spotrebované, 0 zostáva
================================
```

Text výstupu programu môže byť po slovensky alebo anglicky. Nápoveda musí navyše obsahovať presné slovo `Help` alebo
`Pomoc`. Výstup musí obsahovať všetky požadované informácie; presné medzery a ozdobné oddeľovače nemusia zodpovedať
ukážke.

## Chybové stavy a validácia

Program musí zrozumiteľne oznámiť chybu a skončiť s nenulovým návratovým kódom, ak:

- chýba niektorý povinný argument alebo jeho hodnota,
- argument obsahuje hodnotu, ktorá nie je celé číslo,
- číselná hodnota je mimo povoleného rozsahu,
- `--solar-storm` označuje deň mimo plánovaného trvania misie,
- používateľ zadal neznámy argument alebo rovnaký argument viackrát.

Nedostatok zásob nie je chybou argumentov. Je to platný výsledok simulácie a program v takom prípade vypíše záverečnú
štatistiku.

## Implementácia

Program implementujte v jazyku **C 17**. Musí sa dať skompilovať štandardným kompilátorom **GCC** bez platformovo
špecifických rozšírení. Program počas simulácie nepoužíva súbory ani sieťové pripojenie.

Program rozdeľte do vlastných funkcií. Zdrojový kód musí obsahovať aspoň **5 vlastných funkcií vrátane funkcie `main`**.
Odporúčané úlohy pre samostatné funkcie:

- výpis nápovedy,
- validácia vstupných hodnôt,
- výpočet dennej spotreby,
- výpis denného reportu,
- načítanie a validácia odpovede používateľa,
- výpis záverečnej štatistiky.

Všetok zdrojový kód programu musí byť v súbore `src/main.c`. Súbory šablóny projektu potrebné na kompiláciu a testovanie
nemeňte, pokiaľ zadanie alebo vyučujúci výslovne neurčí inak.

Pri spracovaní argumentov sa môžete inšpirovať
článkom [Práca s argumentami programu v jazyku C](https://zapr.interes.group/guides/program_arguments/) na stránke
predmetu alebo priloženými materiálmi k predmetu. Môžete použiť štandardné funkcie knižnice jazyka C.

Pri implementácii si môžete pomáhať AI nástrojmi pri diskusii, hľadaní chýb a testovaní. **Je však zakázané nechať AI
priamo vygenerovať vypracovanie alebo kopírovať väčšie časti riešenia z AI či internetu.** Odovzdaný kód musí byť
výsledkom vašej vlastnej práce a vedomostí.

### Kompilácia

Z koreňového priečinka projektu skompilujte program príkazom:

```bash
mkdir -p bin
gcc -std=c17 -o bin/mission -Wall -Wextra src/main.c
```

Spustiteľný program bude v `bin/mission`.

## Automatizované testovanie

Riešenie bude overené automatizovanými testami, ktoré spustia program s rôznymi argumentmi a v prípade interaktívneho
režimu mu zadajú aj vstup. Testy budú kontrolovať najmä:

- zobrazenie nápovedy,
- správne výpočty dennej spotreby a záverečnej štatistiky,
- úspešné dokončenie misie,
- predčasné ukončenie používateľom,
- zlyhanie pri nedostatku jedla alebo kyslíka,
- správnu spotrebu kyslíka počas slnečnej búrky,
- režim `--non-interactive` bez otázok na vstup,
- chýbajúce, neplatné, duplicitné a neznáme argumenty,
- návratové kódy programu pri úspechu a pri chybe.

Výstup musí byť deterministický: pri rovnakých argumentoch a rovnakých odpovediach používateľa musí program vypísať
rovnaký výsledok.

## Hodnotenie

Zadanie je hodnotené **20 bodmi**. Nefunkčný alebo neskompilovateľný program nemôže získať body za funkcionalitu.

| Oblasť                                                          |   Body |
|-----------------------------------------------------------------|-------:|
| Kompilácia, štruktúra projektu a spustiteľnosť                  |      2 |
| Spracovanie argumentov, `--help` a validácia                    |      4 |
| Správna simulácia dní, spotreby a slnečnej búrky                |      5 |
| Interaktívne pokračovanie/ukončenie a `--non-interactive` režim |      3 |
| Záverečná štatistika a správne výsledné stavy                   |      3 |
| Rozdelenie programu do funkcií, čitateľnosť a komunikácia chýb  |      3 |
| **Spolu**                                                       | **20** |

Pri hodnotení sa bude prihliadať aj na:

- prácu s premennými, cyklami a riadením toku programu,
- správne použitie vlastných funkcií,
- spracovanie textových a číselných argumentov,
- ošetrenie hraničných prípadov a neplatného vstupu,
- dodržanie špecifikácie a formátu výstupu.

## Získanie šablóny projektu

Zadanie je dostupné ako **GitHub template repository**. Na začiatku si vytvorte vlastnú kópiu pomocou funkcie GitHub
**Use this template**, prípadne si projekt stiahnite ako ZIP.

**Odkaz na template
repository:** [https://github.com/Interes-Group/pevs-zapr-2026-zadanie1](https://github.com/Interes-Group/pevs-zapr-2026-zadanie1)

Git môžete pri vypracovaní používať na priebežné ukladanie zmien, ale odovzdáva sa ZIP archív projektu podľa
nasledujúcej časti.

## Odovzdanie

Odovzdáva sa **celý projekt ako ZIP archív**, nie samostatný súbor `main.c`. Odovzdanie prebieha cez zadanie
(*Assignment*) v Microsoft Teams.

1. Skontrolujte, že projekt obsahuje všetky potrebné súbory zo šablóny, najmä `src/main.c` a súbory potrebné na
   kompiláciu.
2. Zabaľte celý priečinok projektu do ZIP archívu. Odporúčaný názov:

   ```text
   priezvisko_meno_login_zapr1.zip
   ```

3. Prihláste sa do Microsoft Teams **školským účtom** a otvorte zadanie v tíme predmetu.
4. V časti svojej práce vyberte **+ Add work** (Pridať prácu) a priložte ZIP archív.
5. Stlačte **Turn in** (Odovzdať) a skontrolujte, že sa stav zadania zmenil na odovzdané.

Odovzdanie je individuálne: každý študent priloží svoj vlastný ZIP cez svoje konto. Súbor neodovzdávajte do
spoločného kanála ani do záložky Súbory tímu. Odovzdanie samotného zdrojového súboru sa nepovažuje za splnenie zadania.

**Termín odovzdania:** `06.11.2026 23:59`

V prípade otázok alebo technických problémov kontaktujte vyučujúceho cez komunikačné kanály predmetu.
