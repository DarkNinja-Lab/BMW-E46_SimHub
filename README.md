# SHCustomProtocol – Integrations-Layer für SimHub, K-Bus und CAN

Dieses Projekt liefert eine schlanke Brücke zwischen SimHub und einem BMW-Cluster über CAN-Bus und K-Bus. Der Code übernimmt das Routing von Game-Telemetry, normt sie auf Cluster-relevante CAN-Frames und steuert diverse Statusindikatoren sowie Backlight-Logiken. Ziel: stabile Runtime, saubere Signalketten und kein Overhead.

## Purpose

Die Klasse `SHCustomProtocol` nimmt SimHub-Daten entgegen, verarbeitet sie in Echtzeit und verteilt sie auf:

- **CAN-Bus (MCP2515)**  
  Drehzahl, Geschwindigkeit, Temperatur, Warnleuchten, Getriebe, DSC/ABS etc.
- **K-Bus**  
  Blinker, Lichtlogik, High/Lowbeam, Nebel und andere LightBytes.
- **Hardware-Outputs**  
  ABS-LED, Handbremse, Cluster-Backlight inkl. Hardware-Schalteroptionen.
- **Akustik-Speedometer**  
  Tachoansteuerung über Frequenzsignal (Piezo / Stepper-Mod).

## Key Features

- Vollständige SimHub-Custom-Protocol-Implementierung  
- Game-abhängige Verarbeitungslogik (ETS2/ATS, Assetto Corsa, pCars, FH5 …)  
- CAN-Frames mit sauberem Payload-Mapping  
- K-Bus-Telegramme inkl. ISO-Checksum  
- Mehrstufige Backlight-Strategie (Ingame / Hardware / Always-On)  
- Gear-Encoding für AT-Anzeige  
- Abstrakte Hilfsfunktionen: `CanSend()`, `sendKbus()`, `Speedometer()`  

## Architekturüberblick

**Setup-Phase**  
- Initialisiert alle Pins  
- Startet K-Bus (Serial2, 9600 8E1)  
- Initialisiert MCP2515 @ 500 kbps  

**Read-Phase**  
- Liest das komplette SimHub-Payload-Paket in einer festen Reihenfolge  
- Zero-Delay, keine blockierenden Aufrufe  

**Loop-Phase**  
- Game-abhängiges Mapping  
- Generiert CAN-Nachrichten (RPM, Temp, Warnungen, AT-Display)  
- Erzeugt K-Bus-Pakete (LightBytes)  
- Steuert physische Outputs  
- Kümmert sich um das akustische Tachosignal  

**Idle-Phase**  
- Muss sauber bleiben, um Durchsatz nicht zu killen  

## Inbetriebnahme

1. **MCP2515 anschließen** (SPI, CS auf Pin 9)  
2. **K-Bus** an `Serial2` hängen  
3. **SimHub** → Custom Serial Device → Protokoll gemäß Code-Reihenfolge konfigurieren  
4. **Game-Auswahl** erfolgt via SimHub-String (`Game`)  
5. Auf korrekte Versorgung des BMW-Clusters achten (12 V, Massepotenzial sauber halten)

## Anpassungen

- `MaxRPM` für Cluster-Skalierung anpassen  
- Hardware-Pins nach Bedarf ändern  
- LightByte-Mapping bei Sonderumbauten erweitern  
- Zusätzliche CAN-Frames via `CanSend()` implementieren  

## Disclaimer

Das Setup erwartet saubere Bus-Topologien und stabile Spannungsversorgung. CAN-/K-Bus-Fehler führen sonst zu unvorhersehbaren Effekten im Kombiinstrument. Deployment erfolgt auf eigene Verantwortung.

---

Wenn du willst, baue ich dir auch eine verkürzte, eine englische oder eine endnutzerfreundliche Variante.
