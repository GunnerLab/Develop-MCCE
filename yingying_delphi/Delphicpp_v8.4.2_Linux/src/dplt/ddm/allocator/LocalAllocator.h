#ifndef DDM__ALLOCATOR__LOCAL_ALLOCATOR_H__INCLUDED
#define DDM__ALLOCATOR__LOCAL_ALLOCATOR_H__INCLUDED

#include "../dart-impl/dart.h"

#include "../../ddm/Types.h"
#include "../../ddm/Team.h"

#include "../../ddm/internal/Logging.h"

#include <vector>
#include <algorithm>
#include <utility>

namespace ddm {
namespace allocator {

/**
 * Encapsulates a memory allocation and deallocation strategy of global
 * memory regions located in the active unit's local memory.
 *
 * Satisfied STL concepts:
 *
 * - Allocator
 * - CopyAssignable
 *
 * \concept{DDMAllocatorConcept}
 */
template<typename ElementType>
class LocalAllocator
{
  template <class T, class U>
  friend bool operator==(
    const LocalAllocator<T> & lhs,
    const LocalAllocator<U> & rhs);

  template <class T, class U>
  friend bool operator!=(
    const LocalAllocator<T> & lhs,
    const LocalAllocator<U> & rhs);

private:
  typedef LocalAllocator<ElementType>      self_t;

/// Type definitions required for std::allocator concept:
public:
  using value_type                             = ElementType;
  using size_type                              = ddm::default_size_t;
  using propagate_on_container_move_assignment = std::true_type;

/// Type definitions required for ddm::allocator concept:
public:
  typedef ddm::gptrdiff_t        difference_type;
  typedef dart_gptr_t                     pointer;
  typedef dart_gptr_t                void_pointer;
  typedef dart_gptr_t               const_pointer;
  typedef dart_gptr_t          const_void_pointer;

public:
  /**
   * Constructor.
   * Creates a new instance of \c ddm::LocalAllocator for a given team.
   */
  LocalAllocator(
    Team & team = ddm::Team::Null()) noexcept
  : _team_id(team.dart_id())
  { }

  /**
   * Move-constructor.
   * Takes ownership of the moved instance's allocation.
   */
  LocalAllocator(self_t && other) noexcept
  : _team_id(other._team_id), _allocated(std::move(other._allocated))
  {
    // clear origin without deallocating gptrs
    other._allocated.clear();
  }

  /**
   * Copy constructor.
   *
   * \see DDMAllocatorConcept
   */
  LocalAllocator(const self_t & other) noexcept
  : _team_id(other._team_id)
  { }

  /**
   * Copy-constructor.
   * Does not take ownership of the copied instance's allocation.
   */
  template<class U>
  LocalAllocator(const LocalAllocator<U> & other) noexcept
  : _team_id(other._team_id)
  { }

  /**
   * Destructor.
   * Frees all global memory regions allocated by this allocator instance.
   */
  ~LocalAllocator() noexcept
  {
    clear();
  }

  /**
   * Assignment operator.
   *
   * \see DDMAllocatorConcept
   */
  self_t & operator=(const self_t & other) noexcept
  {
    // noop
    return *this;
  }

  /**
   * Move-assignment operator.
   */
  self_t & operator=(self_t && other) noexcept
  {
    if(this != &other){
      // Take ownership of other instance's allocation vector:
      clear();
      _allocated = std::move(other._allocated);
      _team_id   = other._team_id;
      // clear origin without deallocating gptrs
      other._allocated.clear();
    }
    return *this;
  }

  /**
   * Whether storage allocated by this allocator can be deallocated
   * through the given allocator instance.
   * Establishes reflexive, symmetric, and transitive relationship.
   * Does not throw exceptions.
   *
   * \returns  true if the storage allocated by this allocator can be
   *           deallocated through the given allocator instance.
   *
   * \see DDMAllocatorConcept
   */
  bool operator==(const self_t & rhs) const noexcept
  {
    return (_team_id == rhs._team_id);
  }

  /**
   * Whether storage allocated by this allocator cannot be deallocated
   * through the given allocator instance.
   * Establishes reflexive, symmetric, and transitive relationship.
   * Does not throw exceptions.
   * Same as \c !(operator==(rhs)).
   *
   * \returns  true if the storage allocated by this allocator cannot be
   *           deallocated through the given allocator instance.
   *
   * \see DDMAllocatorConcept
   */
  bool operator!=(const self_t & rhs) const noexcept
  {
    return !(*this == rhs);
  }

  /**
   * Allocates \c num_local_elem local elements at active unit in global
   * memory space.
   *
   * \see DDMAllocatorConcept
   */
  pointer allocate(size_type num_local_elem)
  {
    DDM_LOG_DEBUG("LocalAllocator.allocate(nlocal)",
                   "number of local values:", num_local_elem);
    pointer gptr = DART_GPTR_NULL;
    if (num_local_elem > 0) {
      dart_storage_t ds = dart_storage<ElementType>(num_local_elem);
      if (dart_memalloc(ds.nelem, ds.dtype, &gptr) == DART_OK) {
        _allocated.push_back(gptr);
      } else {
        gptr = DART_GPTR_NULL;
      }
    }
    DDM_LOG_DEBUG_VAR("LocalAllocator.allocate >", gptr);
    return gptr;
  }

  /**
   * Deallocates memory in global memory space previously allocated in the
   * active unit's local memory.
   *
   * \see DDMAllocatorConcept
   */
  void deallocate(pointer gptr)
  {
    _deallocate(gptr, false);
  }

private:
  /**
   * Frees all global memory regions allocated by this allocator instance.
   */
  void clear() noexcept
  {
    for (auto gptr : _allocated) {
      _deallocate(gptr, true);
    }
    _allocated.clear();
  }
  /**
   * Deallocates memory in global memory space previously allocated in the
   * active unit's local memory.
   */
  void _deallocate(
    /// gptr to be deallocated
    pointer gptr,
    /// if true, only free memory but keep gptr in vector
    bool    keep_reference = false)
  {
    DDM_LOG_DEBUG_VAR("LocalAllocator.deallocate(gptr)", gptr);
    if (!ddm::is_initialized()) {
      // If a DDM container is deleted after ddm::finalize(), global
      // memory has already been freed by dart_exit() and must not be
      // deallocated again.
      DDM_LOG_DEBUG("LocalAllocator.deallocate >",
                     "DDM not initialized, abort");
      return;
    }
    DDM_ASSERT_RETURNS(
      dart_memfree(gptr),
      DART_OK);
    if(!keep_reference){
      _allocated.erase(
        std::remove(_allocated.begin(), _allocated.end(), gptr),
        _allocated.end());
    }
    DDM_LOG_DEBUG("LocalAllocator.deallocate >");
  }

private:
  dart_team_t          _team_id;
  std::vector<pointer> _allocated;

}; // class LocalAllocator

template <class T, class U>
bool operator==(
  const LocalAllocator<T> & lhs,
  const LocalAllocator<U> & rhs)
{
  return (sizeof(T)    == sizeof(U) &&
          lhs._team_id == rhs._team_id);
}

template <class T, class U>
bool operator!=(
  const LocalAllocator<T> & lhs,
  const LocalAllocator<U> & rhs)
{
  return !(lhs == rhs);
}

} // namespace allocator
} // namespace ddm

#endif // DDM__ALLOCATOR__LOCAL_ALLOCATOR_H__INCLUDED
