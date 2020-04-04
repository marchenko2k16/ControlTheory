# All Rights Reserved @ Alexander Marchenko
import scipy.integrate as sci_integrator
import numpy
import math
import matplotlib.pyplot as plotter

SIndex = 0
IIndex = 1
RIndex = 2
DIndex = 3

def PlotEssentials(SIRD, TimeStampsArray, Title) :

    TimeString = "Time Period"
    PopulationString = "Population"

    Figure = plotter.figure()
    
    SubPlot = Figure.add_subplot(211)
    SubPlot.set_xlabel(TimeString)
    SubPlot.set_ylabel(PopulationString)
    SubPlot.set_title(Title)
    STrans = [i[SIndex] for i in SIRD]
    ITrans = [i[IIndex] for i in SIRD]
    RTrans = [i[RIndex] for i in SIRD]
    DTrans = [i[DIndex] for i in SIRD]
    
    plotter.plot(TimeStampsArray, STrans, label = "Suspected")
    plotter.plot(TimeStampsArray, ITrans, label = "Infcted") 
    plotter.plot(TimeStampsArray, RTrans, label = "Recoered")
    plotter.plot(TimeStampsArray, DTrans, label = "Dead")

    plotter.legend(loc='lower center', mode = "expand", ncol = 4)
    plotter.show()


def CalcAndPlot(Population, Infected, Recovered, DeathCount, Suspectible,  
ContactIntensity, TransferPrabability, RecoverySpeed, DeathRate, VaccinatedIndividuals,
 InfectionDays, IntervalMultiplier, ExperimentTitle) :
    

    def DifferentialEquationsModel(SIRD, TimeStampsArray) :
    
        def p(I) :
            return (-1.0)* (ContactIntensity * I * numpy.log(1-TransferPrabability) / Population    )

        dS_dt = -SIRD[SIndex] * p(SIRD[IIndex]) - SIRD[SIndex] * VaccinatedIndividuals
        dI_dt = SIRD[SIndex] * p(SIRD[IIndex]) - RecoverySpeed *SIRD[IIndex] - DeathRate * SIRD[IIndex]
        dR_dt = RecoverySpeed * SIRD[IIndex] + VaccinatedIndividuals * SIRD[SIndex]
        dD_dt = DeathRate* SIRD[IIndex]
        return [dS_dt, dI_dt, dR_dt, dD_dt]

    SIRD = [Suspectible, Infected, Recovered, DeathCount]
    Timestamps = numpy.linspace(0, InfectionDays, InfectionDays * IntervalMultiplier)
    PlotEssentials(sci_integrator.odeint(DifferentialEquationsModel, SIRD, Timestamps), Timestamps, ExperimentTitle)


# DEFAULTS
DefaultSumyPopulation = 270000 # Overall Number (N) - MUTABLE

DefaultInfected = 16 # I
DefaultRecovered = 2 # R
DefaultDeathCount = 3 # D
DefaultSuspectible = DefaultSumyPopulation - DefaultInfected - DefaultRecovered # S

DefaultContactIntensity = 4 #[1,50] (r) - MUTABLE
DefaultTransferPrabability = 0.7 # [0.5, 0.9](c) - MUTABLE
DefaultRecoverySpeed = 0.3 #[0.1, 0.9](q)  - MUTABLE
DefaultDeathRate = 0.04 #[0.01, 0.1](q0) 0.04 -is nearly equal to current statistics - MUTABLE
DefaultVaccinatedIndividuals = 0.0 # [0.0, 0.1](u) CONST/MUTABLE

DefaultEpidemicDays = 300 #[30,300] (T)
# DEFAULTS

DefaultChanceToBeImmunedBy = 0.001
DefaultImunedInduviduals = 10 + DefaultSumyPopulation * DefaultChanceToBeImmunedBy# S(t)
NonImunedIndividuals = DefaultSumyPopulation - DefaultImunedInduviduals # R(t)


CalcAndPlot(DefaultSumyPopulation, DefaultInfected, DefaultRecovered, DefaultDeathCount, DefaultSuspectible, DefaultContactIntensity,
DefaultTransferPrabability, DefaultRecoverySpeed, DefaultDeathRate, DefaultVaccinatedIndividuals, DefaultEpidemicDays, 1, "# Real values 03.04.2019")

CalcAndPlot(DefaultSumyPopulation, DefaultInfected, DefaultRecovered, DefaultDeathCount, DefaultSuspectible, DefaultContactIntensity,
0.9, DefaultRecoverySpeed, DefaultDeathRate, DefaultVaccinatedIndividuals, DefaultEpidemicDays, 1, "Hypotetical values (High Transferability)")

CalcAndPlot(DefaultSumyPopulation, DefaultInfected, DefaultRecovered, DefaultDeathCount, DefaultSuspectible, DefaultContactIntensity,
DefaultTransferPrabability, 0.1, DefaultDeathRate, DefaultVaccinatedIndividuals, DefaultEpidemicDays, 1, "# Hypotetical values (Low Recovery Speed)")

CalcAndPlot(DefaultSumyPopulation, DefaultInfected, DefaultRecovered, DefaultDeathCount, DefaultSuspectible, DefaultContactIntensity,
DefaultTransferPrabability, DefaultRecoverySpeed, 0.1, DefaultVaccinatedIndividuals, DefaultEpidemicDays, 1, "Hypotetical values (High Deathrate)")

CalcAndPlot(DefaultSumyPopulation, DefaultInfected, DefaultRecovered, DefaultDeathCount, DefaultSuspectible, 50,
DefaultTransferPrabability, DefaultRecoverySpeed, DefaultDeathRate, DefaultVaccinatedIndividuals, DefaultEpidemicDays, 1, "# Hypotetical values (High ContactIntensity)")

TestVaccinatedIndividuals = DefaultSumyPopulation * 0.1

CalcAndPlot(DefaultSumyPopulation, DefaultInfected, DefaultRecovered, DefaultDeathCount, DefaultSuspectible, DefaultContactIntensity,
DefaultTransferPrabability, DefaultRecoverySpeed, DefaultDeathRate, TestVaccinatedIndividuals, DefaultEpidemicDays, 1, "# Hypotetical values (High Vacined Individuals)")