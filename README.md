# AutomaticFishFeeder
Automatic fish feeder project for Kajonkietsuksa School.

## Warnings ⚠
* It is always recommended to place the fish feeder either vertically or horizontally. Turning it over will cause the components to fall out.
* Although it shouldn't be used in real-world applications just yet, it still can. Here are the reasons why it should not be used yet.
  * Error handling implementation is still lacking. 
  * Some systems had not been tested fully.
  * The amount of food discharged by the food discharge mechanism is still inconsistent.
 
## Features
* The feeder is design to store about 500 grams of fish food. However how much it can store will also depend on the fish food that is use.
* Up to 4 feeding time can be set.
* Intregration with Netpie and LineNotify.
* ...

## Guides 
 🔴 **This guide will be for the ArduinoIDE. I will assume that you already know the basics and have already setup the IDE to work with an ESP8266.**

### Donwload
First step go to the [release](https://github.com/Nongtajkrub/AutomaticFishFeeder/releases/tag/v0.01-alpha) page to download the code. Download the zip name "release.rar".

### Dependencies
To compile and upload the code, these dependencies are needed.
* [Servo](https://www.arduino.cc/reference/en/libraries/servo/)  
* [NTPClient](https://www.arduino.cc/reference/en/libraries/ntpclient/)
* [PubSubClient](https://www.arduino.cc/reference/en/libraries/pubsubclient/)

### Netpie
 🔴 **I will assume that you already know the basic of Netpie**
1. Set up your project create a device.
2. For the device schema put this in.
```json
{
  "additionalProperties": false,
  "properties": {
    "food_remaining": {
      "type": "number"
    },
    "low_food_threshold": {
      "type": "number"
    },
    "refill_time": {
      "type": "string"
    }
  }
}
```
3. For the device shadow put this in.
```json
{
  "food_remaining": 100,
  "low_food_threshold": 0,
  "refill_time": ""
}
```
4. Create a trigger this will be use to trigger LineNotify


### Setup
1. Create a project in ArduinoIDE call it what ever you want.
2. After the project is create extract the zip you downloaded into the project directory. Incase you are confuse I am talking about the zip folder you downloaded earlier name "release.rar".
3. Copy the code from main.cpp to your main .ino file in the project directory. The main .ino file will be name after your project name. So if your project name is "Fish" your main .ino file will be name "Fish.ino".
4. Go into your main .ino file. And go to this section of the code it should be on the 29th line.
   
```cpp
const struct Program::Data program_data = {
	.netpie = {
		.MQTT_SERVER = "mqtt.netpie.io",
		.MQTT_CLIENT_ID = "ClientId",
		.MQTT_USERNAME = "Token",
		.MQTT_PASSWORD = "Secret",
		.MQTT_PORT = 1883,
	},
	.feeder = {
		.NTP_CLIENT = &timer,
		.EMPTY_THRESHOLD = 0,
		.DISCHARGE_PER_SESSION = 0,
		.FEEDING_BEFORE_EMPTY = 0,
		.SERVO_DISCHARGE_ANGLE = 180,
		.SERVO_PIN = 13,
		.REFILL_TIME = {0, 0},
		.FEEDING_TIME1 = {0, 0},
		.FEEDING_TIME2 = {0, 0},
		.FEEDING_TIME3 = {0, 0},
		.FEEDING_TIME4 = {0, 0}
	}
};
```

Here is where you can tweak the setting of the fish feeder. Let's go through all the settings.

#### Netpie settings

`MQTT_SERVER` - Do not change this.  
`MQTT_CLIENT_ID` - Your Netpie device ClientID.  
`MQTT_USERNAME` - Your Netpie device Token  
`MQTT_PASSWORD` - Your Netpie device Secret  
`MQTT_PORT` - Do not change this.  

#### Feeder settings
🔴 **The feeder tracks how much food is remaining by setting the default max food remaining to 100. When food is discharged, this value will go down depending on the `FEEDING_BEFORE_EMPTY` setting. So if you set `FEEDING_BEFORE_EMPTY` to 5, that means that each time the feeder discharges the food, the value would reduce by 20. So the first feeder discharges the food *100 - 20 = 80* the food remaining is 80. The second time *80 - 20 = 60*, the food remaining is 60. This repeats until the food remaming hits 0.**

`NTP_CLIENT` - Do not change this.  
`EMPTY_THRESHOLD` - Set the threshold for triggering a low food warning. You should set this value about 10 units higher than what you need. If you need 20 units, set it to 30.  

`DISCHARGE_PER_SESSION` - How many times the feeder will discharge food per one feeding session. So if you want to dispense 100 grams per one session but the feeder can only release 20 grams at a time, set this value to 5.

`FEEDING_BEFORE_EMPTY` - How many time can the feeder discharge food before it is empty. This value vary depending on the type of food you use or the amount of food you use.   

`SERVO_DISCHARGE_ANGLE` - Do not change this.  
`SERVO_PIN` - Do not change this.  
`REFILL_TIME` - when to refill the feeder food container. If you want to set it to 12:30 oclock you will have to set this settign to {12, 30}.

`FEEDING_TIME1` ... `FEEDING_TIME4` - The 4 feeding times. These values can't be duplicated. If you already set one to {12, 30} (12:30 oclock), you can't set the other one to 12:30 anymore. 

### Upload
After you are done with tweaking the settings, verify the code and upload it to your board. After looking at the behavior of the feeder, you can also further tweak the setting and reupload the code again until you are satisfied.

## Conclusion
If you need any help pls contact Taj Borthwick on line or email to sunanborthwic@gmail.com
