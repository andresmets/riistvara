ParkimisMaja - Praktikum 2.

R�hma koosseis:
Toomas Juhkov
Andres Mets
Raul Valge

Programm loendab autosid, mis sisenevad ja v�ljuvad parkimismajast ning kuvab vabade parkimiskohtade arvu. Parkimismaja mahutavus on 250. Kui sensori ette j��b seisma m�ni auto (klahvivajutus), ei loendata teda enne kui sensor registreerib lahkumise (klahvivajutus v�lja). Kui autode arv parkimismajas �letab 250, siis kuvatakse endiselt 0 vaba kohta (counter loendab autosid edasi ning vabade kohtade muutumine kuval taastub, kui piisav hulk autosid on v�ljunud). Kui loendur l�heb negatiivseks (teoreetiliselt v�imatu, kuna sisses�itvad s�idukid loendatakse) siis kuvatakse endiselt 250 vaba kohta.

S�iduki loendamiseks vajuta 'A' klahvi auto v�ljumise registreerimiseks ning 'E' klahvi auto sisenemiseks. Sisenemine/v�ljumine registreeritakse teistkordse klahvivajutuse j�rel. "Liiga kiired vajutused" pole soovitavad, kuna simulaatori aegluse t�ttu v�ib nii m�ni vajutus j��da registreerimata - reaalses elus probleemi pole. 