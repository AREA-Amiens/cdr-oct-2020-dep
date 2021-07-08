#include <main.h>


Stepper motorDroit(STEP_MOTEUR_GAUCHE, DIR_MOTUER_GAUCHE);   //STEP pin =  2, DIR pin = 3
Stepper motorGauch(STEP_MOTEUR_DROIT,DIR_MOTEUR_DROIT);   //STEP pin =  9, DIR pin = 10
StepControl controller;
coordoneCartesient emplacementRelleRobot,emplacementObjectif;
String messageResueCan,etapeStrategei;
byte messageResue=0,strategieBicolor,etatRobo,transition0=0,transition1=0,transition2=0,etape,etapeActionDeplacement=0,strategieNumero=0,strategieNumeroP=0;
int conteurFin=0,iStrategie=0,iStrategieP=0,distancePas,distaceMMGo,distanceDegTurn,conteurOdometrie;
int impultionEncodeurDroit=0,impultionEncodeurGauche=0,etatp=0;
boolean passe,passe4=true,retourAction=false,conditionTimerFin=false,arretLidaRoboEnface=false,passerParDetection=false,RecalageDroit=true,RecalageGauche=true;
boolean passeRecalage=false;
float angleRobot=0;
int timerDetection=0,senseGo=1,nbPiont=0;
int timerAttente=0,timerObjectif=0;
static CAN_message_t msg;
String strategie[9];
int xEnvoie,yEnvoie,aEnvoie,passe1,passe2,passe3;
void setup() {
  Serial2.begin(9600);
  Serial.begin(9600);
//  D:0:-100:0:0:D:0:0:0:0:D:0:-100:-100:0:D:0:0:0:0:D:0:0:-100:0:D:0:0:0:0:D:0:100:-100:0:D:0:0:0:0:
//"C:c:270:600:90:R:0:-600:y:105:90:G:0:695:av:0:T:0:90:g:0:R:0:-350:x:105:0:0:G:0:55:av:0:D:0:230:860:0:0:S:D:0:800:600:0:0:D:0:350:200:90:R:0:-100:y:105:90:0:E:";
strategie[0]="C:c:270:600:90:A:h:0:J:d:h:0:J:g:h:0:R:0:-600:y:105:90:G:0:695:av:0:h:T:0:90:g:0:R:0:-350:x:105:0:0:";
strategie[0]+="G:0:55:av:0:h:D:0:230:860:0:0:S:0:D:0:800:600:0:0:D:0:350:200:90:0:R:0:-100:y:105:90:0:";
strategie[0]+="G:0:30:av:0:h:D:0:350:200:103:0:G:0:780:av:0:h:G:0:60:ar:0:h:D:0:750:510:180:0:G:0:560:av:0:h:G:0:100:ar:0:0:D:0:700:1080:180:0:G:0:430:av:0:h:G:0:300:ar:18:h:";
strategie[0]+="T:0:90:d:0:R:0:-900:y:1895:270:0:G:0:80:av:0:h:T:0:90:d:0:D:0:230:1855:0:0:R:0:-275:x:105:0:0:J:d:b:0:J:g:b:0:L:100:0:G:0:680:av:0:h:J:d:h:0:J:g:h:0:";// manche a aire
strategie[0]+="G:0:50:ar:0:h:L:100:0:";
strategie[0]+="D:0:590:1700:0:0:D:0:900:1400:0:0:G:0:1030:av:0:h:T:0:90:d:0:G:0:200:av:0:h:G:0:200:ar:0:h:T:0:90:d:0:G:0:270:av:0:h:T:0:90:g:0:G:0:200:av:0:h:G:0:200:ar:0:h:";
strategie[0]+="T:0:90:d:0:D:0:290:570:220:0:G:0:200:ar:0:h:D:0:300:450:n:0:E:";

strategie[1]="C:c:270:600:90:A:h:0:J:d:h:0:J:g:h:0:R:0:-600:y:105:90:G:0:695:av:0:h:T:0:90:g:0:R:0:-350:x:105:0:0:";
strategie[1]+="G:0:55:av:0:h:D:0:230:900:0:0:S:0:D:0:800:600:0:0:D:0:350:200:90:0:R:0:-205:y:105:90:0:";
strategie[1]+="G:0:40:av:0:h:D:0:350:190:103:0:G:0:770:av:0:h:G:0:60:ar:0:h:D:0:750:510:180:0:G:0:560:av:0:h:G:0:100:ar:0:h:D:0:700:1080:180:0:G:0:430:av:0:h:G:0:300:ar:18:h:";
strategie[1]+="T:0:90:d:0:R:0:-900:y:1895:270:0:G:0:80:av:0:h:T:0:90:d:0:D:0:230:1845:0:0:R:0:-255:x:105:0:0:J:d:b:0:J:g:b:0:L:100:0:G:0:680:av:0:b:J:d:h:0:J:g:h:0:";// manche a aire
strategie[1]+="G:0:50:ar:0:h:L:100:0:";
strategie[1]+="D:0:590:1700:0:0:D:0:900:1400:0:0:G:0:1030:av:0:h:T:0:90:d:0:G:0:200:av:0:h:G:0:200:ar:0:h:T:0:90:d:0:G:0:270:av:0:h:T:0:90:g:0:G:0:200:av:0:h:G:0:200:ar:0:h:";
strategie[1]+="T:0:90:d:0:D:0:290:530:220:0:E:";
/*  strategie[1]="C:c:270:600:90:R:0:-495:y:105:90:G:0:545:av:0:T:0:90:g:0:R:0:-65:x:105:0:0:G:0:55:av:0:";"
  strategie[1]+="D:0:750:650:205:G:0:331:av:0:";//prise gobelet 1
  strategie[1]+="G:0:185:av:";//prise gobelet 2
  strategie[1]+="D:0:250:360:90:0:R:0:100:x:105:90:15:D:0:240:360:114:0:G:0:300:av:0:";//prise goblerer 3
  strategie[1]+="G:0:50:ar:0:T:0:55:d:0:G:0:35:av:0:";//prise goblet 4
  strategie[1]+="D:0:940:540:105:0:G:0:100:av:0";//prise gobler 5
  strategie[1]+="G:0:200:av:0";//prse goblet 6
  strategie[1]+="D:0:450:180:270:0:G:0:250:av:0";//pose goblet 2:2
  strategie[1]+="G;0:80:ar:0";//pose goblet 4:2
  strategie[1]+="G:0:80:ar:0:T:0:90:0:R:0:1010:Y105:90:0:G:0:405:av:0:T:0:90:0:G:0:125:";
  strategie[1]+="";
  strategie[1]+="";
  strategie[1]+="";
  strategie[1]+="";
  strategie[1]+="";
  strategie[1]+="";
  strategie[1]+="";
  strategie[1]+="";
  strategie[1]+="";
  strategie[1]+="";*/


  strategie[2]="C:c:270:600:90:A:h:0:J:d:h:0:J:g:h:0:R:0:-600:y:105:90:G:0:695:av:0:h:T:0:90:g:0:R:0:-350:x:105:0:0:";
  strategie[2]+="G:0:55:av:0:h:D:0:230:860:0:0:S:0:D:0:550:1100:135:0:";
  strategie[2]+="G:0:500:av:0:h:!D:0:568:975:208:0:G:0:975:568:208:0:A:b:0:P:0:a:0:L:500:0:";
  strategie[2]+="A:h:0:L:500:0:O:2:0:G:0:866:av:0:h:A:b:0:P:1:a:0:L:500:0:A:h:0:A:500:0:";
  // strategie[2]="C:c:270:600:90:O:1:g:0:L:5000:0:O:2:0:g:L:5000:0:O:3:0:g:L:5000:0:O:4:0:g:L:5000:0:O:5:0:g:L:5000:0:O:6:0:g:L:5000:0:0:";
  // strategie[2]=+"O:1:g:0:L:5000:0:O:2:0:g:L:5000:0:O:3:0:g:L:5000:0:O:4:0:g:L:5000:0:O:5:0:g:L:5000:0:O:6:0:g:L:5000:0:0:";
  // strategie[2]=+"O:1:g:0:L:5000:0:O:2:0:g:L:5000:0:O:3:0:g:L:5000:0:O:4:0:g:L:5000:0:O:5:0:g:L:5000:0:O:6:0:g:L:5000:0:0:";
  // strategie[2]=+"O:1:g:0:L:5000:0:O:2:0:g:L:5000:0:O:3:0:g:L:5000:0:O:4:0:g:L:5000:0:O:5:0:g:L:5000:0:O:6:0:g:L:5000:0:0:";
  // strategie[2]=+"O:1:g:0:L:5000:0:O:2:0:g:L:5000:0:O:3:0:g:L:5000:0:O:4:0:g:L:5000:0:O:5:0:g:L:5000:0:O:6:0:g:L:5000:0:0:E:";

  strategie[3]="C:c:270:600:90:J:d:h:L:1000:0:J:d:b:g:L:1000:0:J:d:m:J:g:h:L:1000:0:J:g:b:g:L:1000:0:1:g:m:E:";

  strategie[4]="C:b:D:0:500:0:45:E";

  strategie[5]="C:c:270:600:90:P:0:a:0:L:10000:0:P:0:e:0:P:1:a:0:L:10000:0:P:1:e:0:P:2:a:0:L:10000:0:P:2:e:0:P:3:a:0:L:10000:0:P:3:e:0:P:4:a:0:L:10000:0:P:4:e:0:P:5:a:0:L:10000:V:0:a:0:V:1:a:0:V:2:a:0:V:3:a:0:V:4:a:0:V:5:a:0:";
  strategie[5]+="L:10000:P:0:e:0:P:1:e:0:P:2:e:0:P:3:e:0:P:4:e:0:P:5:e:0:L:10000:V:0:e:0:V:1:e:0:V:2:e:0:V:3:e:0:V:4:e:0:V:5:e:0:";
  strategie[5]+="L:10000:P:g:a:0:P:g:a:0:E:g:a:0:E:g:a:0:L:10000:P:g:a:0:P:g:a:0:E:g:e:0:E:g:e:0:L:";

  strategie[6]="C:j:270:600:90:A:h:0:L:5000:0:A:m:0:L:5000:0:A:b:0:E";
  strategie[7]="C:b:";
  strategie[8]="C:c:";
  Can0.begin(1000000);

  MsTimer2::set(1,IntrerrupTimer);
  emplacementRelleRobot.x=1000;
  emplacementRelleRobot.y=1000;
  emplacementRelleRobot.a=90;
  MsTimer2::start();
  // teensy.id=0x006;
  pinMode(ENCODEUR_DROIT_A,INPUT_PULLUP);
  pinMode(ENCODEUR_DROIT_B,INPUT_PULLUP);
  pinMode(ENCODEUR_GAUCHE_A,INPUT_PULLUP);
  pinMode(ENCODEUR_GAUCHE_B,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODEUR_DROIT_A),contageEncodeurDroit,RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODEUR_GAUCHE_A),contageEncodeurGauche,RISING);
  pinMode(M0,OUTPUT);
  pinMode(M1,OUTPUT);
  pinMode(M2,OUTPUT);
  digitalWrite(M0,LOW);
  digitalWrite(M1,HIGH);
  digitalWrite(M2,LOW);

  pinMode(RESETE_MOTEUR_GAUCHE, OUTPUT);    //le resete se fait a l'aita bas
  digitalWrite(RESETE_MOTEUR_GAUCHE, HIGH);
  pinMode(SLEEP_MOTEUR_GAUCHE, OUTPUT);    //le sleep se met a l'aita bas poru une carte fonctionelle
  digitalWrite(SLEEP_MOTEUR_GAUCHE, HIGH);

  pinMode(RESETE_MOTEUR_DROIT, OUTPUT);    //le resete se fait a l'aita bas
  digitalWrite(RESETE_MOTEUR_DROIT, HIGH);
  pinMode(SLEEP_MOTEUR_DROIT, OUTPUT);    //le sleep se met a l'aita bas poru une carte fonctionelle
  digitalWrite(SLEEP_MOTEUR_DROIT, HIGH);
  etapeStrategei=quelEtapeDeStrate();
}
void loop() {
  while(Can0.read(msg)){
    interpretationCan();
  }
  switch (etatRobo) {
    case 0:
      etatRobo=attenteStrategie();
    break;
    case 1:
      etatRobo=getionDesDeplacmentAction();
    break;
    case 2:
      etatRobo=attenteTierte();
    break;
    case 3:
    msg.id=0x4;
    msg.buf[0]='P';
    msg.buf[1]='t';
    msg.buf[2]='f';
    msg.buf[3]=nbPiont;
    msg.len=4;
    Can0.write(msg);
      controller.emergencyStop();
        //indication de fin a l'ihm;
    break;

  }
}
void interpretationCan(){
  byte Tabee[8];
  for(int i=0;i<8;i++){
    Tabee[i]=msg.buf[i];
  }
  if (comparChenCan("ds")){
    if (strategieNumero!=strategieNumeroP){
      emplacementRelleRobot.x=convertionInt(isoInfo(1));
      emplacementRelleRobot.y=convertionInt(isoInfo(2));
      emplacementRelleRobot.a=convertionInt(isoInfo(3));
      if(strategieBicolor){
        emplacementRelleRobot.x=3000-emplacementRelleRobot.x;
      }
    }
    strategieNumero=Tabee[2];
    msg.id=0x4;
    msg.buf[0]='R';
    msg.buf[1]='d';
    msg.buf[2]='s';
    msg.buf[3]=strategie[Tabee[2]][2];
    msg.len=4;
    Can0.write(msg);
  }
  if(comparChenCan("Rcs")){
    strategieBicolor=msg.buf[3];
    if(strategieBicolor){
      emplacementRelleRobot.x=3000-emplacementRelleRobot.x;
    }else{
      emplacementRelleRobot.x=convertionInt(isoInfo(1));
    }
  }
  if(comparChenCan("Srd")){
    transition0=1;
  }
  if(comparChenCan("Gdm")){
    transition2=1;
  }
  if(comparChenCan("LD")){
    arretLidaRoboEnface=true;
    timerDetection=0;
  }
  if(comparChenCan("Rrrg"))RecalageGauche=true;
  if(comparChenCan("Rrrd"))RecalageGauche=true;
  if(comparChenCan("Rga"))retourAction=true;//Retour Gateline position angle Rga
  else if(comparChenCan("Rgh"))retourAction=true;//Retour hauteur gateleine Rgh
  else if(comparChenCan("Rbc"))retourAction=true;//Retour hauteur bras cotée Rbc
  else if(comparChenCan("Rna"))retourAction=true;//Retour hauteur bras arrier Rba
  else if(comparChenCan("Rpb"))retourAction=true;//Retour pompe barriler Rpb
  else if(comparChenCan("Rpa"))retourAction=true;//Retour Pompe arrier Rpa
  else if(comparChenCan("Rvb"))retourAction=true;//Retour electrovane Rvb
  else if(comparChenCan("Rva"))retourAction=true;//Retour electrovane Rva
  else if(comparChenCan("Rdp"))retourAction=true;//Retour drapau Rdp
  //Retour cateur recalage Rcg et Rcd
}
int comparChenCan(String comp){
  for(int i=0;i<9;i++){
    if(comp[i]=='\0')return 1;
    if(msg.buf[i]!=comp[i]) return 0;
  }
  return 0;
}
int comparChen(String chaine1,String chaine2){
  int i=0;
  while(chaine1[i]!='\0'||chaine2[i]!='\0'){
    if(chaine1[i]!=chaine2[i])return 0;
    i++;
  }
  return 1;
}
byte attenteStrategie(){
  return transition0;
}
byte getionDesDeplacmentAction(){
  etape=machineEtatDeplacementAction();
  if(etape==1)transition1=2;
  if(etape==2)transition1=1;
  if(etape==3||conteurFin>=100000){
    transition1=3;
    msg.id=0x00;
    msg.buf[0]='F';
    msg.buf[1]='i';
    msg.buf[2]='n';
    msg.buf[3]=nbPiont;
    msg.len=4;
    Can0.write(msg);
  }
  return transition1;
}
byte attenteTierte(){
  if(transition2){
    etapeActionDeplacement=0;
    conditionTimerFin=true;
    transition2=false;
    return 1;
  }
  return 2;
}
void IntrerrupTimer(){
   if((conteurFin!=0||conditionTimerFin)&&conteurFin<=200000)conteurFin++;
   if(conteurFin>97000){
     msg.id=0x800;
     msg.buf[0]='D';
     msg.buf[1]='p';
     msg.len=2;
     Can0.write(msg);
   }
   conteurOdometrie++;
   if(conteurOdometrie>=50){
    calculePosition();
     conteurOdometrie=0;
   }
   // timerDetection++;
   // if(timerDetection>1000000)timerDetection=100000;
   timerAttente++;
    if(timerAttente>100000000)timerAttente=0;
}
String quelEtapeDeStrate(){
  String retour;
  iStrategieP=iStrategie;
//  if(strategie[strategieNumero][iStrategie]=='\0')Serial.println("truc");
  iStrategie+=2;
  while(strategie[strategieNumero][iStrategie] < 65||strategie[strategieNumero][iStrategie] > 90){
    iStrategie++;

  }
  for(int i=iStrategieP;i<iStrategie;i++){
    retour+=strategie[strategieNumero][i];
  }
  return retour;
}
byte machineEtatDeplacementAction(){
  switch (etapeActionDeplacement) {
    case 0:
      etapeActionDeplacement=actionOuDep();
    break;
    case 1:
      etapeActionDeplacement=Action();
    break;
    case 2:
      etapeActionDeplacement=PreparationGo();
    break;
    case 3:
      etapeActionDeplacement=PreparationTurn();
    break;
    case 4:
     etapeActionDeplacement=Turn1();
    break;
    case 5:
      etapeActionDeplacement=Go();
    break;
    case 6:
      etapeActionDeplacement=Turn2();
    break;
    case 7:
      etapeActionDeplacement=Attente();
    ///  etapeActionDeplacement=Turn();
    break;
    case 8:
      //message DebueRecalageFin
      msg.id=0x4;
      msg.buf[0]='D';
      msg.buf[1]='r';
      msg.buf[2]='f';
      msg.len=3;
      Can0.write(msg);
      etatp=8;
      return 1;
    break;
    case 9:
    etapeActionDeplacement=recalage();
    break;
    case 10:
    break;
    case 11:
    return 3;
    break;
    case 12:
      if(passe4){
        timerObjectif=convertionInt(isoInfo(0));
        timerAttente=0;
        passe4=false;
      }
      if(timerAttente>timerObjectif){
        passe4=true;
        etapeActionDeplacement=0;
      }
      etatp=12;
    break;
  }
  return 2;
}
byte Turn1(){
  //preTrétement
  if(strategieBicolor){
    emplacementObjectif.x=(float)(3000-convertionInt(isoInfo(1)));
    emplacementObjectif.y=(float)(convertionInt(isoInfo(2)));
  //  emplacementObjectif.a=(float)(((convertionInt(isoInfo(3))-90)*-1+90)%360);
  }else{
    emplacementObjectif.x=(float)(convertionInt(isoInfo(1)));
    emplacementObjectif.y=(float)(convertionInt(isoInfo(2)));
    //emplacementObjectif.a=(float)(convertionInt(isoInfo(3)));
  }
  //execution
  int turn1,xInt=(int)emplacementRelleRobot.x,yInt=(int)emplacementRelleRobot.y,aInt=(int)emplacementRelleRobot.a;
  int deltaX=(int)emplacementObjectif.x-xInt;
  int deltaY=(int)emplacementObjectif.y-yInt;
  if(deltaX!=0)turn1=(int)((float)atan((double)(((float)(deltaY))/((float)(deltaX))))*(float)180/PI);
  else if(deltaY>0)turn1=90;
  else if(deltaY<0)turn1=270;
  else turn1=0;
  if((deltaX)<0)turn1=turn1+180;
  turn1+=360;
  turn1+=(-aInt+360);
  turn1=turn1%360;
  senseGo=1;
  if(turn1>90&&turn1<270){
    senseGo=-1;
    turn1-=180;
  }else if(turn1>=270){
    turn1-=360;
  }
  lancemntDesMoteur(turn1*COEF_TURN*COEF_GO,turn1*COEF_TURN*COEF_GO,V_MAX_MOTEUR,V_MAX_MOTEUR,A_MAX_MOTEUR,A_MAX_MOTEUR);
  etatp=4;
  return 7;
}
byte Go(){

  int go;
  int deltaX=(int)emplacementObjectif.x-(int)emplacementRelleRobot.x;
  int deltaY=(int)emplacementObjectif.y-(int)emplacementRelleRobot.y;
  go=sqrt(deltaX*deltaX+deltaY*deltaY);
  distancePas=go*COEF_GO*senseGo;
  lancemntDesMoteur(distancePas,-distancePas,V_MAX_MOTEUR,V_MAX_MOTEUR,A_MAX_MOTEUR,A_MAX_MOTEUR);
  etatp=5;
  return 7;
}
byte Turn2(){
  if(isoInfo(3)!='n'){
    if(strategieBicolor)emplacementObjectif.a=(float)(((convertionInt(isoInfo(3))-90)*-1+90)%360);
    else emplacementObjectif.a=(float)(convertionInt(isoInfo(3)));
    int deltaA=emplacementObjectif.a-(int)emplacementRelleRobot.a+360;
    deltaA%=360;
    if(deltaA>180)deltaA-=360;
    lancemntDesMoteur(deltaA*COEF_TURN*COEF_GO,deltaA*COEF_TURN*COEF_GO,V_MAX_MOTEUR,V_MAX_MOTEUR,A_MAX_MOTEUR,A_MAX_MOTEUR);
  }
  etatp=6;
  return 7;
}
byte recalage(){
  distaceMMGo=convertionInt(isoInfo(1));
  distancePas=(int)distaceMMGo*COEF_GO;
  lancemntDesMoteur(distancePas,-distancePas,V_MAX_MOTEUR,V_MAX_MOTEUR,A_MAX_MOTEUR,A_MAX_MOTEUR);
  etatp=9;
  return 7;
}
byte actionOuDep(){
  etatp=0;
  Serial.print("etapeStrategei  :");
  etapeStrategei=quelEtapeDeStrate();
  Serial.println(etapeStrategei);
  if(etapeStrategei[0]=='F'){
    nbPiont=convertionInt(isoInfo(2));
    return 1;
  }
  else if (etapeStrategei[0]=='O'){
    nbPiont=convertionInt(isoInfo(2));
    return 1;
  }
  else if (etapeStrategei[0]=='A'){
    nbPiont=convertionInt(isoInfo(1));
    return 1;
  }
  else if (etapeStrategei[0]=='P'){
    nbPiont=convertionInt(isoInfo(2));
    return 1;
  }
  else if (etapeStrategei[0]=='V'){
    nbPiont=convertionInt(isoInfo(2));
    return 1;
  }
  else if (etapeStrategei[0]=='H'){
    nbPiont=convertionInt(isoInfo(2));
    return 1;
  }
  else if (etapeStrategei[0]=='B'){
    nbPiont=convertionInt(isoInfo(4));
    return 1;
  }
  else if (etapeStrategei[0]=='J'){
    nbPiont=convertionInt(isoInfo(2));
    return 1;
  }
  else if (etapeStrategei[0]=='G'){
    nbPiont=convertionInt(isoInfo(3));
    return 2;
  }
  else if (etapeStrategei[0]=='S'){
    nbPiont=convertionInt(isoInfo(0));
    return 8;
  }
  else if (etapeStrategei[0]=='T'){
    nbPiont=convertionInt(isoInfo(3));
    return 3;
  }
  else if (etapeStrategei[0]=='D'){
    nbPiont=convertionInt(isoInfo(4));
    return 4;
  }
  else if (etapeStrategei[0]=='R'){
    passeRecalage=true;
    RecalageDroit=false;
    RecalageGauche=false;
    nbPiont=convertionInt(isoInfo(3));
    return 9;
  }
  else if (etapeStrategei[0]=='E'){
    nbPiont=convertionInt(isoInfo(2));
    return 11;
  }
  else if (etapeStrategei[0]=='L'){
    nbPiont=convertionInt(isoInfo(1));
    return 12;
  }
  else return 0;
}
byte Action(){
  switch (etapeStrategei[0]) {
    case 'P':
    if(etapeStrategei[2]=='g'||etapeStrategei[2]=='d'){//pas coder PA
      msg.id=0x410;
      msg.buf[0]='P';
      msg.buf[1]='a';
      msg.buf[2]=etapeStrategei[2];
      if(etapeStrategei[4]=='e')msg.buf[3]='0';
      if(etapeStrategei[4]=='a')msg.buf[3]='1';
      msg.len=4;
      Can0.write(msg);
    }else{
      msg.id=0x400;
      msg.buf[0]='P';
      msg.buf[1]='b';
      msg.buf[2]=etapeStrategei[2];
      if(etapeStrategei[4]=='e')msg.buf[3]='0';
      if(etapeStrategei[4]=='a')msg.buf[3]='1';
      msg.len=4;
      Serial2.println(etapeStrategei[2]);
      Can0.write(msg);
    }
    break;
    case 'O':
    msg.id=0x700;
    msg.buf[0]='O';
    msg.buf[1]='g';
    msg.buf[2]=etapeStrategei[2];
    msg.buf[3]=etapeStrategei[3];
    msg.len=4;
    Can0.write(msg);
    Serial2.println("");
    Serial2.print(msg.buf[2]);
    Serial2.print(msg.buf[3]);
    Serial2.println("");
    Serial2.println("");
    break;
    case 'A':
    Serial2.println("testget");
    msg.id=0x700;
    msg.buf[0]='A';
    msg.buf[1]='g';
    msg.buf[2]=etapeStrategei[2];
    msg.len=3;
    Can0.write(msg);
    break;
    case 'V':
    if(etapeStrategei[0]=='g'||etapeStrategei[0]=='d'){//pas coder PA
      msg.id=0x410;
      msg.buf[0]='V';
      msg.buf[1]='a';
      msg.buf[2]=etapeStrategei[2];
      if(etapeStrategei[2]=='e')msg.buf[3]=0;
      if(etapeStrategei[2]=='a')msg.buf[3]=1;
      msg.len=4;
      Can0.write(msg);
    }else{
      msg.id=0x400;
      msg.buf[0]='V';
      msg.buf[1]='b';
      msg.buf[2]=etapeStrategei[2];
      if(etapeStrategei[4]=='e')msg.buf[3]=0;
      if(etapeStrategei[4]=='a')msg.buf[3]=1;
      msg.len=4;
      Can0.write(msg);
    }
    break;
    case 'H':
    msg.id=0x800;
    msg.buf[0]='H';
    msg.buf[1]='p';
    msg.buf[2]=etapeStrategei[2];
    msg.buf[3]=etapeStrategei[4];
    msg.len=4;
    Can0.write(msg);
    break;
    case 'J':
    msg.id=0x800;
    msg.buf[0]='S';
    msg.buf[1]='c';
    msg.buf[2]=etapeStrategei[2];
    msg.buf[3]=etapeStrategei[4];
    msg.len=4;
    Can0.write(msg);
    break;
    case 'F':
    msg.id=0x700;
    msg.buf[0]='D';
    msg.buf[1]='p';
    msg.buf[2]=etapeStrategei[2];
    msg.len=3;
    Can0.write(msg);
    break;
  }
  etatp=1;
  return 0;
  return 1;
}
byte PreparationGo(){
  int dir;
  if(comparChen(isoInfo(2),"av"))dir=1;
  else dir=-1;
  distaceMMGo=convertionInt(isoInfo(1));
  distancePas=(int)distaceMMGo*COEF_GO*dir;
  Serial.println(isoInfo(4));
  if(comparChen(isoInfo(4),"b"))lancemntDesMoteur(distancePas,-distancePas,V_BASSE_MOTEUR,V_BASSE_MOTEUR,A_BASSE_MOTEUR,A_BASSE_MOTEUR);
  if(comparChen(isoInfo(4),"h"))lancemntDesMoteur(distancePas,-distancePas,V_MAX_MOTEUR,V_MAX_MOTEUR,A_MAX_MOTEUR,A_MAX_MOTEUR);
  etatp=2;
  return 7;
}
byte PreparationTurn(){
  int dir;
  if(comparChen(isoInfo(2),"d"))dir=1;
  else dir=-1;
  if(!strategieBicolor){
    distanceDegTurn=convertionInt(isoInfo(1));
  }
  if(strategieBicolor){
    distanceDegTurn=convertionInt(isoInfo(1))-180;
  }
  distancePas=(int)(COEF_GO*COEF_TURN*distanceDegTurn*dir);
  lancemntDesMoteur(distancePas,distancePas,V_MAX_MOTEUR,V_MAX_MOTEUR,A_MAX_MOTEUR,A_MAX_MOTEUR);
  etatp=3;
  return 7;
}
byte Attente(){
  int mG,mD;
  // if(etatp==9){
  //   if((RecalageGauche||RecalageDroit)&&passeRecalage){
  //     Serial.println("teste ");
  //     motorGauch.setTargetAbs(5000);
  //     motorDroit.setTargetAbs(-5000);
  //     RecalageGauche=!RecalageGauche;
  //     RecalageDroit=!RecalageDroit;
  //     passeRecalage=!passeRecalage;
  //     controller.moveAsync(motorDroit,motorGauch);
  //     //motorGauch.setPosition(0);
  //     //motorDroit.setPosition(0);
  //   }
  // }
  if((etatp==5||etatp==2||etatp==9)&&arretLidaRoboEnface&&conditionTimerFin){
    controller.emergencyStop();
    int poseMg=motorGauch.getPosition();
    int poseMd=motorDroit.getPosition();

    if(distancePas<0){
      mG=distancePas-poseMg;
      mD=-distancePas-poseMd;
    }else{
      mG=distancePas+poseMd;
      mD=-distancePas+poseMg;
    }

    delay(1000);
    distancePas=mG;
    lancemntDesMoteur(mG,mD,V_MAX_MOTEUR,V_MAX_MOTEUR,A_MAX_MOTEUR,A_MAX_MOTEUR);
    arretLidaRoboEnface=false;
  }
  if(!controller.isRunning()){
    calculePosition();

    if(etatp==9){
      if(isoInfo(2)=='x'){
        if(!strategieBicolor){
          emplacementRelleRobot.x=convertionInt(isoInfo(3));
          emplacementRelleRobot.a=convertionInt(isoInfo(4));
        }else {
          emplacementRelleRobot.x=3000-convertionInt(isoInfo(3));
          emplacementRelleRobot.a=convertionInt(isoInfo(4))+(float)180;
          emplacementRelleRobot.a=((int)emplacementRelleRobot.a)%360;
        }
      }else {
        emplacementRelleRobot.y=convertionInt(isoInfo(3));
        emplacementRelleRobot.a=convertionInt(isoInfo(4));
      }
    }
    Serial2.print("empacement robot");
    Serial2.print(emplacementRelleRobot.x);
    Serial2.print(" ");
    Serial2.print(emplacementRelleRobot.y);
    Serial2.print(" ");
    Serial2.println(emplacementRelleRobot.a);
    if(etatp==4)return 5;
    if(etatp==5)return 6;
    return 0;
  }
  return 7;
}
String isoInfo(int nb){
  String retour;
  int j=0;
  byte PremierSeparateurTrouver=0,separateurTrouver=0;
  while(nb+1>separateurTrouver){
    if(etapeStrategei[j]==':')separateurTrouver++;
    j++;
  }
  PremierSeparateurTrouver=j;
  j++;
  while(1){
    if(etapeStrategei[j]==':')break;
    j++;
  }
  for(int i=PremierSeparateurTrouver;i<j;i++){
    retour+=etapeStrategei[i];
  }
  return retour;
}
int  convertionInt(String chaine){
  int longuerChaine=0,mul=1,retour=0,signe=0;
  if(chaine[0]=='-')signe=-1;
  else signe=0;
  while(chaine[longuerChaine] != '\0')longuerChaine++;
  for(int i=longuerChaine-1;i>-1-signe;i--){
    retour+=mul*(chaine[i]-48);
    mul*=10;
  }
  if(chaine[0]=='-')retour*=-1;
  return retour;
}
void lancemntDesMoteur(int nbPasMoteurGauche,int nbPasMoteurDroit,int vitesseMotueurGauche,
  int vitesseMotueurDroit,int axelereationMotueurGauche,int axelereationMotueurDroit){
    motorDroit.setPosition(0);
    motorDroit
     .setMaxSpeed(vitesseMotueurDroit)       // steps/s
     .setAcceleration(axelereationMotueurDroit); // steps/s^2
    motorGauch.setPosition(0);
    motorGauch
     .setMaxSpeed(vitesseMotueurGauche)       // steps/s
     .setAcceleration(axelereationMotueurGauche); // steps/s^2
    motorDroit
      .setTargetRel(nbPasMoteurDroit);
    motorGauch
       .setTargetRel(nbPasMoteurGauche);
   controller.moveAsync(motorDroit,motorGauch);
}
void calculePosition(){
  float impD=0,impG=0;
  coordonePolair sortieEncodeur;
  impD=(float)impultionEncodeurDroit;
  impG=(float)impultionEncodeurGauche;
  impultionEncodeurDroit=0;
  impultionEncodeurGauche=0;
  sortieEncodeur.r=impD*COEF_RD+impG*COEF_RG;
  sortieEncodeur.a=(float)atan((impD*COEF_RD*2-impG*COEF_RG*2)/200)*180/PI;
  //passage en coordoneCartesient et incrementation
  if(emplacementRelleRobot.a<0)emplacementRelleRobot.a+=360;
  emplacementRelleRobot.x+=(sortieEncodeur.r*((float)cos(PI*emplacementRelleRobot.a/180)));//(emplacementRelleRobot.a+sortieEcodeur.a*PI+emplacementRelleRobot.a)/2  possibiliter d'amelioration
  emplacementRelleRobot.y+=(sortieEncodeur.r*((float)sin(PI*emplacementRelleRobot.a/180)));
  emplacementRelleRobot.a-=(sortieEncodeur.a);
  //emplacementRelleRobot.a=emplacementRelleRobot.a+PI;
  while((emplacementRelleRobot.a>360||emplacementRelleRobot.a<-360)){
    if(emplacementRelleRobot.a>0)emplacementRelleRobot.a-=360;
    else emplacementRelleRobot.a+=360;
  }
  emplacementRelleRobot.a=emplacementRelleRobot.a;
  msg.id=0x200;
  msg.buf[0]='/';
  msg.buf[5]=0;
  aEnvoie=(int)emplacementRelleRobot.a;
  passe3=aEnvoie;
  msg.buf[4]=((passe3&=(1<<8)   )>>1);
  if (emplacementRelleRobot.x < 0){
    msg.buf[1]=(int)emplacementRelleRobot.x*-1;
    xEnvoie=(int)emplacementRelleRobot.x*-1;
    msg.buf[5]|=(0x02);
  }else{
    msg.buf[1]=(int)emplacementRelleRobot.x;
    xEnvoie=(int)emplacementRelleRobot.x;
  }
  passe1=xEnvoie;
  msg.buf[4]|= ((  passe1&=(0xF00)  )>>8);

  if (emplacementRelleRobot.y < 0){
    msg.buf[2]=(int)emplacementRelleRobot.y*-1;
    yEnvoie=(int)emplacementRelleRobot.y*-1;
    msg.buf[5]|=(0x04);
  }else{
    msg.buf[2]=(int)emplacementRelleRobot.y;
    yEnvoie=(int)emplacementRelleRobot.y;
  }
  passe2=yEnvoie;
  msg.buf[4]|= ((  passe2&=(0x700)  )>>4);

  msg.buf[3]=(int)emplacementRelleRobot.a;
  if(distancePas>0)msg.buf[5]|=1;
  else msg.buf[5]|=0;
  msg.len=6;
  Can0.write(msg);

}
void contageEncodeurDroit(){
  if(digitalRead(ENCODEUR_DROIT_B))impultionEncodeurDroit++;
  else impultionEncodeurDroit--;
}
void contageEncodeurGauche(){
  if(digitalRead(ENCODEUR_GAUCHE_B))impultionEncodeurGauche--;
  else impultionEncodeurGauche++;
}
