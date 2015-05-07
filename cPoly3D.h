//This is a class that allows you to load a polygon from a .obj file using vertexes and indices
//It is not complete, it will require revising so that textures can be read and wrote properly to the correct vertices.
class cPoly3D
{
private:
	cDirect3D *dev;//pointer to the direct3D device
	string filename;
	double aVertices[1000];//array to hold vertices
	int iVertices;//index value for array
	short aIndices[1000];//array to hold indices
	int iIndices;//index value for array
	struct TEXTUREVERTEX vertices[1000];//holds the vertices in the CustomeVertex
	float xAlign, yAlign, zAlign;//aligns the object to the midpoints

	void readFile();

public:
	cPoly3D(cDirect3D* d3ddev, string file)
	{
		dev=d3ddev;		
		filename=file;
		iVertices=0;
		iIndices=0;
		readFile();
	}
	void prepPoly();
	void renderPoly();
	void loadTexture( void );
};







