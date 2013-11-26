
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)

CXX           = g++
CXXFLAGS      = -g -Wall -Wextra -fPIC
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared

CXXFLAGS     += $(ROOTCFLAGS)
CXXFLAGS     += -I${PWD}/../inc
NLIBS         = $(ROOTLIBS) 
NLIBS        += -lEG
NLIBS        += -lMinuit
NLIBS        += -lTreePlayer
NLIBS        += ${PWD}/../lib/libLaura++.so
LIBS          = $(filter-out -lNew, $(NLIBS))

.SUFFIXES: .cc,.C

# ================================================================================
default: GenFitNoDPMultiDim GenFitNoDP GenFitKpipi GenFit3pi GenFitBelleCPKpipi \
ResultsExtractor PlotResults MergeDataFiles KMatrixExample CalcChiSq

Master: Master.o
	$(LD) $(LDFLAGS) -o Master Master.o $(LIBS)

Slave: Slave.o
	$(LD) $(LDFLAGS) -o Slave Slave.o $(LIBS)

ATLAS-CMS: ATLAS-CMS.o
	$(LD) $(LDFLAGS) -o ATLAS-CMS ATLAS-CMS.o $(LIBS)

GenFitNoDPMultiDim: GenFitNoDPMultiDim.o
	$(LD) $(LDFLAGS) -o GenFitNoDPMultiDim GenFitNoDPMultiDim.o $(LIBS)

GenFitNoDP: GenFitNoDP.o
	$(LD) $(LDFLAGS) -o GenFitNoDP GenFitNoDP.o $(LIBS)

GenFitKpipi: GenFitKpipi.o
	$(LD) $(LDFLAGS) -o GenFitKpipi GenFitKpipi.o $(LIBS)

GenFitBelleCPKpipi: GenFitBelleCPKpipi.o
	$(LD) $(LDFLAGS) -o GenFitBelleCPKpipi GenFitBelleCPKpipi.o $(LIBS)

GenFit3pi: GenFit3pi.o
	$(LD) $(LDFLAGS) -o GenFit3pi GenFit3pi.o $(LIBS)

PlotResults: PlotResults.o
	$(LD) $(LDFLAGS) -o PlotResults PlotResults.o $(LIBS)

ResultsExtractor.o: ResultsExtractor.cc ResultsExtractor.hh
ResultsExtractor: resultsExtractorMain.o ResultsExtractor.o
	$(LD) $(LDFLAGS) -o ResultsExtractor resultsExtractorMain.o ResultsExtractor.o $(LIBS)

MergeDataFiles.o: MergeDataFiles.cc MergeDataFiles.hh
MergeDataFiles: mergeDataFilesMain.o MergeDataFiles.o
	$(LD) $(LDFLAGS) -o MergeDataFiles mergeDataFilesMain.o MergeDataFiles.o $(LIBS)

KMatrixExample: KMatrixExample.o
	$(LD) $(LDFLAGS) -o KMatrixExample KMatrixExample.o $(LIBS)
KMatrixDto3pi: KMatrixDto3pi.o
	$(LD) $(LDFLAGS) -o KMatrixDto3pi KMatrixDto3pi.o $(LIBS)

CalcChiSq.o: CalcChiSq.cc CalcChiSq.hh
CalcChiSq: calcChiSqMain.o CalcChiSq.o
	$(LD) $(LDFLAGS) -o CalcChiSq calcChiSqMain.o CalcChiSq.o $(LIBS)

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f ResultsExtractor MergeDataFiles PlotResults \
	GenFitBelleCPKpipi GenFitKpipi GenFitNoDPMultiDim GenFitNoDP GenFit3pi \
	KMatrixExample KMatrixDto3pi CalcChiSq Master Slave ATLAS-CMS *.o core
