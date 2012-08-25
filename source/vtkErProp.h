/*
*	@file
*	@author  Thomas Kroes <t.kroes at tudelft.nl>
*	@version 1.0
*	
*	@section LICENSE
*	
*	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
*	
*	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
*	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
*	Neither the name of the TU Delft nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
*
*	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "vtkErShape.h"

#include <vtkDataObject.h>

class vtkErProp;

class vtkErObjectData : public vtkDataObject, public vtkHostBindableProp
{
public:
	static vtkErObjectData* New();
	vtkTypeRevisionMacro(vtkErObjectData, vtkDataObject);
	
protected:
	vtkErObjectData() {};
	virtual ~vtkErObjectData() {};
	
	vtkErProp* Object;

private:
	vtkErObjectData(const vtkErObjectData& Other);		// Not implemented.
    void operator = (const vtkErObjectData& Other);		// Not implemented.

	friend class vtkErProp;
	friend class vtkErTracer;
};

class VTK_ER_EXPORT vtkErProp : public vtkErShape
{
public:
	static vtkErProp* New();
	vtkTypeRevisionMacro(vtkErProp, vtkErShape);

	enum Ports
	{
		DiffuseTexturePort = 0,
		SpecularTexturePort,
		GlossinessTexturePort,
		EmissionTexturePort,
		ClippingTexturePort
	};

	virtual int ProcessRequest(vtkInformation* Request, vtkInformationVector** InputVector, vtkInformationVector* OutputVector);

	vtkGetMacro(Name, vtkStdString);
	vtkSetMacro(Name, vtkStdString);

	vtkGetMacro(Enabled, bool);
	vtkSetMacro(Enabled, bool);

	vtkGetMacro(Visible, bool);
	vtkSetMacro(Visible, bool);

	vtkGetMacro(Emitter, bool);
	vtkSetMacro(Emitter, bool);

	vtkGetMacro(Multiplier, float);
	vtkSetMacro(Multiplier, float);

	vtkGetMacro(EmissionUnit, Enums::EmissionUnit);
	vtkSetMacro(EmissionUnit, Enums::EmissionUnit);

	vtkGetMacro(Clip, bool);
	vtkSetMacro(Clip, bool);

protected:
	vtkErProp();
	virtual ~vtkErProp();

	virtual int FillInputPortInformation(int Port, vtkInformation* Info);
	virtual int FillOutputPortInformation(int Port, vtkInformation* Info);

	virtual int RequestDataObject(vtkInformation* vtkNotUsed(Request), vtkInformationVector** vtkNotUsed(InputVector), vtkInformationVector* OutputVector);
	virtual int RequestInformation(vtkInformation* Request, vtkInformationVector** InputVector, vtkInformationVector* OutputVector);
	virtual int RequestData(vtkInformation* Request, vtkInformationVector** InputVector, vtkInformationVector* OutputVector);
	virtual int RequestUpdateExtent(vtkInformation* vtkNotUsed(Request), vtkInformationVector** InputVector, vtkInformationVector* vtkNotUsed(OutputVector));

private:
	vtkErProp(const vtkErProp& Other);			// Not implemented
    void operator = (const vtkErProp& Other);	// Not implemented

	vtkStdString			Name;
	bool					Enabled;
	bool					Visible;
	bool					Emitter;
	float					Multiplier;
	Enums::EmissionUnit		EmissionUnit;
	bool					Clip;
};