/* --------- JSON Serialize State --------- */
const uint16_t jsonSendSize = 256;
void serializeJSON_state(char * json) {
  StaticJsonBuffer<jsonSendSize> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["mode"] = state.mode;
  root["currentTemp"] = state.currentTemp;
  root["setTemp"] = state.setTemp;
  root["alarm"] = state.alarm;
  root["ready"] = state.ready;
  root.printTo(json, jsonSendSize);
  //if (SERIAL_DEBUG) Serial.println(json);
  //if (DEBUG_SERIAL) root.prettyPrintTo(Serial);
}

/* ------ helper function to send state ------*/
void sendState() {
  char stateJSON[jsonSendSize];
  serializeJSON_state(stateJSON);
  //webSocket.sendTXT(num, stateJSON);
  webSocket.broadcastTXT(stateJSON);
}

/* --------- JSON Deserialize --------- */
const uint16_t jsonReceiveSize = 256;
bool deserializeJSON(uint8_t * json) {
  StaticJsonBuffer<jsonReceiveSize> jsonBuffer;     // actually only needs to be about 240 bytes, extra reserved for future use (or just because I have the space..). (http://arduinojson.org/assistant/)
  JsonObject& root = jsonBuffer.parseObject(json);
  if (!root.success()) {
    if (DEBUG_SERIAL) Serial.printf("[ws] deserializeJSON: parseObject() failed\n");
    return false;
  }
  else {
    uint8_t _mode = root["mode"];
    state.mode = (OperatingMode) _mode;
    state.currentTemp = root["currentTemp"];
    state.setTemp = root["setTemp"];
    state.alarm = root["alarm"];
    state.ready = root["ready"];
    if (DEBUG_SERIAL) Serial.printf("[ws] deserializeJSON: success\n");
  }
  return root.success();
}

/*---------- Websocket Event ------------*/
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_ERROR:
      if (DEBUG_SERIAL) Serial.printf("[ws] ERROR!\n");
      break;
    case WStype_DISCONNECTED:
      if (DEBUG_SERIAL) Serial.printf("[ws] [%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
        // num is client ID (because I am a websocket server!)
        IPAddress ip = webSocket.remoteIP(num);
        if (DEBUG_SERIAL) Serial.printf("[ws] [%u] Connected from url: %u.%u.%u.%u%s replying...\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        yield();
        sendState();
      }
      break;
    case WStype_TEXT: {
        if (DEBUG_SERIAL) Serial.printf("[ws] [%u] got text: %s\n", num, payload);
        deserializeJSON(payload);
        writeToEEPROM();
      }
      break;
    case WStype_BIN:
      if (DEBUG_SERIAL) Serial.printf("[ws] got binary (length): %zu\n", length);
      hexdump(payload, length);
      break;
    default:
      break;
  }
}
  
