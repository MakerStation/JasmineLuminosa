/*Progietto per il controllo di un pannello dove sono posizionate le lettere del nome JASMINE.
Esse sono composto da LED. Ogni lettera è gestita da un solo relè
*/


//valutare la gestione delle lettere come se fossero oggetti
//output pin
#define letterJPin_out 3
#define letterAPin_out 4
#define letterSPin_out 5
#define letterMPin_out 6
#define letterIPin_out 7
#define letterNPin_out 8
#define letterEPin_out 9

//input pin
#define modeSelectorPin_in 10

//letter state
int letterJ_state=0;
int letterA_state=0;
int letterS_state=0;
int letterM_state=0;
int letterI_state=0;
int letterN_state=0;
int letterE_state=0;

//variabile di stato per capire in che modalità mi trovo
int currentMode=0;
//variabile per capire la nuova modalità selezionata
int selctedMode=0; 

void setup() {
	//imposto i pin secondo la modalità scelta
	pinMode(letterJPin_out, OUTPUT);
	pinMode(letterAPin_out, OUTPUT);
	pinMode(letterSPin_out, OUTPUT);
	pinMode(letterMPin_out, OUTPUT);
	pinMode(letterIPin_out, OUTPUT);
	pinMode(letterNPin_out, OUTPUT);
	pinMode(letterEPin_out, OUTPUT);
	pinMode(modeSelectorPin_in, INPUT);
}

void loop() {
	selctedMode=digitalRead(modeSelectorPin_in);
    switch(selctedMode){
        case 0:
            digitalWrite(letterJPin_out, HIGH);
            digitalWrite(letterAPin_out, HIGH);
            digitalWrite(letterMPin_out, HIGH);
            digitalWrite(letterIPin_out, HIGH);
            digitalWrite(letterNPin_out, HIGH);
            digitalWrite(letterEPin_out, HIGH);
            digitalWrite(letterSPin_out, HIGH);
            break;
        case 1:
            //TODO
            break;
	}
}
