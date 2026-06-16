// Automatic pybind11 conversion between ATL/MFC CString and Python str.
// Include this in any binding file, then CStringW/CStringA (and CString,
// which aliases one of them) can appear directly in bound signatures.
#pragma once

#include <pybind11/pybind11.h>
#include <atlstr.h>
#include <string>

namespace pybind11 {
namespace detail {

template <>
struct type_caster<CStringW> {
    PYBIND11_TYPE_CASTER(CStringW, const_name("str"));

    bool load(handle src, bool) {
        if (!isinstance<str>(src)) {
            return false;
        }
        std::wstring ws = src.cast<std::wstring>();
        value = CStringW(ws.c_str(), static_cast<int>(ws.size()));
        return true;
    }

    static handle cast(const CStringW& src, return_value_policy, handle) {
        std::wstring ws(src.GetString(), src.GetLength());
        return pybind11::cast(ws).release();
    }
};

template <>
struct type_caster<CStringA> {
    PYBIND11_TYPE_CASTER(CStringA, const_name("str"));

    bool load(handle src, bool) {
        if (!isinstance<str>(src)) {
            return false;
        }
        std::string s = src.cast<std::string>();
        value = CStringA(s.c_str(), static_cast<int>(s.size()));
        return true;
    }

    static handle cast(const CStringA& src, return_value_policy, handle) {
        std::string s(src.GetString(), src.GetLength());
        return pybind11::cast(s).release();
    }
};

} // namespace detail
} // namespace pybind11
