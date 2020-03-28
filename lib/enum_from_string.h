
#include <string>
template <class T, T minimum = static_cast<T>(0), T maximum = T::MAX>
inline T
from_string(const std::string& str) {
  T result{T::MAX};
  for (T value = static_cast<T>(0);
         value < T::MAX;
         value = static_cast<T>(static_cast<int>(value)+1))
  {
    if (str == std::to_string(value)) {
      result = value;
      break;
    }
  }
  return result;
}