/*
Interface for Baron 58 Simulator
Simple Example for Gear Up/Down 

  by Vlad Sychev 2013
http://b58.svglobe.com
 */

//***** library ******************************************************************************
#include <Wire.h>
#include <SPI.h>         
#include <Ethernet.h>
#include <XPlaneData.h>         // -- include XPlaneData library
//#include <XPData.h> 
/*Seems to be 2 versions of library. if you can't compile, 
 do a replace all on "XPlaneData" to "XPData" and include that one 
 instead.
*/

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};// MAC-Address of Arduino
int XPR = 49001;                                  // port to listen to get UDP packets
int XPW = 49000;                                  // port to send UDP packets
int IPx[] = {192,168,0,12};                     // X-Plane IP address ( ! set your !)
byte IP[] = {192,168,0,177}; 
//IPAddress ip(192,168,0,177);
XPlaneData XPlaneData(XPR, XPW, IPx, mac);    //==!==  Create  XPlaneData object (XPData)

float Flaps;      // Flaps, current
float Flaps_pre;  // Flaps previous


/* just here for reference, not needed with direct port manipulation
int flapsled1 = 49; 
int flapsled2 = 48;
int flapsled3 = 47;
int flapsled4 = 46;
int flapsled5 = 45;
int flapsled6 = 44;
int flapsled7 = 43;
int flapsled8 = 42;
int flapsled9 = 41;
int flapsled10 = 40;

int trimled1 = 39;
int trimled2 = 38;
int trimled3 = 37;
int trimled4 = 36;
int trimled5 = 35;
int trimled6 = 34;
int trimled7 = 33;
int trimled8 = 32;
int trimled9 = 31;
int trimled10 = 30;
*/

 float Trim;      // Trim, current
float Trim_pre;  // Trim previous

 float Gear1 = 1;                //--- Gear #1 position ( 1.00 - Down&Locked, 0 - Up)
 float Gear2 = 1;                //--- Gear #2 position 
 float Gear3 = 1;                //--- Gear #3 position  


 // --- Pins for gear LEDs
  const   int Gear1Green = 2;    // Gear 1 Pins
  const   int Gear1Red = 3;

  const   int Gear2Green = 5;    // Gear 2 Pins
  const   int Gear2Red = 6;
  
  const   int Gear3Green = 7;    // Gear 3 Pins
  const   int Gear3Red = 8;

void setup()
{
   
      XPlaneData.begin();      //==!== init XPlaneData
      XPlaneData.cmd_in("sim/none/none");   // --  NULL command to see our Arduino IP in X-Plane "Net connections" screen 
      //Serial.begin(19200);
}


void loop() 
{ 

if (XPlaneData.udpin()) 
    {               // - define group number and position in this group to get needed parameter
     Gear3 = XPlaneData.Dget(67, 3);
       Gear2 = XPlaneData.Dget(67, 2);  
          Gear1 = XPlaneData.Dget(67, 1);

          //Serial.print("Gear ONE   "); Serial.println(Gear1); 
        while(Gear1 == 0) 
        {
        PORTE &= ~_BV(PE5); //OFF Gear1Red/PIN3
        PORTE &= ~_BV(PE4); //OFF Gear1Green/PIN2
        break;
        }  
          
        while(Gear1 > 0.0 && Gear1 < 1.0) 
        {
        PORTE &= ~_BV(PE4); //OFF Gear1Green/PIN2
        PORTE |= _BV(PE5); //ON GEAR1RED/PIN3 
        break;
        }      
          
        while(Gear1 == 1.0)
        {
        PORTE &= ~_BV(PE5); //OFF Gear1Red/PIN3
        PORTE |= _BV(PE4); // ON Gear1Green/PIN2
        break;
        }

          
        
          //Serial.print("Gear TWO   "); Serial.println(Gear2); 
        while(Gear2 == 0)
        {
        PORTH &= ~_BV(PH3); //OFF Gear2Red/PIN6
        PORTE &= ~_BV(PE3); //OFF Gear2Green/PIN5
        break;
        }

        while(Gear2 > 0.0 && Gear2 < 1.0)
        {
        PORTE &= ~_BV(PE3); //OFF Gear2Green/PIN5
        PORTH |= _BV(PH3); // ON Gear2Red/PIN6
        break;
        }          
        
        while(Gear2 == 1.0)
        {
        PORTE |= _BV(PE3); // ON Gear2Green/PIN5
        PORTE &= ~_BV(PH3); //OFF Gear2Red/PIN6
        break;
        }   

          
                   
         
         //Serial.print("Gear Three   "); Serial.println(Gear3);          
        while(Gear3 == 0)
        {
        PORTH &= ~_BV(PH5); //OFF Gear3Red/PIN8
        PORTH &= ~_BV(PH4); //OFF Gear3Green/PIN7
        break;
        }
        while(Gear3 > 0.0 && Gear3 < 1.0)
        {
        PORTH |= _BV(PH5); //ON Gear3Red/PIN8
        PORTH &= ~_BV(PH4); //OFF Gear3Green/PIN7
        break;
        }          
        while(Gear3 == 1.0)
        {
        PORTH &= ~_BV(PH5); //OFF Gear3Red/PIN8
        PORTH |= _BV(PH4); //ON Gear3Green/PIN7
        break;
        }

             float Trim = XPlaneData.Dget(13, 1);
               if (Trim_pre != Trim) {      // check if value has ben changed
               Trim_pre = Trim; 
              // Serial.print("Trim = "); Serial.println(Trim); 
            }

            Flaps = XPlaneData.Dget(13, 5);
               if (Flaps_pre != Flaps) {      // check if value has ben changed
               Flaps_pre = Flaps; 
              // Serial.print("Flaps = "); Serial.println(Flaps); 
            }
      
            int flapPos = Flaps * 10;
      //int FlapsTemp = Flaps * 9;
        //int flapPos = map(FlapsTemp, 0, 9, 0, 9);

   if (Trim >= -1.00 && Trim <= -0.91) 
   {
        PORTG |= _BV(PG2); //ON trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
        
    }
        
    else if (Trim >= -0.90 && Trim <= -0.81)
    {
        PORTG |= _BV(PG2); //ON trimled1/PIN39
        PORTD |= _BV(PD7); //ON trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
        
    } 
        
    else if (Trim >= -0.80 && Trim <= -0.71)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD |= _BV(PD7); //ON trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
       
    }    
        
    else if (Trim >= -0.70 && Trim <= -0.61)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD |= _BV(PD7); //ON trimled2/PIN38
        PORTC |= _BV(PC0); //ON trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
       
    } 
        
    else if (Trim >= -0.60 && Trim <= -0.51)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC |= _BV(PC0); //ON trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
        
    }   
        
    else if (Trim >= -0.50 && Trim <= -0.41)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC |= _BV(PC0); //ON trimled3/PIN37
        PORTC |= _BV(PC1); //ON trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
        
    }   
        
    else if (Trim >= -0.40 && Trim <= -0.31)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC |= _BV(PC1); //ON trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30

    }    
        
    else if (Trim >= -0.30 && Trim <= -0.21)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC |= _BV(PC1); //ON trimled4/PIN36
        PORTC |= _BV(PC2); //ON trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
 
    }   
        
    else if (Trim >= -0.20 && Trim <= -0.11)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC |= _BV(PC2); //ON trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
   }    
        
    else if (Trim >= -0.10 && Trim <= -0.01)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC |= _BV(PC2); //ON trimled5/PIN35
        PORTC |= _BV(PC3); //ON trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30

    }     
        
    else if (Trim >= 0.00 && Trim <= 0.09)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC |= _BV(PC3); //ON trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
      }     
        
    else if (Trim >= 0.10 && Trim <= 0.19)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC |= _BV(PC3); //ON trimled6/PIN34
        PORTC |= _BV(PC4); //ON trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30

    }   
        
    else if (Trim >= 0.20 && Trim <= 0.29)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC |= _BV(PC4); //ON trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30

    }   
        
    else if (Trim >= 0.30 && Trim <= 0.39)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC |= _BV(PC4); //ON trimled7/PIN33
        PORTC |= _BV(PC5); //ON trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
       }    
        
    else if (Trim >= 0.40 && Trim <= 0.49)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC |= _BV(PC5); //ON trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
       
    }   
        
    else if (Trim >= 0.50 && Trim <= 0.62)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC |= _BV(PC5); //ON trimled8/PIN32
        PORTC |= _BV(PC6); //ON trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
      
    }   
        
    else if (Trim >= 0.63 && Trim <= 0.75)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC |= _BV(PC6); //ON trimled9/PIN31
        PORTC &= ~_BV(PC7); //OFF trimled10/PIN30
     
    }   
        
    else if (Trim >= 0.76 && Trim <= 0.87)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC |= _BV(PC6); //ON trimled9/PIN31
        PORTC |= _BV(PC7); //ON trimled10/PIN30
      
    }    
        
    else if (Trim >= 0.88 && Trim <= 1.00)
    {
        PORTG &= ~_BV(PG2); //OFF trimled1/PIN39
        PORTD &= ~_BV(PD7); //OFF trimled2/PIN38
        PORTC &= ~_BV(PC0); //OFF trimled3/PIN37
        PORTC &= ~_BV(PC1); //OFF trimled4/PIN36
        PORTC &= ~_BV(PC2); //OFF trimled5/PIN35
        PORTC &= ~_BV(PC3); //OFF trimled6/PIN34
        PORTC &= ~_BV(PC4); //OFF trimled7/PIN33
        PORTC &= ~_BV(PC5); //OFF trimled8/PIN32
        PORTC &= ~_BV(PC6); //OFF trimled9/PIN31
        PORTC |= _BV(PC7); //ON trimled10/PIN30
   
    }    




 
        if(flapPos == 0)
        {
        PORTL |= _BV(PL0); //ON flapsled1/PIN49
        PORTL &= ~_BV(PL1); //OFF flapsled2/PIN48
        PORTL &= ~_BV(PL2); //OFF flapsled3/PIN47
        PORTL &= ~_BV(PL3); //OFF flapsled4/PIN46
        PORTL &= ~_BV(PL4); //OFF flapsled5/PIN45
        PORTL &= ~_BV(PL5); //OFF flapsled6/PIN44
        PORTL &= ~_BV(PL6); //OFF flapsled7/PIN43
        PORTL &= ~_BV(PL7); //OFF flapsled8/PIN42
        PORTG &= ~_BV(PG0); //OFF flapsled9/PIN41
        PORTG &= ~_BV(PG1); //OFF flapsled10/PIN40
        }
        
        else if(flapPos == 1)
        {
        PORTL |= _BV(PL0); //ON flapsled1/PIN49
        PORTL &= ~_BV(PL1); //OFF flapsled2/PIN48
        PORTL &= ~_BV(PL2); //OFF flapsled3/PIN47
        PORTL &= ~_BV(PL3); //OFF flapsled4/PIN46
        PORTL &= ~_BV(PL4); //OFF flapsled5/PIN45
        PORTL &= ~_BV(PL5); //OFF flapsled6/PIN44
        PORTL &= ~_BV(PL6); //OFF flapsled7/PIN43
        PORTL &= ~_BV(PL7); //OFF flapsled8/PIN42
        PORTG &= ~_BV(PG0); //OFF flapsled9/PIN41
        PORTG &= ~_BV(PG1); //OFF flapsled10/PIN40
        }
        
        else if(flapPos == 2)
        {
        PORTL |= _BV(PL0); //ON flapsled1/PIN49
        PORTL |= _BV(PL1); //ON flapsled2/PIN48
        PORTL &= ~_BV(PL2); //OFF flapsled3/PIN47
        PORTL &= ~_BV(PL3); //OFF flapsled4/PIN46
        PORTL &= ~_BV(PL4); //OFF flapsled5/PIN45
        PORTL &= ~_BV(PL5); //OFF flapsled6/PIN44
        PORTL &= ~_BV(PL6); //OFF flapsled7/PIN43
        PORTL &= ~_BV(PL7); //OFF flapsled8/PIN42
        PORTG &= ~_BV(PG0); //OFF flapsled9/PIN41
        PORTG &= ~_BV(PG1); //OFF flapsled10/PIN40
        }
        
        else if(flapPos == 3)
        {
        PORTL |= _BV(PL0); //ON flapsled1/PIN49
        PORTL |= _BV(PL1); //ON flapsled2/PIN48
        PORTL |= _BV(PL2); //ON flapsled3/PIN47
        PORTL &= ~_BV(PL3); //OFF flapsled4/PIN46
        PORTL &= ~_BV(PL4); //OFF flapsled5/PIN45
        PORTL &= ~_BV(PL5); //OFF flapsled6/PIN44
        PORTL &= ~_BV(PL6); //OFF flapsled7/PIN43
        PORTL &= ~_BV(PL7); //OFF flapsled8/PIN42
        PORTG &= ~_BV(PG0); //OFF flapsled9/PIN41
        PORTG &= ~_BV(PG1); //OFF flapsled10/PIN40
        }
        
        else if(flapPos == 4)
        {
        PORTL |= _BV(PL0); //ON flapsled1/PIN49
        PORTL |= _BV(PL1); //ON flapsled2/PIN48
        PORTL |= _BV(PL2); //ON flapsled3/PIN47
        PORTL |= _BV(PL3); //ON flapsled4/PIN46
        PORTL &= ~_BV(PL4); //OFF flapsled5/PIN45
        PORTL &= ~_BV(PL5); //OFF flapsled6/PIN44
        PORTL &= ~_BV(PL6); //OFF flapsled7/PIN43
        PORTL &= ~_BV(PL7); //OFF flapsled8/PIN42
        PORTG &= ~_BV(PG0); //OFF flapsled9/PIN41
        PORTG &= ~_BV(PG1); //OFF flapsled10/PIN40
        }
        
        else if(flapPos == 5)
        {
        PORTL |= _BV(PL0); //ON flapsled1/PIN49
        PORTL |= _BV(PL1); //ON flapsled2/PIN48
        PORTL |= _BV(PL2); //ON flapsled3/PIN47
        PORTL |= _BV(PL3); //ON flapsled4/PIN46
        PORTL |= _BV(PL4); //ON flapsled5/PIN45
        PORTL &= ~_BV(PL5); //OFF flapsled6/PIN44
        PORTL &= ~_BV(PL6); //OFF flapsled7/PIN43
        PORTL &= ~_BV(PL7); //OFF flapsled8/PIN42
        PORTG &= ~_BV(PG0); //OFF flapsled9/PIN41
        PORTG &= ~_BV(PG1); //OFF flapsled10/PIN40
        }
        
        else if(flapPos == 6)
        {
        PORTL |= _BV(PL0); //ON flapsled1/PIN49
        PORTL |= _BV(PL1); //ON flapsled2/PIN48
        PORTL |= _BV(PL2); //ON flapsled3/PIN47
        PORTL |= _BV(PL3); //ON flapsled4/PIN46
        PORTL |= _BV(PL4); //ON flapsled5/PIN45
        PORTL |= _BV(PL5); //ON flapsled6/PIN44
        PORTL &= ~_BV(PL6); //OFF flapsled7/PIN43
        PORTL &= ~_BV(PL7); //OFF flapsled8/PIN42
        PORTG &= ~_BV(PG0); //OFF flapsled9/PIN41
        PORTG &= ~_BV(PG1); //OFF flapsled10/PIN40
        }
               
        else if(flapPos == 7)
        {
        PORTL |= _BV(PL0); //ON flapsled1/PIN49
        PORTL |= _BV(PL1); //ON flapsled2/PIN48
        PORTL |= _BV(PL2); //ON flapsled3/PIN47
        PORTL |= _BV(PL3); //ON flapsled4/PIN46
        PORTL |= _BV(PL4); //ON flapsled5/PIN45
        PORTL |= _BV(PL5); //ON flapsled6/PIN44
        PORTL |= _BV(PL6); //ON flapsled7/PIN43
        PORTL &= ~_BV(PL7); //OFF flapsled8/PIN42
        PORTG &= ~_BV(PG0); //OFF flapsled9/PIN41
        PORTG &= ~_BV(PG1); //OFF flapsled10/PIN40
        }
        
        else if(flapPos == 8)
        {
        PORTL |= _BV(PL0); //ON flapsled1/PIN49
        PORTL |= _BV(PL1); //ON flapsled2/PIN48
        PORTL |= _BV(PL2); //ON flapsled3/PIN47
        PORTL |= _BV(PL3); //ON flapsled4/PIN46
        PORTL |= _BV(PL4); //ON flapsled5/PIN45
        PORTL |= _BV(PL5); //ON flapsled6/PIN44
        PORTL |= _BV(PL6); //ON flapsled7/PIN43
        PORTL |= _BV(PL7); //ON flapsled8/PIN42
        PORTG &= ~_BV(PG0); //OFF flapsled9/PIN41
        PORTG &= ~_BV(PG1); //OFF flapsled10/PIN40
        }
        
         else if(flapPos == 9)
         {
        PORTL |= _BV(PL0); //ON flapsled1/PIN49
        PORTL |= _BV(PL1); //ON flapsled2/PIN48
        PORTL |= _BV(PL2); //ON flapsled3/PIN47
        PORTL |= _BV(PL3); //ON flapsled4/PIN46
        PORTL |= _BV(PL4); //ON flapsled5/PIN45
        PORTL |= _BV(PL5); //ON flapsled6/PIN44
        PORTL |= _BV(PL6); //ON flapsled7/PIN43
        PORTL |= _BV(PL7); //ON flapsled8/PIN42
        PORTG |= _BV(PG0); //ON flapsled9/PIN41
        PORTG &= ~_BV(PG1); //OFF flapsled10/PIN40
        }
        
        else if(flapPos == 10)
        {
        PORTL |= _BV(PL0); //ON flapsled1/PIN49
        PORTL |= _BV(PL1); //ON flapsled2/PIN48
        PORTL |= _BV(PL2); //ON flapsled3/PIN47
        PORTL |= _BV(PL3); //ON flapsled4/PIN46
        PORTL |= _BV(PL4); //ON flapsled5/PIN45
        PORTL |= _BV(PL5); //ON flapsled6/PIN44
        PORTL |= _BV(PL6); //ON flapsled7/PIN43
        PORTL |= _BV(PL7); //ON flapsled8/PIN42
        PORTG |= _BV(PG0); //ON flapsled9/PIN41
        PORTG |= _BV(PG1);//ON flapsled10/PIN40
        }

       }   
       
 }