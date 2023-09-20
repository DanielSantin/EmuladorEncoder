  float x; float y; float z; 
  int xInt; int yInt; int zInt;

  const int encoderPrimary[3] = {5,4,15};  // gpio5  -> D1   //passo do encoder 1
  const int encoderSecondary[3] = {14,12,13}; // gpio14 -> D5   //direção do encoder 1

  const int led_builtin = 2;
  bool arrayUtilitario[4][2] = {{true,true},{true,false},{false,false},{false,true}};
  const int delayfixo = 1;

  int arrayOfCoordinates[3] = {0,0,0};
  int contador[3] = {0,0,0};
  int multiplicador[3] = {0,0,0};
  int StringCount;

  float arraySomadorDeErros[3] = {0,0,0};

  void setup() { 
    Serial.begin(115200);
    Serial.println("Inciando Setup");

    pinMode(led_builtin, OUTPUT);
    digitalWrite(led_builtin, LOW); //logica invertida
    for (int i = 0; i < 3; i++) {
      pinMode(encoderPrimary[i], OUTPUT);
      pinMode(encoderSecondary[i], OUTPUT);
      digitalWrite(encoderPrimary[i], HIGH);
      digitalWrite(encoderSecondary[i], HIGH);
    }

    Serial.println("Setup concluído");
  }

  void loop() {

    if (Serial.available() > 0)
    {
      String actualString = Serial.readStringUntil('\n');
      String strs[3];
      StringCount = 0;
      int StringLen=atoi(actualString.c_str());
      actualString = actualString.substring(1,StringLen-1);

      while (actualString.length() > 0)
      {
        int index = actualString.indexOf(',');
        if (index == -1)
        {
          strs[StringCount++] = actualString;
          break;
        } 
        else
        {        
          strs[StringCount++] = actualString.substring(0, index);
          actualString = actualString.substring(index+1);
        }
      }

      arraySomadorDeErros[0] = arraySomadorDeErros[0] + strs[0].toFloat();
      arraySomadorDeErros[1] = arraySomadorDeErros[1] + strs[1].toFloat();
      arraySomadorDeErros[2] = arraySomadorDeErros[2] + strs[2].toFloat();

      arrayOfCoordinates[0] = arraySomadorDeErros[0].toInt();
      arrayOfCoordinates[1] = arraySomadorDeErros[1].toInt();
      arrayOfCoordinates[2] = arraySomadorDeErros[2].toInt();

      arraySomadorDeErros[0] = arraySomadorDeErros[0] - arrayOfCoordinates[0];
      arraySomadorDeErros[1] = arraySomadorDeErros[1] - arrayOfCoordinates[1];
      arraySomadorDeErros[2] = arraySomadorDeErros[2] - arrayOfCoordinates[2];



      for (int i = 0; i < 3; i++) {
        if(arrayOfCoordinates[i]>0){
          multiplicador[i] = 1;
        } else if (arrayOfCoordinates[i] < 0){
          multiplicador[i] = -1;
        } else {
          multiplicador[i] = 0;
        }
      }
    }

    while(multiplicador[0] != 0 || multiplicador[1] != 0 || multiplicador[2] != 0){
      for (int i = 0; i < 3; i++) {
        if(multiplicador[i] != 0){
          arrayOfCoordinates[i] = arrayOfCoordinates[i] - multiplicador[i];
          contador[i] = (contador[i] - multiplicador[i])%4;
          digitalWrite(encoderPrimary[i],arrayUtilitario[contador[i]][0]);
          digitalWrite(encoderSecondary[i],arrayUtilitario[contador[i]][1]);
          if(arrayOfCoordinates[i] == 0){
            multiplicador[i] = 0;
          }
        }
      } 
    }
  }