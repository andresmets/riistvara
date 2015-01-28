ParkimisMaja - Praktikum 2.

Rühma koosseis:
Toomas Juhkov
Andres Mets
Raul Valge

Programm loendab autosid, mis sisenevad ja väljuvad parkimismajast ning kuvab vabade parkimiskohtade arvu. Parkimismaja mahutavus on 250. Kui sensori ette jääb seisma mõni auto (klahvivajutus), ei loendata teda enne kui sensor registreerib lahkumise (klahvivajutus välja). Kui autode arv parkimismajas ületab 250, siis kuvatakse endiselt 0 vaba kohta (counter loendab autosid edasi ning vabade kohtade muutumine kuval taastub, kui piisav hulk autosid on väljunud). Kui loendur läheb negatiivseks (teoreetiliselt võimatu, kuna sissesõitvad sõidukid loendatakse) siis kuvatakse endiselt 250 vaba kohta.

Sõiduki loendamiseks vajuta 'A' klahvi auto väljumise registreerimiseks ning 'E' klahvi auto sisenemiseks. Sisenemine/väljumine registreeritakse teistkordse klahvivajutuse järel. "Liiga kiired vajutused" pole soovitavad, kuna simulaatori aegluse tõttu võib nii mõni vajutus jääda registreerimata - reaalses elus probleemi pole. 