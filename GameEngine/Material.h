//#ifndef MATERIAL_H
//#define MATERIAL_H
#pragma once

#include "StlOptions.h"
#include "Color.h"
#include <string>
#include "StlOptions.h"
#include <vector>


/**
* A material texture reference is a reference to a particular texture by name with an indiccation of
* the type of texture that is represented: ambient. specular, bump map, etc.
* This is used by a material to reference the textures which are stored in the image manager.
* @author R. N. Robson
*/
class MaterialTextureReference
{
public:
	/** MaterialTextureType represents the different types of textures which can be associated with a material */
	enum MaterialTextureType {
		TEX_UNKNOWN,
		TEX_AMBIENT,
		TEX_DIFFUSE,
		TEX_SPECULAR,
		TEX_EMISSIVE,
		TEX_ALPHA,
		TEX_BUMP_MAP,
		TEX_NORMAL_MAP
	};

	/**
	* This determines how textures can be combinned when a material consists of mmore than one texture.
	* Thhe operations are applied to combinne a nnew texture with the results of the combination of the
	* previous textures in the texture stack.
	*/
	enum TextureCombOperation {
		TEX_OP_NONE = 0,		// a null operation
		TEX_OP_REPLACE,			// replaces all textures beneath it so this is the only texture you see
		TEX_OP_MULTIPLY,		// multiply the pixels in one texture by the pixles in the second
		TEX_OP_ADD,				// add pixels together t= t1 + t2
		TEX_OP_SUBTRACT,		// subtract pixels t = t1 - t2
		TEX_OP_DIVIDE,			// divide pixels t = t1 / t2
		TEX_OP_SMOOTH_ADD,		// t = (t1 + t2) - (t1 * t2)
		TEX_OP_SIGNED_ADD		// t = t1 + (t2 - 0.5)
	};
private:
	MaterialTextureType		texType;
	std::string				texName;
	TextureCombOperation	combOp;
public:
	/**
	* Default constructor that creates an empty reference
	*/
	MaterialTextureReference() :
		texType(TEX_UNKNOWN), texName(""), combOp(TEX_OP_NONE)
	{}

	/**
	* Constructor that is used most often to create a texture reference
	* @param name The name of the material being references
	* @param the type of the texture
	*/
	MaterialTextureReference(std::string name, MaterialTextureType type) :
		texType(type), texName(name), combOp(TEX_OP_NONE)
	{}

	MaterialTextureReference(const MaterialTextureReference &other) :
		texType(other.texType), texName(other.texName), combOp(other.combOp)
	{}

	/**
	* Return the name of the texture.
	* @return the texture name
	*/
	std::string getName() const;

	/**
	* Return the type of the material
	* @return the material type
	*/
	MaterialTextureType getType() const;

	/**
	* Equality operator
	* @param t1 first texture ref
	* @param t2 second texture ref
	* @return true if the two texture references are equal
	*/
	friend bool operator==(const MaterialTextureReference &t1, const MaterialTextureReference &t2);

	/**
	* Inquality operator
	* @param t1 first texture ref
	* @param t2 second texture ref
	* @return true if the two texture references are not equal
	*/
	friend bool operator!=(const MaterialTextureReference &t1, const MaterialTextureReference &t2);

	/**
	* Assignment operator
	* @param other  texture ref to assign to this
	* @return a reference to this
	*/
	MaterialTextureReference& operator=(const MaterialTextureReference &other);

	/**
	* Insertion operator for MaterialTextureReference.
	* @paran os the stream in which to insert
	* @param mat the MaterialTextureReference to insert
	*/
	friend std::ostream& operator<<(std::ostream &os, const MaterialTextureReference &mat);

	/**
	* Return the operation used to combinne this texture with the other textures in the stack.
	* @return Thhe operation to combine this texture or TEX_OP_NONE if not applicable
	*/
	TextureCombOperation getCombinationOperation() const;

	/**
	* Convert MaterialTextureReference to a readable string
	* @returns a readable string
	*/
	std::string toString() const;
};


/**
* A material is a material which covers a mesh.  A material can consist of:
* <ul>
* <li> the ambient, diffuse, specular and emissive colors of the material
* <li> a coefficient for specular power
* <li> a list of textures that comprise the material
* </ul>
* There are different textures for different purposes.  There are textures which specify the per-pixel
* reflectance of ambient, diffuse, specular and emissive light as well as textures for bumpmaps and
* normal maps.  Not every material will have all of the possible textures and attributes.  In fact, it
* would be surprising if any one material did have all attributes and textures.  This is designed to
* handle many differrent types of materials that have different combinations of attributes.
* @author R. N. Robson
*/
class Material
{

private:
	/** ambient reflectivity */
	Color		ambient;
	/** diffuse reflectivity */
	Color		diffuse;
	/** specular reflectivity */
	Color		specular;
	/** emissive reflectivity */
	Color		emissive;
	/** specular power */
	float		specPower;

	/** The name of this material used to reference it in resource managers */
	std::string	materialName;
	/** The list of texturess associated with this material */
	std::vector<MaterialTextureReference>	textureList;
	/** true if the material has an ambient texture */
	bool						ambientTexturePresent;
	/** True if the material has a diffuse texture */
	bool						diffuseTexturePresent;
	/** The name of the shader used to render this material */
	std::string					shaderName;
	/** This is true if a shader has been assigned to the material */
	bool						shaderPresent;
public:
	typedef  std::vector<MaterialTextureReference>::iterator TextureIterator;

	/**
	* Default constructor that gives a material with full white reflectance for all colours and no textures.
	*/
	Material() :
		ambient(Color::WHITE), diffuse(Color::WHITE), specular(Color::WHITE), emissive(Color::WHITE),
		specPower(0.5), ambientTexturePresent(false), diffuseTexturePresent(false), shaderPresent(false)
	{
	}

	/**
	* Normal constructor.
	* @param nm The name for the material
	* @param amb The ambient colour
	* @param dif The diffuse colour
	* @param spec The specular colour
	* @param emis The emissive colour
	* @param specP The specular power
	*/
	Material(const std::string& nm,
		const Color &amb,
		const Color &dif,
		const Color &spec,
		const Color &emis,
		float specP) :
		materialName(nm), ambient(amb), diffuse(dif), specular(spec), emissive(emis), specPower(specP),
		ambientTexturePresent(false), diffuseTexturePresent(false), shaderPresent(false)
	{}

	/**
	* Copy constructor.
	* @param mat The material to assign to this
	*/
	Material(const Material &mat) :
		ambient(mat.ambient), diffuse(mat.diffuse), specular(mat.specular), emissive(mat.emissive),
		specPower(mat.specPower), ambientTexturePresent(mat.ambientTexturePresent), diffuseTexturePresent(mat.diffuseTexturePresent), shaderPresent(mat.shaderPresent),
		shaderName(mat.shaderName)
	{}

	/**
	* Set the name of the shader for this material.
	* @param name The name of the shader that is used in the resource manager
	*/
	void setShaderName(const std::string& name);

	/**
	* Get the name of the shader for this material, if there is one.
	* @return The name of the shader used to identify it in the resource managers or a zero-length string if there is no shader.
	*/
	std::string getShaderName() const;

	/**
	* Returns an iterator to the first texture in the material.
	* @return an iterator over the textures
	*/
	TextureIterator textureBegin();

	/**
	* Returns an iterator to the past-the-end texture in the material.
	* @return an iterator over the textures
	*/
	TextureIterator textureEnd();

	/**
	* Return the number of textures in the material
	* @return the number of textures in the material
	*/
	int getNumTextures();

	/**
	* Assignment operator.
	* @param mat The material to assign to this
	* @return a reference to this
	*/
	Material& operator=(const Material &mat);

	/**
	* Equality operator
	* @param m1 first material to compare
	* @param m2 second material to compare
	* @return true if m1 is equal to m2
	*/
	friend bool operator==(const Material &m1, const Material &m2);

	/**
	* Inequality operator
	* @param m1 first material to compare
	* @param m2 second material to compare
	* @return true if m1 is not equal to m2
	*/
	friend bool operator!=(const Material &m1, const Material &m2);

	/**
	* Insertion operator for Material.
	* @paran os the stream in which to insert
	* @param mat the material to insert
	*/
	friend std::ostream& operator<<(std::ostream &os, const Material &mat);

	/**
	* Convert Material to a readable string
	* @returns a readable string
	*/
	std::string toString() const;

	/**
	* Set the ambient reflectance for the material.
	* @param v the ambient colour value
	*/
	void setAmbient(const Color &v);

	/**
	* Set the diffuse reflectance for the material.
	* @param v the diffuse colour value
	*/
	void setDiffuse(const Color &v);

	/**
	* Set the specular reflectance for the material.
	* @param v the specular colour value
	*/
	void setSpecular(const Color &v);

	/**
	* Set the emissive reflectance for the material.
	* @param v the emissive colour value
	*/
	void setEmissive(const Color &v);

	/**
	* Return the ambient reflectance for the material.
	* @return the ambient colour value
	*/
	Color getAmbient() const;

	/**
	* Return the diffuse reflectance for the material.
	* @return the diffuse colour value
	*/
	Color getDiffuse() const;

	/**
	* Return the specular reflectance for the material.
	* @return the specular colour value
	*/
	Color getSpecular() const;

	/**
	* Return the emissive reflectance for the material.
	* @return the emissive colour value
	*/
	Color getEmissive() const;

	/**
	* Set the specular power for the material.
	* @param v the specular power
	*/
	void setSpecPower(float v);

	/**
	* Return the specular power for the material.
	* @return the specular power
	*/
	float getSpecPower() const;

	/**
	* Return the name of the first texture of the indicated type.  If there are multiple tecxtures of the same type,
	* only the first one is returned.  If there is no texture with the indicated type, then an empty string is returned.
	* @return the name of the texture or an empty string if there is no such texture.
	*/
	std::string getTextureOfType(const MaterialTextureReference::MaterialTextureType typ) const;

	/**
	* Creates a new reference to a texture of the indicated type and adds it to the list of textures for the material.
	* @param tex The name of the texture to be added
	*/
	void setAmbientTexture(const std::string& tex);

	/**
	* Return the name of the first texture of the indicated type.  If there are multiple tecxtures of the same type,
	* only the first one is returned.  If there is no texture with the indicated type, then an empty string is returned.
	* @return the name of the texture or an empty string if there is no such texture.
	*/
	std::string getAmbientTexture() const;

	/**
	* Creates a new reference to a texture of the indicated type and adds it to the list of textures for the material.
	* @param tex The name of the texture to be added
	*/
	void setDiffuseTexture(const std::string& tex);

	/**
	* Return the name of the first texture of the indicated type.  If there are multiple tecxtures of the same type,
	* only the first one is returned.  If there is no texture with the indicated type, then an empty string is returned.
	* @return the name of the texture or an empty string if there is no such texture.
	*/
	std::string getDiffuseTexture() const;

	/**
	* Creates a new reference to a texture of the indicated type and adds it to the list of textures for the material.
	* @param tex The name of the texture to be added
	*/
	void setSpecularTexture(const std::string& tex);

	/**
	* Return the name of the first texture of the indicated type.  If there are multiple tecxtures of the same type,
	* only the first one is returned.  If there is no texture with the indicated type, then an empty string is returned.
	* @return the name of the texture or an empty string if there is no such texture.
	*/
	std::string getSpecularTexture() const;

	/**
	* Creates a new reference to a texture of the indicated type and adds it to the list of textures for the material.
	* @param tex The name of the texture to be added
	*/
	void setEmissiveTexture(const std::string& tex);

	/**
	* Return the name of the first texture of the indicated type.  If there are multiple tecxtures of the same type,
	* only the first one is returned.  If there is no texture with the indicated type, then an empty string is returned.
	* @return the name of the texture or an empty string if there is no such texture.
	*/
	std::string getEmissiveTexture() const;

	/**
	* Creates a new reference to a texture of the indicated type and adds it to the list of textures for the material.
	* @param tex The name of the texture to be added
	*/
	void setAlphaTexture(const std::string& tex);

	/**
	* Return the name of the first texture of the indicated type.  If there are multiple tecxtures of the same type,
	* only the first one is returned.  If there is no texture with the indicated type, then an empty string is returned.
	* @return the name of the texture or an empty string if there is no such texture.
	*/
	std::string getAlphaTexture() const;

	/**
	* Creates a new reference to a texture of the indicated type and adds it to the list of textures for the material.
	* @param tex The name of the texture to be added
	*/
	void setBumpMap(const std::string& tex);

	/**
	* Return the name of the first texture of the indicated type.  If there are multiple tecxtures of the same type,
	* only the first one is returned.  If there is no texture with the indicated type, then an empty string is returned.
	* @return the name of the texture or an empty string if there is no such texture.
	*/
	std::string getBumpMap() const;

	/**
	* Set the name of this material.  This simply sets the name in this object and does nothing to
	* change the name in the resource manager or elsewhere where the material might be stored.
	* @parm nm the new name for the material
	*/
	void setMaterialName(const std::string& nm);

	/**
	* Return the name of this material.
	* @return the name of the material
	*/
	std::string getMaterialName() const;

	/**
	* Reset all material colours to white and remove all textures.
	*/
	void reset();

	/**
	* Return true if this material has any textures of any type.
	* @return true if this material has any textures
	*/
	bool hasTextures();

	/**
	* Return true if this material has an ambient texture.
	* @return true if this material has ambient texture
	*/
	bool hasAmbientTexture();

	/**
	* Return true if this material has an diffuse texture.
	* @return true if this material has diffuse texture
	*/
	bool hasDiffuseTexture();

};

//#endif