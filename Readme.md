# AES-Implementierungsprojekt (Bewertete Aufgabe)

## Überblick

In diesem Projekt sollen Sie den Advanced Encryption Standard (AES) implementieren, einen symmetrischen Blockchiffre, der von NIST standardisiert wurde. AES arbeitet mit 128-Bit-Blöcken und unterstützt Schlüssellängen von 128, 192 oder 256 Bits.

## Anforderungen

- Implementieren Sie den AES-Verschlüsselungs- und Entschlüsselungsalgorithmus
- Stellen Sie sicher, dass Ihre Implementierung in der bereitgestellten Vagrant-Umgebung lauffähig ist
- Bestehen Sie alle vorgegebenen Testfälle
- Halten Sie sich an die Funktionsdeklarationen in der bereitgestellten Header-Datei

## Erste Schritte

### 1. Repository klonen

```console
$ git clone https://github.com/bladewing/infosec-uebungen-graded-01.git
$ cd infosec-uebungen-graded-01
```

### 2. Projektstruktur

- `/code/src/aes.h`: Enthält alle Funktionsdeklarationen, die Sie implementieren müssen
- `/code/src/aes.c`: Enthält Dummy-Implementierungen und die S-Box-Tabellen
- `/code/tests/`: Enthält Testdateien für jede AES-Funktion

### 3. Implementierungsdetails

- Die Datei `aes.h` enthält Funktionsdeklarationen mit Kommentaren, die das erwartete Verhalten beschreiben
- Die Datei `aes.c` enthält:
  - Leere Implementierungen aller erforderlichen Funktionen
  - Die **S-Box** und **inverse S-Box** Tabellen, die Sie für Ihre Implementierung benötigen
- Ihre Aufgabe besteht darin, jede Funktion gemäß der AES-Spezifikation zu implementieren

## Kompilieren und Testen

### Verwendung der Vagrant-Umgebung (Empfohlen)

Die bereitgestellte Vagrant-Box verfügt bereits über alle notwendigen Abhängigkeiten.

```console
$ vagrant up
$ vagrant ssh
$ cd /vagrant/code
```

### Build-Anweisungen

Navigieren Sie zum Verzeichnis `code` und führen Sie folgende Befehle aus:

1. Konfigurieren Sie das CMake-Projekt:

   ```console
   $ cmake .
   ```

2. Kompilieren Sie das Projekt:

   ```console
   $ cmake --build .
   ```

3. Führen Sie die Tests aus:
   ```console
   $ ctest --output-on-failure
   ```
   Dieser Befehl zeigt detaillierte Ausgaben für fehlgeschlagene Tests an.

### Fehlersuche bei Tests

Bei fehlgeschlagenen Tests:

1. Überprüfen Sie die spezifische Testausgabe, um Hinweise darauf zu erhalten, welcher Aspekt Ihrer Implementierung fehlerhaft ist
2. Sehen Sie sich die Testdatei in `/code/tests/` an, um zu verstehen, was der Test überprüft
3. Verwenden Sie bei Bedarf Debugging-Tools wie `gdb`

## Implementierungstipps

1. **Einfach beginnen**: Starten Sie mit grundlegenden Funktionen wie S-Box-Lookups und Key-Scheduling
2. **Schrittweiser Ansatz**: Implementieren und testen Sie eine Funktion nach der anderen
3. **Debugging**: Die Testdateien können Ihnen helfen, die erwarteten Eingabe-/Ausgabebeziehungen zu verstehen
4. **Speicherverwaltung**: Achten Sie sorgfältig auf Array-Indizes und Puffergrößen
5. **AES-Struktur**: Denken Sie an die Hauptoperationen: SubBytes, ShiftRows, MixColumns und AddRoundKey

## Abgaberichtlinien

- Reichen Sie Ihre Lösung als ZIP-Datei auf der OPAL-Kursplattform ein
- Behalten Sie die ursprüngliche Projektstruktur bei
- Sowohl C- als auch C++-Implementierungen werden akzeptiert
- Stellen Sie sicher, dass Ihr Code in der Vagrant-Umgebung kompiliert und alle Tests besteht

## Zusätzliche Ressourcen

- **Kursbuch**: Verwenden Sie die Kapitel zur AES-Implementierung im bereitgestellten Kursbuch
- **Interaktives Tutorial**: [CrypTool AES Step-by-Step](https://www.cryptool.org/de/cto/aes-step-by-step) - Visualisieren Sie den AES-Algorithmus und debuggen Sie Ihre Implementierung
- **NIST-Standard**: [FIPS 197](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf) - Offizielle AES-Spezifikation
- **Online-Referenzen**:
  - [Rijndael Animation](https://formaestudio.com/rijndaelinspector/archivos/Rijndael_Animation_v4_eng.swf) - Visuelle Animation des AES-Prozesses
  - [AES Wikipedia](https://de.wikipedia.org/wiki/Advanced_Encryption_Standard) - Überblick über den Algorithmus

## Typische Fallstricke

- Verwechslung der Zeilen- und Spaltenreihenfolge in der State-Matrix
- Fehlerhafte Implementierung des MixColumns-Schritts
- Fehler im Key-Expansion-Algorithmus
- Off-by-one-Fehler bei der Rundenzählung
- Probleme mit der Byte-Reihenfolge

Viel Erfolg bei Ihrer Implementierung!
