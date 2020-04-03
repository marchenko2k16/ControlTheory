#pragma once

#include <string>
#include <vector>

struct PlotPoints
{
	PlotPoints(std::string InLegend, std::vector<float_t> InXCoordinate, std::vector<float_t> InYCoordinate, float_t InGoalX, float_t InGoalY) :
		Legend(InLegend), XCoordinate(InXCoordinate), YCoordinate(InYCoordinate), GoalX(InGoalX), GoalY(InGoalY)
	{}
	std::string Legend;
	std::vector<float_t> XCoordinate;
	std::vector<float_t> YCoordinate;
	float_t GoalX = 0;
	float_t GoalY = 0;
};