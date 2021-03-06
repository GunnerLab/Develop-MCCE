#ifndef DDM__ALGORITHM__FILL_H__
#define DDM__ALGORITHM__FILL_H__

#include "../../ddm/internal/Config.h"

#include "../../ddm/iterator/GlobIter.h"

#include "../../ddm/algorithm/LocalRange.h"
#include "../../ddm/algorithm/Operation.h"

#include "../../ddm/util/UnitLocality.h"

#include "../dart-impl/dart_communication.h"

#ifdef DDM_ENABLE_OPENMP
#include <omp.h>
#endif


namespace ddm {

/**
 * Assigns the given value to the elements in the range [first, last)
 *
 * Being a collaborative operation, each unit will assign the value to
 * its local elements only.
 *
 * \tparam      ElementType  Type of the elements in the sequence
 * \complexity  O(d) + O(nl), with \c d dimensions in the global iterators'
 *              pattern and \c nl local elements within the global range
 *
 * \ingroup     DDMAlgorithms
 */
template <typename GlobIterType>
void fill(
  /// Iterator to the initial position in the sequence
  GlobIterType        first,
  /// Iterator to the final position in the sequence
  GlobIterType        last,
  /// Value which will be assigned to the elements in range [first, last)
  const typename GlobIterType::value_type & value)
{
  typedef typename GlobIterType::index_type index_t;
  typedef typename GlobIterType::value_type value_t;

  // Global iterators to local range:
  auto      index_range = ddm::local_range(first, last);
  value_t * lfirst      = index_range.begin;
  value_t * llast       = index_range.end;
  auto      nlocal      = llast - lfirst;

#if 0
  for (index_t lt = 0; lt < nlocal; lt++) {
    lfirst[lt] = value;
  }
#else
#ifdef DDM_ENABLE_OPENMP
  ddm::util::UnitLocality uloc;
  auto n_threads = uloc.num_domain_threads();
  DDM_LOG_DEBUG("ddm::fill", "thread capacity:",  n_threads);
  #pragma omp parallel num_threads(n_threads)
  for (index_t lt = 0; lt < nlocal; lt += 2) {
    lfirst[lt] = value;
  }

  #pragma omp parallel num_threads(n_threads)
  for (index_t lt = 1; lt < nlocal; lt += 2) {
    lfirst[lt] = value;
  }
#else
  for (index_t lt = 0; lt < nlocal; lt += 2) {
    lfirst[lt] = value;
  }
  for (index_t lt = 1; lt < nlocal; lt += 2) {
    lfirst[lt] = value;
  }
#endif
#endif
}

} // namespace ddm

#endif // DDM__ALGORITHM__FILL_H__
