// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__LaurapLpL
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "/home/oryan/laura/inc/Lau1DCubicSpline.hh"
#include "/home/oryan/laura/inc/Lau1DHistPdf.hh"
#include "/home/oryan/laura/inc/Lau2DAbsDP.hh"
#include "/home/oryan/laura/inc/Lau2DAbsDPPdf.hh"
#include "/home/oryan/laura/inc/Lau2DAbsHistDP.hh"
#include "/home/oryan/laura/inc/Lau2DAbsHistDPPdf.hh"
#include "/home/oryan/laura/inc/Lau2DCubicSpline.hh"
#include "/home/oryan/laura/inc/Lau2DHistDP.hh"
#include "/home/oryan/laura/inc/Lau2DHistDPPdf.hh"
#include "/home/oryan/laura/inc/Lau2DHistPdf.hh"
#include "/home/oryan/laura/inc/Lau2DSplineDP.hh"
#include "/home/oryan/laura/inc/Lau2DSplineDPPdf.hh"
#include "/home/oryan/laura/inc/LauASqMaxFinder.hh"
#include "/home/oryan/laura/inc/LauAbsBkgndDPModel.hh"
#include "/home/oryan/laura/inc/LauAbsCoeffSet.hh"
#include "/home/oryan/laura/inc/LauAbsEffModel.hh"
#include "/home/oryan/laura/inc/LauAbsFitModel.hh"
#include "/home/oryan/laura/inc/LauAbsFitter.hh"
#include "/home/oryan/laura/inc/LauAbsIncohRes.hh"
#include "/home/oryan/laura/inc/LauAbsModIndPartWave.hh"
#include "/home/oryan/laura/inc/LauAbsPdf.hh"
#include "/home/oryan/laura/inc/LauAbsRValue.hh"
#include "/home/oryan/laura/inc/LauAbsResonance.hh"
#include "/home/oryan/laura/inc/LauArgusPdf.hh"
#include "/home/oryan/laura/inc/LauAsymmCalc.hh"
#include "/home/oryan/laura/inc/LauBelleCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauBelleNR.hh"
#include "/home/oryan/laura/inc/LauBelleSymNR.hh"
#include "/home/oryan/laura/inc/LauBifurcatedGaussPdf.hh"
#include "/home/oryan/laura/inc/LauBkgndDPModel.hh"
#include "/home/oryan/laura/inc/LauBlattWeisskopfFactor.hh"
#include "/home/oryan/laura/inc/LauBlind.hh"
#include "/home/oryan/laura/inc/LauBreitWignerRes.hh"
#include "/home/oryan/laura/inc/LauCPFitModel.hh"
#include "/home/oryan/laura/inc/LauCacheData.hh"
#include "/home/oryan/laura/inc/LauCalcChiSq.hh"
#include "/home/oryan/laura/inc/LauCartesianCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauCartesianGammaCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauChebychevPdf.hh"
#include "/home/oryan/laura/inc/LauCleoCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauComplex.hh"
#include "/home/oryan/laura/inc/LauConstants.hh"
#include "/home/oryan/laura/inc/LauCruijffPdf.hh"
#include "/home/oryan/laura/inc/LauCrystalBallPdf.hh"
#include "/home/oryan/laura/inc/LauDPDepBifurGaussPdf.hh"
#include "/home/oryan/laura/inc/LauDPDepCruijffPdf.hh"
#include "/home/oryan/laura/inc/LauDPDepGaussPdf.hh"
#include "/home/oryan/laura/inc/LauDPDepMapPdf.hh"
#include "/home/oryan/laura/inc/LauDPDepSumPdf.hh"
#include "/home/oryan/laura/inc/LauDPPartialIntegralInfo.hh"
#include "/home/oryan/laura/inc/LauDabbaRes.hh"
#include "/home/oryan/laura/inc/LauDatabasePDG.hh"
#include "/home/oryan/laura/inc/LauDaughters.hh"
#include "/home/oryan/laura/inc/LauEFKLLMRes.hh"
#include "/home/oryan/laura/inc/LauEffModel.hh"
#include "/home/oryan/laura/inc/LauEmbeddedData.hh"
#include "/home/oryan/laura/inc/LauExponentialPdf.hh"
#include "/home/oryan/laura/inc/LauFitDataTree.hh"
#include "/home/oryan/laura/inc/LauFitNtuple.hh"
#include "/home/oryan/laura/inc/LauFitObject.hh"
#include "/home/oryan/laura/inc/LauFitter.hh"
#include "/home/oryan/laura/inc/LauFlatNR.hh"
#include "/home/oryan/laura/inc/LauFlatteRes.hh"
#include "/home/oryan/laura/inc/LauFormulaPar.hh"
#include "/home/oryan/laura/inc/LauGaussIncohRes.hh"
#include "/home/oryan/laura/inc/LauGaussPdf.hh"
#include "/home/oryan/laura/inc/LauGenNtuple.hh"
#include "/home/oryan/laura/inc/LauGounarisSakuraiRes.hh"
#include "/home/oryan/laura/inc/LauIntegrals.hh"
#include "/home/oryan/laura/inc/LauIsobarDynamics.hh"
#include "/home/oryan/laura/inc/LauKMatrixProdPole.hh"
#include "/home/oryan/laura/inc/LauKMatrixProdSVP.hh"
#include "/home/oryan/laura/inc/LauKMatrixPropFactory.hh"
#include "/home/oryan/laura/inc/LauKMatrixPropagator.hh"
#include "/home/oryan/laura/inc/LauKappaRes.hh"
#include "/home/oryan/laura/inc/LauKinematics.hh"
#include "/home/oryan/laura/inc/LauLASSBWRes.hh"
#include "/home/oryan/laura/inc/LauLASSNRRes.hh"
#include "/home/oryan/laura/inc/LauLASSRes.hh"
#include "/home/oryan/laura/inc/LauLinearPdf.hh"
#include "/home/oryan/laura/inc/LauMagPhaseCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauMagPhaseCoeffSet.hh"
#include "/home/oryan/laura/inc/LauMergeDataFiles.hh"
#include "/home/oryan/laura/inc/LauMinuit.hh"
#include "/home/oryan/laura/inc/LauModIndPartWaveMagPhase.hh"
#include "/home/oryan/laura/inc/LauModIndPartWaveRealImag.hh"
#include "/home/oryan/laura/inc/LauNRAmplitude.hh"
#include "/home/oryan/laura/inc/LauNovosibirskPdf.hh"
#include "/home/oryan/laura/inc/LauParamFixed.hh"
#include "/home/oryan/laura/inc/LauParameter.hh"
#include "/home/oryan/laura/inc/LauParametricStepFuncPdf.hh"
#include "/home/oryan/laura/inc/LauParticlePDG.hh"
#include "/home/oryan/laura/inc/LauPolNR.hh"
#include "/home/oryan/laura/inc/LauPolarFormFactorNR.hh"
#include "/home/oryan/laura/inc/LauPolarFormFactorSymNR.hh"
#include "/home/oryan/laura/inc/LauPolarGammaCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauPoleRes.hh"
#include "/home/oryan/laura/inc/LauPrint.hh"
#include "/home/oryan/laura/inc/LauRandom.hh"
#include "/home/oryan/laura/inc/LauRealImagCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauRealImagCoeffSet.hh"
#include "/home/oryan/laura/inc/LauRealImagGammaCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauRelBreitWignerRes.hh"
#include "/home/oryan/laura/inc/LauRescattering2Res.hh"
#include "/home/oryan/laura/inc/LauRescatteringRes.hh"
#include "/home/oryan/laura/inc/LauResonanceInfo.hh"
#include "/home/oryan/laura/inc/LauResonanceMaker.hh"
#include "/home/oryan/laura/inc/LauResultsExtractor.hh"
#include "/home/oryan/laura/inc/LauRhoOmegaMix.hh"
#include "/home/oryan/laura/inc/LauSPlot.hh"
#include "/home/oryan/laura/inc/LauScfMap.hh"
#include "/home/oryan/laura/inc/LauSigmaRes.hh"
#include "/home/oryan/laura/inc/LauSigmoidPdf.hh"
#include "/home/oryan/laura/inc/LauSimFitCoordinator.hh"
#include "/home/oryan/laura/inc/LauSimFitTask.hh"
#include "/home/oryan/laura/inc/LauSimpleFitModel.hh"
#include "/home/oryan/laura/inc/LauString.hh"
#include "/home/oryan/laura/inc/LauSumPdf.hh"
#include "/home/oryan/laura/inc/LauTextFileParser.hh"
#include "/home/oryan/laura/inc/LauVetoes.hh"
#include "/home/oryan/laura/inc/LauWeightedSumEffModel.hh"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace LauConstants {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *LauConstants_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("LauConstants", 0 /*version*/, "LauConstants.hh", 39,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &LauConstants_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *LauConstants_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace LauRandom {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *LauRandom_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("LauRandom", 0 /*version*/, "LauRandom.hh", 42,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &LauRandom_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *LauRandom_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static void delete_Lau1DCubicSpline(void *p);
   static void deleteArray_Lau1DCubicSpline(void *p);
   static void destruct_Lau1DCubicSpline(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau1DCubicSpline*)
   {
      ::Lau1DCubicSpline *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau1DCubicSpline >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau1DCubicSpline", ::Lau1DCubicSpline::Class_Version(), "Lau1DCubicSpline.hh", 84,
                  typeid(::Lau1DCubicSpline), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau1DCubicSpline::Dictionary, isa_proxy, 4,
                  sizeof(::Lau1DCubicSpline) );
      instance.SetDelete(&delete_Lau1DCubicSpline);
      instance.SetDeleteArray(&deleteArray_Lau1DCubicSpline);
      instance.SetDestructor(&destruct_Lau1DCubicSpline);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau1DCubicSpline*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau1DCubicSpline*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau1DCubicSpline*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauFitDataTree(void *p);
   static void deleteArray_LauFitDataTree(void *p);
   static void destruct_LauFitDataTree(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauFitDataTree*)
   {
      ::LauFitDataTree *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauFitDataTree >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauFitDataTree", ::LauFitDataTree::Class_Version(), "LauFitDataTree.hh", 51,
                  typeid(::LauFitDataTree), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauFitDataTree::Dictionary, isa_proxy, 4,
                  sizeof(::LauFitDataTree) );
      instance.SetDelete(&delete_LauFitDataTree);
      instance.SetDeleteArray(&deleteArray_LauFitDataTree);
      instance.SetDestructor(&destruct_LauFitDataTree);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauFitDataTree*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauFitDataTree*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauFitDataTree*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauAbsRValue(void *p);
   static void deleteArray_LauAbsRValue(void *p);
   static void destruct_LauAbsRValue(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauAbsRValue*)
   {
      ::LauAbsRValue *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauAbsRValue >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauAbsRValue", ::LauAbsRValue::Class_Version(), "LauAbsRValue.hh", 45,
                  typeid(::LauAbsRValue), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauAbsRValue::Dictionary, isa_proxy, 4,
                  sizeof(::LauAbsRValue) );
      instance.SetDelete(&delete_LauAbsRValue);
      instance.SetDeleteArray(&deleteArray_LauAbsRValue);
      instance.SetDestructor(&destruct_LauAbsRValue);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauAbsRValue*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauAbsRValue*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauAbsRValue*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LauBlind(void *p = nullptr);
   static void *newArray_LauBlind(Long_t size, void *p);
   static void delete_LauBlind(void *p);
   static void deleteArray_LauBlind(void *p);
   static void destruct_LauBlind(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauBlind*)
   {
      ::LauBlind *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauBlind >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauBlind", ::LauBlind::Class_Version(), "LauBlind.hh", 42,
                  typeid(::LauBlind), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauBlind::Dictionary, isa_proxy, 4,
                  sizeof(::LauBlind) );
      instance.SetNew(&new_LauBlind);
      instance.SetNewArray(&newArray_LauBlind);
      instance.SetDelete(&delete_LauBlind);
      instance.SetDeleteArray(&deleteArray_LauBlind);
      instance.SetDestructor(&destruct_LauBlind);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauBlind*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauBlind*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauBlind*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LauParameter(void *p = nullptr);
   static void *newArray_LauParameter(Long_t size, void *p);
   static void delete_LauParameter(void *p);
   static void deleteArray_LauParameter(void *p);
   static void destruct_LauParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauParameter*)
   {
      ::LauParameter *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauParameter >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauParameter", ::LauParameter::Class_Version(), "LauParameter.hh", 49,
                  typeid(::LauParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauParameter::Dictionary, isa_proxy, 4,
                  sizeof(::LauParameter) );
      instance.SetNew(&new_LauParameter);
      instance.SetNewArray(&newArray_LauParameter);
      instance.SetDelete(&delete_LauParameter);
      instance.SetDeleteArray(&deleteArray_LauParameter);
      instance.SetDestructor(&destruct_LauParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauParameter*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauParameter*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauParameter*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *LauParamFixed_Dictionary();
   static void LauParamFixed_TClassManip(TClass*);
   static void *new_LauParamFixed(void *p = nullptr);
   static void *newArray_LauParamFixed(Long_t size, void *p);
   static void delete_LauParamFixed(void *p);
   static void deleteArray_LauParamFixed(void *p);
   static void destruct_LauParamFixed(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauParamFixed*)
   {
      ::LauParamFixed *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::LauParamFixed));
      static ::ROOT::TGenericClassInfo 
         instance("LauParamFixed", "LauParamFixed.hh", 38,
                  typeid(::LauParamFixed), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &LauParamFixed_Dictionary, isa_proxy, 4,
                  sizeof(::LauParamFixed) );
      instance.SetNew(&new_LauParamFixed);
      instance.SetNewArray(&newArray_LauParamFixed);
      instance.SetDelete(&delete_LauParamFixed);
      instance.SetDeleteArray(&deleteArray_LauParamFixed);
      instance.SetDestructor(&destruct_LauParamFixed);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauParamFixed*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauParamFixed*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauParamFixed*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *LauParamFixed_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::LauParamFixed*>(nullptr))->GetClass();
      LauParamFixed_TClassManip(theClass);
   return theClass;
   }

   static void LauParamFixed_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void delete_LauAbsPdf(void *p);
   static void deleteArray_LauAbsPdf(void *p);
   static void destruct_LauAbsPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauAbsPdf*)
   {
      ::LauAbsPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauAbsPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauAbsPdf", ::LauAbsPdf::Class_Version(), "LauAbsPdf.hh", 55,
                  typeid(::LauAbsPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauAbsPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauAbsPdf) );
      instance.SetDelete(&delete_LauAbsPdf);
      instance.SetDeleteArray(&deleteArray_LauAbsPdf);
      instance.SetDestructor(&destruct_LauAbsPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauAbsPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauAbsPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauAbsPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Lau1DHistPdf(void *p);
   static void deleteArray_Lau1DHistPdf(void *p);
   static void destruct_Lau1DHistPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau1DHistPdf*)
   {
      ::Lau1DHistPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau1DHistPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau1DHistPdf", ::Lau1DHistPdf::Class_Version(), "Lau1DHistPdf.hh", 45,
                  typeid(::Lau1DHistPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau1DHistPdf::Dictionary, isa_proxy, 4,
                  sizeof(::Lau1DHistPdf) );
      instance.SetDelete(&delete_Lau1DHistPdf);
      instance.SetDeleteArray(&deleteArray_Lau1DHistPdf);
      instance.SetDestructor(&destruct_Lau1DHistPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau1DHistPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau1DHistPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau1DHistPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Lau2DAbsDP(void *p);
   static void deleteArray_Lau2DAbsDP(void *p);
   static void destruct_Lau2DAbsDP(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau2DAbsDP*)
   {
      ::Lau2DAbsDP *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau2DAbsDP >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau2DAbsDP", ::Lau2DAbsDP::Class_Version(), "Lau2DAbsDP.hh", 41,
                  typeid(::Lau2DAbsDP), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau2DAbsDP::Dictionary, isa_proxy, 4,
                  sizeof(::Lau2DAbsDP) );
      instance.SetDelete(&delete_Lau2DAbsDP);
      instance.SetDeleteArray(&deleteArray_Lau2DAbsDP);
      instance.SetDestructor(&destruct_Lau2DAbsDP);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau2DAbsDP*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau2DAbsDP*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau2DAbsDP*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Lau2DAbsDPPdf(void *p);
   static void deleteArray_Lau2DAbsDPPdf(void *p);
   static void destruct_Lau2DAbsDPPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau2DAbsDPPdf*)
   {
      ::Lau2DAbsDPPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau2DAbsDPPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau2DAbsDPPdf", ::Lau2DAbsDPPdf::Class_Version(), "Lau2DAbsDPPdf.hh", 40,
                  typeid(::Lau2DAbsDPPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau2DAbsDPPdf::Dictionary, isa_proxy, 4,
                  sizeof(::Lau2DAbsDPPdf) );
      instance.SetDelete(&delete_Lau2DAbsDPPdf);
      instance.SetDeleteArray(&deleteArray_Lau2DAbsDPPdf);
      instance.SetDestructor(&destruct_Lau2DAbsDPPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau2DAbsDPPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau2DAbsDPPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau2DAbsDPPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Lau2DAbsHistDP(void *p);
   static void deleteArray_Lau2DAbsHistDP(void *p);
   static void destruct_Lau2DAbsHistDP(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau2DAbsHistDP*)
   {
      ::Lau2DAbsHistDP *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau2DAbsHistDP >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau2DAbsHistDP", ::Lau2DAbsHistDP::Class_Version(), "Lau2DAbsHistDP.hh", 48,
                  typeid(::Lau2DAbsHistDP), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau2DAbsHistDP::Dictionary, isa_proxy, 4,
                  sizeof(::Lau2DAbsHistDP) );
      instance.SetDelete(&delete_Lau2DAbsHistDP);
      instance.SetDeleteArray(&deleteArray_Lau2DAbsHistDP);
      instance.SetDestructor(&destruct_Lau2DAbsHistDP);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau2DAbsHistDP*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau2DAbsHistDP*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau2DAbsHistDP*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Lau2DAbsHistDPPdf(void *p);
   static void deleteArray_Lau2DAbsHistDPPdf(void *p);
   static void destruct_Lau2DAbsHistDPPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau2DAbsHistDPPdf*)
   {
      ::Lau2DAbsHistDPPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau2DAbsHistDPPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau2DAbsHistDPPdf", ::Lau2DAbsHistDPPdf::Class_Version(), "Lau2DAbsHistDPPdf.hh", 47,
                  typeid(::Lau2DAbsHistDPPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau2DAbsHistDPPdf::Dictionary, isa_proxy, 4,
                  sizeof(::Lau2DAbsHistDPPdf) );
      instance.SetDelete(&delete_Lau2DAbsHistDPPdf);
      instance.SetDeleteArray(&deleteArray_Lau2DAbsHistDPPdf);
      instance.SetDestructor(&destruct_Lau2DAbsHistDPPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau2DAbsHistDPPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau2DAbsHistDPPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau2DAbsHistDPPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Lau2DCubicSpline(void *p);
   static void deleteArray_Lau2DCubicSpline(void *p);
   static void destruct_Lau2DCubicSpline(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau2DCubicSpline*)
   {
      ::Lau2DCubicSpline *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau2DCubicSpline >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau2DCubicSpline", ::Lau2DCubicSpline::Class_Version(), "Lau2DCubicSpline.hh", 65,
                  typeid(::Lau2DCubicSpline), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau2DCubicSpline::Dictionary, isa_proxy, 4,
                  sizeof(::Lau2DCubicSpline) );
      instance.SetDelete(&delete_Lau2DCubicSpline);
      instance.SetDeleteArray(&deleteArray_Lau2DCubicSpline);
      instance.SetDestructor(&destruct_Lau2DCubicSpline);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau2DCubicSpline*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau2DCubicSpline*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau2DCubicSpline*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Lau2DHistDP(void *p);
   static void deleteArray_Lau2DHistDP(void *p);
   static void destruct_Lau2DHistDP(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau2DHistDP*)
   {
      ::Lau2DHistDP *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau2DHistDP >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau2DHistDP", ::Lau2DHistDP::Class_Version(), "Lau2DHistDP.hh", 48,
                  typeid(::Lau2DHistDP), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau2DHistDP::Dictionary, isa_proxy, 4,
                  sizeof(::Lau2DHistDP) );
      instance.SetDelete(&delete_Lau2DHistDP);
      instance.SetDeleteArray(&deleteArray_Lau2DHistDP);
      instance.SetDestructor(&destruct_Lau2DHistDP);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau2DHistDP*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau2DHistDP*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau2DHistDP*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Lau2DHistDPPdf(void *p);
   static void deleteArray_Lau2DHistDPPdf(void *p);
   static void destruct_Lau2DHistDPPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau2DHistDPPdf*)
   {
      ::Lau2DHistDPPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau2DHistDPPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau2DHistDPPdf", ::Lau2DHistDPPdf::Class_Version(), "Lau2DHistDPPdf.hh", 47,
                  typeid(::Lau2DHistDPPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau2DHistDPPdf::Dictionary, isa_proxy, 4,
                  sizeof(::Lau2DHistDPPdf) );
      instance.SetDelete(&delete_Lau2DHistDPPdf);
      instance.SetDeleteArray(&deleteArray_Lau2DHistDPPdf);
      instance.SetDestructor(&destruct_Lau2DHistDPPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau2DHistDPPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau2DHistDPPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau2DHistDPPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Lau2DHistPdf(void *p);
   static void deleteArray_Lau2DHistPdf(void *p);
   static void destruct_Lau2DHistPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau2DHistPdf*)
   {
      ::Lau2DHistPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau2DHistPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau2DHistPdf", ::Lau2DHistPdf::Class_Version(), "Lau2DHistPdf.hh", 47,
                  typeid(::Lau2DHistPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau2DHistPdf::Dictionary, isa_proxy, 4,
                  sizeof(::Lau2DHistPdf) );
      instance.SetDelete(&delete_Lau2DHistPdf);
      instance.SetDeleteArray(&deleteArray_Lau2DHistPdf);
      instance.SetDestructor(&destruct_Lau2DHistPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau2DHistPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau2DHistPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau2DHistPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Lau2DSplineDP(void *p);
   static void deleteArray_Lau2DSplineDP(void *p);
   static void destruct_Lau2DSplineDP(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau2DSplineDP*)
   {
      ::Lau2DSplineDP *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau2DSplineDP >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau2DSplineDP", ::Lau2DSplineDP::Class_Version(), "Lau2DSplineDP.hh", 49,
                  typeid(::Lau2DSplineDP), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau2DSplineDP::Dictionary, isa_proxy, 4,
                  sizeof(::Lau2DSplineDP) );
      instance.SetDelete(&delete_Lau2DSplineDP);
      instance.SetDeleteArray(&deleteArray_Lau2DSplineDP);
      instance.SetDestructor(&destruct_Lau2DSplineDP);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau2DSplineDP*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau2DSplineDP*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau2DSplineDP*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Lau2DSplineDPPdf(void *p);
   static void deleteArray_Lau2DSplineDPPdf(void *p);
   static void destruct_Lau2DSplineDPPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Lau2DSplineDPPdf*)
   {
      ::Lau2DSplineDPPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Lau2DSplineDPPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Lau2DSplineDPPdf", ::Lau2DSplineDPPdf::Class_Version(), "Lau2DSplineDPPdf.hh", 48,
                  typeid(::Lau2DSplineDPPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Lau2DSplineDPPdf::Dictionary, isa_proxy, 4,
                  sizeof(::Lau2DSplineDPPdf) );
      instance.SetDelete(&delete_Lau2DSplineDPPdf);
      instance.SetDeleteArray(&deleteArray_Lau2DSplineDPPdf);
      instance.SetDestructor(&destruct_Lau2DSplineDPPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Lau2DSplineDPPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::Lau2DSplineDPPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Lau2DSplineDPPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauAbsFitter(void *p);
   static void deleteArray_LauAbsFitter(void *p);
   static void destruct_LauAbsFitter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauAbsFitter*)
   {
      ::LauAbsFitter *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauAbsFitter >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauAbsFitter", ::LauAbsFitter::Class_Version(), "LauAbsFitter.hh", 48,
                  typeid(::LauAbsFitter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauAbsFitter::Dictionary, isa_proxy, 4,
                  sizeof(::LauAbsFitter) );
      instance.SetDelete(&delete_LauAbsFitter);
      instance.SetDeleteArray(&deleteArray_LauAbsFitter);
      instance.SetDestructor(&destruct_LauAbsFitter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauAbsFitter*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauAbsFitter*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauAbsFitter*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauFormulaPar(void *p);
   static void deleteArray_LauFormulaPar(void *p);
   static void destruct_LauFormulaPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauFormulaPar*)
   {
      ::LauFormulaPar *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauFormulaPar >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauFormulaPar", ::LauFormulaPar::Class_Version(), "LauFormulaPar.hh", 49,
                  typeid(::LauFormulaPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauFormulaPar::Dictionary, isa_proxy, 4,
                  sizeof(::LauFormulaPar) );
      instance.SetDelete(&delete_LauFormulaPar);
      instance.SetDeleteArray(&deleteArray_LauFormulaPar);
      instance.SetDestructor(&destruct_LauFormulaPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauFormulaPar*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauFormulaPar*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauFormulaPar*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauFitObject(void *p);
   static void deleteArray_LauFitObject(void *p);
   static void destruct_LauFitObject(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauFitObject*)
   {
      ::LauFitObject *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauFitObject >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauFitObject", ::LauFitObject::Class_Version(), "LauFitObject.hh", 46,
                  typeid(::LauFitObject), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauFitObject::Dictionary, isa_proxy, 4,
                  sizeof(::LauFitObject) );
      instance.SetDelete(&delete_LauFitObject);
      instance.SetDeleteArray(&deleteArray_LauFitObject);
      instance.SetDestructor(&destruct_LauFitObject);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauFitObject*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauFitObject*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauFitObject*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauASqMaxFinder(void *p);
   static void deleteArray_LauASqMaxFinder(void *p);
   static void destruct_LauASqMaxFinder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauASqMaxFinder*)
   {
      ::LauASqMaxFinder *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauASqMaxFinder >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauASqMaxFinder", ::LauASqMaxFinder::Class_Version(), "LauASqMaxFinder.hh", 46,
                  typeid(::LauASqMaxFinder), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauASqMaxFinder::Dictionary, isa_proxy, 4,
                  sizeof(::LauASqMaxFinder) );
      instance.SetDelete(&delete_LauASqMaxFinder);
      instance.SetDeleteArray(&deleteArray_LauASqMaxFinder);
      instance.SetDestructor(&destruct_LauASqMaxFinder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauASqMaxFinder*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauASqMaxFinder*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauASqMaxFinder*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauAbsBkgndDPModel(void *p);
   static void deleteArray_LauAbsBkgndDPModel(void *p);
   static void destruct_LauAbsBkgndDPModel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauAbsBkgndDPModel*)
   {
      ::LauAbsBkgndDPModel *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauAbsBkgndDPModel >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauAbsBkgndDPModel", ::LauAbsBkgndDPModel::Class_Version(), "LauAbsBkgndDPModel.hh", 45,
                  typeid(::LauAbsBkgndDPModel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauAbsBkgndDPModel::Dictionary, isa_proxy, 4,
                  sizeof(::LauAbsBkgndDPModel) );
      instance.SetDelete(&delete_LauAbsBkgndDPModel);
      instance.SetDeleteArray(&deleteArray_LauAbsBkgndDPModel);
      instance.SetDestructor(&destruct_LauAbsBkgndDPModel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauAbsBkgndDPModel*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauAbsBkgndDPModel*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauAbsBkgndDPModel*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauAbsCoeffSet(void *p);
   static void deleteArray_LauAbsCoeffSet(void *p);
   static void destruct_LauAbsCoeffSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauAbsCoeffSet*)
   {
      ::LauAbsCoeffSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauAbsCoeffSet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauAbsCoeffSet", ::LauAbsCoeffSet::Class_Version(), "LauAbsCoeffSet.hh", 49,
                  typeid(::LauAbsCoeffSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauAbsCoeffSet::Dictionary, isa_proxy, 4,
                  sizeof(::LauAbsCoeffSet) );
      instance.SetDelete(&delete_LauAbsCoeffSet);
      instance.SetDeleteArray(&deleteArray_LauAbsCoeffSet);
      instance.SetDestructor(&destruct_LauAbsCoeffSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauAbsCoeffSet*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauAbsCoeffSet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauAbsCoeffSet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauAbsEffModel(void *p);
   static void deleteArray_LauAbsEffModel(void *p);
   static void destruct_LauAbsEffModel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauAbsEffModel*)
   {
      ::LauAbsEffModel *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauAbsEffModel >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauAbsEffModel", ::LauAbsEffModel::Class_Version(), "LauAbsEffModel.hh", 46,
                  typeid(::LauAbsEffModel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauAbsEffModel::Dictionary, isa_proxy, 4,
                  sizeof(::LauAbsEffModel) );
      instance.SetDelete(&delete_LauAbsEffModel);
      instance.SetDeleteArray(&deleteArray_LauAbsEffModel);
      instance.SetDestructor(&destruct_LauAbsEffModel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauAbsEffModel*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauAbsEffModel*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauAbsEffModel*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LauComplex(void *p = nullptr);
   static void *newArray_LauComplex(Long_t size, void *p);
   static void delete_LauComplex(void *p);
   static void deleteArray_LauComplex(void *p);
   static void destruct_LauComplex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauComplex*)
   {
      ::LauComplex *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauComplex >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauComplex", ::LauComplex::Class_Version(), "LauComplex.hh", 62,
                  typeid(::LauComplex), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauComplex::Dictionary, isa_proxy, 4,
                  sizeof(::LauComplex) );
      instance.SetNew(&new_LauComplex);
      instance.SetNewArray(&newArray_LauComplex);
      instance.SetDelete(&delete_LauComplex);
      instance.SetDeleteArray(&deleteArray_LauComplex);
      instance.SetDestructor(&destruct_LauComplex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauComplex*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauComplex*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauComplex*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauSimFitTask(void *p);
   static void deleteArray_LauSimFitTask(void *p);
   static void destruct_LauSimFitTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauSimFitTask*)
   {
      ::LauSimFitTask *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauSimFitTask >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauSimFitTask", ::LauSimFitTask::Class_Version(), "LauSimFitTask.hh", 51,
                  typeid(::LauSimFitTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauSimFitTask::Dictionary, isa_proxy, 4,
                  sizeof(::LauSimFitTask) );
      instance.SetDelete(&delete_LauSimFitTask);
      instance.SetDeleteArray(&deleteArray_LauSimFitTask);
      instance.SetDestructor(&destruct_LauSimFitTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauSimFitTask*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauSimFitTask*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauSimFitTask*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauSPlot(void *p);
   static void deleteArray_LauSPlot(void *p);
   static void destruct_LauSPlot(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauSPlot*)
   {
      ::LauSPlot *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauSPlot >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauSPlot", ::LauSPlot::Class_Version(), "LauSPlot.hh", 69,
                  typeid(::LauSPlot), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauSPlot::Dictionary, isa_proxy, 4,
                  sizeof(::LauSPlot) );
      instance.SetDelete(&delete_LauSPlot);
      instance.SetDeleteArray(&deleteArray_LauSPlot);
      instance.SetDestructor(&destruct_LauSPlot);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauSPlot*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauSPlot*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauSPlot*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauAbsFitModel(void *p);
   static void deleteArray_LauAbsFitModel(void *p);
   static void destruct_LauAbsFitModel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauAbsFitModel*)
   {
      ::LauAbsFitModel *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauAbsFitModel >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauAbsFitModel", ::LauAbsFitModel::Class_Version(), "LauAbsFitModel.hh", 88,
                  typeid(::LauAbsFitModel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauAbsFitModel::Dictionary, isa_proxy, 4,
                  sizeof(::LauAbsFitModel) );
      instance.SetDelete(&delete_LauAbsFitModel);
      instance.SetDeleteArray(&deleteArray_LauAbsFitModel);
      instance.SetDestructor(&destruct_LauAbsFitModel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauAbsFitModel*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauAbsFitModel*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauAbsFitModel*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauBlattWeisskopfFactor(void *p);
   static void deleteArray_LauBlattWeisskopfFactor(void *p);
   static void destruct_LauBlattWeisskopfFactor(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauBlattWeisskopfFactor*)
   {
      ::LauBlattWeisskopfFactor *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauBlattWeisskopfFactor >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauBlattWeisskopfFactor", ::LauBlattWeisskopfFactor::Class_Version(), "LauBlattWeisskopfFactor.hh", 45,
                  typeid(::LauBlattWeisskopfFactor), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauBlattWeisskopfFactor::Dictionary, isa_proxy, 4,
                  sizeof(::LauBlattWeisskopfFactor) );
      instance.SetDelete(&delete_LauBlattWeisskopfFactor);
      instance.SetDeleteArray(&deleteArray_LauBlattWeisskopfFactor);
      instance.SetDestructor(&destruct_LauBlattWeisskopfFactor);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauBlattWeisskopfFactor*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauBlattWeisskopfFactor*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauBlattWeisskopfFactor*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauAbsResonance(void *p);
   static void deleteArray_LauAbsResonance(void *p);
   static void destruct_LauAbsResonance(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauAbsResonance*)
   {
      ::LauAbsResonance *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauAbsResonance >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauAbsResonance", ::LauAbsResonance::Class_Version(), "LauAbsResonance.hh", 51,
                  typeid(::LauAbsResonance), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauAbsResonance::Dictionary, isa_proxy, 4,
                  sizeof(::LauAbsResonance) );
      instance.SetDelete(&delete_LauAbsResonance);
      instance.SetDeleteArray(&deleteArray_LauAbsResonance);
      instance.SetDestructor(&destruct_LauAbsResonance);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauAbsResonance*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauAbsResonance*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauAbsResonance*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauAbsIncohRes(void *p);
   static void deleteArray_LauAbsIncohRes(void *p);
   static void destruct_LauAbsIncohRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauAbsIncohRes*)
   {
      ::LauAbsIncohRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauAbsIncohRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauAbsIncohRes", ::LauAbsIncohRes::Class_Version(), "LauAbsIncohRes.hh", 43,
                  typeid(::LauAbsIncohRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauAbsIncohRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauAbsIncohRes) );
      instance.SetDelete(&delete_LauAbsIncohRes);
      instance.SetDeleteArray(&deleteArray_LauAbsIncohRes);
      instance.SetDestructor(&destruct_LauAbsIncohRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauAbsIncohRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauAbsIncohRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauAbsIncohRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauAbsModIndPartWave(void *p);
   static void deleteArray_LauAbsModIndPartWave(void *p);
   static void destruct_LauAbsModIndPartWave(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauAbsModIndPartWave*)
   {
      ::LauAbsModIndPartWave *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauAbsModIndPartWave >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauAbsModIndPartWave", ::LauAbsModIndPartWave::Class_Version(), "LauAbsModIndPartWave.hh", 48,
                  typeid(::LauAbsModIndPartWave), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauAbsModIndPartWave::Dictionary, isa_proxy, 4,
                  sizeof(::LauAbsModIndPartWave) );
      instance.SetDelete(&delete_LauAbsModIndPartWave);
      instance.SetDeleteArray(&deleteArray_LauAbsModIndPartWave);
      instance.SetDestructor(&destruct_LauAbsModIndPartWave);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauAbsModIndPartWave*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauAbsModIndPartWave*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauAbsModIndPartWave*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauArgusPdf(void *p);
   static void deleteArray_LauArgusPdf(void *p);
   static void destruct_LauArgusPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauArgusPdf*)
   {
      ::LauArgusPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauArgusPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauArgusPdf", ::LauArgusPdf::Class_Version(), "LauArgusPdf.hh", 48,
                  typeid(::LauArgusPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauArgusPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauArgusPdf) );
      instance.SetDelete(&delete_LauArgusPdf);
      instance.SetDeleteArray(&deleteArray_LauArgusPdf);
      instance.SetDestructor(&destruct_LauArgusPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauArgusPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauArgusPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauArgusPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauAsymmCalc(void *p);
   static void deleteArray_LauAsymmCalc(void *p);
   static void destruct_LauAsymmCalc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauAsymmCalc*)
   {
      ::LauAsymmCalc *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauAsymmCalc >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauAsymmCalc", ::LauAsymmCalc::Class_Version(), "LauAsymmCalc.hh", 39,
                  typeid(::LauAsymmCalc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauAsymmCalc::Dictionary, isa_proxy, 4,
                  sizeof(::LauAsymmCalc) );
      instance.SetDelete(&delete_LauAsymmCalc);
      instance.SetDeleteArray(&deleteArray_LauAsymmCalc);
      instance.SetDestructor(&destruct_LauAsymmCalc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauAsymmCalc*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauAsymmCalc*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauAsymmCalc*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauBelleCPCoeffSet(void *p);
   static void deleteArray_LauBelleCPCoeffSet(void *p);
   static void destruct_LauBelleCPCoeffSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauBelleCPCoeffSet*)
   {
      ::LauBelleCPCoeffSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauBelleCPCoeffSet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauBelleCPCoeffSet", ::LauBelleCPCoeffSet::Class_Version(), "LauBelleCPCoeffSet.hh", 54,
                  typeid(::LauBelleCPCoeffSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauBelleCPCoeffSet::Dictionary, isa_proxy, 4,
                  sizeof(::LauBelleCPCoeffSet) );
      instance.SetDelete(&delete_LauBelleCPCoeffSet);
      instance.SetDeleteArray(&deleteArray_LauBelleCPCoeffSet);
      instance.SetDestructor(&destruct_LauBelleCPCoeffSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauBelleCPCoeffSet*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauBelleCPCoeffSet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauBelleCPCoeffSet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauBelleNR(void *p);
   static void deleteArray_LauBelleNR(void *p);
   static void destruct_LauBelleNR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauBelleNR*)
   {
      ::LauBelleNR *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauBelleNR >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauBelleNR", ::LauBelleNR::Class_Version(), "LauBelleNR.hh", 48,
                  typeid(::LauBelleNR), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauBelleNR::Dictionary, isa_proxy, 4,
                  sizeof(::LauBelleNR) );
      instance.SetDelete(&delete_LauBelleNR);
      instance.SetDeleteArray(&deleteArray_LauBelleNR);
      instance.SetDestructor(&destruct_LauBelleNR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauBelleNR*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauBelleNR*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauBelleNR*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauBelleSymNR(void *p);
   static void deleteArray_LauBelleSymNR(void *p);
   static void destruct_LauBelleSymNR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauBelleSymNR*)
   {
      ::LauBelleSymNR *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauBelleSymNR >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauBelleSymNR", ::LauBelleSymNR::Class_Version(), "LauBelleSymNR.hh", 47,
                  typeid(::LauBelleSymNR), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauBelleSymNR::Dictionary, isa_proxy, 4,
                  sizeof(::LauBelleSymNR) );
      instance.SetDelete(&delete_LauBelleSymNR);
      instance.SetDeleteArray(&deleteArray_LauBelleSymNR);
      instance.SetDestructor(&destruct_LauBelleSymNR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauBelleSymNR*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauBelleSymNR*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauBelleSymNR*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauBifurcatedGaussPdf(void *p);
   static void deleteArray_LauBifurcatedGaussPdf(void *p);
   static void destruct_LauBifurcatedGaussPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauBifurcatedGaussPdf*)
   {
      ::LauBifurcatedGaussPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauBifurcatedGaussPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauBifurcatedGaussPdf", ::LauBifurcatedGaussPdf::Class_Version(), "LauBifurcatedGaussPdf.hh", 48,
                  typeid(::LauBifurcatedGaussPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauBifurcatedGaussPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauBifurcatedGaussPdf) );
      instance.SetDelete(&delete_LauBifurcatedGaussPdf);
      instance.SetDeleteArray(&deleteArray_LauBifurcatedGaussPdf);
      instance.SetDestructor(&destruct_LauBifurcatedGaussPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauBifurcatedGaussPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauBifurcatedGaussPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauBifurcatedGaussPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauBkgndDPModel(void *p);
   static void deleteArray_LauBkgndDPModel(void *p);
   static void destruct_LauBkgndDPModel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauBkgndDPModel*)
   {
      ::LauBkgndDPModel *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauBkgndDPModel >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauBkgndDPModel", ::LauBkgndDPModel::Class_Version(), "LauBkgndDPModel.hh", 48,
                  typeid(::LauBkgndDPModel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauBkgndDPModel::Dictionary, isa_proxy, 4,
                  sizeof(::LauBkgndDPModel) );
      instance.SetDelete(&delete_LauBkgndDPModel);
      instance.SetDeleteArray(&deleteArray_LauBkgndDPModel);
      instance.SetDestructor(&destruct_LauBkgndDPModel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauBkgndDPModel*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauBkgndDPModel*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauBkgndDPModel*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauBreitWignerRes(void *p);
   static void deleteArray_LauBreitWignerRes(void *p);
   static void destruct_LauBreitWignerRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauBreitWignerRes*)
   {
      ::LauBreitWignerRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauBreitWignerRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauBreitWignerRes", ::LauBreitWignerRes::Class_Version(), "LauBreitWignerRes.hh", 45,
                  typeid(::LauBreitWignerRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauBreitWignerRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauBreitWignerRes) );
      instance.SetDelete(&delete_LauBreitWignerRes);
      instance.SetDeleteArray(&deleteArray_LauBreitWignerRes);
      instance.SetDestructor(&destruct_LauBreitWignerRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauBreitWignerRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauBreitWignerRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauBreitWignerRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauCPFitModel(void *p);
   static void deleteArray_LauCPFitModel(void *p);
   static void destruct_LauCPFitModel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauCPFitModel*)
   {
      ::LauCPFitModel *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauCPFitModel >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauCPFitModel", ::LauCPFitModel::Class_Version(), "LauCPFitModel.hh", 62,
                  typeid(::LauCPFitModel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauCPFitModel::Dictionary, isa_proxy, 4,
                  sizeof(::LauCPFitModel) );
      instance.SetDelete(&delete_LauCPFitModel);
      instance.SetDeleteArray(&deleteArray_LauCPFitModel);
      instance.SetDestructor(&destruct_LauCPFitModel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauCPFitModel*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauCPFitModel*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauCPFitModel*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LauCacheData(void *p = nullptr);
   static void *newArray_LauCacheData(Long_t size, void *p);
   static void delete_LauCacheData(void *p);
   static void deleteArray_LauCacheData(void *p);
   static void destruct_LauCacheData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauCacheData*)
   {
      ::LauCacheData *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauCacheData >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauCacheData", ::LauCacheData::Class_Version(), "LauCacheData.hh", 44,
                  typeid(::LauCacheData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauCacheData::Dictionary, isa_proxy, 4,
                  sizeof(::LauCacheData) );
      instance.SetNew(&new_LauCacheData);
      instance.SetNewArray(&newArray_LauCacheData);
      instance.SetDelete(&delete_LauCacheData);
      instance.SetDeleteArray(&deleteArray_LauCacheData);
      instance.SetDestructor(&destruct_LauCacheData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauCacheData*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauCacheData*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauCacheData*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LauCalcChiSq(void *p = nullptr);
   static void *newArray_LauCalcChiSq(Long_t size, void *p);
   static void delete_LauCalcChiSq(void *p);
   static void deleteArray_LauCalcChiSq(void *p);
   static void destruct_LauCalcChiSq(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauCalcChiSq*)
   {
      ::LauCalcChiSq *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauCalcChiSq >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauCalcChiSq", ::LauCalcChiSq::Class_Version(), "LauCalcChiSq.hh", 50,
                  typeid(::LauCalcChiSq), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauCalcChiSq::Dictionary, isa_proxy, 4,
                  sizeof(::LauCalcChiSq) );
      instance.SetNew(&new_LauCalcChiSq);
      instance.SetNewArray(&newArray_LauCalcChiSq);
      instance.SetDelete(&delete_LauCalcChiSq);
      instance.SetDeleteArray(&deleteArray_LauCalcChiSq);
      instance.SetDestructor(&destruct_LauCalcChiSq);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauCalcChiSq*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauCalcChiSq*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauCalcChiSq*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauCartesianCPCoeffSet(void *p);
   static void deleteArray_LauCartesianCPCoeffSet(void *p);
   static void destruct_LauCartesianCPCoeffSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauCartesianCPCoeffSet*)
   {
      ::LauCartesianCPCoeffSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauCartesianCPCoeffSet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauCartesianCPCoeffSet", ::LauCartesianCPCoeffSet::Class_Version(), "LauCartesianCPCoeffSet.hh", 50,
                  typeid(::LauCartesianCPCoeffSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauCartesianCPCoeffSet::Dictionary, isa_proxy, 4,
                  sizeof(::LauCartesianCPCoeffSet) );
      instance.SetDelete(&delete_LauCartesianCPCoeffSet);
      instance.SetDeleteArray(&deleteArray_LauCartesianCPCoeffSet);
      instance.SetDestructor(&destruct_LauCartesianCPCoeffSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauCartesianCPCoeffSet*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauCartesianCPCoeffSet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauCartesianCPCoeffSet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauCartesianGammaCPCoeffSet(void *p);
   static void deleteArray_LauCartesianGammaCPCoeffSet(void *p);
   static void destruct_LauCartesianGammaCPCoeffSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauCartesianGammaCPCoeffSet*)
   {
      ::LauCartesianGammaCPCoeffSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauCartesianGammaCPCoeffSet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauCartesianGammaCPCoeffSet", ::LauCartesianGammaCPCoeffSet::Class_Version(), "LauCartesianGammaCPCoeffSet.hh", 50,
                  typeid(::LauCartesianGammaCPCoeffSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauCartesianGammaCPCoeffSet::Dictionary, isa_proxy, 4,
                  sizeof(::LauCartesianGammaCPCoeffSet) );
      instance.SetDelete(&delete_LauCartesianGammaCPCoeffSet);
      instance.SetDeleteArray(&deleteArray_LauCartesianGammaCPCoeffSet);
      instance.SetDestructor(&destruct_LauCartesianGammaCPCoeffSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauCartesianGammaCPCoeffSet*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauCartesianGammaCPCoeffSet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauCartesianGammaCPCoeffSet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauChebychevPdf(void *p);
   static void deleteArray_LauChebychevPdf(void *p);
   static void destruct_LauChebychevPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauChebychevPdf*)
   {
      ::LauChebychevPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauChebychevPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauChebychevPdf", ::LauChebychevPdf::Class_Version(), "LauChebychevPdf.hh", 63,
                  typeid(::LauChebychevPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauChebychevPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauChebychevPdf) );
      instance.SetDelete(&delete_LauChebychevPdf);
      instance.SetDeleteArray(&deleteArray_LauChebychevPdf);
      instance.SetDestructor(&destruct_LauChebychevPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauChebychevPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauChebychevPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauChebychevPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauCleoCPCoeffSet(void *p);
   static void deleteArray_LauCleoCPCoeffSet(void *p);
   static void destruct_LauCleoCPCoeffSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauCleoCPCoeffSet*)
   {
      ::LauCleoCPCoeffSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauCleoCPCoeffSet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauCleoCPCoeffSet", ::LauCleoCPCoeffSet::Class_Version(), "LauCleoCPCoeffSet.hh", 54,
                  typeid(::LauCleoCPCoeffSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauCleoCPCoeffSet::Dictionary, isa_proxy, 4,
                  sizeof(::LauCleoCPCoeffSet) );
      instance.SetDelete(&delete_LauCleoCPCoeffSet);
      instance.SetDeleteArray(&deleteArray_LauCleoCPCoeffSet);
      instance.SetDestructor(&destruct_LauCleoCPCoeffSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauCleoCPCoeffSet*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauCleoCPCoeffSet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauCleoCPCoeffSet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauCruijffPdf(void *p);
   static void deleteArray_LauCruijffPdf(void *p);
   static void destruct_LauCruijffPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauCruijffPdf*)
   {
      ::LauCruijffPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauCruijffPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauCruijffPdf", ::LauCruijffPdf::Class_Version(), "LauCruijffPdf.hh", 62,
                  typeid(::LauCruijffPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauCruijffPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauCruijffPdf) );
      instance.SetDelete(&delete_LauCruijffPdf);
      instance.SetDeleteArray(&deleteArray_LauCruijffPdf);
      instance.SetDestructor(&destruct_LauCruijffPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauCruijffPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauCruijffPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauCruijffPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauCrystalBallPdf(void *p);
   static void deleteArray_LauCrystalBallPdf(void *p);
   static void destruct_LauCrystalBallPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauCrystalBallPdf*)
   {
      ::LauCrystalBallPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauCrystalBallPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauCrystalBallPdf", ::LauCrystalBallPdf::Class_Version(), "LauCrystalBallPdf.hh", 64,
                  typeid(::LauCrystalBallPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauCrystalBallPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauCrystalBallPdf) );
      instance.SetDelete(&delete_LauCrystalBallPdf);
      instance.SetDeleteArray(&deleteArray_LauCrystalBallPdf);
      instance.SetDestructor(&destruct_LauCrystalBallPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauCrystalBallPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauCrystalBallPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauCrystalBallPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauDPDepBifurGaussPdf(void *p);
   static void deleteArray_LauDPDepBifurGaussPdf(void *p);
   static void destruct_LauDPDepBifurGaussPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauDPDepBifurGaussPdf*)
   {
      ::LauDPDepBifurGaussPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauDPDepBifurGaussPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauDPDepBifurGaussPdf", ::LauDPDepBifurGaussPdf::Class_Version(), "LauDPDepBifurGaussPdf.hh", 47,
                  typeid(::LauDPDepBifurGaussPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauDPDepBifurGaussPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauDPDepBifurGaussPdf) );
      instance.SetDelete(&delete_LauDPDepBifurGaussPdf);
      instance.SetDeleteArray(&deleteArray_LauDPDepBifurGaussPdf);
      instance.SetDestructor(&destruct_LauDPDepBifurGaussPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauDPDepBifurGaussPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauDPDepBifurGaussPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauDPDepBifurGaussPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauDPDepCruijffPdf(void *p);
   static void deleteArray_LauDPDepCruijffPdf(void *p);
   static void destruct_LauDPDepCruijffPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauDPDepCruijffPdf*)
   {
      ::LauDPDepCruijffPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauDPDepCruijffPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauDPDepCruijffPdf", ::LauDPDepCruijffPdf::Class_Version(), "LauDPDepCruijffPdf.hh", 49,
                  typeid(::LauDPDepCruijffPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauDPDepCruijffPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauDPDepCruijffPdf) );
      instance.SetDelete(&delete_LauDPDepCruijffPdf);
      instance.SetDeleteArray(&deleteArray_LauDPDepCruijffPdf);
      instance.SetDestructor(&destruct_LauDPDepCruijffPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauDPDepCruijffPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauDPDepCruijffPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauDPDepCruijffPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauDPDepGaussPdf(void *p);
   static void deleteArray_LauDPDepGaussPdf(void *p);
   static void destruct_LauDPDepGaussPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauDPDepGaussPdf*)
   {
      ::LauDPDepGaussPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauDPDepGaussPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauDPDepGaussPdf", ::LauDPDepGaussPdf::Class_Version(), "LauDPDepGaussPdf.hh", 49,
                  typeid(::LauDPDepGaussPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauDPDepGaussPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauDPDepGaussPdf) );
      instance.SetDelete(&delete_LauDPDepGaussPdf);
      instance.SetDeleteArray(&deleteArray_LauDPDepGaussPdf);
      instance.SetDestructor(&destruct_LauDPDepGaussPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauDPDepGaussPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauDPDepGaussPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauDPDepGaussPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauDPDepMapPdf(void *p);
   static void deleteArray_LauDPDepMapPdf(void *p);
   static void destruct_LauDPDepMapPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauDPDepMapPdf*)
   {
      ::LauDPDepMapPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauDPDepMapPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauDPDepMapPdf", ::LauDPDepMapPdf::Class_Version(), "LauDPDepMapPdf.hh", 54,
                  typeid(::LauDPDepMapPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauDPDepMapPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauDPDepMapPdf) );
      instance.SetDelete(&delete_LauDPDepMapPdf);
      instance.SetDeleteArray(&deleteArray_LauDPDepMapPdf);
      instance.SetDestructor(&destruct_LauDPDepMapPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauDPDepMapPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauDPDepMapPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauDPDepMapPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauDPDepSumPdf(void *p);
   static void deleteArray_LauDPDepSumPdf(void *p);
   static void destruct_LauDPDepSumPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauDPDepSumPdf*)
   {
      ::LauDPDepSumPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauDPDepSumPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauDPDepSumPdf", ::LauDPDepSumPdf::Class_Version(), "LauDPDepSumPdf.hh", 48,
                  typeid(::LauDPDepSumPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauDPDepSumPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauDPDepSumPdf) );
      instance.SetDelete(&delete_LauDPDepSumPdf);
      instance.SetDeleteArray(&deleteArray_LauDPDepSumPdf);
      instance.SetDestructor(&destruct_LauDPDepSumPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauDPDepSumPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauDPDepSumPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauDPDepSumPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauDPPartialIntegralInfo(void *p);
   static void deleteArray_LauDPPartialIntegralInfo(void *p);
   static void destruct_LauDPPartialIntegralInfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauDPPartialIntegralInfo*)
   {
      ::LauDPPartialIntegralInfo *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauDPPartialIntegralInfo >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauDPPartialIntegralInfo", ::LauDPPartialIntegralInfo::Class_Version(), "LauDPPartialIntegralInfo.hh", 49,
                  typeid(::LauDPPartialIntegralInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauDPPartialIntegralInfo::Dictionary, isa_proxy, 4,
                  sizeof(::LauDPPartialIntegralInfo) );
      instance.SetDelete(&delete_LauDPPartialIntegralInfo);
      instance.SetDeleteArray(&deleteArray_LauDPPartialIntegralInfo);
      instance.SetDestructor(&destruct_LauDPPartialIntegralInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauDPPartialIntegralInfo*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauDPPartialIntegralInfo*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauDPPartialIntegralInfo*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauDabbaRes(void *p);
   static void deleteArray_LauDabbaRes(void *p);
   static void destruct_LauDabbaRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauDabbaRes*)
   {
      ::LauDabbaRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauDabbaRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauDabbaRes", ::LauDabbaRes::Class_Version(), "LauDabbaRes.hh", 45,
                  typeid(::LauDabbaRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauDabbaRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauDabbaRes) );
      instance.SetDelete(&delete_LauDabbaRes);
      instance.SetDeleteArray(&deleteArray_LauDabbaRes);
      instance.SetDestructor(&destruct_LauDabbaRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauDabbaRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauDabbaRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauDabbaRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauDatabasePDG*)
   {
      ::LauDatabasePDG *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauDatabasePDG >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauDatabasePDG", ::LauDatabasePDG::Class_Version(), "LauDatabasePDG.hh", 46,
                  typeid(::LauDatabasePDG), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauDatabasePDG::Dictionary, isa_proxy, 4,
                  sizeof(::LauDatabasePDG) );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauDatabasePDG*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauDatabasePDG*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauDatabasePDG*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauKinematics(void *p);
   static void deleteArray_LauKinematics(void *p);
   static void destruct_LauKinematics(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauKinematics*)
   {
      ::LauKinematics *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauKinematics >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauKinematics", ::LauKinematics::Class_Version(), "LauKinematics.hh", 46,
                  typeid(::LauKinematics), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauKinematics::Dictionary, isa_proxy, 4,
                  sizeof(::LauKinematics) );
      instance.SetDelete(&delete_LauKinematics);
      instance.SetDeleteArray(&deleteArray_LauKinematics);
      instance.SetDestructor(&destruct_LauKinematics);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauKinematics*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauKinematics*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauKinematics*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauDaughters(void *p);
   static void deleteArray_LauDaughters(void *p);
   static void destruct_LauDaughters(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauDaughters*)
   {
      ::LauDaughters *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauDaughters >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauDaughters", ::LauDaughters::Class_Version(), "LauDaughters.hh", 47,
                  typeid(::LauDaughters), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauDaughters::Dictionary, isa_proxy, 4,
                  sizeof(::LauDaughters) );
      instance.SetDelete(&delete_LauDaughters);
      instance.SetDeleteArray(&deleteArray_LauDaughters);
      instance.SetDestructor(&destruct_LauDaughters);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauDaughters*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauDaughters*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauDaughters*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauEFKLLMRes(void *p);
   static void deleteArray_LauEFKLLMRes(void *p);
   static void destruct_LauEFKLLMRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauEFKLLMRes*)
   {
      ::LauEFKLLMRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauEFKLLMRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauEFKLLMRes", ::LauEFKLLMRes::Class_Version(), "LauEFKLLMRes.hh", 50,
                  typeid(::LauEFKLLMRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauEFKLLMRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauEFKLLMRes) );
      instance.SetDelete(&delete_LauEFKLLMRes);
      instance.SetDeleteArray(&deleteArray_LauEFKLLMRes);
      instance.SetDestructor(&destruct_LauEFKLLMRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauEFKLLMRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauEFKLLMRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauEFKLLMRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauEffModel(void *p);
   static void deleteArray_LauEffModel(void *p);
   static void destruct_LauEffModel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauEffModel*)
   {
      ::LauEffModel *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauEffModel >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauEffModel", ::LauEffModel::Class_Version(), "LauEffModel.hh", 51,
                  typeid(::LauEffModel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauEffModel::Dictionary, isa_proxy, 4,
                  sizeof(::LauEffModel) );
      instance.SetDelete(&delete_LauEffModel);
      instance.SetDeleteArray(&deleteArray_LauEffModel);
      instance.SetDestructor(&destruct_LauEffModel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauEffModel*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauEffModel*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauEffModel*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauEmbeddedData(void *p);
   static void deleteArray_LauEmbeddedData(void *p);
   static void destruct_LauEmbeddedData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauEmbeddedData*)
   {
      ::LauEmbeddedData *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauEmbeddedData >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauEmbeddedData", ::LauEmbeddedData::Class_Version(), "LauEmbeddedData.hh", 47,
                  typeid(::LauEmbeddedData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauEmbeddedData::Dictionary, isa_proxy, 4,
                  sizeof(::LauEmbeddedData) );
      instance.SetDelete(&delete_LauEmbeddedData);
      instance.SetDeleteArray(&deleteArray_LauEmbeddedData);
      instance.SetDestructor(&destruct_LauEmbeddedData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauEmbeddedData*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauEmbeddedData*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauEmbeddedData*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauExponentialPdf(void *p);
   static void deleteArray_LauExponentialPdf(void *p);
   static void destruct_LauExponentialPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauExponentialPdf*)
   {
      ::LauExponentialPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauExponentialPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauExponentialPdf", ::LauExponentialPdf::Class_Version(), "LauExponentialPdf.hh", 49,
                  typeid(::LauExponentialPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauExponentialPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauExponentialPdf) );
      instance.SetDelete(&delete_LauExponentialPdf);
      instance.SetDeleteArray(&deleteArray_LauExponentialPdf);
      instance.SetDestructor(&destruct_LauExponentialPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauExponentialPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauExponentialPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauExponentialPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauFitNtuple(void *p);
   static void deleteArray_LauFitNtuple(void *p);
   static void destruct_LauFitNtuple(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauFitNtuple*)
   {
      ::LauFitNtuple *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauFitNtuple >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauFitNtuple", ::LauFitNtuple::Class_Version(), "LauFitNtuple.hh", 58,
                  typeid(::LauFitNtuple), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauFitNtuple::Dictionary, isa_proxy, 4,
                  sizeof(::LauFitNtuple) );
      instance.SetDelete(&delete_LauFitNtuple);
      instance.SetDeleteArray(&deleteArray_LauFitNtuple);
      instance.SetDestructor(&destruct_LauFitNtuple);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauFitNtuple*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauFitNtuple*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauFitNtuple*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LauPrint(void *p = nullptr);
   static void *newArray_LauPrint(Long_t size, void *p);
   static void delete_LauPrint(void *p);
   static void deleteArray_LauPrint(void *p);
   static void destruct_LauPrint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauPrint*)
   {
      ::LauPrint *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauPrint >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauPrint", ::LauPrint::Class_Version(), "LauPrint.hh", 55,
                  typeid(::LauPrint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauPrint::Dictionary, isa_proxy, 4,
                  sizeof(::LauPrint) );
      instance.SetNew(&new_LauPrint);
      instance.SetNewArray(&newArray_LauPrint);
      instance.SetDelete(&delete_LauPrint);
      instance.SetDeleteArray(&deleteArray_LauPrint);
      instance.SetDestructor(&destruct_LauPrint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauPrint*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauPrint*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauPrint*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauFitter*)
   {
      ::LauFitter *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauFitter >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauFitter", ::LauFitter::Class_Version(), "LauFitter.hh", 47,
                  typeid(::LauFitter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauFitter::Dictionary, isa_proxy, 4,
                  sizeof(::LauFitter) );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauFitter*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauFitter*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauFitter*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauFlatNR(void *p);
   static void deleteArray_LauFlatNR(void *p);
   static void destruct_LauFlatNR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauFlatNR*)
   {
      ::LauFlatNR *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauFlatNR >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauFlatNR", ::LauFlatNR::Class_Version(), "LauFlatNR.hh", 44,
                  typeid(::LauFlatNR), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauFlatNR::Dictionary, isa_proxy, 4,
                  sizeof(::LauFlatNR) );
      instance.SetDelete(&delete_LauFlatNR);
      instance.SetDeleteArray(&deleteArray_LauFlatNR);
      instance.SetDestructor(&destruct_LauFlatNR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauFlatNR*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauFlatNR*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauFlatNR*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauFlatteRes(void *p);
   static void deleteArray_LauFlatteRes(void *p);
   static void destruct_LauFlatteRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauFlatteRes*)
   {
      ::LauFlatteRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauFlatteRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauFlatteRes", ::LauFlatteRes::Class_Version(), "LauFlatteRes.hh", 45,
                  typeid(::LauFlatteRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauFlatteRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauFlatteRes) );
      instance.SetDelete(&delete_LauFlatteRes);
      instance.SetDeleteArray(&deleteArray_LauFlatteRes);
      instance.SetDestructor(&destruct_LauFlatteRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauFlatteRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauFlatteRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauFlatteRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauGaussIncohRes(void *p);
   static void deleteArray_LauGaussIncohRes(void *p);
   static void destruct_LauGaussIncohRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauGaussIncohRes*)
   {
      ::LauGaussIncohRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauGaussIncohRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauGaussIncohRes", ::LauGaussIncohRes::Class_Version(), "LauGaussIncohRes.hh", 46,
                  typeid(::LauGaussIncohRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauGaussIncohRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauGaussIncohRes) );
      instance.SetDelete(&delete_LauGaussIncohRes);
      instance.SetDeleteArray(&deleteArray_LauGaussIncohRes);
      instance.SetDestructor(&destruct_LauGaussIncohRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauGaussIncohRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauGaussIncohRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauGaussIncohRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauGaussPdf(void *p);
   static void deleteArray_LauGaussPdf(void *p);
   static void destruct_LauGaussPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauGaussPdf*)
   {
      ::LauGaussPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauGaussPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauGaussPdf", ::LauGaussPdf::Class_Version(), "LauGaussPdf.hh", 47,
                  typeid(::LauGaussPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauGaussPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauGaussPdf) );
      instance.SetDelete(&delete_LauGaussPdf);
      instance.SetDeleteArray(&deleteArray_LauGaussPdf);
      instance.SetDestructor(&destruct_LauGaussPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauGaussPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauGaussPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauGaussPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauGenNtuple(void *p);
   static void deleteArray_LauGenNtuple(void *p);
   static void destruct_LauGenNtuple(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauGenNtuple*)
   {
      ::LauGenNtuple *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauGenNtuple >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauGenNtuple", ::LauGenNtuple::Class_Version(), "LauGenNtuple.hh", 46,
                  typeid(::LauGenNtuple), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauGenNtuple::Dictionary, isa_proxy, 4,
                  sizeof(::LauGenNtuple) );
      instance.SetDelete(&delete_LauGenNtuple);
      instance.SetDeleteArray(&deleteArray_LauGenNtuple);
      instance.SetDestructor(&destruct_LauGenNtuple);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauGenNtuple*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauGenNtuple*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauGenNtuple*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauGounarisSakuraiRes(void *p);
   static void deleteArray_LauGounarisSakuraiRes(void *p);
   static void destruct_LauGounarisSakuraiRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauGounarisSakuraiRes*)
   {
      ::LauGounarisSakuraiRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauGounarisSakuraiRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauGounarisSakuraiRes", ::LauGounarisSakuraiRes::Class_Version(), "LauGounarisSakuraiRes.hh", 45,
                  typeid(::LauGounarisSakuraiRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauGounarisSakuraiRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauGounarisSakuraiRes) );
      instance.SetDelete(&delete_LauGounarisSakuraiRes);
      instance.SetDeleteArray(&deleteArray_LauGounarisSakuraiRes);
      instance.SetDestructor(&destruct_LauGounarisSakuraiRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauGounarisSakuraiRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauGounarisSakuraiRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauGounarisSakuraiRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LauIntegrals(void *p = nullptr);
   static void *newArray_LauIntegrals(Long_t size, void *p);
   static void delete_LauIntegrals(void *p);
   static void deleteArray_LauIntegrals(void *p);
   static void destruct_LauIntegrals(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauIntegrals*)
   {
      ::LauIntegrals *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauIntegrals >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauIntegrals", ::LauIntegrals::Class_Version(), "LauIntegrals.hh", 44,
                  typeid(::LauIntegrals), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauIntegrals::Dictionary, isa_proxy, 4,
                  sizeof(::LauIntegrals) );
      instance.SetNew(&new_LauIntegrals);
      instance.SetNewArray(&newArray_LauIntegrals);
      instance.SetDelete(&delete_LauIntegrals);
      instance.SetDeleteArray(&deleteArray_LauIntegrals);
      instance.SetDestructor(&destruct_LauIntegrals);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauIntegrals*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauIntegrals*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauIntegrals*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauIsobarDynamics(void *p);
   static void deleteArray_LauIsobarDynamics(void *p);
   static void destruct_LauIsobarDynamics(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauIsobarDynamics*)
   {
      ::LauIsobarDynamics *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauIsobarDynamics >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauIsobarDynamics", ::LauIsobarDynamics::Class_Version(), "LauIsobarDynamics.hh", 53,
                  typeid(::LauIsobarDynamics), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauIsobarDynamics::Dictionary, isa_proxy, 4,
                  sizeof(::LauIsobarDynamics) );
      instance.SetDelete(&delete_LauIsobarDynamics);
      instance.SetDeleteArray(&deleteArray_LauIsobarDynamics);
      instance.SetDestructor(&destruct_LauIsobarDynamics);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauIsobarDynamics*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauIsobarDynamics*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauIsobarDynamics*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauKMatrixProdPole(void *p);
   static void deleteArray_LauKMatrixProdPole(void *p);
   static void destruct_LauKMatrixProdPole(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauKMatrixProdPole*)
   {
      ::LauKMatrixProdPole *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauKMatrixProdPole >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauKMatrixProdPole", ::LauKMatrixProdPole::Class_Version(), "LauKMatrixProdPole.hh", 45,
                  typeid(::LauKMatrixProdPole), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauKMatrixProdPole::Dictionary, isa_proxy, 4,
                  sizeof(::LauKMatrixProdPole) );
      instance.SetDelete(&delete_LauKMatrixProdPole);
      instance.SetDeleteArray(&deleteArray_LauKMatrixProdPole);
      instance.SetDestructor(&destruct_LauKMatrixProdPole);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauKMatrixProdPole*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauKMatrixProdPole*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauKMatrixProdPole*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauKMatrixProdSVP(void *p);
   static void deleteArray_LauKMatrixProdSVP(void *p);
   static void destruct_LauKMatrixProdSVP(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauKMatrixProdSVP*)
   {
      ::LauKMatrixProdSVP *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauKMatrixProdSVP >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauKMatrixProdSVP", ::LauKMatrixProdSVP::Class_Version(), "LauKMatrixProdSVP.hh", 45,
                  typeid(::LauKMatrixProdSVP), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauKMatrixProdSVP::Dictionary, isa_proxy, 4,
                  sizeof(::LauKMatrixProdSVP) );
      instance.SetDelete(&delete_LauKMatrixProdSVP);
      instance.SetDeleteArray(&deleteArray_LauKMatrixProdSVP);
      instance.SetDestructor(&destruct_LauKMatrixProdSVP);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauKMatrixProdSVP*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauKMatrixProdSVP*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauKMatrixProdSVP*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauKMatrixPropFactory(void *p);
   static void deleteArray_LauKMatrixPropFactory(void *p);
   static void destruct_LauKMatrixPropFactory(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauKMatrixPropFactory*)
   {
      ::LauKMatrixPropFactory *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauKMatrixPropFactory >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauKMatrixPropFactory", ::LauKMatrixPropFactory::Class_Version(), "LauKMatrixPropFactory.hh", 43,
                  typeid(::LauKMatrixPropFactory), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauKMatrixPropFactory::Dictionary, isa_proxy, 4,
                  sizeof(::LauKMatrixPropFactory) );
      instance.SetDelete(&delete_LauKMatrixPropFactory);
      instance.SetDeleteArray(&deleteArray_LauKMatrixPropFactory);
      instance.SetDestructor(&destruct_LauKMatrixPropFactory);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauKMatrixPropFactory*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauKMatrixPropFactory*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauKMatrixPropFactory*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauResonanceMaker*)
   {
      ::LauResonanceMaker *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauResonanceMaker >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauResonanceMaker", ::LauResonanceMaker::Class_Version(), "LauResonanceMaker.hh", 49,
                  typeid(::LauResonanceMaker), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauResonanceMaker::Dictionary, isa_proxy, 4,
                  sizeof(::LauResonanceMaker) );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauResonanceMaker*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauResonanceMaker*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauResonanceMaker*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauResonanceInfo(void *p);
   static void deleteArray_LauResonanceInfo(void *p);
   static void destruct_LauResonanceInfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauResonanceInfo*)
   {
      ::LauResonanceInfo *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauResonanceInfo >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauResonanceInfo", ::LauResonanceInfo::Class_Version(), "LauResonanceInfo.hh", 46,
                  typeid(::LauResonanceInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauResonanceInfo::Dictionary, isa_proxy, 4,
                  sizeof(::LauResonanceInfo) );
      instance.SetDelete(&delete_LauResonanceInfo);
      instance.SetDeleteArray(&deleteArray_LauResonanceInfo);
      instance.SetDestructor(&destruct_LauResonanceInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauResonanceInfo*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauResonanceInfo*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauResonanceInfo*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauKMatrixPropagator(void *p);
   static void deleteArray_LauKMatrixPropagator(void *p);
   static void destruct_LauKMatrixPropagator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauKMatrixPropagator*)
   {
      ::LauKMatrixPropagator *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauKMatrixPropagator >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauKMatrixPropagator", ::LauKMatrixPropagator::Class_Version(), "LauKMatrixPropagator.hh", 54,
                  typeid(::LauKMatrixPropagator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauKMatrixPropagator::Dictionary, isa_proxy, 4,
                  sizeof(::LauKMatrixPropagator) );
      instance.SetDelete(&delete_LauKMatrixPropagator);
      instance.SetDeleteArray(&deleteArray_LauKMatrixPropagator);
      instance.SetDestructor(&destruct_LauKMatrixPropagator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauKMatrixPropagator*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauKMatrixPropagator*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauKMatrixPropagator*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauKappaRes(void *p);
   static void deleteArray_LauKappaRes(void *p);
   static void destruct_LauKappaRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauKappaRes*)
   {
      ::LauKappaRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauKappaRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauKappaRes", ::LauKappaRes::Class_Version(), "LauKappaRes.hh", 46,
                  typeid(::LauKappaRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauKappaRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauKappaRes) );
      instance.SetDelete(&delete_LauKappaRes);
      instance.SetDeleteArray(&deleteArray_LauKappaRes);
      instance.SetDestructor(&destruct_LauKappaRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauKappaRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauKappaRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauKappaRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauLASSBWRes(void *p);
   static void deleteArray_LauLASSBWRes(void *p);
   static void destruct_LauLASSBWRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauLASSBWRes*)
   {
      ::LauLASSBWRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauLASSBWRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauLASSBWRes", ::LauLASSBWRes::Class_Version(), "LauLASSBWRes.hh", 45,
                  typeid(::LauLASSBWRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauLASSBWRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauLASSBWRes) );
      instance.SetDelete(&delete_LauLASSBWRes);
      instance.SetDeleteArray(&deleteArray_LauLASSBWRes);
      instance.SetDestructor(&destruct_LauLASSBWRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauLASSBWRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauLASSBWRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauLASSBWRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauLASSNRRes(void *p);
   static void deleteArray_LauLASSNRRes(void *p);
   static void destruct_LauLASSNRRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauLASSNRRes*)
   {
      ::LauLASSNRRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauLASSNRRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauLASSNRRes", ::LauLASSNRRes::Class_Version(), "LauLASSNRRes.hh", 45,
                  typeid(::LauLASSNRRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauLASSNRRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauLASSNRRes) );
      instance.SetDelete(&delete_LauLASSNRRes);
      instance.SetDeleteArray(&deleteArray_LauLASSNRRes);
      instance.SetDestructor(&destruct_LauLASSNRRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauLASSNRRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauLASSNRRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauLASSNRRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauLASSRes(void *p);
   static void deleteArray_LauLASSRes(void *p);
   static void destruct_LauLASSRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauLASSRes*)
   {
      ::LauLASSRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauLASSRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauLASSRes", ::LauLASSRes::Class_Version(), "LauLASSRes.hh", 45,
                  typeid(::LauLASSRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauLASSRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauLASSRes) );
      instance.SetDelete(&delete_LauLASSRes);
      instance.SetDeleteArray(&deleteArray_LauLASSRes);
      instance.SetDestructor(&destruct_LauLASSRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauLASSRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauLASSRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauLASSRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauLinearPdf(void *p);
   static void deleteArray_LauLinearPdf(void *p);
   static void destruct_LauLinearPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauLinearPdf*)
   {
      ::LauLinearPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauLinearPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauLinearPdf", ::LauLinearPdf::Class_Version(), "LauLinearPdf.hh", 44,
                  typeid(::LauLinearPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauLinearPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauLinearPdf) );
      instance.SetDelete(&delete_LauLinearPdf);
      instance.SetDeleteArray(&deleteArray_LauLinearPdf);
      instance.SetDestructor(&destruct_LauLinearPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauLinearPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauLinearPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauLinearPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauMagPhaseCPCoeffSet(void *p);
   static void deleteArray_LauMagPhaseCPCoeffSet(void *p);
   static void destruct_LauMagPhaseCPCoeffSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauMagPhaseCPCoeffSet*)
   {
      ::LauMagPhaseCPCoeffSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauMagPhaseCPCoeffSet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauMagPhaseCPCoeffSet", ::LauMagPhaseCPCoeffSet::Class_Version(), "LauMagPhaseCPCoeffSet.hh", 53,
                  typeid(::LauMagPhaseCPCoeffSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauMagPhaseCPCoeffSet::Dictionary, isa_proxy, 4,
                  sizeof(::LauMagPhaseCPCoeffSet) );
      instance.SetDelete(&delete_LauMagPhaseCPCoeffSet);
      instance.SetDeleteArray(&deleteArray_LauMagPhaseCPCoeffSet);
      instance.SetDestructor(&destruct_LauMagPhaseCPCoeffSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauMagPhaseCPCoeffSet*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauMagPhaseCPCoeffSet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauMagPhaseCPCoeffSet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauMagPhaseCoeffSet(void *p);
   static void deleteArray_LauMagPhaseCoeffSet(void *p);
   static void destruct_LauMagPhaseCoeffSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauMagPhaseCoeffSet*)
   {
      ::LauMagPhaseCoeffSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauMagPhaseCoeffSet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauMagPhaseCoeffSet", ::LauMagPhaseCoeffSet::Class_Version(), "LauMagPhaseCoeffSet.hh", 49,
                  typeid(::LauMagPhaseCoeffSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauMagPhaseCoeffSet::Dictionary, isa_proxy, 4,
                  sizeof(::LauMagPhaseCoeffSet) );
      instance.SetDelete(&delete_LauMagPhaseCoeffSet);
      instance.SetDeleteArray(&deleteArray_LauMagPhaseCoeffSet);
      instance.SetDestructor(&destruct_LauMagPhaseCoeffSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauMagPhaseCoeffSet*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauMagPhaseCoeffSet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauMagPhaseCoeffSet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauMergeDataFiles(void *p);
   static void deleteArray_LauMergeDataFiles(void *p);
   static void destruct_LauMergeDataFiles(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauMergeDataFiles*)
   {
      ::LauMergeDataFiles *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauMergeDataFiles >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauMergeDataFiles", ::LauMergeDataFiles::Class_Version(), "LauMergeDataFiles.hh", 43,
                  typeid(::LauMergeDataFiles), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauMergeDataFiles::Dictionary, isa_proxy, 4,
                  sizeof(::LauMergeDataFiles) );
      instance.SetDelete(&delete_LauMergeDataFiles);
      instance.SetDeleteArray(&deleteArray_LauMergeDataFiles);
      instance.SetDestructor(&destruct_LauMergeDataFiles);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauMergeDataFiles*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauMergeDataFiles*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauMergeDataFiles*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauMinuit(void *p);
   static void deleteArray_LauMinuit(void *p);
   static void destruct_LauMinuit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauMinuit*)
   {
      ::LauMinuit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauMinuit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauMinuit", ::LauMinuit::Class_Version(), "LauMinuit.hh", 51,
                  typeid(::LauMinuit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauMinuit::Dictionary, isa_proxy, 4,
                  sizeof(::LauMinuit) );
      instance.SetDelete(&delete_LauMinuit);
      instance.SetDeleteArray(&deleteArray_LauMinuit);
      instance.SetDestructor(&destruct_LauMinuit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauMinuit*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauMinuit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauMinuit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauModIndPartWaveMagPhase(void *p);
   static void deleteArray_LauModIndPartWaveMagPhase(void *p);
   static void destruct_LauModIndPartWaveMagPhase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauModIndPartWaveMagPhase*)
   {
      ::LauModIndPartWaveMagPhase *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauModIndPartWaveMagPhase >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauModIndPartWaveMagPhase", ::LauModIndPartWaveMagPhase::Class_Version(), "LauModIndPartWaveMagPhase.hh", 45,
                  typeid(::LauModIndPartWaveMagPhase), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauModIndPartWaveMagPhase::Dictionary, isa_proxy, 4,
                  sizeof(::LauModIndPartWaveMagPhase) );
      instance.SetDelete(&delete_LauModIndPartWaveMagPhase);
      instance.SetDeleteArray(&deleteArray_LauModIndPartWaveMagPhase);
      instance.SetDestructor(&destruct_LauModIndPartWaveMagPhase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauModIndPartWaveMagPhase*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauModIndPartWaveMagPhase*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauModIndPartWaveMagPhase*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauModIndPartWaveRealImag(void *p);
   static void deleteArray_LauModIndPartWaveRealImag(void *p);
   static void destruct_LauModIndPartWaveRealImag(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauModIndPartWaveRealImag*)
   {
      ::LauModIndPartWaveRealImag *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauModIndPartWaveRealImag >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauModIndPartWaveRealImag", ::LauModIndPartWaveRealImag::Class_Version(), "LauModIndPartWaveRealImag.hh", 45,
                  typeid(::LauModIndPartWaveRealImag), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauModIndPartWaveRealImag::Dictionary, isa_proxy, 4,
                  sizeof(::LauModIndPartWaveRealImag) );
      instance.SetDelete(&delete_LauModIndPartWaveRealImag);
      instance.SetDeleteArray(&deleteArray_LauModIndPartWaveRealImag);
      instance.SetDestructor(&destruct_LauModIndPartWaveRealImag);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauModIndPartWaveRealImag*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauModIndPartWaveRealImag*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauModIndPartWaveRealImag*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauNRAmplitude(void *p);
   static void deleteArray_LauNRAmplitude(void *p);
   static void destruct_LauNRAmplitude(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauNRAmplitude*)
   {
      ::LauNRAmplitude *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauNRAmplitude >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauNRAmplitude", ::LauNRAmplitude::Class_Version(), "LauNRAmplitude.hh", 47,
                  typeid(::LauNRAmplitude), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauNRAmplitude::Dictionary, isa_proxy, 4,
                  sizeof(::LauNRAmplitude) );
      instance.SetDelete(&delete_LauNRAmplitude);
      instance.SetDeleteArray(&deleteArray_LauNRAmplitude);
      instance.SetDestructor(&destruct_LauNRAmplitude);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauNRAmplitude*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauNRAmplitude*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauNRAmplitude*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauNovosibirskPdf(void *p);
   static void deleteArray_LauNovosibirskPdf(void *p);
   static void destruct_LauNovosibirskPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauNovosibirskPdf*)
   {
      ::LauNovosibirskPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauNovosibirskPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauNovosibirskPdf", ::LauNovosibirskPdf::Class_Version(), "LauNovosibirskPdf.hh", 45,
                  typeid(::LauNovosibirskPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauNovosibirskPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauNovosibirskPdf) );
      instance.SetDelete(&delete_LauNovosibirskPdf);
      instance.SetDeleteArray(&deleteArray_LauNovosibirskPdf);
      instance.SetDestructor(&destruct_LauNovosibirskPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauNovosibirskPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauNovosibirskPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauNovosibirskPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauParametricStepFuncPdf(void *p);
   static void deleteArray_LauParametricStepFuncPdf(void *p);
   static void destruct_LauParametricStepFuncPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauParametricStepFuncPdf*)
   {
      ::LauParametricStepFuncPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauParametricStepFuncPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauParametricStepFuncPdf", ::LauParametricStepFuncPdf::Class_Version(), "LauParametricStepFuncPdf.hh", 65,
                  typeid(::LauParametricStepFuncPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauParametricStepFuncPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauParametricStepFuncPdf) );
      instance.SetDelete(&delete_LauParametricStepFuncPdf);
      instance.SetDeleteArray(&deleteArray_LauParametricStepFuncPdf);
      instance.SetDestructor(&destruct_LauParametricStepFuncPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauParametricStepFuncPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauParametricStepFuncPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauParametricStepFuncPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauParticlePDG(void *p);
   static void deleteArray_LauParticlePDG(void *p);
   static void destruct_LauParticlePDG(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauParticlePDG*)
   {
      ::LauParticlePDG *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauParticlePDG >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauParticlePDG", ::LauParticlePDG::Class_Version(), "LauParticlePDG.hh", 43,
                  typeid(::LauParticlePDG), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauParticlePDG::Dictionary, isa_proxy, 4,
                  sizeof(::LauParticlePDG) );
      instance.SetDelete(&delete_LauParticlePDG);
      instance.SetDeleteArray(&deleteArray_LauParticlePDG);
      instance.SetDestructor(&destruct_LauParticlePDG);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauParticlePDG*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauParticlePDG*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauParticlePDG*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauPolNR(void *p);
   static void deleteArray_LauPolNR(void *p);
   static void destruct_LauPolNR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauPolNR*)
   {
      ::LauPolNR *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauPolNR >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauPolNR", ::LauPolNR::Class_Version(), "LauPolNR.hh", 47,
                  typeid(::LauPolNR), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauPolNR::Dictionary, isa_proxy, 4,
                  sizeof(::LauPolNR) );
      instance.SetDelete(&delete_LauPolNR);
      instance.SetDeleteArray(&deleteArray_LauPolNR);
      instance.SetDestructor(&destruct_LauPolNR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauPolNR*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauPolNR*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauPolNR*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauPolarFormFactorNR(void *p);
   static void deleteArray_LauPolarFormFactorNR(void *p);
   static void destruct_LauPolarFormFactorNR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauPolarFormFactorNR*)
   {
      ::LauPolarFormFactorNR *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauPolarFormFactorNR >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauPolarFormFactorNR", ::LauPolarFormFactorNR::Class_Version(), "LauPolarFormFactorNR.hh", 49,
                  typeid(::LauPolarFormFactorNR), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauPolarFormFactorNR::Dictionary, isa_proxy, 4,
                  sizeof(::LauPolarFormFactorNR) );
      instance.SetDelete(&delete_LauPolarFormFactorNR);
      instance.SetDeleteArray(&deleteArray_LauPolarFormFactorNR);
      instance.SetDestructor(&destruct_LauPolarFormFactorNR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauPolarFormFactorNR*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauPolarFormFactorNR*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauPolarFormFactorNR*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauPolarFormFactorSymNR(void *p);
   static void deleteArray_LauPolarFormFactorSymNR(void *p);
   static void destruct_LauPolarFormFactorSymNR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauPolarFormFactorSymNR*)
   {
      ::LauPolarFormFactorSymNR *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauPolarFormFactorSymNR >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauPolarFormFactorSymNR", ::LauPolarFormFactorSymNR::Class_Version(), "LauPolarFormFactorSymNR.hh", 50,
                  typeid(::LauPolarFormFactorSymNR), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauPolarFormFactorSymNR::Dictionary, isa_proxy, 4,
                  sizeof(::LauPolarFormFactorSymNR) );
      instance.SetDelete(&delete_LauPolarFormFactorSymNR);
      instance.SetDeleteArray(&deleteArray_LauPolarFormFactorSymNR);
      instance.SetDestructor(&destruct_LauPolarFormFactorSymNR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauPolarFormFactorSymNR*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauPolarFormFactorSymNR*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauPolarFormFactorSymNR*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauPolarGammaCPCoeffSet(void *p);
   static void deleteArray_LauPolarGammaCPCoeffSet(void *p);
   static void destruct_LauPolarGammaCPCoeffSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauPolarGammaCPCoeffSet*)
   {
      ::LauPolarGammaCPCoeffSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauPolarGammaCPCoeffSet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauPolarGammaCPCoeffSet", ::LauPolarGammaCPCoeffSet::Class_Version(), "LauPolarGammaCPCoeffSet.hh", 54,
                  typeid(::LauPolarGammaCPCoeffSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauPolarGammaCPCoeffSet::Dictionary, isa_proxy, 4,
                  sizeof(::LauPolarGammaCPCoeffSet) );
      instance.SetDelete(&delete_LauPolarGammaCPCoeffSet);
      instance.SetDeleteArray(&deleteArray_LauPolarGammaCPCoeffSet);
      instance.SetDestructor(&destruct_LauPolarGammaCPCoeffSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauPolarGammaCPCoeffSet*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauPolarGammaCPCoeffSet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauPolarGammaCPCoeffSet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauPoleRes(void *p);
   static void deleteArray_LauPoleRes(void *p);
   static void destruct_LauPoleRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauPoleRes*)
   {
      ::LauPoleRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauPoleRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauPoleRes", ::LauPoleRes::Class_Version(), "LauPoleRes.hh", 46,
                  typeid(::LauPoleRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauPoleRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauPoleRes) );
      instance.SetDelete(&delete_LauPoleRes);
      instance.SetDeleteArray(&deleteArray_LauPoleRes);
      instance.SetDestructor(&destruct_LauPoleRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauPoleRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauPoleRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauPoleRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauRealImagCPCoeffSet(void *p);
   static void deleteArray_LauRealImagCPCoeffSet(void *p);
   static void destruct_LauRealImagCPCoeffSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauRealImagCPCoeffSet*)
   {
      ::LauRealImagCPCoeffSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauRealImagCPCoeffSet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauRealImagCPCoeffSet", ::LauRealImagCPCoeffSet::Class_Version(), "LauRealImagCPCoeffSet.hh", 51,
                  typeid(::LauRealImagCPCoeffSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauRealImagCPCoeffSet::Dictionary, isa_proxy, 4,
                  sizeof(::LauRealImagCPCoeffSet) );
      instance.SetDelete(&delete_LauRealImagCPCoeffSet);
      instance.SetDeleteArray(&deleteArray_LauRealImagCPCoeffSet);
      instance.SetDestructor(&destruct_LauRealImagCPCoeffSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauRealImagCPCoeffSet*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauRealImagCPCoeffSet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauRealImagCPCoeffSet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauRealImagCoeffSet(void *p);
   static void deleteArray_LauRealImagCoeffSet(void *p);
   static void destruct_LauRealImagCoeffSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauRealImagCoeffSet*)
   {
      ::LauRealImagCoeffSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauRealImagCoeffSet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauRealImagCoeffSet", ::LauRealImagCoeffSet::Class_Version(), "LauRealImagCoeffSet.hh", 49,
                  typeid(::LauRealImagCoeffSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauRealImagCoeffSet::Dictionary, isa_proxy, 4,
                  sizeof(::LauRealImagCoeffSet) );
      instance.SetDelete(&delete_LauRealImagCoeffSet);
      instance.SetDeleteArray(&deleteArray_LauRealImagCoeffSet);
      instance.SetDestructor(&destruct_LauRealImagCoeffSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauRealImagCoeffSet*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauRealImagCoeffSet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauRealImagCoeffSet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauRealImagGammaCPCoeffSet(void *p);
   static void deleteArray_LauRealImagGammaCPCoeffSet(void *p);
   static void destruct_LauRealImagGammaCPCoeffSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauRealImagGammaCPCoeffSet*)
   {
      ::LauRealImagGammaCPCoeffSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauRealImagGammaCPCoeffSet >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauRealImagGammaCPCoeffSet", ::LauRealImagGammaCPCoeffSet::Class_Version(), "LauRealImagGammaCPCoeffSet.hh", 52,
                  typeid(::LauRealImagGammaCPCoeffSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauRealImagGammaCPCoeffSet::Dictionary, isa_proxy, 4,
                  sizeof(::LauRealImagGammaCPCoeffSet) );
      instance.SetDelete(&delete_LauRealImagGammaCPCoeffSet);
      instance.SetDeleteArray(&deleteArray_LauRealImagGammaCPCoeffSet);
      instance.SetDestructor(&destruct_LauRealImagGammaCPCoeffSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauRealImagGammaCPCoeffSet*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauRealImagGammaCPCoeffSet*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauRealImagGammaCPCoeffSet*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauRelBreitWignerRes(void *p);
   static void deleteArray_LauRelBreitWignerRes(void *p);
   static void destruct_LauRelBreitWignerRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauRelBreitWignerRes*)
   {
      ::LauRelBreitWignerRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauRelBreitWignerRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauRelBreitWignerRes", ::LauRelBreitWignerRes::Class_Version(), "LauRelBreitWignerRes.hh", 45,
                  typeid(::LauRelBreitWignerRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauRelBreitWignerRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauRelBreitWignerRes) );
      instance.SetDelete(&delete_LauRelBreitWignerRes);
      instance.SetDeleteArray(&deleteArray_LauRelBreitWignerRes);
      instance.SetDestructor(&destruct_LauRelBreitWignerRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauRelBreitWignerRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauRelBreitWignerRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauRelBreitWignerRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauRescattering2Res(void *p);
   static void deleteArray_LauRescattering2Res(void *p);
   static void destruct_LauRescattering2Res(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauRescattering2Res*)
   {
      ::LauRescattering2Res *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauRescattering2Res >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauRescattering2Res", ::LauRescattering2Res::Class_Version(), "LauRescattering2Res.hh", 46,
                  typeid(::LauRescattering2Res), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauRescattering2Res::Dictionary, isa_proxy, 4,
                  sizeof(::LauRescattering2Res) );
      instance.SetDelete(&delete_LauRescattering2Res);
      instance.SetDeleteArray(&deleteArray_LauRescattering2Res);
      instance.SetDestructor(&destruct_LauRescattering2Res);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauRescattering2Res*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauRescattering2Res*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauRescattering2Res*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauRescatteringRes(void *p);
   static void deleteArray_LauRescatteringRes(void *p);
   static void destruct_LauRescatteringRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauRescatteringRes*)
   {
      ::LauRescatteringRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauRescatteringRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauRescatteringRes", ::LauRescatteringRes::Class_Version(), "LauRescatteringRes.hh", 49,
                  typeid(::LauRescatteringRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauRescatteringRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauRescatteringRes) );
      instance.SetDelete(&delete_LauRescatteringRes);
      instance.SetDeleteArray(&deleteArray_LauRescatteringRes);
      instance.SetDestructor(&destruct_LauRescatteringRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauRescatteringRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauRescatteringRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauRescatteringRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauResultsExtractor(void *p);
   static void deleteArray_LauResultsExtractor(void *p);
   static void destruct_LauResultsExtractor(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauResultsExtractor*)
   {
      ::LauResultsExtractor *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauResultsExtractor >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauResultsExtractor", ::LauResultsExtractor::Class_Version(), "LauResultsExtractor.hh", 51,
                  typeid(::LauResultsExtractor), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauResultsExtractor::Dictionary, isa_proxy, 4,
                  sizeof(::LauResultsExtractor) );
      instance.SetDelete(&delete_LauResultsExtractor);
      instance.SetDeleteArray(&deleteArray_LauResultsExtractor);
      instance.SetDestructor(&destruct_LauResultsExtractor);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauResultsExtractor*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauResultsExtractor*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauResultsExtractor*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauRhoOmegaMix(void *p);
   static void deleteArray_LauRhoOmegaMix(void *p);
   static void destruct_LauRhoOmegaMix(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauRhoOmegaMix*)
   {
      ::LauRhoOmegaMix *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauRhoOmegaMix >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauRhoOmegaMix", ::LauRhoOmegaMix::Class_Version(), "LauRhoOmegaMix.hh", 50,
                  typeid(::LauRhoOmegaMix), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauRhoOmegaMix::Dictionary, isa_proxy, 4,
                  sizeof(::LauRhoOmegaMix) );
      instance.SetDelete(&delete_LauRhoOmegaMix);
      instance.SetDeleteArray(&deleteArray_LauRhoOmegaMix);
      instance.SetDestructor(&destruct_LauRhoOmegaMix);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauRhoOmegaMix*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauRhoOmegaMix*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauRhoOmegaMix*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LauScfMap(void *p = nullptr);
   static void *newArray_LauScfMap(Long_t size, void *p);
   static void delete_LauScfMap(void *p);
   static void deleteArray_LauScfMap(void *p);
   static void destruct_LauScfMap(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauScfMap*)
   {
      ::LauScfMap *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauScfMap >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauScfMap", ::LauScfMap::Class_Version(), "LauScfMap.hh", 45,
                  typeid(::LauScfMap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauScfMap::Dictionary, isa_proxy, 4,
                  sizeof(::LauScfMap) );
      instance.SetNew(&new_LauScfMap);
      instance.SetNewArray(&newArray_LauScfMap);
      instance.SetDelete(&delete_LauScfMap);
      instance.SetDeleteArray(&deleteArray_LauScfMap);
      instance.SetDestructor(&destruct_LauScfMap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauScfMap*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauScfMap*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauScfMap*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauSigmaRes(void *p);
   static void deleteArray_LauSigmaRes(void *p);
   static void destruct_LauSigmaRes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauSigmaRes*)
   {
      ::LauSigmaRes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauSigmaRes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauSigmaRes", ::LauSigmaRes::Class_Version(), "LauSigmaRes.hh", 45,
                  typeid(::LauSigmaRes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauSigmaRes::Dictionary, isa_proxy, 4,
                  sizeof(::LauSigmaRes) );
      instance.SetDelete(&delete_LauSigmaRes);
      instance.SetDeleteArray(&deleteArray_LauSigmaRes);
      instance.SetDestructor(&destruct_LauSigmaRes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauSigmaRes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauSigmaRes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauSigmaRes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauSigmoidPdf(void *p);
   static void deleteArray_LauSigmoidPdf(void *p);
   static void destruct_LauSigmoidPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauSigmoidPdf*)
   {
      ::LauSigmoidPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauSigmoidPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauSigmoidPdf", ::LauSigmoidPdf::Class_Version(), "LauSigmoidPdf.hh", 50,
                  typeid(::LauSigmoidPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauSigmoidPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauSigmoidPdf) );
      instance.SetDelete(&delete_LauSigmoidPdf);
      instance.SetDeleteArray(&deleteArray_LauSigmoidPdf);
      instance.SetDestructor(&destruct_LauSigmoidPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauSigmoidPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauSigmoidPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauSigmoidPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauSimFitCoordinator(void *p);
   static void deleteArray_LauSimFitCoordinator(void *p);
   static void destruct_LauSimFitCoordinator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauSimFitCoordinator*)
   {
      ::LauSimFitCoordinator *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauSimFitCoordinator >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauSimFitCoordinator", ::LauSimFitCoordinator::Class_Version(), "LauSimFitCoordinator.hh", 57,
                  typeid(::LauSimFitCoordinator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauSimFitCoordinator::Dictionary, isa_proxy, 4,
                  sizeof(::LauSimFitCoordinator) );
      instance.SetDelete(&delete_LauSimFitCoordinator);
      instance.SetDeleteArray(&deleteArray_LauSimFitCoordinator);
      instance.SetDestructor(&destruct_LauSimFitCoordinator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauSimFitCoordinator*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauSimFitCoordinator*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauSimFitCoordinator*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauSimpleFitModel(void *p);
   static void deleteArray_LauSimpleFitModel(void *p);
   static void destruct_LauSimpleFitModel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauSimpleFitModel*)
   {
      ::LauSimpleFitModel *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauSimpleFitModel >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauSimpleFitModel", ::LauSimpleFitModel::Class_Version(), "LauSimpleFitModel.hh", 59,
                  typeid(::LauSimpleFitModel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauSimpleFitModel::Dictionary, isa_proxy, 4,
                  sizeof(::LauSimpleFitModel) );
      instance.SetDelete(&delete_LauSimpleFitModel);
      instance.SetDeleteArray(&deleteArray_LauSimpleFitModel);
      instance.SetDestructor(&destruct_LauSimpleFitModel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauSimpleFitModel*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauSimpleFitModel*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauSimpleFitModel*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *LauString_Dictionary();
   static void LauString_TClassManip(TClass*);
   static void *new_LauString(void *p = nullptr);
   static void *newArray_LauString(Long_t size, void *p);
   static void delete_LauString(void *p);
   static void deleteArray_LauString(void *p);
   static void destruct_LauString(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauString*)
   {
      ::LauString *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::LauString));
      static ::ROOT::TGenericClassInfo 
         instance("LauString", "LauString.hh", 43,
                  typeid(::LauString), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &LauString_Dictionary, isa_proxy, 4,
                  sizeof(::LauString) );
      instance.SetNew(&new_LauString);
      instance.SetNewArray(&newArray_LauString);
      instance.SetDelete(&delete_LauString);
      instance.SetDeleteArray(&deleteArray_LauString);
      instance.SetDestructor(&destruct_LauString);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauString*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauString*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauString*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *LauString_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::LauString*>(nullptr))->GetClass();
      LauString_TClassManip(theClass);
   return theClass;
   }

   static void LauString_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void delete_LauSumPdf(void *p);
   static void deleteArray_LauSumPdf(void *p);
   static void destruct_LauSumPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauSumPdf*)
   {
      ::LauSumPdf *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauSumPdf >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauSumPdf", ::LauSumPdf::Class_Version(), "LauSumPdf.hh", 46,
                  typeid(::LauSumPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauSumPdf::Dictionary, isa_proxy, 4,
                  sizeof(::LauSumPdf) );
      instance.SetDelete(&delete_LauSumPdf);
      instance.SetDeleteArray(&deleteArray_LauSumPdf);
      instance.SetDestructor(&destruct_LauSumPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauSumPdf*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauSumPdf*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauSumPdf*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *LauTextFileParser_Dictionary();
   static void LauTextFileParser_TClassManip(TClass*);
   static void delete_LauTextFileParser(void *p);
   static void deleteArray_LauTextFileParser(void *p);
   static void destruct_LauTextFileParser(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauTextFileParser*)
   {
      ::LauTextFileParser *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::LauTextFileParser));
      static ::ROOT::TGenericClassInfo 
         instance("LauTextFileParser", "LauTextFileParser.hh", 46,
                  typeid(::LauTextFileParser), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &LauTextFileParser_Dictionary, isa_proxy, 4,
                  sizeof(::LauTextFileParser) );
      instance.SetDelete(&delete_LauTextFileParser);
      instance.SetDeleteArray(&deleteArray_LauTextFileParser);
      instance.SetDestructor(&destruct_LauTextFileParser);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauTextFileParser*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauTextFileParser*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauTextFileParser*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *LauTextFileParser_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::LauTextFileParser*>(nullptr))->GetClass();
      LauTextFileParser_TClassManip(theClass);
   return theClass;
   }

   static void LauTextFileParser_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_LauVetoes(void *p = nullptr);
   static void *newArray_LauVetoes(Long_t size, void *p);
   static void delete_LauVetoes(void *p);
   static void deleteArray_LauVetoes(void *p);
   static void destruct_LauVetoes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauVetoes*)
   {
      ::LauVetoes *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauVetoes >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauVetoes", ::LauVetoes::Class_Version(), "LauVetoes.hh", 50,
                  typeid(::LauVetoes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauVetoes::Dictionary, isa_proxy, 4,
                  sizeof(::LauVetoes) );
      instance.SetNew(&new_LauVetoes);
      instance.SetNewArray(&newArray_LauVetoes);
      instance.SetDelete(&delete_LauVetoes);
      instance.SetDeleteArray(&deleteArray_LauVetoes);
      instance.SetDestructor(&destruct_LauVetoes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauVetoes*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauVetoes*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauVetoes*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LauWeightedSumEffModel(void *p);
   static void deleteArray_LauWeightedSumEffModel(void *p);
   static void destruct_LauWeightedSumEffModel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LauWeightedSumEffModel*)
   {
      ::LauWeightedSumEffModel *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LauWeightedSumEffModel >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("LauWeightedSumEffModel", ::LauWeightedSumEffModel::Class_Version(), "LauWeightedSumEffModel.hh", 48,
                  typeid(::LauWeightedSumEffModel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LauWeightedSumEffModel::Dictionary, isa_proxy, 4,
                  sizeof(::LauWeightedSumEffModel) );
      instance.SetDelete(&delete_LauWeightedSumEffModel);
      instance.SetDeleteArray(&deleteArray_LauWeightedSumEffModel);
      instance.SetDestructor(&destruct_LauWeightedSumEffModel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LauWeightedSumEffModel*)
   {
      return GenerateInitInstanceLocal(static_cast<::LauWeightedSumEffModel*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::LauWeightedSumEffModel*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Lau1DCubicSpline::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau1DCubicSpline::Class_Name()
{
   return "Lau1DCubicSpline";
}

//______________________________________________________________________________
const char *Lau1DCubicSpline::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau1DCubicSpline*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau1DCubicSpline::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau1DCubicSpline*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau1DCubicSpline::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau1DCubicSpline*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau1DCubicSpline::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau1DCubicSpline*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauFitDataTree::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauFitDataTree::Class_Name()
{
   return "LauFitDataTree";
}

//______________________________________________________________________________
const char *LauFitDataTree::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFitDataTree*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauFitDataTree::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFitDataTree*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauFitDataTree::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFitDataTree*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauFitDataTree::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFitDataTree*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauAbsRValue::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauAbsRValue::Class_Name()
{
   return "LauAbsRValue";
}

//______________________________________________________________________________
const char *LauAbsRValue::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsRValue*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauAbsRValue::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsRValue*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauAbsRValue::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsRValue*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauAbsRValue::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsRValue*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauBlind::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauBlind::Class_Name()
{
   return "LauBlind";
}

//______________________________________________________________________________
const char *LauBlind::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBlind*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauBlind::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBlind*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauBlind::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBlind*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauBlind::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBlind*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauParameter::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauParameter::Class_Name()
{
   return "LauParameter";
}

//______________________________________________________________________________
const char *LauParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauParameter*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauParameter*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauParameter*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauParameter*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauAbsPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauAbsPdf::Class_Name()
{
   return "LauAbsPdf";
}

//______________________________________________________________________________
const char *LauAbsPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauAbsPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauAbsPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauAbsPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Lau1DHistPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau1DHistPdf::Class_Name()
{
   return "Lau1DHistPdf";
}

//______________________________________________________________________________
const char *Lau1DHistPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau1DHistPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau1DHistPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau1DHistPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau1DHistPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau1DHistPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau1DHistPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau1DHistPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Lau2DAbsDP::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau2DAbsDP::Class_Name()
{
   return "Lau2DAbsDP";
}

//______________________________________________________________________________
const char *Lau2DAbsDP::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsDP*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau2DAbsDP::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsDP*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau2DAbsDP::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsDP*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau2DAbsDP::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsDP*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Lau2DAbsDPPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau2DAbsDPPdf::Class_Name()
{
   return "Lau2DAbsDPPdf";
}

//______________________________________________________________________________
const char *Lau2DAbsDPPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsDPPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau2DAbsDPPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsDPPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau2DAbsDPPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsDPPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau2DAbsDPPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsDPPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Lau2DAbsHistDP::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau2DAbsHistDP::Class_Name()
{
   return "Lau2DAbsHistDP";
}

//______________________________________________________________________________
const char *Lau2DAbsHistDP::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsHistDP*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau2DAbsHistDP::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsHistDP*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau2DAbsHistDP::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsHistDP*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau2DAbsHistDP::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsHistDP*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Lau2DAbsHistDPPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau2DAbsHistDPPdf::Class_Name()
{
   return "Lau2DAbsHistDPPdf";
}

//______________________________________________________________________________
const char *Lau2DAbsHistDPPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsHistDPPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau2DAbsHistDPPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsHistDPPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau2DAbsHistDPPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsHistDPPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau2DAbsHistDPPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DAbsHistDPPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Lau2DCubicSpline::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau2DCubicSpline::Class_Name()
{
   return "Lau2DCubicSpline";
}

//______________________________________________________________________________
const char *Lau2DCubicSpline::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DCubicSpline*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau2DCubicSpline::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DCubicSpline*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau2DCubicSpline::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DCubicSpline*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau2DCubicSpline::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DCubicSpline*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Lau2DHistDP::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau2DHistDP::Class_Name()
{
   return "Lau2DHistDP";
}

//______________________________________________________________________________
const char *Lau2DHistDP::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistDP*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau2DHistDP::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistDP*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau2DHistDP::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistDP*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau2DHistDP::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistDP*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Lau2DHistDPPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau2DHistDPPdf::Class_Name()
{
   return "Lau2DHistDPPdf";
}

//______________________________________________________________________________
const char *Lau2DHistDPPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistDPPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau2DHistDPPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistDPPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau2DHistDPPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistDPPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau2DHistDPPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistDPPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Lau2DHistPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau2DHistPdf::Class_Name()
{
   return "Lau2DHistPdf";
}

//______________________________________________________________________________
const char *Lau2DHistPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau2DHistPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau2DHistPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau2DHistPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DHistPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Lau2DSplineDP::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau2DSplineDP::Class_Name()
{
   return "Lau2DSplineDP";
}

//______________________________________________________________________________
const char *Lau2DSplineDP::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DSplineDP*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau2DSplineDP::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DSplineDP*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau2DSplineDP::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DSplineDP*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau2DSplineDP::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DSplineDP*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Lau2DSplineDPPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Lau2DSplineDPPdf::Class_Name()
{
   return "Lau2DSplineDPPdf";
}

//______________________________________________________________________________
const char *Lau2DSplineDPPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DSplineDPPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Lau2DSplineDPPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Lau2DSplineDPPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Lau2DSplineDPPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DSplineDPPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Lau2DSplineDPPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Lau2DSplineDPPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauAbsFitter::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauAbsFitter::Class_Name()
{
   return "LauAbsFitter";
}

//______________________________________________________________________________
const char *LauAbsFitter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsFitter*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauAbsFitter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsFitter*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauAbsFitter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsFitter*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauAbsFitter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsFitter*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauFormulaPar::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauFormulaPar::Class_Name()
{
   return "LauFormulaPar";
}

//______________________________________________________________________________
const char *LauFormulaPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFormulaPar*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauFormulaPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFormulaPar*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauFormulaPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFormulaPar*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauFormulaPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFormulaPar*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauFitObject::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauFitObject::Class_Name()
{
   return "LauFitObject";
}

//______________________________________________________________________________
const char *LauFitObject::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFitObject*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauFitObject::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFitObject*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauFitObject::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFitObject*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauFitObject::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFitObject*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauASqMaxFinder::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauASqMaxFinder::Class_Name()
{
   return "LauASqMaxFinder";
}

//______________________________________________________________________________
const char *LauASqMaxFinder::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauASqMaxFinder*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauASqMaxFinder::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauASqMaxFinder*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauASqMaxFinder::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauASqMaxFinder*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauASqMaxFinder::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauASqMaxFinder*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauAbsBkgndDPModel::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauAbsBkgndDPModel::Class_Name()
{
   return "LauAbsBkgndDPModel";
}

//______________________________________________________________________________
const char *LauAbsBkgndDPModel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsBkgndDPModel*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauAbsBkgndDPModel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsBkgndDPModel*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauAbsBkgndDPModel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsBkgndDPModel*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauAbsBkgndDPModel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsBkgndDPModel*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauAbsCoeffSet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauAbsCoeffSet::Class_Name()
{
   return "LauAbsCoeffSet";
}

//______________________________________________________________________________
const char *LauAbsCoeffSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsCoeffSet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauAbsCoeffSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsCoeffSet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauAbsCoeffSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsCoeffSet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauAbsCoeffSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsCoeffSet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauAbsEffModel::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauAbsEffModel::Class_Name()
{
   return "LauAbsEffModel";
}

//______________________________________________________________________________
const char *LauAbsEffModel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsEffModel*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauAbsEffModel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsEffModel*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauAbsEffModel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsEffModel*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauAbsEffModel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsEffModel*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauComplex::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauComplex::Class_Name()
{
   return "LauComplex";
}

//______________________________________________________________________________
const char *LauComplex::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauComplex*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauComplex::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauComplex*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauComplex::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauComplex*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauComplex::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauComplex*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauSimFitTask::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauSimFitTask::Class_Name()
{
   return "LauSimFitTask";
}

//______________________________________________________________________________
const char *LauSimFitTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSimFitTask*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauSimFitTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSimFitTask*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauSimFitTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSimFitTask*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauSimFitTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSimFitTask*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauSPlot::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauSPlot::Class_Name()
{
   return "LauSPlot";
}

//______________________________________________________________________________
const char *LauSPlot::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSPlot*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauSPlot::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSPlot*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauSPlot::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSPlot*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauSPlot::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSPlot*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauAbsFitModel::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauAbsFitModel::Class_Name()
{
   return "LauAbsFitModel";
}

//______________________________________________________________________________
const char *LauAbsFitModel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsFitModel*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauAbsFitModel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsFitModel*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauAbsFitModel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsFitModel*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauAbsFitModel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsFitModel*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauBlattWeisskopfFactor::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauBlattWeisskopfFactor::Class_Name()
{
   return "LauBlattWeisskopfFactor";
}

//______________________________________________________________________________
const char *LauBlattWeisskopfFactor::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBlattWeisskopfFactor*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauBlattWeisskopfFactor::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBlattWeisskopfFactor*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauBlattWeisskopfFactor::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBlattWeisskopfFactor*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauBlattWeisskopfFactor::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBlattWeisskopfFactor*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauAbsResonance::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauAbsResonance::Class_Name()
{
   return "LauAbsResonance";
}

//______________________________________________________________________________
const char *LauAbsResonance::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsResonance*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauAbsResonance::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsResonance*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauAbsResonance::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsResonance*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauAbsResonance::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsResonance*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauAbsIncohRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauAbsIncohRes::Class_Name()
{
   return "LauAbsIncohRes";
}

//______________________________________________________________________________
const char *LauAbsIncohRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsIncohRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauAbsIncohRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsIncohRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauAbsIncohRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsIncohRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauAbsIncohRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsIncohRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauAbsModIndPartWave::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauAbsModIndPartWave::Class_Name()
{
   return "LauAbsModIndPartWave";
}

//______________________________________________________________________________
const char *LauAbsModIndPartWave::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsModIndPartWave*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauAbsModIndPartWave::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAbsModIndPartWave*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauAbsModIndPartWave::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsModIndPartWave*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauAbsModIndPartWave::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAbsModIndPartWave*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauArgusPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauArgusPdf::Class_Name()
{
   return "LauArgusPdf";
}

//______________________________________________________________________________
const char *LauArgusPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauArgusPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauArgusPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauArgusPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauArgusPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauArgusPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauArgusPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauArgusPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauAsymmCalc::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauAsymmCalc::Class_Name()
{
   return "LauAsymmCalc";
}

//______________________________________________________________________________
const char *LauAsymmCalc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAsymmCalc*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauAsymmCalc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauAsymmCalc*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauAsymmCalc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAsymmCalc*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauAsymmCalc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauAsymmCalc*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauBelleCPCoeffSet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauBelleCPCoeffSet::Class_Name()
{
   return "LauBelleCPCoeffSet";
}

//______________________________________________________________________________
const char *LauBelleCPCoeffSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBelleCPCoeffSet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauBelleCPCoeffSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBelleCPCoeffSet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauBelleCPCoeffSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBelleCPCoeffSet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauBelleCPCoeffSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBelleCPCoeffSet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauBelleNR::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauBelleNR::Class_Name()
{
   return "LauBelleNR";
}

//______________________________________________________________________________
const char *LauBelleNR::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBelleNR*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauBelleNR::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBelleNR*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauBelleNR::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBelleNR*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauBelleNR::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBelleNR*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauBelleSymNR::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauBelleSymNR::Class_Name()
{
   return "LauBelleSymNR";
}

//______________________________________________________________________________
const char *LauBelleSymNR::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBelleSymNR*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauBelleSymNR::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBelleSymNR*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauBelleSymNR::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBelleSymNR*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauBelleSymNR::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBelleSymNR*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauBifurcatedGaussPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauBifurcatedGaussPdf::Class_Name()
{
   return "LauBifurcatedGaussPdf";
}

//______________________________________________________________________________
const char *LauBifurcatedGaussPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBifurcatedGaussPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauBifurcatedGaussPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBifurcatedGaussPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauBifurcatedGaussPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBifurcatedGaussPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauBifurcatedGaussPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBifurcatedGaussPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauBkgndDPModel::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauBkgndDPModel::Class_Name()
{
   return "LauBkgndDPModel";
}

//______________________________________________________________________________
const char *LauBkgndDPModel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBkgndDPModel*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauBkgndDPModel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBkgndDPModel*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauBkgndDPModel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBkgndDPModel*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauBkgndDPModel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBkgndDPModel*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauBreitWignerRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauBreitWignerRes::Class_Name()
{
   return "LauBreitWignerRes";
}

//______________________________________________________________________________
const char *LauBreitWignerRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBreitWignerRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauBreitWignerRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauBreitWignerRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauBreitWignerRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBreitWignerRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauBreitWignerRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauBreitWignerRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauCPFitModel::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauCPFitModel::Class_Name()
{
   return "LauCPFitModel";
}

//______________________________________________________________________________
const char *LauCPFitModel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCPFitModel*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauCPFitModel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCPFitModel*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauCPFitModel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCPFitModel*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauCPFitModel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCPFitModel*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauCacheData::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauCacheData::Class_Name()
{
   return "LauCacheData";
}

//______________________________________________________________________________
const char *LauCacheData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCacheData*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauCacheData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCacheData*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauCacheData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCacheData*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauCacheData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCacheData*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauCalcChiSq::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauCalcChiSq::Class_Name()
{
   return "LauCalcChiSq";
}

//______________________________________________________________________________
const char *LauCalcChiSq::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCalcChiSq*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauCalcChiSq::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCalcChiSq*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauCalcChiSq::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCalcChiSq*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauCalcChiSq::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCalcChiSq*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauCartesianCPCoeffSet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauCartesianCPCoeffSet::Class_Name()
{
   return "LauCartesianCPCoeffSet";
}

//______________________________________________________________________________
const char *LauCartesianCPCoeffSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCartesianCPCoeffSet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauCartesianCPCoeffSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCartesianCPCoeffSet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauCartesianCPCoeffSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCartesianCPCoeffSet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauCartesianCPCoeffSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCartesianCPCoeffSet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauCartesianGammaCPCoeffSet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauCartesianGammaCPCoeffSet::Class_Name()
{
   return "LauCartesianGammaCPCoeffSet";
}

//______________________________________________________________________________
const char *LauCartesianGammaCPCoeffSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCartesianGammaCPCoeffSet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauCartesianGammaCPCoeffSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCartesianGammaCPCoeffSet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauCartesianGammaCPCoeffSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCartesianGammaCPCoeffSet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauCartesianGammaCPCoeffSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCartesianGammaCPCoeffSet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauChebychevPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauChebychevPdf::Class_Name()
{
   return "LauChebychevPdf";
}

//______________________________________________________________________________
const char *LauChebychevPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauChebychevPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauChebychevPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauChebychevPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauChebychevPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauChebychevPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauChebychevPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauChebychevPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauCleoCPCoeffSet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauCleoCPCoeffSet::Class_Name()
{
   return "LauCleoCPCoeffSet";
}

//______________________________________________________________________________
const char *LauCleoCPCoeffSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCleoCPCoeffSet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauCleoCPCoeffSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCleoCPCoeffSet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauCleoCPCoeffSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCleoCPCoeffSet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauCleoCPCoeffSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCleoCPCoeffSet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauCruijffPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauCruijffPdf::Class_Name()
{
   return "LauCruijffPdf";
}

//______________________________________________________________________________
const char *LauCruijffPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCruijffPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauCruijffPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCruijffPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauCruijffPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCruijffPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauCruijffPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCruijffPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauCrystalBallPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauCrystalBallPdf::Class_Name()
{
   return "LauCrystalBallPdf";
}

//______________________________________________________________________________
const char *LauCrystalBallPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCrystalBallPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauCrystalBallPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauCrystalBallPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauCrystalBallPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCrystalBallPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauCrystalBallPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauCrystalBallPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauDPDepBifurGaussPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauDPDepBifurGaussPdf::Class_Name()
{
   return "LauDPDepBifurGaussPdf";
}

//______________________________________________________________________________
const char *LauDPDepBifurGaussPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepBifurGaussPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauDPDepBifurGaussPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepBifurGaussPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauDPDepBifurGaussPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepBifurGaussPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauDPDepBifurGaussPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepBifurGaussPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauDPDepCruijffPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauDPDepCruijffPdf::Class_Name()
{
   return "LauDPDepCruijffPdf";
}

//______________________________________________________________________________
const char *LauDPDepCruijffPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepCruijffPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauDPDepCruijffPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepCruijffPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauDPDepCruijffPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepCruijffPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauDPDepCruijffPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepCruijffPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauDPDepGaussPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauDPDepGaussPdf::Class_Name()
{
   return "LauDPDepGaussPdf";
}

//______________________________________________________________________________
const char *LauDPDepGaussPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepGaussPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauDPDepGaussPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepGaussPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauDPDepGaussPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepGaussPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauDPDepGaussPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepGaussPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauDPDepMapPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauDPDepMapPdf::Class_Name()
{
   return "LauDPDepMapPdf";
}

//______________________________________________________________________________
const char *LauDPDepMapPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepMapPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauDPDepMapPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepMapPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauDPDepMapPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepMapPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauDPDepMapPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepMapPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauDPDepSumPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauDPDepSumPdf::Class_Name()
{
   return "LauDPDepSumPdf";
}

//______________________________________________________________________________
const char *LauDPDepSumPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepSumPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauDPDepSumPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepSumPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauDPDepSumPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepSumPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauDPDepSumPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPDepSumPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauDPPartialIntegralInfo::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauDPPartialIntegralInfo::Class_Name()
{
   return "LauDPPartialIntegralInfo";
}

//______________________________________________________________________________
const char *LauDPPartialIntegralInfo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPPartialIntegralInfo*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauDPPartialIntegralInfo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDPPartialIntegralInfo*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauDPPartialIntegralInfo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPPartialIntegralInfo*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauDPPartialIntegralInfo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDPPartialIntegralInfo*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauDabbaRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauDabbaRes::Class_Name()
{
   return "LauDabbaRes";
}

//______________________________________________________________________________
const char *LauDabbaRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDabbaRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauDabbaRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDabbaRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauDabbaRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDabbaRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauDabbaRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDabbaRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauDatabasePDG::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauDatabasePDG::Class_Name()
{
   return "LauDatabasePDG";
}

//______________________________________________________________________________
const char *LauDatabasePDG::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDatabasePDG*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauDatabasePDG::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDatabasePDG*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauDatabasePDG::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDatabasePDG*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauDatabasePDG::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDatabasePDG*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauKinematics::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauKinematics::Class_Name()
{
   return "LauKinematics";
}

//______________________________________________________________________________
const char *LauKinematics::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKinematics*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauKinematics::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKinematics*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauKinematics::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKinematics*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauKinematics::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKinematics*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauDaughters::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauDaughters::Class_Name()
{
   return "LauDaughters";
}

//______________________________________________________________________________
const char *LauDaughters::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDaughters*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauDaughters::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauDaughters*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauDaughters::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDaughters*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauDaughters::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauDaughters*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauEFKLLMRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauEFKLLMRes::Class_Name()
{
   return "LauEFKLLMRes";
}

//______________________________________________________________________________
const char *LauEFKLLMRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauEFKLLMRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauEFKLLMRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauEFKLLMRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauEFKLLMRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauEFKLLMRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauEFKLLMRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauEFKLLMRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauEffModel::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauEffModel::Class_Name()
{
   return "LauEffModel";
}

//______________________________________________________________________________
const char *LauEffModel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauEffModel*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauEffModel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauEffModel*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauEffModel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauEffModel*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauEffModel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauEffModel*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauEmbeddedData::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauEmbeddedData::Class_Name()
{
   return "LauEmbeddedData";
}

//______________________________________________________________________________
const char *LauEmbeddedData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauEmbeddedData*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauEmbeddedData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauEmbeddedData*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauEmbeddedData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauEmbeddedData*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauEmbeddedData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauEmbeddedData*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauExponentialPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauExponentialPdf::Class_Name()
{
   return "LauExponentialPdf";
}

//______________________________________________________________________________
const char *LauExponentialPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauExponentialPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauExponentialPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauExponentialPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauExponentialPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauExponentialPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauExponentialPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauExponentialPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauFitNtuple::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauFitNtuple::Class_Name()
{
   return "LauFitNtuple";
}

//______________________________________________________________________________
const char *LauFitNtuple::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFitNtuple*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauFitNtuple::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFitNtuple*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauFitNtuple::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFitNtuple*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauFitNtuple::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFitNtuple*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauPrint::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauPrint::Class_Name()
{
   return "LauPrint";
}

//______________________________________________________________________________
const char *LauPrint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPrint*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauPrint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPrint*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauPrint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPrint*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauPrint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPrint*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauFitter::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauFitter::Class_Name()
{
   return "LauFitter";
}

//______________________________________________________________________________
const char *LauFitter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFitter*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauFitter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFitter*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauFitter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFitter*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauFitter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFitter*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauFlatNR::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauFlatNR::Class_Name()
{
   return "LauFlatNR";
}

//______________________________________________________________________________
const char *LauFlatNR::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFlatNR*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauFlatNR::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFlatNR*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauFlatNR::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFlatNR*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauFlatNR::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFlatNR*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauFlatteRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauFlatteRes::Class_Name()
{
   return "LauFlatteRes";
}

//______________________________________________________________________________
const char *LauFlatteRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFlatteRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauFlatteRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauFlatteRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauFlatteRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFlatteRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauFlatteRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauFlatteRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauGaussIncohRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauGaussIncohRes::Class_Name()
{
   return "LauGaussIncohRes";
}

//______________________________________________________________________________
const char *LauGaussIncohRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauGaussIncohRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauGaussIncohRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauGaussIncohRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauGaussIncohRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauGaussIncohRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauGaussIncohRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauGaussIncohRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauGaussPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauGaussPdf::Class_Name()
{
   return "LauGaussPdf";
}

//______________________________________________________________________________
const char *LauGaussPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauGaussPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauGaussPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauGaussPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauGaussPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauGaussPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauGaussPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauGaussPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauGenNtuple::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauGenNtuple::Class_Name()
{
   return "LauGenNtuple";
}

//______________________________________________________________________________
const char *LauGenNtuple::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauGenNtuple*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauGenNtuple::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauGenNtuple*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauGenNtuple::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauGenNtuple*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauGenNtuple::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauGenNtuple*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauGounarisSakuraiRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauGounarisSakuraiRes::Class_Name()
{
   return "LauGounarisSakuraiRes";
}

//______________________________________________________________________________
const char *LauGounarisSakuraiRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauGounarisSakuraiRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauGounarisSakuraiRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauGounarisSakuraiRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauGounarisSakuraiRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauGounarisSakuraiRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauGounarisSakuraiRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauGounarisSakuraiRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauIntegrals::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauIntegrals::Class_Name()
{
   return "LauIntegrals";
}

//______________________________________________________________________________
const char *LauIntegrals::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauIntegrals*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauIntegrals::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauIntegrals*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauIntegrals::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauIntegrals*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauIntegrals::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauIntegrals*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauIsobarDynamics::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauIsobarDynamics::Class_Name()
{
   return "LauIsobarDynamics";
}

//______________________________________________________________________________
const char *LauIsobarDynamics::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauIsobarDynamics*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauIsobarDynamics::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauIsobarDynamics*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauIsobarDynamics::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauIsobarDynamics*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauIsobarDynamics::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauIsobarDynamics*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauKMatrixProdPole::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauKMatrixProdPole::Class_Name()
{
   return "LauKMatrixProdPole";
}

//______________________________________________________________________________
const char *LauKMatrixProdPole::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixProdPole*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauKMatrixProdPole::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixProdPole*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauKMatrixProdPole::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixProdPole*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauKMatrixProdPole::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixProdPole*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauKMatrixProdSVP::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauKMatrixProdSVP::Class_Name()
{
   return "LauKMatrixProdSVP";
}

//______________________________________________________________________________
const char *LauKMatrixProdSVP::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixProdSVP*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauKMatrixProdSVP::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixProdSVP*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauKMatrixProdSVP::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixProdSVP*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauKMatrixProdSVP::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixProdSVP*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauKMatrixPropFactory::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauKMatrixPropFactory::Class_Name()
{
   return "LauKMatrixPropFactory";
}

//______________________________________________________________________________
const char *LauKMatrixPropFactory::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixPropFactory*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauKMatrixPropFactory::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixPropFactory*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauKMatrixPropFactory::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixPropFactory*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauKMatrixPropFactory::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixPropFactory*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauResonanceMaker::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauResonanceMaker::Class_Name()
{
   return "LauResonanceMaker";
}

//______________________________________________________________________________
const char *LauResonanceMaker::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauResonanceMaker*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauResonanceMaker::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauResonanceMaker*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauResonanceMaker::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauResonanceMaker*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauResonanceMaker::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauResonanceMaker*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauResonanceInfo::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauResonanceInfo::Class_Name()
{
   return "LauResonanceInfo";
}

//______________________________________________________________________________
const char *LauResonanceInfo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauResonanceInfo*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauResonanceInfo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauResonanceInfo*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauResonanceInfo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauResonanceInfo*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauResonanceInfo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauResonanceInfo*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauKMatrixPropagator::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauKMatrixPropagator::Class_Name()
{
   return "LauKMatrixPropagator";
}

//______________________________________________________________________________
const char *LauKMatrixPropagator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixPropagator*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauKMatrixPropagator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixPropagator*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauKMatrixPropagator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixPropagator*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauKMatrixPropagator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKMatrixPropagator*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauKappaRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauKappaRes::Class_Name()
{
   return "LauKappaRes";
}

//______________________________________________________________________________
const char *LauKappaRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKappaRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauKappaRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauKappaRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauKappaRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKappaRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauKappaRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauKappaRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauLASSBWRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauLASSBWRes::Class_Name()
{
   return "LauLASSBWRes";
}

//______________________________________________________________________________
const char *LauLASSBWRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauLASSBWRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauLASSBWRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauLASSBWRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauLASSBWRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauLASSBWRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauLASSBWRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauLASSBWRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauLASSNRRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauLASSNRRes::Class_Name()
{
   return "LauLASSNRRes";
}

//______________________________________________________________________________
const char *LauLASSNRRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauLASSNRRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauLASSNRRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauLASSNRRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauLASSNRRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauLASSNRRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauLASSNRRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauLASSNRRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauLASSRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauLASSRes::Class_Name()
{
   return "LauLASSRes";
}

//______________________________________________________________________________
const char *LauLASSRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauLASSRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauLASSRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauLASSRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauLASSRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauLASSRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauLASSRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauLASSRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauLinearPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauLinearPdf::Class_Name()
{
   return "LauLinearPdf";
}

//______________________________________________________________________________
const char *LauLinearPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauLinearPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauLinearPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauLinearPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauLinearPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauLinearPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauLinearPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauLinearPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauMagPhaseCPCoeffSet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauMagPhaseCPCoeffSet::Class_Name()
{
   return "LauMagPhaseCPCoeffSet";
}

//______________________________________________________________________________
const char *LauMagPhaseCPCoeffSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauMagPhaseCPCoeffSet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauMagPhaseCPCoeffSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauMagPhaseCPCoeffSet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauMagPhaseCPCoeffSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauMagPhaseCPCoeffSet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauMagPhaseCPCoeffSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauMagPhaseCPCoeffSet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauMagPhaseCoeffSet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauMagPhaseCoeffSet::Class_Name()
{
   return "LauMagPhaseCoeffSet";
}

//______________________________________________________________________________
const char *LauMagPhaseCoeffSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauMagPhaseCoeffSet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauMagPhaseCoeffSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauMagPhaseCoeffSet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauMagPhaseCoeffSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauMagPhaseCoeffSet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauMagPhaseCoeffSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauMagPhaseCoeffSet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauMergeDataFiles::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauMergeDataFiles::Class_Name()
{
   return "LauMergeDataFiles";
}

//______________________________________________________________________________
const char *LauMergeDataFiles::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauMergeDataFiles*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauMergeDataFiles::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauMergeDataFiles*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauMergeDataFiles::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauMergeDataFiles*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauMergeDataFiles::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauMergeDataFiles*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauMinuit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauMinuit::Class_Name()
{
   return "LauMinuit";
}

//______________________________________________________________________________
const char *LauMinuit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauMinuit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauMinuit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauMinuit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauMinuit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauMinuit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauMinuit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauMinuit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauModIndPartWaveMagPhase::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauModIndPartWaveMagPhase::Class_Name()
{
   return "LauModIndPartWaveMagPhase";
}

//______________________________________________________________________________
const char *LauModIndPartWaveMagPhase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauModIndPartWaveMagPhase*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauModIndPartWaveMagPhase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauModIndPartWaveMagPhase*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauModIndPartWaveMagPhase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauModIndPartWaveMagPhase*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauModIndPartWaveMagPhase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauModIndPartWaveMagPhase*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauModIndPartWaveRealImag::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauModIndPartWaveRealImag::Class_Name()
{
   return "LauModIndPartWaveRealImag";
}

//______________________________________________________________________________
const char *LauModIndPartWaveRealImag::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauModIndPartWaveRealImag*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauModIndPartWaveRealImag::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauModIndPartWaveRealImag*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauModIndPartWaveRealImag::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauModIndPartWaveRealImag*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauModIndPartWaveRealImag::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauModIndPartWaveRealImag*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauNRAmplitude::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauNRAmplitude::Class_Name()
{
   return "LauNRAmplitude";
}

//______________________________________________________________________________
const char *LauNRAmplitude::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauNRAmplitude*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauNRAmplitude::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauNRAmplitude*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauNRAmplitude::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauNRAmplitude*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauNRAmplitude::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauNRAmplitude*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauNovosibirskPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauNovosibirskPdf::Class_Name()
{
   return "LauNovosibirskPdf";
}

//______________________________________________________________________________
const char *LauNovosibirskPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauNovosibirskPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauNovosibirskPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauNovosibirskPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauNovosibirskPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauNovosibirskPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauNovosibirskPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauNovosibirskPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauParametricStepFuncPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauParametricStepFuncPdf::Class_Name()
{
   return "LauParametricStepFuncPdf";
}

//______________________________________________________________________________
const char *LauParametricStepFuncPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauParametricStepFuncPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauParametricStepFuncPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauParametricStepFuncPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauParametricStepFuncPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauParametricStepFuncPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauParametricStepFuncPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauParametricStepFuncPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauParticlePDG::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauParticlePDG::Class_Name()
{
   return "LauParticlePDG";
}

//______________________________________________________________________________
const char *LauParticlePDG::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauParticlePDG*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauParticlePDG::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauParticlePDG*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauParticlePDG::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauParticlePDG*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauParticlePDG::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauParticlePDG*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauPolNR::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauPolNR::Class_Name()
{
   return "LauPolNR";
}

//______________________________________________________________________________
const char *LauPolNR::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPolNR*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauPolNR::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPolNR*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauPolNR::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPolNR*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauPolNR::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPolNR*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauPolarFormFactorNR::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauPolarFormFactorNR::Class_Name()
{
   return "LauPolarFormFactorNR";
}

//______________________________________________________________________________
const char *LauPolarFormFactorNR::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPolarFormFactorNR*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauPolarFormFactorNR::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPolarFormFactorNR*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauPolarFormFactorNR::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPolarFormFactorNR*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauPolarFormFactorNR::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPolarFormFactorNR*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauPolarFormFactorSymNR::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauPolarFormFactorSymNR::Class_Name()
{
   return "LauPolarFormFactorSymNR";
}

//______________________________________________________________________________
const char *LauPolarFormFactorSymNR::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPolarFormFactorSymNR*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauPolarFormFactorSymNR::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPolarFormFactorSymNR*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauPolarFormFactorSymNR::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPolarFormFactorSymNR*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauPolarFormFactorSymNR::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPolarFormFactorSymNR*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauPolarGammaCPCoeffSet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauPolarGammaCPCoeffSet::Class_Name()
{
   return "LauPolarGammaCPCoeffSet";
}

//______________________________________________________________________________
const char *LauPolarGammaCPCoeffSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPolarGammaCPCoeffSet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauPolarGammaCPCoeffSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPolarGammaCPCoeffSet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauPolarGammaCPCoeffSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPolarGammaCPCoeffSet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauPolarGammaCPCoeffSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPolarGammaCPCoeffSet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauPoleRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauPoleRes::Class_Name()
{
   return "LauPoleRes";
}

//______________________________________________________________________________
const char *LauPoleRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPoleRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauPoleRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauPoleRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauPoleRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPoleRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauPoleRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauPoleRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauRealImagCPCoeffSet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauRealImagCPCoeffSet::Class_Name()
{
   return "LauRealImagCPCoeffSet";
}

//______________________________________________________________________________
const char *LauRealImagCPCoeffSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagCPCoeffSet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauRealImagCPCoeffSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagCPCoeffSet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauRealImagCPCoeffSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagCPCoeffSet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauRealImagCPCoeffSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagCPCoeffSet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauRealImagCoeffSet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauRealImagCoeffSet::Class_Name()
{
   return "LauRealImagCoeffSet";
}

//______________________________________________________________________________
const char *LauRealImagCoeffSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagCoeffSet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauRealImagCoeffSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagCoeffSet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauRealImagCoeffSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagCoeffSet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauRealImagCoeffSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagCoeffSet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauRealImagGammaCPCoeffSet::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauRealImagGammaCPCoeffSet::Class_Name()
{
   return "LauRealImagGammaCPCoeffSet";
}

//______________________________________________________________________________
const char *LauRealImagGammaCPCoeffSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagGammaCPCoeffSet*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauRealImagGammaCPCoeffSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagGammaCPCoeffSet*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauRealImagGammaCPCoeffSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagGammaCPCoeffSet*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauRealImagGammaCPCoeffSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRealImagGammaCPCoeffSet*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauRelBreitWignerRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauRelBreitWignerRes::Class_Name()
{
   return "LauRelBreitWignerRes";
}

//______________________________________________________________________________
const char *LauRelBreitWignerRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRelBreitWignerRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauRelBreitWignerRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRelBreitWignerRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauRelBreitWignerRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRelBreitWignerRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauRelBreitWignerRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRelBreitWignerRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauRescattering2Res::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauRescattering2Res::Class_Name()
{
   return "LauRescattering2Res";
}

//______________________________________________________________________________
const char *LauRescattering2Res::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRescattering2Res*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauRescattering2Res::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRescattering2Res*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauRescattering2Res::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRescattering2Res*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauRescattering2Res::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRescattering2Res*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauRescatteringRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauRescatteringRes::Class_Name()
{
   return "LauRescatteringRes";
}

//______________________________________________________________________________
const char *LauRescatteringRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRescatteringRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauRescatteringRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRescatteringRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauRescatteringRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRescatteringRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauRescatteringRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRescatteringRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauResultsExtractor::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauResultsExtractor::Class_Name()
{
   return "LauResultsExtractor";
}

//______________________________________________________________________________
const char *LauResultsExtractor::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauResultsExtractor*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauResultsExtractor::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauResultsExtractor*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauResultsExtractor::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauResultsExtractor*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauResultsExtractor::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauResultsExtractor*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauRhoOmegaMix::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauRhoOmegaMix::Class_Name()
{
   return "LauRhoOmegaMix";
}

//______________________________________________________________________________
const char *LauRhoOmegaMix::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRhoOmegaMix*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauRhoOmegaMix::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauRhoOmegaMix*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauRhoOmegaMix::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRhoOmegaMix*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauRhoOmegaMix::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauRhoOmegaMix*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauScfMap::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauScfMap::Class_Name()
{
   return "LauScfMap";
}

//______________________________________________________________________________
const char *LauScfMap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauScfMap*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauScfMap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauScfMap*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauScfMap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauScfMap*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauScfMap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauScfMap*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauSigmaRes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauSigmaRes::Class_Name()
{
   return "LauSigmaRes";
}

//______________________________________________________________________________
const char *LauSigmaRes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSigmaRes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauSigmaRes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSigmaRes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauSigmaRes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSigmaRes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauSigmaRes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSigmaRes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauSigmoidPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauSigmoidPdf::Class_Name()
{
   return "LauSigmoidPdf";
}

//______________________________________________________________________________
const char *LauSigmoidPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSigmoidPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauSigmoidPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSigmoidPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauSigmoidPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSigmoidPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauSigmoidPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSigmoidPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauSimFitCoordinator::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauSimFitCoordinator::Class_Name()
{
   return "LauSimFitCoordinator";
}

//______________________________________________________________________________
const char *LauSimFitCoordinator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSimFitCoordinator*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauSimFitCoordinator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSimFitCoordinator*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauSimFitCoordinator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSimFitCoordinator*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauSimFitCoordinator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSimFitCoordinator*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauSimpleFitModel::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauSimpleFitModel::Class_Name()
{
   return "LauSimpleFitModel";
}

//______________________________________________________________________________
const char *LauSimpleFitModel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSimpleFitModel*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauSimpleFitModel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSimpleFitModel*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauSimpleFitModel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSimpleFitModel*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauSimpleFitModel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSimpleFitModel*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauSumPdf::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauSumPdf::Class_Name()
{
   return "LauSumPdf";
}

//______________________________________________________________________________
const char *LauSumPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSumPdf*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauSumPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauSumPdf*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauSumPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSumPdf*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauSumPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauSumPdf*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauVetoes::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauVetoes::Class_Name()
{
   return "LauVetoes";
}

//______________________________________________________________________________
const char *LauVetoes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauVetoes*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauVetoes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauVetoes*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauVetoes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauVetoes*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauVetoes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauVetoes*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LauWeightedSumEffModel::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *LauWeightedSumEffModel::Class_Name()
{
   return "LauWeightedSumEffModel";
}

//______________________________________________________________________________
const char *LauWeightedSumEffModel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauWeightedSumEffModel*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int LauWeightedSumEffModel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LauWeightedSumEffModel*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LauWeightedSumEffModel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauWeightedSumEffModel*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LauWeightedSumEffModel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LauWeightedSumEffModel*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Lau1DCubicSpline::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau1DCubicSpline.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau1DCubicSpline::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau1DCubicSpline::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau1DCubicSpline(void *p) {
      delete (static_cast<::Lau1DCubicSpline*>(p));
   }
   static void deleteArray_Lau1DCubicSpline(void *p) {
      delete [] (static_cast<::Lau1DCubicSpline*>(p));
   }
   static void destruct_Lau1DCubicSpline(void *p) {
      typedef ::Lau1DCubicSpline current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau1DCubicSpline

//______________________________________________________________________________
void LauFitDataTree::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauFitDataTree.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauFitDataTree::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauFitDataTree::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauFitDataTree(void *p) {
      delete (static_cast<::LauFitDataTree*>(p));
   }
   static void deleteArray_LauFitDataTree(void *p) {
      delete [] (static_cast<::LauFitDataTree*>(p));
   }
   static void destruct_LauFitDataTree(void *p) {
      typedef ::LauFitDataTree current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauFitDataTree

//______________________________________________________________________________
void LauAbsRValue::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauAbsRValue.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauAbsRValue::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauAbsRValue::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauAbsRValue(void *p) {
      delete (static_cast<::LauAbsRValue*>(p));
   }
   static void deleteArray_LauAbsRValue(void *p) {
      delete [] (static_cast<::LauAbsRValue*>(p));
   }
   static void destruct_LauAbsRValue(void *p) {
      typedef ::LauAbsRValue current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauAbsRValue

//______________________________________________________________________________
void LauBlind::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauBlind.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauBlind::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauBlind::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LauBlind(void *p) {
      return  p ? new(p) ::LauBlind : new ::LauBlind;
   }
   static void *newArray_LauBlind(Long_t nElements, void *p) {
      return p ? new(p) ::LauBlind[nElements] : new ::LauBlind[nElements];
   }
   // Wrapper around operator delete
   static void delete_LauBlind(void *p) {
      delete (static_cast<::LauBlind*>(p));
   }
   static void deleteArray_LauBlind(void *p) {
      delete [] (static_cast<::LauBlind*>(p));
   }
   static void destruct_LauBlind(void *p) {
      typedef ::LauBlind current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauBlind

//______________________________________________________________________________
void LauParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LauParameter(void *p) {
      return  p ? new(p) ::LauParameter : new ::LauParameter;
   }
   static void *newArray_LauParameter(Long_t nElements, void *p) {
      return p ? new(p) ::LauParameter[nElements] : new ::LauParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_LauParameter(void *p) {
      delete (static_cast<::LauParameter*>(p));
   }
   static void deleteArray_LauParameter(void *p) {
      delete [] (static_cast<::LauParameter*>(p));
   }
   static void destruct_LauParameter(void *p) {
      typedef ::LauParameter current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauParameter

namespace ROOT {
   // Wrappers around operator new
   static void *new_LauParamFixed(void *p) {
      return  p ? new(p) ::LauParamFixed : new ::LauParamFixed;
   }
   static void *newArray_LauParamFixed(Long_t nElements, void *p) {
      return p ? new(p) ::LauParamFixed[nElements] : new ::LauParamFixed[nElements];
   }
   // Wrapper around operator delete
   static void delete_LauParamFixed(void *p) {
      delete (static_cast<::LauParamFixed*>(p));
   }
   static void deleteArray_LauParamFixed(void *p) {
      delete [] (static_cast<::LauParamFixed*>(p));
   }
   static void destruct_LauParamFixed(void *p) {
      typedef ::LauParamFixed current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauParamFixed

//______________________________________________________________________________
void LauAbsPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauAbsPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauAbsPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauAbsPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauAbsPdf(void *p) {
      delete (static_cast<::LauAbsPdf*>(p));
   }
   static void deleteArray_LauAbsPdf(void *p) {
      delete [] (static_cast<::LauAbsPdf*>(p));
   }
   static void destruct_LauAbsPdf(void *p) {
      typedef ::LauAbsPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauAbsPdf

//______________________________________________________________________________
void Lau1DHistPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau1DHistPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau1DHistPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau1DHistPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau1DHistPdf(void *p) {
      delete (static_cast<::Lau1DHistPdf*>(p));
   }
   static void deleteArray_Lau1DHistPdf(void *p) {
      delete [] (static_cast<::Lau1DHistPdf*>(p));
   }
   static void destruct_Lau1DHistPdf(void *p) {
      typedef ::Lau1DHistPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau1DHistPdf

//______________________________________________________________________________
void Lau2DAbsDP::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau2DAbsDP.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau2DAbsDP::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau2DAbsDP::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau2DAbsDP(void *p) {
      delete (static_cast<::Lau2DAbsDP*>(p));
   }
   static void deleteArray_Lau2DAbsDP(void *p) {
      delete [] (static_cast<::Lau2DAbsDP*>(p));
   }
   static void destruct_Lau2DAbsDP(void *p) {
      typedef ::Lau2DAbsDP current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau2DAbsDP

//______________________________________________________________________________
void Lau2DAbsDPPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau2DAbsDPPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau2DAbsDPPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau2DAbsDPPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau2DAbsDPPdf(void *p) {
      delete (static_cast<::Lau2DAbsDPPdf*>(p));
   }
   static void deleteArray_Lau2DAbsDPPdf(void *p) {
      delete [] (static_cast<::Lau2DAbsDPPdf*>(p));
   }
   static void destruct_Lau2DAbsDPPdf(void *p) {
      typedef ::Lau2DAbsDPPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau2DAbsDPPdf

//______________________________________________________________________________
void Lau2DAbsHistDP::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau2DAbsHistDP.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau2DAbsHistDP::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau2DAbsHistDP::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau2DAbsHistDP(void *p) {
      delete (static_cast<::Lau2DAbsHistDP*>(p));
   }
   static void deleteArray_Lau2DAbsHistDP(void *p) {
      delete [] (static_cast<::Lau2DAbsHistDP*>(p));
   }
   static void destruct_Lau2DAbsHistDP(void *p) {
      typedef ::Lau2DAbsHistDP current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau2DAbsHistDP

//______________________________________________________________________________
void Lau2DAbsHistDPPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau2DAbsHistDPPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau2DAbsHistDPPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau2DAbsHistDPPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau2DAbsHistDPPdf(void *p) {
      delete (static_cast<::Lau2DAbsHistDPPdf*>(p));
   }
   static void deleteArray_Lau2DAbsHistDPPdf(void *p) {
      delete [] (static_cast<::Lau2DAbsHistDPPdf*>(p));
   }
   static void destruct_Lau2DAbsHistDPPdf(void *p) {
      typedef ::Lau2DAbsHistDPPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau2DAbsHistDPPdf

//______________________________________________________________________________
void Lau2DCubicSpline::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau2DCubicSpline.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau2DCubicSpline::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau2DCubicSpline::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau2DCubicSpline(void *p) {
      delete (static_cast<::Lau2DCubicSpline*>(p));
   }
   static void deleteArray_Lau2DCubicSpline(void *p) {
      delete [] (static_cast<::Lau2DCubicSpline*>(p));
   }
   static void destruct_Lau2DCubicSpline(void *p) {
      typedef ::Lau2DCubicSpline current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau2DCubicSpline

//______________________________________________________________________________
void Lau2DHistDP::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau2DHistDP.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau2DHistDP::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau2DHistDP::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau2DHistDP(void *p) {
      delete (static_cast<::Lau2DHistDP*>(p));
   }
   static void deleteArray_Lau2DHistDP(void *p) {
      delete [] (static_cast<::Lau2DHistDP*>(p));
   }
   static void destruct_Lau2DHistDP(void *p) {
      typedef ::Lau2DHistDP current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau2DHistDP

//______________________________________________________________________________
void Lau2DHistDPPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau2DHistDPPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau2DHistDPPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau2DHistDPPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau2DHistDPPdf(void *p) {
      delete (static_cast<::Lau2DHistDPPdf*>(p));
   }
   static void deleteArray_Lau2DHistDPPdf(void *p) {
      delete [] (static_cast<::Lau2DHistDPPdf*>(p));
   }
   static void destruct_Lau2DHistDPPdf(void *p) {
      typedef ::Lau2DHistDPPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau2DHistDPPdf

//______________________________________________________________________________
void Lau2DHistPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau2DHistPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau2DHistPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau2DHistPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau2DHistPdf(void *p) {
      delete (static_cast<::Lau2DHistPdf*>(p));
   }
   static void deleteArray_Lau2DHistPdf(void *p) {
      delete [] (static_cast<::Lau2DHistPdf*>(p));
   }
   static void destruct_Lau2DHistPdf(void *p) {
      typedef ::Lau2DHistPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau2DHistPdf

//______________________________________________________________________________
void Lau2DSplineDP::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau2DSplineDP.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau2DSplineDP::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau2DSplineDP::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau2DSplineDP(void *p) {
      delete (static_cast<::Lau2DSplineDP*>(p));
   }
   static void deleteArray_Lau2DSplineDP(void *p) {
      delete [] (static_cast<::Lau2DSplineDP*>(p));
   }
   static void destruct_Lau2DSplineDP(void *p) {
      typedef ::Lau2DSplineDP current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau2DSplineDP

//______________________________________________________________________________
void Lau2DSplineDPPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class Lau2DSplineDPPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Lau2DSplineDPPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(Lau2DSplineDPPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Lau2DSplineDPPdf(void *p) {
      delete (static_cast<::Lau2DSplineDPPdf*>(p));
   }
   static void deleteArray_Lau2DSplineDPPdf(void *p) {
      delete [] (static_cast<::Lau2DSplineDPPdf*>(p));
   }
   static void destruct_Lau2DSplineDPPdf(void *p) {
      typedef ::Lau2DSplineDPPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Lau2DSplineDPPdf

//______________________________________________________________________________
void LauAbsFitter::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauAbsFitter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauAbsFitter::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauAbsFitter::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauAbsFitter(void *p) {
      delete (static_cast<::LauAbsFitter*>(p));
   }
   static void deleteArray_LauAbsFitter(void *p) {
      delete [] (static_cast<::LauAbsFitter*>(p));
   }
   static void destruct_LauAbsFitter(void *p) {
      typedef ::LauAbsFitter current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauAbsFitter

//______________________________________________________________________________
void LauFormulaPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauFormulaPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauFormulaPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauFormulaPar::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauFormulaPar(void *p) {
      delete (static_cast<::LauFormulaPar*>(p));
   }
   static void deleteArray_LauFormulaPar(void *p) {
      delete [] (static_cast<::LauFormulaPar*>(p));
   }
   static void destruct_LauFormulaPar(void *p) {
      typedef ::LauFormulaPar current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauFormulaPar

//______________________________________________________________________________
void LauFitObject::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauFitObject.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauFitObject::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauFitObject::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauFitObject(void *p) {
      delete (static_cast<::LauFitObject*>(p));
   }
   static void deleteArray_LauFitObject(void *p) {
      delete [] (static_cast<::LauFitObject*>(p));
   }
   static void destruct_LauFitObject(void *p) {
      typedef ::LauFitObject current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauFitObject

//______________________________________________________________________________
void LauASqMaxFinder::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauASqMaxFinder.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauASqMaxFinder::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauASqMaxFinder::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauASqMaxFinder(void *p) {
      delete (static_cast<::LauASqMaxFinder*>(p));
   }
   static void deleteArray_LauASqMaxFinder(void *p) {
      delete [] (static_cast<::LauASqMaxFinder*>(p));
   }
   static void destruct_LauASqMaxFinder(void *p) {
      typedef ::LauASqMaxFinder current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauASqMaxFinder

//______________________________________________________________________________
void LauAbsBkgndDPModel::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauAbsBkgndDPModel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauAbsBkgndDPModel::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauAbsBkgndDPModel::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauAbsBkgndDPModel(void *p) {
      delete (static_cast<::LauAbsBkgndDPModel*>(p));
   }
   static void deleteArray_LauAbsBkgndDPModel(void *p) {
      delete [] (static_cast<::LauAbsBkgndDPModel*>(p));
   }
   static void destruct_LauAbsBkgndDPModel(void *p) {
      typedef ::LauAbsBkgndDPModel current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauAbsBkgndDPModel

//______________________________________________________________________________
void LauAbsCoeffSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauAbsCoeffSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauAbsCoeffSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauAbsCoeffSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauAbsCoeffSet(void *p) {
      delete (static_cast<::LauAbsCoeffSet*>(p));
   }
   static void deleteArray_LauAbsCoeffSet(void *p) {
      delete [] (static_cast<::LauAbsCoeffSet*>(p));
   }
   static void destruct_LauAbsCoeffSet(void *p) {
      typedef ::LauAbsCoeffSet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauAbsCoeffSet

//______________________________________________________________________________
void LauAbsEffModel::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauAbsEffModel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauAbsEffModel::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauAbsEffModel::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauAbsEffModel(void *p) {
      delete (static_cast<::LauAbsEffModel*>(p));
   }
   static void deleteArray_LauAbsEffModel(void *p) {
      delete [] (static_cast<::LauAbsEffModel*>(p));
   }
   static void destruct_LauAbsEffModel(void *p) {
      typedef ::LauAbsEffModel current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauAbsEffModel

//______________________________________________________________________________
void LauComplex::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauComplex.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauComplex::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauComplex::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LauComplex(void *p) {
      return  p ? new(p) ::LauComplex : new ::LauComplex;
   }
   static void *newArray_LauComplex(Long_t nElements, void *p) {
      return p ? new(p) ::LauComplex[nElements] : new ::LauComplex[nElements];
   }
   // Wrapper around operator delete
   static void delete_LauComplex(void *p) {
      delete (static_cast<::LauComplex*>(p));
   }
   static void deleteArray_LauComplex(void *p) {
      delete [] (static_cast<::LauComplex*>(p));
   }
   static void destruct_LauComplex(void *p) {
      typedef ::LauComplex current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauComplex

//______________________________________________________________________________
void LauSimFitTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauSimFitTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauSimFitTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauSimFitTask::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauSimFitTask(void *p) {
      delete (static_cast<::LauSimFitTask*>(p));
   }
   static void deleteArray_LauSimFitTask(void *p) {
      delete [] (static_cast<::LauSimFitTask*>(p));
   }
   static void destruct_LauSimFitTask(void *p) {
      typedef ::LauSimFitTask current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauSimFitTask

//______________________________________________________________________________
void LauSPlot::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauSPlot.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauSPlot::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauSPlot::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauSPlot(void *p) {
      delete (static_cast<::LauSPlot*>(p));
   }
   static void deleteArray_LauSPlot(void *p) {
      delete [] (static_cast<::LauSPlot*>(p));
   }
   static void destruct_LauSPlot(void *p) {
      typedef ::LauSPlot current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauSPlot

//______________________________________________________________________________
void LauAbsFitModel::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauAbsFitModel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauAbsFitModel::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauAbsFitModel::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauAbsFitModel(void *p) {
      delete (static_cast<::LauAbsFitModel*>(p));
   }
   static void deleteArray_LauAbsFitModel(void *p) {
      delete [] (static_cast<::LauAbsFitModel*>(p));
   }
   static void destruct_LauAbsFitModel(void *p) {
      typedef ::LauAbsFitModel current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauAbsFitModel

//______________________________________________________________________________
void LauBlattWeisskopfFactor::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauBlattWeisskopfFactor.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauBlattWeisskopfFactor::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauBlattWeisskopfFactor::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauBlattWeisskopfFactor(void *p) {
      delete (static_cast<::LauBlattWeisskopfFactor*>(p));
   }
   static void deleteArray_LauBlattWeisskopfFactor(void *p) {
      delete [] (static_cast<::LauBlattWeisskopfFactor*>(p));
   }
   static void destruct_LauBlattWeisskopfFactor(void *p) {
      typedef ::LauBlattWeisskopfFactor current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauBlattWeisskopfFactor

//______________________________________________________________________________
void LauAbsResonance::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauAbsResonance.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauAbsResonance::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauAbsResonance::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauAbsResonance(void *p) {
      delete (static_cast<::LauAbsResonance*>(p));
   }
   static void deleteArray_LauAbsResonance(void *p) {
      delete [] (static_cast<::LauAbsResonance*>(p));
   }
   static void destruct_LauAbsResonance(void *p) {
      typedef ::LauAbsResonance current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauAbsResonance

//______________________________________________________________________________
void LauAbsIncohRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauAbsIncohRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauAbsIncohRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauAbsIncohRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauAbsIncohRes(void *p) {
      delete (static_cast<::LauAbsIncohRes*>(p));
   }
   static void deleteArray_LauAbsIncohRes(void *p) {
      delete [] (static_cast<::LauAbsIncohRes*>(p));
   }
   static void destruct_LauAbsIncohRes(void *p) {
      typedef ::LauAbsIncohRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauAbsIncohRes

//______________________________________________________________________________
void LauAbsModIndPartWave::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauAbsModIndPartWave.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauAbsModIndPartWave::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauAbsModIndPartWave::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauAbsModIndPartWave(void *p) {
      delete (static_cast<::LauAbsModIndPartWave*>(p));
   }
   static void deleteArray_LauAbsModIndPartWave(void *p) {
      delete [] (static_cast<::LauAbsModIndPartWave*>(p));
   }
   static void destruct_LauAbsModIndPartWave(void *p) {
      typedef ::LauAbsModIndPartWave current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauAbsModIndPartWave

//______________________________________________________________________________
void LauArgusPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauArgusPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauArgusPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauArgusPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauArgusPdf(void *p) {
      delete (static_cast<::LauArgusPdf*>(p));
   }
   static void deleteArray_LauArgusPdf(void *p) {
      delete [] (static_cast<::LauArgusPdf*>(p));
   }
   static void destruct_LauArgusPdf(void *p) {
      typedef ::LauArgusPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauArgusPdf

//______________________________________________________________________________
void LauAsymmCalc::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauAsymmCalc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauAsymmCalc::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauAsymmCalc::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauAsymmCalc(void *p) {
      delete (static_cast<::LauAsymmCalc*>(p));
   }
   static void deleteArray_LauAsymmCalc(void *p) {
      delete [] (static_cast<::LauAsymmCalc*>(p));
   }
   static void destruct_LauAsymmCalc(void *p) {
      typedef ::LauAsymmCalc current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauAsymmCalc

//______________________________________________________________________________
void LauBelleCPCoeffSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauBelleCPCoeffSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauBelleCPCoeffSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauBelleCPCoeffSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauBelleCPCoeffSet(void *p) {
      delete (static_cast<::LauBelleCPCoeffSet*>(p));
   }
   static void deleteArray_LauBelleCPCoeffSet(void *p) {
      delete [] (static_cast<::LauBelleCPCoeffSet*>(p));
   }
   static void destruct_LauBelleCPCoeffSet(void *p) {
      typedef ::LauBelleCPCoeffSet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauBelleCPCoeffSet

//______________________________________________________________________________
void LauBelleNR::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauBelleNR.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauBelleNR::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauBelleNR::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauBelleNR(void *p) {
      delete (static_cast<::LauBelleNR*>(p));
   }
   static void deleteArray_LauBelleNR(void *p) {
      delete [] (static_cast<::LauBelleNR*>(p));
   }
   static void destruct_LauBelleNR(void *p) {
      typedef ::LauBelleNR current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauBelleNR

//______________________________________________________________________________
void LauBelleSymNR::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauBelleSymNR.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauBelleSymNR::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauBelleSymNR::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauBelleSymNR(void *p) {
      delete (static_cast<::LauBelleSymNR*>(p));
   }
   static void deleteArray_LauBelleSymNR(void *p) {
      delete [] (static_cast<::LauBelleSymNR*>(p));
   }
   static void destruct_LauBelleSymNR(void *p) {
      typedef ::LauBelleSymNR current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauBelleSymNR

//______________________________________________________________________________
void LauBifurcatedGaussPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauBifurcatedGaussPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauBifurcatedGaussPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauBifurcatedGaussPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauBifurcatedGaussPdf(void *p) {
      delete (static_cast<::LauBifurcatedGaussPdf*>(p));
   }
   static void deleteArray_LauBifurcatedGaussPdf(void *p) {
      delete [] (static_cast<::LauBifurcatedGaussPdf*>(p));
   }
   static void destruct_LauBifurcatedGaussPdf(void *p) {
      typedef ::LauBifurcatedGaussPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauBifurcatedGaussPdf

//______________________________________________________________________________
void LauBkgndDPModel::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauBkgndDPModel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauBkgndDPModel::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauBkgndDPModel::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauBkgndDPModel(void *p) {
      delete (static_cast<::LauBkgndDPModel*>(p));
   }
   static void deleteArray_LauBkgndDPModel(void *p) {
      delete [] (static_cast<::LauBkgndDPModel*>(p));
   }
   static void destruct_LauBkgndDPModel(void *p) {
      typedef ::LauBkgndDPModel current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauBkgndDPModel

//______________________________________________________________________________
void LauBreitWignerRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauBreitWignerRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauBreitWignerRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauBreitWignerRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauBreitWignerRes(void *p) {
      delete (static_cast<::LauBreitWignerRes*>(p));
   }
   static void deleteArray_LauBreitWignerRes(void *p) {
      delete [] (static_cast<::LauBreitWignerRes*>(p));
   }
   static void destruct_LauBreitWignerRes(void *p) {
      typedef ::LauBreitWignerRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauBreitWignerRes

//______________________________________________________________________________
void LauCPFitModel::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauCPFitModel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauCPFitModel::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauCPFitModel::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauCPFitModel(void *p) {
      delete (static_cast<::LauCPFitModel*>(p));
   }
   static void deleteArray_LauCPFitModel(void *p) {
      delete [] (static_cast<::LauCPFitModel*>(p));
   }
   static void destruct_LauCPFitModel(void *p) {
      typedef ::LauCPFitModel current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauCPFitModel

//______________________________________________________________________________
void LauCacheData::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauCacheData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauCacheData::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauCacheData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LauCacheData(void *p) {
      return  p ? new(p) ::LauCacheData : new ::LauCacheData;
   }
   static void *newArray_LauCacheData(Long_t nElements, void *p) {
      return p ? new(p) ::LauCacheData[nElements] : new ::LauCacheData[nElements];
   }
   // Wrapper around operator delete
   static void delete_LauCacheData(void *p) {
      delete (static_cast<::LauCacheData*>(p));
   }
   static void deleteArray_LauCacheData(void *p) {
      delete [] (static_cast<::LauCacheData*>(p));
   }
   static void destruct_LauCacheData(void *p) {
      typedef ::LauCacheData current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauCacheData

//______________________________________________________________________________
void LauCalcChiSq::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauCalcChiSq.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauCalcChiSq::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauCalcChiSq::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LauCalcChiSq(void *p) {
      return  p ? new(p) ::LauCalcChiSq : new ::LauCalcChiSq;
   }
   static void *newArray_LauCalcChiSq(Long_t nElements, void *p) {
      return p ? new(p) ::LauCalcChiSq[nElements] : new ::LauCalcChiSq[nElements];
   }
   // Wrapper around operator delete
   static void delete_LauCalcChiSq(void *p) {
      delete (static_cast<::LauCalcChiSq*>(p));
   }
   static void deleteArray_LauCalcChiSq(void *p) {
      delete [] (static_cast<::LauCalcChiSq*>(p));
   }
   static void destruct_LauCalcChiSq(void *p) {
      typedef ::LauCalcChiSq current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauCalcChiSq

//______________________________________________________________________________
void LauCartesianCPCoeffSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauCartesianCPCoeffSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauCartesianCPCoeffSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauCartesianCPCoeffSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauCartesianCPCoeffSet(void *p) {
      delete (static_cast<::LauCartesianCPCoeffSet*>(p));
   }
   static void deleteArray_LauCartesianCPCoeffSet(void *p) {
      delete [] (static_cast<::LauCartesianCPCoeffSet*>(p));
   }
   static void destruct_LauCartesianCPCoeffSet(void *p) {
      typedef ::LauCartesianCPCoeffSet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauCartesianCPCoeffSet

//______________________________________________________________________________
void LauCartesianGammaCPCoeffSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauCartesianGammaCPCoeffSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauCartesianGammaCPCoeffSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauCartesianGammaCPCoeffSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauCartesianGammaCPCoeffSet(void *p) {
      delete (static_cast<::LauCartesianGammaCPCoeffSet*>(p));
   }
   static void deleteArray_LauCartesianGammaCPCoeffSet(void *p) {
      delete [] (static_cast<::LauCartesianGammaCPCoeffSet*>(p));
   }
   static void destruct_LauCartesianGammaCPCoeffSet(void *p) {
      typedef ::LauCartesianGammaCPCoeffSet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauCartesianGammaCPCoeffSet

//______________________________________________________________________________
void LauChebychevPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauChebychevPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauChebychevPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauChebychevPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauChebychevPdf(void *p) {
      delete (static_cast<::LauChebychevPdf*>(p));
   }
   static void deleteArray_LauChebychevPdf(void *p) {
      delete [] (static_cast<::LauChebychevPdf*>(p));
   }
   static void destruct_LauChebychevPdf(void *p) {
      typedef ::LauChebychevPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauChebychevPdf

//______________________________________________________________________________
void LauCleoCPCoeffSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauCleoCPCoeffSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauCleoCPCoeffSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauCleoCPCoeffSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauCleoCPCoeffSet(void *p) {
      delete (static_cast<::LauCleoCPCoeffSet*>(p));
   }
   static void deleteArray_LauCleoCPCoeffSet(void *p) {
      delete [] (static_cast<::LauCleoCPCoeffSet*>(p));
   }
   static void destruct_LauCleoCPCoeffSet(void *p) {
      typedef ::LauCleoCPCoeffSet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauCleoCPCoeffSet

//______________________________________________________________________________
void LauCruijffPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauCruijffPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauCruijffPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauCruijffPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauCruijffPdf(void *p) {
      delete (static_cast<::LauCruijffPdf*>(p));
   }
   static void deleteArray_LauCruijffPdf(void *p) {
      delete [] (static_cast<::LauCruijffPdf*>(p));
   }
   static void destruct_LauCruijffPdf(void *p) {
      typedef ::LauCruijffPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauCruijffPdf

//______________________________________________________________________________
void LauCrystalBallPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauCrystalBallPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauCrystalBallPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauCrystalBallPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauCrystalBallPdf(void *p) {
      delete (static_cast<::LauCrystalBallPdf*>(p));
   }
   static void deleteArray_LauCrystalBallPdf(void *p) {
      delete [] (static_cast<::LauCrystalBallPdf*>(p));
   }
   static void destruct_LauCrystalBallPdf(void *p) {
      typedef ::LauCrystalBallPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauCrystalBallPdf

//______________________________________________________________________________
void LauDPDepBifurGaussPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauDPDepBifurGaussPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauDPDepBifurGaussPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauDPDepBifurGaussPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauDPDepBifurGaussPdf(void *p) {
      delete (static_cast<::LauDPDepBifurGaussPdf*>(p));
   }
   static void deleteArray_LauDPDepBifurGaussPdf(void *p) {
      delete [] (static_cast<::LauDPDepBifurGaussPdf*>(p));
   }
   static void destruct_LauDPDepBifurGaussPdf(void *p) {
      typedef ::LauDPDepBifurGaussPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauDPDepBifurGaussPdf

//______________________________________________________________________________
void LauDPDepCruijffPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauDPDepCruijffPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauDPDepCruijffPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauDPDepCruijffPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauDPDepCruijffPdf(void *p) {
      delete (static_cast<::LauDPDepCruijffPdf*>(p));
   }
   static void deleteArray_LauDPDepCruijffPdf(void *p) {
      delete [] (static_cast<::LauDPDepCruijffPdf*>(p));
   }
   static void destruct_LauDPDepCruijffPdf(void *p) {
      typedef ::LauDPDepCruijffPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauDPDepCruijffPdf

//______________________________________________________________________________
void LauDPDepGaussPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauDPDepGaussPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauDPDepGaussPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauDPDepGaussPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauDPDepGaussPdf(void *p) {
      delete (static_cast<::LauDPDepGaussPdf*>(p));
   }
   static void deleteArray_LauDPDepGaussPdf(void *p) {
      delete [] (static_cast<::LauDPDepGaussPdf*>(p));
   }
   static void destruct_LauDPDepGaussPdf(void *p) {
      typedef ::LauDPDepGaussPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauDPDepGaussPdf

//______________________________________________________________________________
void LauDPDepMapPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauDPDepMapPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauDPDepMapPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauDPDepMapPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauDPDepMapPdf(void *p) {
      delete (static_cast<::LauDPDepMapPdf*>(p));
   }
   static void deleteArray_LauDPDepMapPdf(void *p) {
      delete [] (static_cast<::LauDPDepMapPdf*>(p));
   }
   static void destruct_LauDPDepMapPdf(void *p) {
      typedef ::LauDPDepMapPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauDPDepMapPdf

//______________________________________________________________________________
void LauDPDepSumPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauDPDepSumPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauDPDepSumPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauDPDepSumPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauDPDepSumPdf(void *p) {
      delete (static_cast<::LauDPDepSumPdf*>(p));
   }
   static void deleteArray_LauDPDepSumPdf(void *p) {
      delete [] (static_cast<::LauDPDepSumPdf*>(p));
   }
   static void destruct_LauDPDepSumPdf(void *p) {
      typedef ::LauDPDepSumPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauDPDepSumPdf

//______________________________________________________________________________
void LauDPPartialIntegralInfo::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauDPPartialIntegralInfo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauDPPartialIntegralInfo::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauDPPartialIntegralInfo::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauDPPartialIntegralInfo(void *p) {
      delete (static_cast<::LauDPPartialIntegralInfo*>(p));
   }
   static void deleteArray_LauDPPartialIntegralInfo(void *p) {
      delete [] (static_cast<::LauDPPartialIntegralInfo*>(p));
   }
   static void destruct_LauDPPartialIntegralInfo(void *p) {
      typedef ::LauDPPartialIntegralInfo current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauDPPartialIntegralInfo

//______________________________________________________________________________
void LauDabbaRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauDabbaRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauDabbaRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauDabbaRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauDabbaRes(void *p) {
      delete (static_cast<::LauDabbaRes*>(p));
   }
   static void deleteArray_LauDabbaRes(void *p) {
      delete [] (static_cast<::LauDabbaRes*>(p));
   }
   static void destruct_LauDabbaRes(void *p) {
      typedef ::LauDabbaRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauDabbaRes

//______________________________________________________________________________
void LauDatabasePDG::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauDatabasePDG.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauDatabasePDG::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauDatabasePDG::Class(),this);
   }
}

namespace ROOT {
} // end of namespace ROOT for class ::LauDatabasePDG

//______________________________________________________________________________
void LauKinematics::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauKinematics.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauKinematics::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauKinematics::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauKinematics(void *p) {
      delete (static_cast<::LauKinematics*>(p));
   }
   static void deleteArray_LauKinematics(void *p) {
      delete [] (static_cast<::LauKinematics*>(p));
   }
   static void destruct_LauKinematics(void *p) {
      typedef ::LauKinematics current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauKinematics

//______________________________________________________________________________
void LauDaughters::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauDaughters.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauDaughters::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauDaughters::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauDaughters(void *p) {
      delete (static_cast<::LauDaughters*>(p));
   }
   static void deleteArray_LauDaughters(void *p) {
      delete [] (static_cast<::LauDaughters*>(p));
   }
   static void destruct_LauDaughters(void *p) {
      typedef ::LauDaughters current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauDaughters

//______________________________________________________________________________
void LauEFKLLMRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauEFKLLMRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauEFKLLMRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauEFKLLMRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauEFKLLMRes(void *p) {
      delete (static_cast<::LauEFKLLMRes*>(p));
   }
   static void deleteArray_LauEFKLLMRes(void *p) {
      delete [] (static_cast<::LauEFKLLMRes*>(p));
   }
   static void destruct_LauEFKLLMRes(void *p) {
      typedef ::LauEFKLLMRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauEFKLLMRes

//______________________________________________________________________________
void LauEffModel::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauEffModel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauEffModel::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauEffModel::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauEffModel(void *p) {
      delete (static_cast<::LauEffModel*>(p));
   }
   static void deleteArray_LauEffModel(void *p) {
      delete [] (static_cast<::LauEffModel*>(p));
   }
   static void destruct_LauEffModel(void *p) {
      typedef ::LauEffModel current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauEffModel

//______________________________________________________________________________
void LauEmbeddedData::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauEmbeddedData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauEmbeddedData::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauEmbeddedData::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauEmbeddedData(void *p) {
      delete (static_cast<::LauEmbeddedData*>(p));
   }
   static void deleteArray_LauEmbeddedData(void *p) {
      delete [] (static_cast<::LauEmbeddedData*>(p));
   }
   static void destruct_LauEmbeddedData(void *p) {
      typedef ::LauEmbeddedData current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauEmbeddedData

//______________________________________________________________________________
void LauExponentialPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauExponentialPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauExponentialPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauExponentialPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauExponentialPdf(void *p) {
      delete (static_cast<::LauExponentialPdf*>(p));
   }
   static void deleteArray_LauExponentialPdf(void *p) {
      delete [] (static_cast<::LauExponentialPdf*>(p));
   }
   static void destruct_LauExponentialPdf(void *p) {
      typedef ::LauExponentialPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauExponentialPdf

//______________________________________________________________________________
void LauFitNtuple::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauFitNtuple.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauFitNtuple::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauFitNtuple::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauFitNtuple(void *p) {
      delete (static_cast<::LauFitNtuple*>(p));
   }
   static void deleteArray_LauFitNtuple(void *p) {
      delete [] (static_cast<::LauFitNtuple*>(p));
   }
   static void destruct_LauFitNtuple(void *p) {
      typedef ::LauFitNtuple current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauFitNtuple

//______________________________________________________________________________
void LauPrint::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauPrint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauPrint::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauPrint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LauPrint(void *p) {
      return  p ? new(p) ::LauPrint : new ::LauPrint;
   }
   static void *newArray_LauPrint(Long_t nElements, void *p) {
      return p ? new(p) ::LauPrint[nElements] : new ::LauPrint[nElements];
   }
   // Wrapper around operator delete
   static void delete_LauPrint(void *p) {
      delete (static_cast<::LauPrint*>(p));
   }
   static void deleteArray_LauPrint(void *p) {
      delete [] (static_cast<::LauPrint*>(p));
   }
   static void destruct_LauPrint(void *p) {
      typedef ::LauPrint current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauPrint

//______________________________________________________________________________
void LauFitter::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauFitter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauFitter::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauFitter::Class(),this);
   }
}

namespace ROOT {
} // end of namespace ROOT for class ::LauFitter

//______________________________________________________________________________
void LauFlatNR::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauFlatNR.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauFlatNR::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauFlatNR::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauFlatNR(void *p) {
      delete (static_cast<::LauFlatNR*>(p));
   }
   static void deleteArray_LauFlatNR(void *p) {
      delete [] (static_cast<::LauFlatNR*>(p));
   }
   static void destruct_LauFlatNR(void *p) {
      typedef ::LauFlatNR current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauFlatNR

//______________________________________________________________________________
void LauFlatteRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauFlatteRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauFlatteRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauFlatteRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauFlatteRes(void *p) {
      delete (static_cast<::LauFlatteRes*>(p));
   }
   static void deleteArray_LauFlatteRes(void *p) {
      delete [] (static_cast<::LauFlatteRes*>(p));
   }
   static void destruct_LauFlatteRes(void *p) {
      typedef ::LauFlatteRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauFlatteRes

//______________________________________________________________________________
void LauGaussIncohRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauGaussIncohRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauGaussIncohRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauGaussIncohRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauGaussIncohRes(void *p) {
      delete (static_cast<::LauGaussIncohRes*>(p));
   }
   static void deleteArray_LauGaussIncohRes(void *p) {
      delete [] (static_cast<::LauGaussIncohRes*>(p));
   }
   static void destruct_LauGaussIncohRes(void *p) {
      typedef ::LauGaussIncohRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauGaussIncohRes

//______________________________________________________________________________
void LauGaussPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauGaussPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauGaussPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauGaussPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauGaussPdf(void *p) {
      delete (static_cast<::LauGaussPdf*>(p));
   }
   static void deleteArray_LauGaussPdf(void *p) {
      delete [] (static_cast<::LauGaussPdf*>(p));
   }
   static void destruct_LauGaussPdf(void *p) {
      typedef ::LauGaussPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauGaussPdf

//______________________________________________________________________________
void LauGenNtuple::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauGenNtuple.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauGenNtuple::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauGenNtuple::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauGenNtuple(void *p) {
      delete (static_cast<::LauGenNtuple*>(p));
   }
   static void deleteArray_LauGenNtuple(void *p) {
      delete [] (static_cast<::LauGenNtuple*>(p));
   }
   static void destruct_LauGenNtuple(void *p) {
      typedef ::LauGenNtuple current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauGenNtuple

//______________________________________________________________________________
void LauGounarisSakuraiRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauGounarisSakuraiRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauGounarisSakuraiRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauGounarisSakuraiRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauGounarisSakuraiRes(void *p) {
      delete (static_cast<::LauGounarisSakuraiRes*>(p));
   }
   static void deleteArray_LauGounarisSakuraiRes(void *p) {
      delete [] (static_cast<::LauGounarisSakuraiRes*>(p));
   }
   static void destruct_LauGounarisSakuraiRes(void *p) {
      typedef ::LauGounarisSakuraiRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauGounarisSakuraiRes

//______________________________________________________________________________
void LauIntegrals::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauIntegrals.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauIntegrals::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauIntegrals::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LauIntegrals(void *p) {
      return  p ? new(p) ::LauIntegrals : new ::LauIntegrals;
   }
   static void *newArray_LauIntegrals(Long_t nElements, void *p) {
      return p ? new(p) ::LauIntegrals[nElements] : new ::LauIntegrals[nElements];
   }
   // Wrapper around operator delete
   static void delete_LauIntegrals(void *p) {
      delete (static_cast<::LauIntegrals*>(p));
   }
   static void deleteArray_LauIntegrals(void *p) {
      delete [] (static_cast<::LauIntegrals*>(p));
   }
   static void destruct_LauIntegrals(void *p) {
      typedef ::LauIntegrals current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauIntegrals

//______________________________________________________________________________
void LauIsobarDynamics::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauIsobarDynamics.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauIsobarDynamics::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauIsobarDynamics::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauIsobarDynamics(void *p) {
      delete (static_cast<::LauIsobarDynamics*>(p));
   }
   static void deleteArray_LauIsobarDynamics(void *p) {
      delete [] (static_cast<::LauIsobarDynamics*>(p));
   }
   static void destruct_LauIsobarDynamics(void *p) {
      typedef ::LauIsobarDynamics current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauIsobarDynamics

//______________________________________________________________________________
void LauKMatrixProdPole::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauKMatrixProdPole.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauKMatrixProdPole::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauKMatrixProdPole::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauKMatrixProdPole(void *p) {
      delete (static_cast<::LauKMatrixProdPole*>(p));
   }
   static void deleteArray_LauKMatrixProdPole(void *p) {
      delete [] (static_cast<::LauKMatrixProdPole*>(p));
   }
   static void destruct_LauKMatrixProdPole(void *p) {
      typedef ::LauKMatrixProdPole current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauKMatrixProdPole

//______________________________________________________________________________
void LauKMatrixProdSVP::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauKMatrixProdSVP.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauKMatrixProdSVP::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauKMatrixProdSVP::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauKMatrixProdSVP(void *p) {
      delete (static_cast<::LauKMatrixProdSVP*>(p));
   }
   static void deleteArray_LauKMatrixProdSVP(void *p) {
      delete [] (static_cast<::LauKMatrixProdSVP*>(p));
   }
   static void destruct_LauKMatrixProdSVP(void *p) {
      typedef ::LauKMatrixProdSVP current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauKMatrixProdSVP

//______________________________________________________________________________
void LauKMatrixPropFactory::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauKMatrixPropFactory.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauKMatrixPropFactory::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauKMatrixPropFactory::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauKMatrixPropFactory(void *p) {
      delete (static_cast<::LauKMatrixPropFactory*>(p));
   }
   static void deleteArray_LauKMatrixPropFactory(void *p) {
      delete [] (static_cast<::LauKMatrixPropFactory*>(p));
   }
   static void destruct_LauKMatrixPropFactory(void *p) {
      typedef ::LauKMatrixPropFactory current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauKMatrixPropFactory

//______________________________________________________________________________
void LauResonanceMaker::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauResonanceMaker.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauResonanceMaker::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauResonanceMaker::Class(),this);
   }
}

namespace ROOT {
} // end of namespace ROOT for class ::LauResonanceMaker

//______________________________________________________________________________
void LauResonanceInfo::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauResonanceInfo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauResonanceInfo::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauResonanceInfo::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauResonanceInfo(void *p) {
      delete (static_cast<::LauResonanceInfo*>(p));
   }
   static void deleteArray_LauResonanceInfo(void *p) {
      delete [] (static_cast<::LauResonanceInfo*>(p));
   }
   static void destruct_LauResonanceInfo(void *p) {
      typedef ::LauResonanceInfo current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauResonanceInfo

//______________________________________________________________________________
void LauKMatrixPropagator::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauKMatrixPropagator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauKMatrixPropagator::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauKMatrixPropagator::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauKMatrixPropagator(void *p) {
      delete (static_cast<::LauKMatrixPropagator*>(p));
   }
   static void deleteArray_LauKMatrixPropagator(void *p) {
      delete [] (static_cast<::LauKMatrixPropagator*>(p));
   }
   static void destruct_LauKMatrixPropagator(void *p) {
      typedef ::LauKMatrixPropagator current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauKMatrixPropagator

//______________________________________________________________________________
void LauKappaRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauKappaRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauKappaRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauKappaRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauKappaRes(void *p) {
      delete (static_cast<::LauKappaRes*>(p));
   }
   static void deleteArray_LauKappaRes(void *p) {
      delete [] (static_cast<::LauKappaRes*>(p));
   }
   static void destruct_LauKappaRes(void *p) {
      typedef ::LauKappaRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauKappaRes

//______________________________________________________________________________
void LauLASSBWRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauLASSBWRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauLASSBWRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauLASSBWRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauLASSBWRes(void *p) {
      delete (static_cast<::LauLASSBWRes*>(p));
   }
   static void deleteArray_LauLASSBWRes(void *p) {
      delete [] (static_cast<::LauLASSBWRes*>(p));
   }
   static void destruct_LauLASSBWRes(void *p) {
      typedef ::LauLASSBWRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauLASSBWRes

//______________________________________________________________________________
void LauLASSNRRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauLASSNRRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauLASSNRRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauLASSNRRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauLASSNRRes(void *p) {
      delete (static_cast<::LauLASSNRRes*>(p));
   }
   static void deleteArray_LauLASSNRRes(void *p) {
      delete [] (static_cast<::LauLASSNRRes*>(p));
   }
   static void destruct_LauLASSNRRes(void *p) {
      typedef ::LauLASSNRRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauLASSNRRes

//______________________________________________________________________________
void LauLASSRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauLASSRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauLASSRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauLASSRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauLASSRes(void *p) {
      delete (static_cast<::LauLASSRes*>(p));
   }
   static void deleteArray_LauLASSRes(void *p) {
      delete [] (static_cast<::LauLASSRes*>(p));
   }
   static void destruct_LauLASSRes(void *p) {
      typedef ::LauLASSRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauLASSRes

//______________________________________________________________________________
void LauLinearPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauLinearPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauLinearPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauLinearPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauLinearPdf(void *p) {
      delete (static_cast<::LauLinearPdf*>(p));
   }
   static void deleteArray_LauLinearPdf(void *p) {
      delete [] (static_cast<::LauLinearPdf*>(p));
   }
   static void destruct_LauLinearPdf(void *p) {
      typedef ::LauLinearPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauLinearPdf

//______________________________________________________________________________
void LauMagPhaseCPCoeffSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauMagPhaseCPCoeffSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauMagPhaseCPCoeffSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauMagPhaseCPCoeffSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauMagPhaseCPCoeffSet(void *p) {
      delete (static_cast<::LauMagPhaseCPCoeffSet*>(p));
   }
   static void deleteArray_LauMagPhaseCPCoeffSet(void *p) {
      delete [] (static_cast<::LauMagPhaseCPCoeffSet*>(p));
   }
   static void destruct_LauMagPhaseCPCoeffSet(void *p) {
      typedef ::LauMagPhaseCPCoeffSet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauMagPhaseCPCoeffSet

//______________________________________________________________________________
void LauMagPhaseCoeffSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauMagPhaseCoeffSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauMagPhaseCoeffSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauMagPhaseCoeffSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauMagPhaseCoeffSet(void *p) {
      delete (static_cast<::LauMagPhaseCoeffSet*>(p));
   }
   static void deleteArray_LauMagPhaseCoeffSet(void *p) {
      delete [] (static_cast<::LauMagPhaseCoeffSet*>(p));
   }
   static void destruct_LauMagPhaseCoeffSet(void *p) {
      typedef ::LauMagPhaseCoeffSet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauMagPhaseCoeffSet

//______________________________________________________________________________
void LauMergeDataFiles::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauMergeDataFiles.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauMergeDataFiles::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauMergeDataFiles::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauMergeDataFiles(void *p) {
      delete (static_cast<::LauMergeDataFiles*>(p));
   }
   static void deleteArray_LauMergeDataFiles(void *p) {
      delete [] (static_cast<::LauMergeDataFiles*>(p));
   }
   static void destruct_LauMergeDataFiles(void *p) {
      typedef ::LauMergeDataFiles current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauMergeDataFiles

//______________________________________________________________________________
void LauMinuit::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauMinuit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauMinuit::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauMinuit::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauMinuit(void *p) {
      delete (static_cast<::LauMinuit*>(p));
   }
   static void deleteArray_LauMinuit(void *p) {
      delete [] (static_cast<::LauMinuit*>(p));
   }
   static void destruct_LauMinuit(void *p) {
      typedef ::LauMinuit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauMinuit

//______________________________________________________________________________
void LauModIndPartWaveMagPhase::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauModIndPartWaveMagPhase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauModIndPartWaveMagPhase::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauModIndPartWaveMagPhase::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauModIndPartWaveMagPhase(void *p) {
      delete (static_cast<::LauModIndPartWaveMagPhase*>(p));
   }
   static void deleteArray_LauModIndPartWaveMagPhase(void *p) {
      delete [] (static_cast<::LauModIndPartWaveMagPhase*>(p));
   }
   static void destruct_LauModIndPartWaveMagPhase(void *p) {
      typedef ::LauModIndPartWaveMagPhase current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauModIndPartWaveMagPhase

//______________________________________________________________________________
void LauModIndPartWaveRealImag::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauModIndPartWaveRealImag.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauModIndPartWaveRealImag::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauModIndPartWaveRealImag::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauModIndPartWaveRealImag(void *p) {
      delete (static_cast<::LauModIndPartWaveRealImag*>(p));
   }
   static void deleteArray_LauModIndPartWaveRealImag(void *p) {
      delete [] (static_cast<::LauModIndPartWaveRealImag*>(p));
   }
   static void destruct_LauModIndPartWaveRealImag(void *p) {
      typedef ::LauModIndPartWaveRealImag current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauModIndPartWaveRealImag

//______________________________________________________________________________
void LauNRAmplitude::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauNRAmplitude.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauNRAmplitude::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauNRAmplitude::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauNRAmplitude(void *p) {
      delete (static_cast<::LauNRAmplitude*>(p));
   }
   static void deleteArray_LauNRAmplitude(void *p) {
      delete [] (static_cast<::LauNRAmplitude*>(p));
   }
   static void destruct_LauNRAmplitude(void *p) {
      typedef ::LauNRAmplitude current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauNRAmplitude

//______________________________________________________________________________
void LauNovosibirskPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauNovosibirskPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauNovosibirskPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauNovosibirskPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauNovosibirskPdf(void *p) {
      delete (static_cast<::LauNovosibirskPdf*>(p));
   }
   static void deleteArray_LauNovosibirskPdf(void *p) {
      delete [] (static_cast<::LauNovosibirskPdf*>(p));
   }
   static void destruct_LauNovosibirskPdf(void *p) {
      typedef ::LauNovosibirskPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauNovosibirskPdf

//______________________________________________________________________________
void LauParametricStepFuncPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauParametricStepFuncPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauParametricStepFuncPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauParametricStepFuncPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauParametricStepFuncPdf(void *p) {
      delete (static_cast<::LauParametricStepFuncPdf*>(p));
   }
   static void deleteArray_LauParametricStepFuncPdf(void *p) {
      delete [] (static_cast<::LauParametricStepFuncPdf*>(p));
   }
   static void destruct_LauParametricStepFuncPdf(void *p) {
      typedef ::LauParametricStepFuncPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauParametricStepFuncPdf

//______________________________________________________________________________
void LauParticlePDG::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauParticlePDG.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauParticlePDG::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauParticlePDG::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauParticlePDG(void *p) {
      delete (static_cast<::LauParticlePDG*>(p));
   }
   static void deleteArray_LauParticlePDG(void *p) {
      delete [] (static_cast<::LauParticlePDG*>(p));
   }
   static void destruct_LauParticlePDG(void *p) {
      typedef ::LauParticlePDG current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauParticlePDG

//______________________________________________________________________________
void LauPolNR::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauPolNR.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauPolNR::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauPolNR::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauPolNR(void *p) {
      delete (static_cast<::LauPolNR*>(p));
   }
   static void deleteArray_LauPolNR(void *p) {
      delete [] (static_cast<::LauPolNR*>(p));
   }
   static void destruct_LauPolNR(void *p) {
      typedef ::LauPolNR current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauPolNR

//______________________________________________________________________________
void LauPolarFormFactorNR::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauPolarFormFactorNR.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauPolarFormFactorNR::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauPolarFormFactorNR::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauPolarFormFactorNR(void *p) {
      delete (static_cast<::LauPolarFormFactorNR*>(p));
   }
   static void deleteArray_LauPolarFormFactorNR(void *p) {
      delete [] (static_cast<::LauPolarFormFactorNR*>(p));
   }
   static void destruct_LauPolarFormFactorNR(void *p) {
      typedef ::LauPolarFormFactorNR current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauPolarFormFactorNR

//______________________________________________________________________________
void LauPolarFormFactorSymNR::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauPolarFormFactorSymNR.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauPolarFormFactorSymNR::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauPolarFormFactorSymNR::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauPolarFormFactorSymNR(void *p) {
      delete (static_cast<::LauPolarFormFactorSymNR*>(p));
   }
   static void deleteArray_LauPolarFormFactorSymNR(void *p) {
      delete [] (static_cast<::LauPolarFormFactorSymNR*>(p));
   }
   static void destruct_LauPolarFormFactorSymNR(void *p) {
      typedef ::LauPolarFormFactorSymNR current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauPolarFormFactorSymNR

//______________________________________________________________________________
void LauPolarGammaCPCoeffSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauPolarGammaCPCoeffSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauPolarGammaCPCoeffSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauPolarGammaCPCoeffSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauPolarGammaCPCoeffSet(void *p) {
      delete (static_cast<::LauPolarGammaCPCoeffSet*>(p));
   }
   static void deleteArray_LauPolarGammaCPCoeffSet(void *p) {
      delete [] (static_cast<::LauPolarGammaCPCoeffSet*>(p));
   }
   static void destruct_LauPolarGammaCPCoeffSet(void *p) {
      typedef ::LauPolarGammaCPCoeffSet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauPolarGammaCPCoeffSet

//______________________________________________________________________________
void LauPoleRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauPoleRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauPoleRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauPoleRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauPoleRes(void *p) {
      delete (static_cast<::LauPoleRes*>(p));
   }
   static void deleteArray_LauPoleRes(void *p) {
      delete [] (static_cast<::LauPoleRes*>(p));
   }
   static void destruct_LauPoleRes(void *p) {
      typedef ::LauPoleRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauPoleRes

//______________________________________________________________________________
void LauRealImagCPCoeffSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauRealImagCPCoeffSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauRealImagCPCoeffSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauRealImagCPCoeffSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauRealImagCPCoeffSet(void *p) {
      delete (static_cast<::LauRealImagCPCoeffSet*>(p));
   }
   static void deleteArray_LauRealImagCPCoeffSet(void *p) {
      delete [] (static_cast<::LauRealImagCPCoeffSet*>(p));
   }
   static void destruct_LauRealImagCPCoeffSet(void *p) {
      typedef ::LauRealImagCPCoeffSet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauRealImagCPCoeffSet

//______________________________________________________________________________
void LauRealImagCoeffSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauRealImagCoeffSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauRealImagCoeffSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauRealImagCoeffSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauRealImagCoeffSet(void *p) {
      delete (static_cast<::LauRealImagCoeffSet*>(p));
   }
   static void deleteArray_LauRealImagCoeffSet(void *p) {
      delete [] (static_cast<::LauRealImagCoeffSet*>(p));
   }
   static void destruct_LauRealImagCoeffSet(void *p) {
      typedef ::LauRealImagCoeffSet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauRealImagCoeffSet

//______________________________________________________________________________
void LauRealImagGammaCPCoeffSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauRealImagGammaCPCoeffSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauRealImagGammaCPCoeffSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauRealImagGammaCPCoeffSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauRealImagGammaCPCoeffSet(void *p) {
      delete (static_cast<::LauRealImagGammaCPCoeffSet*>(p));
   }
   static void deleteArray_LauRealImagGammaCPCoeffSet(void *p) {
      delete [] (static_cast<::LauRealImagGammaCPCoeffSet*>(p));
   }
   static void destruct_LauRealImagGammaCPCoeffSet(void *p) {
      typedef ::LauRealImagGammaCPCoeffSet current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauRealImagGammaCPCoeffSet

//______________________________________________________________________________
void LauRelBreitWignerRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauRelBreitWignerRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauRelBreitWignerRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauRelBreitWignerRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauRelBreitWignerRes(void *p) {
      delete (static_cast<::LauRelBreitWignerRes*>(p));
   }
   static void deleteArray_LauRelBreitWignerRes(void *p) {
      delete [] (static_cast<::LauRelBreitWignerRes*>(p));
   }
   static void destruct_LauRelBreitWignerRes(void *p) {
      typedef ::LauRelBreitWignerRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauRelBreitWignerRes

//______________________________________________________________________________
void LauRescattering2Res::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauRescattering2Res.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauRescattering2Res::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauRescattering2Res::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauRescattering2Res(void *p) {
      delete (static_cast<::LauRescattering2Res*>(p));
   }
   static void deleteArray_LauRescattering2Res(void *p) {
      delete [] (static_cast<::LauRescattering2Res*>(p));
   }
   static void destruct_LauRescattering2Res(void *p) {
      typedef ::LauRescattering2Res current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauRescattering2Res

//______________________________________________________________________________
void LauRescatteringRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauRescatteringRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauRescatteringRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauRescatteringRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauRescatteringRes(void *p) {
      delete (static_cast<::LauRescatteringRes*>(p));
   }
   static void deleteArray_LauRescatteringRes(void *p) {
      delete [] (static_cast<::LauRescatteringRes*>(p));
   }
   static void destruct_LauRescatteringRes(void *p) {
      typedef ::LauRescatteringRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauRescatteringRes

//______________________________________________________________________________
void LauResultsExtractor::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauResultsExtractor.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauResultsExtractor::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauResultsExtractor::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauResultsExtractor(void *p) {
      delete (static_cast<::LauResultsExtractor*>(p));
   }
   static void deleteArray_LauResultsExtractor(void *p) {
      delete [] (static_cast<::LauResultsExtractor*>(p));
   }
   static void destruct_LauResultsExtractor(void *p) {
      typedef ::LauResultsExtractor current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauResultsExtractor

//______________________________________________________________________________
void LauRhoOmegaMix::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauRhoOmegaMix.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauRhoOmegaMix::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauRhoOmegaMix::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauRhoOmegaMix(void *p) {
      delete (static_cast<::LauRhoOmegaMix*>(p));
   }
   static void deleteArray_LauRhoOmegaMix(void *p) {
      delete [] (static_cast<::LauRhoOmegaMix*>(p));
   }
   static void destruct_LauRhoOmegaMix(void *p) {
      typedef ::LauRhoOmegaMix current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauRhoOmegaMix

//______________________________________________________________________________
void LauScfMap::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauScfMap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauScfMap::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauScfMap::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LauScfMap(void *p) {
      return  p ? new(p) ::LauScfMap : new ::LauScfMap;
   }
   static void *newArray_LauScfMap(Long_t nElements, void *p) {
      return p ? new(p) ::LauScfMap[nElements] : new ::LauScfMap[nElements];
   }
   // Wrapper around operator delete
   static void delete_LauScfMap(void *p) {
      delete (static_cast<::LauScfMap*>(p));
   }
   static void deleteArray_LauScfMap(void *p) {
      delete [] (static_cast<::LauScfMap*>(p));
   }
   static void destruct_LauScfMap(void *p) {
      typedef ::LauScfMap current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauScfMap

//______________________________________________________________________________
void LauSigmaRes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauSigmaRes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauSigmaRes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauSigmaRes::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauSigmaRes(void *p) {
      delete (static_cast<::LauSigmaRes*>(p));
   }
   static void deleteArray_LauSigmaRes(void *p) {
      delete [] (static_cast<::LauSigmaRes*>(p));
   }
   static void destruct_LauSigmaRes(void *p) {
      typedef ::LauSigmaRes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauSigmaRes

//______________________________________________________________________________
void LauSigmoidPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauSigmoidPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauSigmoidPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauSigmoidPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauSigmoidPdf(void *p) {
      delete (static_cast<::LauSigmoidPdf*>(p));
   }
   static void deleteArray_LauSigmoidPdf(void *p) {
      delete [] (static_cast<::LauSigmoidPdf*>(p));
   }
   static void destruct_LauSigmoidPdf(void *p) {
      typedef ::LauSigmoidPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauSigmoidPdf

//______________________________________________________________________________
void LauSimFitCoordinator::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauSimFitCoordinator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauSimFitCoordinator::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauSimFitCoordinator::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauSimFitCoordinator(void *p) {
      delete (static_cast<::LauSimFitCoordinator*>(p));
   }
   static void deleteArray_LauSimFitCoordinator(void *p) {
      delete [] (static_cast<::LauSimFitCoordinator*>(p));
   }
   static void destruct_LauSimFitCoordinator(void *p) {
      typedef ::LauSimFitCoordinator current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauSimFitCoordinator

//______________________________________________________________________________
void LauSimpleFitModel::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauSimpleFitModel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauSimpleFitModel::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauSimpleFitModel::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauSimpleFitModel(void *p) {
      delete (static_cast<::LauSimpleFitModel*>(p));
   }
   static void deleteArray_LauSimpleFitModel(void *p) {
      delete [] (static_cast<::LauSimpleFitModel*>(p));
   }
   static void destruct_LauSimpleFitModel(void *p) {
      typedef ::LauSimpleFitModel current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauSimpleFitModel

namespace ROOT {
   // Wrappers around operator new
   static void *new_LauString(void *p) {
      return  p ? new(p) ::LauString : new ::LauString;
   }
   static void *newArray_LauString(Long_t nElements, void *p) {
      return p ? new(p) ::LauString[nElements] : new ::LauString[nElements];
   }
   // Wrapper around operator delete
   static void delete_LauString(void *p) {
      delete (static_cast<::LauString*>(p));
   }
   static void deleteArray_LauString(void *p) {
      delete [] (static_cast<::LauString*>(p));
   }
   static void destruct_LauString(void *p) {
      typedef ::LauString current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauString

//______________________________________________________________________________
void LauSumPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauSumPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauSumPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauSumPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauSumPdf(void *p) {
      delete (static_cast<::LauSumPdf*>(p));
   }
   static void deleteArray_LauSumPdf(void *p) {
      delete [] (static_cast<::LauSumPdf*>(p));
   }
   static void destruct_LauSumPdf(void *p) {
      typedef ::LauSumPdf current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauSumPdf

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauTextFileParser(void *p) {
      delete (static_cast<::LauTextFileParser*>(p));
   }
   static void deleteArray_LauTextFileParser(void *p) {
      delete [] (static_cast<::LauTextFileParser*>(p));
   }
   static void destruct_LauTextFileParser(void *p) {
      typedef ::LauTextFileParser current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauTextFileParser

//______________________________________________________________________________
void LauVetoes::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauVetoes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauVetoes::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauVetoes::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LauVetoes(void *p) {
      return  p ? new(p) ::LauVetoes : new ::LauVetoes;
   }
   static void *newArray_LauVetoes(Long_t nElements, void *p) {
      return p ? new(p) ::LauVetoes[nElements] : new ::LauVetoes[nElements];
   }
   // Wrapper around operator delete
   static void delete_LauVetoes(void *p) {
      delete (static_cast<::LauVetoes*>(p));
   }
   static void deleteArray_LauVetoes(void *p) {
      delete [] (static_cast<::LauVetoes*>(p));
   }
   static void destruct_LauVetoes(void *p) {
      typedef ::LauVetoes current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauVetoes

//______________________________________________________________________________
void LauWeightedSumEffModel::Streamer(TBuffer &R__b)
{
   // Stream an object of class LauWeightedSumEffModel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LauWeightedSumEffModel::Class(),this);
   } else {
      R__b.WriteClassBuffer(LauWeightedSumEffModel::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LauWeightedSumEffModel(void *p) {
      delete (static_cast<::LauWeightedSumEffModel*>(p));
   }
   static void deleteArray_LauWeightedSumEffModel(void *p) {
      delete [] (static_cast<::LauWeightedSumEffModel*>(p));
   }
   static void destruct_LauWeightedSumEffModel(void *p) {
      typedef ::LauWeightedSumEffModel current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::LauWeightedSumEffModel

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = nullptr);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 386,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<string>","std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<string>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<string>*>(nullptr))->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete (static_cast<vector<string>*>(p));
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] (static_cast<vector<string>*>(p));
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *maplEintcOvectorlEstringgRsPgR_Dictionary();
   static void maplEintcOvectorlEstringgRsPgR_TClassManip(TClass*);
   static void *new_maplEintcOvectorlEstringgRsPgR(void *p = nullptr);
   static void *newArray_maplEintcOvectorlEstringgRsPgR(Long_t size, void *p);
   static void delete_maplEintcOvectorlEstringgRsPgR(void *p);
   static void deleteArray_maplEintcOvectorlEstringgRsPgR(void *p);
   static void destruct_maplEintcOvectorlEstringgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,vector<string> >*)
   {
      map<int,vector<string> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,vector<string> >));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,vector<string> >", -2, "map", 100,
                  typeid(map<int,vector<string> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOvectorlEstringgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,vector<string> >) );
      instance.SetNew(&new_maplEintcOvectorlEstringgRsPgR);
      instance.SetNewArray(&newArray_maplEintcOvectorlEstringgRsPgR);
      instance.SetDelete(&delete_maplEintcOvectorlEstringgRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOvectorlEstringgRsPgR);
      instance.SetDestructor(&destruct_maplEintcOvectorlEstringgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,vector<string> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("map<int,vector<string> >","std::map<int, std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >, std::less<int>, std::allocator<std::pair<int const, std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const map<int,vector<string> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOvectorlEstringgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const map<int,vector<string> >*>(nullptr))->GetClass();
      maplEintcOvectorlEstringgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOvectorlEstringgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOvectorlEstringgRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<int,vector<string> > : new map<int,vector<string> >;
   }
   static void *newArray_maplEintcOvectorlEstringgRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<int,vector<string> >[nElements] : new map<int,vector<string> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOvectorlEstringgRsPgR(void *p) {
      delete (static_cast<map<int,vector<string> >*>(p));
   }
   static void deleteArray_maplEintcOvectorlEstringgRsPgR(void *p) {
      delete [] (static_cast<map<int,vector<string> >*>(p));
   }
   static void destruct_maplEintcOvectorlEstringgRsPgR(void *p) {
      typedef map<int,vector<string> > current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class map<int,vector<string> >

namespace ROOT {
   static TClass *maplELauParametermUcOdoublegR_Dictionary();
   static void maplELauParametermUcOdoublegR_TClassManip(TClass*);
   static void *new_maplELauParametermUcOdoublegR(void *p = nullptr);
   static void *newArray_maplELauParametermUcOdoublegR(Long_t size, void *p);
   static void delete_maplELauParametermUcOdoublegR(void *p);
   static void deleteArray_maplELauParametermUcOdoublegR(void *p);
   static void destruct_maplELauParametermUcOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<LauParameter*,double>*)
   {
      map<LauParameter*,double> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<LauParameter*,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<LauParameter*,double>", -2, "map", 100,
                  typeid(map<LauParameter*,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplELauParametermUcOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<LauParameter*,double>) );
      instance.SetNew(&new_maplELauParametermUcOdoublegR);
      instance.SetNewArray(&newArray_maplELauParametermUcOdoublegR);
      instance.SetDelete(&delete_maplELauParametermUcOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplELauParametermUcOdoublegR);
      instance.SetDestructor(&destruct_maplELauParametermUcOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<LauParameter*,double> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("map<LauParameter*,double>","std::map<LauParameter*, double, std::less<LauParameter*>, std::allocator<std::pair<LauParameter* const, double> > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const map<LauParameter*,double>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplELauParametermUcOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const map<LauParameter*,double>*>(nullptr))->GetClass();
      maplELauParametermUcOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplELauParametermUcOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplELauParametermUcOdoublegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<LauParameter*,double> : new map<LauParameter*,double>;
   }
   static void *newArray_maplELauParametermUcOdoublegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<LauParameter*,double>[nElements] : new map<LauParameter*,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplELauParametermUcOdoublegR(void *p) {
      delete (static_cast<map<LauParameter*,double>*>(p));
   }
   static void deleteArray_maplELauParametermUcOdoublegR(void *p) {
      delete [] (static_cast<map<LauParameter*,double>*>(p));
   }
   static void destruct_maplELauParametermUcOdoublegR(void *p) {
      typedef map<LauParameter*,double> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class map<LauParameter*,double>

namespace {
  void TriggerDictionaryInitialization_libLaurapLpL_Impl() {
    static const char* headers[] = {
"/home/oryan/laura/inc/Lau1DCubicSpline.hh",
"/home/oryan/laura/inc/Lau1DHistPdf.hh",
"/home/oryan/laura/inc/Lau2DAbsDP.hh",
"/home/oryan/laura/inc/Lau2DAbsDPPdf.hh",
"/home/oryan/laura/inc/Lau2DAbsHistDP.hh",
"/home/oryan/laura/inc/Lau2DAbsHistDPPdf.hh",
"/home/oryan/laura/inc/Lau2DCubicSpline.hh",
"/home/oryan/laura/inc/Lau2DHistDP.hh",
"/home/oryan/laura/inc/Lau2DHistDPPdf.hh",
"/home/oryan/laura/inc/Lau2DHistPdf.hh",
"/home/oryan/laura/inc/Lau2DSplineDP.hh",
"/home/oryan/laura/inc/Lau2DSplineDPPdf.hh",
"/home/oryan/laura/inc/LauASqMaxFinder.hh",
"/home/oryan/laura/inc/LauAbsBkgndDPModel.hh",
"/home/oryan/laura/inc/LauAbsCoeffSet.hh",
"/home/oryan/laura/inc/LauAbsEffModel.hh",
"/home/oryan/laura/inc/LauAbsFitModel.hh",
"/home/oryan/laura/inc/LauAbsFitter.hh",
"/home/oryan/laura/inc/LauAbsIncohRes.hh",
"/home/oryan/laura/inc/LauAbsModIndPartWave.hh",
"/home/oryan/laura/inc/LauAbsPdf.hh",
"/home/oryan/laura/inc/LauAbsRValue.hh",
"/home/oryan/laura/inc/LauAbsResonance.hh",
"/home/oryan/laura/inc/LauArgusPdf.hh",
"/home/oryan/laura/inc/LauAsymmCalc.hh",
"/home/oryan/laura/inc/LauBelleCPCoeffSet.hh",
"/home/oryan/laura/inc/LauBelleNR.hh",
"/home/oryan/laura/inc/LauBelleSymNR.hh",
"/home/oryan/laura/inc/LauBifurcatedGaussPdf.hh",
"/home/oryan/laura/inc/LauBkgndDPModel.hh",
"/home/oryan/laura/inc/LauBlattWeisskopfFactor.hh",
"/home/oryan/laura/inc/LauBlind.hh",
"/home/oryan/laura/inc/LauBreitWignerRes.hh",
"/home/oryan/laura/inc/LauCPFitModel.hh",
"/home/oryan/laura/inc/LauCacheData.hh",
"/home/oryan/laura/inc/LauCalcChiSq.hh",
"/home/oryan/laura/inc/LauCartesianCPCoeffSet.hh",
"/home/oryan/laura/inc/LauCartesianGammaCPCoeffSet.hh",
"/home/oryan/laura/inc/LauChebychevPdf.hh",
"/home/oryan/laura/inc/LauCleoCPCoeffSet.hh",
"/home/oryan/laura/inc/LauComplex.hh",
"/home/oryan/laura/inc/LauConstants.hh",
"/home/oryan/laura/inc/LauCruijffPdf.hh",
"/home/oryan/laura/inc/LauCrystalBallPdf.hh",
"/home/oryan/laura/inc/LauDPDepBifurGaussPdf.hh",
"/home/oryan/laura/inc/LauDPDepCruijffPdf.hh",
"/home/oryan/laura/inc/LauDPDepGaussPdf.hh",
"/home/oryan/laura/inc/LauDPDepMapPdf.hh",
"/home/oryan/laura/inc/LauDPDepSumPdf.hh",
"/home/oryan/laura/inc/LauDPPartialIntegralInfo.hh",
"/home/oryan/laura/inc/LauDabbaRes.hh",
"/home/oryan/laura/inc/LauDatabasePDG.hh",
"/home/oryan/laura/inc/LauDaughters.hh",
"/home/oryan/laura/inc/LauEFKLLMRes.hh",
"/home/oryan/laura/inc/LauEffModel.hh",
"/home/oryan/laura/inc/LauEmbeddedData.hh",
"/home/oryan/laura/inc/LauExponentialPdf.hh",
"/home/oryan/laura/inc/LauFitDataTree.hh",
"/home/oryan/laura/inc/LauFitNtuple.hh",
"/home/oryan/laura/inc/LauFitObject.hh",
"/home/oryan/laura/inc/LauFitter.hh",
"/home/oryan/laura/inc/LauFlatNR.hh",
"/home/oryan/laura/inc/LauFlatteRes.hh",
"/home/oryan/laura/inc/LauFormulaPar.hh",
"/home/oryan/laura/inc/LauGaussIncohRes.hh",
"/home/oryan/laura/inc/LauGaussPdf.hh",
"/home/oryan/laura/inc/LauGenNtuple.hh",
"/home/oryan/laura/inc/LauGounarisSakuraiRes.hh",
"/home/oryan/laura/inc/LauIntegrals.hh",
"/home/oryan/laura/inc/LauIsobarDynamics.hh",
"/home/oryan/laura/inc/LauKMatrixProdPole.hh",
"/home/oryan/laura/inc/LauKMatrixProdSVP.hh",
"/home/oryan/laura/inc/LauKMatrixPropFactory.hh",
"/home/oryan/laura/inc/LauKMatrixPropagator.hh",
"/home/oryan/laura/inc/LauKappaRes.hh",
"/home/oryan/laura/inc/LauKinematics.hh",
"/home/oryan/laura/inc/LauLASSBWRes.hh",
"/home/oryan/laura/inc/LauLASSNRRes.hh",
"/home/oryan/laura/inc/LauLASSRes.hh",
"/home/oryan/laura/inc/LauLinearPdf.hh",
"/home/oryan/laura/inc/LauMagPhaseCPCoeffSet.hh",
"/home/oryan/laura/inc/LauMagPhaseCoeffSet.hh",
"/home/oryan/laura/inc/LauMergeDataFiles.hh",
"/home/oryan/laura/inc/LauMinuit.hh",
"/home/oryan/laura/inc/LauModIndPartWaveMagPhase.hh",
"/home/oryan/laura/inc/LauModIndPartWaveRealImag.hh",
"/home/oryan/laura/inc/LauNRAmplitude.hh",
"/home/oryan/laura/inc/LauNovosibirskPdf.hh",
"/home/oryan/laura/inc/LauParamFixed.hh",
"/home/oryan/laura/inc/LauParameter.hh",
"/home/oryan/laura/inc/LauParametricStepFuncPdf.hh",
"/home/oryan/laura/inc/LauParticlePDG.hh",
"/home/oryan/laura/inc/LauPolNR.hh",
"/home/oryan/laura/inc/LauPolarFormFactorNR.hh",
"/home/oryan/laura/inc/LauPolarFormFactorSymNR.hh",
"/home/oryan/laura/inc/LauPolarGammaCPCoeffSet.hh",
"/home/oryan/laura/inc/LauPoleRes.hh",
"/home/oryan/laura/inc/LauPrint.hh",
"/home/oryan/laura/inc/LauRandom.hh",
"/home/oryan/laura/inc/LauRealImagCPCoeffSet.hh",
"/home/oryan/laura/inc/LauRealImagCoeffSet.hh",
"/home/oryan/laura/inc/LauRealImagGammaCPCoeffSet.hh",
"/home/oryan/laura/inc/LauRelBreitWignerRes.hh",
"/home/oryan/laura/inc/LauRescattering2Res.hh",
"/home/oryan/laura/inc/LauRescatteringRes.hh",
"/home/oryan/laura/inc/LauResonanceInfo.hh",
"/home/oryan/laura/inc/LauResonanceMaker.hh",
"/home/oryan/laura/inc/LauResultsExtractor.hh",
"/home/oryan/laura/inc/LauRhoOmegaMix.hh",
"/home/oryan/laura/inc/LauSPlot.hh",
"/home/oryan/laura/inc/LauScfMap.hh",
"/home/oryan/laura/inc/LauSigmaRes.hh",
"/home/oryan/laura/inc/LauSigmoidPdf.hh",
"/home/oryan/laura/inc/LauSimFitCoordinator.hh",
"/home/oryan/laura/inc/LauSimFitTask.hh",
"/home/oryan/laura/inc/LauSimpleFitModel.hh",
"/home/oryan/laura/inc/LauString.hh",
"/home/oryan/laura/inc/LauSumPdf.hh",
"/home/oryan/laura/inc/LauTextFileParser.hh",
"/home/oryan/laura/inc/LauVetoes.hh",
"/home/oryan/laura/inc/LauWeightedSumEffModel.hh",
nullptr
    };
    static const char* includePaths[] = {
"/home/oryan/laura/inc",
"/home/oryan/laura/inc",
"/home/oryan/root-6.30.06-install/include",
"/home/oryan/root-6.30.06-install/include/",
"/home/oryan/laura/build/inc/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libLaurapLpL dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau1DCubicSpline.hh")))  Lau1DCubicSpline;
class __attribute__((annotate("$clingAutoload$LauFitDataTree.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau1DHistPdf.hh")))  LauFitDataTree;
class __attribute__((annotate("$clingAutoload$LauAbsRValue.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau1DHistPdf.hh")))  LauAbsRValue;
class __attribute__((annotate("$clingAutoload$LauBlind.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau1DHistPdf.hh")))  LauBlind;
class __attribute__((annotate("$clingAutoload$LauParameter.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau1DHistPdf.hh")))  LauParameter;
class __attribute__((annotate("$clingAutoload$LauParamFixed.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau1DHistPdf.hh")))  LauParamFixed;
class __attribute__((annotate("$clingAutoload$LauAbsPdf.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau1DHistPdf.hh")))  LauAbsPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau1DHistPdf.hh")))  Lau1DHistPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau2DAbsDP.hh")))  Lau2DAbsDP;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau2DAbsDPPdf.hh")))  Lau2DAbsDPPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau2DAbsHistDP.hh")))  Lau2DAbsHistDP;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau2DAbsHistDPPdf.hh")))  Lau2DAbsHistDPPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau2DCubicSpline.hh")))  Lau2DCubicSpline;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau2DHistDP.hh")))  Lau2DHistDP;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau2DHistDPPdf.hh")))  Lau2DHistDPPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau2DHistPdf.hh")))  Lau2DHistPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau2DSplineDP.hh")))  Lau2DSplineDP;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/Lau2DSplineDPPdf.hh")))  Lau2DSplineDPPdf;
class __attribute__((annotate("$clingAutoload$LauAbsFitter.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauASqMaxFinder.hh")))  LauAbsFitter;
class __attribute__((annotate("$clingAutoload$LauFormulaPar.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauASqMaxFinder.hh")))  LauFormulaPar;
class __attribute__((annotate("$clingAutoload$LauFitObject.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauASqMaxFinder.hh")))  LauFitObject;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauASqMaxFinder.hh")))  LauASqMaxFinder;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAbsBkgndDPModel.hh")))  LauAbsBkgndDPModel;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAbsCoeffSet.hh")))  LauAbsCoeffSet;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAbsEffModel.hh")))  LauAbsEffModel;
class __attribute__((annotate("$clingAutoload$LauComplex.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAbsFitModel.hh")))  LauComplex;
class __attribute__((annotate("$clingAutoload$LauSimFitTask.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAbsFitModel.hh")))  LauSimFitTask;
class __attribute__((annotate("$clingAutoload$LauSPlot.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAbsFitModel.hh")))  LauSPlot;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAbsFitModel.hh")))  LauAbsFitModel;
class __attribute__((annotate("$clingAutoload$LauBlattWeisskopfFactor.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAbsIncohRes.hh")))  LauBlattWeisskopfFactor;
class __attribute__((annotate("$clingAutoload$LauAbsResonance.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAbsIncohRes.hh")))  LauAbsResonance;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAbsIncohRes.hh")))  LauAbsIncohRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAbsModIndPartWave.hh")))  LauAbsModIndPartWave;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauArgusPdf.hh")))  LauArgusPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauAsymmCalc.hh")))  LauAsymmCalc;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauBelleCPCoeffSet.hh")))  LauBelleCPCoeffSet;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauBelleNR.hh")))  LauBelleNR;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauBelleSymNR.hh")))  LauBelleSymNR;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauBifurcatedGaussPdf.hh")))  LauBifurcatedGaussPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauBkgndDPModel.hh")))  LauBkgndDPModel;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauBreitWignerRes.hh")))  LauBreitWignerRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauCPFitModel.hh")))  LauCPFitModel;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauCacheData.hh")))  LauCacheData;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauCalcChiSq.hh")))  LauCalcChiSq;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauCartesianCPCoeffSet.hh")))  LauCartesianCPCoeffSet;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauCartesianGammaCPCoeffSet.hh")))  LauCartesianGammaCPCoeffSet;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauChebychevPdf.hh")))  LauChebychevPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauCleoCPCoeffSet.hh")))  LauCleoCPCoeffSet;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauCruijffPdf.hh")))  LauCruijffPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauCrystalBallPdf.hh")))  LauCrystalBallPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauDPDepBifurGaussPdf.hh")))  LauDPDepBifurGaussPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauDPDepCruijffPdf.hh")))  LauDPDepCruijffPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauDPDepGaussPdf.hh")))  LauDPDepGaussPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauDPDepMapPdf.hh")))  LauDPDepMapPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauDPDepSumPdf.hh")))  LauDPDepSumPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauDPPartialIntegralInfo.hh")))  LauDPPartialIntegralInfo;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauDabbaRes.hh")))  LauDabbaRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauDatabasePDG.hh")))  LauDatabasePDG;
class __attribute__((annotate("$clingAutoload$LauKinematics.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauDaughters.hh")))  LauKinematics;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauDaughters.hh")))  LauDaughters;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauEFKLLMRes.hh")))  LauEFKLLMRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauEffModel.hh")))  LauEffModel;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauEmbeddedData.hh")))  LauEmbeddedData;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauExponentialPdf.hh")))  LauExponentialPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauFitNtuple.hh")))  LauFitNtuple;
class __attribute__((annotate("$clingAutoload$LauPrint.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauFitter.hh")))  LauPrint;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauFitter.hh")))  LauFitter;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauFlatNR.hh")))  LauFlatNR;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauFlatteRes.hh")))  LauFlatteRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauGaussIncohRes.hh")))  LauGaussIncohRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauGaussPdf.hh")))  LauGaussPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauGenNtuple.hh")))  LauGenNtuple;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauGounarisSakuraiRes.hh")))  LauGounarisSakuraiRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauIntegrals.hh")))  LauIntegrals;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauIsobarDynamics.hh")))  LauIsobarDynamics;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauKMatrixProdPole.hh")))  LauKMatrixProdPole;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauKMatrixProdSVP.hh")))  LauKMatrixProdSVP;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauKMatrixPropFactory.hh")))  LauKMatrixPropFactory;
class __attribute__((annotate("$clingAutoload$LauResonanceMaker.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauKMatrixPropagator.hh")))  LauResonanceMaker;
class __attribute__((annotate("$clingAutoload$LauResonanceInfo.hh")))  __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauKMatrixPropagator.hh")))  LauResonanceInfo;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauKMatrixPropagator.hh")))  LauKMatrixPropagator;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauKappaRes.hh")))  LauKappaRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauLASSBWRes.hh")))  LauLASSBWRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauLASSNRRes.hh")))  LauLASSNRRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauLASSRes.hh")))  LauLASSRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauLinearPdf.hh")))  LauLinearPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauMagPhaseCPCoeffSet.hh")))  LauMagPhaseCPCoeffSet;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauMagPhaseCoeffSet.hh")))  LauMagPhaseCoeffSet;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauMergeDataFiles.hh")))  LauMergeDataFiles;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauMinuit.hh")))  LauMinuit;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauModIndPartWaveMagPhase.hh")))  LauModIndPartWaveMagPhase;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauModIndPartWaveRealImag.hh")))  LauModIndPartWaveRealImag;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauNRAmplitude.hh")))  LauNRAmplitude;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauNovosibirskPdf.hh")))  LauNovosibirskPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauParametricStepFuncPdf.hh")))  LauParametricStepFuncPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauParticlePDG.hh")))  LauParticlePDG;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauPolNR.hh")))  LauPolNR;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauPolarFormFactorNR.hh")))  LauPolarFormFactorNR;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauPolarFormFactorSymNR.hh")))  LauPolarFormFactorSymNR;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauPolarGammaCPCoeffSet.hh")))  LauPolarGammaCPCoeffSet;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauPoleRes.hh")))  LauPoleRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauRealImagCPCoeffSet.hh")))  LauRealImagCPCoeffSet;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauRealImagCoeffSet.hh")))  LauRealImagCoeffSet;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauRealImagGammaCPCoeffSet.hh")))  LauRealImagGammaCPCoeffSet;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauRelBreitWignerRes.hh")))  LauRelBreitWignerRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauRescattering2Res.hh")))  LauRescattering2Res;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauRescatteringRes.hh")))  LauRescatteringRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauResultsExtractor.hh")))  LauResultsExtractor;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauRhoOmegaMix.hh")))  LauRhoOmegaMix;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauScfMap.hh")))  LauScfMap;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauSigmaRes.hh")))  LauSigmaRes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauSigmoidPdf.hh")))  LauSigmoidPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauSimFitCoordinator.hh")))  LauSimFitCoordinator;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauSimpleFitModel.hh")))  LauSimpleFitModel;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauString.hh")))  LauString;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauSumPdf.hh")))  LauSumPdf;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauTextFileParser.hh")))  LauTextFileParser;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauVetoes.hh")))  LauVetoes;
class __attribute__((annotate("$clingAutoload$/home/oryan/laura/inc/LauWeightedSumEffModel.hh")))  LauWeightedSumEffModel;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libLaurapLpL dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "/home/oryan/laura/inc/Lau1DCubicSpline.hh"
#include "/home/oryan/laura/inc/Lau1DHistPdf.hh"
#include "/home/oryan/laura/inc/Lau2DAbsDP.hh"
#include "/home/oryan/laura/inc/Lau2DAbsDPPdf.hh"
#include "/home/oryan/laura/inc/Lau2DAbsHistDP.hh"
#include "/home/oryan/laura/inc/Lau2DAbsHistDPPdf.hh"
#include "/home/oryan/laura/inc/Lau2DCubicSpline.hh"
#include "/home/oryan/laura/inc/Lau2DHistDP.hh"
#include "/home/oryan/laura/inc/Lau2DHistDPPdf.hh"
#include "/home/oryan/laura/inc/Lau2DHistPdf.hh"
#include "/home/oryan/laura/inc/Lau2DSplineDP.hh"
#include "/home/oryan/laura/inc/Lau2DSplineDPPdf.hh"
#include "/home/oryan/laura/inc/LauASqMaxFinder.hh"
#include "/home/oryan/laura/inc/LauAbsBkgndDPModel.hh"
#include "/home/oryan/laura/inc/LauAbsCoeffSet.hh"
#include "/home/oryan/laura/inc/LauAbsEffModel.hh"
#include "/home/oryan/laura/inc/LauAbsFitModel.hh"
#include "/home/oryan/laura/inc/LauAbsFitter.hh"
#include "/home/oryan/laura/inc/LauAbsIncohRes.hh"
#include "/home/oryan/laura/inc/LauAbsModIndPartWave.hh"
#include "/home/oryan/laura/inc/LauAbsPdf.hh"
#include "/home/oryan/laura/inc/LauAbsRValue.hh"
#include "/home/oryan/laura/inc/LauAbsResonance.hh"
#include "/home/oryan/laura/inc/LauArgusPdf.hh"
#include "/home/oryan/laura/inc/LauAsymmCalc.hh"
#include "/home/oryan/laura/inc/LauBelleCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauBelleNR.hh"
#include "/home/oryan/laura/inc/LauBelleSymNR.hh"
#include "/home/oryan/laura/inc/LauBifurcatedGaussPdf.hh"
#include "/home/oryan/laura/inc/LauBkgndDPModel.hh"
#include "/home/oryan/laura/inc/LauBlattWeisskopfFactor.hh"
#include "/home/oryan/laura/inc/LauBlind.hh"
#include "/home/oryan/laura/inc/LauBreitWignerRes.hh"
#include "/home/oryan/laura/inc/LauCPFitModel.hh"
#include "/home/oryan/laura/inc/LauCacheData.hh"
#include "/home/oryan/laura/inc/LauCalcChiSq.hh"
#include "/home/oryan/laura/inc/LauCartesianCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauCartesianGammaCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauChebychevPdf.hh"
#include "/home/oryan/laura/inc/LauCleoCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauComplex.hh"
#include "/home/oryan/laura/inc/LauConstants.hh"
#include "/home/oryan/laura/inc/LauCruijffPdf.hh"
#include "/home/oryan/laura/inc/LauCrystalBallPdf.hh"
#include "/home/oryan/laura/inc/LauDPDepBifurGaussPdf.hh"
#include "/home/oryan/laura/inc/LauDPDepCruijffPdf.hh"
#include "/home/oryan/laura/inc/LauDPDepGaussPdf.hh"
#include "/home/oryan/laura/inc/LauDPDepMapPdf.hh"
#include "/home/oryan/laura/inc/LauDPDepSumPdf.hh"
#include "/home/oryan/laura/inc/LauDPPartialIntegralInfo.hh"
#include "/home/oryan/laura/inc/LauDabbaRes.hh"
#include "/home/oryan/laura/inc/LauDatabasePDG.hh"
#include "/home/oryan/laura/inc/LauDaughters.hh"
#include "/home/oryan/laura/inc/LauEFKLLMRes.hh"
#include "/home/oryan/laura/inc/LauEffModel.hh"
#include "/home/oryan/laura/inc/LauEmbeddedData.hh"
#include "/home/oryan/laura/inc/LauExponentialPdf.hh"
#include "/home/oryan/laura/inc/LauFitDataTree.hh"
#include "/home/oryan/laura/inc/LauFitNtuple.hh"
#include "/home/oryan/laura/inc/LauFitObject.hh"
#include "/home/oryan/laura/inc/LauFitter.hh"
#include "/home/oryan/laura/inc/LauFlatNR.hh"
#include "/home/oryan/laura/inc/LauFlatteRes.hh"
#include "/home/oryan/laura/inc/LauFormulaPar.hh"
#include "/home/oryan/laura/inc/LauGaussIncohRes.hh"
#include "/home/oryan/laura/inc/LauGaussPdf.hh"
#include "/home/oryan/laura/inc/LauGenNtuple.hh"
#include "/home/oryan/laura/inc/LauGounarisSakuraiRes.hh"
#include "/home/oryan/laura/inc/LauIntegrals.hh"
#include "/home/oryan/laura/inc/LauIsobarDynamics.hh"
#include "/home/oryan/laura/inc/LauKMatrixProdPole.hh"
#include "/home/oryan/laura/inc/LauKMatrixProdSVP.hh"
#include "/home/oryan/laura/inc/LauKMatrixPropFactory.hh"
#include "/home/oryan/laura/inc/LauKMatrixPropagator.hh"
#include "/home/oryan/laura/inc/LauKappaRes.hh"
#include "/home/oryan/laura/inc/LauKinematics.hh"
#include "/home/oryan/laura/inc/LauLASSBWRes.hh"
#include "/home/oryan/laura/inc/LauLASSNRRes.hh"
#include "/home/oryan/laura/inc/LauLASSRes.hh"
#include "/home/oryan/laura/inc/LauLinearPdf.hh"
#include "/home/oryan/laura/inc/LauMagPhaseCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauMagPhaseCoeffSet.hh"
#include "/home/oryan/laura/inc/LauMergeDataFiles.hh"
#include "/home/oryan/laura/inc/LauMinuit.hh"
#include "/home/oryan/laura/inc/LauModIndPartWaveMagPhase.hh"
#include "/home/oryan/laura/inc/LauModIndPartWaveRealImag.hh"
#include "/home/oryan/laura/inc/LauNRAmplitude.hh"
#include "/home/oryan/laura/inc/LauNovosibirskPdf.hh"
#include "/home/oryan/laura/inc/LauParamFixed.hh"
#include "/home/oryan/laura/inc/LauParameter.hh"
#include "/home/oryan/laura/inc/LauParametricStepFuncPdf.hh"
#include "/home/oryan/laura/inc/LauParticlePDG.hh"
#include "/home/oryan/laura/inc/LauPolNR.hh"
#include "/home/oryan/laura/inc/LauPolarFormFactorNR.hh"
#include "/home/oryan/laura/inc/LauPolarFormFactorSymNR.hh"
#include "/home/oryan/laura/inc/LauPolarGammaCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauPoleRes.hh"
#include "/home/oryan/laura/inc/LauPrint.hh"
#include "/home/oryan/laura/inc/LauRandom.hh"
#include "/home/oryan/laura/inc/LauRealImagCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauRealImagCoeffSet.hh"
#include "/home/oryan/laura/inc/LauRealImagGammaCPCoeffSet.hh"
#include "/home/oryan/laura/inc/LauRelBreitWignerRes.hh"
#include "/home/oryan/laura/inc/LauRescattering2Res.hh"
#include "/home/oryan/laura/inc/LauRescatteringRes.hh"
#include "/home/oryan/laura/inc/LauResonanceInfo.hh"
#include "/home/oryan/laura/inc/LauResonanceMaker.hh"
#include "/home/oryan/laura/inc/LauResultsExtractor.hh"
#include "/home/oryan/laura/inc/LauRhoOmegaMix.hh"
#include "/home/oryan/laura/inc/LauSPlot.hh"
#include "/home/oryan/laura/inc/LauScfMap.hh"
#include "/home/oryan/laura/inc/LauSigmaRes.hh"
#include "/home/oryan/laura/inc/LauSigmoidPdf.hh"
#include "/home/oryan/laura/inc/LauSimFitCoordinator.hh"
#include "/home/oryan/laura/inc/LauSimFitTask.hh"
#include "/home/oryan/laura/inc/LauSimpleFitModel.hh"
#include "/home/oryan/laura/inc/LauString.hh"
#include "/home/oryan/laura/inc/LauSumPdf.hh"
#include "/home/oryan/laura/inc/LauTextFileParser.hh"
#include "/home/oryan/laura/inc/LauVetoes.hh"
#include "/home/oryan/laura/inc/LauWeightedSumEffModel.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"Lau1DCubicSpline", payloadCode, "@",
"Lau1DHistPdf", payloadCode, "@",
"Lau2DAbsDP", payloadCode, "@",
"Lau2DAbsDPPdf", payloadCode, "@",
"Lau2DAbsHistDP", payloadCode, "@",
"Lau2DAbsHistDPPdf", payloadCode, "@",
"Lau2DCubicSpline", payloadCode, "@",
"Lau2DHistDP", payloadCode, "@",
"Lau2DHistDPPdf", payloadCode, "@",
"Lau2DHistPdf", payloadCode, "@",
"Lau2DSplineDP", payloadCode, "@",
"Lau2DSplineDPPdf", payloadCode, "@",
"LauASqMaxFinder", payloadCode, "@",
"LauAbsBkgndDPModel", payloadCode, "@",
"LauAbsCoeffSet", payloadCode, "@",
"LauAbsEffModel", payloadCode, "@",
"LauAbsFitModel", payloadCode, "@",
"LauAbsFitter", payloadCode, "@",
"LauAbsIncohRes", payloadCode, "@",
"LauAbsModIndPartWave", payloadCode, "@",
"LauAbsPdf", payloadCode, "@",
"LauAbsRValue", payloadCode, "@",
"LauAbsResonance", payloadCode, "@",
"LauArgusPdf", payloadCode, "@",
"LauAsymmCalc", payloadCode, "@",
"LauBelleCPCoeffSet", payloadCode, "@",
"LauBelleNR", payloadCode, "@",
"LauBelleSymNR", payloadCode, "@",
"LauBifurcatedGaussPdf", payloadCode, "@",
"LauBkgndDPModel", payloadCode, "@",
"LauBlattWeisskopfFactor", payloadCode, "@",
"LauBlind", payloadCode, "@",
"LauBreitWignerRes", payloadCode, "@",
"LauCPFitModel", payloadCode, "@",
"LauCacheData", payloadCode, "@",
"LauCalcChiSq", payloadCode, "@",
"LauCartesianCPCoeffSet", payloadCode, "@",
"LauCartesianGammaCPCoeffSet", payloadCode, "@",
"LauChebychevPdf", payloadCode, "@",
"LauCleoCPCoeffSet", payloadCode, "@",
"LauComplex", payloadCode, "@",
"LauCruijffPdf", payloadCode, "@",
"LauCrystalBallPdf", payloadCode, "@",
"LauDPDepBifurGaussPdf", payloadCode, "@",
"LauDPDepCruijffPdf", payloadCode, "@",
"LauDPDepGaussPdf", payloadCode, "@",
"LauDPDepMapPdf", payloadCode, "@",
"LauDPDepSumPdf", payloadCode, "@",
"LauDPPartialIntegralInfo", payloadCode, "@",
"LauDabbaRes", payloadCode, "@",
"LauDatabasePDG", payloadCode, "@",
"LauDaughters", payloadCode, "@",
"LauEFKLLMRes", payloadCode, "@",
"LauEffModel", payloadCode, "@",
"LauEmbeddedData", payloadCode, "@",
"LauExponentialPdf", payloadCode, "@",
"LauFitDataTree", payloadCode, "@",
"LauFitNtuple", payloadCode, "@",
"LauFitObject", payloadCode, "@",
"LauFitter", payloadCode, "@",
"LauFlatNR", payloadCode, "@",
"LauFlatteRes", payloadCode, "@",
"LauFormulaPar", payloadCode, "@",
"LauGaussIncohRes", payloadCode, "@",
"LauGaussPdf", payloadCode, "@",
"LauGenNtuple", payloadCode, "@",
"LauGounarisSakuraiRes", payloadCode, "@",
"LauIntegrals", payloadCode, "@",
"LauIsobarDynamics", payloadCode, "@",
"LauKMatrixProdPole", payloadCode, "@",
"LauKMatrixProdSVP", payloadCode, "@",
"LauKMatrixPropFactory", payloadCode, "@",
"LauKMatrixPropagator", payloadCode, "@",
"LauKappaRes", payloadCode, "@",
"LauKinematics", payloadCode, "@",
"LauLASSBWRes", payloadCode, "@",
"LauLASSNRRes", payloadCode, "@",
"LauLASSRes", payloadCode, "@",
"LauLinearPdf", payloadCode, "@",
"LauMagPhaseCPCoeffSet", payloadCode, "@",
"LauMagPhaseCoeffSet", payloadCode, "@",
"LauMergeDataFiles", payloadCode, "@",
"LauMinuit", payloadCode, "@",
"LauModIndPartWaveMagPhase", payloadCode, "@",
"LauModIndPartWaveRealImag", payloadCode, "@",
"LauNRAmplitude", payloadCode, "@",
"LauNovosibirskPdf", payloadCode, "@",
"LauParamFixed", payloadCode, "@",
"LauParameter", payloadCode, "@",
"LauParametricStepFuncPdf", payloadCode, "@",
"LauParticlePDG", payloadCode, "@",
"LauPolNR", payloadCode, "@",
"LauPolarFormFactorNR", payloadCode, "@",
"LauPolarFormFactorSymNR", payloadCode, "@",
"LauPolarGammaCPCoeffSet", payloadCode, "@",
"LauPoleRes", payloadCode, "@",
"LauPrint", payloadCode, "@",
"LauRealImagCPCoeffSet", payloadCode, "@",
"LauRealImagCoeffSet", payloadCode, "@",
"LauRealImagGammaCPCoeffSet", payloadCode, "@",
"LauRelBreitWignerRes", payloadCode, "@",
"LauRescattering2Res", payloadCode, "@",
"LauRescatteringRes", payloadCode, "@",
"LauResonanceInfo", payloadCode, "@",
"LauResonanceMaker", payloadCode, "@",
"LauResultsExtractor", payloadCode, "@",
"LauRhoOmegaMix", payloadCode, "@",
"LauSPlot", payloadCode, "@",
"LauScfMap", payloadCode, "@",
"LauSigmaRes", payloadCode, "@",
"LauSigmoidPdf", payloadCode, "@",
"LauSimFitCoordinator", payloadCode, "@",
"LauSimFitTask", payloadCode, "@",
"LauSimpleFitModel", payloadCode, "@",
"LauString", payloadCode, "@",
"LauSumPdf", payloadCode, "@",
"LauTextFileParser", payloadCode, "@",
"LauVetoes", payloadCode, "@",
"LauWeightedSumEffModel", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libLaura++",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libLaurapLpL_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libLaurapLpL_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libLaurapLpL() {
  TriggerDictionaryInitialization_libLaurapLpL_Impl();
}
