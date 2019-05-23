#include "Signal.h"

#include <memory>
#include <cmath>

float Signal::Statistics::MeanF(const float* samples, const size_t nSamples)
{
	// prevent runtime error
	if (nSamples == 0 || samples == nullptr)
	{
		return 0.0f;
	}
	
	float sum = 0.0f;
	for (size_t i = 0; i < nSamples; ++i)
	{
		sum += samples[i];
	}
	return sum / static_cast<float>(nSamples);
}

double Signal::Statistics::MeanD(const double* samples, const size_t nSamples)
{
	// prevent runtime error
	if (nSamples == 0 || samples == nullptr)
	{
		return 0.0;
	}

	double sum = 0.0;
	for (size_t i = 0; i < nSamples; ++i)
	{
		sum += samples[i];
	}
	return sum / static_cast<double>(nSamples);
}

float Signal::Statistics::VarienceF(const float* samples, const size_t nSamples, const float mean)
{
	// prevent runtime error, need atleast 2 samples
	if (nSamples <= 1 || samples == nullptr)
	{
		return 0.0f;
	}

	float netVarience = 0.0f;
	for (size_t i = 0; i < nSamples; ++i)
	{
		netVarience += powf(samples[i] - mean, 2);
	}
	return netVarience / static_cast<float>(nSamples - 1);
}

double Signal::Statistics::VarienceD(const double* samples, const size_t nSamples, const double mean)
{
	// prevent runtime error, need atleast 2 samples
	if (nSamples <= 1 || samples == nullptr)
	{
		return 0.0;
	}

	double netVarience = 0.0;
	for (size_t i = 0; i < nSamples; ++i)
	{
		netVarience += pow(samples[i] - mean, 2);
	}
	return netVarience / static_cast<double>(nSamples - 1);
}

float Signal::Statistics::StandardDeviationF(const float varience)
{
	return sqrtf(varience);
}

double Signal::Statistics::StandardDeviationD(const double varience)
{
	return sqrt(varience);
}

void Signal::Convolution::ConvolutionD(
	const double* inputSignalSamples, const size_t nInputSignalSamples,
	const double* inputSignalImpulseResponse, const size_t nElementInInputSignalImpulseResponse,
	double* outputSignalSamples // note that outputSignalSamples is expected to be of have nInputSignalSamples + nElementInInputSignalImpulseResponse elements
	)
{
	// 0 the output buffer
	const size_t outputBufferMemSz = sizeof(double) * (nInputSignalSamples + nElementInInputSignalImpulseResponse);
	std::memset(outputSignalSamples, 0, outputBufferMemSz);

	// O(N ^ 2)
	for (size_t i = 0; i < nInputSignalSamples; ++i)
	{
		for (size_t j = 0; j < nElementInInputSignalImpulseResponse; ++j)
		{
			outputSignalSamples[i + j] = outputSignalSamples[i + j] + 
				inputSignalSamples[i] * inputSignalImpulseResponse[j];
		}
	}
}

void Signal::Convolution::ConvolutionF(
	const float* inputSignalSamples, const size_t nInputSignalSamples,
	const float* inputSignalImpulseResponse, const size_t nElementInInputSignalImpulseResponse,
	float* outputSignalSamples // note that outputSignalSamples is expected to be of have nInputSignalSamples + nElementInInputSignalImpulseResponse elements
	)
{
	// 0 the output buffer
	const size_t outputBufferMemSz = sizeof(float) * (nInputSignalSamples + nElementInInputSignalImpulseResponse);
	std::memset(outputSignalSamples, 0, outputBufferMemSz);

	// O(N ^ 2)
	for (size_t i = 0; i < nInputSignalSamples; ++i)
	{
		for (size_t j = 0; j < nElementInInputSignalImpulseResponse; ++j)
		{
			outputSignalSamples[i + j] = outputSignalSamples[i + j] +
				inputSignalSamples[i] * inputSignalImpulseResponse[j];
		}
	}
}

void Signal::Convolution::RunningSumD(const double* inputSignal, const size_t nSamplesInputSignal, double* output)
{
	output[0] = inputSignal[0];
	for (size_t i = 1; i < nSamplesInputSignal; ++i)
	{
		output[i] = output[i - 1] + inputSignal[i];
	}
}

void Signal::Convolution::RunningSumF(const float* inputSignal, const size_t nSamplesInputSignal, float* output)
{
	output[0] = inputSignal[0];
	for (size_t i = 1; i < nSamplesInputSignal; ++i)
	{
		output[i] = output[i - 1] + inputSignal[i];
	}
}