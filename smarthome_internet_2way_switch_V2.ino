//FirebaseESP8266.h must be included before ESP8266WiFi.h
// Firebase ESP8266 library
#include <FirebaseESP8266.h> 
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "smarthome-auto-default-rtdb.firebaseio.com"

#define FIREBASE_AUTH "I2H7kHib2SXJmSbeHgZB28x43pxKHB6YVJAeb2iH"

#define UserId "EC LAB"
#define password "Diploma@EC"

//Define FirebaseESP8266 data object
FirebaseData firebasedata;
FirebaseJson json;

int debug=0;

// load output pin define
int fan = D7;
int light1 = D3;
int light2 = D4;

int fan_sen = D2;
int light1_sen = D5;
int light2_sen = D6;


// switch status store 
int fan_sw_status = 0;
int light1_sw_status = 0;
int light2_sw_status = 0;

// app button status store 
int fan_app_status = 0;
int light1_app_status = 0;
int light2_app_status = 0;

// final load status store 
int fan_status = 0;
int light1_status = 0;
int light2_status = 0;


/*   NOTE :- VOID SETUP SYNTAX RUN ONLY ONE TIME AND VOID LOOP SYNTAX RUN CONTINUOUSLY    */ 


// void setup start....void setup start....void setup start...
   
void setup()
{

  Serial.begin(115200);

  pinMode(fan, OUTPUT);
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(fan_sen, INPUT_PULLUP);
  pinMode(light1_sen, INPUT_PULLUP);
  pinMode(light2_sen, INPUT_PULLUP); 

  WiFi.begin(UserId, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(50);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);    
                           
}


// void loop start....void loop start....void loop start...
void loop()
{
                                         
  // Read 2 way switch position using sensor     
 
 fan_sw_status= digitalRead(fan_sen);        
    
 if(debug==1)
   { delay(900); 
Serial.print("Fan switch status : ");               Serial.println(fan_sw_status);}      
    
light1_sw_status=digitalRead(light1_sen);         
     
if(debug==1)
   { delay(900); 
Serial.print("Light1 switch status : ");               Serial.println(light1_sw_status);}       
    
    
light2_sw_status=digitalRead(light2_sen);          
  
if(debug==1)
   { delay(900); 
Serial.print("Light2 switch status : ");               Serial.println(light2_sw_status);}       
      
// app load staus read on firebase database ................................            
        
 if(Firebase.getString(firebasedata, "fan/"))
{  if(firebasedata.stringData()== "1")
     { fan_app_status=1;
       digitalWrite(fan,LOW); }
   else 
     { fan_app_status=0;
       digitalWrite(fan,HIGH); }
}    
 
if(debug==1)
   { delay(900); 
Serial.print("Fan app status : ");               Serial.println(fan_app_status);}              
    
if(Firebase.getString(firebasedata, "light1/"))
{                                          if(firebasedata.stringData()== "1")
    { light1_app_status=1;
      digitalWrite(light1, LOW); }
  else 
    { light1_app_status=0;
      digitalWrite(light1, HIGH); }    
}

if(debug==1)
 { delay(900); 
Serial.print("Light1 app status : ");               Serial.println(light1_app_status);}        
        
if(Firebase.getString(firebasedata, "light2/"))
{                                          if(firebasedata.stringData()== "1")
    { light2_app_status=1;
      digitalWrite(light2, LOW); }
  else 
    { light2_app_status=0;
      digitalWrite(light2, HIGH); }
}
    
if(debug==1)
   { delay(900); 
Serial.print("Light2 app status : ");               Serial.println(light2_app_status);}        
    
// load feedback send on firebase database................................    
fan_status= (fan_sw_status ^ fan_app_status);

if(debug==1)
   { delay(900); 
Serial.print("Fan status XOR operation : ");               Serial.println(fan_status);}        
        
light1_status= (light1_sw_status ^ light1_app_status);

if(debug==1)
   { delay(900); 
Serial.print("Light1 status XOR operation : ");               Serial.println(light1_status);}       
        
light2_status= (light2_sw_status ^ light2_app_status);      

if(debug==1)
   { delay(900); 
Serial.print("Light2 status XOR operation : ");               Serial.println(light2_status);}       
 
 if (fan_status==0)   
    { fan_status=1;}
 else 
    { fan_status=0;}
    
 if (light1_status==0)   
    { light1_status=1;}
 else 
    { light1_status=0;} 
         
 if (light2_status==0)   
   { light2_status=1;}   
 else 
    { light2_status=0;}
               
Firebase.setInt(firebasedata, "fanfeed/",fan_status);
    
Firebase.setInt(firebasedata, "light1feed/",light1_status);

Firebase.setInt(firebasedata, "light2feed/",light2_status);
    
}


 
 
      
