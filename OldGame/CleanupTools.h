#pragma once
#ifndef CLEANUPTOOLS_H
#define CLEANUPTOOLS_H

//SafeRealse function from the D2D tutorial that might be usefull in other parts of the program
template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != nullptr)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = nullptr;
	}
}

#endif // !CLEANUPTOOLS_H



