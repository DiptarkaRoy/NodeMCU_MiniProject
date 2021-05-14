#include <ESP8266WiFi.h>           // Include the Wi-Fi library

int FloatSensorHigh = 12;              //D6 pin of NodeMCU
int FloatSensorLow = 15;               //D8 pin of NodeMCU
int relay = 5;                         // D1 pin of NodeMCU
int upperLimit,lowerLimit;             //reads pushbutton status
int value;
String waterLevel,motorStatus;

const char *ssid = "DEEPSARA_2G";  // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "a1b2c3d4"; // The password of the Wi-Fi network


WiFiServer server(80);
void motorON(){
    digitalWrite(relay, HIGH); // if request is ON, turn ON the relay.
     motorStatus = "true"; 
}
void motorOFF(){
    digitalWrite(relay, LOW); // if request is OFF, turn OFF the relay.    
    motorStatus = "false";
}
void setup()
{
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  WiFi.begin(ssid, password); // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED)
  { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i);
    Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

  server.begin();                   //Starting the Server
  Serial.println("Server started"); //Server Started message

  pinMode(FloatSensorHigh, INPUT_PULLUP); //Arduino Internal Resistor 10K
  pinMode(FloatSensorLow, INPUT_PULLUP); //Arduino Internal Resistor 10K
  pinMode(relay, OUTPUT);              // set relay pin as output
  motorOFF();
  delay(4000);
}

void loop()
{
  
  upperLimit = digitalRead(FloatSensorHigh); // read the value of FloatSensorHigh sensor
  lowerLimit = digitalRead(FloatSensorLow); // read the value of FloatSensorLow sensor

  bool tooHigh = (lowerLimit == LOW && lowerLimit == LOW); // if both the float sensors are floating
  bool tooLow = (lowerLimit == HIGH && lowerLimit == HIGH); // if both the float sensors are not floating

  
  
  if (tooHigh)   // if the value is tooHIGH 
  {                                        
    Serial.println("WATER LEVEL - HIGH");
    waterLevel = "true";
    motorOFF();         //turn OFF the motor
  }
  else if(tooLow)
  {
    Serial.println("WATER LEVEL - LOW");   // if the value is tooLOW
    waterLevel = "false";                     
    motorON();        //turn ON the motor
  }
  
  WiFiClient client = server.available(); // Check if a client has connected
  if (!client)
  {
    return;
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  // Match the request

  if (request.indexOf("/MOTOR=ON") != -1 && !(tooLow||tooHigh))       //if the value is neither tooLow or tooHigh then do whatever the user says
  {
     motorON();   
  }
  if (request.indexOf("/MOTOR=OFF") != -1 && !(tooLow||tooHigh))      //if the value is neither tooLow or tooHigh then do whatever the user says
  {
    motorOFF();
  }
  delay(100);
  
  // Prepare the response
 String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html>\n<html lang=\"en\">\n\n<head>\n    <meta charset=\"UTF-8\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n <meta http-equiv=\"refresh\" content=\"15\">\n   <title>IOT Water-level Indicator NodeMCU</title>\n    <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\">\n    <link href=\"https://fonts.googleapis.com/css2?family=Kiwi+Maru:wght@500&display=swap\" rel=\"stylesheet\">\n    <link href=\"https://fonts.googleapis.com/css2?family=Fira+Code:wght@500&display=swap\" rel=\"stylesheet\">\n\n    <style>\n        body {\n            height: 100vh;\n            overflow-y: hidden;\n        }\n\n        .navbar {\n            color: white;\n            background: black;\n            width: 100%;\n            font-size: 30px;\n        }\n\n        main {\n            height: 100%;\n            background: aliceblue;\n        }\n\n        .top {\n            width: 100%;\n            height: 50%;\n            display: flex;\n            border-bottom: thin solid black;\n            font-size: 13px;\n        }\n\n        .bottom {\n            width: 100%;\n            height: 50%;\n            display: flex;\n            border-top: thin solid black;\n        }\n\n        #sensor-info {\n            width: 60%;\n            height: 100%;\n            padding-top: 15px;\n            border-right: thin solid black;\n        }\n\n        #sensor-log {\n            overflow-y: scroll;\n            width: 40%;\n            height: 100%;\n            padding-top: 15px;\n            background: rgb(39, 39, 39);\n            color: whitesmoke;\n            font-family: 'Fira Code', monospace;\n        }\n\n        #motor-control {\n            display: flex;\n        }\n\n        * {\n            margin: 0px;\n            padding: 0px;\n            text-align: center;\n            font-family: 'Kiwi Maru', serif;\n            box-sizing: border-box;\n            justify-content: center;\n            align-items: center;\n        }\n\n        .log {\n            padding-left: 10px;\n            text-align: left;\n            font-family: 'Fira Code', monospace;\n        }\n\n        .switch-label {\n            margin-right: 15px;\n            font-weight: 600;\n        }\n\n        .switch {\n            position: relative;\n            height: 40px;\n            width: 80px;\n            -webkit-appearance: none;\n            background: #c6c6c6;\n            outline: none;\n            border-radius: 20px;\n            box-shadow: inset 0 0 5px rgba(0, 0, 0, 0.2);\n            transition: 0.5s;\n        }\n\n        .switch:checked {\n            background: #03a9f4;\n        }\n\n        .switch::before {\n            content: '';\n            position: absolute;\n            width: 40px;\n            height: 40px;\n            border-radius: 20px;\n            top: 0px;\n            left: 0px;\n            background: #fff;\n            transform: scale(1.1);\n            box-shadow: 0 2px 5px rgba(0, 0, 0, .2);\n            transition: .5s;\n        }\n\n        .switch:checked::before {\n            left: 40px;\n        }\n    </style>\n</head>\n\n<body>\n    <nav class=\"navbar\">Smart IOT based Water level Indicator</nav>\n    <main>\n        <div class=\"top\">\n            <div id=\"sensor-info\">\n                <div>Water Level - <span id=\"water-status\">EMPTY</span></div>\n            </div>\n            <div id=\"sensor-log\">\n                <!-- log will show here -->\n            </div>\n        </div>\n        <div class=\"bottom\">\n            <div id=\"control-section\">\n                <div id=\"motor-control\">\n                    <p class=\"switch-label\">Motor Switch</p>\n                   <form action=\"/MOTOR=ON\" method=get  name=\"tickthebox\"> \n <input class=\"switch\" type=\"checkbox\" name=\"motor-switch\">\n </form>\n                </div>\n            </div>\n        </div>\n    </main>\n    <script>\n  function toggle() {\n            if(motorSwitch[0].checked == true){\n                window.location = \"http://192.168.0.194//MOTOR=ON\";\n            }\n            else{\n                window.location = \"http://192.168.0.194//MOTOR=OFF\";\n            }\n        }      //DOM variables\n        const motorSwitch = document.getElementsByClassName('switch'),\n            sensorLog = document.querySelector('#sensor-log');\n\n        //Variables\n        let newLog,\n            time = new Date();\n\n        // NodeMCU Variables\n        const waterLevel = ";
  s+=waterLevel;
  s+=";\n        let motorStatusBoolean = ";
  s+=motorStatus;
  s+=";\n\n        //Initialising everything\n        init();\n\n        //============== functions and middlewares==================// \n\n        function init() {\n            setInterval(() => {\n                changeWaterStatus();\n                changeMotorStatus();\n            }, 1000);  //this code checks motor and water status every second\n        }\n\n        function changeWaterStatus() {\n            if (waterStatus.textContent !== 'FULL' && waterLevel) {\n                waterStatus.textContent = 'FULL';\n            } else if (waterStatus.textContent !== 'EMPTY' && !waterLevel) {\n                waterStatus.textContent = 'EMPTY';\n            } else if (waterLevel === undefined) {\n                alert('Water level information not found');\n            }\n        }\n\n\n        function changeMotorStatus() {\n            if (motorSwitch[0].checked !== motorStatusBoolean) {\n                time = \"unknown\";\n                changeMotorLog(time);\n            }\n        }\n\n        function changeMotorLog(time) {\n            if (motorStatusBoolean == true) {\n                motorSwitch[0].checked = true;\n                motorON(time);\n            } else {\n                motorSwitch[0].checked = false;\n                motorOFF(time);\n            }\n        }\n\n        function motorON(time) {\n            newLog = document.createElement(\"div\");\n            newLog.classList.add(\"log\")\n            newLog.innerText = `~Motor Switched ON at ${time}`;\n            sensorLog.append(newLog);\n            motorStatusBoolean = true;\n\n            //ADD FUNCTIONALITY FOR TURNING ON THE MOTOR.\n            // The functionality will send a signal to the NodeMCU and turn the motor on.\n\n            // Insert code here.\n        }\n\n        function motorOFF(time) {\n            newLog = document.createElement(\"div\");\n            newLog.classList.add(\"log\")\n            newLog.innerText = `~Motor Switched OFF at ${time}`;\n            sensorLog.append(newLog);\n\n            //ADD FUNCTIONALITY FOR TURNING OFF THE MOTOR.\n            // The functionality will send a signal to the NodeMCU and turn the motor on.\n\n            // Insert code here.\n        }\n\n        // TOGGLES and EVENTS\n        motorSwitch[0].addEventListener(\"click\", () => {\n            motorStatusBoolean = !motorStatusBoolean;\n            time = new Date();\n            changeMotorLog(time);\n\n            let currentlocation = window.location.origin + \"/MOTOR=ON\";\n            console.log(currentlocation);\n            if (motorSwitch[0].checked == true) {\n                window.location = window.location.origin + \"/MOTOR=ON\";\n            }\n            else {\n                window.location = window.location.origin + \"/MOTOR=OFF\";\n            }\n        })\n var waterStatus = document.querySelector('#water-status');\n\n        // TOGGLES and EVENTS\n\n        function changeWaterStatus() {\n            if (waterStatus.textContent !== 'FULL' && waterLevel) {\n                waterStatus.textContent = 'FULL';\n            } else if (waterStatus.textContent !== 'EMPTY' && !waterLevel) {\n                waterStatus.textContent = 'EMPTY';\n            } else if (waterLevel === undefined) {\n                alert('Water level information not found');\n            }\n        }\n\n        // Runs the above function every second and sees if the value of water level has changed or not.\n        setInterval(\"changeWaterStatus()\", 1000);\n    </script>\n</body>\n</html>\n<!-- https://tomeko.net/online_tools/cpp_text_escape.php?lang=en -->";
  client.print(s); // all the values are send to the webpage
  delay(100);
}