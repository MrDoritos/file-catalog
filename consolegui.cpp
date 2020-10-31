#include <iostream>
#include <string>
#include "box.h"
#include "boxsize.h"
#include "image.h"
#if defined __WIN32
#include <Windows.h>
#define delay(x) Sleep(x)
#elif defined __linux__
#define delay(x) usleep(x)
#endif
#define size_x 210
#define size_y 140

using namespace std;

int main() {
	HANDLE con, last = GetStdHandle(-11);
	
	con = CreateConsoleScreenBuffer(0x80000000U | 0x40000000U, 0, 0, 1, 0);
	#ifdef NOGUI
	#else
	SetConsoleActiveScreenBuffer(con);
	#endif
	
	box camera = box(0,0,size_x,size_y);
	
	float q = camera.getMinScale(0.333);
	float g = 0;
	
	//image i[3];
	//image i[3]{"test.png", &camera, g,g,q,size_y};
	//for (int h = 0; h < 3; h++) {
		//i[h] = image("test.png", &camera, 0, 0, q, size_y);
	//}
	image i1 = image("test.png", &camera, 0, 0, size_x, size_y);
	
	image i2 = image("test1.png", &camera, 0, 0, q, size_y);
	//image i3 = image("test2.png", &camera, 0, 0, q, size_y);
	
	
	i1.resize(0,0,size_x,size_y);
	
	//g+=q;
	i2.resize(q,q,q,q);
	//i2.limitedResize(q,q);
	//g+=q;
	//i3.resize(g,0,q,size_y);
	//g+=q;
	
	
	//i1.raster();
	
	//i2.raster();
	//i3.raster();
	
	//Print
	//char* fb = camera.getFramebuffer(); 
	//for (int is = 0; is < camera.characters(); is++) {
	//	cout << fb[is];
	//}
	i2.resize(0,0,size_x - 5,size_y);
	//i1.resize(0,0,size_x / 2,size_y);
	float i = 0;
	while (1) {
		i+=0.005;	
		if (i > M_PI * 2) i = 0.0;
		//camera.clear();
		i2.clear();
		//i1.clear();
		
		i2.sampletest(i);
		//i1.sampletest(0-i);
		
		const struct rect {
			static void draw(image& d) {
				d.drawline(0, 0, 30, 0);
				d.drawline(20, 20, 50, 20);
				d.drawline(0,0,20,20);
				d.drawline(30, 0, 50, 20);
				
				d.drawline(0,0,0,30);
				d.drawline(0,30,20,50);
				d.drawline(20,20,20,50);
				d.drawline(20,50,50,50);
				d.drawline(50,20,50,50);
				
			}
			
			const struct pnt {
				public:
				pnt(int x, int y, int z) {
					this->x = x;
					this->y = y;
					this->z = z;
				}
				int x, y, z;
			} points[8] = {{0,0,0},{1,0,0},{0,0,1},{1,0,1},
						   {0,1,0},{1,1,0},{0,1,1},{1,1,1}};
		} r;
		//i2.drawline(20, 20, 80, 80);
		//r.draw(i2);
	
		//i1.raster();
		i2.raster();		
		
		//delay(10);
		LPDWORD d = (LPDWORD)alloca(sizeof(LPDWORD));
		WriteConsoleOutputCharacter(con, camera.getFramebuffer(), camera.characters(), {0,0}, d);
	}
	SetConsoleActiveScreenBuffer(last);
	return 0;
}