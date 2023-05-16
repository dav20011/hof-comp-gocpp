# Vergleich der Implementierung von Funktionen höherer Ordnung in C++ und Go

## Einführung

Funktionen höherer Ordnung sind Funktionen, die entweder andere Funktionen als Argumente akzeptieren oder als Rückgabewerte zurückgeben.
Diese sind ein wichtiger Bestandteil der funktionalen Programmierung und ermöglichen außerdem, die Wiederverwendbarkeit von Programmcode zu erhöhen.
Allerdings gibt es viele verschiedene Varianten von Funktionen höherer Ordnung und auch entsprechende Implementierungen.
Ziel dieser Projektarbeit ist es, eine sehr allgemeine Implementierung in C++ mit einer spezifischen Variante in theoretischer Sicht zu vergleichen und zudem die Ausführungsgeschwindigkeit verschiedener Varianten zu untersuchen.

## Grundlagen

Betrachtet man beispielsweise eine einstellige Funktion `f: A -> B`, dann ist `f` eine Funktion höherer Ordnung, wenn mindestens eine der Mengen `A` und `B` eine Funktion `g` enthält.
In der Programmierung kann dieses `g` dabei in einigen verschiedenen Varianten auftreten.

### Varianten

Das einfachste Unterscheidungsmerkmal ist die Benennung von `g`.
`g` kann eine reguläre Funktion mit einem eigenen Namen, jedoch ist in vielen Programmiersprachen auch die deklaration einer Funktion in beispielweise dem Kontext eines Funktionsaufrufs möglich.
In diesem Fall spricht man von einer anonymen Funktion bzw. einem Lambda.
Auch wenn der Begriff Lambda auch häufig fälschlicherweise zur Beschreibung anderer Eigenschaften genutzt wird, hat ein Lambda im eigentlichen Sinne keine Bedeutung für die Semantik und wird hier deshalb nicht näher betrachtet.

Des Weiteren kann sich `g` auch darin unterscheiden, auf welchen Datenkontext die Funktion zugreifen kann. Dabei gibt es mehrere Abstufungen:

#### 1. Kein Zugriff auf externe Daten

Die Funktion verhält sich wie eine reguläre Funktion (oder ist sogar eine) und hat keinen Zugriff auf einen speziellen Kontext.
Dementsprechend ist eine solche Funktion auch nie an einen entsprechenden Zustand gebunden.
Typische Anwendungsfälle sind beispielsweise Vergleichsfunktionen für Sortieralgorithmen.
Derartige Funktionen haben auch einen Bezug zu purely functional programming, denn wenn eine Funktion keinen Zustand hat liefert sie bei der gleichen Eingabe auch immer das gleiche Ergebnis.

#### 2. Zugriff auf externe Daten, die den darüberliegenden Kontext nicht überdauern

Ist `g` in dem Kontext einer anderen Funktion deklariert, ist ein Zugriff auf dessen lokale Variablen möglich.
Dies kann kritisch sein, da `g` und seine Aufrufe gegebenenfalls den aufrufenden Kontext überdauern.
Wird der Elternkontext beendet, spricht man davon, dass die enthaltenen lokalen Variablen "out of scope" sind und folglich ist ein Zugriff nicht mehr erlaubt.

#### 3. Zugriff auf externe Daten, die den darüberliegenden Kontext überdauern

In dieser Variante hat `g` auch Zugriff auf die Daten des darüberliegenden Kontextes, wenn dieser bereits beendet ist.

## Implementierungstechniken

Funktionen höherer Ordnung können abhängig der Variante auf verschiedene Arten implementiert werden.
Wirklich interessant ist dabei nur die dritte Variante, da die Umsetzung der beiden ersten Varianten trivial ist.
Wenn kein Zugriff auf externe Daten besteht, handelt sich schlichtweg um eine gewöhnliche anonyme Funktion.
Auch die zweite Variante ist wenig problematisch, da die benötigten Variablen sich noch weiter unten im Stack befinden, wenn der Aufruf geschieht.
Bei der dritten Variante besteht nun aber das Problem, dass die Daten nicht mehr wie gewöhnlich im Elternkontext auf dem Stack gespeichert werden können, da dieser zum Zeitpunkt des Aufrufs schon beendet sein könnte.

### Closure

Eine Closure ist eine Funktion, die den benötigten Kontext einer Funktion in einer Struktur speichert.
Die Strategie ist am einfachsten an einem C++ Beispiel zu erkennen:

``` cpp
std::function<int(int)> createAdd(int a) {
    return [a](int b) -> int {
        return a + b;
    };
}

int add(int a, int b) {
    return createAdd(a)(b);
}
```

Hier wird eine einfache Addierfunktion mittels eines C++ Lambdas erstellt.
Die Angabe in den eckigen Klammern gibt vor, dass a zwischengespeichert werden muss.
Eine Übersetzung zu einer Closure könnte wie folgt aussehen:

``` cpp
struct Closure {
    int a;
    
    int operator()(int b) {
        return a + b;
    }
};

Closure createAdd(int a) {
    return {a};
}

int add(int a, int b) {
    return createAdd(a)(b);
}
```

Diese Form der Übersetzung ist einfach und insbesondere für den Compiler problemlos übersetzbar.
Jedoch birgt sie ein grundlegendes neues Problem, die Speicherung der Closure.
Hierfür wird in der Praxis meist auf den Heap zurückgegriffen, was jedoch einen signifikanten Overhead zur Folge haben kann.

Hinweis: Für eine vollständige Übersetzung mit Polymorphie für Closures wäre in C++ zusätzlich eine Klassenhierarchie mit `virtual`-Methoden notwendig.

### Lambda Lifting

Lambda Lifting ist ein Metaprozess, bei welchem die Daten, die man in einer Closure speichern würde, die sog. freien Variablen, zu Parametern umgewandelt werden.
Um dies zu erreichen, müssen alle Funktionen, die im Call Stack zwischen der higher-order Funktion und dem Aufruf liegen, umstrukturiert werden.
Aus dem obigen Beispiel für Closures würde bei Lambda Lifting ein Trivialbeispiel der Addition entstehen:

``` cpp
int add(int a, int b) {
    return a + b;
}
```

Das Ergebnis ist offensichtlich wesentlich effizienter, jedoch gibt es auch Nachteile.
Zunächst ist die Übersetzung aufwendiger und die besten bekannten Algorithmen liegen mit ihrer Zeitkomplexität in `O(n²)`.
Außerdem setzt diese Technik die Verwendung des gleichen Stacks voraus und so ist es nicht möglich, eine Funktion höherer Ordnung mittels Lambda Lifting zu implementieren, falls der Erstellungs- und der Aufrufkontext in verschiedenen Threads sind.


## Implementierungen

### C++

Typisch für C++ bietet die Sprache für Funktionen höherer Ordnung sehr grundlegende aber mächtige Werkzeuge, die durch die Standardbibliothek vervollständigt werden.
Die Kernfunktion ist hier das Lambda, was eine Closure Implementierung nutzt.
Es erlaubt die Definition einer geschachtelten Funktion mit einem explizit angegebenen Kontext.
Dabei ist es möglich, Werte direkt oder als Referenz zu übergeben. Die Syntax sieht wie folgt aus:

``` cpp
void lambdaSample(int x, int y) {
    auto lambda = [x, &y](int z) -> int {
        y = x + z;
    };
}
```

Die Angabe des Rückgabewertes ist meist nicht notwendig, da dieser inferiert werden kann.
Aufgrund der Speicherung von Daten in dem Closure wird ein neuer Typ erstellt, der jedoch nicht direkt benannt werden kann und den Call-Operator unterstützt.
Gleichartige Lambdas haben nicht den gleichen Typ und können daher nur mithilfe von Templates direkt übergeben werden.
Da es sich wie eine reguläre Struktur verhält, wird bei einer Übergabe die gesamte Closure kopiert.

Da diese Funktion für sich noch sehr rudimentär ist, wird sie durch `std::function` vervollständigt.
`std::function` ist ein Containertyp für aufrufbare Typen, der mittels Templates viele Funktionen anbietet:
* Referenzierung eines Aufrufbaren Typs, wie einer Funktion, Methode, eines Functors oder eines Lambdas
* Aufruf per Operatorenüberladung
* Zusammenfassung aller gleichartigen aufrufbaren Typen unter jeweils einer Template-Instanz, wie beispielsweise std::function<int(int)>
* Speicherung des Kontextes in einem kleinen internen Puffer
* Speicherung von größeren Kontexten auf dem Heap

Durch die automatische Anwendung von Konstruktoren in C++ ist es außerdem möglich, aufrufbare Typen wie Lambdas direkt als `std::function` Parameter zu übergeben.
Eine große Schwäche dieser Umsetzung ist jedoch, dass ein Großteil davon in der späteren Anwendungssoftware landet und so die Geschwindigkeit beeinträchtigt.
Dazu gehören auch Dinge, die bereits der Compiler statisch effizienter lösen könnte.

### Go

Anders als C++ unterstützt Go schon von Beginn an Funktionen höherer Ordnung und hat diese auch vollständig abstrahiert.
So sieht das äquivalente Beispiel in Go wie folgt aus:
``` go
func createAdd(a int) func(int) int {
	return func(b int) int {
		return a + b
	}
}

func add(a int, b int) int {
	return createAdd(a)(b)
}
```

Zugriff auf Variablen des darüberliegenden Kontextes unterliegen dabei keiner Einschränkungen.
Die Eigenschaft von Go Pointer zu unterstützen, aber gleichzeitig eine automatische Speicherverwaltung zu haben, führt dabei zu einem interessanten Randeffekt.
Folgendes Beispiel ist in Go völlig unproblematisch, wäre aber in beinahe jeder anderen Programmiersprache ein Fehler:

``` go
func createAdd(a int) func(int) int {
	aRef := &a
	
	return func(b int) int {
		return *aRef + b
	}
}
```

Denn anders als beispielsweise Java, das lokale Variablen mit primitiven Datentypen immer auf dem Stack und Objekte immer im Heap speichert, speichert Go Variablen abhängig von ihrer Verwendung entweder auf dem Heap oder dem Stack.
Ist es wie in diesem Beispiel möglich, dass noch nach Beendigung einer Funktion eine Referenz auf eine lokale Variable besteht, so wird diese automatisch auf den Stack ausgelagert.

Dadurch ist bereits eine der Hürden gelöst, jedoch bleibt offen, wie Go den Kontext einer Funktion höherer Ordnung erhält.
Unglücklicherweise ist nicht spezifiziert oder dokumentiert, wie dies konkret umgesetzt wird.
Allerdings ermöglicht der `go build` Befehl es, einen speziellen Go Assembly des Programms ausgeben zu lassen.
Bei einer Erstellung einer Funktion höherer Ordnung mit vier Werten im Kontext wird beispielsweise diese Struktur angelegt:

`$type:noalg.struct { F uintptr; main.a int; main.b int; main.c int; main.d int }`

Dabei handelt es sich um eine Closure. Neben den vier Werten wird außerdem eine Referenz auf die Funktion gespeichert.
Vor dem Aufruf werden diese Werte von der aufrufenden Funktion wieder auf den Stack gelegt und so Verhält sich der Kontext wie ein zusätzlicher Satz an Parametern.

## Performance-Untersuchung

Ziel dieser Untersuchung ist es, die verschiedenen Varianten der Umsetzung in C++ mit Go hinsichtlich ihrer Performance zu untersuchen.
Dazu habe ich einige Testfälle angelegt, welche verschiedene Anwendungsszenarien mit Funktionen höherer Ordnung abbilden.
Zur besseren Vergleichbarkeit sind diese Szenarien nicht realitätsnahe, weshalb für beide Sprachen die Optimierungen vollständig deaktiviert wurden, damit beispielsweise die Funktionen nicht vollständig wegoptimiert werden.

### Eigenschaften des Testsystems

| Eigenschaft         | Wert        |
|---------------------|-------------|
| Testdurchläufe      | 5           |
| Anzahl Iterationen  | 10000000    |
| Go Version          | 1.20.2      |
| GCC Version (MinGW) | 6.3.0       |
| Betriebssystem      | Windows 11  |
| CPU                 | Ryzen 5900X |
| RAM                 | DDR4-3200   |

### Ergebnisse

| Test              | Mittelwert | Variationskoeffizient |
|-------------------|------------|-----------------------|
| FunctionPointer   | 23,12 ms   | 8,53 %                |
| Lambda            | 34,47 ms   | 5,28 %                |
| LambdaCapture     | 75,44 ms   | 8,25 %                |
| FunctionPure      | 320,79 ms  | 2,57 %                |
| FunctionCapture   | 921,48 ms  | 2,06 %                |
| FunctionHeap      | 976,25 ms  | 3,93 %                |
| StructHeap        | 173,16 ms  | 6,64 %                |
| GoFunctionPure    | 43,67 ms   | 9,90 %                |
| GoFunctionCapture | 46,90 ms   | 4,95 %                |
| GoFunctionHeap    | 65,96 ms   | 9,61 %                |

### Auswertung

Die Ergebnisse für einfache Funktionstypen in C++ liegt in einem erwartbaren Bereich.
Auffällig, dass selbst ein einfaches Lambda ohne Capture bereits einen kleinen Overhead hat, der sich durch einen Capture noch einmal deutlich erhöht.
Die Ausführungszeit erhöht sich dagegen massiv, sobald `std::function` verwendet wird, selbst ohne Capture.
Die Umsetzung der Laufzeit scheint ein signifikanter Nachteil zu sein, der sich durch die Verwendung von Captures noch einmal deutlich erhöht.
Entgegen der Erwartung hat es deshalb auch keinen großen Einfluss mehr, wenn man durch ein größeres Capture eine Heap-Zuweisung erzwingt.
Deutlich performanter als `std::function` ist dagegen eine direkte Übersetzung mit Strukturen und doppelter Indirektion (aufgrund von virtual).

Go kann zwar nicht die Geschwindigkeit von einfacher Indirektion mit C++ Funktionspointern erreichen, ist aber mit Funktionen höherer Ordnung nicht weit davon entfernt und bleibt bei allen direkt übersetzten Tests sehr stabil.
Zwar ist davon auszugehen, dass Speicherzuweisungen von Go schneller sind als die eine Standard malloc-Implementierung, jedoch kommt hier der Verdacht auf, dass Go komplett auf die Nutzung des Heaps verzichtet hat.