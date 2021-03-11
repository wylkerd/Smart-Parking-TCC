/***********************************/
/*          SMART PARKING          */
/***********************************/

//Configuração de Distancia Mínima em centimetros
const int distancia_carro = 2;

//Configurações de Portas do Arduino

//Sensor
const int TRIG1 = 3;
const int ECHO1 = 2;

const int TRIG2 = 5;
const int ECHO2 = 4;

//Demais componentes
const int ledGreen1 = 7;
const int ledRed1 = 8;

const int ledGreen2 = 1;
const int ledRed2 = 2;

const int rows = 10;
const int columns = 3;

char status[rows][columns] = {
    {(char)'1', (char)'1', (char)'livre'},
    {(char)'1', (char)'2', (char)'livre'},
    {(char)'1', (char)'3', (char)'livre'},
    {(char)'1', (char)'4', (char)'livre'},
    {(char)'1', (char)'5', (char)'livre'},
    {(char)'1', (char)'6', (char)'livre'},
    {(char)'1', (char)'7', (char)'livre'},
    {(char)'1', (char)'8', (char)'livre'},
    {(char)'1', (char)'9', (char)'livre'},
    {(char)'1', (char)'10', (char)'livre'}};

void setup()
{
    Serial.begin(9600);

    // Configurações do Sensor1
    pinMode(TRIG1, OUTPUT);
    pinMode(ECHO1, INPUT);

    // Configurações do LED1
    pinMode(ledGreen1, OUTPUT);
    pinMode(ledRed1, OUTPUT);

    // Configurações do Sensor2
    pinMode(TRIG2, OUTPUT);
    pinMode(ECHO2, INPUT);

    // Configurações do LED2
    pinMode(ledGreen2, OUTPUT);
    pinMode(ledRed2, OUTPUT);
}

void loop()
{

    char result = (verificacao1() == 1) ? status[0][2] = (char)'livre' : status[0][2] = (char)'ocupada';
    result = (verificacao2() == 1) ? status[1][2] = (char)'livre' : status[1][2] = (char)'ocupada';
    //Serial.print(status);
    for (byte i = 0; i < sizeof(status); i = i + 1)
    {
        Serial.println(status[i]);
    }
}

int sensor_morcego1(int pinotrig, int pinoecho)
{
    digitalWrite(pinotrig, LOW);
    delayMicroseconds(2);
    digitalWrite(pinotrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinotrig, LOW);

    return pulseIn(pinoecho, HIGH) / 58;
}

int verificacao1()
{
    int distancia1 = sensor_morcego1(TRIG1, ECHO1);

    if (distancia1 <= distancia_carro)
    {
        digitalWrite(ledGreen1, LOW);
        digitalWrite(ledRed1, HIGH);
        return 0;
    }
    else
    {
        digitalWrite(ledGreen1, HIGH);
        digitalWrite(ledRed1, LOW);
        return 1;
    }
    delay(100);
}

/*************************************************************************/

int sensor_morcego2(int pinotrig, int pinoecho)
{
    digitalWrite(pinotrig, LOW);
    delayMicroseconds(2);
    digitalWrite(pinotrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinotrig, LOW);

    return pulseIn(pinoecho, HIGH) / 58;
}

int verificacao2()
{
    int distancia2 = sensor_morcego2(TRIG2, ECHO2);

    if (distancia2 <= distancia_carro)
    {
        digitalWrite(ledGreen2, LOW);
        digitalWrite(ledRed2, HIGH);
        return 0;
    }
    else
    {
        digitalWrite(ledGreen2, HIGH);
        digitalWrite(ledRed2, LOW);
        return 1;
    }
    delay(100);
}
