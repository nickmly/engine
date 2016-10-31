#include "Material.h"
#include <sstream>

std::string MaterialTextureReference::getName() const
{
	return texName;
}

MaterialTextureReference::MaterialTextureType MaterialTextureReference::getType() const
{
	return texType;
}

MaterialTextureReference::TextureCombOperation MaterialTextureReference::getCombinationOperation() const
{
	return combOp;
}

bool operator==(const MaterialTextureReference &t1, const MaterialTextureReference &t2)
{
	return (&t1 == &t2) || (t1.texName == t2.texName && t1.texType == t2.texType && t1.combOp == t2.combOp);
}

bool operator!=(const MaterialTextureReference &t1, const MaterialTextureReference &t2)
{
	return !(t1 == t2);
}

MaterialTextureReference& MaterialTextureReference::operator=(const MaterialTextureReference &other)
{
	if (this != &other)
	{
		texName = other.texName;
		texType = other.texType;
		combOp = other.combOp;
	}
	return *this;
}

std::ostream& operator<<(std::ostream &os, const MaterialTextureReference &mat)
{
	os << mat.texName << ":";
	std::string typ = "";
	switch (mat.texType)
	{
	case MaterialTextureReference::MaterialTextureType::TEX_ALPHA:
		typ = "ALPHA";
		break;
	case MaterialTextureReference::MaterialTextureType::TEX_AMBIENT:
		typ = "AMBIENT";
		break;
	case MaterialTextureReference::MaterialTextureType::TEX_BUMP_MAP:
		typ = "BUMP_MAP";
		break;
	case MaterialTextureReference::MaterialTextureType::TEX_DIFFUSE:
		typ = "DIFFUSE";
		break;
	case MaterialTextureReference::MaterialTextureType::TEX_EMISSIVE:
		typ = "EMISSIVE";
		break;
	case MaterialTextureReference::MaterialTextureType::TEX_NORMAL_MAP:
		typ = "NORMAL_MAP";
		break;
	case MaterialTextureReference::MaterialTextureType::TEX_SPECULAR:
		typ = "SPECULAR";
		break;
	default:
		typ = "UNKNOWN";
		break;
	}
	os << typ;
	switch (mat.combOp)
	{
	case MaterialTextureReference::TextureCombOperation::TEX_OP_ADD:
		typ = "ADD";
		break;
	case MaterialTextureReference::TextureCombOperation::TEX_OP_DIVIDE:
		typ = "DIVIDE";
		break;
	case MaterialTextureReference::TextureCombOperation::TEX_OP_MULTIPLY:
		typ = "MULTIPLY";
		break;
	case MaterialTextureReference::TextureCombOperation::TEX_OP_NONE:
		typ = "NONE";
		break;
	case MaterialTextureReference::TextureCombOperation::TEX_OP_REPLACE:
		typ = "REPLACE";
		break;
	case MaterialTextureReference::TextureCombOperation::TEX_OP_SIGNED_ADD:
		typ = "SIGNED_ADD";
		break;
	case MaterialTextureReference::TextureCombOperation::TEX_OP_SMOOTH_ADD:
		typ = "SMOOTH_ADD";
		break;
	case MaterialTextureReference::TextureCombOperation::TEX_OP_SUBTRACT:
		typ = "SUBTRACT";
		break;
	default:
		typ = "UNKNOWN";
		break;
	}
	os << " (" << typ << ")";
	return os;
}

std::string MaterialTextureReference::toString() const
{
	std::stringstream ss;
	ss << *this;
	return ss.str();
}



std::ostream& operator<<(std::ostream &os, const Material &mat)
{
	os << "[(" << mat.materialName << ") " << mat.ambient << mat.diffuse << mat.specular << mat.emissive <<
		", " << mat.specPower << "]";
	if (mat.textureList.size() > 0)
	{
		os << std::endl << "{";
		for (int i = 0; i < mat.textureList.size(); i++)
		{
			os << mat.textureList[i] << std::endl;
		}
		os << "}";
	}
	return os;
}

std::string Material::toString() const
{
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

Material& Material::operator=(const Material &mat)
{
	if (this != &mat)
	{
		materialName = mat.materialName;
		ambient = mat.ambient;
		diffuse = mat.diffuse;
		specular = mat.specular;
		emissive = mat.emissive;
		specPower = mat.specPower;
		shaderName = mat.shaderName;
		shaderPresent = mat.shaderPresent;
		ambientTexturePresent = mat.ambientTexturePresent;
		diffuseTexturePresent = mat.diffuseTexturePresent;
		for (int i = 0; i < mat.textureList.size(); i++)
		{
			textureList.push_back(mat.textureList[i]);
		}
	}
	return *this;
}

void Material::reset()
{
	materialName = "";
	ambient = Color::WHITE;
	diffuse = Color::WHITE;
	specular = Color::WHITE;
	emissive = Color::WHITE;
	specPower = 0.5;
	textureList.clear();
	shaderName = std::string("");
}

bool operator==(const Material &m1, const Material &m2)
{
	bool result = m1.materialName == m2.materialName &&
		m1.ambient == m2.ambient &&
		m1.diffuse == m2.diffuse &&
		m1.specular == m2.specular &&
		m1.emissive == m2.emissive &&
		m1.specPower == m2.specPower &&
		m1.shaderName == m2.shaderName;
	// should we compare each of the textures?  Could be slow!
	return result;
}

void Material::setShaderName(const std::string& name)
{
	shaderName = name;
}


std::string Material::getShaderName() const
{
	return shaderName;
}

Material::TextureIterator Material::textureBegin()
{
	return textureList.begin();
}

Material::TextureIterator Material::textureEnd()
{
	return textureList.end();
}

int Material::getNumTextures()
{
	return textureList.size();
}

bool operator!=(const Material &m1, const Material &m2)
{
	return !(m1 == m2);
}

void Material::setAmbientTexture(const std::string& tex)
{
	textureList.push_back(MaterialTextureReference(tex, MaterialTextureReference::MaterialTextureType::TEX_AMBIENT));
	ambientTexturePresent = true;
}

std::string Material::getTextureOfType(const MaterialTextureReference::MaterialTextureType typ) const
{
	std::string result = "";
	std::vector<MaterialTextureReference>::const_iterator iter;
	for (iter = textureList.begin(); iter != textureList.end(); iter++)
	{
		if ((*iter).getType() == typ)
		{
			result = (*iter).getName();
			break;
		}
	}
	return result;
}

std::string Material::getAmbientTexture() const
{
	return getTextureOfType(MaterialTextureReference::MaterialTextureType::TEX_AMBIENT);
}

void Material::setDiffuseTexture(const std::string& tex)
{
	textureList.push_back(MaterialTextureReference(tex, MaterialTextureReference::MaterialTextureType::TEX_DIFFUSE));
	diffuseTexturePresent = true;
}

std::string Material::getDiffuseTexture() const
{
	return getTextureOfType(MaterialTextureReference::MaterialTextureType::TEX_DIFFUSE);
}

void Material::setSpecularTexture(const std::string& tex)
{
	textureList.push_back(MaterialTextureReference(tex, MaterialTextureReference::MaterialTextureType::TEX_SPECULAR));
}

std::string Material::getSpecularTexture() const
{
	return getTextureOfType(MaterialTextureReference::MaterialTextureType::TEX_SPECULAR);
}

void Material::setEmissiveTexture(const std::string& tex)
{
	textureList.push_back(MaterialTextureReference(tex, MaterialTextureReference::MaterialTextureType::TEX_EMISSIVE));
}

std::string Material::getEmissiveTexture() const
{
	return getTextureOfType(MaterialTextureReference::MaterialTextureType::TEX_ALPHA);
}

void Material::setAlphaTexture(const std::string& tex)
{
	textureList.push_back(MaterialTextureReference(tex, MaterialTextureReference::MaterialTextureType::TEX_SPECULAR));
}

std::string Material::getAlphaTexture() const
{
	return getTextureOfType(MaterialTextureReference::MaterialTextureType::TEX_ALPHA);
}

void Material::setBumpMap(const std::string& tex)
{
	textureList.push_back(MaterialTextureReference(tex, MaterialTextureReference::MaterialTextureType::TEX_BUMP_MAP));
}

std::string Material::getBumpMap() const
{
	return getTextureOfType(MaterialTextureReference::MaterialTextureType::TEX_BUMP_MAP);
}

void Material::setMaterialName(const std::string& nm)
{
	materialName = nm;
}

std::string Material::getMaterialName() const
{
	return materialName;
}

void Material::setAmbient(const Color &v)
{
	ambient = v;
}

void Material::setDiffuse(const Color &v)
{
	diffuse = v;
}

void Material::setSpecular(const Color &v)
{
	specular = v;
}

void Material::setEmissive(const Color &v)
{
	emissive = v;
}

Color Material::getAmbient() const
{
	return ambient;
}

Color Material::getDiffuse() const
{
	return diffuse;
}

Color Material::getSpecular() const
{
	return specular;
}

Color Material::getEmissive() const
{
	return emissive;
}

void Material::setSpecPower(float v)
{
	specPower = v;
}

float Material::getSpecPower() const
{
	return specPower;
}

bool Material::hasTextures()
{
	return textureList.size() > 0;
}

bool Material::hasAmbientTexture()
{
	return ambientTexturePresent;
}

bool Material::hasDiffuseTexture()
{
	return diffuseTexturePresent;
}

