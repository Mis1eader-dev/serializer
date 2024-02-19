#pragma once

#include <bit>
#include <cassert>
#include <string>
#include <string_view>
#include <type_traits>

namespace serializer
{
	inline constexpr bool isBigEndian = std::endian::native == std::endian::big;

	template<typename I, typename B>
	inline I rawFromBytes(const B* buf)
	{
		return *(I*)buf;
	}
	template<typename I>
	inline I rawFromBytes(std::string_view buf)
	{
		assert(buf.size() == sizeof(I));
		return *(I*)buf.data();
	}

	template<typename I, typename B>
	inline I readBE(const B* buf)
	{
		if constexpr(isBigEndian)
			return rawFromBytes<I, B>(buf);
		else
			return std::byteswap(rawFromBytes<I, B>(buf));
	}
	template<typename I>
	inline I readBE(std::string_view buf)
	{
		if constexpr(isBigEndian)
			return rawFromBytes<I>(buf);
		else
			return std::byteswap(rawFromBytes<I>(buf));
	}

	template<typename I, typename B>
	inline const B* readBE(const B* buf, I& num)
	{
		num = readBE<I, B>(buf);
		return (uint8_t*)buf + sizeof(I);
	}
	template<typename I, typename B>
	inline B* readBE(B* buf, I& num)
	{
		num = readBE<I, B>(buf);
		return (uint8_t*)buf + sizeof(I);
	}
	template<typename I>
	inline void readBE(std::string_view buf, I& num)
	{
		num = readBE<I>(buf);
	}
	/// Removes the [buf]'s prefix by that many bytes read.
	template<typename I>
	inline void readBE(I& num, std::string_view& buf)
	{
		num = readBE<I>(buf);
		buf.remove_prefix(sizeof(I));
	}

	template<typename I, typename B>
	inline B* writeRawBytes(I num, B* buf)
	{
		assert(std::is_const_v<B> == false);
		*(I*)buf = num;
		return (uint8_t*)buf + sizeof(I);
	}

	template<typename I, typename B>
	inline B* writeBE(I num, B* buf)
	{
		if constexpr(isBigEndian)
			return writeRawBytes<I, B>(num, buf);
		else
			return writeRawBytes<I, B>(std::byteswap(num), buf);
	}
	template<typename I>
	inline std::string toBEString(I num)
	{
		std::string buf(sizeof(I), '\0');
		writeBE<I>(num, buf.data());
		return buf;
	}
}
