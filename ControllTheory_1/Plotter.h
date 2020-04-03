#pragma once

#include <vector>
#include <string>
#include "PlotPoints.h"


class Plotter
{
private:

	std::vector<PlotPoints> Plots;

public:
	Plotter() = default;

	template <class T>
	Plotter(PlotPoints Element) 
	{
		Plots.emplace_back(Element);
	}

	//template <typename PlotPoint, typename... PlotPointsPack>
	//Plotter(PlotPoint Head, PlotPointsPack... Tail)
	//{
	//	Plots.emplace_back(Head);
	//	Plotter(Tail...);
	//};
	Plotter(std::vector<PlotPoints> PointsList)
	{
		for (const auto& Point : PointsList)
		{
			Plots.emplace_back(Point);
		}
	};
	void DrawPlot() const;
};