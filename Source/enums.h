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

namespace ExposureRender
{

namespace Enums
{
	enum MemoryType
	{
		Host,
		Device
	};

	enum MemoryUnit
	{
		KiloByte,
		MegaByte,
		GigaByte
	};

	enum ProceduralType
	{
		Uniform = 0,
		Checker,
		Gradient
	};

	enum TextureType
	{
		Procedural = 0,
		Bitmap
	};

	enum ShapeType
	{
		Plane = 0,
		Disk,
		Ring,
		Box,
		Sphere,
		Cylinder,
		Cone
	};

	enum ShadingMode
	{
		BrdfOnly = 0,
		PhaseFunctionOnly,
		Hybrid,
		Modulation
	};

	enum GradientMode
	{
		ForwardDifferences = 0,
		CentralDifferences,
		Filtered,
	};

	enum ExceptionLevel
	{
		Info = 0,
		Warning,
		Error,
		Fatal
	};

	enum EmissionUnit
	{
		Power = 0,
		Lux,
	};

	enum ScatterFunction
	{
		Brdf,
		PhaseFunction
	};

	enum ScatterType
	{
		Volume			= 0x001,
		Light			= 0x002,
		Object			= 0x004
	};

	enum AlignmentType
	{
		AxisAlign = 0,
		LookAt,
		Spherical,
		Manual
	};

	enum Axis
	{
		X = 0,
		Y,
		Z
	};

	enum FilterMode
	{
		NearestNeighbour = 0,
		Linear,
	};

	enum FocusMode
	{
		AutoFocus = 0,
		ManualFocus,
	};

	enum DeviceType
	{
		Cuda = 0,
		OpenCL,
	};

	enum AddressMode
	{
		Wrap = 0,
		Clamp,
		Mirror,
		Border
	};

	enum AcceleratorType
	{
		NoAcceleration = 0,
		Octree
	};

	enum ApertureShape
	{
		Circular = 0,
		Polygon
	};

	enum OverlapType
	{
		Complete = 0,
		Left,
		Right,
		Exact
	};

	enum GradientType
	{
		Ramp = 0,
		Radial
	};

	enum RenderMode
	{
		StandardRayCasting,
		StochasticRayCasting
	};
}

}
