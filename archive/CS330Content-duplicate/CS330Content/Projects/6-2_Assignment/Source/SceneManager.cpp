///////////////////////////////////////////////////////////////////////////////
// shadermanager.cpp
// ============
// manage the loading and rendering of 3D scenes
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////

#include "SceneManager.h"

#include <glm/gtx/transform.hpp>

// declare the global variables
namespace
{
	const char* g_ModelName = "model";
	const char* g_ColorValueName = "objectColor";
	const char* g_TextureValueName = "objectTexture";
	const char* g_UseTextureName = "bUseTexture";
	const char* g_UseLightingName = "bUseLighting";
}

/***********************************************************
 *  SceneManager()
 *
 *  The constructor for the class
 ***********************************************************/
SceneManager::SceneManager(ShaderManager *pShaderManager)
{
	m_pShaderManager = pShaderManager;
	m_basicMeshes = new ShapeMeshes();
}

/***********************************************************
 *  ~SceneManager()
 *
 *  The destructor for the class
 ***********************************************************/
SceneManager::~SceneManager()
{
	// free up the allocated memory
	m_pShaderManager = NULL;
	if (NULL != m_basicMeshes)
	{
		delete m_basicMeshes;
		m_basicMeshes = NULL;
	}
	// clear the collection of defined materials
	m_objectMaterials.clear();
}

/***********************************************************
 *  FindMaterial()
 *
 *  This method is used for getting a material from the previously
 *  defined materials list that is associated with the passed in tag.
 ***********************************************************/
bool SceneManager::FindMaterial(std::string tag, OBJECT_MATERIAL& material)
{
	if (m_objectMaterials.size() == 0)
	{
		return(false);
	}

	int index = 0;
	bool bFound = false;
	while ((index < m_objectMaterials.size()) && (bFound == false))
	{
		if (m_objectMaterials[index].tag.compare(tag) == 0)
		{
			bFound = true;
			material.ambientColor = m_objectMaterials[index].ambientColor;
			material.ambientStrength = m_objectMaterials[index].ambientStrength;
			material.diffuseColor = m_objectMaterials[index].diffuseColor;
			material.specularColor = m_objectMaterials[index].specularColor;
			material.shininess = m_objectMaterials[index].shininess;
		}
		else
		{
			index++;
		}
	}

	return(true);
}

/***********************************************************
 *  SetTransformation()
 *
 *  This method is used for setting the transform buffer
 *  using the passed in transformation values.
 ***********************************************************/
void SceneManager::SetTransformations(
	glm::vec3 scaleXYZ,
	float XrotationDegrees,
	float YrotationDegrees,
	float ZrotationDegrees,
	glm::vec3 positionXYZ)
{
	// variables for this method
	glm::mat4 modelView;
	glm::mat4 scale;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
	glm::mat4 translation;

	// set the scale value in the transform buffer
	scale = glm::scale(scaleXYZ);
	// set the rotation values in the transform buffer
	rotationX = glm::rotate(glm::radians(XrotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::radians(YrotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::radians(ZrotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
	// set the translation value in the transform buffer
	translation = glm::translate(positionXYZ);

	// matrix math is used to calculate the final model matrix
	modelView = translation * rotationX * rotationY * rotationZ * scale;
	if (NULL != m_pShaderManager)
	{
		// pass the model matrix into the shader
		m_pShaderManager->setMat4Value(g_ModelName, modelView);
	}
}

/***********************************************************
 *  SetShaderColor()
 *
 *  This method is used for setting the passed in color
 *  into the shader for the next draw command
 ***********************************************************/
void SceneManager::SetShaderColor(
	float redColorValue,
	float greenColorValue,
	float blueColorValue,
	float alphaValue)
{
	// variables for this method
	glm::vec4 currentColor;

	currentColor.r = redColorValue;
	currentColor.g = greenColorValue;
	currentColor.b = blueColorValue;
	currentColor.a = alphaValue;

	if (NULL != m_pShaderManager)
	{
		// pass the color values into the shader
		m_pShaderManager->setVec4Value(g_ColorValueName, currentColor);
	}
}

/***********************************************************
 *  SetShaderMaterial()
 *
 *  This method is used for passing the material values
 *  into the shader.
 ***********************************************************/
void SceneManager::SetShaderMaterial(
	std::string materialTag)
{
	if (m_objectMaterials.size() > 0)
	{
		OBJECT_MATERIAL material;
		bool bReturn = false;

		// find the defined material that matches the tag
		bReturn = FindMaterial(materialTag, material);
		if (bReturn == true)
		{
			// pass the material properties into the shader
			m_pShaderManager->setVec3Value("material.ambientColor", material.ambientColor);
			m_pShaderManager->setFloatValue("material.ambientStrength", material.ambientStrength);
			m_pShaderManager->setVec3Value("material.diffuseColor", material.diffuseColor);
			m_pShaderManager->setVec3Value("material.specularColor", material.specularColor);
			m_pShaderManager->setFloatValue("material.shininess", material.shininess);
		}
	}
}

/**************************************************************/
/*** STUDENTS CAN MODIFY the code in the methods BELOW for  ***/
/*** preparing and rendering their own 3D replicated scenes.***/
/*** Please refer to the code in the OpenGL sample project  ***/
/*** for assistance.                                        ***/
/**************************************************************/

 /***********************************************************
  *  DefineObjectMaterials()
  *
  *  This method is used for configuring the various material
  *  settings for all of the objects within the 3D scene.
  ***********************************************************/
void SceneManager::DefineObjectMaterials()
{
	/*** STUDENTS - add the code BELOW for defining object materials. ***/
	/*** There is no limit to the number of object materials that can ***/
	/*** be defined. Refer to the code in the OpenGL Sample for help  ***/

	// Define white material for most objects (cone, cylinder, boxes, sphere)
	// MATTE white surfaces - no specular highlights
	OBJECT_MATERIAL whiteMaterial;
	whiteMaterial.ambientColor = glm::vec3(0.1f, 0.1f, 0.1f);
	whiteMaterial.ambientStrength = 0.08f;  // Reduced to prevent color bleed
	whiteMaterial.diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);  // Pure white
	whiteMaterial.specularColor = glm::vec3(0.0f, 0.0f, 0.0f);  // NO specular - matte finish
	whiteMaterial.shininess = 2.0;  // Very low shininess
	whiteMaterial.tag = "white";
	m_objectMaterials.push_back(whiteMaterial);

	// Define PINK material for ground plane
	// MATTE pink surface
	OBJECT_MATERIAL pinkMaterial;
	pinkMaterial.ambientColor = glm::vec3(0.1f, 0.1f, 0.1f);
	pinkMaterial.ambientStrength = 0.08f;  // Reduced
	pinkMaterial.diffuseColor = glm::vec3(1.0f, 0.7f, 0.85f);  // Pink surface
	pinkMaterial.specularColor = glm::vec3(0.0f, 0.0f, 0.0f);  // NO specular - matte
	pinkMaterial.shininess = 2.0;  // Very low shininess
	pinkMaterial.tag = "pink";
	m_objectMaterials.push_back(pinkMaterial);

	// Define BLACK material for back plane
	// PURE BLACK backdrop - no pink contamination
	OBJECT_MATERIAL blackMaterial;
	blackMaterial.ambientColor = glm::vec3(0.02f, 0.02f, 0.02f);  // Nearly black ambient
	blackMaterial.ambientStrength = 0.05f;  // Minimal ambient
	blackMaterial.diffuseColor = glm::vec3(0.0f, 0.0f, 0.0f);  // Pure black
	blackMaterial.specularColor = glm::vec3(0.0f, 0.0f, 0.0f);  // NO specular
	blackMaterial.shininess = 1.0;  // Minimal shininess
	blackMaterial.tag = "black";
	m_objectMaterials.push_back(blackMaterial);

}

/***********************************************************
 *  SetupSceneLights()
 *
 *  This method is called to add and configure the light
 *  sources for the 3D scene.  There are up to 4 light sources.
 ***********************************************************/
void SceneManager::SetupSceneLights()
{
	// this line of code is NEEDED for telling the shaders to render
	// the 3D scene with custom lighting, if no light sources have
	// been added then the display window will be black - to use the
	// default OpenGL lighting then comment out the following line
	m_pShaderManager->setBoolValue(g_UseLightingName, true);

	/*** STUDENTS - add the code BELOW for setting up light sources ***/
	/*** Up to four light sources can be defined. Refer to the code ***/
	/*** in the OpenGL Sample for help                              ***/

	// Light Source 1 - Primary overhead key light from upper-left
	// Positioned to create left-to-right directional shadow gradient
	m_pShaderManager->setVec3Value("lightSources[0].position", -2.0f, 12.0f, 4.0f);
	// NEUTRAL gray ambient - prevents pink color bleed onto white objects
	m_pShaderManager->setVec3Value("lightSources[0].ambientColor", 0.12f, 0.12f, 0.12f);
	// Strong WHITE diffuse - creates directional lighting
	// Left surfaces bright, right surfaces shadowed
	m_pShaderManager->setVec3Value("lightSources[0].diffuseColor", 1.3f, 1.3f, 1.3f);
	// NO specular - matte surfaces only
	m_pShaderManager->setVec3Value("lightSources[0].specularColor", 0.0f, 0.0f, 0.0f);
	// Medium focal strength for balanced distribution
	m_pShaderManager->setFloatValue("lightSources[0].focalStrength", 24.0f);
	// NO specular highlights - matte finish
	m_pShaderManager->setFloatValue("lightSources[0].specularIntensity", 0.0f);

	// Light Source 2 - Very subtle fill light
	// Minimal contribution to prevent harsh shadows
	m_pShaderManager->setVec3Value("lightSources[1].position", 6.0f, 5.0f, 3.0f);
	// Neutral gray ambient fill
	m_pShaderManager->setVec3Value("lightSources[1].ambientColor", 0.08f, 0.08f, 0.08f);
	// Soft WHITE diffuse for fill
	m_pShaderManager->setVec3Value("lightSources[1].diffuseColor", 0.4f, 0.4f, 0.4f);
	// NO specular
	m_pShaderManager->setVec3Value("lightSources[1].specularColor", 0.0f, 0.0f, 0.0f);
	// Lower focal for soft fill
	m_pShaderManager->setFloatValue("lightSources[1].focalStrength", 12.0f);
	// NO specular highlights
	m_pShaderManager->setFloatValue("lightSources[1].specularIntensity", 0.0f);

}

/***********************************************************
 *  PrepareScene()
 *
 *  This method is used for preparing the 3D scene by loading
 *  the shapes, textures in memory to support the 3D scene 
 *  rendering
 ***********************************************************/
void SceneManager::PrepareScene()
{
	// define the materials for objects in the scene
	DefineObjectMaterials();
	// add and define the light sources for the scene
	SetupSceneLights();

	// only one instance of a particular mesh needs to be
	// loaded in memory no matter how many times it is drawn
	// in the rendered 3D scene - the following code loads
	// the basic 3D meshes into the graphics pipeline buffers

	m_basicMeshes->LoadBoxMesh();
	m_basicMeshes->LoadPlaneMesh();
	m_basicMeshes->LoadCylinderMesh();
	m_basicMeshes->LoadConeMesh();
	m_basicMeshes->LoadSphereMesh();
}

/***********************************************************
 *  RenderScene()
 *
 *  This method is used for rendering the 3D scene by 
 *  transforming and drawing the basic 3D shapes
 ***********************************************************/
void SceneManager::RenderScene()
{
	// declare the variables for the transformations
	glm::vec3 scaleXYZ;
	float XrotationDegrees = 0.0f;
	float YrotationDegrees = 0.0f;
	float ZrotationDegrees = 0.0f;
	glm::vec3 positionXYZ;

	/*** Set needed transformations before drawing the basic mesh.  ***/
	/*** This same ordering of code should be used for transforming ***/
	/*** and drawing all the basic 3D shapes.						***/
	/******************************************************************/
	// GROUND PLANE (horizontal, foreground) - PINK surface
	scaleXYZ = glm::vec3(20.0f, 1.0f, 10.0f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 0.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);

	// set the active color values in the shader (RGBA)
	SetShaderColor(1, 1, 1, 1);
	// Apply PINK material - ground plane has inherent pink surface color
	SetShaderMaterial("pink");

	// draw the mesh with transformation values - this plane is used for the ground
	m_basicMeshes->DrawPlaneMesh();
	/****************************************************************/

	/*** Set needed transformations before drawing the basic mesh.  ***/
	/*** This same ordering of code should be used for transforming ***/
	/*** and drawing all the basic 3D shapes.						***/
	/******************************************************************/
	// BACK PLANE (vertical, background) - BLACK backdrop behind scene
	scaleXYZ = glm::vec3(20.0f, 1.0f, 15.0f);

	// Rotate 90 degrees on X axis to make it vertical (stand up the plane)
	XrotationDegrees = 90.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 0.0f;

	// Position it behind the scene at Z=-5 (negative Z is behind)
	positionXYZ = glm::vec3(0.0f, 7.5f, -5.0f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);

	// set the active color values in the shader (RGBA)
	SetShaderColor(1, 1, 1, 1);
	// Apply BLACK material - back plane is dark backdrop
	SetShaderMaterial("black");

	// draw the back plane mesh
	m_basicMeshes->DrawPlaneMesh();
	/****************************************************************/

	/*** Set needed transformations before drawing the basic mesh.  ***/
	/*** This same ordering of code should be used for transforming ***/
	/*** and drawing all the basic 3D shapes.						***/
	/******************************************************************/
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(0.9f, 2.8f, 0.9f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 90.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = -15.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(0.0f, 0.9f, 0.4f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);

	// set the active color values in the shader (RGBA)
	SetShaderColor(1, 1, 1, 1);
	// Apply white material - pink tones come from ambient environment lighting
	SetShaderMaterial("white");

	m_basicMeshes->DrawCylinderMesh();
	/****************************************************************/

	/*** Set needed transformations before drawing the basic mesh.  ***/
	/*** This same ordering of code should be used for transforming ***/
	/*** and drawing all the basic 3D shapes.						***/
	/******************************************************************/
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(0.5f, 6.0f, 0.5f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 0.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 15.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(0.0f, 2.3f, 2.0f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);

	// set the active color values in the shader (RGBA)
	SetShaderColor(1, 1, 1, 1);
	// Apply white material - pink tones come from ambient environment lighting
	SetShaderMaterial("white");

	m_basicMeshes->DrawBoxMesh();
	/****************************************************************/

	/*** Set needed transformations before drawing the basic mesh.  ***/
	/*** This same ordering of code should be used for transforming ***/
	/*** and drawing all the basic 3D shapes.						***/
	/******************************************************************/
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(1.7f, 1.5f, 1.5f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 0.0f;
	YrotationDegrees = 40.0f;
	ZrotationDegrees = 8.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(3.3f, 3.85f, 2.19f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);

	// set the active color values in the shader (RGBA)
	SetShaderColor(1, 1, 1, 1);
	// Apply white material - pink tones come from ambient environment lighting
	SetShaderMaterial("white");

	m_basicMeshes->DrawBoxMesh();
	/****************************************************************/

	/*** Set needed transformations before drawing the basic mesh.  ***/
	/*** This same ordering of code should be used for transforming ***/
	/*** and drawing all the basic 3D shapes.						***/
	/******************************************************************/
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(1.0f, 1.0f, 1.0f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 0.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 0.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(3.2f, 5.6f, 2.5f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);

	// set the active color values in the shader (RGBA)
	SetShaderColor(1, 1, 1, 1);
	// Apply white material - pink tones come from ambient environment lighting
	SetShaderMaterial("white");

	m_basicMeshes->DrawSphereMesh();
	/****************************************************************/

	/*** Set needed transformations before drawing the basic mesh.  ***/
	/*** This same ordering of code should be used for transforming ***/
	/*** and drawing all the basic 3D shapes.						***/
	/******************************************************************/
	// set the XYZ scale for the mesh
	scaleXYZ = glm::vec3(1.2f, 4.0f, 1.2f);

	// set the XYZ rotation for the mesh
	XrotationDegrees = 0.0f;
	YrotationDegrees = 0.0f;
	ZrotationDegrees = 5.0f;

	// set the XYZ position for the mesh
	positionXYZ = glm::vec3(-3.3f, 2.50f, 2.0f);

	// set the transformations into memory to be used on the drawn meshes
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);

	// set the active color values in the shader (RGBA)
	SetShaderColor(1, 1, 1, 1);
	// Apply white material - pink tones come from ambient environment lighting
	SetShaderMaterial("white");

	m_basicMeshes->DrawConeMesh();
	/****************************************************************/
}



