
"""
Copyright 2017 University of Warwick

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Laura++ package authors:
John Back
Paul Harrison
Thomas Latham
"""

import sys

# Process the command-line arguments
def usage( progName ) :
    print 'Usage:'
    print '%s gen [nExpt = 1] [firstExpt = 0]' % progName
    print '%s fit <iFit> [nExpt = 1] [firstExpt = 0]' % progName

if len(sys.argv) < 2 :
    usage( sys.argv[0] )
    sys.exit(1)

command = sys.argv[1]
command = command.lower()

iFit = 0
nExpt = 1
firstExpt = 0
if command == 'gen' :
    if len(sys.argv) > 2 :
        nExpt = int( sys.argv[2] )
        if len(sys.argv) > 3 :
            firstExpt = int( sys.argv[3] )
elif command == 'fit' :
    if len(sys.argv) < 3 :
        usage( sys.argv[0] )
        sys.exit(1)
    iFit = int( sys.argv[2] )
    if len(sys.argv) > 3 :
        nExpt = int( sys.argv[3] )
        if len(sys.argv) > 4 :
            firstExpt = int( sys.argv[4] )
else :
    usage( sys.argv[0] )
    sys.exit(1)

# Import ROOT and load the appropriate libraries
import ROOT
ROOT.gSystem.Load('libEG')
ROOT.gSystem.Load('libHist')
ROOT.gSystem.Load('libMatrix')
ROOT.gSystem.Load('libTree')
ROOT.gSystem.Load('libTreePlayer')
ROOT.gSystem.Load('libMinuit')
ROOT.gSystem.Load('../lib/libLaura++.so')

# If you want to use square DP histograms for efficiency,
# backgrounds or you just want the square DP co-ordinates
# stored in the toy MC ntuple then set this to True
squareDP = False

# This defines the DP => decay is B+ -> pi+ pi+ pi-
# Particle 1 = pi+
# Particle 2 = pi+
# Particle 3 = pi-
# The DP is defined in terms of m13Sq and m23Sq
daughters = ROOT.LauDaughters('B+', 'pi+', 'pi+', 'pi-', squareDP)

# Optionally apply some vetoes to the DP
# (example syntax given but commented-out)
vetoes = ROOT.LauVetoes()
#DMin = 1.70
#DMax = 1.925
#JpsiMin = 3.051
#JpsiMax = 3.222
#psi2SMin = 3.676
#psi2SMax = 3.866
# D0 veto, m23 (and automatically m13)
#vetoes.addMassVeto(1, DMin, DMax)
# J/psi veto, m23 (and automatically m13)
#vetoes.addMassVeto(1, JpsiMin, JpsiMax)
# psi(2S) veto, m23 (and automatically m13)
#vetoes.addMassVeto(1, psi2SMin, psi2SMax)

# Define the efficiency model (defaults to unity everywhere)
effModel = ROOT.LauEffModel(daughters, vetoes)

# Can optionally provide a histogram to model variation over DP
# (example syntax given but commented-out)
#effHistFile = ROOT.TFile.Open('histoFiles/B3piNRDPEff.root', 'read')
#effHist = effHistFile.Get('effHist')
#useInterpolation = True
#fluctuateBins = False
#useUpperHalf = True
#effModel.setEffHisto(effHist, useInterpolation, fluctuateBins, 0.0, 0.0, useUpperHalf, squareDP)

# Create the isobar model

# Set the values of the Blatt-Weisskopf barrier radii and whether they are fixed or floating
resMaker = ROOT.LauResonanceMaker.get()
resMaker.setDefaultBWRadius( ROOT.LauBlattWeisskopfFactor.Parent, 5.0 )
resMaker.setDefaultBWRadius( ROOT.LauBlattWeisskopfFactor.Light,  4.0 )
resMaker.fixBWRadius( ROOT.LauBlattWeisskopfFactor.Parent, True )
resMaker.fixBWRadius( ROOT.LauBlattWeisskopfFactor.Light,  True )

sigModel = ROOT.LauIsobarDynamics(daughters, effModel)

# Add various components to the isobar model,
# modifying some resonance parameters
# addResonance arguments: resName, resPairAmpInt, resType
reson = sigModel.addResonance('rho0(770)',     1, ROOT.LauAbsResonance.GS)
reson = sigModel.addResonance('rho0(1450)',    1, ROOT.LauAbsResonance.RelBW)
reson = sigModel.addResonance('f_0(980)',      1, ROOT.LauAbsResonance.Flatte)
reson.setResonanceParameter('g1',0.2)
reson.setResonanceParameter('g2',1.0)
reson = sigModel.addResonance('f_2(1270)',     1, ROOT.LauAbsResonance.RelBW)
reson = sigModel.addResonance('BelleNR_Swave', 0, ROOT.LauAbsResonance.BelleSymNRNoInter)
reson.setResonanceParameter("alpha", 0.2)

# Reset the maximum signal DP ASq value
# This will be automatically adjusted to avoid bias or extreme
# inefficiency if you get the value wrong but best to set this by
# hand once you've found the right value through some trial and error.
sigModel.setASqMaxValue(0.35)

# Create the fit model
fitModel = ROOT.LauSimpleFitModel(sigModel)

# Create the complex coefficients for the isobar model
# Here we're using the magnitude and phase form:
# c_j = a_j exp(i*delta_j)
coeffset = []
coeffset.append( ROOT.LauMagPhaseCoeffSet('rho0(770)',     1.00,  0.00,  True,  True) )
coeffset.append( ROOT.LauMagPhaseCoeffSet("rho0(1450)",    0.37,  1.99, False, False) )
coeffset.append( ROOT.LauMagPhaseCoeffSet("f_0(980)",      0.27, -1.59, False, False) )
coeffset.append( ROOT.LauMagPhaseCoeffSet("f_2(1270)",     0.53,  1.39, False, False) )
coeffset.append( ROOT.LauMagPhaseCoeffSet('BelleNR_Swave', 0.54, -0.84, False, False) )
for i in coeffset :
    fitModel.setAmpCoeffSet(i)

# Set the signal yield and define whether it is fixed or floated
nSigEvents = 1500.0
signalEvents = ROOT.LauParameter('signalEvents',nSigEvents,-1.0*nSigEvents,2.0*nSigEvents,False)
fitModel.setNSigEvents(signalEvents)

# Set the number of experiments to generate or fit and which experiment to start with
fitModel.setNExpts( nExpt, firstExpt )


# Set up a background model

# First declare the names of the background class(es)
bkgndNames = ROOT.std.vector(ROOT.TString)()
bkgndNames.push_back(ROOT.TString('qqbar'))
fitModel.setBkgndClassNames( bkgndNames )

# Define and set the yield parameter for the background
nBkg = 1250.0
nBkgndEvents = ROOT.LauParameter('qqbar',nBkg,-2.0*nBkg,2.0*nBkg,False)
fitModel.setNBkgndEvents( nBkgndEvents )

# Create the background DP model
qqbarModel = ROOT.LauBkgndDPModel(daughters, vetoes)

# Load in background DP model histogram
# (example syntax given but commented-out - the background will be treated as being uniform in the DP in the absence of a histogram)
#qqFileName = 'histoFiles/offResDP.root'
#qqFile = TFile.Open(qqFileName, 'read')
#qqDP = qqFile.Get('AllmTheta')
#qqbarModel.setBkgndHisto(qqDP, useInterpolation, fluctuateBins, useUpperHalf, squareDP)

# Add the background DP model into the fit model
fitModel.setBkgndDPModel( 'qqbar', qqbarModel )


# Configure various fit options

# Switch on/off calculation of asymmetric errors.
fitModel.useAsymmFitErrors(False)

# Randomise initial fit values for the signal mode
fitModel.useRandomInitFitPars(True)

haveBkgnds = ( fitModel.nBkgndClasses() > 0 )

# Switch on/off Poissonian smearing of total number of events
fitModel.doPoissonSmearing(haveBkgnds)

# Switch on/off Extended ML Fit option
fitModel.doEMLFit(haveBkgnds)

# Generate toy from the fitted parameters
#fitToyFileName = 'fitToyMC_3pi_%d.root' % iFit
#fitModel.compareFitData(100, fitToyFileName)

# Write out per-event likelihoods and sWeights
#splotFileName = 'splot_3pi_%d.root' % iFit
#fitModel.writeSPlotData(splotFileName, 'splot', False)

# Set the names of the files to read/write
dataFile = 'gen-3pi.root'
treeName = 'genResults'
rootFileName = ''
tableFileName = ''
if command == 'fit' :
    rootFileName = 'fit3pi_%d_expt_%d-%d.root' % ( iFit, firstExpt, firstExpt+nExpt-1 )
    tableFileName = 'fit3piResults_%d' % iFit
else :
    rootFileName = 'dummy.root'
    tableFileName = 'gen3piResults'

# Execute the generation/fit
fitModel.run( command, dataFile, treeName, rootFileName, tableFileName )

