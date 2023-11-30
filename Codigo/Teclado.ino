
/*
    Confirma se a senha digitada é igual a cadastrada
*/
void verificaSenha() {
  if ( senhaDigitada.length() == 5 ) {
    if (senhaDigitada == senhaCadastrada) {
      telaSenhaCorreta();
      comandoAbrirPorta();
    } else {
      telaSenhaErrada();
      delay(3000);
      telaInicio();
    }
  }
}

/* Função para capturar tecla */
void capturaTecla() {
  tecla = teclado.getKey();
}

/*
    Função para capturar tecla e digitar na tela a senha
    Rotinas auxiliares:
    - tecla 'A': Alterar a senha
    - tecla 'B': Cadastrar o RFID
    - tecla 'C': Retornar ao Inicio
    - tecla 'D': Pressionado por 5s Factory Reset

*/
void capturaTeclaSenha() {
  tecla = teclado.getKey();
  if (tecla != NO_KEY) {
    if (tecla == 'A') {}

    if (tecla == 'B') {
      if (rfidCadastrado != "") {
        telaDesejaTrocarRfid();
        while (HIGH) {
          capturaTecla();
          Serial.println(tecla);
          if (tecla == 'A' || tecla == 'B') {
            break;
          }
        }
        if (tecla == 'B') {
          telaInicio();
          return;
        }
      }
      telaDigiteSenha();
      while (HIGH) {
        capturaTecla();
        if (tecla != NO_KEY) {
          senhaDigitada += tecla;
          lcd.setCursor(6, 1);
          for (int i = 0; i < senhaDigitada.length() - 1; i++) {
            lcd.print('*');
          }
          lcd.print(tecla);
        }
        if (senhaDigitada.length() == 5) {
          if (senhaDigitada != senhaCadastrada) {
            telaInicio();
            return;
          }
          break;
        }
      }
      telaEncosteRfid();
      // Loop para capturar o RFID novo
      while(HIGH) {
        if (mfrc522.PICC_IsNewCardPresent()) {
          // Seleciono um cartao da lista
          if ( mfrc522.PICC_ReadCardSerial()) {
            //Mostra UID na serial
            Serial.print("UID da tag :");
            // Imprime na Serial e salva o cartao na variavel conteudo
            conteudo = "";
            byte letra;
            for (byte i = 0; i < mfrc522.uid.size; i++) {
              Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
              Serial.print(mfrc522.uid.uidByte[i], HEX);
              conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
              conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
            }
            Serial.println();
            rfidCadastrado = conteudo.substring(1);
            Serial.print("Novo RFID: ");
            Serial.println(rfidCadastrado);
            break;
          }
        }
      }
      telaRfidCadastrado();
      delay(3000);

      telaInicio();
      return;
    }

    if (tecla == 'C') {
      telaInicio();
      return;
    }

    if (tecla == 'D') {
      unsigned long momentoPressionado;
      momentoPressionado = millis();
      unsigned long tempoPressionado = 0;
      bool telaApresentada = LOW;
      while (tempoPressionado < tempoParaResetFabrica) {
        unsigned long tempoAgora = millis();
        tempoPressionado = tempoAgora - momentoPressionado;
        unsigned long tempoRestante = (tempoParaResetFabrica - tempoPressionado) / 1000;
        if (tempoPressionado > 2000) {
          if (!telaApresentada) {
            telaFactoryReset();
            telaApresentada = HIGH;
          }
          lcd.setCursor(0, 1);
          lcd.print(tempoRestante);
        }
        if (dTeclaSolta) {
          telaInicio();
          break;
        }
      }
      if (dTeclaSolta) {
        return;
      }
      rfidCadastrado = "";
      senhaCadastrada = "1234#";
      telaConfirmaFactoryReset();
      telaInicio();
      return;
    }

    Serial.println(tecla);
    Serial.println(senhaDigitada);
    senhaDigitada += tecla;
    lcd.setCursor(7, 1);
    for (int i = 0; i < senhaDigitada.length() - 1; i++) {
      lcd.print('*');
    }
    lcd.print(tecla);
  }
}



// Taking care of some special events.
void keypadEvent(KeypadEvent key) {
  switch (teclado.getState()) {
    case PRESSED:
      if (key == 'D') {
        dTeclaSolta = LOW;
      }
      break;

    case RELEASED:
      if (key == 'D') {
        dTeclaSolta = HIGH;
      }
      break;

    case HOLD:

      break;
  }
}
