# Arduino Pendel

Voorbeeld van een pendelautomaat op basis van een Arduino Micro. De opzet bestaat uit een Arduino Micro, een L298N-bordje, en 2 sensoren.

Er wordt tussen 2 stations gependeld, station A en B. Er wordt eerst 2 seconden gewacht. Hierna wordt binnen 2,5 seconden aangezet naar (bijna) volle snelheid. Wanneer de trein op snelheid is, wordt er gewacht totdat de sensor bij station B wordt geactiveerd. 
Wanneer dit gebeurt, remt de trein binnen 2,5 seconden af. Er wordt van richting veranderd, 2 seconden gewacht, en het eerdergenoemde proces wordt in de tegenovergestelde richting herhaald.

Om de richting om te keren, worden 2 pinnen gebruikt, welke aangesloten worden op IN1 en IN2 van de L298N. Voor het optrekken en afremmen wordt een PWM-sturing gebruikt, deze komt uit pin 9 van de Arduino, en wordt aangesloten op pin ENA van de L298N.

Het aansluitschema is hieronder weergegeven:

![Overzicht drawio (1)](https://user-images.githubusercontent.com/105547245/168430324-600f108f-6d3c-446d-8fce-a3e13f38e61f.png)

Dit is een eenvoudig voorbeeldje, je kunt natuurlijk ook altijd grapjes uithalen zoals bijvoorbeeld kruisende trams die op elkaar wachten. Mocht er iets niet kloppen, of is er iets onduidelijk, laat het vooral weten!
