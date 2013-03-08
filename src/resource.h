/************************************************************************
*             INCLUDE THIS HEADER FILE INTO YOUR PROJECT                *
*************************************************************************
* Accessing binary data of a member:           RESOURCES::MEMBER.data   *
* Getting the binary data size of a member:    RESOURCES::MEMBER.length *
************************************************************************/

#ifndef RESOURCES_H
#define RESOURCES_H

struct RCDATA
{
	unsigned int length;
	unsigned char* data;
};

struct RESOURCES
{
	// File: "/home/ronny/Documents/Developement/avconvgui/res/app.ico"
	public: static const RCDATA APP_ICO;
};

#endif // RESOURCES_H
