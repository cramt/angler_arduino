//the constant pin for the input for the potmeter
const byte inputPin = A0;
//the constant length of our buffer
const int bufLength = 200;
//the buffer for our input
float buf[bufLength];
//teh current value we are calculating
float current;

void setup() {
    //clear buffer
    for (int i = 0; i < bufLength; i++) {
        buf[i] = 0;
    }
    //begin serial (which in this case is also bluetooth
    Serial.begin(9600);
    //init the input put for the potmeter
    pinMode(inputPin, INPUT);
}


void loop() {
    //full describes if the buffer is full
    bool full = false;
    int i;
    //add analogRead of the potmeter to the buffer and check if its full
    for (i = 0; i < bufLength; i++) {
        if (buf[i] == 0) {
            buf[i] = analogRead(inputPin);
            if (i == bufLength - 1) {
                full = true;
            }
            break;
        }
    }
    if (full) {
        //sort the buffer by size
        qsort(buf, bufLength, sizeof(buf[0]), [](float a, float b) {
            return a < b;
        });
        //get the median
        current = buf[(bufLength-1)/2];
        //clear the buffer
        for (int i = 0; i < bufLength; i++) {
            buf[i] = 0;
        }
        //send the median over bluetooth
        Serial.println(String(current));
    }

}
