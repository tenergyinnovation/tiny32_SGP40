/***********************************************************************
 * Project      :     tiny32_SGP40
 * Description  :     this code is template source code Interface test
 *                    between tiny32 and The SGP40 Air Quality sensor adopts the new SGP40 digital VOC sensor
 * Hardware     :     tiny32_v4
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     21/10/2024
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89-140-7205
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <esp_task_wdt.h>
#include <stdio.h>
#include <stdint.h>
#include <Wire.h>
#include <Adafruit_SGP40.h>

/**************************************/
/*          Firmware Version          */
/**************************************/
String version = "1.0";

/**************************************/
/*          Header project            */
/**************************************/
void header_print(void)
{
    Serial.printf("\r\n***********************************************************************\r\n");
    Serial.printf("* Project      :     tiny32_SGP40\r\n");
    Serial.printf("* Description  :     this code is template source code Interface test  \r\n");
    Serial.printf("*                    between tiny32 and The SGP40 Air Quality sensor adopts the new SGP40 digital VOC sensor \r\n");
    Serial.printf("* Hardware     :     tiny32_v4\r\n");
    Serial.printf("* Author       :     Tenergy Innovation Co., Ltd.\r\n");
    Serial.printf("* Date         :     19/06/2023\r\n");
    Serial.printf("* Revision     :     %s\r\n", version);
    Serial.printf("* Rev1.0       :     Origital\r\n");
    Serial.printf("* website      :     http://www.tenergyinnovation.co.th\r\n");
    Serial.printf("* Email        :     uten.boonliam@tenergyinnovation.co.th\r\n");
    Serial.printf("* TEL          :     +66 89-140-7205\r\n");
    Serial.printf("***********************************************************************/\r\n");
}

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;
Adafruit_SGP40 sgp;

/**************************************/
/*   MultiTasking function define     */
/**************************************/

/**************************************/
/*            GPIO define             */
/**************************************/

/**************************************/
/*       Constand define value        */
/**************************************/
#define WDT_TIMEOUT 10

/**************************************/
/*       eeprom address define        */
/**************************************/

/**************************************/
/*        define global variable      */
/**************************************/
int counter = 0;

/**************************************/
/*           define function          */
/**************************************/

/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    header_print();

    Serial.println("SGP40 test");
    if (!sgp.begin())
    {
        Serial.println("Sensor not found :(");
        while (1)
            ;
    }
    Serial.print("Found SGP40 serial #");
    Serial.print(sgp.serialnumber[0], HEX);
    Serial.print(sgp.serialnumber[1], HEX);
    Serial.println(sgp.serialnumber[2], HEX);

    Serial.print("Configuring WDT...");
    esp_task_wdt_init(WDT_TIMEOUT, true); // enable panic so ESP32 restarts
    esp_task_wdt_add(NULL);
    Serial.println("done");
    mcu.TickBuildinLED(1);
    mcu.buzzer_beep(2);
}

/***********************************************************************
 * FUNCTION:    loop
 * DESCRIPTION: loop process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void loop()
{
    uint16_t raw;

    raw = sgp.measureRaw();

    Serial.print("Measurement: ");
    Serial.println(raw);
    delay(1000);

    esp_task_wdt_reset();
}