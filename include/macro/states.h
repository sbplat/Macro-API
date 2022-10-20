#ifndef _states_h_
#define _states_h_

#include <cstring>
#include <stdexcept>
#include <string>

namespace Macro {

template <typename ValueType, typename KeyType, int ArraySize> class States {
  protected:
    ValueType states[ArraySize];

    inline void checkBounds(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range (index = " + std::to_string(index) +
                                    ", array size = " + std::to_string(size) + ")");
        }
    }

  public:
    static const int size = ArraySize;

    inline void fill(ValueType value) { memset(states, value, size * sizeof(ValueType)); }

    States() {}
    explicit States(ValueType value) { fill(value); }

    ~States() {}

    inline ValueType &operator[](KeyType key) {
        int index = static_cast<int>(key);
        checkBounds(index);
        return states[index];
    }

    inline const ValueType &operator[](KeyType key) const {
        int index = static_cast<int>(key);
        checkBounds(index);
        return states[index];
    }

    inline const ValueType *begin() const { return states; }
    inline const ValueType *end() const { return states + size; }

    inline ValueType *begin() { return states; }
    inline ValueType *end() { return states + size; }
};

}  // namespace Macro

#endif  // _states_h_
