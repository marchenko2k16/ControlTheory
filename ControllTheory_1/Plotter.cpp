#include "Plotter.h"
#include "GnuplotWrapper.h"

#include <algorithm>

void Plotter::DrawPlot() const
{
	Gnuplot gp;
	gp.remove_tmpfiles();
	gp.set_xrange(-100, 100);
	gp.set_yrange(-100, 100);
	for (const auto& Plot : Plots)
	{
		int32_t size_dbg = Plot.XCoordinate.size();
		std::cout << size_dbg << std::endl;;
		
		gp.set_style("lines");
		gp.plot_xy(Plot.XCoordinate, Plot.YCoordinate, Plot.Legend);
		gp.set_style("points");
		std::vector<float_t> GoalX{ Plot.GoalX };
		std::vector<float_t> GoalY{ Plot.GoalY };
		gp.plot_xy(GoalX, GoalY);
	}
	//gp.plot_xy(Plot.XCoordinate, Plot.YCoordinate, Plot.Legend);
	// cassually prevents Gnuplot from RAII to see graph
	std::cin.get();
}
