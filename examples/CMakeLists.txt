
list(APPEND EXAMPLE_SOURCES
    B3piKMatrixMassProj
    B3piKMatrixPlots
    CalcChiSq
    GenFit3K
    GenFit3KS
    GenFit3pi
    GenFitBelleCPKpipi
    GenFitDs2KKpi
    GenFitEFKLLM
    GenFitKpipi
    GenFitNoDP
    GenFitNoDPMultiDim
    KMatrixDto3pi
    KMatrixExample
    Master
    MergeDataFiles
    mixedSampleTest
    PlotKMatrixTAmp
    PlotResults
    point2PointTestSample
    ResultsExtractor
    Slave
    SlaveRooFit
    )

if(NOT LAURA_BUILD_ROOFIT_SLAVE)
    list(REMOVE_ITEM EXAMPLE_SOURCES SlaveRooFit)
endif()

foreach( _example ${EXAMPLE_SOURCES})
    add_executable(${_example} ${_example}.cc)
    target_link_libraries(${_example} PRIVATE Laura++)
    install(TARGETS ${_example} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endforeach()

