#ifndef IMPORTER_H
#define IMPORTER_H
#include <iostream>
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

#define DLLEXPORT __declspec(dllexport)

using namespace std;

namespace Engine
{
	class DLLEXPORT Importer_Test
	{
	public:
		bool DoTheImportThing(const std::string& pFile);
	};
}

#endif // IMPORTER_H
