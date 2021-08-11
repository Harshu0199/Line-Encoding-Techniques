#include <GL/glut.h>
#include<iostream>
#include<sstream>
#include<cstring>
#include<windows.h>
using namespace std;
int a[50],n,x;
int cmp(int n)
{
	if (n==0) return 1;
	else return 0;
}
std::string NumberToString (int Number)
{
	stringstream ss; ss << Number;
	return ss.str();
}
void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}
void printtext(int x, int y, string String)
{
//(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);
    for (int i=0; i<String.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
void display()
{
	int b[50],c[100],t=0,z;
	for(int i=0;i<n;i++)
	b[i]=a[i];
	string s;
	glClear(GL_COLOR_BUFFER_BIT);
	for(int j=0;j<=1;j++)
	{	
		glColor3f(0.0, 0.0, 0.0);
		s="0";printtext(16,99.8-60*j,s);
		s="1";printtext(16,109.8-60*j,s);
		s="-1";printtext(15.5,89.8-60*j,s);
		glPushAttrib(GL_ENABLE_BIT);
		glLineStipple(1,0xAAA0);
		glEnable(GL_LINE_STIPPLE);
		for(int i=0;i<n;i++)
		{
		glBegin(GL_LINES);
			glVertex2i(20+10*(i+1),80-60*j);
			glVertex2i(20+10*(i+1),120-60*j);
		glEnd();
		}
		glPopAttrib();
		glLineWidth(1.0);
		glBegin(GL_LINES);
			glVertex2i(20,80-60*j);
			glVertex2i(20,120-60*j);
			glVertex2i(20,100-60*j);
			glVertex2i(10*(n+1)+30,100-60*j);
		glEnd();
		glPointSize(5.0);
		glBegin(GL_POINTS);
			glVertex2i(20,110-60*j);
			glVertex2i(20,100-60*j);
			glVertex2i(20,90-60*j);
		glEnd();
		glLineWidth(2.0);
		switch(x)
		{
			case 1:                      //NRZ-L
				if(j==1)
				for(int k=0;k<n;k++)
				a[k]=cmp(a[k]);
				for(int i=0;i<n;i++)
				{
					glBegin(GL_LINES);
					glVertex2i(20+10*i,100+20*a[i]-10-60*j);
					glVertex2i(20+10*i+10,100+20*a[i]-10-60*j);
					if(a[i]!=a[i+1]||i==n-1)
					{
						glVertex2i(20+10*i+10,100-10-60*j);
						glVertex2i(20+10*i+10,100+20-10-60*j);
					}
					glEnd();
					glBegin(GL_POINTS);
					glVertex2i(20+10*(i+1),100-60*j);
					glEnd();
					s=NumberToString(i+1);
	   				 printtext(18+10*(i+1),96-60*j,s);
	   				 s=NumberToString(b[i]);
	   				 printtext(25+10*i,115-60*j,s);
				}
				break;
			case 2:                              //NRZ-I
				if(j==1)
				{
					for(int i=0;i<n;i++)
					a[i]=b[i];
					a[0]=cmp(a[0]);
				}	
				for(int i=0;i<n;i++)
				{
					if(i>0)
					if(a[i]==1)
					{
						if(a[i-1]==0)
						a[i]=1;
						else a[i]=0;
					}
					else a[i]=a[i-1];
				}
				for(int i=0;i<n;i++)
				{
					glBegin(GL_LINES);
					glVertex2i(20+10*i,100+20*a[i]-10-60*j);
					glVertex2i(20+10*i+10,100+20*a[i]-10-60*j);
					if(a[i]!=a[i+1]||i==n-1)
					{
						glVertex2i(20+10*i+10,100-10-60*j);
						glVertex2i(20+10*i+10,100+20-10-60*j);
					}
					glEnd();
					glBegin(GL_POINTS);
					glVertex2i(20+10*(i+1),100-60*j);
					glEnd();
					s=NumberToString(i+1);
	   				 printtext(18+10*(i+1),96-60*j,s);
	   				 s=NumberToString(b[i]);
	   				 printtext(25+10*i,115-60*j,s);
				}
				break;
			case 3:                                //MANCHESTER
				if(j==0)
				{
					for(int i=0;i<2*n;i++)
					{
						if(a[i]==0)
						{
							c[t++]=1;
							c[t++]=0;
						}
						else
						{
							c[t++]=0;
							c[t++]=1;
						}
					}
				}
				else
				{
					for(int i=0;i<2*n;i++)
					c[i]=cmp(c[i]);
				}	
				for(int i=0;i<2*n;i++)
				{
					glBegin(GL_LINES);
					glVertex2i(20+5*i,100+20*c[i]-10-60*j);
					glVertex2i(20+5*i+5,100+20*c[i]-10-60*j);
					if(i==2*n-1||i%2==0)
					{
						glVertex2i(20+5*i+5,100-10-60*j);
						glVertex2i(20+5*i+5,100+20-10-60*j);
					}
					if(i%2==0)
					if(a[i/2]==a[i/2+1])
					{
						glVertex2i(20+5*i+10,100-10-60*j);
						glVertex2i(20+5*i+10,100+20-10-60*j);
					}
					glEnd();
					glBegin(GL_POINTS);
					if(i%2!=0)
					glVertex2i(20+5*(i+1),100-60*j);
					glEnd();
					if(i%2==0)
					{
						s=NumberToString(i/2+1);
	   				 	printtext(18+10*(i/2+1),96-60*j,s);
	   					 s=NumberToString(b[i/2]);
	   				 	printtext(25+10*i/2,115-60*j,s);
	   				}
				}
				break;
			case 4:                                 //DIFFERENTIAL MANCHESTER
				t=0;
				if(j==1)
				{
					for(int i=0;i<n;i++)
					a[i]=b[i];
					a[0]=cmp(a[0]);
				}	
				for(int i=0;i<n;i++)
				{
					if(i>0)
					if(a[i]==1)
					{
						if(a[i-1]==0)
						a[i]=1;
						else a[i]=0;
					}
					else a[i]=a[i-1];
				}
					for(int i=0;i<n;i++)
					{
						if(a[i]==0)
						{
							c[t++]=1;
							c[t++]=0;
						}
						else
						{
							c[t++]=0;
							c[t++]=1;
						}
					}
				for(int i=0;i<2*n;i++)
				{
					glBegin(GL_LINES);
					glVertex2i(20+5*i,100+20*c[i]-10-60*j);
					glVertex2i(20+5*i+5,100+20*c[i]-10-60*j);
					if(i==2*n-1||i%2==0)
					{
						glVertex2i(20+5*i+5,100-10-60*j);
						glVertex2i(20+5*i+5,100+20-10-60*j);
					}
					if(i%2==0)
					if(a[i/2]==a[i/2+1])
					{
						glVertex2i(20+5*i+10,100-10-60*j);
						glVertex2i(20+5*i+10,100+20-10-60*j);
					}
					glEnd();
					glBegin(GL_POINTS);
					if(i%2!=0)
					glVertex2i(20+5*(i+1),100-60*j);
					glEnd();
					if(i%2==0)
					{
					s=NumberToString(i/2+1);
	   				 printtext(18+10*(i/2+1),96-60*j,s);
	   				 s=NumberToString(b[i/2]);
	   				 printtext(25+10*i/2,115-60*j,s);
	   				}
				}
				break;
			case 6:				//  SCRAMBLING 
				z=-1;t=0;
				if(j==0)
				for(int i=0;i<n;i++)
				{
					if(a[i]==1)
					{
						t++;
						a[i]=-z;
						z=a[i];
					}
					else if(i+8<=n)
					if(a[i]+a[i+1]+a[i+2]+a[i+3]+a[i+4]+a[i+5]+a[i+6]+a[i+7]==0)
					{
						s="V";printtext(25+10*(i+3),119,s);printtext(25+10*(i+3),59,s);
						s="B";printtext(25+10*(i+4),119,s);printtext(25+10*(i+4),59,s);
						s="V";printtext(25+10*(i+6),119,s);printtext(25+10*(i+6),59,s);
						s="B";printtext(25+10*(i+7),119,s);printtext(25+10*(i+7),59,s);
						a[i+3]=z;a[i+4]=-z;a[i+6]=a[i+4];a[i+7]=a[i+3];
						z=a[i+7];
						i=i+7;
					}
				}
				else
					for(int i=0;i<n;i++)
						a[i]=-a[i];
					goto case5;
			case 7: //        SCRAMBLING HDB3
				z=-1;t=0;
				if(j==0)
				for(int i=0;i<n;i++)
				{
					if(a[i]==1)
					{
						t++;
						a[i]=-z;
						z=a[i];
					}
					else if(i+4<=n)
					if(a[i]+a[i+1]+a[i+2]+a[i+3]==0)
					{
						if(t%2==0)
						{
							s="B";printtext(25+10*(i),119,s);printtext(25+10*(i),59,s);
							s="V";printtext(25+10*(i+3),119,s);printtext(25+10*(i+3),59,s);
							a[i]=-a[i-1];
							a[i+3]=a[i];
						}
						else
						{
							s="V";printtext(25+10*(i+3),119,s);printtext(25+10*(i+3),59,s);
							a[i+3]=a[i-1];
							t++;
						}
						z=a[i+3];
						i=i+3;
					}
				}
				else
					for(int i=0;i<n;i++)
						a[i]=-a[i];
					goto case5;
			case 5:// AMI AND PSEUDOTERNARY
				t=0;
				if(j==1)
				{
					for(int i=0;i<n;i++)
					{
						a[i]=b[i];
						a[i]=cmp(a[i]);
					}
				}	
				for(int i=0;i<n;i++)
				{
					if(a[i]==1)
					{
						t++;
						if(t%2==0)
						a[i]=-1;
					}
				}
				case5:
				for(int i=0;i<n;i++)
				{
					glBegin(GL_LINES);
					glVertex2i(20+10*i,100+10*a[i]-60*j);
					glVertex2i(20+10*i+10,100+10*a[i]-60*j);
					if(a[i]!=a[i+1]||i==n-1)
					{
						glVertex2i(20+10*i+10,100+10*a[i]-60*j);
						glVertex2i(20+10*i+10,100+10*a[i+1]-60*j);
					}
					glEnd();
					glBegin(GL_POINTS);
					glVertex2i(20+10*(i+1),100-60*j);
					glEnd();
					s=NumberToString(i+1);
	   				 printtext(18+10*(i+1),96-60*j,s);
	   				 s=NumberToString(b[i]);
	   				 printtext(25+10*i,115-60*j,s);
				}
				break;	
		}
		if(x==5)
		{
			s="AMI";
			if(j==1) s="Pseudoternary";
		}
		else
		{
			s="+VE LOGIC";
			if(j==1) s="-VE LOGIC";
		}
		printtext(30,125-60*j,s);
	}
	glFlush();
	for(int i=0;i<n;i++)
	a[i]=b[i];
}
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 400);
	glutInitWindowPosition (400, 100);
		cout<<"Enter The number of bits to be encoded: n =";
		cin>>n;
		cout<<"Enter the bits for encoding:\n";
		for(int i=0;i<n;i++)
		cin>>a[i];
		printf("Choose which line codind to be done?\n");
		printf("1.NRZ-L\n2.NRZ-I\n3.MANCHESTER\n4.DIFFERENTIAL MANCHESTER\n");
		printf("5.AMI and pseodoternary\n");
		printf("6.AMI WITH B8ZS SCRAMBLING\n7.AMI WITH HDB3 SCRAMBLING\n");
		cin>>x;
		switch(x)
		{
			case 1:
				glutCreateWindow ("NRZ-L ENCODING");
				break;
			case 2:
				glutCreateWindow ("NRZ-I ENCODING");
				break;
			case 3:
				glutCreateWindow ("MANCHESTER ENCODING");
				break;	
			case 4:
				glutCreateWindow ("DIFFERENTIAL MANCHESTER ENCODING");
				break;	
			case 5:
				glutCreateWindow ("AMI AND PSEODOTERNARY ENCODING");
				break;
			case 6:
				glutCreateWindow ("AMI WITH B8ZS SCRAMBLING");
				break;
			case 7:
				glutCreateWindow ("AMI WITH HDB3 SCRAMBLING");
				break;
		}
		init2D(0.3,0.3,2);
		glutDisplayFunc(display);
		glutMainLoop();
}
