#ifndef GLUTAPP_H
#define GLUTAPP_H

class GLUTApplication
{
public:
	GLUTApplication(){}
	virtual ~GLUTApplication(){}
	virtual void setup(){}
	virtual void render(){}
	virtual void onResizeWindow( int w, int h ){}
};

#endif