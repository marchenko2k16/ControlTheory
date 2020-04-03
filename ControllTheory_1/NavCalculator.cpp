#include "NavCalculator.h"

#include <cmath>
#include <iostream>

#include <algorithm>

const float_t PI = 3.14159;

void NavCalculator::RecalculateMutableVariables()
{
	Tau = L / V / N;
	GoalX1 = L * std::cos(Fi);
	GoalX2 = L * std::sin(Fi);
}

std::vector<float_t> NavCalculator::FillVectorWithStep(float_t Start, float_t End, float_t Step) const
{
	std::vector<float_t> Vector;
	float_t CurrentStep = Start;
	for (int32_t CurrentIndex = 0; CurrentIndex < End; CurrentIndex++, CurrentStep += Step)
	{
		Vector.emplace_back(CurrentStep);
	}
	return Vector;
}

void NavCalculator::ResetS0(int32_t NewValueS0)
{
	S0 = NewValueS0;
}

void NavCalculator::ResetV(int32_t NewValueV)
{
	V = NewValueV;
	RecalculateMutableVariables();
}

void NavCalculator::ResetL(int32_t NewValueL)
{
	L = NewValueL;
	RecalculateMutableVariables();
}

void NavCalculator::ResetFi(int32_t NewValueFi)
{
	Fi = NewValueFi;
	RecalculateMutableVariables();
}

void NavCalculator::ResetN(int32_t NewValueN)
{
	N = NewValueN;
	RecalculateMutableVariables();
}

NavCalculator::NavCalculator(int32_t StudentN, float_t InStartX1, float_t InStartX2)
{
	S0 = StudentN;
	V = StudentN;
	L = StudentN;
	
	Fi = StudentN * PI / 25.f;

	Tau = L / V / N;

	StartX1 = InStartX1;
	StartX2 = InStartX2;

	GoalX1 = L * std::cos(Fi);
	GoalX2 = L * std::sin(Fi);
}

void NavCalculator::Calculate()
{
	int32_t MaxIterations = 2000;

	std::cout << "tau: " << Tau << std::endl;
	std::cout << "x1_goal: " << GoalX1 << std::endl;
	std::cout << "x2_goa2: " << GoalX2 << std::endl;
	
	std::vector<float_t> t;
	std::vector<float_t>Lambda_k;
	std::vector<float_t>u1_k;
	std::vector<float_t>u2_k;
	std::vector<float_t>x1_k;
	std::vector<float_t>x2_k;

	int32_t K = 0;
	for (; K < MaxIterations; K++)
	{
		t = FillVectorWithStep(0, K, Tau);
		Lambda_k = FillVectorWithStep(0, K, 0);
		u1_k = FillVectorWithStep(0, K, 0);
		u2_k = FillVectorWithStep(0, K, 0);
		x1_k = FillVectorWithStep(StartX1, K + 1, 0);
		x2_k = FillVectorWithStep(StartX2, K + 1, 0);

		const auto func_s_x2 = [](float_t x2)
		{
			return x2;
		};

		const auto s = [&](float_t x2)
		{
			return S0 * func_s_x2(x2);
		};

		const auto Lambda = [&](int32_t t_index)
		{
			return std::sqrt(std::pow(GoalX1 - x1_k[t_index] - s(x2_k[t_index]) * Tau, 2) + std::pow(GoalX2 - x2_k[t_index], 2)) 
				* V * Tau - std::pow(V, 2) * std::pow(Tau, 2);
		};

		const auto u1 = [&](int32_t t_index)
		{
			return ((GoalX1 - x1_k[t_index] - s(x2_k[t_index]) * Tau) * V * Tau) /
				(Lambda_k[t_index] + std::pow(V, 2) * std::pow(Tau, 2));
		};
		
		const auto u2 = [&](int32_t t_index)
		{
			return ((GoalX2 - x2_k[t_index]) * V * Tau) / (Lambda_k[t_index] + std::pow(V, 2) * std::pow(Tau, 2));
		};
		
		const auto func_x1 = [&](int32_t t_index)
		{
			return t_index == 0 ? StartX1 : x1_k[t_index - 1] + Tau * (s(x2_k[t_index - 1]) + V * u1_k[t_index - 1]);
		};


		const auto func_x2 = [&](int32_t t_index)
		{
			return t_index == 0 ? StartX2 : x2_k[t_index - 1] + V * Tau * u2_k[t_index - 1];
		};

		for (int32_t CurrentK = 0; CurrentK < K; CurrentK++)
		{
			Lambda_k[CurrentK] = Lambda(CurrentK);
			u1_k[CurrentK] = u1(CurrentK);
			u2_k[CurrentK] = u2(CurrentK);
			x1_k[CurrentK + 1] = func_x1(CurrentK + 1);
			x2_k[CurrentK + 1] = func_x2(CurrentK + 1);
		}

		if (std::abs(x1_k.back() - GoalX1) <= Epsilon && std::abs(x2_k.back() - GoalX2) <= Epsilon)
		{
			TimeSpent = (L / V / N) * (N + K);
			IterationsCount = K;
			X1 = x1_k;
			X2 = x2_k;
			return;
		}
	}

	X1 = x1_k;
	X2 = x2_k;
	IterationsCount = K;
	TimeSpent = -1.f;
}

float_t NavCalculator::GetTimeSpent() const
{
	return TimeSpent;
}

int32_t NavCalculator::GetIterationCount() const
{
	return IterationsCount;
}

std::vector<float_t> NavCalculator::GetCalculatedX1() const
{
	return X1;
}

std::vector<float_t> NavCalculator::GetCalculatedX2() const
{
	return X2;
}

float_t NavCalculator::GetGoalX() const
{
	return GoalX1;
}

float_t NavCalculator::GetGoalY() const
{
	return GoalX2;
}
