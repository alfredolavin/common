#pragma once
#include <eduardino_int_types.hpp>
#include <ranges>
#include <concepts>
#include <math.h>
#include <type_traits>
#include <algorithm>

// template<u64 value> struct _smaller_int{
//     static constexpr size_t n_bytes = (log(value)/log(2)/8);
//   using type = std::tuple_element_t<(log(value)/log(2)/8), std::tuple<u8, u16, u24, u32, u64>>;
//     };

template<u64 value> using smaller_int_t = std::tuple_element_t<(size_t)(log(value)/log(2)/8), std::tuple<u8, u16, u24, u32, u64>>;

template <std::integral... Ts>
inline auto constexpr range(const Ts&&... _args) {
  using int_t = u16;//smaller_int_t<max_arg>;

  const size_t args_n = sizeof...(_args);
  const int_t args[args_n] = {(int_t)_args...}; 
  const int max_arg = std::max({_args...});

  const int_t from_count = (args_n == 1) ? 0 : args[0];
  const int_t to_count = (args_n == 1) ? args[0] : args[1];
  const int_t step = (args_n == 3) ? args[2] : 1;

  struct Iter {
    int_t count;
    int_t step;
    bool operator!=(const int_t &rhs) const {
      return count<=rhs; } // oh!!!
    void operator++() {
      count+=step; }
    auto operator*() const {
      return count; } };

  struct _range {
    int_t from_count;
    int_t to_count;
    int_t step;
    auto begin() {
      return Iter{from_count, step }; }
    auto end() {
      return to_count; } };

  return _range{std::min(from_count, to_count),
                std::max(from_count, to_count),
                step }; }


template<std::integral ... Args>
inline constexpr auto _range(Args... _args) {
  //using 

  cu16 args_n =  sizeof...(_args),
    args[] = {(uint8_t)_args...};
    u16 start = (args_n == 1) ? 0 : args[0],
    end = (args_n == 1) ? args[0] : args[1],
    step = (args_n == 3) ? args[2] : 1;

    start = std::min(start, end);
    end = std::max(start, end);

  return std::views::iota(0)
        | std::views::transform([=](uint8_t x) { return x * step + start; })
        | std::views::take_while([=](uint8_t x) { return x <= end; });
}

// template<std::integral ... Args>
// inline constexpr auto _range(Args... _args) {
//   //using 

//   cu16 args_n =  sizeof...(_args),
//     args[] = {(uint8_t)_args...};
//     u16 start = (args_n == 1) ? 0 : args[0],
//     end = (args_n == 1) ? args[0] : args[1],
//     step = (args_n == 3) ? args[2] : 1;

//     start = std::min(start, end);
//     end = std::max(start, end);



//   return std::views::iota(0)
//         | std::views::transform([=](uint8_t x) { return x * step + start; })
//         | std::views::take_while([=](uint8_t x) { return x <= end; });
// }

#define define_range(x, letter, int_type) int_type letter = 0; letter < (x); letter++

#define iRange16(x) define_range(x, i, u16)
#define iRange32(x) define_range(x, i, u32)
#define iRange(x) (auto i : range((x)))
#define jRange(x) define_range(x, j, u8)
#define kRange(x) define_range(x, k, u8)
#define xRange(_x) define_range(_x, x, u8)
#define yRange(x) define_range(x, y, u8)
#define zRange(x) define_range(x, z, u8)

#define iRangeLen(x) define_range(countof(x), i, u8)
#define jRangeLen(x) define_range(countof(x), j, u8)
#define kRangeLen(x) define_range(countof(x), k, u8)

#define iRangeLen16(x) define_range(countof(x), i, u16)
#define jRangeLen16(x) define_range(countof(x), j, u16)
#define kRangeLen16(x) define_range(countof(x), k, u16)






