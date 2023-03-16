#include <iostream>
#include <graphics.h>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <fstream>
#include <math.h>
#include <ctime>

using namespace std;
// Ordonnees du Robot
int xRbt = 350, yRbt = 75, rRbt = 50;
// Ordonnees du But
int xBut = 300, yBut = 350, rBut = 25;
// angle de rotation
double angle = 90;
int cpt = 0;
// les démenstions de l'écrant
int height = GetSystemMetrics(SM_CYSCREEN);
int width = GetSystemMetrics(SM_CXSCREEN);
    
void cercles(int Xobs,int Yobs,int Robs){
	// Draw the circle
	circle(xRbt, yRbt, rRbt);
	setcolor(2);
    circle(xBut, yBut, rBut);
	setcolor(4);
	circle(Xobs, Yobs, Robs);
	setcolor(15);
}
    
void rotate(){
	// Calculer les nouveaux positions de triangle
		int x11=xRbt-rRbt, y11=yRbt, x22=xRbt, y22=yRbt-rRbt, x33=xRbt+rRbt, y33=yRbt,x44=xRbt-rRbt/2,x55=xRbt-rRbt/2;
		int x66=xRbt+rRbt/2,x77=xRbt+rRbt/2,y44=yRbt-15,y55=yRbt+15,y66=yRbt-15,y77=yRbt+15;
		
		int x1 = xRbt+(x11-xRbt)*cos(angle* M_PI / 180)-(y11-yRbt)*sin(angle* M_PI / 180);
        int y1 = yRbt+(x11-xRbt)*sin(angle* M_PI / 180)+(y11-yRbt)*cos(angle* M_PI / 180);
        int x2 = xRbt+(x22-xRbt)*cos(angle* M_PI / 180)-(y22-yRbt)*sin(angle* M_PI / 180);
        int y2 = yRbt+(x22-xRbt)*sin(angle* M_PI / 180)+(y22-yRbt)*cos(angle* M_PI / 180);
        int x3 = xRbt+(x33-xRbt)*cos(angle* M_PI / 180)-(y33-yRbt)*sin(angle* M_PI / 180);
        int y3 = yRbt+(x33-xRbt)*sin(angle* M_PI / 180)+(y33-yRbt)*cos(angle* M_PI / 180);
        // Calculate the new positions of whiles
        int dx=xRbt+(x44-xRbt)*cos(angle* M_PI / 180)-(y44-yRbt)*sin(angle* M_PI / 180);
	    int dy=yRbt+(x44-xRbt)*sin(angle* M_PI / 180)+(y44-yRbt)*cos(angle* M_PI / 180);
	    int ex=xRbt+(x55-xRbt)*cos(angle* M_PI / 180)-(y55-yRbt)*sin(angle* M_PI / 180);
	    int ey=yRbt+(x55-xRbt)*sin(angle* M_PI / 180)+(y55-yRbt)*cos(angle* M_PI / 180);
	    int fx=xRbt+(x66-xRbt)*cos(angle* M_PI / 180)-(y66-yRbt)*sin(angle* M_PI / 180);
	    int fy=yRbt+(x66-xRbt)*sin(angle* M_PI / 180)+(y66-yRbt)*cos(angle* M_PI / 180);
	    int gx=xRbt+(x77-xRbt)*cos(angle* M_PI / 180)-(y77-yRbt)*sin(angle* M_PI / 180);
	    int gy=yRbt+(x77-xRbt)*sin(angle* M_PI / 180)+(y77-yRbt)*cos(angle* M_PI / 180);
	    // dessin des roues
	    line(dx,dy,ex,ey);
	    line(fx,fy,gx,gy);

        // dessin du triangle
        line(x1, y1, x2, y2);
        line(x2, y2, x3, y3);
        line(x3, y3, x1, y1);
        
}

void Move(int angle_robot_but ,float DistRoue1,float DistRoue2,float Angle){
	// Translation du Robot a partir des vitesses angulaires 
	xRbt += DistRoue1*cos(Angle)-DistRoue2*sin(Angle), 
	yRbt += DistRoue1*sin(Angle)+DistRoue2*cos(Angle);;
}

bool detecterOBS(int Xobs, int Yobs, int Robs) {
	  // Calcul de la distance entre le ROBOT et OBSTACLE
	  double dx = xRbt - Xobs;
	  double dy = yRbt - Yobs;
	  double d = sqrt(dx * dx + dy * dy);
	  double distance = rRbt + Robs + 50;
	  
	  return d < distance;
	}

bool detectBut(int Xbut, int Ybut, int Rbut) {
	  // Calcul de la distance entre le ROBOT et BUT
	  double dx = xRbt - Xbut;
	  double dy = yRbt - Ybut;
	  double d = sqrt(dx * dx + dy * dy);
	  double distance = 90;
	  
	  return d <= distance;
	}

void Random_But(){
	// Generee aleatoirement les cordonnees de BUT 
	xBut = rand() % width;
    yBut = rand() % height;
}

int main()
{
	initwindow(width, height, "Mini Projet robot auto");
	// initialiser les vitesses angulaires
    float wd=0,wg=0,DistEn100ms=0,Dist=0,cptTemps=0;
    // la distance parcourus par chaque roues
	float DistRoue1=0,DistRoue2=0;
    // on ouvre le fichier trajectoire pour enregistrer le trajectoire du robot
    string const nomFichier("trajectoire.txt");
    ofstream monFlux(nomFichier.c_str());
    // on ouvre le fichier obstacle pour lire les cordonnées des obstacles
    fstream fichier("obstacle.OBS");
    
    while (true)
    {
    	// lire les obstacles from fichier obstacle
    	string ligne; 
		int Xobs,Yobs,robs,Xobs1,Yobs1,robs1,Xobs2,Yobs2,robs2;
      	while(getline(fichier, ligne)) 
      	{
         fichier >> Xobs >> Yobs >> robs>> Xobs1 >> Yobs1 >> robs1 >> Xobs2 >> Yobs2 >> robs2;
      	}
    	// Clear screen
        cleardevice();
    	
    	// Calcul distance de chaque roue a partir de la vitesse angulaire
		DistRoue1 = (wd*0.1)*0.0124;
		DistRoue2 = (wg*0.1)*0.0124;
		// Calcul de la distance totale du ROBOT
		DistEn100ms = (DistRoue1 + DistRoue2)/2;
		Dist += DistEn100ms;
		// convertir angle degre en radian
		float Angle=(angle*3.14)/180 - 90.25;
		// covertir metre to pixel
		DistRoue1 = DistRoue1/0.0002568 ;
		DistRoue2 = DistRoue2/0.0002568 ;
		
        cercles(Xobs,Yobs,robs);
        cercles(Xobs1,Yobs1,robs1);
        cercles(Xobs2,Yobs2,robs2);
        // Calculer l'angle entre le ROBOT et le BUT
        double dx = xBut - xRbt;
        double dy = yBut - yRbt;
        double angle_robot_but = atan2(dy, dx) * 180 / M_PI;

        // Calculer la difference entre target angle et l'angle du ROBOT 
        double angle_diff = angle_robot_but - angle + 90;
        if (angle_diff > 180) angle_diff -= 360;

        // Mise a jour du l'angle du rotation (delais de rotation)
        angle += angle_diff * 0.06;

		// rotate ROBOT
        rotate();
        // detecter et Eviter OBSTACLE
		bool colli = false;
		if(detecterOBS(Xobs,Yobs,robs) || detecterOBS(Xobs1,Yobs1,robs1) || detecterOBS(Xobs2,Yobs2,robs2)){
			colli = true;
			angle -= 10;	
		}

        // attendre de l'Orientation du Robot vers But puis avancer
        cpt++;
        if (cpt >= 25 && !detectBut(xBut, yBut, rBut) && colli == false)
        {
        	wd = 1;
			wg = 1;
			Move(angle_robot_but,DistRoue1,DistRoue2,Angle);
		}else if(colli == true) {
			// dimunier la vitesse du ROBOT lorsque la detection d'Obstacle
			wd = 0.4;
			wg = 0.4;
			Move(angle_robot_but,DistRoue1,DistRoue2,Angle);
		}else{
			wd = 0.0;
			wg = 0.0;
			Move(angle_robot_but,DistRoue1,DistRoue2,Angle);
		}
		// Generation d'un nouveau but lorsque atteint l'ancien but
		if(detectBut(xBut, yBut, rBut)){
			Random_But();
			cpt =0;
		}
		
		
		// écrire la trajectoire dans le fichier trajectoire
		monFlux << "<< T :" << cptTemps << " s >> << X : " << xRbt << " px >> << Y : " << yRbt << " px >> << Vitesse angulaire Roue Droite : " << wd << " rad/s >> << Vitesse angulaire Roue Gauche : " << wg <<" rad/s >> << Distance : " << Dist << " m >>" << endl;
       
        delay(100);
        // Pour decrir chaque instant du ROBOT
        cptTemps += 0.1;
    }
    closegraph();
    return 0;
}


