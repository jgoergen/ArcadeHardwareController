const char COMMAND_BEGIN_CHAR = '<';
const char COMMAND_END_CHAR = '>';
const char* COMMAND_DIVIDER_CHAR = ":";
const char* COMMAND_DIVIDER_CHAR_SECONDARY = ",";
const byte COMMAND_LENGTH = 200;

char receivedChars[COMMAND_LENGTH];
boolean newData = false;
char receivedNewData[COMMAND_LENGTH];

void serialInterface_Init() {
  
    Serial.begin(115200);
}

void serialInterface_Update() {

  static boolean recvInProgress = false;
  static byte ndx = 0;
  char rc;
  
  while (Serial.available() > 0 && newData == false) {
    
    rc = Serial.read();

    if (recvInProgress == true) {
      
        if (rc != COMMAND_END_CHAR) {
          
            receivedChars[ndx] = rc;
            ndx++;
            
            if (ndx >= COMMAND_LENGTH)              
                ndx = COMMAND_LENGTH - 1;
        } else {
          
            receivedChars[ndx] = '\0'; // terminate the string
            recvInProgress = false;
            ndx = 0;
            newData = true;
        }
    }

    else if (rc == COMMAND_BEGIN_CHAR)      
        recvInProgress = true;
  }

  if (newData == true) {

    newData = false;
    memcpy(
      receivedNewData, 
      receivedChars, 
      COMMAND_LENGTH * sizeof(char));
      
  } else {

    receivedNewData[0] = 0;
    receivedNewData[1] = 0;
    receivedNewData[2] = 0;
  }

  if (receivedNewData[0] != 0 && receivedNewData[1] != 0 && receivedNewData[2] != 0) {
  
    // seperate the command from the parameter and process it
    
    char* command = strtok(receivedNewData, COMMAND_DIVIDER_CHAR);
    char* param = strtok(NULL, COMMAND_DIVIDER_CHAR);
    processSerialCommand(command, param);
  }
}

void processSerialCommand(char* command, char* param) {

  // commands should be in the format "<COMMAND:PARAMER>"

  if (strcmp(command, "mode") == 0) {

    changeMode(atoi(param));
    Serial.print("ok|");    
    
  } else if (strcmp(command, "btn") == 0) {

    buttonLights_Parse_Command(param);
    Serial.print("ok|");    
    
  } else if (strcmp(command, "amb") == 0) {

    ambientLights_Parse_Command(param);
    Serial.print("ok|");    
    
  }
}
