#pragma once
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;
const string CANNOT_FIND_FILE_STRING = "Cannot find file: ";
namespace ErrorHandler
{
	void vShowFileNotFoundMessageBox(string &s_message);
	template<typename T> void vFreeSpaceFromVectors(vector<T*> &c_vector0);
	template<typename T> void vFreeSpaceFromVectors(vector<T*> &c_vector0, vector<T*> &c_vector1);
	template<typename T> void vFreeSpaceFromVectors(vector<T*> &c_vector0, vector<T*> &c_vector1, vector<T*> &c_vector2);
}

template<class T> void ErrorHandler::vFreeSpaceFromVectors(vector<T*> &c_vector0)
{
	for (int i_i = 0; i_i < c_vector0.size(); i_i++)
		delete c_vector0[i_i];
}
template<class T> void ErrorHandler::vFreeSpaceFromVectors(vector<T*> &c_vector0, vector<T*> &c_vector1)
{
	vFreeSpaceFromVectors(c_vector0);
	vFreeSpaceFromVectors(c_vector1);
}
template<class T> void ErrorHandler::vFreeSpaceFromVectors(vector<T*> &c_vector0, vector<T*> &c_vector1, vector<T*> &c_vector2)
{
	vFreeSpaceFromVectors(c_vector0, c_vector1);
	vFreeSpaceFromVectors(c_vector2);
}