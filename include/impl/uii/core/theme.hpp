// Copyright (c) 2026 UII. Licensed under the GPL-3.0 License.

#pragma once
#include "impl/uii/core/widget_base.hpp"
#include "impl/basic_storage.hpp"
#include "impl/data_utils.hpp"
#include "tx/math.h"
#include <concepts>
#include <type_traits>
#include <vector>
#include <cstring>

namespace uii {
using namespace tx::primitives;

namespace impl {
// DevNote: Move to type_traits

template <class W>
struct is_widget {
	static constexpr bool value =
	    std::derived_from<W, WidgetBase> &&
	    requires {
		    typename W::StyleSheet;
		    requires std::is_trivially_copyable_v<typename W::StyleSheet>;
		    typename W::Base;
		    requires std::same_as<typename W::Base, WidgetBase> ||
		                 is_widget<typename W::Base>::value;
		    requires requires(typename W::StyleSheet& ss) {
			    { W::setStyleSheetDefault(ss) };
		    };
		    requires std::derived_from<
		        typename W::StyleSheet, typename W::Base::StyleSheet>;
	    };
};
template <class W>
constexpr bool is_widget_v = is_widget<W>::value;

template <class W>
concept widget = is_widget_v<W>;
} // namespace impl

namespace impl {
template <widget W>
struct theme_traits {
	using StyleSheet = typename W::StyleSheet;
	using Base = typename W::Base;

	static const StyleSheet& defaultStyleSheet();
	static const u32 id;

private:
	static u32 makeId_impl();
};
} // namespace impl

class Theme {
	template <impl::widget W>
	friend struct impl::theme_traits;

public:
	// ================ Construction ================

	/**
	 * Note that since the construction of Theme requires it's static default
	 * style sheet array to be populated, and global variable initialization
	 * order is undefined, a Theme object cannot be constructed globally.
	 */

	Theme()
	    : m_ssBuffer(findSSBufferSize_impl()),
	      m_metaBuffer(defaults().size()) {
		constructBuffers_impl(
		    m_ssBuffer.data, m_metaBuffer.data, [](u32 i) {
			    return defaults()[i];
		    });
	}
	~Theme() = default;

	Theme(const Theme& other)
	    : m_ssBuffer(findSSBufferSize_impl()),
	      m_metaBuffer(defaults().size()) {
		constructBuffers_impl(
		    m_ssBuffer.data, m_metaBuffer.data, [&](u32 i) {
			    return tx::impl::at<WidgetBase::StyleSheet>(
			        other.m_ssBuffer.data + other.m_metaBuffer.data[i]);
		    });
	}
	Theme& operator=(const Theme& other) {
		constructBuffers_impl(
		    m_ssBuffer.data, m_metaBuffer.data, [&](u32 i) {
			    return tx::impl::at<WidgetBase::StyleSheet>(
			        other.m_ssBuffer.data + other.m_metaBuffer.data[i]);
		    });
		return *this;
	};
	Theme(Theme&& other) = default;
	Theme& operator=(Theme&& other) = default;

public:
	// ================ Public Interface ================

	template <impl::widget W>
	typename impl::theme_traits<W>::StyleSheet& styleSheet() {
		return *tx::impl::at<typename impl::theme_traits<W>::StyleSheet>(
		    m_ssBuffer.data + m_metaBuffer.data[impl::theme_traits<W>::id]);
	}
	template <impl::widget W>
	const typename impl::theme_traits<W>::StyleSheet& styleSheet() const {
		return *tx::impl::at<typename impl::theme_traits<W>::StyleSheet>(
		    m_ssBuffer.data + m_metaBuffer.data[impl::theme_traits<W>::id]);
	}

private:
	// ================ Static Registry ================

	static std::vector<const typename WidgetBase::StyleSheet*>& defaults() {
		static std::vector<const typename WidgetBase::StyleSheet*> local;
		return local;
	};
	struct StyleSheetMeta {
		u32 size = 0, align = 0;
	};
	static std::vector<StyleSheetMeta>& styleSheetMeta() {
		static std::vector<StyleSheetMeta> local;
		return local;
	};

private:
	// ================ Helpers ================

	static u32 findSSBufferSize_impl() {
		u32 acc = 0;
		for (StyleSheetMeta i : styleSheetMeta())
			acc += i.size + i.align - 1;
		return acc;
	}
	template <tx::invocable_r<const typename WidgetBase::StyleSheet*, u32> Func>
	static void constructBuffers_impl(u8* ptr, u32* metaPtr, Func&& f) {
		u8* begin = ptr;
		u32 i = 0;
		for (StyleSheetMeta meta : styleSheetMeta()) {
			u8* aligned = tx::nextAlign(ptr, meta.align);
			std::memcpy(aligned, f(i), meta.size);
			*(metaPtr++) = static_cast<u32>(aligned - begin);
			ptr = aligned + meta.size;
			i++;
		}
	}

private:
	tx::BasicStorage<u8> m_ssBuffer; // style sheet buffer
	tx::BasicStorage<u32> m_metaBuffer; // style sheet object offset buffer
};

namespace impl {
template <widget W>
const theme_traits<W>::StyleSheet& theme_traits<W>::defaultStyleSheet() {
	static StyleSheet local = []() {
		if constexpr (std::same_as<W, WidgetBase>) {
			return StyleSheet{};
		} else if constexpr (std::derived_from<StyleSheet, typename Base::StyleSheet>) {
			StyleSheet ret{ theme_traits<Base>::defaultStyleSheet() };
			W::setStyleSheetDefault(ret);
			return ret;
		} else {
			StyleSheet ret{};
			W::setStyleSheetDefault(ret);
			return ret;
		}
	}();
	return local;
}
template <widget W>
u32 theme_traits<W>::makeId_impl() {
	u32 id_ = Theme::defaults().size();
	Theme::defaults().push_back(&defaultStyleSheet());
	Theme::styleSheetMeta().push_back(Theme::StyleSheetMeta{
	    sizeof(StyleSheet), alignof(StyleSheet) });
	return id_;
}
template <widget W>
const u32 theme_traits<W>::id = makeId_impl();
} // namespace impl
} // namespace uii