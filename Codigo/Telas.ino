/* ---------------------------------------------- */
/* TODAS AS TELAS DO LCD FORAM DESENVOLVIDAS AQUI */
/* ---------------------------------------------- */

void telaInicializacao() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Acesso Cofre");
  lcd.setCursor(0, 1);
  lcd.print("Inicializando...");
}

void telaInicio() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Encoste o cartao");
  lcd.setCursor(0, 1);
  lcd.print("Senha: ");
  // Reset de senha digitada
  senhaDigitada = "";
}

/* Telas para acesso pelo RFID */

void telaCartaoReconhecido() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Cartao");
  lcd.setCursor(2, 1);
  lcd.print("Reconhecido");
}

void telaCartaoNaoReconhecido() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Cartao nao");
  lcd.setCursor(2, 1);
  lcd.print("Reconhecido ");
}

/* Telas para acesso pela senha */

void telaSenhaCorreta() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Senha");
  lcd.setCursor(4, 1);
  lcd.print("Correta");
}

void telaSenhaErrada() {
  tentativas--;
  lcd.clear();

  if (tentativas > 0 ) {
    lcd.setCursor(0, 0);
    lcd.print("Senha Incorreta");
    lcd.setCursor(2, 1);
    if (tentativas >= 2) {
      lcd.print(tentativas);
      lcd.print(" tentativas");
    } else if (tentativas == 1) {
      lcd.print(tentativas);
      lcd.print(" tentativa");
    }
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Limite tentativa");
    lcd.setCursor(1, 1);
    lcd.print("Aguarde 10 seg");
    delay(10000);
    tentativas = 3;
  }
}

/* Telas para alterar senha */
void telaDesejaTrocarSenha() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Trocar senha?");
  lcd.setCursor(0, 1);
  lcd.print("SIM(A)    NAO(B)");
}

void telaOperacaoCancelada() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Operacao cancelada!");
  lcd.setCursor(0, 1);
  lcd.print("Tente novamente!");
}

void telaDigiteNovaSenha() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Nova senha");
}

void telaConfirmeNovaSenha() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Confirme a senha");
}

void telaSenhaNaoConfere (){
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Senha errada");
  lcd.setCursor(0, 1);
  lcd.print("Tente novamente!");
  }

void telaSenhasNaoConfere() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Senhas diferentes!");
  lcd.setCursor(0, 1);
  lcd.print("Tente novamente!");
}

void telaSenhaAlteradaComSucesso() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Senhas Alterada!");
  lcd.setCursor(0, 1);
  lcd.print("Obrigado!!!");
  
  }

/* Telas para alterar RFID */
void telaDesejaTrocarRfid() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Trocar RFID?");
  lcd.setCursor(0, 1);
  lcd.print("SIM(A)    NAO(B)");
}

void telaDigiteSenha() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Digite a senha");
}


void telaEncosteRfid() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Aproxime");
  lcd.setCursor(3, 1);
  lcd.print("o RFID!!!");
}

void telaRfidCadastrado() {
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("RFID");
  lcd.setCursor(2, 1);
  lcd.print("cadastrado!!");
}

/* Telas para Factory Reset */
void telaFactoryReset() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Pressione por");
  lcd.setCursor(1, 1);
  lcd.print(" seg para resetar");
}

void telaConfirmaFactoryReset() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Restaurado");
  lcd.setCursor(3, 1);
  lcd.print("parametros");
  delay(3000);
}

/* Tela de porta liberada */
void telaPortaLiberada() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Porta");
  lcd.setCursor(4, 1);
  lcd.print("Liberada");
}
