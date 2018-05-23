#define _CRT_SECURE_NO_WARNINGS 

#include "NMSEHelper.h"
#include <iostream>
#include <fstream>
#include <string>

NMSEHelper::NMSEHelper()
{
}


NMSEHelper::~NMSEHelper()
{
}

std::string NMSEHelper::RunTimePath(void) {
	char buf[MAX_PATH];
	GetModuleFileNameA(NULL, buf, MAX_PATH);
	return std::string(buf).substr(0, std::string(buf).find_last_of("\\/"));

}
