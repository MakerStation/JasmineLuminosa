/*Progietto per il controllo di un pannello dove sono posizionate le lettere del nome JASMINE.
Esse sono composto da LED. Ogni lettera è gestita da un solo relè
*/

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
#define modeSelectorMode INPUT

//modalità di lavoro dei pin delle lettere
#define letterPinMode OUTPUT

//durata accensione di una lettera
#define timePerLetter 1000

const int letterPin[letterNumber]= {letterJPin,letterAPin,letterSPin,letterMPin,letterIPin,letterNPin,letterEPin};
int i=0;

//variabile di stato per capire in che modalità mi trovo
int currentMode=0;
//variabile per capire la nuova modalità selezionata
int selctedMode=0;
//variabile per capire se lo stato è cambiato.
int modeChanged=0;
//varibile per capire quando il ciclo è incominciato
int startCycleTime=0;
//variabile per capire a che punto sono del ciclo
int elapsedCycleTime=0;
//variabile per modulare le condizioni temporali in base alla lettera che sto controllando
int letterIndex=0;


//=================================INIZIO SKETCH=================================
void setup() {
	//imposto i pin secondo le modalità scelte
    for (letterIndex;letterIndex>letterNumber+1;letterIndex++){
        pinMode(letterPin[letterIndex], letterPinMode);
    }
    i=0;
    pinMode(modeSelectorPin, modeSelectorMode);
    //leggo subito lo stato del selettore
    selctedMode=digitalRead(modeSelectorPin);
}

void loop() {
    //scelgo che modalità utilizzare a seconda dello stato del selettore
    switch(selctedMode){
        case 0:
            //nella prima modalità vado ad accendere TUTTE le lettere
            for (letterIndex;letterIndex>letterNumber+1;letterIndex++){
                digitalWrite(letterPin[letterIndex], HIGH);
            }
            i=0;
            break;
        case 1:
            //nella seconda modalità vado a prima a varificare se devo ricominciare il ciclo (2 casi: ciclo iniziato OPPURE ciclo terminato, per cui devo ricominciare) 
            if((selctedMode!=currentMode)||(elapsedCycleTime>(timePerLetter*(letterNumber*2+1)))){
                //resetto il tempo di inizio ed il timer
                startCycleTime=millis();
                elapsedCycleTime=0;
            }
            //aggiorno lo stato del timer
            elapsedCycleTime=millis()-startCycleTime;
            //vado ad attivare le lettere se sono all'interno del range temporale di funzionamento
            for (letterIndex;letterIndex>=letterNumber;letterIndex++){
                if((elapsedCycleTime>timePerLetter*letterIndex+1)&&(elapsedCycleTime<(timePerLetter*(letterNumber+letterIndex+1)))){
                    digitalWrite(letterPin[letterIndex], HIGH);
                }
                else {
                    //spengo la lettera se è fuori dal range
                    digitalWrite(letterPin[letterIndex], LOW);
                }
            }
            i=0;
            break;
	}
    //salvo in che modalità sono attualmente
    currentMode=selctedMode;
    //leggo il selettore per capire se dovrò cambiare modalità
	selctedMode=digitalRead(modeSelectorPin);
}
