# ortoYunMini - InternetOfGreens

## Intro

L'ortoYunMini è la verisone mini IoG ( Internet of Green ) di un orto idroponico gestito dall'Arduino Yùn.
La versione corrente è semplificazione della verione ortoYun con maggiori dimansioni, sensori e funzionalità.

## Caratteristiche/Obiettivi del progetto:

- Ora corrente sincronizzata via ntpd Linux;
- Dati sensori ambiente raccolti da un DHT11
- Collezione dati su SD Card come datalogging;
- Accesso e Visaulizzazione dei dati via web;

## Sensori/Attuatori presenti:

- n.1 sensore DHT11 per rilevare Temperatura ed Umidità dell'ambiente
- n.4 relay a 220v per il controllo di n.2 serie di luci, n.1 pompe e n.1 sistema di fertilizzazione con pompa controllata da relay;

## Valori monitorati direttamente da sensori connessi ad Arduno Yùn:

- Temperatura ambiente
- Umidità ambiente

## Attività automatiche presenti:

- Gestione cicli di accensione/spegnimento lampade;
- Gestione cicli di irrigazione;
- Gestione ciclo di fertilizzazione dell'acqua;

## Prerequisiti - Package Required

opkg update
opkg install php5 php5-cgi php5-cli php5-mod-curl php5-mod-json zoneinfo-core zoneinfo-europe
