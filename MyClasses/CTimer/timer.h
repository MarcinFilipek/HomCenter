#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

/**
 *     \brief    Timer
 *     \version  2.0.0
 *     \author   fabia
 *     
 *     Inicjalizacja
 *     =============
 *
 *     W swoim projekcie utwórz zmienną (tick) typu uint32_t, która będzie inkrementowana 1000 razy na sekundę.
 *     Przygotuj też statyczny lub globalny getter, ktory zwraca aktualną wartość tick'a. Jeśli mikrokontroler
 *     jest mniej niz 32-bitowy (atmega), getter powinien na czas odczytu wstrzymać przerwanie,
 *     w którym tick jest inkrementowany (albo po prostu wszystkie przerwania).
 *     Inicjalizacja polega na wywołaniu funkcji statycznej CTimer::classInit1000(uint32_t (*getterTick1000)())
 *     z getterem jako argumentem. Od tego momentu obiekty CTimer'a mogą już odmierzać czas.
 *
 *     Działanie
 *     =========
 *     Jednostkę odmierzania czasu można podać w konstruktorze lub zmienić później.
 *
 *     Funkcje start(uint32_t x), startAligned(uint32_t x), startStrictAligned(uint32_t x) uruchamiają timer
 *     w trybie downcounter'a. Timer zostaje włączony (isTurnedOn() == true), licznik timer zostaje ustawiony
 *     na x jednostek czasu i zmniejsza się aż do osiągnięcia 0. Osiągnięcie zera (isZero() == true) oznacza,
 *     że odmierzany czas upłynął (isElapsed() == true), ale timer wciąż uznajemy za włączony (isTurnedOn() == true).
 *     Zawsze możemy:
 *       - rozpocząć nowy pomiar jedną z funkcji _start_
 *       - wyłączyć timer funkcją turnOff(). Wtedy isTurnedOn() == false, isElapsed() == false.
 *       
 *     Czasami potrzebne jest rozróżnienie między dwoma sytuacjami:
 *       1. nie wykonano jeszcze pomiaru (isZero() == true, isTurnedOn() == false, isElapsed() == false) 
 *       2. zakończono odmierzanie czasu (isZero() == true, isTurnedOn() == true, isElapsed() == true)
 *     
 *     Wtedy można skorzystać z funkcji turnOff() - pozwala ona przejść ze stanu 2. do 1.
 *     Przykład zastosowania poniżej.
 *
 *     Timer można też uruchomić funkcją startFreeRun() - będzie wtedy działał w trybie free-run. W tym trybie
 *     licznik timera stopniowo rośnie zaczynając od zera. Czas, który upłynął od startu, można sprawdzić
 *     funkcją getElapsedTime(). Jedynym sposobem na zatrzymanie timera jest jego wyłączenie (turnOff()).
 *
 *     Przykład zastosowania
 *     =====================
 *     
 *     Wykrycie sygnału, który musi trwać przynajmniej 0.5 sekundy.
 *
 *         // utworzenie timera z jednostką ds (decysekunda = 0.1s)
 *         // Timer pozostaje wyłaczony (isTurnedOn() == false)
 *         CTimer m_mojTimer = CTimer(CTimer::UNIT_TENTHS_SEC);
 *
 *         if (sygnal_na_pinie())
 *         {
 *             if (!m_mojTimer.isTurnedOn()) //warunek A
 *             {
 *                 m_mojTimer.start(5);
 *                 //timer został włączony (isTurnedOn() == true) i jest ustawiony na 5 dziesiętnych
 *                 //sekundy (getRemainingTime() == 5) w miarę upływu czasu wartość getRemainingTime()
 *                 //będzie się zmniejszać (4, 3, ..., aż do 0), a czas, który upłynął
 *                 //zwiększać (getElapsedTime() rośnie 0, 1, ..., aż do 5)
 *             }
 *             if (m_mojTimer.isZero())  //mozna zastapic przez m_mojTimer.isElapsed()
 *             {
 *                 //wykryty sygnal trwajacy 0.5 s!
 *                 //m_mojTimer odmierzył ustawiony czas (isZero == true). m_mojTimer wciąż pozostaje
 *                 //włączony (isTurnedOn() == true). Dzieki temu nie uruchomi się od razu następny pomiar (patrz warunek A)
 *                 start_obsluga_sygnalu();
 *             }
 *         }
 *         else
 *         {
 *             m_mojTimer.turnOff();
 *             //m_mojTimer został wyłączony (isTurnedOn() == false). m_mojTimer rozpocznie nowy pomiar od razu
 *             //po wystąpieniu nowego sygnału na pinie
 *         }
 *
 *
 *     
 */

class CTimer
{
public:
    enum Unit
    {
        UNIT_MILISEC,       /**< milisekunda */
        UNIT_HUNDRETHS_SEC, /**< setna sekundy*/
        UNIT_TENTHS_SEC,    /**< dziesiętna sekundy */
        UNIT_SEC,           /**< sekunda */
        UNIT_MIN,           /**< minuta */
        UNIT_HOUR,          /**< godzina */
        COUNTER_CSEK = UNIT_HUNDRETHS_SEC,     /**< deprecated */
        COUNTER_DSEK = UNIT_TENTHS_SEC,        /**< deprecated */
        COUNTER_SEK  = UNIT_SEC,               /**< deprecated */
        COUNTER_MIN  = UNIT_MIN,               /**< deprecated */
    };

    /**
     * \brief Jednorazowa inicjalizacja klasy
     *
     * Funkcją zwracającą wartość tick'a. Wymagana częstotliwość zwiększania tick'a:
     * 1000 razy na sekundę
     */
    static void classInit1000(uint32_t (*getterTick1000)());

    /**
     * \brief        Tworzy nowy obiekt
     *
     * \param unit   jednostka timera. Można pominąć ten parametr, domyślną wartością jest wtedy CTimer::UNIT_SEC
     */
	CTimer(Unit unit = UNIT_SEC);

    /**
     * \brief Zmiana jednostki countera
     *
     * Zmiana jednostki countera. Powoduje rowniez wylaczenie countera
     */
	void setCounterUnit(Unit unit);

    /**
     * \brief Deprecated
     * \deprecated Zamiast tej funkcji użyj setCounterUnit(Unit unit)
     */
	void setCounterType(Unit unit);

    /**
     * \brief Ustawia i wlacza timer w standardowym trybie (downcounter).
     *
     * Jednostka zgodna z ustawionym typem za pomoca setCounterUnit(Unit unit).
     * Poczatkiem pomiaru czasu jest wywolanie tej funkcji
     */
	void start(uint32_t time);

    /**
     * \brief Funkcja podobna do startStrictAligned(), ale posiada dodatkowe zabezpiecznie.
     *
     * Jesli zostala wywolana na tyle pozno, ze ustawiany czas uplynal juz w chwili uruchomienia,
     * to zamiast tego wykonuje start().
     */
	void startAligned(uint32_t time);

    /**
     * \brief Ustawia i wlacza timer w standardowym trybie (downcounter).
     *
     * Jednostka zgodna z ustawionym typem za pomoca
     * setCounterUnit(Unit unit). Poczatkiem pomiaru czasu jest zakonczenie poprzedniego pomiaru.
     * Jesli:
     *   - poprzedni pomiar jeszcze sie nie zakonczyl,
     *   - timer pracuje w trybie free-run,
     *   - timer jest wylaczony,
     * to poczatkiem pomiaru jest wywolanie tej funkcji, czyli dzialanie takie samo jak start()
     *
     * \attention rezultaty moga byc niezgodne z oczekiwaniami, jesli counter pracowal jako downcounter
     * i pozostal na dluzszy czas na 0. Bezpieczniej jest uzywac startAligned()
     */
	void startStrictAligned(uint32_t time);

    /**
     * \brief Zmienia ustawiony wczesniej czas zachowujac ciaglosc dzialania.
     *
     * Zmienia ustawiony wczesniej czas zachowujac ciaglosc dzialania, rowniez jesli czas juz uplynal.
     * Nic nie robi w trybie free run lub wylaczonym
     */
	void changeOverallTime(uint32_t time);

    /**
     * \brief Uruchamia free-running timer.
     *
     * Plynacy czas mozna pobierac funkcja getElapsedTime()
     */
	void startFreeRun();

    /**
     * \brief     Zwraca całkowity czas, na jaki ustwiono timer.
     * \return    czas, na jaki zostal ustawiony timer. Jesli jest wylaczony albo w trybie free run, zwraca 0
     */
	uint32_t getOverallTime();

    /**
     * \brief Wylacza jawnie counter
     */
	void turnOff();

    /**
     * \brief     Informacja, czy timer jest włączony
     * \return    true od momentu uruchomienia timera az do wylaczenia go funkcja turnOff(). Uplyniecie ustawionego
     *            czasu nie wylacza timera
     */
	bool isTurnedOn();

    /**
     * \brief     Informuje, czy odmierzana wartość spadła do zera
     * \return    true, gdy czas uplynal lub counter wylaczony. W trybie free-run zawsze false
     */
	bool isZero();

    /**
     * \brief     Informuje, czy wartość timera wciąż maleje/rośnie
     * \return    true, gdy counter wlaczony i czas jeszcze nie uplynal. W trybie free-run zawsze true
     */
	bool isGoingOn();

    /**
     * \brief     Informuje, że czas upłynął
     * \return    true, gdy counter zostal uruchomiony i uplynal ustawiony czas. W trybie free-run zawsze false
     */
	bool isElapsed();

    /**
     * \brief     Informuje, jak długi czas został już odmierzony
     * \return    czas od uruchomienia countera. W standardowym trybie (downcounter) rosnie do osiagniecia
     *            ustawionego czasu. W trybie free-run rosnie bez ograniczen
     */
	uint32_t getElapsedTime();

    /**
     * \brief     Informuje, ile czasu pozostaje do końca pomiaru
     * \return    pozostaly czas. W trybie free-run zawsze 0
     */
	uint32_t getRemainingTime();

    /**
     * \brief     Zwraca wartość tick'a
     * \return    Wartość tick'a
     */
    static uint32_t getTick();

private:

	enum ETimerState {TS_OFF, TS_DOWNCOUNTING, TS_ELAPSED, TS_FREE_RUN};

	uint32_t startTick;

//	ustawiony czas
	uint32_t duration;

//	jednostka licznika
	Unit unit;

//	timer state
	ETimerState timState;

//  zwraca czas od uruchomienia timera. Jednostka zgodna z typem timera
    uint32_t _getTimeSinceStart();

//	wykonuje update stanu TS_DOWNCOUNTING->TS_ELAPSED, jesli uplynal czas
	uint32_t _updateDowncounter();

//	zwraca true, jesli timer pracuje w trybie downcountera. Czas plynie lub uplynal
	bool _isInDowncounterMode();

//	sprawdza, czy uplynal czas
	bool _isTimeElapsed(uint32_t _timeSinceStart);

//	konwersje
	uint32_t _timerUnits2ticks(uint32_t timerUnits);
	uint32_t _ticks2timerUnits(uint32_t ticks);
	static uint32_t getFactor1000(Unit unit);

	static uint32_t (*getTickFunc)();

//	domyslny getter tick'a
	static uint32_t defaultGetTickFunc();
};

#endif /* TIMER_H_ */
