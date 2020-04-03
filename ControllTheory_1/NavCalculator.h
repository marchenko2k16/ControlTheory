#pragma once

#include <vector>
#include <string>

class NavCalculator
{
private:
	std::vector<float_t> X1;
	std::vector<float_t> X2;
	
	int32_t IterationsCount = 0;
	float_t TimeSpent = -1.f;

	float_t S0 = 0;
	float_t V = 0;
	float_t L = 0;
	float_t Fi = 0;
	
	int32_t N = 100;

	float_t GoalX1 = 0.f;
	float_t GoalX2 = 0.f;
	
	float_t StartX1 = 0.f;
	float_t StartX2 = 0.f;

	float_t Tau = 0;

	float_t Epsilon = 0.05f;
	void RecalculateMutableVariables();
	std::vector<float_t> FillVectorWithStep(float_t Start, float_t End, float_t Step) const;

public:
	void ResetS0(int32_t NewValueS0);
	void ResetV(int32_t NewValueV);
	void ResetL(int32_t NewValueL);
	void ResetFi(int32_t NewValueFi);
	void ResetN(int32_t NewValueN);

	NavCalculator(int32_t StudentN, float_t InStartX1, float_t InStartX2);

	void Calculate();

	float_t GetTimeSpent() const;
	int32_t GetIterationCount() const;
	std::vector<float_t> GetCalculatedX1() const;
	std::vector<float_t> GetCalculatedX2() const;
	float_t GetGoalX() const;
	float_t GetGoalY() const;

};