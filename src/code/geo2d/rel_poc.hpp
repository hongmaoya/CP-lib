#ifndef TIFA_LIBS_GEO2D_REL_POC
#define TIFA_LIBS_GEO2D_REL_POC

#include "circle.hpp"
#include "polygon.hpp"
#include "rel_cs.hpp"
#include "rel_pop.hpp"

namespace tifa_libs::geo {

// relation between polygon/convex hull and circle
enum RELPoC {
  otherwise_poc,
  touchin_poc,
  covered_poc
};

template <class FP>
RELPoC relation_PoC(polygon<FP> const &po, circle<FP> const &c) {
  auto x = covered_poc;
  if (relation_PoP(po, c.o) != RELPoP::inside_pop) return otherwise_poc;
  for (usz i = 0; i < po.vs.size(); ++i) {
    usz state = relation_CS(c, {po.vs[i], po.vs[po.next(i)]});
    if (state == RELCS::intersect_cs) return otherwise_poc;
    if (state == RELCS::tagante_cs) x = touchin_poc;
  }
  return x;
}

}  // namespace tifa_libs::geo

#endif