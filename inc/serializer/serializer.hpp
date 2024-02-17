#pragma once

#include <endian.h>
#include <string>
#include <string_view>
#include <type_traits>

namespace serializer
{
	template<typename I, typename B>
	inline I readBE(const B* buf)
	{
		constexpr auto bytes = sizeof(I);

		static_assert(bytes >= sizeof(uint8_t) && bytes <= sizeof(uint64_t), "Invalid amount of bytes");

		switch(bytes)
		{
			case sizeof(uint8_t):
				return *buf;
			case sizeof(uint16_t):
				return be16toh(*(uint16_t*)buf);
			case sizeof(uint32_t):
				return be32toh(*(uint32_t*)buf);
			case sizeof(uint64_t):
				return be64toh(*(uint64_t*)buf);
			default:
				return 0;
		}
	}
	template<typename I>
	inline I readBE(std::string_view buf)
	{
		constexpr auto bytes = sizeof(I);

		static_assert(bytes >= sizeof(uint8_t) && bytes <= sizeof(uint64_t), "Invalid amount of bytes");

		switch(bytes)
		{
			case sizeof(uint8_t):
				return *buf.data();
			case sizeof(uint16_t):
				return be16toh(*(uint16_t*)buf.data());
			case sizeof(uint32_t):
				return be32toh(*(uint32_t*)buf.data());
			case sizeof(uint64_t):
				return be64toh(*(uint64_t*)buf.data());
			default:
				return 0;
		}
	}
	template<typename I, typename B>
	inline B* readBE(B* buf, I& num)
	{
		constexpr auto bytes = sizeof(I);

		static_assert(bytes >= sizeof(uint8_t) && bytes <= sizeof(uint64_t), "Invalid amount of bytes");

		switch(bytes)
		{
			case sizeof(uint8_t):
				num = *buf;
				break;
			case sizeof(uint16_t):
				num = be16toh(*(uint16_t*)buf);
				break;
			case sizeof(uint32_t):
				num = be32toh(*(uint32_t*)buf);
				break;
			case sizeof(uint64_t):
				num = be64toh(*(uint64_t*)buf);
				break;
			default:
				return buf;
		}
		return buf + bytes;
	}
	template<typename I>
	inline void readBE(std::string_view buf, I& num)
	{
		constexpr auto bytes = sizeof(I);

		static_assert(bytes >= sizeof(uint8_t) && bytes <= sizeof(uint64_t), "Invalid amount of bytes");

		switch(bytes)
		{
			case sizeof(uint8_t):
				num = *buf.data();
				break;
			case sizeof(uint16_t):
				num = be16toh(*(uint16_t*)buf.data());
				break;
			case sizeof(uint32_t):
				num = be32toh(*(uint32_t*)buf.data());
				break;
			case sizeof(uint64_t):
				num = be64toh(*(uint64_t*)buf.data());
				break;
			default:
				return;
		}
	}

	template<typename I, typename B>
	inline B* writeBE(I num, B* buf)
	{
		static_assert(std::is_const_v<B> == false, "Buffer must not be const");

		constexpr auto bytes = sizeof(I);

		static_assert(bytes >= sizeof(uint8_t) && bytes <= sizeof(uint64_t), "Invalid amount of bytes");

		switch(bytes)
		{
			case sizeof(uint8_t):
				*buf = num;
				break;
			case sizeof(uint16_t):
				*(uint16_t*)buf = htobe16(num);
				break;
			case sizeof(uint32_t):
				*(uint32_t*)buf = htobe32(num);
				break;
			case sizeof(uint64_t):
				*(uint64_t*)buf = htobe64(num);
				break;
			default:
				return buf;
		}
		return buf + bytes;
	}
	template<typename I>
	inline std::string toBEString(I num)
	{
		constexpr auto bytes = sizeof(I);

		static_assert(bytes >= sizeof(uint8_t) && bytes <= sizeof(uint64_t), "Invalid amount of bytes");

		std::string buf(bytes, '\0');
		switch(bytes)
		{
			case sizeof(uint8_t):
				*buf.data() = num;
				break;
			case sizeof(uint16_t):
				*(uint16_t*)buf.data() = htobe16(num);
				break;
			case sizeof(uint32_t):
				*(uint32_t*)buf.data() = htobe32(num);
				break;
			case sizeof(uint64_t):
				*(uint64_t*)buf.data() = htobe64(num);
				break;
			default:
				return buf;
		}
		return buf;
	}
}
