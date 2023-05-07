#include <WiFi.h>
#include <WebServer.h>
const char* ssid     = "MI10T";
const char* password = "123212321";
/* create a server and listen on port 8088 */

String html ="<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n    <meta charset=\"UTF-8\">\n    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n    <title>Document</title>\n    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js\"></script>\n    <style>\n        body{\n            margin:2rem;\n            background: linear-gradient(\n                0deg,#dae90d 0%, #e2a407 100%\n            ) ;\n            height: 95vh; \n            padding: 1em;\n        }\n        .container{\n            margin:5rem;\n            display:flex;\n            justify-content: space-between;\n        }\n        .half{\n            display:flex;\n            justify-content: space-between;\n        }\n        .empty{\n            flex: 1;\n            margin: 0 10px;\n        }\n        .range-slider{\n            max-width: 30em;\n            margin: 8em auto;\n            position: relative;\n            display:flex;\n            \n\n        }\n\n        .middle {\n            display: flex;\n            /* 水平置中 */\n            justify-content: center;    \n            /* 垂直置中 */\n            align-items: center;        \n            }\n        .range-slider .slider{\n            -webkit-appearance: none;\n            width:10rem;\n            height: 1.4em;\n            outline:none;\n            border-radius: 3px;\n            background: #e8e6e1;\n            box-shadow: \n                3px 3px 6ppx #000\n                insert 1px 1px 1px #909090;\n        }\n\n        .range-slider .slider::-webkit-slider-thumb{\n            -webkit-appearance: none;\n            width:1.7em;\n            height: 1.7em;\n            cursor: pointer;\n            z-index:3;\n            position:relative;\n        }\n\n        .range-slider .slider-thumb{\n            position: absolute;\n            width:1.7em;\n            height: 1.7em;\n            background:#909090;\n            border-radius: 50%;\n            top:50%;\n            left:50%;\n            transform: translate(-50%,-50%);\n            z-index:2;\n            box-shadow: inset 0px 1px 2px #909090\n        }\n\n        .range-slider .slider-thumb::before{\n            content: '';\n            position:absolute;\n            top:50%;\n            left:50%;\n            transform: translate(-50%,-50%);\n            width:0.7em;\n            height: 0.7em;\n            background: #333;\n            border-radius: inherit;\n            transition: 0.3s;\n        }\n\n        .range-slider:hover .slider-thumb::before{\n            background: #2ae0c0;\n\n        }\n        .range-slider .tooltip{\n            position: absolute;\n            width:2.8em;\n            height: 2em;\n            top:-6em;\n            left:52%;\n            transform: translate(-50%,-50%);\n            background: #333;\n            text-align: center;\n            line-height: 35px;\n            color: #fff;\n            border-radius: 3px;\n            box-shadow: \n                3px 3px 6ppx #000,\n                insert 0px 1px 2px #909090;\n        }\n        .range-slider .tooltip::before{\n            content:'';\n            position: absolute;\n            width:0;\n            height: 0;\n            border-left:  6px solid transparent;\n            border-right:  6px solid transparent;\n            border-top:  10px solid #909090;\n            bottom: -0.5em;\n            left: 50%;\n            transform: translate(-50%);\n        }\n\n        .range-slider .progress2{\n            width: 50%;\n            height: 1.4em;\n            border-radius: 3px;\n            background: linear-gradient(\n                90deg, #335bf4 0%, #2ae9c9 100%\n            ) ; \n            position: absolute;\n            top: 50%;\n            transform: translateY(-50%);\n            left:0;\n            pointer-events: none;\n        }\n        .range-slider .progresst{\n            width: 50%;\n            height: 1.4em;\n            border-radius: 3px;\n            background: linear-gradient(\n                90deg, #335bf4 0%, #b4ac0d 100%\n            ) ; \n            position: absolute;\n            top: 50%;\n            transform: translateY(-50%);\n            left:0;\n            pointer-events: none;\n        }\n        @media  screen and (max-width: 700px) {\n            .neu-range-slider{\n                width:100%;\n            }\n        }\n\n        .vertical{\n            transform: rotate(-90deg) ;\n        }\n\n        .toggle__input{\n            visibility: hidden;\n            pointer-events: none;\n            }\n\n            .toggle__label{\n            display: inline-block;\n            width: 60px;\n            height: 30px;\n            border: 2px solid lightgrey;\n            border-radius: 30px;\n            background: #ffe4e4;\n            cursor: pointer;\n            \n            position: relative;\n            }\n\n            .toggle__label::before{\n                content:'off';\n                display: inline-block;\n                width: 30px;\n                height: 30px;\n                background: #af4154;\n                border-radius: 50%;\n                color: #fff;\n                line-height: 30px;\n                text-align: center;\n                font-size: 15px;\n                position: absolute;\n                left: 0;\n                top: 0;\n                transform: rotate(0);\n                \n                transition: 1s;\n                }\n                .toggle__input:checked + .toggle__label{\n                    background: #bedce3;\n                    }\n\n                    .toggle__input:checked + .toggle__label::before{\n                    content:'on';\n                    background: #0b7fab;\n                    left: 30px;\n                    transform: rotate(360deg);\n                    }\n\n                .slider:disabled {\n                    opacity: 0.5;\n                    }\n    </style>\n</head>\n<body>\n    <h1 class=\"middle\"><big><big><big><big>LIGHT CONTROL</big></big></big></big></h1>\n    <div class =\"container \">\n        <div class = \"half\">\n            <div class = \"range-slider \">\n                <div class=\"tooltip \"></div>\n                \n                <div class = \"vertical\">\n                    <input type=\"range\" min=\"0\" max=\"99\" value=\"50\" class=\"slider\" height=\"10rem\" onchange=\"sendSliderData('1', this.value)\"id=\"slider1\">\n                    <div class=\"slider-thumb\"></div>\n                    <div class=\"progress2\"></div>\n                </div>\n                \n            </div>\n            <div class = \"range-slider \">\n                <div class=\"tooltip \"></div>\n                \n                <div class = \"vertical\">\n                    <input type=\"range\" min=\"0\" max=\"99\" value=\"50\" class=\"slider\"onchange=\"sendSliderData('2', this.value)\"id=\"slider2\">\n                    <div class=\"slider-thumb\"></div>\n                    <div class=\"progress2\"></div>\n                </div>\n                \n            </div>\n   \n        </div>\n        <div class=\"empty\"></div>\n        <div class = \"half\">\n            <div class = \"range-slider \">\n                <div class=\"tooltip \"></div>\n                \n                <div class = \"vertical\">\n                    <input type=\"range\" min=\"0\" max=\"99\" value=\"50\" class=\"slider\"onchange=\"sendSliderData('3', this.value)\"id=\"slider3\">\n                    <div class=\"slider-thumb\"></div>\n                    <div class=\"progress2\"></div>\n                </div>\n                \n            </div>\n            <div class = \"range-slider \">\n                <div class=\"tooltip \"></div>\n                \n                <div class = \"vertical\">\n                    <input type=\"range\" min=\"0\" max=\"99\" value=\"50\" class=\"slider\"onchange=\"sendSliderData('4', this.value)\"id=\"slider4\">\n                    <div class=\"slider-thumb\"></div>\n                    <div class=\"progress2\"></div>\n                </div>\n                \n            </div>\n   \n        </div>\n        <div class=\"empty\"></div>\n        <div class = \"half\">\n            <div class = \"range-slider \">\n                <div class=\"tooltip \"></div>\n                \n                <div class = \"vertical\">\n                    <input type=\"range\" min=\"0\" max=\"99\" value=\"50\" class=\"slider\"onchange=\"sendSliderData('5', this.value)\"id=\"slider5\">\n                    <div class=\"slider-thumb\"></div>\n                    <div class=\"progress2\"></div>\n                </div>\n                \n            </div>\n            <div class = \"range-slider \">\n                <div class=\"tooltip \"></div>\n                \n                <div class = \"vertical\">\n                    <input type=\"range\" min=\"0\" max=\"99\" value=\"50\" class=\"slider\"onchange=\"sendSliderData('6', this.value)\"id=\"slider6\">\n                    <div class=\"slider-thumb\"></div>\n                    <div class=\"progress2\"></div>\n                </div>\n                \n            </div>\n   \n        </div>\n        <div class=\"empty\"></div>\n        <div class = \"half\">\n            <div class = \"range-slider \">\n                <div class=\"tooltip \"></div>\n                \n                <div class = \"vertical\">\n                    <input type=\"range\" min=\"0\" max=\"99\" value=\"50\" class=\"slider\"onchange=\"sendSliderData('7', this.value)\"id=\"slider7\">\n                    <div class=\"slider-thumb\"></div>\n                    <div class=\"progress2\"></div>\n                </div>\n                \n            </div>\n            <div class = \"range-slider \">\n                <div class=\"tooltip \"></div>\n                \n                <div class = \"vertical\">\n                    <input type=\"range\" min=\"0\" max=\"99\" value=\"50\" class=\"slider\"onchange=\"sendSliderData('8', this.value)\"id=\"slider8\">\n                    <div class=\"slider-thumb\"></div>\n                    <div class=\"progress2\"></div>\n                </div>\n                \n            </div>\n   \n        </div>\n        \n        \n    </div>\n    <div class=\"middle\">\n        <input id=\"toggle\" class=\"toggle__input\" type=\"checkbox\"onchange=\"sendManual(this.checked)\" ></input>\n        <label for=\"toggle\" class=\"toggle__label\"></label>\n    </div>\n    <script>\n        const container = document.querySelectorAll(\".range-slider\");\n\n        for(let i=0;i<container.length;i++){\n            const slider = container[i].querySelector(\".slider\");\n            const thumb = container[i].querySelector(\".slider-thumb\");\n            const tooltip = container[i].querySelector(\".tooltip\");\n            //const progress1 = container[i].querySelector(\".progress1\");\n            const progress2 = container[i].querySelector(\".progress2\");\n\n            function customSlider(){\n                const maxval = slider.getAttribute(\"max\");\n                const val = (slider.value/maxval)*100 +\"%\";\n                const opt =((slider.value/maxval)*50+50)+\"%\";\n\n                tooltip.innerHTML = slider.value;\n                tooltip.style.opacity = opt;\n                //progress1.style.width = val;\n                progress2.style.width = val;\n                thumb.style.left = val;\n            }\n\n            customSlider();\n\n            slider.addEventListener(\"input\",()=>{\n                customSlider();\n            })\n        }\n        function sendSliderData(sliderId, sliderValue) {\n        $.get(\"/web\", {id:sliderId, power: sliderValue }, function(data) {\n          console.log(\"Data sent successfully!\");\n        });\n        }   \n        function sendManual(manual) {\n        var slider1 = document.getElementById(\"slider1\");\n        var slider2 = document.getElementById(\"slider2\");\n        var slider3 = document.getElementById(\"slider3\");\n        var slider4 = document.getElementById(\"slider4\");\n        var slider5 = document.getElementById(\"slider5\");\n        var slider6 = document.getElementById(\"slider6\");\n        var slider7 = document.getElementById(\"slider7\");\n        var slider8 = document.getElementById(\"slider8\");\n        slider1.disabled = !manual;\n        slider2.disabled = !manual;\n        slider3.disabled = !manual;\n        slider4.disabled = !manual;\n        slider5.disabled = !manual;\n        slider6.disabled = !manual;\n        slider7.disabled = !manual;\n        slider8.disabled = !manual;\n            console.log(manual);\n        $.get(\"/web\", {man:manual}, function(data) {\n          console.log(\"Data sent successfully!\");\n        });\n        }   \n\n        \n    </script>\n</body>\n</html>";

WebServer web(80);
int cL1 = 0,cL2 = 0,cL3 = 0,cL4 = 0,Blub_color = 50,Blub_brightness = 50,L11,L12,L21,L22,L31,L32,L41,L42;
bool manmode = 0;
String toTwoDigit(int a){
    if(a<10){
      String aa = "";
      return aa+"0"+String(a);
    }
    if(a>99){
      Serial.print(a);
      Serial.print("to string error"); 
      return "99"  ;
    }
    return String(a);
}
String calculate_light(){
    if(!manmode){
      if(cL1 == 0){L11 = 0;}else{L11 = min(cL1*4/10 -(65-Blub_brightness)*8/10,99);L11 = max(0,L11);}
      if(cL2 == 0){L21 = 0;}else{L21 = min(cL2*4/10 -(65-Blub_brightness)*8/10,99);L21 = max(0,L21);}
      if(cL3 == 0){L31 = 0;}else{L31 = min(cL3*4/10 -(65-Blub_brightness)*8/10,99);L31 = max(0,L31);}
      if(cL4 == 0){L41 = 0;}else{L41 = min(cL4*4/10 -(65-Blub_brightness)*8/10,99);L41 = max(0,L41);}
      if(L11 == 0){L11 = min(10,L12/20);}
      if(L21 == 0){L21 = min(10,L11/30+L31/30);}
      if(L31 == 0){L31 = min(10,L12/30+L42/30);}
      if(L41 == 0){L41 = min(10,L31/20);}
      L12 = Blub_color;
      L22 = Blub_color;
      L32 = Blub_color;
      L42 = Blub_color; 
    }
    String calculated_result = toTwoDigit(L11)+toTwoDigit(L12)+toTwoDigit(L21)+toTwoDigit(L22)+toTwoDigit(L31)+toTwoDigit(L32)+toTwoDigit(L41)+toTwoDigit(L42);
    return calculated_result;
} 
void handleBlub(){
  String sControl = calculate_light();
  Serial.println("sControl");
  Serial.println(sControl);
  web.send(200, "text/plain",sControl);   
}
void handleLightmeter() {
  String color = web.arg("color");
  String bright = web.arg("bright");
  Blub_color = atoi(color.c_str());
  Blub_color = 100 - Blub_color;
  if (Blub_color >99){
    Blub_color = 99;
  }
  Blub_brightness = atoi(bright.c_str());
  Serial.println(color);
  Serial.println(bright);
  web.send(200, "text/plain","successful send"); 
}
void handleCamera() {
  /*String body = web.arg("plain");
  //web.send(200, "text/plain","Hello CLient"); 
  Serial.println(body);
  web.send(200, "text/plain","received");*/
  String ID1 = web.arg("ID1");
  String ID2 = web.arg("ID2");
  String ID3 = web.arg("ID3");
  String ID4 = web.arg("ID4");
  cL1 = atoi(ID1.c_str());
  cL2 = atoi(ID2.c_str());
  cL3 = atoi(ID3.c_str());
  cL4 = atoi(ID4.c_str());
  Serial.print(cL1);
  Serial.print(" ");
  Serial.print(cL2);
  Serial.print(" ");
  Serial.print(cL3);
  Serial.print(" ");
  Serial.println(cL4);
  web.send(200, "text/plain","received");
}
void handleWeb(){
  String id = "";
  String power = "";
  String manual = "";
  if(web.hasArg("id")){
    id = web.arg("id");
  }
  if(web.hasArg("power")){
    power = web.arg("power");
    if(id=="1"){
      L41 = atoi(power.c_str());
    }else if(id=="3"){
      L31 = atoi(power.c_str());
    }else if(id=="5"){
      L21 = atoi(power.c_str());
    }else if(id=="7"){
      L11 = atoi(power.c_str());
    }else if(id=="2"){
      L42 = atoi(power.c_str());
    }else if(id=="4"){
      L32 = atoi(power.c_str());
    }else if(id=="6"){
      L22 = atoi(power.c_str());
    }else if(id=="8"){
      L12 = atoi(power.c_str()); 
    }else{
      Serial.print("iderror");
    }
    Serial.print(id);
    Serial.print(":");
    Serial.println(power);
  }
  if(web.hasArg("man")){
    manual = web.arg("man");
    if(manual[0] == 't' or manual[0] == '1'){
      manmode = 1;
    }else{
      manmode = 0;
    }
    Serial.print("Manual mode:");
    Serial.println(manual);
  }
  web.send(200, "text/plain","successful!"); 
}
void handleRoot(){
  web.send(200, "text/html",html); 
}
void setup()
{   
    pinMode(2, OUTPUT);
    Serial.begin(115200);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    /* connecting to WiFi */
    WiFi.begin(ssid, password);
    /*wait until ESP32 connect to WiFi*/
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected with IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(2, HIGH);
    web.on("/lightmeter",HTTP_GET ,handleLightmeter);
    web.on("/camera", HTTP_GET, handleCamera); 
    web.on("/web", HTTP_GET, handleWeb); 
    web.on("/", HTTP_GET, handleRoot); 
    web.on("/blub", HTTP_GET, handleBlub); 
    /* start Server */
    web.begin();
}
void loop(){
    /* listen for client */
    web.handleClient();
    delay(2);
}