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

#include "macros.cuh"
#include "textures.h"
#include "shader.h"

namespace ExposureRender
{

KERNEL void KrnlSampleBrdf(int NoSamples)
{
	KERNEL_2D(gpTracer->FrameBuffer.Resolution[0], gpTracer->FrameBuffer.Resolution[1])

	if (IDk >= NoSamples)
		return;

	// Get sample ID
	int& SampleID = gpTracer->FrameBuffer.IDs(IDx, IDy);

	if (SampleID < 0)
		return;

	// Get sample
	Sample& Sample = gpTracer->FrameBuffer.Samples[SampleID];
	
	// Get random number generator
	RNG RNG(&gpTracer->FrameBuffer.RandomSeeds1(Sample.UV[0], Sample.UV[1]), &gpTracer->FrameBuffer.RandomSeeds2(Sample.UV[0], Sample.UV[1]));

	Shader Shader;

	GetShader(Sample.Intersection, Shader, RNG);

	float ShaderPdf = 0.0f;

	Ray R;
	
	R.O		= Sample.Intersection.P;
	R.MinT	= gStepFactorShadow;
	R.MaxT	= 1000.0f;

	const ColorXYZf F = Shader.SampleF(Sample.Intersection.Wo, R.D, ShaderPdf, RNG);

	if (F.IsBlack() || ShaderPdf <= 0.0f)
		return;
	
	Intersection Int;

	ColorXYZAf& FrameEstimate = gpTracer->FrameBuffer.FrameEstimate(Sample.UV[0], Sample.UV[1]);

	if (Intersect(R, RNG, Int, Enums::Light))
	{
		switch (Int.ScatterType)
		{
			case Enums::Light:
			{
				if (Int.ID == Sample.LightID)
				{
					Object& Light = gpObjects[Int.ID];

					ColorXYZf Li = Light.Multiplier * EvaluateTexture(Light.EmissionTextureID, Int.UV);

					if (Light.EmissionUnit == Enums::Power)
						Li /= Light.Shape.Area;

					const float LightPdf = DistanceSquared(Int.P, Sample.Intersection.P) / (AbsDot(-R.D, Int.N) * Light.Shape.Area);

					const float Weight = PowerHeuristic(1, ShaderPdf, 1, LightPdf);

					ColorXYZf Ld;

					if (Shader.Type == Enums::Brdf)
						Ld = F * Li * (AbsDot(R.D, Sample.Intersection.N) * Weight / ShaderPdf);
					else
						Ld = F * ((Li * Weight) / ShaderPdf);

					Ld *= (float)gpTracer->LightIDs.Count;
					
					R.O		= Int.P;
					R.D		= Normalize(Sample.Intersection.P - R.O);
					R.MinT	= RAY_EPS;
					R.MaxT	= (Sample.Intersection.P - R.O).Length();

					if (!Intersects(R, RNG))
					{
						FrameEstimate[0] += Ld[0];
						FrameEstimate[1] += Ld[1];
						FrameEstimate[2] += Ld[2];
					}
				}

				SampleID = -1;

				break;
			}

			case Enums::Object:
			case Enums::Volume:
			{
				Sample.Intersection = Int;

				break;
			}
		}
	}
	else
	{
		SampleID = -1;
	}
}

void SampleShader(Tracer& Tracer, Statistics& Statistics, int Bounce, int NoSamples)
{
	LAUNCH_DIMENSIONS(Tracer.FrameBuffer.Resolution[0], Tracer.FrameBuffer.Resolution[1], 1, BLOCK_W, BLOCK_H, 1)

	char Message[MAX_CHAR_SIZE];

	sprintf_s(Message, MAX_CHAR_SIZE, "Sample shader (%d bounces)", Bounce);

	LAUNCH_CUDA_KERNEL_TIMED((KrnlSampleBrdf<<<GridDim, BlockDim>>>(NoSamples)), Message); 
}

}