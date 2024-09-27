/*
 * (C) Copyright 2017-2018 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef UFO_OPERATORS_GNSSRO_REFNCEP_OBSGNSSROREFNCEPTLAD_H_
#define UFO_OPERATORS_GNSSRO_REFNCEP_OBSGNSSROREFNCEPTLAD_H_

#include <memory>
#include <ostream>
#include <string>

#include "ioda/ObsDataVector.h"
#include "oops/base/Variables.h"
#include "oops/util/ObjectCounter.h"
#include "ufo/LinearObsOperatorBase.h"
#include "ufo/operators/gnssro/RefNCEP/ObsGnssroRefNCEP.h"
#include "ufo/operators/gnssro/RefNCEP/ObsGnssroRefNCEPTLAD.interface.h"

// Forward declarations
namespace eckit {
  class Configuration;
}

namespace ioda {
  class ObsSpace;
  class ObsVector;
}

namespace ufo {
  class GeoVaLs;
  class ObsDiagnostics;

// -------------------------------------------------------------------------
/// GnssroRefNCEP observation operator
class ObsGnssroRefNCEPTLAD : public LinearObsOperatorBase,
                          private util::ObjectCounter<ObsGnssroRefNCEPTLAD> {
 public:
  typedef GnssroRefNCEPParameters Parameters_;
  typedef ioda::ObsDataVector<int> QCFlags_t;

  static const std::string classname() {return "ufo::ObsGnssroRefNCEPTLAD";}

  ObsGnssroRefNCEPTLAD(const ioda::ObsSpace &, const Parameters_ &);
  virtual ~ObsGnssroRefNCEPTLAD();

  // Obs Operators
  void setTrajectory(const GeoVaLs &, ObsDiagnostics &, const QCFlags_t &) override;
  void simulateObsTL(const GeoVaLs &, ioda::ObsVector &, const QCFlags_t &) const override;
  void simulateObsAD(GeoVaLs &, const ioda::ObsVector &, const QCFlags_t &) const override;

  // Other
  const oops::Variables & requiredVars() const override {return *varin_;}

  int & toFortran() {return keyOperGnssroRefNCEP_;}
  const int & toFortran() const {return keyOperGnssroRefNCEP_;}

 private:
  void print(std::ostream &) const override;
  F90hop keyOperGnssroRefNCEP_;
  std::unique_ptr<const oops::Variables> varin_;
};

// -----------------------------------------------------------------------------

}  // namespace ufo
#endif  // UFO_OPERATORS_GNSSRO_REFNCEP_OBSGNSSROREFNCEPTLAD_H_
