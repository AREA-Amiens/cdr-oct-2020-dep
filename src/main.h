#include <SPI.h>
#include <TeensyStep.h>
#include <MsTimer2.h>
#include <FlexCan.h>
#include <kinetis_flexcan.h>


typedef struct{
  float x;
  float y;
  float a;
}coordoneCartesient;
typedef struct{
  float r;
  float a;
}coordonePolair;
#define COEF_RD 0.103085738//coeficient de la roue droit * son coretctifre / 2
#define COEF_RG 0.105383985//coeficient de la roue gauche * sont corectiffe / 2

#define COEF_ROT 0.0568810239//coeficient pour le calcuele de langle 2 / (pi * l'entraxe)

#define COEF_GO -7.520210565
#define COEF_TURN 1.483529864

#define V_MAX_MOTEUR 8400//1500
#define A_MAX_MOTEUR 2250//150

#define V_BASSE_MOTEUR 4200//1500
#define A_BASSE_MOTEUR 1125//150

#define DIR_MOTUER_GAUCHE     0
#define CAN_TX                3
#define CAN_RX                4
#define STEP_MOTEUR_GAUCHE    2
#define SLEEP_MOTEUR_GAUCHE   1
#define RESETE_MOTEUR_GAUCHE  5
#define DIR_MOTEUR_DROIT      6
#define STEP_MOTEUR_DROIT     7
#define SLEEP_MOTEUR_DROIT    8
#define XBEE_RX               9
#define XBER_TX               10
#define RESETE_MOTEUR_DROIT   11
#define M2                    12

#define SPI_SDA               18
#define SPI_SDL               19

#define M1                    24
#define M0                    25
#define ENABLE                26
#define ENCODEUR_DROIT_A      28
#define ENCODEUR_DROIT_B      27
#define ENCODEUR_DROIT_T      29
#define ENCODEUR_GAUCHE_A     31
#define ENCODEUR_GAUCHE_B     30
#define ENCODEUR_GAUCHE_T     32








void interpretationCan();
int comparChenCan(String comp);
int comparChen(String chaine1,String chaine2);
byte actionOuDep();
byte machineEtatDeplacementAction();
String quelEtapeDeStrate();
void IntrerrupTimer();
byte attenteTierte();
byte getionDesDeplacmentAction();
byte attenteStrategie();
byte getionDesDeplacment();
byte PreparationGo();
String isoInfo(int nb);
int convertionInt(String chaine);
void lancemntDesMoteur(int nbPasMoteurGauche,int nbPasMoteurDroit,int vitesseMotueurGauche,int vitesseMotueurDroit,int axelereationMotueurGauche,int axelereationMotueurDroit);
byte Attente();
byte PreparationTurn();
void calculePosition();
void contageEncodeurDroit();
void contageEncodeurGauche();
byte Turn1();
byte Go();
byte Turn2();
byte Action();
byte recalage();
