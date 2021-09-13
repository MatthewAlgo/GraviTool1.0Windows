#include <iostream>
#include <conio.h>
#include <dos.h>
#include <math.h>
#include <Windows.h>
#include "graphics.h"

using namespace std;
#define MASSB 50
#define MASSS 100
#define ANGULARVELOCITY 200
double xme[100000];
double yme[100000];
double newxme[100000];
double newyme[100000];
double angular = -50, ifin, jfin;

void ffillblue(int i, int j) {
	putpixel(i, j, BLUE);
	int dx[4] = { -1,0,1,0 };
	int dy[4] = { 0,1,0,-1 };
	for (unsigned int ii = 0; i < 4; i++) {
		if (i + dx[ii] <= 1000 && i + dx[ii] >= 1 && j + dy[ii] <= 1000 && j + dy[ii] >= 1) {
			if (getpixel(i + dx[ii], j + dy[ii]) == BLACK) {
				ffillblue(i + dx[ii], j + dy[ii]);
			}
		}
	}
}
int coster = 0;
double newton(double radius) {
	double F;
	//UNIVERSAL LAW OF GRAVITY
	F = (0.01 * MASSB * MASSS) / radius;
	return F - 1;
}
double radcalc(double xM, double yM, double xm, double ym) {
	double radsquared;
	double xdist, ydist;
	if (ym - yM > 0) {
		ydist = ym - yM;
	}
	else {
		ydist = yM - ym;
	}
	if (xm - xM > 0) {
		xdist = xm - xM;
	}
	else {
		xdist = xM - xm;
	}
	radsquared = pow(xdist, 2) + pow(ydist, 2);
	return sqrt(radsquared);
}
bool changed;
double futurex, futurey, ifinalu, jfinalu, difix, difig, wheretomovex, wheretomovey;
double maxi = -1, ifinalu2, jfinalu2;
int xM, yM, xm, ym;
double newxm, newym;
double fx0, fy0, fx1, fy1;
double force2;
double intercepti, interceptj;
unsigned long long contoru = 0;
double calcposition(int& xm, int& ym, int xM, int yM) {
	double centripetal_force, angular_velocity;
	centripetal_force = newton(radcalc(xM, yM, xm, ym)) * 10;
	return 0;
}
void fillpixel(int& xm, int& ym, int xM, int yM) {
	if (changed == false) {
		bool ver = 0;
		changed = true;
		Beep(1000, 100);
		double forcev = newton(radcalc(xM, yM, xm, ym)) * 10, maxi = -1;
		for (double i = xm - forcev - 10; i <= xm + forcev + 10; i += 0.5) {
			for (double j = ym - forcev - 10; j <= ym + forcev + 10; j += 0.5) {
				short int x = getpixel(i, j);
				if (x == WHITE) {
					if (radcalc(xm, ym, i, j) > maxi) {
						maxi = radcalc(xm, ym, i, j);
						ifin = i;
						jfin = j;
					}
					ver = 1;
				
				}
			}
		}
		if (ver == 0) {
			ifin = xm;
			jfin = ym;
		}
		if (fx0 != 0 && fx1 != 0 && fy0 != 0 && fy1 != 0) {
			line(fx0, fy0, fx1, fy1);
			setcolor(GREEN);
			circle(fx1, fy1, 5);
			setcolor(RED);
		}
		circle(ifin, jfin, 5);
		circle(xm + (angular), ym, 5);
		rectangle(ifin - 5, jfin - 5, ifin + 5, jfin + 5);
		setcolor(YELLOW);
		///
		line(xm + (angular), ym, ifin + (angular), jfin);
		line(ifin, jfin, ifin + (angular), jfin);
		///
		double cangular = angular;
		double x = radcalc(ifin + (angular), jfin, xm, ym);
		
		circle(ifin, jfin, 5);
		circle(ifin + angular, jfin, 5);
		setcolor(GREEN);
		line(xM, yM, ifin + angular, jfin);
		setcolor(YELLOW);
		line(xm, ym, ifin + (angular), jfin);
		line(xm, ym, xm + (angular), ym);
		///DRAWING SECOND COMPONENT
		
		newxm = ifin + angular;
		newym = jfin;
	

		line(newxm, newym, newxm + (ifin + angular - xm), newym + (jfin - ym));
		circle(newxm + (ifin + angular - xm), newym + (jfin - ym), 5);
		//FORCE VECTOR IN THE SECOND POSITION
		double force2 = newton(radcalc(xM, yM, xm, ym)) * 10;
		maxi = -1;
		ver = 0;
		for (double i = newxm - force2 - 10; i <= newxm + force2 + 10; i += 1) {
			for (double j = newym - force2 - 10; j <= newym + force2 + 10; j += 1) {
				short int x = getpixel(i, j);
				if (x == GREEN) {
					if (radcalc(newxm, newym, i, j) > maxi) {
						maxi = radcalc(newxm, newym, i, j);
						ifinalu = i;
						jfinalu = j;
					}
					ver = 1;
				
				}
			}
		}
		if (ver == 1) {
			circle(ifinalu, jfinalu, 5);
		}
		///
		fx0 = newxm;
		fy0 = newym;
		fx1 = newxm + (ifin + angular - xm);
		fy1 = newym + (jfin - ym);
		///
		futurex = fx0 + (ifin + angular - xm);
		futurey = fy0 + (jfin - ym);
	
		if (fx0 != 0 && fy0 != 0) {
			
			setcolor(BLUE);
			difix = ifinalu - newxm;
			difig = jfinalu - newym;
			///BLUECIRCLE PLUS BLUELINE PER COMPONENTS
			circle(futurex + difix, futurey + difig, 5);
			line(newxm, newym, futurex + difix, futurey + difig);
			circle(futurex, futurey, 5);
			line(futurex, futurey, ifinalu, jfinalu);
			setcolor(YELLOW);
			xm = newxm;
			ym = newym;
			wheretomovex = futurex + difix;
			wheretomovey = futurey + difig;
			newxm = wheretomovex;
			newym = wheretomovey;

		}
		setcolor(RED);
		delay(200);
	}
	else { //IF ONE ITERATION WAS COMPLETED
	   
		bool ver = 0;
		setcolor(YELLOW);
		
		//THE NEW GRAVITATIONAL VECTOR
		circle(ifinalu, jfinalu, 5);
		
		circle(newxm, newym, 5);


		line(newxm, newym, futurex + difix, futurey + difig);

		circle(futurex, futurey, 5);
		line(futurex, futurey, ifinalu, jfinalu);
		line(newxm, newym, ifinalu, jfinalu);
		line(xm, ym, newxm, newym);
		//LOWER LINE
		line(xm, ym, futurex, futurey);
		//RIGHT PARALLEL LINE
		line(futurex, futurey, newxm, newym);
		
		//LINKING WITH THE STAR (GREEN COMPONENT)
		
		setcolor(GREEN);
		line(newxm, newym, xM, yM);
		setcolor(YELLOW);
		
		//PRECALCULATING THE FUTURE MOVEMENT OF THE PLANET
		force2 = newton(radcalc(xM, yM, newxm, newym)) * 10;
		
		maxi = -1;
		ver = 0;

		bool verifinalu = 0;
		newxm = futurex + difix;
		newym = futurey + difig;
		for (double i = newxm - force2 - 20; i <= newxm + force2 + 20; i += 0.5) {
			for (double j = newym - force2 - 20; j <= newym + force2 + 20; j += 0.5) {
				short int x = getpixel(i, j);
				if (x == GREEN) {
					if (radcalc(newxm, newym, i, j) > maxi) {
						maxi = radcalc(newxm, newym, i, j);
						ifinalu2 = i;
						jfinalu2 = j;
						verifinalu = 1;
					}
					ver = 1;
					
				}
			}
		}
		if (verifinalu == 0) {
			ifinalu2 = newxm - force2 + 10;
			jfinalu2 = newym - force2 + 10;
		}
		if (ver == 1) {
			circle(ifinalu2, jfinalu2, 5);
		}
		

		line(newxm, newym, newxm + (newxm - xm), newym + (newym - ym));
		circle(newxm + (newxm - xm), newym + (newym - ym), 5);

		//newxm newym ARE THE OFFSET VALUES

		///PRECALCULATING THE COMPONENT AFER THE NEXT COMPONENT
		intercepti = ifinalu2 - newxm;
		interceptj = jfinalu2 - newym;


		line(newxm, newym, newxm + (newxm - xm) + intercepti, newym + (newym - ym) + interceptj);
		circle(newxm + (newxm - xm) + intercepti, newym + (newym - ym) + interceptj, 5);


		///DRAWING THE LINES
		line(newxm, newym, newxm + (newxm - xm) + intercepti, newym + (newym - ym) + interceptj);
		line(ifinalu2, jfinalu2, newxm + (newxm - xm) + intercepti, newym + (newym - ym) + interceptj);
		line(newxm + (newxm - xm) + intercepti, newym + (newym - ym) + interceptj, newxm + (newxm - xm), newym + (newym - ym));
		line(newxm + (newxm - xm), newym + (newym - ym), ifinalu2, jfinalu2);
		
		//THE YELLOW INTERCONNECTING LINE
		setcolor(YELLOW);
		line(newxm + (newxm - xm) + intercepti, newym + (newym - ym) + interceptj, xM, yM);
		setcolor(YELLOW);

		///TO MODIFY
		double cxm, cym;
		ifinalu = ifinalu2;
		jfinalu = jfinalu2;
		futurex = newxm + (newxm - xm);
		futurey = newym + (newym - ym);
		cxm = xm;
		cym = ym;
		xm = newxm;
		ym = newym;
		difix = ifinalu - newxm;
		difig = jfinalu - newym;
		
		newxm = newxm + (newxm - cxm) + intercepti;

		newym = newym + (newym - cym) + interceptj;


	}

}
int window1;
int window2;
int window3; 
void showinconsole() {
	coster++;
	cout << "_________________________REPORT No " << coster << "_________________________" << endl << endl;
	cout << "DISTANCE FROM PARENT STAR (ASTRONOMICAL UNIT): " << radcalc(xM, yM, xm, ym) << " units;" << endl;
	cout << "VECTORIAL FORCE STAR / PLANET: " << newton(radcalc(xM, yM, xm, ym)) * 10 << " force units" << endl;
	cout << "CURRENT SPEED / UNIT OF TIME: " << radcalc(xm, ym, newxm, newym) << " units/time" << endl;
	cout << "VERTICAL INTERCEPT (O_ALPHA): " << radcalc(xm, 1000, xm, ym) << " ym:" << ym << endl;
	cout << "HORIZONTAL INTERCEPT (O_BETA): " << radcalc(1000, ym, xm, ym) << " xm:" << xm << endl;
	cout << "UL CONSTRAINT: " << radcalc(xm, ym, 0, 0) << endl;
	cout << "UR CONSTRAINT: " << radcalc(xm, ym, 1000, 0) << endl;
	cout << "LL CONSTRAINT: " << radcalc(xm, ym, 0, 1000) << endl;
	cout << "LR CONSTRAINT: " << radcalc(xm, ym, 1000, 1000) << endl;
	cout << endl << endl << endl << endl;
	Beep(750, 100);
}
double speedvector[50];
double speedyvector[50];
void drawdistancegraph() {
	setcurrentwindow(window2);
	cleardevice();
	double distance = radcalc(xM, yM, xm, ym);
	speedvector[41] = distance;
	for (unsigned int i = 1; i <= 40; i++) {
		speedvector[i] = speedvector[i + 1];
	}
	setcolor(YELLOW);
	line(0, 200, 1000, 200);
	line(200, 0, 200, 1000);
	setcolor(WHITE);
	for (unsigned int i = 1; i <= 39; i++) {
		line(10 * (i-1), 200 - speedvector[i]/2 , 10 * i,200 - speedvector[i + 1]/2);
	}
	setcurrentwindow(window1);
}
void drawspeedgraph() {
	setcurrentwindow(window3);
	cleardevice();
	double speed = radcalc(xm, ym, newxm, newym);
	speedyvector[41] = speed;
	for (unsigned int i = 1; i <= 40; i++) {
		speedyvector[i] = speedyvector[i + 1];
	}
	setcolor(YELLOW);
	line(0, 200, 1000, 200);
	line(200, 0, 200, 1000);
	setcolor(WHITE);
	for (unsigned int i = 1; i <= 39; i++) {
		line(10 * (i - 1), 200 - speedyvector[i] / 2, 10 * i, 200 - speedyvector[i + 1] / 2);
	}
	setcurrentwindow(window1);
}
double centripetal_force, angular_velocity;
int main()
{
 	int gd = DETECT, gm, x = 320, y = 700, color, angle = 0;

	int radius;
	window1 = initwindow(1000, 1000, "GraviTool_Main");
	window2 = initwindow(400, 400, "DistanceGraph");
	window3 = initwindow(400, 400, "SpeedGraph");
	xM = 500; yM = 500, xm = 700, ym = 700;
	
	setcurrentwindow(window1);
	
	for (unsigned int i = 1; i; i++) {
	
		setcolor(YELLOW);
		
		circle(xM, yM, 30);

		setcolor(YELLOW);
		circle(xm, ym, 5);
		setcolor(WHITE);
		line(xm, ym, xM, yM);
		setcolor(RED);
		line(xm, ym, xm, yM);
		line(xm, ym, xM, ym);
		line(xM, ym, xM, yM);
		line(xm, yM, xM, yM);
		///
		line(xm, ym, 0, 0);
		line(xm, ym, 1000, 0);
		line(xm, ym, 0, 1000);
		line(xm, ym, 1000, 1000);
		///
		line(xm, 0, xm, ym);
		line(0, ym, xm, ym);
		line(100000, ym, xm, ym);
		line(xm, 10000, xm, ym);
		///
		line(xM, yM, 0, yM);
		line(xM, yM, xM, 0);
		line(xM, yM, 10000, yM);
		line(xM, yM, xM, 10000);
		fillpixel(xm, ym, xM, yM);
		contoru++;
		xme[contoru] = xm;
		yme[contoru] = ym;
		newxme[contoru] = newxm;
		newyme[contoru] = newym;
		setcolor(BLUE);
		for (unsigned int i = 1; i <= contoru; i++) {
			line(xme[i], yme[i], newxme[i], newyme[i]);
		}
		setcolor(YELLOW);
		showinconsole();
		drawdistancegraph();
		delay(10);
		
		setcolor(WHITE);

		delay(500);
		drawdistancegraph();
		drawspeedgraph();
		cleardevice();
	}
	getch();
	closegraph();
}