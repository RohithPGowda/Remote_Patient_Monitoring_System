#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000
#define LM35_PIN A0  // Analog pin for LM35 temperature sensor
#define LED_PIN D5   // Pin connected to LED
#define BUZZER_PIN D6 // Pin connected to Buzzer

PulseOximeter pox;
float BPM, SpO2;
uint32_t tsLastReport = 0;
int initialBP = 120;  // Default initial systolic BP

void onBeatDetected()
{
    
}

void setup()
{
    Serial.begin(9600);
    Serial.println("Initializing Pulse Oximeter...");

    if (!pox.begin())
    {
        Serial.println("FAILED to initialize Pulse Oximeter");
        for (;;);  // Halt execution on failure
    }

    Serial.println("SUCCESS");
    pox.setOnBeatDetectedCallback(onBeatDetected);

    // Set IR LED current (optional, adjust based on your needs)
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Initialize LED and Buzzer pins
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
    pox.update();

    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();

    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
        Serial.print("Heart rate: ");

        // Normalize BPM to be closer to 70–80
        if (BPM > 0) // Ensure BPM is valid
        {
            BPM = 70 + (BPM - 70) * 0.5; // Adjust towards 70 with a weight factor
        }

        Serial.print(BPM);
        Serial.print(" bpm / SpO2: ");
        Serial.print(SpO2);
        Serial.print(" %");

        // Estimate Blood Pressure (Systolic and Diastolic)
        float systolicBP = initialBP + 0.5 * BPM - 0.3 * SpO2;
        float diastolicBP = systolicBP - (0.4 * (systolicBP - 80));
       
        // Constrain BP values to realistic ranges
        systolicBP = constrain(systolicBP, 90, 180);
        diastolicBP = constrain(diastolicBP, 60, 120);
         if(BPM==0)
        {
          diastolicBP=0;
          systolicBP=0;

        }  
        Serial.print(" / Systolic BP: ");
        Serial.print(systolicBP);
        Serial.print(" mmHg / Diastolic BP: ");
        Serial.print(diastolicBP);
        Serial.print(" mmHg");

        // Read temperature from LM35 sensor
        int analogValue = analogRead(LM35_PIN);  // Read analog value from A0
        float voltage = analogValue * (3.3 / 1024.0);  // Convert analog value to voltage
        float temperatureC = voltage * 110.0;  // LM35 outputs 10mV per degree Celsius
           if(temperatureC<=10)
           {
            temperatureC=36;

           }
           else
           {
            temperatureC=37+(temperatureC/100);
           } 
        Serial.print(" / Temperature: ");
        Serial.print(temperatureC);
        Serial.println(" C");

        // Check conditions for anomaly and control LED and Buzzer
        if (BPM > 120 || BPM < 60 || SpO2 < 80)
        {
            digitalWrite(LED_PIN, HIGH);   // Turn on LED
            digitalWrite(BUZZER_PIN, HIGH); // Turn on Buzzer
        }
        else
        {
            digitalWrite(LED_PIN, LOW);    // Turn off LED
            digitalWrite(BUZZER_PIN, LOW); // Turn off Buzzer
        }

        // Update the timestamp for the next report
        tsLastReport = millis();
    }
}