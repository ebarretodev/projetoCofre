
/* 
 *  Confirma se a senha digitada é igual a cadastrada
*/
void verificaSenha(){
  if( senhaDigitada.length() == 5 ){
    if (senhaDigitada == senhaCadastrada){
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
void capturaTecla(){
  tecla = teclado.getKey();
}

/* 
 *  Função para capturar tecla e digitar na tela a senha 
 *  Rotinas auxiliares:
 *  - tecla 'A': Alterar a senha
 *  - tecla 'B': Cadastrar o RFID
 *  - tecla 'C': Retornar ao Inicio
 *  - tecla 'D': Pressionado por 5s Factory Reset
 *  
*/
void capturaTeclaSenha(){
  tecla = teclado.getKey();
  if (tecla != NO_KEY){
    if(tecla == 'A'){}
    
    if(tecla == 'B'){
      
    }
    
    if(tecla == 'C'){
      telaInicio();
      return;
    }
    
    if(tecla == 'D'){
      unsigned long momentoPressionado; 
      momentoPressionado = millis();
      unsigned long tempoPressionado = 0;
      bool telaApresentada = LOW;
      while(tempoPressionado < tempoParaResetFabrica){
        unsigned long tempoAgora = millis();
        tempoPressionado = tempoAgora - momentoPressionado;
        unsigned long tempoRestante = (tempoParaResetFabrica - tempoPressionado) / 1000;
        if(tempoPressionado > 2000){
          if (!telaApresentada){
            telaFactoryReset();
            telaApresentada = HIGH;
          }
          lcd.setCursor(0,1);
          lcd.print(tempoRestante);
        }
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
    lcd.setCursor(7,1);
    for(int i = 0; i < senhaDigitada.length() - 1; i++){
      lcd.print('*');
    }
    lcd.print(tecla);
   }
}
