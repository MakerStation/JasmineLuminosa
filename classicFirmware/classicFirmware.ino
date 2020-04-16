/*Progietto per il controllo di un pannello dove sono posizionate le lettere del nome JASMINE.
Esse sono composta da LED. Ogni lettera è gestita da un solo relè
*/

// alt+254
// alt+176

/*Commentare la successiva riga se si vogliono escludere tutte le righe di DEBUG.
NOTA: purtroppo in questa versione c'è un problema che se si escludono tutte le righe di serial.print entra in modalità waveMode e da lì non esce.
Considerando i tempi di consegna e che non inficiano o rallentano il fw ho deciso di lasciarlo sempre attivo. Vedrò poi se spendere ulteriore tempo in ricerca del problema.
*/
#define DEBUG

//rapida impostazione per cambiare la logica di controllo a seconda che stia utilizzando dei led o i rele: "1" per i led; "0" per i rele
#define testLed 0

//numero lettere
#define letterNumber 7

//letter pin
#define letterJPin 3
#define letterAPin 4
#define letterSPin 5
#define letterMPin 6
#define letterIPin 7
#define letterNPin 8
#define letterEPin 9
//pin per selzionare la modalità
#define modeSelectorPin 10

//modalità di lavoro del pin del selettore
#define readingModeSelectorModePin INPUT
//modalità di lavoro dei pin delle lettere
#define letterPinMode OUTPUT
//durata accensione di una lettera (ms)
#define defaultTimePerLetter 800
//definisco quale numero corrisponde a quale modalità.
#define steadyMode 0
#define waveMode 1
//preparo il mio array di lettere. 
const int letterPin[letterNumber]= {letterJPin,letterAPin,letterSPin,letterMPin,letterIPin,letterNPin,letterEPin};

//variabile di stato per capire in che modalità mi trovavo
int previusMode=0;
//variabile di stato per capire in che modalità mi trovo attualmente
int currentMode=0;
//variabile per capire la nuova modalità selezionata
int selectedMode=0;
//varibile per capire quando il ciclo è incominciato
unsigned long startCycleTime=0;
//variabile per capire a che punto sono del ciclo
unsigned long elapsedCycleTime=0;
//variabile per modulare le condizioni temporali in base alla lettera che sto controllando
int letterIndex=0;
//semplice inizializzazione della variabile. nel setup decido che valore deve avere.
int lightON=0;

unsigned long timePerLetter=defaultTimePerLetter;

//=================================INIZIO SKETCH=================================
void setup() {
	#ifdef DEBUG
		Serial.begin(2000000);
		Serial.print("STARTING SYSTEM");
	#endif
	//imposto i pin secondo le modalità scelte
    for (letterIndex;letterIndex<=letterNumber;letterIndex++){
        pinMode(letterPin[letterIndex], letterPinMode);
    }
    letterIndex=0;
    pinMode(modeSelectorPin, readingModeSelectorModePin);
    //leggo subito lo stato del selettore
    selectedMode=digitalRead(modeSelectorPin);
	//decido se devo controllare i rele (LOW=accesi) o se devo accendere direttamente i led (HIGH=accesi)
	if(testLed){
		lightON=1;
	}
	else if(!testLed){
		lightON=0;
	}
	for (letterIndex;letterIndex<=letterNumber;letterIndex++){
		//delay(200);
		digitalWrite(letterPin[letterIndex], !lightON);
	}
	letterIndex=0;
	//semplice accensione iniziale per non avere la stangata di corrente subito.
	for (letterIndex;letterIndex<=letterNumber;letterIndex++){
		delay(200);
		digitalWrite(letterPin[letterIndex], lightON);
		#ifdef DEBUG
			Serial.print(".");
		#endif
	}
	letterIndex=0;
}

void loop() {
	#ifdef DEBUG
		Serial.print("\n");
		Serial.print(millis()/1000.0);
		Serial.print("s - ");
		Serial.print(elapsedCycleTime);
		Serial.print("ms - ");
		Serial.print(selectedMode);
		Serial.print("/");
        Serial.print(currentMode);
		Serial.print("/");
        Serial.print(previusMode);
        Serial.print(" - LED:");
	#endif
    //scelgo che modalità utilizzare a seconda dello stato del selettore
	if(currentMode==steadyMode){
        //nella prima modalità vado ad accendere TUTTE le lettere
		elapsedCycleTime=0;
		for (letterIndex;letterIndex<=letterNumber;letterIndex++){
			digitalWrite(letterPin[letterIndex], lightON);
			#ifdef DEBUG
				Serial.print("*");
			#endif
		}
		letterIndex=0;
	}
	else if(currentMode==waveMode){
		//nella seconda modalità vado a prima a varificare se devo ricominciare il ciclo (2 casi: ciclo iniziato per la prima volta OPPURE ciclo terminato, per cui devo ricominciare) 
		if((currentMode!=previusMode)||(elapsedCycleTime>(timePerLetter*(letterNumber*2)))){
			//resetto il tempo di inizio ed il timer
			startCycleTime=millis();
			elapsedCycleTime=0;
		}
		//aggiorno lo stato del timer
		elapsedCycleTime=millis()-startCycleTime;
		//vado ad attivare le lettere se sono all'interno del range temporale di funzionamento
		for (letterIndex;letterIndex<=letterNumber;letterIndex++){
			if(((elapsedCycleTime>timePerLetter*(letterIndex+1)))&&(elapsedCycleTime<(timePerLetter*(letterNumber+letterIndex+1)))){
				digitalWrite(letterPin[letterIndex], lightON); //
				#ifdef DEBUG
					Serial.print("*");
				#endif
			}
			else {
				//spengo la lettera se è fuori dal range
				digitalWrite(letterPin[letterIndex], !lightON);
				#ifdef DEBUG
					Serial.print("-");
				#endif
			}
		}
		letterIndex=0;
	}
	#ifdef DEBUG
		Serial.print(" | ");
		Serial.print((unsigned long)(timePerLetter*(letterNumber*2+1)));
	#endif
	//salvo in che modalità ero
	previusMode=currentMode;
    //leggo il selettore per capire se dovrò cambiare modalità
	selectedMode=digitalRead(modeSelectorPin);
    currentMode=selectedMode;
	//delay(100);
    //selectedMode=0;
}
