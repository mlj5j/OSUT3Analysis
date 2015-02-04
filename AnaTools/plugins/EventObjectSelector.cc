#include "OSUT3Analysis/AnaTools/interface/ObjectSelector.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#if IS_VALID(events)
  typedef ObjectSelector<TYPE(events)> EventObjectSelector;
  DEFINE_FWK_MODULE(EventObjectSelector);
#endif
