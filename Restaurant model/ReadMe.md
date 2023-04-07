# 3. Lab. darbas.

## 2. Savitarnos kavinė (ADT: stekas, ilgas sveikas skaičius). 

 Procesas: klientai ateina į kavinę pasiima lėkštę iš stirtos, įsideda maisto, pavalgo, nešvarias lėkštes deda į indų plovimo mašiną, kuri švarias lėkštes deda atgal į stirtą. Tikslas: patyrinėti, kiek lėkščių reikėtų įsigyti kavinei (pageidautina, kad apie 10 procentų lėkščių būtų nenaudojamos, nes šiame modelyje nenumatyta sudaužimo galimybė). Pradiniai duomenys: lėkščių skaičius, kliento pavalgymo laikas, kliento atvykimo tikimybė (galima realizacija: generuojamas atsitiktinis skaičius ir tikrinama, ar jis tenkina tam tikrą sąlygą), lėkštės plovimo laikas (indų plovimo mašinos pajėgumai neriboti, t.y. plaunamų lėkščių skaičius neturi įtakos lėkštės išplovimo laikui). Rezultatai: statistika kažkuriam  (vartotojo nurodytam) laiko momentui, pavyzdžiui, vidutinis ir minimalus švarių lėkščių skaičius stirtoje (turėtų būti numatyta ir išskirtinė situacija; su pateiktais pradiniais duomenimis susidaro situacija, kad atėjęs klientas neranda švarios lėkštės).

## Programos paleidimas
Programa paleidžiama per `go.cmd` arba per `command line`. Programa turi du režimus
1. Atsitiktinių duomenų režimas - programa atsitiktinai sugeneruos pradinius duomenis, kad tai aktyvuoti, reikia paleisti programa per `command line` su papildoma komanda `r` arba `randomised`, pvz.: ``main r`` arba paleidus per `goR.cmd` .
2. Paleidus programa per `go.cmd` arba per `command line` su parametru `fixed` arba `f`  programa paleidžiama su neatsitiktiniais parametrais iš failo `parameters.txt`. Paleidmo  per `command line` pvz.: `main fixed`


## Failų aprašymai
`main.c` -- pagrindinis programos failas.

`stack.c` -- failas kuris laiko visas steko funkcijas.

`stack.h` --failas kuris laiko steko funkcijų prototipus.

`BigInteger.c` -- failas kuris laiko visas ilgo sveiko skaičiaus funkcijas.

`BigInteger.h` --failas kuris laiko ilgo sveiko skaičiaus funkcijų prototipus.

`additionalFunctions.c` -- failas kuris laiko visas papildomai pasirašytas funkcijas.

`Go.cmd` -- komandų failas main sutransliavimui ir įvykdymui.

`GoR.cmd` -- komandų failas main sutransliavimui ir įvykdymui su atsitiktiniais skaičiais.

`Makefile` -- transliavimo make failas.

`parameters.txt` -- parametrų failas, kuriame laikomi pradiniai duomenys: lėkščių skaičius, modeliavimo laikas, maksimalus valgymo laikas, minimalus valgymo laikas, valymo laikas, kliento atėjimo tikimybė (%).

`log.txt` -- programai baigius dirbti, sukuriamas log.txt failas, kuriame galima pažiūrėti kas modeliavimo programoje vyko kiekvieną laiko vienetą.



