# snek.io

## Wstęp
Snek.io to wieloosobowa gra czasu rzeczywistego inspirowana grami Snake i Slither.io. Podobnie jak w tych grach, rozgrywka snek.io skupia się na sterowaniu wężami na dwuwymiarowej planszy.

## Konfiguracja
Parametry konfigurowalne:
- adres serwera (dla klienta) oraz port serwera (dla klienta i serwera)
- przyciski sterowania (dla klienta)
- domyślny nick i kolor
- otrzymywanie powiadomień o dołączaniu i wychodzeniu graczy z gry

## Gameplay
1. Gracz łączy się do serwera i wysyła swój nick (jeśli nick jest już zajęty, serwer prosi o podanie innego nicku) i kolor swojego węża.
2. Gracz po wybraniu nicku trafia na planszę.
3. Gracz znajduje się na planszy w jednej z trzech sytuacji:
- Jeżeli jest jedynym graczem na planszy, oczekuje na drugiego gracza. Przez ten czas, nie może się poruszać, a na samej planszy nie są wykonywane żadne zmiany.
- Jeżeli jest drugim graczem, rozpoczyna się odliczanie, po którym rozpoczyna się gra.
- Jeśli w grze znajdowało się już co najmniej dwoje graczy, nowy gracz dołącza do gry od razu. Wszyscy pozostali gracze na planszy otrzymują informację o dołączeniu gracza.
4. Gracze poruszają się po planszy, sterując swoimi wężami za pomocą klawiatury. Wąż może nachodzić na miejsca, w których znajduje się już inna część jego ciała.
5. Na planszy pojawia się jedzenie.
6. Gracze mogą zjadać jedzenie, co zwiększa wielkość (długość i grubość) ich węża.
7. Ilość jedzenia utrzymywana jest na stałym poziomie, zależnym od liczby graczy na planszy. Gdy wąż zje jedzenie, w losowym miejscu pojawia się nowe.
8. Za pomocą specjalnego przycisku, można korzystać z przyspieszenia, które sprawia, że wąż porusza się znacznie szybciej, ale zmniejsza się i pozostawia za sobą jedzenie. Szybkość utraty masy jest zależna od wielkości węża. Przyspieszenie trwa do momentu puszczenia przycisku, lub upłynięcia pewnego czasu.
9. Gracze mogą zderzać się ze sobą:
- Jeśli gracz zderzy się z wężem innego gracza, ginie. Jeśli trafił w jego głowę, ginie również ten drugi gracz.
- Jeśli gracz zderzy się z krawędzią świata, ginie.
10. Gdy gracz ginie, jego wąż znika z planszy.
11. Gracz który przegrał, otrzymuje ekran końca gry z informacją o tym, ile punktów zdobył, jak długo przeżył, ile zabił innych graczy i które miejsce w rankingu zajął w każdej z tych kategorii. Dostaje możliwosć ponownego wyboru nicku i koloru węża oraz wejścia do gry.
12. Gracz może wyjść z gry w dowolnym momencie. W takiej sytuacji, jego wąż znika z planszy.
13. Wąż który zniknął z planszy (w dowolny sposób), pozostawia za sobą jedzenie, którego ilość jest zależna od wielkości, jaką osiągnął.

## Obsługa nadzwyczajnego przerwania/zakończenia rozgrywki
1. Wąż gracza, który stracił połączenie, traktowany jest identycznie jak inne węże, co oznacza, że może zbierać jedzenie lub zginąć.
2. Przerwanie połączenia:
- W przypadku zerwania połączenia, z perspektywy serwera wąż utrzymuje swój kierunek i prędkość do momentu przywrócenia połączenia, lub upłynięcia pewnego czasu A (około sekundę lub mniej) lub czasu B (kilka/kilkanaście sekund).
- Z perspektywy klienta, wąż nadal reaguje na sterowanie.
3. Przywrócenie połączenia:
- Po przywróceniu połączenia w ciągu czasu A, jeśli jego wąż nie zginął, gracz odzyskuje nad nim kontrolę i kontynuuje rozgrywkę od miejsca, które wynika z pozycji utrzymywanej przez klienta.
- Po przywróceniu połączenia w ciągu czasu B, jeśli jego wąż nie zginął, gracz odzyskuje nad nim kontrolę i kontynuuje rozgrywkę od miejsca, które wynika z jego ruchu obliczanego przez serwer.
- Jeśli gracz nie przywróci połączenia w ciągu czasu B, serwer uznaje, że gracz zakończył grę i usuwa jego węża z planszy.
4. Jeśli gracz zamknie okno podczas gry, klient uznaje, że gracz zakończył grę. Serwer usuwa jego węża z planszy.

## Budowanie i uruchamianie
1. Wymagania
- System operacyjny Linux lub macOS
- Biblioteka SFML (w systemie Linux można ją zainstalować za pomocą polecenia: `sudo apt-get install libsfml-dev`, a w systemie macOS: `brew install sfml`)
- Kompilator GCC lub Clang obsługujący standard C++23
2. Instalacja - niniejsze repozytorium należy pobrać lub sklonować poleceniem `git clone`.
3. Budowanie - w katalogu głównym repozytorium należy wykonać polecenie `make client` lub `make server`.
4. Po wykonaniu kompilacji, w katalogu `build` znajdują się wyniki kompilacji oraz pliki konfiguracyjne.
5. Uruchamianie - w katalogu głównym repozytorium należy wykonać polecenie `make run-client` lub `make run-server`. Polecenia te wykonują także kompilację jeśli nie została jeszcze wykonana.