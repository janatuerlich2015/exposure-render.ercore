/*
	Copyright (c) 2011, T. Kroes <t.kroes@tudelft.nl>
	All rights reserved.

	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

	- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
	- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
	- Neither the name of the TU Delft nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
	
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "erlight.h"
#include "exception.h"

namespace ExposureRender
{

class Light
{
public:
	HOST Light() :
		ID(),
		Visible(),
		TextureID(-1),
		Multiplier(0.0f),
		EmissionUnit(Enums::Power)
	{
	}

	HOST Light(const ErLight& Other)
	{
		*this = Other;
	}

	HOST Light& operator = (const ErLight& Other)
	{
		this->ID			= Other.ID;
		this->Visible		= Other.Visible;
		this->Shape			= Other.Shape;
		
		if (Other.TextureID >= 0)
		{
			if (gTexturesHashMap.find(Other.TextureID) != gTexturesHashMap.end())
				this->TextureID = gTexturesHashMap[Other.TextureID];
			else
				throw(Exception(Enums::Fatal, "Texture not found!"));
		}

		this->Multiplier	= Other.Multiplier;
		this->EmissionUnit	= Other.EmissionUnit;

		this->Shape.Update();

		return *this;
	}

	int						ID;
	bool					Visible;
	Shape					Shape;
	int						TextureID;
	float					Multiplier;
	Enums::EmissionUnit		EmissionUnit;
};

}
