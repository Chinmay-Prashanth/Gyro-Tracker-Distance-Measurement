#include <mbed.h>
#define _USE_MATH_DEFINES
#include <math.h>
//this file has all the functions for interacting
//with the screen
#include "drivers/LCD_DISCO_F429ZI.h"
#define BACKGROUND 1
#define FOREGROUND 0
#define GRAPH_PADDING 5
#define PI 3.14159265358979323846

LCD_DISCO_F429ZI lcd;
//buffer for holding displayed text strings
char display_buf[2][60];
uint32_t graph_width=lcd.GetXSize()-2*GRAPH_PADDING;
uint32_t graph_height=graph_width;


/*
DataReading:  -- 20% - Ability to successfully and continuously measure gyro values from the angular velocity sensor
Use SPI, Ticker to read the data.
SPI, TICKER -> setFlag(), setMode();
ReadData -> readData();

Calibration: -- 15% - Creativity
Calibration1 -> We utilize calibration to eliminate the influence of the fluctuate of the raw data. 
Calibration2 -> Verify the relationship between angular speed and the raw data from the sensor.
The code is also contained in the ZIP. Go to the zip to find the code.

Methods:
Our Program contains three mehtods to calculate the moving distance. You can find the corresponding code in the calculationDinstance 1 to 3.
method1 -> CalculationDistance1() -- 20% - Ability to convert measured data to forward movement velocity
                                  -- 20% - Ability to calculate distance traveled
method2 -> CalculationDistance2() -- 15% - Creativity
method3(Best method/ default method) -> CalculationDinstance3()-- 15% - Creativity

IMPORTANT! 
1.If you want to run the code for specific method, please comment the code for other methods in the main while loop. 
  Otherwise you will run into bugs instead of geting the correct result.
2. The Sensor should be tied exactly to the right side of the knee.
*/

volatile int flag = 0;
// mosi, miso, sclk
SPI spi(PF_9, PF_8, PF_7);
DigitalOut cs(PC_1);

// Initialize for method 1:
int8_t fullTime = 30;
int8_t size = fullTime / 0.05;
int16_t dataSet[600];
double totalDist = 0;

// Initialize for method 2:
int steps = 0;
//indicate the moving have started
int state = 0;


void setFlag();
void setMode();
int16_t readData(int code);

double calculateDistance1();
void calculateDistance2(int16_t dataX);
void calculateDistance3(int16_t tempData);

void setFlag() {          
  flag = 1;
}

void setMode() {          
  cs=0;
  spi.write(0x20);
  spi.write(0xCF);
  cs=1;
}

/*
- 20% - Ability to successfully and continuously measure gyro values from the angular velocity sensor
*/
int16_t readData(int code){
  cs = 0;
  spi.write(code);//X_L
  uint8_t xl =spi.write(0x00);
  cs = 1;
  cs = 0;
  spi.write(code+1);
  int8_t xh =spi.write(0x00);
  cs = 1;
  int16_t data= xh*256+xl;
  return data;
}


/*
- 20% - Ability to convert measured data to forward movement velocity
- 20% - Ability to calculate distance traveled
IDEA1: - For method 1
Gyroscope is a device that produces a positive-going digital output for counter-clockwise rotation around the axis considered.
Since it could measure the angular, after caliburation, we could convert the raw data into angular velocity.According to datasheet, 
the sensitivity of the gyroscope, when FS = 245 dps and typical values at +25 °C,the transfer factor is 8.75 mdps/digit. (Page 10 of the datasheet). 
After transformation, we could get the velocity and distance.
*/
double calculateDistance1(){
  double realData;
  double totalDist1 = 0;
  for (int i = 0; i < 600; i++){
    dataSet[i] = abs(dataSet[i]);
    if (dataSet[i] > 5000){
      // Transform to angle velocity. 
      realData = (0.00875 * (dataSet[i] + 63));
      totalDist1 = totalDist1 + ((double) 0.05) * (realData / 360) * 2 * PI * 1.015;
    }
  }
  return totalDist1;
}


/*
IDEA2: - For method 2
Count steps and calculate final distance using stride.
*/

void calculateDistance2(int16_t dataZ){
  if(dataZ < -12000 && state == 0){
      state=1;
    }
    if(dataZ > 12000 && state == 1){
      state = 0;
      steps++;
      //printf("The steps moved: %d\n",steps);
      int distance = steps * 7;
      printf("the distance moved:%d.%dm\n",distance / 10,distance % 10);
    }
}


/*
IDEA3: - For method 3
Realtime distance calculation for demo presentaion and video record.
calculate distance during runtime using gyroscope's reading.
*/

void calculateDistance3(int16_t tempData){
  double realData;
  if(abs(tempData) > 3000) {
    // Transform to angle velocity. 
    realData = (0.00875 * abs(tempData + 63));
    totalDist+=(double)(0.05 * realData / 360 * 2 * PI * 1.015);
    printf("Distance: %d meters\n",(int)totalDist);
  }

}


//###################################################display functions####################################################
//sets the background layer 
//to be visible, transparent, and
//resets its colors to all black
void setup_background_layer(){
  lcd.SelectLayer(BACKGROUND);
  lcd.Clear(LCD_COLOR_BLACK);
  lcd.SetBackColor(LCD_COLOR_BLACK);
  lcd.SetTextColor(LCD_COLOR_GREEN);
  lcd.SetLayerVisible(BACKGROUND,ENABLE);
  lcd.SetTransparency(BACKGROUND,0x7Fu);
}

//resets the foreground layer to
//all black
void setup_foreground_layer(){
    lcd.SelectLayer(FOREGROUND);
    lcd.Clear(LCD_COLOR_BLACK);
    lcd.SetBackColor(LCD_COLOR_BLACK);
    lcd.SetTextColor(LCD_COLOR_LIGHTGREEN);
}









///*//START OF EXAMPLE 1---------------------------------------------
int main() {

      cs=1;
  setMode();
  spi.format(8,3);
  spi.frequency(100000);
	Ticker t;
  t.attach(&setFlag,0.05);
  uint16_t iter = 0;


  while(1) {
    if(flag){
      int16_t dataZ = readData(0xAC);
      // Method3: Real Time distance calculation. Used for Demo presentation. Get the total distance while moving
      calculateDistance3(dataZ);


    //#####################display on screen###############
      setup_background_layer();

      setup_foreground_layer();

        //creates c-strings in the display buffers, in preparation
        //for displaying them on the screen
        snprintf(display_buf[0],60,"DISTANCE: %d METERS",(int)totalDist);

        lcd.SelectLayer(FOREGROUND);
        //display the buffered string on the screen

        lcd.DisplayStringAt(0, LINE(17), (uint8_t *)display_buf[0], LEFT_MODE);
        


        lcd.SelectLayer(FOREGROUND); 


    flag = 0;
    }
    
  }

}