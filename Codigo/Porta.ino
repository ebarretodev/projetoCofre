/* Rotina usada para abrir a porta */ 
void comandoAbrirPorta(){
  abrirTranca();
  delay(3000);
  telaPortaLiberada();
  fecharTranca();
  delay(3000);
  telaInicio();
}
/* Função para fechar porta */ 
void fecharTranca(){
  digitalWrite(PINO_TRANCA, HIGH);
}

/* Função para abrir porta */
void abrirTranca(){
  digitalWrite(PINO_TRANCA, LOW);
}
