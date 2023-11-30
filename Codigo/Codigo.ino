/*------------------------------*/
/* Bibliotecas usadas no projeto*/
/*------------------------------*/
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>

/*  Variaveis de configuração do padrão
 *  
 */
 unsigned long tempoParaResetFabrica = 10000;
 

/*-------------------------*/
/* Configurações do sistema*/
/*-------------------------*/

/*  Tranca solenoide 12V, ligada no Pino A7 alterado para A3 
 *  De acordo com a documentação as portas A6 e A7 só podem 
 *  ser usadas como Entrada Analógica
 */
const byte PINO_TRANCA = A3;

/* Configuração do keypad */
const byte rows = 4; 
const byte cols = 4; 
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[cols] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad teclado = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
char tecla;
bool dTeclaSolta;

/* Configuração do leitor RFID */ 
const byte SS_PIN = 10;
const byte RST_PIN = A0;
MFRC522 mfrc522(SS_PIN, RST_PIN); 

/* Rotina de inicialização do RFID */ 
void initRfid(){
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
}

/* Variaveis para controle do RFID */ 
String conteudo;
String rfidCadastrado = "";
//String rfidCadastrado = "45 7d 0b ad";

/* Variaveis para controle da Senha */ 
int tentativas = 3;
String senhaDigitada;
String senhaCadastrada = "1234#";

/* 
 * Configuração do LCD 
 * Confirmar o endereço do I2C se é 0x3F
 */ 
LiquidCrystal_I2C lcd(0x3F,16,2); 


/* Incialização do microcontrolador */ 
void setup(){
  //Inicialização da serial para fazer o debbug do programa
  Serial.begin(9600);  
  //Inicialização do RFID
  initRfid();
  //Inicialização da tranca
  pinMode(PINO_TRANCA, OUTPUT);                                             
  fecharTranca();
  // Add an event listener for this keypad
  teclado.addEventListener(keypadEvent); 
  //Inicialização do LCD
  lcd.init();
  lcd.backlight();
  telaInicializacao();
  delay(3000);
  telaInicio(); 
}

/* Incialização do microcontrolador */ 
void loop(){ 
  // Verifica se tem algum cartao no leitor
  lerRfid();
  // Verifica se tem alguma tecla pressionada
  capturaTeclaSenha();
  // Verifica se a senha esta correta
  verificaSenha();
}
