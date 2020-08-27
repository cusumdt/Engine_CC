#ifndef IMPORTER_H
#define IMPORTER_H
#include <iostream>
#include <Importer.hpp>// C++ importer interface
#include <scene.h>           // Output data structure
#include <postprocess.h>

#define DLLEXPORT __declspec(dllexport)

using namespace std;

namespace Graficos2
{
	class DLLEXPORT Importer_Test // Todos los metodos van a ser exportados en un .lib para saber su direccion de memoria.
	{
	private:

	public:
		bool DoTheImportThing(const std::string& pFile);
	};
}

#endif // IMPORTER_H
