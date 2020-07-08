#include <Importer.h>
using namespace Engine;

bool Importer_Test::DoTheImportThing(const std::string& pFile)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if (!scene)
        return false;
    
    cout << "Modelo Cargado Correctamente." << endl;
    return true;
}
