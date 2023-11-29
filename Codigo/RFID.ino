/* 
 *  Função para leitura do RFID
 *  Aqui é analisado se o RFID tem o código cadastrado
*/
void lerRfid() {
  // Verifico se tem algum cartão presente
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

      /* 
       * Se o codigo RFID do cartao for o
       * mesmo cadastrado abre a porta
      */
      if (conteudo.substring(1) == rfidCadastrado) {
        telaCartaoReconhecido();
        comandoAbrirPorta();
      } else {
        telaCartaoNaoReconhecido();
        delay(3000);
        telaInicio();
      }
    }
  }
}
