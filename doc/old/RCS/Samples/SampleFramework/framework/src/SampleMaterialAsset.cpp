/*
 * Copyright 2008-2012 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.  Users and possessors of this source code
 * are hereby granted a nonexclusive, royalty-free license to use this code
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 *
 * U.S. Government End Users.   This source code is a "commercial item" as
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer  software"  and "commercial computer software
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the
 * source code with only those rights set forth herein.
 *
 * Any use of this source code in individual and commercial software must
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */
#include <SampleMaterialAsset.h>

#include <Renderer.h>
#include <RendererMaterial.h>
#include <RendererMaterialDesc.h>
#include <RendererMaterialInstance.h>

#include <SampleAssetManager.h>
#include <SampleTextureAsset.h>

#include "SampleXml.h"
#include <ctype.h>

using namespace SampleFramework;

static void readFloats(const char *str, float *floats, unsigned int numFloats)
{
	PxU32 fcount = 0;
	while(*str && !((*str>='0'&&*str<='9') || *str=='.')) str++;
	for(PxU32 i=0; i<numFloats; i++)
	{
		if(*str)
		{
			floats[i] = (float)atof(str);
			while(*str &&  ((*str>='0'&&*str<='9') || *str=='.')) str++;
			while(*str && !((*str>='0'&&*str<='9') || *str=='.')) str++;
			fcount++;
		}
	}
	PX_ASSERT(fcount==numFloats);
}

SampleMaterialAsset::SampleMaterialAsset(SampleAssetManager &assetManager, FAST_XML::xml_node &xmlroot, const char *path) :
SampleAsset(ASSET_MATERIAL, path),
	m_assetManager(assetManager)
{

	std::vector<const char*> mVertexShaderPaths;
	//m_material         = 0;
	//m_materialInstance = 0;

	SampleRenderer::Renderer &renderer = assetManager.getRenderer();

	SampleRenderer::RendererMaterialDesc matdesc;
	const char *materialTypeName = xmlroot.getXMLAttribute("type");
	if(materialTypeName && !strcmp(materialTypeName, "lit"))
	{
		matdesc.type = SampleRenderer::RendererMaterial::TYPE_LIT;
	}
	else if(materialTypeName && !strcmp(materialTypeName, "unlit"))
	{
		matdesc.type = SampleRenderer::RendererMaterial::TYPE_UNLIT;
	}
	for(FAST_XML::xml_node *child=xmlroot.first_node(); child; child=child->next_sibling())
	{
		const char *nodeName  = child->name();
		const char *nodeValue = child->value();
		const char *name      = child->getXMLAttribute("name");
		if(nodeName && nodeValue)
		{
			while(isspace(*nodeValue)) nodeValue++; // skip leading spaces.
			if(!strcmp(nodeName, "shader"))
			{
				if(name && !strcmp(name, "vertex"))
				{
					//matdesc.vertexShaderPath = nodeValue;
					mVertexShaderPaths.push_back(nodeValue);
				}
				else if(name && !strcmp(name, "fragment"))
				{
					matdesc.fragmentShaderPath = nodeValue;
				}
			}
			else if(!strcmp(nodeName, "alphaTestFunc"))
			{
				if(     !strcmp(nodeValue, "EQUAL"))         matdesc.alphaTestFunc = SampleRenderer::RendererMaterial::ALPHA_TEST_EQUAL;
				else if(!strcmp(nodeValue, "NOT_EQUAL"))     matdesc.alphaTestFunc = SampleRenderer::RendererMaterial::ALPHA_TEST_NOT_EQUAL;
				else if(!strcmp(nodeValue, "LESS"))          matdesc.alphaTestFunc = SampleRenderer::RendererMaterial::ALPHA_TEST_LESS;
				else if(!strcmp(nodeValue, "LESS_EQUAL"))    matdesc.alphaTestFunc = SampleRenderer::RendererMaterial::ALPHA_TEST_LESS_EQUAL;
				else if(!strcmp(nodeValue, "GREATER"))       matdesc.alphaTestFunc = SampleRenderer::RendererMaterial::ALPHA_TEST_GREATER;
				else if(!strcmp(nodeValue, "GREATER_EQUAL")) matdesc.alphaTestFunc = SampleRenderer::RendererMaterial::ALPHA_TEST_GREATER_EQUAL;
				else PX_ASSERT(0); // Unknown alpha test func!
			}
			else if(!strcmp(nodeName, "alphaTestRef"))
			{
				matdesc.alphaTestRef = PxClamp((float)atof(nodeValue), 0.0f, 1.0f);
			}
			else if(!strcmp(nodeName, "blending") && strstr(nodeValue, "true"))
			{
				matdesc.blending = true;
				// HACK/TODO: read these values from disk!
				matdesc.srcBlendFunc = SampleRenderer::RendererMaterial::BLEND_SRC_ALPHA;
				matdesc.dstBlendFunc = SampleRenderer::RendererMaterial::BLEND_ONE_MINUS_SRC_ALPHA;
			}
		}
	}

	for (size_t materialIndex = 0; materialIndex < mVertexShaderPaths.size(); materialIndex++)
	{
		MaterialStruct materialStruct;

		matdesc.vertexShaderPath = mVertexShaderPaths[materialIndex];
		materialStruct.m_material = NULL;
		materialStruct.m_materialInstance = NULL;
		materialStruct.m_maxBones = 0;
		if (strstr(mVertexShaderPaths[materialIndex], "skeletalmesh") != NULL)
			materialStruct.m_maxBones = RENDERER_MAX_BONES;

		materialStruct.m_material = renderer.createMaterial(matdesc);
		PX_ASSERT(materialStruct.m_material);
		if(materialStruct.m_material)
		{
			FAST_XML::xml_node *varsnode = xmlroot.first_node("variables");
			if(varsnode)
			{
				materialStruct.m_materialInstance = new SampleRenderer::RendererMaterialInstance(*materialStruct.m_material);
				for(FAST_XML::xml_node *child=varsnode->first_node(); child; child=child->next_sibling())
				{
					const char *nodename = child->name();
					const char *varname  = child->getXMLAttribute("name");
					const char *value    = child->value();

					if(!strcmp(nodename, "float"))
					{
						float f = (float)atof(value);
						const SampleRenderer::RendererMaterial::Variable *var = materialStruct.m_materialInstance->findVariable(varname, SampleRenderer::RendererMaterial::VARIABLE_FLOAT);
						PX_ASSERT(var);
						if(var) materialStruct.m_materialInstance->writeData(*var, &f);
					}
					else if(!strcmp(nodename, "float2"))
					{
						float f[2];
						readFloats(value, f, 2);
						const SampleRenderer::RendererMaterial::Variable *var = materialStruct.m_materialInstance->findVariable(varname, SampleRenderer::RendererMaterial::VARIABLE_FLOAT2);
						PX_ASSERT(var);
						if(var) materialStruct.m_materialInstance->writeData(*var, f);
					}
					else if(!strcmp(nodename, "float3"))
					{
						float f[3];
						readFloats(value, f, 3);
						const SampleRenderer::RendererMaterial::Variable *var = materialStruct.m_materialInstance->findVariable(varname, SampleRenderer::RendererMaterial::VARIABLE_FLOAT3);
						PX_ASSERT(var);
						if(var) materialStruct.m_materialInstance->writeData(*var, f);
					}
					else if(!strcmp(nodename, "float4"))
					{
						float f[4];
						readFloats(value, f, 4);
						const SampleRenderer::RendererMaterial::Variable *var = materialStruct.m_materialInstance->findVariable(varname, SampleRenderer::RendererMaterial::VARIABLE_FLOAT4);
						PX_ASSERT(var);
						if(var) materialStruct.m_materialInstance->writeData(*var, f);
					}
					else if(!strcmp(nodename, "sampler2D"))
					{
						SampleTextureAsset *textureAsset = static_cast<SampleTextureAsset*>(assetManager.getAsset(value, ASSET_TEXTURE));
						PX_ASSERT(textureAsset);
						if(textureAsset)
						{
							m_assets.push_back(textureAsset);
							const SampleRenderer::RendererMaterial::Variable *var = materialStruct.m_materialInstance->findVariable(varname, SampleRenderer::RendererMaterial::VARIABLE_SAMPLER2D);
							PX_ASSERT(var);
							if(var)
							{
								SampleRenderer::RendererTexture2D *texture = textureAsset->getTexture();
								materialStruct.m_materialInstance->writeData(*var, &texture);
							}
						}
					}

				}
			}

			m_vertexShaders.push_back(materialStruct);
		}
	}
}

SampleMaterialAsset::~SampleMaterialAsset(void)
{
	PxU32 numAssets = (PxU32)m_assets.size();
	for(PxU32 i=0; i<numAssets; i++)
	{
		m_assetManager.returnAsset(*m_assets[i]);
	}
	for (size_t index = 0; index < m_vertexShaders.size(); index++)
	{
		if(m_vertexShaders[index].m_materialInstance) delete m_vertexShaders[index].m_materialInstance;
		if(m_vertexShaders[index].m_material)         m_vertexShaders[index].m_material->release();
	}
}

size_t SampleMaterialAsset::getNumVertexShaders() const
{
	return m_vertexShaders.size();
}

SampleRenderer::RendererMaterial *SampleMaterialAsset::getMaterial(size_t vertexShaderIndex)
{
	return m_vertexShaders[vertexShaderIndex].m_material;
}

SampleRenderer::RendererMaterialInstance *SampleMaterialAsset::getMaterialInstance(size_t vertexShaderIndex)
{
	return m_vertexShaders[vertexShaderIndex].m_materialInstance;
}

bool SampleMaterialAsset::isOk(void) const
{
	return !m_vertexShaders.empty();
}

unsigned int SampleMaterialAsset::getMaxBones(size_t vertexShaderIndex) const
{
	return m_vertexShaders[vertexShaderIndex].m_maxBones;
}
