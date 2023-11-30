
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
  /* Pega a tecla do teclado para analisar */
  tecla = teclado.getKey();
  /* Senão tiver tecla pula a lógica para otimizar o código */
  if (tecla != NO_KEY) {

    /* tecla 'A': Alterar a senha */
    if (tecla == 'A') {
      telaDesejaTrocarSenha();
      while (HIGH) {
        capturaTecla();
        Serial.println(tecla);
        if (tecla == 'A' || tecla == 'B' || tecla == 'C') {
          break;
        }
      }
      if (tecla == 'B' || tecla == 'C') {
        telaInicio();
        return;
      }
      telaDigiteSenha();
      while (HIGH) {
        capturaTecla();
        if (tecla != NO_KEY) {
          if (tecla == 'A' || tecla == 'B' ||  tecla == 'C' || tecla == 'D' ) {
            tecla = NO_KEY;
            telaInicio();
            break;
          }
          senhaDigitada += tecla;
          lcd.setCursor(6, 1);
          for (int i = 0; i < senhaDigitada.length() - 1; i++) {
            lcd.print('*');
          }
          lcd.print(tecla);
        }
        if (senhaDigitada.length() == 5) {
          if (senhaDigitada != senhaCadastrada) {
            telaSenhaNaoConfere();
            delay(3000);
            telaInicio();
            return;
          }
          break;
        }
      }
      telaDigiteNovaSenha();
      while (HIGH) {
        capturaTecla();
        if (tecla != NO_KEY) {
          if (tecla == 'A' || tecla == 'B' ||  tecla == 'C' || tecla == 'D' || tecla == '#'  || tecla == '*' ) {
            tecla = NO_KEY;
            telaInicio();
            break;
          }
          novaSenhaDigitada += tecla;
          lcd.setCursor(6, 1);
          for (int i = 0; i < novaSenhaDigitada.length() - 1; i++) {
            lcd.print('*');
          }
          lcd.print(tecla);
        }
        if (novaSenhaDigitada.length() == 4) {
          novaSenhaDigitada += "#";
          break;
        }
      }
      telaConfirmeNovaSenha();
      while (HIGH) {
        capturaTecla();
        if (tecla != NO_KEY) {
          if (tecla == 'A' || tecla == 'B' ||  tecla == 'C' || tecla == 'D' || tecla == '#'  || tecla == '*' ) {
            tecla = NO_KEY;
            telaInicio();
            break;
          }
          confirmaNovaSenhaDigitada += tecla;
          lcd.setCursor(6, 1);
          for (int i = 0; i < confirmaNovaSenhaDigitada.length() - 1; i++) {
            lcd.print('*');
          }
          lcd.print(tecla);
        }
        if (confirmaNovaSenhaDigitada.length() == 4) {
          confirmaNovaSenhaDigitada += "#";
          break;
        }
      }
      if (novaSenhaDigitada == confirmaNovaSenhaDigitada) {
        senhaCadastrada = novaSenhaDigitada;
      } else {
        telaSenhasNaoConfere();
        delay(3000);
        telaInicio();
        return;
      }

      telaSenhaAlteradaComSucesso();
      delay(2000);
      novaSenhaDigitada = "";
      confirmaNovaSenhaDigitada = "";
      telaInicio();
      return;
    }

    /* tecla 'B': Cadastrar o RFID */
    if (tecla == 'B') {
      if (rfidCadastrado != "") {
        telaDesejaTrocarRfid();
        while (HIGH) {
          capturaTecla();
          Serial.println(tecla);
          if (tecla == 'A' || tecla == 'B' || tecla == 'C') {
            break;
          }
        }
        if (tecla == 'B' || tecla == 'C') {
          telaInicio();
          return;
        }
      }
      telaDigiteSenha();
      while (HIGH) {
        capturaTecla();
        if (tecla != NO_KEY) {
          if (tecla == 'C') {
            break;
          }
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

      /* tecla 'C': Retornar ao Inicio */
      if (tecla == 'C') {
        telaInicio();
        return;
      }
      telaEncosteRfid();
      // Loop para capturar o RFID novo
      while (HIGH) {
        capturaTecla();
        if (tecla != NO_KEY) {
          if (tecla == 'C') {
            break;
          }
        }
        if (mfrc522.PICC_IsNewCardPresent()) {
          // Seleciono um cartao da lista
          if ( mfrc522.PICC_ReadCardSerial()) {
            //Mostra UID na serial
            Serial.print("UID da tag :");
            // Imprime na Serial e salva o  valor do cartao na variavel conteudo
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
      if (tecla == 'C') {
        telaInicio();
        return;
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

    /* tecla 'D': Pressionado por 5s Factory Reset */
    if (tecla == 'D') {
      unsigned long momentoPressionado;
      momentoPressionado = millis();
      unsigned long tempoPressionado = 0;
      bool telaApresentada = LOW;
      //Verifica se o tempo que ficou pressionado for maios que 10s
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
        capturaTecla();
        if (tecla != NO_KEY) {
          if (tecla == 'C') {
            break;
          }
        }
        if (dTeclaSolta ) {
          telaInicio();
          break;
        }
      }
      if (dTeclaSolta || tecla == 'C') {
        telaInicio();
        return;
      }
      // Valores para padrão de fábrica
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

/* Evento de teclado, criado para controle da Tecla D
   Utilizado para monitorar se a tecla D está pressionada
   ou não.
*/

void keypadEvent(KeypadEvent key) {
  switch (teclado.getState()) {
    case PRESSED:
      if (key == 'D') {
        dTeclaSolta = LOW;
        Serial.println("Tecla pressionada");
      }
      break;

    case RELEASED:
      if (key == 'D') {
        Serial.println("Tecla solta");
        dTeclaSolta = HIGH;
      } else if (key == 'C') {
        telaInicio();
      }
      break;

    case HOLD:

      break;
  }
}
