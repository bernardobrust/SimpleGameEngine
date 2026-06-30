// Dynamic Array Data Structure
export module dyn_arr;

import <type_traits>;
import <cstdlib>;
import <cassert>;

export namespace engine::ds::dyn_arr
{
/*
    Templated dynamic array data structure:
    - Supports trivial data types
    - Max elements: 2^{64-1} (18,446,744,073,709,551,615)
    - 8 bytes of overhead (2 unsigneds of metadata)
*/
template <typename T> struct DynArr
{
  unsigned sza;
  unsigned used;
  T *data;
};

template <typename T>
DynArr<T> *
init (unsigned sza = 1)
{
  // We need this to avoid a bunch of weird C++ stuff
  // Still, it's better than creating a bunch of copies of this function and
  // struct or using void*
  static_assert (std::is_trivially_copyable_v<T>,
                 "T must be trivially copyable");

  // The lion checks for failed allocations only on debug
  T *data = (T *)malloc (sizeof (T) * sza);
  assert (data != NULL);
  DynArr<T> *dyn_arr = (DynArr<T> *)malloc (sizeof (DynArr<T>));
  assert (dyn_arr != NULL);
  dyn_arr->sza = sza;
  dyn_arr->used = 0;
  dyn_arr->data = data;

  return dyn_arr;
}
}