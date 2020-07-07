#ifndef IMPORTER_H
#define IMPORTER_H
#include <iostream>
#include <Importer.hpp>// C++ importer interface
#include <scene.h>           // Output data structure
#include <postprocess.h>

#define DLLEXPORT __declspec(dllexport)

using namespace std;

namespace Engine
{
	class DLLEXPORT Importer_Test
	{
	private:

	public:
		bool DoTheImportThing(const std::string& pFile);
	};
}

#endif // IMPORTER_H
