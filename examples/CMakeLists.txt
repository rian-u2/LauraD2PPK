
list(APPEND EXAMPLE_SOURCES
    B3piKMatrixMassProj
    B3piKMatrixPlots
    CalcChiSq
    GenFit3K
    GenFit3KS
    GenFit3pi
    GenFitBelleCPKpipi
    GenFitDpipi
    GenFitDs2KKpi
    GenFitEFKLLM
    GenFitKpipi
    GenFitNoDP
    GenFitNoDPMultiDim
    KMatrixDto3pi
    KMatrixExample
    MergeDataFiles
    mixedSampleTest
    PlotKMatrixTAmp
    PlotResults
    point2PointTestSample
    QuasiFlatSqDalitz
    ResultsExtractor
    SimFitCoordinator
    SimFitTask
    SimFitTaskRooFit
    )

if(NOT LAURA_BUILD_ROOFIT_TASK)
    list(REMOVE_ITEM EXAMPLE_SOURCES SimFitTaskRooFit)
endif()

foreach( _example ${EXAMPLE_SOURCES})
    add_executable(${_example} ${_example}.cc)
    target_link_libraries(${_example} PRIVATE Laura++)
    install(TARGETS ${_example} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endforeach()

# Also install the python script version of GenFit3pi
configure_file(GenFit3pi.py.in GenFit3pi.py @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/GenFit3pi.py DESTINATION ${CMAKE_INSTALL_BINDIR})

