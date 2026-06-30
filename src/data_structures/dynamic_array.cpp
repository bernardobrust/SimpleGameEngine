// Dynamic Array Data Structure
export module dyn_arr;

import <iostream>;
import <cstdlib>;
import <cassert>;
import <type_traits>;

export namespace engine::ds::dyn_arr
{
template <typename T> struct DynArr
{
  size_t sza;
  size_t used;
  T *data;
};

// Info
template <typename T>
inline size_t
length (DynArr<T> *dyn_arr)
{
  return dyn_arr->used;
}

template <typename T>
inline size_t
size (DynArr<T> *dyn_arr, bool header = false)
{
  return header ? (dyn_arr->sza * sizeof (T)) + (sizeof (size_t) * 2)
                : dyn_arr->sza * sizeof (T);
}

template <typename T>
T
get (DynArr<T> *dyn_arr, size_t i)
{
  // For debug builds, this is *really* slow, but for non-debug builds it gets
  // removed so it's great
  assert (i < dyn_arr->used);

  return dyn_arr->data[i];
}

// Debug
template <typename T>
void
print_data (DynArr<T> *dyn_arr)
{
  for (size_t i{ 0 }; i < length (dyn_arr); ++i)
    {
      std::cout << "Element " << i << " = " << dyn_arr->data[i] << "\n";
    }
}

template <typename T>
inline void
print_metadata (DynArr<T> *dyn_arr)
{
  std::cout << "Length = " << dyn_arr->used << ", Avaliable = " << dyn_arr->sza
            << ", Size = " << dyn_arr::size (dyn_arr)
            << ", Size (total) = " << dyn_arr::size (dyn_arr, true) << "\n";
}

// Actions
template <typename T>
DynArr<T> *
init (size_t sza = 1)
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

template <typename T>
void
push (DynArr<T> *dyn_arr, T new_elem, float scale = 2.0f)
{
  assert (dyn_arr != NULL);
  assert (dyn_arr->sza != 0);
  assert (scale >= 1.0f);

  // Realocate
  if (dyn_arr->used == dyn_arr->sza)
    {
      dyn_arr->sza = (size_t)(dyn_arr->sza * scale);
      dyn_arr->data = (T *)realloc (dyn_arr->data, sizeof (T) * dyn_arr->sza);
      dyn_arr->data[dyn_arr->used] = new_elem;
      ++dyn_arr->used;
    }
  else
    {
      dyn_arr->data[dyn_arr->used] = new_elem;
      ++dyn_arr->used;
    }
}

template <typename T>
void
// I think it's a good design decision to not descaalate by default
pop (DynArr<T> *dyn_arr, bool descale = false, float scale = 2.0f)
{
  assert (dyn_arr != NULL);
  assert (dyn_arr->sza > 0);
  // We obviously can't pop nothing
  // We could ignore, but if this happes it's likely a bug
  assert (dyn_arr->used > 0);
  assert (scale >= 1.0f);

  // Release
  if (descale and dyn_arr->sza / dyn_arr->used >= scale)
    {
      dyn_arr->sza = (size_t)(dyn_arr->sza / scale);

      // Just in case
      assert (dyn_arr->sza >= dyn_arr->used);

      dyn_arr->data = (T *)realloc (dyn_arr->data, sizeof (T) * dyn_arr->sza);
      --dyn_arr->used;
    }
  else
    {
      --dyn_arr->used;
    }
}

}