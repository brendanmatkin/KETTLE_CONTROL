// TODO load these files dynamically from SPIFFS

// for now, hard-coded literal:
static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8"/>
    <meta name = "viewport" content = "width = device-width, initial-scale = 1.0">
    <title>Kettle Thermostat</title>
    <style>
      body {
        background-color: #FFFFFF;
        font-family: Arial, Helvetica, Sans-Serif;
        color: #020202;
        -webkit-touch-callout:none;
        -webkit-user-select:none;
        -khtml-user-select:none;
        -moz-user-select:none;
        -ms-user-select:none;
        user-select:none;
      }
      .container {
        width: 85%;
        margin: 0 auto;
      }
      h3 {
        text-transform: lowercase;
        margin: 1.1em 0 0.75em;
      }

      .label {
          font-weight:normal;
          font-size: 80%;
      }

      /* slider css: */
      .slider {
          -webkit-appearance: none;
          width: 100%;
          height: 15px;
          /*margin: 15px 0;*/
          background: #e0e0e0;
          outline: none;
          opacity: 0.7;
          border-radius: 3px;
          -webkit-transition: .2s;
          transition: opacity .2s;
      }
      .slider:hover {
          opacity: 1;
      }
      .slider::-webkit-slider-thumb {
          -webkit-appearance: none;
          appearance: none;
          width: 32px;
          height: 32px;
          border-radius: 50%;
          background: #101010;
          cursor: pointer;
      }
      .slider::-moz-range-thumb {
          width: 30px;
          height: 30px;
          border-radius: 50%;
          background: #101010;
          cursor: pointer;
      }
      .disabled {
        opacity: 0.3;
      }
      .disabled::-webkit-slider-thumb {
        cursor: default;
      }
      .disabled:hover {
        opacity: 0.3;
      }

      .fields {
        padding: 2px;
        width: 100px;
        font-size:16px;
        /*margin: 0;*/
        margin: -10px 0;
      }

      button {
        width: 30%;
        height: 30px;
        font-size:12px;
        margin: 1%;
        border:none;
        cursor: pointer;
      }
      button:disabled {
        border: 2px solid #0033cc;
        color: #0033cc;
        cursor: default;
      }
      select {
        width: 30%;
        height: 30px;
        font-size: 12px;
        border: none;
        margin: 1%;
        cursor: pointer;
      }


      /* toggle switch stuff: */
      .switch {
        position: relative;
        display: inline-block;
        width: 60px;
        height: 34px;
        top: -5px;
      }
      .switch input {display:none;}
      .slide-switch {
        position: absolute;
        cursor: pointer;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
        background-color: #e0e0e0;
        -webkit-transition: .4s;
        transition: .4s;
        border-radius: 34px;
      }
      .slide-switch:before {
        position: absolute;
        content: "";
        height: 26px;
        width: 26px;
        left: 4px;
        bottom: 4px;
        background-color: white;
        -webkit-transition: .4s;
        transition: .4s;
        border-radius: 50%;
      }
      input:checked + .slide-switch {
        background-color: #101010;
        opacity:0.7;
      }
      input:focus + .slide-switch {
        box-shadow: 0 0 1px #101010;
        opacity:0.7;
      }
      input:checked + .slide-switch:before {
        -webkit-transform: translateX(26px);
        -ms-transform: translateX(26px);
        transform: translateX(26px);
      }

    </style>
  </head>
  <body>
    <div class = "container">
      <header>
        <h1>Kettle Thermostat</h1>
      </header>

      <h3>Current Temperature:</h3>
      <!--<h2 id="currentTemp"><span id="label_currentTemp">[Not Connected]</span>°C</h2>-->
      <h2 id="currentTemp">[Not Connected]</h2>

      <h3>Set Temperature:</h3>
      <h2><span id="label_setTemp">75.0</span>°C</h2>
      <input class="slider" id="temp" type="range" min="0.0" max="100.0" step="0.5" oninput="updateSetTemp()" value="75.0">

    </div>




    <script>
        "strict"
        /*
        mode:
          ON = 0,
          OFF = 1,
          STANDBY = 2,
          INTERNET = 3,
          ADJUST = 4
        */
        let state = {
          mode: 0,
          currentTemp: 21.0,
          setTemp: 75.0,
          alarm: false,
          ready: false
        }

        let sendWS = true
        let connection
        let connected = false

        if (sendWS) {
          connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);
          //connection = new WebSocket('ws://127.0.0.1:8080/')
          connection.onopen = function () {
            connection.send('Connect ' + new Date())
            connected = true
            document.getElementById('currentTemp').innerHTML = '<span id=\"label_currentTemp\"></span>°C'
          }
          connection.onerror = function (error) {
            console.log('WebSocket Error ', error)
          }
          connection.onmessage = function (e) {
            getStateFromWS(e.data)
            console.log('Server: ', e.data)
          }
          connection.onclose = function () {
            console.log('WebSocket connection closed')
          }
        }

        function sendStateToWS() {
          let stateJSON = JSON.stringify(state)
          console.log(stateJSON)
          if (sendWS) connection.send(stateJSON)
        }

        function getStateFromWS(rawJSON) {
          //console.log('Server State: ' + rawJSON)
          state = JSON.parse(rawJSON)
          console.log('Updated state object. ' + state.setTemp)
          updateCurrentTemp()
        }

        function updateSetTemp() {
          state.setTemp = parseFloat(document.getElementById('temp').value)
          document.getElementById('label_setTemp').innerHTML = state.setTemp.toFixed(1)
          console.log('New Set Temperature: ', state.setTemp)
          if (connected) sendStateToWS()
        }

        function updateCurrentTemp() {
          document.getElementById('label_currentTemp').innerHTML = state.currentTemp.toFixed(1)
          //<span id="label_currentTemp">[Not Connected]</span>°C
        }


    </script>
  </body>
</html>
)rawliteral";



//<!DOCTYPE html>
//<html>
//  <head>
//    <meta name = "viewport" content = "width = device-width, initial-scale = 1.0">
//    <title>Kettle Thermostat</title>
//    <style>
//    </style>
//  </head>
//  <body>
//    <header>
//      <h1>Kettle Thermostat</h1>
//    </header>
//    <script>
//  </body>
//</html>
