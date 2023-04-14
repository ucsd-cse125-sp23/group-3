#include <assimp/Importer.hpp>

class BlinderImporter
{
public:
	BlinderImporter();
	~BlinderImporter();

private:
	Assimp::Importer importer;
};
