

//VARIABLE


// Servo
#include <Servo.h>
#include <List.hpp>
Servo monservo; // Déclare l'utilisation d'un servomoteur
int position=0; // Position du servo moteur
int pincapt=12;

// Capteur
#define pinTrig 2
#define pinEcho 3
float duration, distance; // valeurs décimales

// Moteurs
int in1=4; // droite
int in2=5; 

int in3=6; // gauche
int in4=7;
int i = 0;


List<float> list_dist;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// SETUP/LOOP
void setup(){
  // Capteur:
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  Serial.begin(9600);

  // Led:
  pinMode (13, OUTPUT);

  // Servo
  monservo.attach(pincapt); // Servomoteur connecté sur le port 12
  monservo.write(position);

  // Moteurs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}


void loop(){

 int j = 0;
 while (j<10)
 {
 sonar(350,8); //recherche du cube en tournant
 delay(1000);
 
 int index =cible(350,8);
 int angle = index*340;
 float dist = list_dist[index]/2-10/100*(list_dist[index]/2);

 droitegauche(true,(angle-10/100*angle)); //on se met en face de la position 
                                          //de la plus grande distance
 delay(500);
 avancer_reculer(true); //fait avncer le robot tout droit
 
 float temps = dist/0.04481;
 delay(temps); //permt de faire avancer le robot 
               //sur la moitier de la plus longue distance
               
 arret(); //arrête le robot 
 delay(500);
 list_dist.clear();
 delay(500); 
 j++;
 }
 arret();
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//FUNCTION

// fonction qui fait tourner le robot à droite si 
//pos est a true sinon le robot tourne a gauche
void droitegauche (bool pos, int angle)
{
  if (pos)
  {
    digitalWrite(in1,1);
    digitalWrite(in2,0);
    digitalWrite(in3,0);
    digitalWrite(in4,1);
    delay (angle);
    arret();
  }
  else
  {
    digitalWrite(in1,0);
    digitalWrite(in2,1);
    digitalWrite(in3,1);
    digitalWrite(in4,0);
    delay (angle);
    arret();
  }
}


//permet d'arrete le robot 
void arret()
{
    digitalWrite(in1,0);
    digitalWrite(in2,0);
    digitalWrite(in3,0);
    digitalWrite(in4,0);
}

//si av est a true le robot avance sinon il recule
void avancer_reculer(bool av)
{
  if(!av)
  {
    digitalWrite(in1,1);
    digitalWrite(in2,0);
    digitalWrite(in3,1);
    digitalWrite(in4,0);
  }
  else
  {
    digitalWrite(in1,0);
    digitalWrite(in2,1);
    digitalWrite(in3,0);
    digitalWrite(in4,1);
  }
}


// x est l'attente entre chaque arrêt du robot lorsqu'il tourne 
// nb ets le nombre de fragmentation pour un tour que fait le robot
// cette fonction permet de faire tourner le robot et 
//fait la liste des distance rencontrer en tournant 
void sonar (int x, int nb)
{
  for(int i=0;i<nb;i++)
  {
    float dist = calculdist();
    list_dist.add(dist);
    droitegauche(true,x); //fait une rotation vers la droite pendant x milliseconde
    delay(500);
  }
}

void esquive()
{
  distance = calculdist();

   if (distance<=28.0)
  {
    digitalWrite(in1,1);
    digitalWrite(in2,0);

    digitalWrite(in3,0);
    digitalWrite(in4,1);
  }
    else
  {
    avancer_reculer(true);
  }
}

// fonction qui permet de calculer la distance grâce au module ultrason
float calculdist()
{
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2); // On s'assure que le pinTrig est au niveau bas
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10); // Envoi une rafale d'ultrasons
  digitalWrite(pinTrig, LOW);

  duration = pulseIn(pinEcho, HIGH); // détermine la durée pdt laquelle pinEcho est "HIGH"
  distance = (0.0340*duration)/2; // d=vt, t est en µs donc on convertit 340m/s en cm/µs
  return distance;
}


//fonction qui renc=voie la place de l'élément maximum de la 
//liste pour ensuite choisir la bonne destination
 int cible(int x,int nb)
{
  float maxnum = 0;
  int index = 0;
  for(int i=0;i<nb;i++)
  {
    if (list_dist[i]>maxnum)
    {
      index = i;
      maxnum= list_dist[i]; 
    }
  }
  return (index);
}

void bloquer()
{
   float dist = calculdist();
   delay(5000);
   float dist2 = calculdist();
   float ecart = dist-dist2;
   if (ecart <1 && ecart>0 ||  ecart> -1 && ecart <0)
   {
    avancer_reculer(false);
    droitegauche(true,300);
   }
}
