#include "OSUT3Analysis/Collections/plugins/OSUBjetProducer.h"

#if IS_VALID(bjets)

#include "OSUT3Analysis/AnaTools/interface/CommonUtils.h"

OSUBjetProducer::OSUBjetProducer (const edm::ParameterSet &cfg) :
  collections_ (cfg.getParameter<edm::ParameterSet> ("collections")),
  cfg_ (cfg)
{
  collection_ = collections_.getParameter<edm::InputTag> ("bjets");

  produces<vector<osu::Bjet> > (collection_.instance ());

  token_ = consumes<vector<TYPE(bjets)> > (collection_);
  mcparticleToken_ = consumes<vector<osu::Mcparticle> > (collections_.getParameter<edm::InputTag> ("mcparticles"));
}

OSUBjetProducer::~OSUBjetProducer ()
{
}

void
OSUBjetProducer::produce (edm::Event &event, const edm::EventSetup &setup)
{
  edm::Handle<vector<TYPE(bjets)> > collection;
  if (!event.getByToken (token_, collection))
    return;
  edm::Handle<vector<osu::Mcparticle> > particles;
  event.getByToken (mcparticleToken_, particles);

  pl_ = auto_ptr<vector<osu::Bjet> > (new vector<osu::Bjet> ());
  for (const auto &object : *collection)
    {
      osu::Bjet bjet (object, particles, cfg_);
#if DATA_FORMAT == MINI_AOD || DATA_FORMAT == MINI_AOD_CUSTOM
      bjet.set_pfCombinedInclusiveSecondaryVertexV2BJetTags(bjet.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
      bjet.set_pfCombinedSecondaryVertexV2BJetTags(bjet.bDiscriminator("pfCombinedSecondaryVertexV2BJetTags"));
#endif
      pl_->push_back (bjet);
    }

  event.put (pl_, collection_.instance ());
  pl_.reset ();
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(OSUBjetProducer);

#endif
