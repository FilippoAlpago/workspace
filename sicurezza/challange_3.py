import time
import hashlib

def brute(numero):
  pinIdeale1=''
  pinIdeale2=''
  pinIdeale3=''
  
  timestamp1='{}-{}-{}-{}:{}'.format(2020,4,8,21,45)
  timestamp2='{}-{}-{}-{}:{}'.format(2020,4,8,21,46)
  timestamp3='{}-{}-{}-{}:{}'.format(2020,4,8,21,47)
  
  hash1=hashlib.sha256((numero+timestamp1).encode()).digest()
  hash2=hashlib.sha256((numero+timestamp2).encode()).digest()
  hash3=hashlib.sha256((numero+timestamp3).encode()).digest()
  for i in range(6):
    digit1=hash1[i]%10
    pinIdeale1+=str(digit1)
    digit2=hash2[i]%10
    pinIdeale2+=str(digit2)
    digit3=hash3[i]%10
    pinIdeale3+=str(digit3)
  if(pinIdeale1=='754104' and pinIdeale2=='353471' and pinIdeale3=='084633'):
    return True
  else:
    return False

def formatNumber(num):
  NumStringFormat=''
  format=''
  app=8-len(str(num))
  i=0
  while(i<app):
    
      format +='0'
      i +=1
  NumStringFormat +=format
  NumStringFormat+= str(num) 
  return NumStringFormat

Numero=41131337
Numero=0
StringNumber=formatNumber(Numero)
start_time=time.gmtime()
start_time_min=start_time.tm_min
start_time_second=start_time.tm_sec
print("minute start ",start_time_min,":",start_time_second) 
while(brute(StringNumber)==False or Numero>99999999):
  Numero+=1
  StringNumber=formatNumber(Numero)
finish_time=time.gmtime()
finish_time_min=finish_time.tm_min
finish_time_sec=finish_time.tm_sec
print("minute finish ",finish_time_min,":",finish_time_sec)

if(finish_time_sec<start_time_second):
  
    finish_time_min -=1

tempo_impiegato=str(((finish_time_min-start_time_min)%60))+":"+str(((finish_time_sec-start_time_second)%60))
print("tempo impiegato: "+str(tempo_impiegato))
print("PIN cercato è ",Numero)