#include <Importer.h>
using namespace Engine3D;

bool Importer_Test::DoTheImportThing(const std::string& pFile)
{
    Assimp::Importer importer;
    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);
    // If the import failed, report it
    if (!scene)
    {
        //DoTheErrorLogging(importer.GetErrorString());
        return false;
    }
    // Now we can access the file's contents.
    //DoTheSceneProcessing(scene);
    cout << "Se cargo el model supuestamente"<<endl;
    // We're done. Everything will be cleaned up by the importer destructor
    return true;
}
