#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

int PIXEL_SIZE = 5;

void init() {
    glClearColor(0.4,0.2,0.8,1.0);
    glColor3i(0.0,0.0,0.0);
};

void reshape(int w, int h) {
    glViewport(0,0,GLsizei(w),GLsizei(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50,50,-50,50);
    glMatrixMode(GL_MODELVIEW);
}


void PlotPixel(int x, int y, int psize) {
    glPointSize(psize);
    glBegin(GL_POINTS);

    glVertex2i(x,y);

    glEnd();

    glFlush();
}

void display_callback_line();

class DrawLine {
    
    public: int x,y,a,b;

    public: int main(int argc, char **argv) {

        cout << "Enter coordinates of point 1:" << endl;
        cin >> x >> y;
        cout << "Enter coordinates of point 2:" << endl;
        cin >> a >> b;

        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_RGB);

        glutInitWindowPosition(200,100);
        glutInitWindowSize(600,600);

        glutCreateWindow("Window_World");
        glutReshapeFunc(reshape);
        glutDisplayFunc(display_callback_line);
        
        init();

        glutMainLoop();
        return 0;
    }

    void midpointline(int x1, int y1, int x2, int y2) {
        int dx, dy, i, e;
        int incx, incy, inc1, inc2;
        int x,y;

        dx = x2-x1;
        dy = y2-y1;

        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;
        incx = 1;
        if (x2 < x1) incx = -1;
        incy = 1;
        if (y2 < y1) incy = -1;
        x = x1; y = y1;
        if (dx > dy) {
            PlotPixel(x, y,PIXEL_SIZE);
            e = 2 * dy-dx;
            inc1 = 2*(dy-dx);
            inc2 = 2*dy;
            for (i=0; i<dx; i++) {
                if (e >= 0) {
                    y += incy;
                    e += inc1;
                }
                else
                    e += inc2;
                x += incx;
                PlotPixel(x, y,PIXEL_SIZE);
            }

        } else {
            PlotPixel(x, y,PIXEL_SIZE);
            e = 2*dx-dy;
            inc1 = 2*(dx-dy);
            inc2 = 2*dx;
            for (i=0; i<dy; i++) {
                if (e >= 0) {
                    x += incx;
                    e += inc1;
                }
                else
                    e += inc2;
                y += incy;
                PlotPixel(x, y, PIXEL_SIZE);
            }
        }
    }
};

DrawLine obj_linedrawer;

void display_callback_line() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f (0.0, 0.0, 0.0);
    obj_linedrawer.midpointline(-50,0,50,0);
    obj_linedrawer.midpointline(0,-50,0,50);
    cout << obj_linedrawer.x,obj_linedrawer.y,obj_linedrawer.a,obj_linedrawer.b + "\n";
    obj_linedrawer.midpointline(obj_linedrawer.x,obj_linedrawer.y,obj_linedrawer.a,obj_linedrawer.b);
    glFlush ();
};

void display_callback_circle();

class DrawCircle {
    int pntX1, pntY1, r;

    public: void midPointCircleAlgo()
    {
        int x = 0;
        int y = r;
        float decision = 5/4 - r;
        PlotPixel(x, y, PIXEL_SIZE);

        while (y > x)
        {
            if (decision < 0)
            {
                x++; 
                decision += 2*x+1;
            }
            else
            {
                y--;
                x++;
                decision += 2*(x-y)+1;
            }
            PlotPixel(x, y, PIXEL_SIZE);
            PlotPixel(x, -y, PIXEL_SIZE);
            PlotPixel(-x, y, PIXEL_SIZE);
            PlotPixel(-x, -y, PIXEL_SIZE);
            PlotPixel(y, x, PIXEL_SIZE);
            PlotPixel(-y, x, PIXEL_SIZE);
            PlotPixel(y, -x, PIXEL_SIZE);
            PlotPixel(-y, -x, PIXEL_SIZE);
        }

    }

    public: int main(int argc, char** argv)
    {	
        
        // cout << "Enter the coordinates of the center:\n\n" << endl;

        // cout << "X-coordinate   : "; cin >> pntX1;
        // cout << "\nY-coordinate : "; cin >> pntY1;
        cout << "\nEnter radius : "; cin >> r;


        glutInit(&argc, argv);
        glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize (700, 700);
        glutInitWindowPosition (100, 150);
        glutCreateWindow ("Circle Drawing Algorithm");
        glutReshapeFunc(reshape);
        glutDisplayFunc(display_callback_circle);
        init ();
        glutMainLoop();

        return 0;

    }
};

DrawCircle obj_circledrawer;

void display_callback_circle()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);
    obj_linedrawer.midpointline(-50,0,50,0);
    obj_linedrawer.midpointline(0,-50,0,50);
    obj_circledrawer.midPointCircleAlgo();
    glFlush ();
}

int main(int argc, char** argv) {
    string c;
    cout << "What do you want to draw?? (Line/Circle)" << endl;
    cin >> c;

    c == "Line" ? obj_linedrawer.main(argc, argv) : obj_circledrawer.main(argc, argv);
    return 0;
}