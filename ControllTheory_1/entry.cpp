#include "Plotter.h"
#include "NavCalculator.h"

#include <iostream>

namespace Globals 
{
	int32_t StudentN = 10;
	float_t StartX = 0.f;
	float_t StartY = 0.f;
}

int main()
{
	NavCalculator Calculator0(Globals::StudentN, Globals::StartX, Globals::StartY);
	Calculator0.Calculate();
	
	std::string Legend0 = "Default valuee " + std::to_string(Calculator0.GetTimeSpent()) +
		", iterations count = " + std::to_string(Calculator0.GetIterationCount());
	PlotPoints PlotPointsDefault(Legend0, Calculator0.GetCalculatedX1(), Calculator0.GetCalculatedX2(), Calculator0.GetGoalX(), Calculator0.GetGoalY());
	
	NavCalculator Calculator1(Globals::StudentN, Globals::StartX, Globals::StartY);
	Calculator1.ResetS0(0);
	Calculator1.Calculate();
	
	std::string Legend1 = "S0 set to 0, time spent " + std::to_string(Calculator1.GetTimeSpent()) +
		", iterations count = " + std::to_string(Calculator1.GetIterationCount());
	PlotPoints PlotPointsS0(Legend1, Calculator1.GetCalculatedX1(), Calculator1.GetCalculatedX2(), Calculator1.GetGoalX(), Calculator1.GetGoalY());
	
	NavCalculator Calculator2(Globals::StudentN, Globals::StartX, Globals::StartY); 
	Calculator2.ResetV(100);
	Calculator2.Calculate();
	std::string Legend2 = "V set to 100, time spent " + std::to_string(Calculator2.GetTimeSpent()) + 
		", iterations count = " + std::to_string(Calculator2.GetIterationCount());
	
	PlotPoints PlotPointsV(Legend2, Calculator2.GetCalculatedX1(), Calculator2.GetCalculatedX2(), Calculator2.GetGoalX(), Calculator2.GetGoalY());
	
	NavCalculator Calculator3(Globals::StudentN, Globals::StartX, Globals::StartY);
	Calculator3.ResetL(100);
	Calculator3.Calculate();
	
	std::string Legend3 = "L set to 100, time spent " + std::to_string(Calculator3.GetTimeSpent()) +
		", iterations count = " + std::to_string(Calculator3.GetIterationCount());
	PlotPoints PlotPointsL(Legend3, Calculator3.GetCalculatedX1(), Calculator3.GetCalculatedX2(), Calculator3.GetGoalX(), Calculator3.GetGoalY());
	
	NavCalculator Calculator4(Globals::StudentN, Globals::StartX, Globals::StartY);
	Calculator4.ResetFi(100);
	Calculator4.Calculate();
	
	std::string Legend4 = "Fi set to 100, time spent " + std::to_string(Calculator4.GetTimeSpent()) +
		", iterations count = " + std::to_string(Calculator4.GetIterationCount());
	PlotPoints PlotPointsFi(Legend4, Calculator4.GetCalculatedX1(), Calculator4.GetCalculatedX2(), Calculator4.GetGoalX(), Calculator4.GetGoalY());
	
	NavCalculator Calculator5(Globals::StudentN, Globals::StartX, Globals::StartY);
	Calculator5.ResetN(250);
	Calculator5.Calculate();
	
	std::string Legend5 = "N set to 250, time spent " + std::to_string(Calculator5.GetTimeSpent()) +
		", iterations count = " + std::to_string(Calculator5.GetIterationCount());
	PlotPoints PlotPointsN(Legend5, Calculator5.GetCalculatedX1(), Calculator5.GetCalculatedX2(), Calculator5.GetGoalX(), Calculator5.GetGoalY());

	// additional tests 	
	NavCalculator Calculator6(Globals::StudentN, Globals::StartX, Globals::StartY);
	Calculator6.ResetV(1);
	Calculator6.ResetS0(0);
	Calculator6.Calculate();

	std::string Legend6 = "S0 = 0, V = 1, time spent " + std::to_string(Calculator6.GetTimeSpent()) +
		", iterations count = " + std::to_string(Calculator6.GetIterationCount());
	PlotPoints PlotPointsTest1(Legend6, Calculator6.GetCalculatedX1(), Calculator6.GetCalculatedX2(), Calculator6.GetGoalX(), Calculator6.GetGoalY());


	NavCalculator Calculator7(Globals::StudentN, Globals::StartX, Globals::StartY);
	Calculator7.ResetV(1);
	Calculator7.ResetS0(2);
	Calculator7.Calculate();

	std::string Legend7 = "S0 = 2, V = 1, time spent " + std::to_string(Calculator7.GetTimeSpent()) +
		", iterations count = " + std::to_string(Calculator7.GetIterationCount());
	PlotPoints PlotPointsTest2(Legend7, Calculator7.GetCalculatedX1(), Calculator7.GetCalculatedX2(), Calculator7.GetGoalX(), Calculator7.GetGoalY());

	NavCalculator Calculator8(Globals::StudentN, Globals::StartX, Globals::StartY);
	Calculator8.ResetV(1);
	Calculator8.ResetS0(2);
	Calculator8.ResetFi(50);
	Calculator8.Calculate();

	std::string Legend8 = "S0 = 2, V = 1, Fi = 50, time spent " + std::to_string(Calculator8.GetTimeSpent()) +
		", iterations count = " + std::to_string(Calculator8.GetIterationCount());
	PlotPoints PlotPointsTest3(Legend8, Calculator8.GetCalculatedX1(), Calculator8.GetCalculatedX2(), Calculator8.GetGoalX(), Calculator8.GetGoalY());

	NavCalculator Calculator9(Globals::StudentN, Globals::StartX, Globals::StartY);
	Calculator9.ResetV(1);
	Calculator9.ResetS0(2);
	Calculator9.ResetFi(-90);
	Calculator9.Calculate();

	std::string Legend9 = "S0 = 2, V = 1, Fi = 0, time spent " + std::to_string(Calculator9.GetTimeSpent()) +
		", iterations count = " + std::to_string(Calculator9.GetIterationCount());
	PlotPoints PlotPointsTest4(Legend9, Calculator9.GetCalculatedX1(), Calculator9.GetCalculatedX2(), Calculator9.GetGoalX(), Calculator7.GetGoalY());

	std::vector<PlotPoints> Points; 

	bool AdditionalTest = true;
	if (AdditionalTest)
	{
		Points = { PlotPointsTest1, PlotPointsTest2, PlotPointsTest3, PlotPointsTest4 };
	}
	else
	{
		Points = { PlotPointsDefault, PlotPointsS0, PlotPointsV, PlotPointsL, PlotPointsFi, PlotPointsN };
	}
	Plotter Plot(Points);
	Plot.DrawPlot();
}