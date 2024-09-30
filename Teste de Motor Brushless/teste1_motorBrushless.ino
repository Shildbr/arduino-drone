int rotacao;  
 int porta = 9;  
    
 void setup()
 {  
 }  
    
 void loop()
 {  
  for(rotacao=0; rotacao<=255; rotacao=rotacao+5)  
  {  
   analogWrite(porta,rotacao);  
   delay(500);  
  }  
    
  delay(1000);  
  for(rotacao=100; rotacao>=0; rotacao=rotacao-5)  
  {  
   analogWrite(porta,rotacao);  
   delay(500);  
  }  
    
  delay(1000);  
 }  
